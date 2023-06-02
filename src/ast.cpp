#include "ast.hpp"
#include "codegen.hpp"
#include "utils.hpp"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

Value *LogError(const char *str) {
    errs() << "\033[1;31mError: \033[0m" << str;
    return nullptr;
}

Value *LogError(string str) {
    errs() << "\033[1;31mError: \033[0m" << str;
    return nullptr;
}

Type *CalcArithMergedType(Type *lhs, Type *rhs) {
    static Type *doubleTy = mBuilder.getDoubleTy();
    static Type *floatTy = mBuilder.getFloatTy();
    static Type *intTy = mBuilder.getInt32Ty();
    static Type *charTy = mBuilder.getInt8Ty();
    static Type *boolTy = mBuilder.getInt1Ty();
    if (lhs->isPointerTy() || rhs->isPointerTy()) return nullptr;
    if (lhs->isArrayTy() || rhs->isArrayTy()) return nullptr;
    if (lhs->isStructTy() || rhs->isStructTy()) return nullptr;
    if (lhs == doubleTy || rhs == doubleTy) return doubleTy;
    if (lhs == floatTy || rhs == floatTy) return floatTy;
    if (lhs == intTy || rhs == intTy) return intTy;
    if (lhs == charTy || rhs == charTy) return charTy;
    if (lhs == boolTy || rhs == boolTy) return boolTy;
    return nullptr;
}

Value *TypeCastTo(Value *val, Type *target) {
    Type *type = val->getType();
    if (type == target) return val;
    if (type->isArrayTy() || target->isArrayTy()) return nullptr;
    if (type->isStructTy() || target->isStructTy()) return nullptr;
    if (type->isPointerTy() || target->isPointerTy()) return nullptr;
    if (type->isFloatingPointTy() && target->isFloatingPointTy()) {
        return mBuilder.CreateFPCast(val, target);
    }
    if (type->isFloatingPointTy() && target->isIntegerTy()) {
        return target == mBuilder.getInt1Ty() ? mBuilder.CreateFPToUI(val, target) :
            mBuilder.CreateFPToSI(val, target);
    }
    if (type->isIntegerTy() && target->isFloatingPointTy()) {
        return type == mBuilder.getInt1Ty() ? mBuilder.CreateUIToFP(val, target) :
            mBuilder.CreateSIToFP(val, target);
    }
    if (type->isIntegerTy() && target->isIntegerTy()) {
        return mBuilder.CreateIntCast(val, target, type->getIntegerBitWidth() != 1);
    }
    return nullptr;
}

Value *AST::Program::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "Program::GenCode()" << endl;
#endif

    if (!_Defs) return nullptr;
    Value *ret = nullptr;
    for (auto def: (*_Defs)) {
        if (def) {
            if(!(ret = def->GenCode(context))) {
                return nullptr;
            }
        }
    }
    return ret;
}

Value *TypeCastToBool(Value *value) {
    Type *type = value->getType();
    if (type->isPointerTy()) {
        return mBuilder.CreateICmpNE(
            mBuilder.CreatePtrToInt(value, mBuilder.getInt64Ty()), mBuilder.getInt64(0));
    } else if (type->isIntegerTy()) {
        if (type != mBuilder.getInt1Ty()) {
            return mBuilder.CreateICmpNE(value, ConstantInt::get(type, 0, true));
        }
        return value;
    } else if(type->isFloatingPointTy()) {
        return mBuilder.CreateFCmpONE(value, ConstantFP::get(type, 0));
    }
    return nullptr;
}

Value *AST::IfStm::GenCode(CODEGEN_PARAMS) {
    if (context->curFunction == nullptr) {
        return LogError("'if' statement can only be used inside a function.\n");
    }

    if (_Condition == nullptr) {
        return LogError("Missing 'if' condition.\n");
    }
    llvm::Value* condition = _Condition->GenCode(context);
    if (!condition) return nullptr;

    if ((condition = TypeCastToBool(condition)) == nullptr) {
        return LogError("Invalid conversion of 'if' condition to bool.\n");
    }

    BasicBlock *thenBlock = BasicBlock::Create(mContext, "then");
    BasicBlock *elseBlock = BasicBlock::Create(mContext, "else");
    BasicBlock *endBlock = BasicBlock::Create(mContext, "end");
    mBuilder.CreateCondBr(condition, thenBlock, elseBlock);

    context->curFunction->getBasicBlockList().push_back(thenBlock);
    mBuilder.SetInsertPoint(thenBlock);
    if (_Then) {
        if (!_Then->GenCode(context)) return nullptr;
    }
    if (!mBuilder.GetInsertBlock()->getTerminator()) mBuilder.CreateBr(endBlock);
    
    context->curFunction->getBasicBlockList().push_back(elseBlock);
    mBuilder.SetInsertPoint(elseBlock);
    if (_Else) {
        if (!_Else->GenCode(context)) return nullptr;
    }
    if (!mBuilder.GetInsertBlock()->getTerminator()) mBuilder.CreateBr(endBlock);
    
    context->curFunction->getBasicBlockList().push_back(endBlock);
    mBuilder.SetInsertPoint(endBlock);

    return condition;
}

