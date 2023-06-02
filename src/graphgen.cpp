#include "ast.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace AST;

int Program::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ Program | |{";
    ss << "<c1>_Defs";
    ss << "} }\"]\n";

    if ((*_Defs).size() > 0) {
        for (auto i: (*_Defs)) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c1->N" << ch << "\n";
        }
    }
    
    return id;
}

int IfStm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ IfStm | |{";
    ss << "<c1>_Condition |";
    ss << "<c2>_Then |";
    ss << "<c3>_Else";
    ss << "} }\"]\n";

    if (_Condition) {
        int ch = _Condition->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_Then) {
        int ch = _Then->GenGraphNode(counter, ss);
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    if (_Else) {
        int ch = _Else->GenGraphNode(counter, ss);
        ss << "N" << id << ":c3->N" << ch << "\n";
    }
    
    return id;
}

int WhileStm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ WhileStm | |{";
    ss << "<c1>_Condition |";
    ss << "<c2>_LoopBody |";
    ss << "} }\"]\n";

    if (_Condition) {
        int ch = _Condition->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_LoopBody) {
        int ch = _LoopBody->GenGraphNode(counter, ss);
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    
    return id;
}

int ForStm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ ForStm | |{";
    ss << "<c1>_Initial |";
    ss << "<c2>_Condition |";
    ss << "<c3>_ExecuteInst |";
    ss << "<c4>_LoopBody";
    ss << "} }\"]\n";

    if (_Initial) {
        int ch = _Initial->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_Condition) {
        int ch = _Condition->GenGraphNode(counter, ss);
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    if (_ExecuteInst) {
        int ch = _ExecuteInst->GenGraphNode(counter, ss);
        ss << "N" << id << ":c3->N" << ch << "\n";
    }
    if (_LoopBody) {
        int ch = _LoopBody->GenGraphNode(counter, ss);
        ss << "N" << id << ":c4->N" << ch << "\n";
    }

    return id;
}

int BreakStm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ BreakStm | |  }\"]\n";
    return id;
}

int ContinueStm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ ContinueStm | |  }\"]\n";
    return id;
}

int ReturnStm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ ReturnStm | |{";
    ss << "<c1>_ReturnValue";
    ss << "} }\"]\n";

    if (_ReturnValue) {
        int ch = _ReturnValue->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    
    return id;
}

int Block::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ Block | |{";
    ss << "<c1>_Stms";
    ss << "} }\"]\n";

    if ((*_Stms).size() > 0) {
        for (auto i: (*_Stms)) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c1->N" << ch << "\n";
        }
    }
    
    return id;
}

int Variable::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ Variable | ";
    ss << "_Name = \\\"" << _Name << "\\\"";
    ss << " |  }\"]\n";
    
    return id;
}

int AST::Constant::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ Constant | ";
    ss << "_Type = " << _Type << "\\n";
    switch (_Type) {
        case VarType::TypeID::_Bool:
            ss << "_Bool = " << _Bool ? "True" : "False";
            break;
        case VarType::TypeID::_Char:
            ss << "_Character = " << _Character;
            break;
        case VarType::TypeID::_Short:
        case VarType::TypeID::_Int:
        case VarType::TypeID::_Long:
            ss << "_Int = " << _Integer;
            break;
        case VarType::TypeID::_Float:
        case VarType::TypeID::_Double:
            ss << "_Real = " << _Real;
            break;
        case VarType::TypeID::_String:
            ss << "_String = \\\"" << _String << "\\\"";
            break;
        default:
            break;
    }
    ss << " |  }\"]\n";
    
    return id;
}

int ArraySubscript::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ ArraySubscript | |{";
    ss << "<c1>_Array |";
    ss << "<c2>_IndexVal";
    ss << "} }\"]\n";
    
    if (_Array) {
        int ch = _Array->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_IndexVal) {
        int ch = _IndexVal->GenGraphNode(counter, ss);
        ss << "N" << id << ":c2->N" << ch << "\n";
    }

    return id;
}

