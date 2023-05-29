#include "codegen.hpp"
#include "ast.hpp"

LLVMContext mContext;
IRBuilder<> mBuilder(mContext);

CodeGenContext::CodeGenContext() {
    mModule = make_unique<Module>("main", mContext);
    curFunction = NULL;
    mGlobalSymbolTable = make_unique<SymbolTable>();
}

void CodeGenContext::PushScope() {
    mSymbolTables.push_back(make_unique<SymbolTable>());
    mValueTables.push_back(make_unique<ValueTable>());
}

void CodeGenContext::PopScope() {
    if (mSymbolTables.size()) mSymbolTables.pop_back();
    if (mValueTables.size()) mValueTables.pop_back();
}

Value *CodeGenContext::LookUpVariable(string name) {
    for (auto it = mValueTables.rbegin(); it != mValueTables.rend(); ++ it) {
        if ((*it)->find(name) != (*it)->end()) {
            return (*it)->find(name)->second;
        }
    }
    return nullptr;
}

Type *CodeGenContext::LookUpVariableLLVMType(string name) {
    for (auto it = mValueTables.rbegin(); it != mValueTables.rend(); ++ it) {
        if ((*it)->find(name) != (*it)->end()) {
            return (*it)->find(name)->second->getType();
        }
    }
    return nullptr;
}

CodeGenContext::SymbolType CodeGenContext::LookUpVariableSymbolType(string name) {
    for (auto it = mSymbolTables.rbegin(); it != mSymbolTables.rend(); ++ it) {
        if ((*it)->find(name) != (*it)->end()) {
            return (*it)->find(name)->second;
        }
    }
    return CodeGenContext::SymbolType::tUndefined;
}

void CodeGenContext::AddDefinition(string name, Value *value, CodeGenContext::SymbolType type) {
    if (mSymbolTables.size() == 0 || mValueTables.size() == 0) return;
    mValueTables.back()->insert(make_pair(name, value));
    mSymbolTables.back()->insert(make_pair(name, type));
}

bool CodeGenContext::isDefinedInCurrentScope(string name) {
    if (mSymbolTables.size() == 0 || mValueTables.size() == 0) return false;
    return mSymbolTables.back()->find(name) != mSymbolTables.back()->end();
}

CodeGenContext::SymbolType CodeGenContext::LookUpGlobalSymbolType(string name) {
    if (mGlobalSymbolTable->find(name) != mGlobalSymbolTable->end()) {
        return mGlobalSymbolTable->find(name)->second;
    }
    return CodeGenContext::SymbolType::tUndefined;
}

void CodeGenContext::AddGlobalDefinition(string name, CodeGenContext::SymbolType type){
    mGlobalSymbolTable->insert(make_pair(name, type));
}

bool CodeGenContext::isDefinedGlobally(string name) {
    return mGlobalSymbolTable->find(name) != mGlobalSymbolTable->end();
}

void CodeGenContext::PushLoopBlocks(BasicBlock *beginBlock, BasicBlock *endBlock) {
    mLoopBeginBlocks.push_back(beginBlock);
    mLoopEndBlocks.push_back(endBlock);
}

void CodeGenContext::PopLoopBlocks() {
    mLoopBeginBlocks.pop_back();
    mLoopEndBlocks.pop_back();
}

BasicBlock *CodeGenContext::CurBeginBlock() {
    return mLoopBeginBlocks.size() ? mLoopBeginBlocks.back() : nullptr;
}

BasicBlock *CodeGenContext::CurEndBlock() {
    return mLoopEndBlocks.size() ? mLoopEndBlocks.back() : nullptr;
}

bool CodeGenContext::GenerateIRCode(AST::Program *Root) {
#ifdef DEBUG
    cerr << "Generating IRCode\n";
#endif

    while (!mLoopBeginBlocks.empty()) mLoopBeginBlocks.pop_back();
    while (!mLoopEndBlocks.empty()) mLoopEndBlocks.pop_back();
    while (!mValueTables.empty()) mValueTables.pop_back();
    while (!mSymbolTables.empty()) mSymbolTables.pop_back();
    curFunction = nullptr;

    PushScope(); // global variables

    // Define printf
    std::vector<Type *> printfArgs;
    printfArgs.push_back(mBuilder.getInt8Ty()->getPointerTo());
    ArrayRef<Type*> argsRef(printfArgs);
    FunctionType *printfType = FunctionType::get(mBuilder.getInt32Ty(), argsRef, true);
    // Constant *printfFunc = mModule->getOrInsertFunction("printf", printfType);
    auto printf_func = Function::Create(printfType, GlobalValue::ExternalLinkage, "printf", mModule.get());
    AddGlobalDefinition("printf", SymbolType::tFunction);
    auto scanf_func = Function::Create(printfType, GlobalValue::ExternalLinkage, "scanf", mModule.get());
    AddGlobalDefinition("scanf", SymbolType::tFunction);
    
    Value *ret = Root->GenCode(this);

    PopScope();

    return ret != nullptr;
}

bool CodeGenContext::OutputIRCode(string filename) {
    std::error_code EC;
	llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OF_None);
	if (EC) {
		errs() << "Could not open file: " + EC.message() + "\n";
		return false;
	}
    mModule->print(dest, nullptr);
    dest.flush();
    dest.close();
    return true;
}

bool CodeGenContext::GenerateExecutable(string filename, string options) {
#ifdef DEBUG
    cerr << "Generating executable: " << filename << " | " << options << endl;
#endif

    string llcCommand = "llc-12";
    if(system("command -v llc-12 >/dev/null 2>&1")) {
        if (system("command -v llc >/dev/null 2>&1")) {
            errs() << "\033[1;31mFatal error: \033[0mllc is not installed.\n";
            return false;
        } else {
            llcCommand = "llc";
        }
    }

    string gccCommand = "gcc";
    if(system("command -v gcc >/dev/null 2>&1")) {
        if (system("command -v clang >/dev/null 2>&1")) {
            errs() << "\033[1;31mFatal error: \033[0mgcc/clang is not installed.\n";
            return false;
        } else {
            gccCommand = "clang";
        }
    }

    OutputIRCode(filename + ".ll");
    return system((
        llcCommand + " " + options + " " + filename + ".ll -o " + filename + ".s && " +
        gccCommand + " " + filename + ".s -o " + filename + " -no-pie").c_str()) == 0;
}