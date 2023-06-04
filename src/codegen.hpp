#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <deque>
#include <string>
#include <exception>
#include <unordered_map>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include "ast.hpp"

using namespace llvm;
using namespace std;

extern LLVMContext mContext;
extern IRBuilder<> mBuilder;

class CodeGenContext {
public:

    enum SymbolType {
        tVariable,
        tConstant,
        tFunction,
        tType,
        tUndefined
    };

    using SymbolTable = unordered_map<string, SymbolType>;
    using ValueTable = unordered_map<string, Value *>;
    using StructTable = unordered_map<Type *, AST::StructType *>;

    CodeGenContext();
    ~CodeGenContext() {}

    // add new define scope
    void PushScope();
    // pop the top define scope
    void PopScope();

    Value *LookUpVariable(string name);
    Type *LookUpVariableLLVMType(string name);
    SymbolType LookUpVariableSymbolType(string name);
    void AddDefinition(string name, Value *value, SymbolType type);
    bool isDefinedInCurrentScope(string name);
    
    SymbolType LookUpGlobalSymbolType(string name);
    void AddGlobalDefinition(string name, SymbolType type);
    bool isDefinedGlobally(string name);

    void AddStructType(Type *type, AST::StructType *node);
    AST::StructType *LookUpStructType(Type *type);

    void PushLoopBlocks(BasicBlock *beginBlock, BasicBlock *endBlock);
    void PopLoopBlocks();
    BasicBlock *CurBeginBlock();
    BasicBlock *CurEndBlock();

    bool GenerateIRCode(AST::Program *Root);
    bool OutputIRCode(string filename);
    bool GenerateExecutable(string filename, string options);

    unique_ptr<Module> mModule;
    Function *curFunction;

private:
    BasicBlock *mGlobalBlock;
    deque<BasicBlock *> mLoopBeginBlocks;
    deque<BasicBlock *> mLoopEndBlocks;
    deque<unique_ptr<SymbolTable>> mSymbolTables;
    deque<unique_ptr<ValueTable>> mValueTables;
    unique_ptr<SymbolTable> mGlobalSymbolTable;
    unique_ptr<StructTable> mStructTable;
};