Value *AST::WhileStm::GenCode(CODEGEN_PARAMS) {
    if (context->curFunction == nullptr) {
        return LogError("'while' statement can only be used inside a function.\n");
    }

    if (_Condition == nullptr) {
        return LogError("Missing 'while' condition.\n");
    }

    BasicBlock *startBlock = BasicBlock::Create(mContext, "start");
    BasicBlock *bodyBlock = BasicBlock::Create(mContext, "body");
    BasicBlock *endBlock = BasicBlock::Create(mContext, "end");

    mBuilder.CreateBr(startBlock);
    context->curFunction->getBasicBlockList().push_back(startBlock);
    mBuilder.SetInsertPoint(startBlock);

    llvm::Value* condition = _Condition->GenCode(context);
    if (!condition) return nullptr;
    
    if ((condition = TypeCastToBool(condition)) == nullptr) {
        return LogError("Invalid conversion of 'while' condition to bool.\n");
    }
    if (!mBuilder.GetInsertBlock()->getTerminator()) mBuilder.CreateCondBr(condition, bodyBlock, endBlock);

    context->curFunction->getBasicBlockList().push_back(bodyBlock);
    mBuilder.SetInsertPoint(bodyBlock);
    if (_LoopBody) {
        context->PushLoopBlocks(startBlock, endBlock);
        if (!_LoopBody->GenCode(context)) return nullptr;
        context->PopLoopBlocks();
    }
    mBuilder.CreateBr(startBlock);
    
    context->curFunction->getBasicBlockList().push_back(endBlock);
    mBuilder.SetInsertPoint(endBlock);

    return condition;
}

Value *AST::ForStm::GenCode(CODEGEN_PARAMS) {
    if (context->curFunction == nullptr) {
        return LogError("'for' statement can only be used inside a function.\n");
    }

    BasicBlock *condBlock = BasicBlock::Create(mContext, "cond");
    BasicBlock *instBlock = BasicBlock::Create(mContext, "inst");
    BasicBlock *bodyBlock = BasicBlock::Create(mContext, "body");
    BasicBlock *endBlock = BasicBlock::Create(mContext, "end");

    context->PushScope();

    if (_Initial) {
        if (!_Initial->GenCode(context)) return nullptr;
    }
    mBuilder.CreateBr(condBlock);
    context->curFunction->getBasicBlockList().push_back(condBlock);
    mBuilder.SetInsertPoint(condBlock);

    llvm::Value* condition = mBuilder.getInt1(1);
    if (_Condition) {
        if (!(condition = _Condition->GenCode(context))) return nullptr;
    }
    
    if ((condition = TypeCastToBool(condition)) == nullptr) {
        return LogError("Invalid conversion of 'for' condition to bool.\n");
    }
    mBuilder.CreateCondBr(condition, bodyBlock, endBlock);

    context->curFunction->getBasicBlockList().push_back(bodyBlock);
    mBuilder.SetInsertPoint(bodyBlock);
    if (_LoopBody) {
        context->PushLoopBlocks(instBlock, endBlock);
        if (!_LoopBody->GenCode(context)) return nullptr;
        context->PopLoopBlocks();
    }
    if (!mBuilder.GetInsertBlock()->getTerminator()) mBuilder.CreateBr(instBlock);
    
    context->curFunction->getBasicBlockList().push_back(instBlock);
    mBuilder.SetInsertPoint(instBlock);

    if (_ExecuteInst) {
        if (!_ExecuteInst->GenCode(context)) return nullptr;
    }
    mBuilder.CreateBr(condBlock);
    
    context->curFunction->getBasicBlockList().push_back(endBlock);
    mBuilder.SetInsertPoint(endBlock);

    context->PopScope();

    return condition;
}

Value *AST::BreakStm::GenCode(CODEGEN_PARAMS) {
    BasicBlock *block = context->CurEndBlock();
    if (block) {
        return mBuilder.CreateBr(block);
    } else {
        return LogError("'break' can only be used within loops.\n");
    }
}

Value *AST::ContinueStm::GenCode(CODEGEN_PARAMS) {
    BasicBlock *block = context->CurBeginBlock();
    if (block) {
        return mBuilder.CreateBr(block);
    } else {
        return LogError("'continue' can only be used within loops.\n");
    }
}

string GetTypeString(Type *type) {
    string additional = "";
    bool flag = true;
    while (flag) {
        flag = false;
        if (type->isArrayTy()) {
            additional = " ARRAY(" + to_string(type->getArrayNumElements()) + ")" + additional;
            type = type->getArrayElementType();
            flag = true;
        }
        if (type->isPointerTy()) {
            additional = " PTR" + additional;
            type = type->getPointerElementType();
            flag = true;
        }
    }
    if (type->isStructTy()) {
        return "struct" + additional;
    } else if (type == Type::getInt1Ty(mContext)) {
        return "bool" + additional;
    } else if (type == Type::getInt8Ty(mContext)) {
        return "char" + additional;
    } else if (type == Type::getInt32Ty(mContext)) {
        return "int" + additional;
    } else if (type == Type::getFloatTy(mContext)) {
        return "float" + additional;
    } else if (type == Type::getDoubleTy(mContext)) {
        return "double" + additional;
    }
    return "undefined";
}