int FuncCall::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ FuncCall | ";
    ss << "_FuncName = \\\"" << _FuncName << "\\\"";
    ss << " |{";
    ss << "<c1>_ParmList";
    ss << "} }\"]\n";
    
    if ((*_ParmList).size() > 0) {
        for (auto i: (*_ParmList)) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c1->N" << ch << "\n";
        }
    }

    return id;
}

int StructReference::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ StructReference | ";
    ss << "_Member = \\\"" << _Member << "\\\"";
    ss << " |{";
    ss << "<c1>_Struct";
    ss << "} }\"]\n";
    
    if (_Struct) {
        int ch = _Struct->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int StructDereference::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ StructDereference | ";
    ss << "_Member = \\\"" << _Member << "\\\"";
    ss << " |{";
    ss << "<c1>_Struct";
    ss << "} }\"]\n";
    
    if (_Struct) {
        int ch = _Struct->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int UnaryPlus::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ UnaryPlus | |{";
    ss << "<c1>_Operand";
    ss << "} }\"]\n";
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int UnaryMinus::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ UnaryMinus | |{";
    ss << "<c1>_Operand";
    ss << "} }\"]\n";
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int TypeCast::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ TypeCast | |{";
    ss << "<c1>_VarType | ";
    ss << "<c2>_Operand";
    ss << "} }\"]\n";
    
    if (_VarType) {
        int ch = _VarType->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c2->N" << ch << "\n";
    }

    return id;
}

int Indirection::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ Indirection | |{";
    ss << "<c1>_Operand";
    ss << "} }\"]\n";
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int AddressOf::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ AddressOf | |{";
    ss << "<c1>_Operand";
    ss << "} }\"]\n";
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int LogicNot::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ LogicNot | |{";
    ss << "<c1>_Operand";
    ss << "} }\"]\n";
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int BitwiseNot::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ BitwiseNot | |{";
    ss << "<c1>_Operand";
    ss << "} }\"]\n";
    
    if (_Operand) {
        int ch = _Operand->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int twoOperands(int& counter, stringstream& ss, string name, Exp* _LHS, Exp* _RHS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ " << name << " | |{";
    ss << "<c1>_LHS | ";
    ss << "<c2>_RHS";
    ss << "} }\"]\n";
    
    if (_LHS) {
        int ch = _LHS->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    
    if (_RHS) {
        int ch = _RHS->GenGraphNode(counter, ss);
        ss << "N" << id << ":c2->N" << ch << "\n";
    }

    return id;
}

int Division::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "Division", _LHS, _RHS);
}

int Multiplication::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "Multiplication", _LHS, _RHS);
}

int Modulo::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "Modulo", _LHS, _RHS);
}

int Addition::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "Addition", _LHS, _RHS);
}

int Subtraction::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "Subtraction", _LHS, _RHS);
}

int LeftShift::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LeftShift", _LHS, _RHS);
}

int RightShift::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "RightShift", _LHS, _RHS);
}

int LogicGT::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicGT", _LHS, _RHS);
}

int LogicGE::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicGE", _LHS, _RHS);
}

int LogicLT::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicLT", _LHS, _RHS);
}

int LogicLE::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicLE", _LHS, _RHS);
}

int LogicEQ::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicEQ", _LHS, _RHS);
}

int LogicNEQ::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicNEQ", _LHS, _RHS);
}

int BitwiseAND::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "BitwiseAND", _LHS, _RHS);
}

int BitwiseXOR::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "BitwiseXOR", _LHS, _RHS);
}

int BitwiseOR::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "BitwiseOR", _LHS, _RHS);
}

int LogicAND::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicAND", _LHS, _RHS);
}

int LogicOR::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "LogicOR", _LHS, _RHS);
}

int DirectAssign::GenGraphNode(GRAPHGEN_PARAMS) {
    return twoOperands(counter, ss, "DirectAssign", _LHS, _RHS);
}

