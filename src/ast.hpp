/*
 * @Author: Theta 1467116498@qq.com
 * @Date: 2023-05-14 13:04:27
 * @LastEditors: Theta 1467116498@qq.com
 * @LastEditTime: 2023-05-15 14:06:23
 * @FilePath: /MCC/src/ast.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _ASTNODE_H_

#define _ASTNODE_H_

#include "llvm/ADT/STLExtras.h"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <llvm/IR/Value.h>
#include <string>
#include <vector>

using namespace std;

namespace AST{

    class Node;

    //root node
    class Program;

    class Stm;
    using Stms = std::vector<Stm*>;
        class IfStm;
        class WhileStm;
        class ForStm;
        class BreakStm;
        class ContinueStm;
        class ReturnStm;
        class Block;

    class Exp;
        class Variable;
        class Constant;
        class Subscription;
        class FuncCall;

    class Def;
    using Defs = std::vector<Def*>;
        class FuncDef;
            class Parm;
            using Parms = std::vector<Parm*>;
            class ParmList;
        class VarDef;

    class VarType;
        class DefinedType;
		class PointerType;
		class ArrayType;
		class StructType;
        class IntType;
        class FloatType;
        class CharType;
        class StringType;
        class ArrayType;
}

namespace AST {

    class Node{
    public:
        Node() {}
        virtual ~Node() {}
    };

    class Program : public Node{
    public:
        Defs* _Defs;

        Program(Defs* _Defs) :_Defs(_Defs) {}
    };

    class Stm : public Node{
    public:
        Stm() {}
        ~Stm() {}
    };

    class IfStm : public Stm{
    public:
        Exp* _Condition;
        Stm* _Then;
        Stm* _Else;

        IfStm(Exp* _Condition, Stm* _Then, Stm* _Else = NULL): _Condition(_Condition), _Then(_Then), _Else(_Else) {}
    };

    class WhileStm : public Stm{
    public:
        Exp* _Condition;
        Stm* _LoopBody;

        WhileStm(Exp* _Condition, Stm* _Loopbody): _Condition(_Condition), _LoopBody(_Loopbody) {}
    };

    class ForStm : public Stm{
    public:
        Stm* _Initial;
        Exp* _Condition;
        Stm* _ExecuteInst;
        Stm* _LoopBody;

        ForStm(Stm* _Initial, Exp* _Condition, Stm* _ExecuteInst, Stm* _Loopbody):
                 _Initial(_Initial), _Condition(_Condition), _ExecuteInst(_ExecuteInst), _LoopBody(_LoopBody) {}
    };

    class BreakStm : public Stm{
    public:
        BreakStm() {}
        ~BreakStm() {}
    };

    class ContinueStm : public Stm{
    public:
        ContinueStm() {}
        ~ContinueStm() {}
    };

    class ReturnStm : public Stm{
    public:
        Exp* _ReturnValue;

        ReturnStm(Exp* _ReturnValue): _ReturnValue(_ReturnValue){}
    };

    class Block : public Stm{
    public:
        Stms* _Stms; 

        Block(Stms* _Stms): _Stms(_Stms) {}
    };

    class Exp : public Node{
    public:
        Exp() {}
        ~Exp() {}
    };



    class Def : public Stm{
    public:
        Def() {}
        ~Def() {}
    };

    class FuncDef: public Def{
    public:

        std::string _Name;

        VarType* _RetType;

        ParmList* _ParmList;

        Block* _FuncBody;

        Fundef(std::string _Name)

    };

    //parameter 
    class Parm: public Node{
    public:

        std::string _Name;

        VarType* _Type;

        Parm(VarType* _Type,std::string _Name, ): _Name(_Name), _Type(_Type) {}

    };

    class ParmList: public Node{
    public:
        Parms _Parms;

        ParmList(Parms _Parms): _Parms(_Parms){}
    };



    

    class VarType : public Node{
    public:
        bool _isConst;


        VarType() : _isConst(false) {};
        VarType(bool _isConst) : _isConst(_isConst) {};
    };

    
}


#endif //_ASTNODE_H_