Value *AST::ReturnStm::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "Return::GenCode()" << endl;
#endif

    Function *function = context->curFunction;
    if (!function) {
        return LogError("'return' should be used inside a function.\n");
    }
    if (!_ReturnValue) {
        if (!function->getReturnType()->isVoidTy()) {
            return LogError("Return-statement must have a value, in function returning '" + GetTypeString(function->getReturnType()) + "'.\n");
        }
        return mBuilder.CreateRetVoid();
    } else {
        Value *returnValue = _ReturnValue->GenCode(context);
        if ((returnValue = TypeCastTo(returnValue, function->getReturnType())) == nullptr) {
            return LogError("Invalid conversion from'" + GetTypeString(returnValue->getType()) + "' to '" +
                GetTypeString(function->getReturnType()) + "'.\n");
        }
        return mBuilder.CreateRet(returnValue);
    }
}

Value *AST::Block::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "Block::GenCode()" << endl;
#endif

    context->PushScope();

    Value *ret = nullptr;

    if (_Stms) {
        for (auto stm: (*_Stms)) {
            if (stm) {
                ret = stm->GenCode(context);
                if (!ret) return nullptr;
                if (mBuilder.GetInsertBlock()->getTerminator()) break;
            }
        }
    }

    context->PopScope();

    return ret;
}

Value *AST::Variable::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "Variable::GenCode()" << endl;
#endif

    CodeGenContext::SymbolType type = context->LookUpVariableSymbolType(_Name);
    if (type == CodeGenContext::SymbolType::tUndefined) {
        return LogError("Identifier undeclared: " + _Name + "\n");
    }
    if (type != CodeGenContext::SymbolType::tVariable && type != CodeGenContext::SymbolType::tConstant) {
        return LogError(_Name + " is not a variable or constant\n");
    }
    Value *val = context->LookUpVariable(_Name);
    Type *vtype = val->getType()->getPointerElementType();
    if (vtype->isArrayTy()) {
        return mBuilder.CreatePointerCast(val, vtype->getArrayElementType()->getPointerTo());
    }
    return mBuilder.CreateLoad(vtype, val, _Name.c_str());
}

Value *AST::Variable::GenPointer(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "Variable::GenPointer()" << endl;
#endif

    CodeGenContext::SymbolType type = context->LookUpVariableSymbolType(_Name);
    if (type == CodeGenContext::SymbolType::tUndefined) {
        return LogError("Identifier undeclared: " + _Name + "\n");
    }
    if (type != CodeGenContext::SymbolType::tVariable && type != CodeGenContext::SymbolType::tConstant) {
        return LogError(_Name + " is not a variable or constant\n");
    }
    Value *val = context->LookUpVariable(_Name);
    return val;
}

Value *AST::Constant::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "Constant::GenCode()" << endl;
#endif

    switch (_Type) {
        case AST::VarType::_Bool:
            return mBuilder.getInt1(this->_Bool);
        case AST::VarType::_Char:
            return mBuilder.getInt8(this->_Integer);
        case AST::VarType::_Int:
            return mBuilder.getInt32(this->_Integer);
        case AST::VarType::_Float:
            return ConstantFP::get(mBuilder.getFloatTy(), this->_Real);
        case AST::VarType::_Double:
            return ConstantFP::get(mBuilder.getDoubleTy(), this->_Real);
        case AST::VarType::_String:
            return mBuilder.CreateGlobalStringPtr(this->_String.c_str());
    }
    return LogError("Internal error: Undefined constant type.\n");
}

Value *AST::ArraySubscript::GenCode(CODEGEN_PARAMS) {
    Value *arr = _Array->GenCode(context);
    if (!arr) return nullptr;
    if (!(arr->getType()->isPointerTy())) {
        return LogError("Operator '[]' can only be used with arrays or pointers.\n");
    }
    Value *idx = _IndexVal->GenCode(context);
    if (!idx) return nullptr;
    if (!(idx->getType()->isIntegerTy())) {
        return LogError("The index of array must be a integer.\n");
    }
    Type *elemType = arr->getType()->getPointerElementType();
    Value *addr = mBuilder.CreateGEP(elemType, arr, idx);
    return elemType->isArrayTy() ?
        mBuilder.CreatePointerCast(addr, elemType->getArrayElementType()->getPointerTo()) :
        mBuilder.CreateLoad(elemType, addr);
}

Value *AST::ArraySubscript::GenPointer(CODEGEN_PARAMS) {
    Value *arr = _Array->GenCode(context);
    if (!arr) return nullptr;
    if (!(arr->getType()->isPointerTy())) {
        return LogError("Operator '[]' can only be used with arrays or pointers.\n");
    }
    Value *idx = _IndexVal->GenCode(context);
    if (!idx) return nullptr;
    if (!(idx->getType()->isIntegerTy())) {
        return LogError("The index of array must be a integer.\n");
    }
    return mBuilder.CreateGEP(arr->getType()->getPointerElementType(), arr, idx);
}