int FuncDef::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ FuncDef | ";
    ss << "_Name = \\\"" << _Name << "\\\"";
    ss << " |{";
    ss << "<c1>_RetType |";
    ss << "<c2>_ParmList |";
    ss << "<c3>_FuncBody";
    ss << "} }\"]\n";
    
    if (_RetType) {
        int ch = _RetType->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if ((*_ParmList).size() > 0) {
        for (auto i: (*_ParmList)) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c2->N" << ch << "\n";
        }
    }
    if (_FuncBody) {
        int ch = _FuncBody->GenGraphNode(counter, ss);
        ss << "N" << id << ":c3->N" << ch << "\n";
    }

    return id;
}

int Parm::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ Parm | ";
    ss << "_Name = \\\"" << _Name << "\\\"";
    ss << " |{";
    ss << "<c1>_Type";
    ss << "} }\"]\n";
    
    if (_Type) {
        int ch = _Type->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int ParmList::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ ParmList | |{";
    ss << "<c1>_Parms(size = " << _Parms.size() << ")";
    ss << "} }\"]\n";
    
    if (_Parms.size() > 0) {
        for (auto i: _Parms) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c1->N" << ch << "\n";
        }
    }

    return id;
}

int VarDef::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ VarDef | |{";
    ss << "<c1>_Type | ";
    ss << "<c2>_VarList";
    ss << "} }\"]\n";
    
    if (_Type) {
        int ch = _Type->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if ((*_VarList).size() > 0) {
        for (auto i: (*_VarList)) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c2->N" << ch << "\n";
        }
    }

    return id;
}

int VarInit::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ VarInit | ";
    ss << "_Name = \\\"" << _Name << "\\\"";
    ss << " |{";
    ss << "<c1>_InitialExp";
    ss << "} }\"]\n";
    
    if (_InitialExp) {
        int ch = _InitialExp->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int VarType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ VarType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int TypeDef::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ TypeDef | ";
    ss << "_Alias = \\\"" << _Alias << "\\\"";
    ss << " |{";
    ss << "<c1>_VarType";
    ss << "} }\"]\n";
    
    if (_VarType) {
        int ch = _VarType->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int DefinedType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ DefinedType | ";
    ss << "_isConst = " << _isConst << "\\n";
    ss << "_Name = \\\"" << _Name << "\\\"";
    ss << " | }\"]\n";

    return id;
}

int AST::PointerType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ PointerType | ";
    ss << "_isConst = " << _isConst;
    ss << " |{";
    ss << "<c1>_BaseType";
    ss << "} }\"]\n";
    
    if (_BaseType) {
        int ch = _BaseType->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int AST::ArrayType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ ArrayType | ";
    ss << "_isConst = " << _isConst << "\\n";
    ss << "_Length = " << _Length;
    ss << " |{";
    ss << "<c1>_BaseType";
    ss << "} }\"]\n";
    
    if (_BaseType) {
        int ch = _BaseType->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int AST::StructType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ StructType | ";
    ss << "_isConst = " << _isConst;
    ss << " |{";
    ss << "<c1>_Member";
    ss << "} }\"]\n";
    
    if ((*_Member).size() > 0) {
        for (auto i: (*_Member)) {
            int ch = i->GenGraphNode(counter, ss);
            ss << "N" << id << ":c1->N" << ch << "\n";
        }
    }

    return id;
}

int StructMember::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ StructMember | ";
    for (auto i: (*_MemberList)) {
        ss << i << "\\n";
    }
    ss << " |{";
    ss << "<c1>_Type";
    ss << "} }\"]\n";
    
    if (_Type) {
        int ch = _Type->GenGraphNode(counter, ss);
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int IntType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ IntType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int CharType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ CharType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int FloatType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ FloatType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int DoubleType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ DoubleType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int StringType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ StringType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int BoolType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ BoolType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}

int VoidType::GenGraphNode(GRAPHGEN_PARAMS) {
    int id = ++ counter;
    ss << "N" << id << "[label = \"{ VoidType | ";
    ss << "_isConst = " << _isConst;
    ss << " | }\"]\n";

    return id;
}