Value *AST::FuncCall::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "FuncCall::GenCode()" << endl;
#endif

    CodeGenContext::SymbolType symbolType = context->LookUpGlobalSymbolType(_FuncName);
    if (symbolType != CodeGenContext::SymbolType::tFunction) {
        return LogError(_FuncName + " is not a function.\n");
    }
    Function *function = context->mModule->getFunction(_FuncName);
    if (symbolType != CodeGenContext::SymbolType::tFunction) {
        return LogError(_FuncName + " is not a function.\n");
    }
    int numParams = function->getFunctionType()->getNumParams();
    if (!function->isVarArg() && _ParmList->size() != numParams
        || function->isVarArg() && _ParmList->size() < numParams) {
        return LogError(_FuncName + " takes " + to_string(numParams) + " params, but " +
            to_string(_ParmList->size()) + " given.\n");
    }
    vector<Value *> params;
    for (int i = 0; i < (int)_ParmList->size(); ++ i) {
        Value *val = _ParmList->at(i)->GenCode(context);
        if (i < numParams && (val = TypeCastTo(val, function->getArg(i)->getType())) == nullptr) {
            return LogError("Invalid type-casting when calling " + _FuncName + " .\n");
        }
        params.push_back(val);
    }

    return mBuilder.CreateCall(function, params);
}

Value *AST::StructReference::GenCode(CODEGEN_PARAMS) {
    Value *ptr = this->GenPointer(context);
    return mBuilder.CreateLoad(ptr->getType()->getPointerElementType(), ptr);
}

Value *AST::StructReference::GenPointer(CODEGEN_PARAMS) {
    Value *val = _Struct->GenPointer(context);
    if (val == nullptr) return nullptr;
    if (!val->getType()->getPointerElementType()->isStructTy()) {
        return LogError("Cannot request member '" + _Member + "' from a non-struct type.\n");
    }
    AST::StructType *node = context->LookUpStructType(val->getType()->getPointerElementType());
    if (node == nullptr) {
        return LogError("Internal error: Undefined struct type.\n");
    }
    Type *memType = nullptr;
    int idx = 0, flag = 0;
    for (AST::StructMember *member: *(node->_Member)) {
        for (string name: *(member->_MemberList)) {
            if (name == _Member) {
                memType = member->_Type->GetLLVMType(context);
                flag = 1;
                break;
            }
            ++ idx;
        }
        if (flag) break;
    }
    if (flag == 0) {
        return LogError("The struct has no member named '" + _Member + "'.\n");
    }
    return mBuilder.CreateGEP(val->getType()->getPointerElementType(), val,
        {mBuilder.getInt32(0), mBuilder.getInt32(idx)});
}

Value *AST::StructDereference::GenCode(CODEGEN_PARAMS) {
    Value *ptr = this->GenPointer(context);
    return mBuilder.CreateLoad(ptr->getType()->getPointerElementType(), ptr);
}

Value *AST::StructDereference::GenPointer(CODEGEN_PARAMS) {
    Value *val = _Struct->GenCode(context);
    if (val == nullptr) return nullptr;
    if (!val->getType()->getPointerElementType()->isStructTy()) {
        return LogError("Cannot request member '" + _Member + "' from a non-struct type.\n");
    }
    AST::StructType *node = context->LookUpStructType(val->getType()->getPointerElementType());
    if (node == nullptr) {
        return LogError("Internal error: Undefined struct type.\n");
    }
    Type *memType = nullptr;
    int idx = 0, flag = 0;
    for (AST::StructMember *member: *(node->_Member)) {
        for (string name: *(member->_MemberList)) {
            if (name == _Member) {
                memType = member->_Type->GetLLVMType(context);
                flag = 1;
                break;
            }
            ++ idx;
        }
        if (flag) break;
    }
    if (flag == 0) {
        return LogError("The struct has no member named '" + _Member + "'.\n");
    }
    return mBuilder.CreateGEP(val->getType()->getPointerElementType(), val,
        {mBuilder.getInt32(0), mBuilder.getInt32(idx)});
}

Value *AST::UnaryPlus::GenCode(CODEGEN_PARAMS) {
    Value *val = _Operand->GenCode(context);
    if (!val) return nullptr;
    if (val->getType()->isIntegerTy() || val->getType()->isFloatingPointTy()) {
        return val;
    }
    return LogError("Invalid use of unary '+'.\n");
}

Value *AST::UnaryMinus::GenCode(CODEGEN_PARAMS) {
    Value *val = _Operand->GenCode(context);
    if (!val) return nullptr;
    if (val->getType()->isIntegerTy()) {
        return mBuilder.CreateNeg(val);
    }
    if (val->getType()->isFloatingPointTy()) {
        return mBuilder.CreateFNeg(val);
    }
    return LogError("Invalid use of unary '-'.\n");
}

Value *AST::TypeCast::GenCode(CODEGEN_PARAMS) {
    Value *val = _Operand->GenCode(context);
    Type *type = _VarType->GetLLVMType(context);
    if (!val || !type) return nullptr;
    val = TypeCastTo(val, type);
    if (val == nullptr) {
        return LogError("Invalid type-casting.\n");
    }
    return val;
}

Value *AST::Indirection::GenCode(CODEGEN_PARAMS) {
    Value *ptr = _Operand->GenCode(context);
    if (!ptr->getType()->isPointerTy()) {
        return LogError("Operator * can only be used with pointers.\n");
    }
    return mBuilder.CreateLoad(ptr->getType()->getPointerElementType(), ptr);
}

Value *AST::Indirection::GenPointer(CODEGEN_PARAMS) {
    Value *ptr = _Operand->GenCode(context);
    if (!ptr->getType()->isPointerTy()) {
        return LogError("Operator * can only be used with pointers.\n");
    }
    return ptr;
}

Value *AST::AddressOf::GenCode(CODEGEN_PARAMS) {
    return _Operand->GenPointer(context);
}

Value *AST::AddressOf::GenPointer(CODEGEN_PARAMS) {
    return LogError("Expected r-value, but found l-value.\n");
}

Value *AST::LogicNot::GenCode(CODEGEN_PARAMS) {
    return mBuilder.CreateICmpEQ(TypeCastToBool(_Operand->GenCode(context)), mBuilder.getInt1(0));
}

Value *AST::BitwiseNot::GenCode(CODEGEN_PARAMS) {
    Value *val = _Operand->GenCode(context);
    if (!val->getType()->isIntegerTy()) {
        return LogError("Bitwise NOT operator only takes two integers.");
    }
    return mBuilder.CreateNot(val);
}

Value *AST::Division::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Invalid type conversion when doing division.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Invalid type conversion when doing division.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFDiv(lhs, rhs) : mBuilder.CreateSDiv(lhs, rhs);
}

Value *AST::Multiplication::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Invalid type conversion when doing multiplication.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Invalid type conversion when doing multiplication.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFMul(lhs, rhs) : mBuilder.CreateMul(lhs, rhs);
}

Value *AST::Modulo::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType || targetType->isFloatingPointTy()) {
        return LogError("Invalid type conversion when doing modulo.\n");
    }
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Invalid type conversion when doing modulo.\n");
    return mBuilder.CreateSRem(lhs, rhs);
}

Value *AST::Addition::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if ((lhsType->isPointerTy() && rhsType->isIntegerTy()) ||
        (rhsType->isPointerTy() && lhsType->isIntegerTy())) {
        if (lhsType->isPointerTy()) {
            return mBuilder.CreateGEP(lhsType->getPointerElementType(), lhs, rhs);
        } else {
            return mBuilder.CreateGEP(rhsType->getPointerElementType(), rhs, lhs);
        }
    } else {
        Type *targetType = CalcArithMergedType(lhsType, rhsType);
        if (!targetType) return LogError("Invalid type conversion when doing addition.\n");
        if (lhsType != targetType) {
            lhs = TypeCastTo(lhs, targetType);
        }
        if (rhsType != targetType) {
            rhs = TypeCastTo(rhs, targetType);
        }
        if (!lhs || !rhs) return LogError("Invalid type conversion when doing addition.\n");
        return targetType->isFloatingPointTy() ? mBuilder.CreateFAdd(lhs, rhs) : mBuilder.CreateAdd(lhs, rhs);
    }
}

Value *AST::Subtraction::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
		return mBuilder.CreatePtrDiff(lhs, rhs);
    }
    if ((lhsType->isPointerTy() && rhsType->isIntegerTy()) ||
        (rhsType->isPointerTy() && lhsType->isIntegerTy())) {
        if (lhsType->isPointerTy()) {
            return mBuilder.CreateGEP(lhsType->getPointerElementType(), lhs, mBuilder.CreateNeg(rhs));
        } else {
            return mBuilder.CreateGEP(rhsType->getPointerElementType(), rhs, mBuilder.CreateNeg(rhs));
        }
    } else {
        Type *targetType = CalcArithMergedType(lhsType, rhsType);
        if (!targetType) return LogError("Invalid type conversion when doing subtraction.\n");
        if (lhsType != targetType) {
            lhs = TypeCastTo(lhs, targetType);
        }
        if (rhsType != targetType) {
            rhs = TypeCastTo(rhs, targetType);
        }
        if (!lhs || !rhs) return LogError("Invalid type conversion when doing subtraction.\n");
        return targetType->isFloatingPointTy() ? mBuilder.CreateFSub(lhs, rhs) : mBuilder.CreateSub(lhs, rhs);
    }
}

Value *AST::LeftShift::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType || targetType->isFloatingPointTy()) {
        return LogError("Bitwise SHL operator only takes two integers.\n");
    }
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Bitwise SHL operator only takes two integers.\n");
    return mBuilder.CreateShl(lhs, rhs);
}

Value *AST::RightShift::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType || targetType->isFloatingPointTy()) {
        return LogError("Bitwise SHR operator only takes two integers.\n");
    }
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Bitwise SHR operator only takes two integers.\n");
    return mBuilder.CreateAShr(lhs, rhs);
}

Value *AST::LogicGT::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
        return mBuilder.CreateICmpUGT(mBuilder.CreatePtrToInt(lhs, mBuilder.getInt64Ty()),
            mBuilder.CreatePtrToInt(rhs, mBuilder.getInt64Ty()));
    }
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Cannot compare with these two types.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Cannot compare with these two types.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFCmpOGT(lhs, rhs) : mBuilder.CreateICmpSGT(lhs, rhs);
}

Value *AST::LogicGE::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
        return mBuilder.CreateICmpUGE(mBuilder.CreatePtrToInt(lhs, mBuilder.getInt64Ty()),
            mBuilder.CreatePtrToInt(rhs, mBuilder.getInt64Ty()));
    }
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Cannot compare with these two types.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Cannot compare with these two types.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFCmpOGE(lhs, rhs) : mBuilder.CreateICmpSGE(lhs, rhs);
}

Value *AST::LogicLT::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
        return mBuilder.CreateICmpULT(mBuilder.CreatePtrToInt(lhs, mBuilder.getInt64Ty()),
            mBuilder.CreatePtrToInt(rhs, mBuilder.getInt64Ty()));
    }
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Cannot compare with these two types.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Cannot compare with these two types.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFCmpOLT(lhs, rhs) : mBuilder.CreateICmpSLT(lhs, rhs);
}

Value *AST::LogicLE::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
        return mBuilder.CreateICmpULE(mBuilder.CreatePtrToInt(lhs, mBuilder.getInt64Ty()),
            mBuilder.CreatePtrToInt(rhs, mBuilder.getInt64Ty()));
    }
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Cannot compare with these two types.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Cannot compare with these two types.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFCmpOLE(lhs, rhs) : mBuilder.CreateICmpSLE(lhs, rhs);
}

Value *AST::LogicEQ::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
        return mBuilder.CreateICmpEQ(mBuilder.CreatePtrToInt(lhs, mBuilder.getInt64Ty()),
            mBuilder.CreatePtrToInt(rhs, mBuilder.getInt64Ty()));
    }
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Cannot compare with these two types.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Cannot compare with these two types.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFCmpOEQ(lhs, rhs) : mBuilder.CreateICmpEQ(lhs, rhs);
}

Value *AST::LogicNEQ::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    if (lhsType->isPointerTy() && lhsType == rhsType) {
        return mBuilder.CreateICmpNE(mBuilder.CreatePtrToInt(lhs, mBuilder.getInt64Ty()),
            mBuilder.CreatePtrToInt(rhs, mBuilder.getInt64Ty()));
    }
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType) return LogError("Cannot compare with these two types.\n");
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Cannot compare with these two types.\n");
    return targetType->isFloatingPointTy() ? mBuilder.CreateFCmpONE(lhs, rhs) : mBuilder.CreateICmpNE(lhs, rhs);
}

Value *AST::BitwiseAND::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType || targetType->isFloatingPointTy()) {
        return LogError("Bitwise AND operator only takes two integers.\n");
    }
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Bitwise AND operator only takes two integers.\n");
    return mBuilder.CreateAnd(lhs, rhs);
}

Value *AST::BitwiseXOR::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType || targetType->isFloatingPointTy()) {
        return LogError("Bitwise XOR operator only takes two integers.\n");
    }
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Bitwise XOR operator only takes two integers.\n");
    return mBuilder.CreateXor(lhs, rhs);
}

Value *AST::BitwiseOR::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    Type *targetType = CalcArithMergedType(lhsType, rhsType);
    if (!targetType || targetType->isFloatingPointTy()) {
        return LogError("Bitwise OR operator only takes two integers.\n");
    }
    if (lhsType != targetType) {
        lhs = TypeCastTo(lhs, targetType);
    }
    if (rhsType != targetType) {
        rhs = TypeCastTo(rhs, targetType);
    }
    if (!lhs || !rhs) return LogError("Bitwise OR operator only takes two integers.\n");
    return mBuilder.CreateOr(lhs, rhs);
}

Value *AST::LogicAND::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    lhs = TypeCastToBool(lhs);
    rhs = TypeCastToBool(rhs);
    if (!lhs || !rhs) return LogError("Error when converting operands to bool.\n");
    return mBuilder.CreateAnd(lhs, rhs);
}

Value *AST::LogicOR::GenCode(CODEGEN_PARAMS) {
    Value* lhs = this->_LHS->GenCode(context);
    Value* rhs = this->_RHS->GenCode(context);
    Type* lhsType = lhs->getType();
    Type* rhsType = rhs->getType();
    if (!lhs || !rhs) return nullptr;
    lhs = TypeCastToBool(lhs);
    rhs = TypeCastToBool(rhs);
    if (!lhs || !rhs) return LogError("Error when converting operands to bool.\n");
    return mBuilder.CreateOr(lhs, rhs);
}

Value *AST::DirectAssign::GenCode(CODEGEN_PARAMS) {
    Value *lhs = _LHS->GenPointer(context);
    Value *rhs = _RHS->GenCode(context);
    if (!lhs || !rhs) return nullptr;
    if (lhs->getType()->getPointerElementType()->isArrayTy()) {
        return LogError("Cannot assign value to an array.\n");
    }
    if (lhs->getType()->getPointerElementType()->isPointerTy()) {
        return LogError("Cannot assign value to a pointer.\n");
    }
    if (lhs->getType()->getPointerElementType()->isStructTy()) {
        return LogError("Cannot assign value to a struct.\n");
    }
    if (!(rhs = TypeCastTo(rhs, lhs->getType()->getPointerElementType()))) {
        return LogError("Invalid type conversion when assigning value.\n");
    }
    mBuilder.CreateStore(rhs, lhs);
    return mBuilder.CreateLoad(lhs->getType()->getPointerElementType(), lhs);
}

Value *AST::DirectAssign::GenPointer(CODEGEN_PARAMS) {
    Value *lhs = _LHS->GenPointer(context);
    Value *rhs = _RHS->GenCode(context);
    if (!lhs || !rhs) return nullptr;
    if (lhs->getType()->getPointerElementType()->isArrayTy()) {
        return LogError("Cannot assign value to an array.\n");
    }
    if (lhs->getType()->getPointerElementType()->isPointerTy()) {
        return LogError("Cannot assign value to a pointer.\n");
    }
    if (lhs->getType()->getPointerElementType()->isStructTy()) {
        return LogError("Cannot assign value to a struct.\n");
    }
    if (!(rhs = TypeCastTo(rhs, lhs->getType()->getPointerElementType()))) {
        return LogError("Invalid type conversion when assigning value.\n");
    }
    mBuilder.CreateStore(rhs, lhs);
    return lhs;
}

bool CompareFunctionType(FunctionType *x, FunctionType *y) {
    if (x->getReturnType() != y->getReturnType()) return false;
    if (x->getNumParams() != y->getNumParams()) return false;
    for (unsigned i = 0; i < x->getNumParams(); ++ i) {
        if (x->params()[i] != y->params()[i]) return false;
    }
    return true;
}

Value *AST::FuncDef::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "FuncDef::GenCode()" << endl;
#endif

    if (context->curFunction != nullptr) {
        return LogError("Declaration of function (" + _Name + ") is not allowed inside another function.\n");
    }

    vector<Type*> parmTypes;
    bool hasVoid = false;
    for (auto parm: (*_ParmList)) {
        Type *type = parm->_Type->GetLLVMType(context);
        if (!type) {
            return LogError("Undefined type " +
                reinterpret_cast<AST::DefinedType *>(parm->_Type)->_Name +
                " of function " + _Name + ".\n");
        }
        if (type->isVoidTy()) {
            hasVoid = true;
            if (parm->_Name != "") {
                return LogError("invalid use of type 'void' in parameter declaration.\n");
            }
        }
        // TODO array param
        parmTypes.push_back(type);
    }
    if (parmTypes.size() > 1 && hasVoid) {
        return LogError("invalid use of type 'void' in parameter declaration.\n");
    }
    if (hasVoid) {
        parmTypes.clear();
    }
    
    Type *returnType = _RetType->GetLLVMType(context);
    FunctionType *ftype = FunctionType::get(returnType, makeArrayRef(parmTypes), false);
    Function *function = nullptr;

    if (context->isDefinedGlobally(_Name)) {
        // pre defined
        function = context->mModule->getFunction(_Name);
        if (CompareFunctionType(ftype, function->getFunctionType()) == false) {
            LogError("Ambiguous declaration of function " + _Name + ".\n");
        }
        if (!function->empty() && _FuncBody) {
            LogError("Duplicated definition of function " + _Name + ".\n");
        }
    } else {
        function = Function::Create(ftype, GlobalValue::ExternalLinkage, _Name.c_str(), context->mModule.get());
        context->AddGlobalDefinition(_Name, CodeGenContext::SymbolType::tFunction);
    }

    if (_FuncBody) {
        BasicBlock *funcBlock = BasicBlock::Create(mContext, "entry", function);
        mBuilder.SetInsertPoint(funcBlock);
        context->PushScope();

        auto parm = _ParmList->begin();
        for (auto &arg: function->args()) {
            AllocaInst *alloca = mBuilder.CreateAlloca((*parm)->_Type->GetLLVMType(context),
                nullptr, (*parm)->_Name);
            mBuilder.CreateStore(&arg, alloca);
            context->AddDefinition((*parm)->_Name, alloca, CodeGenContext::SymbolType::tVariable);
        }
        context->curFunction = function;
        context->PushScope();
        _FuncBody->GenCode(context);
        if (!funcBlock->getTerminator()) {
            if (!returnType->isVoidTy()) mBuilder.CreateRet(UndefValue::get(returnType));
            else mBuilder.CreateRetVoid();
        }
        context->PopScope();    
        context->curFunction = nullptr;
        context->PopScope();
    }

    return function;
}

Value *AST::Parm::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::ParmList::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::VarDef::GenCode(CODEGEN_PARAMS) {
#ifdef DEBUG
    cerr << "VarDef::GenCode()" << endl;
#endif

    Type *type = _Type->GetLLVMType(context);
    if (type == nullptr) {
        return nullptr; //LogError("Type " + reinterpret_cast<AST::DefinedType *>(_Type)->_Name + " is not defined.\n");
    }
    if (_Type->isVoid() && !_Type->isPointer()) {
        return LogError("Cannot define void variables.\n");
    }

    if (_VarList->size() == 0) {
        return LogError("Nothing is declared.\n");
    }
    
    Value *ret = nullptr;
    if (context->curFunction) {
        for (auto var: (*_VarList)) {
            if (context->isDefinedInCurrentScope(var->_Name)) {
                return LogError("Duplicated definition of " + var->_Name + ".\n");
            }
            Value *initialExp = nullptr;
            if (var->_InitialExp) {
                initialExp = var->_InitialExp->GenCode(context); // TODO: type casting
                if (initialExp == nullptr) {
                    return nullptr;
                }
            }
            AllocaInst *alloc = mBuilder.CreateAlloca(type, nullptr, var->_Name);
            if (initialExp) mBuilder.CreateStore(initialExp, alloc);
            context->AddDefinition(var->_Name, alloc, _Type->_isConst ?
                CodeGenContext::SymbolType::tConstant : CodeGenContext::SymbolType::tVariable);
            ret = alloc;
        }
    } else {
        // global variables
        for (auto var: (*_VarList)) {
            if (context->isDefinedInCurrentScope(var->_Name)) {
                return LogError("Duplicated definition of " + var->_Name + ".\n");
            }
            llvm::Constant *initialExp = nullptr;
            if (var->_InitialExp) {
                if (!var->_InitialExp->isConstant()) {
                    return LogError("Global variables can only be initialized with constants.\n");
                }
                Value *exp = var->_InitialExp->GenCode(context); // TODO: type casting
                if (exp == nullptr) {
                    return nullptr;
                }
                initialExp = reinterpret_cast<llvm::Constant *>(exp);
            }

            context->mModule->getOrInsertGlobal(var->_Name, type);
            GlobalVariable *globalVar = context->mModule->getNamedGlobal(var->_Name);
            globalVar->setLinkage(GlobalValue::InternalLinkage);
            if (initialExp) globalVar->setInitializer(initialExp);
            else globalVar->setInitializer(UndefValue::get(type));
            context->AddDefinition(var->_Name, globalVar, _Type->_isConst ?
                CodeGenContext::SymbolType::tConstant : CodeGenContext::SymbolType::tVariable);

            ret = globalVar;
        }
    }

    return ret;
}

Value *AST::VarInit::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::TypeDef::GenCode(CODEGEN_PARAMS) {
    Type *type = _VarType->GetLLVMType(context);
    if (type == nullptr) return nullptr;
    if (context->LookUpVariableSymbolType(_Alias) != CodeGenContext::SymbolType::tUndefined) {
        return LogError("Type alias '" + _Alias + "' has already been declared.\n");
    }
    context->AddDefinition(_Alias, reinterpret_cast<Value *>(type), CodeGenContext::SymbolType::tType);
    return reinterpret_cast<Value *>(type);
}

Value *AST::DefinedType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Type *AST::DefinedType::GetLLVMType(CODEGEN_PARAMS) {
    if (context->LookUpVariableSymbolType(_Name) != CodeGenContext::SymbolType::tType) {
        LogError("'" + _Name + "' is not a defined type.\n");
        return nullptr;
    }
    Type *type = reinterpret_cast<Type *>(context->LookUpVariable(_Name));
    return type;
}

Value *AST::PointerType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Type *AST::PointerType::GetLLVMType(CODEGEN_PARAMS) {
    if (_LLVMType) return _LLVMType;
    Type *elemType = _BaseType->GetLLVMType(context);
    return _LLVMType = llvm::PointerType::get(elemType, 0);
}

Value *AST::ArrayType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Type *AST::ArrayType::GetLLVMType(CODEGEN_PARAMS) {
    if (_LLVMType) return _LLVMType;
    Type *elemType = _BaseType->GetLLVMType(context);
    if (elemType->isVoidTy()) {
        LogError("Illegal declaration: an array of void.\n");
        return nullptr;
    }
    return _LLVMType = llvm::ArrayType::get(elemType, _Length);
}

Value *AST::StructType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Type *AST::StructType::GetLLVMType(CODEGEN_PARAMS) {
    if (_LLVMType) return _LLVMType;
    _LLVMType = llvm::StructType::create(mContext);
    // context->AddStructType(_LLVMType, this);
    vector<Type *> members;
    for (StructMember *i: (*_Member)) {
        Type *memType = i->_Type->GetLLVMType(context);
        if (memType == nullptr) return nullptr;
        for (int _ = 0; _ < (int)(i->_MemberList->size()); ++ _) {
            members.push_back(memType);
        }
    }
    ((llvm::StructType *)_LLVMType)->setBody(members);
    context->AddStructType(_LLVMType, this);
    return _LLVMType;
}

Value *AST::StructMember::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::IntType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::CharType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::FloatType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::DoubleType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::StringType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::BoolType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}

Value *AST::VoidType::GenCode(CODEGEN_PARAMS) {
    return nullptr;
}