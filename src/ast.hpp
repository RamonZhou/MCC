/*
 * @Author: Theta 1467116498@qq.com
 * @Date: 2023-05-14 13:04:27
 * @LastEditors: Theta 1467116498@qq.com
 * @LastEditTime: 2023-05-21 20:07:10
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
#include <sstream>
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
    using Exps = std::vector<Exp*>;
        class Variable;
        class Constant;
        class Subscription;
        class ArraySubscript;
        class Sizeof;
        class FuncCall;


    class Def;
    using Defs = std::vector<Def*>;
        class FuncDef;
            class Parm;
            using Parms = std::vector<Parm*>;
            class ParmList;
        class VarDef;
            class VarInit;
            using VarList = std::vector<VarInit*>;
        class TypeDef;

    class VarType;
        class DefinedType;
		class PointerType;
		class ArrayType;
		class StructType;
            class StructMember;
            using StructMembers = std::vector<StructMember*>;
            using MemberList = std::vector<string>;
        class IntType;
        class FloatType;
        class DoubleType;
        class CharType;
        class StringType;
        class BoolType;
        class VoidType;
}

namespace AST {

#define GRAPHGEN_PARAMS int& counter, stringstream& ss

    class Node{
    public:
        Node() {}
        virtual ~Node() {}
        virtual int GenGraphNode(GRAPHGEN_PARAMS) = 0;
    };

    class Program : public Node{
    public:
        Defs* _Defs;

        Program(Defs* _Defs) :_Defs(_Defs) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Stm : public Node{
    public:
        Stm() {}
        ~Stm() {}
        virtual int GenGraphNode(GRAPHGEN_PARAMS) = 0;
    };

    class IfStm : public Stm{
    public:
        Exp* _Condition;
        Block* _Then;
        Block* _Else;

        IfStm(Exp* _Condition, Block* _Then, Block* _Else = NULL): _Condition(_Condition), _Then(_Then), _Else(_Else) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class WhileStm : public Stm{
    public:
        Exp* _Condition;
        Block* _LoopBody;

        WhileStm(Exp* _Condition, Block* _Loopbody): _Condition(_Condition), _LoopBody(_Loopbody) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class ForStm : public Stm{
    public:
        Stm* _Initial;
        Exp* _Condition;
        Stm* _ExecuteInst;
        Block* _LoopBody;

        ForStm(Stm* _Initial, Exp* _Condition, Stm* _ExecuteInst, Block* _LoopBody):
                 _Initial(_Initial), _Condition(_Condition), _ExecuteInst(_ExecuteInst), _LoopBody(_LoopBody) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class BreakStm : public Stm{
    public:
        BreakStm() {}
        ~BreakStm() {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class ContinueStm : public Stm{
    public:
        ContinueStm() {}
        ~ContinueStm() {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class ReturnStm : public Stm{
    public:
        Exp* _ReturnValue;

        ReturnStm(Exp* _ReturnValue = NULL): _ReturnValue(_ReturnValue){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Block : public Stm{
    public:
        Stms* _Stms; 

        Block(Stms* _Stms): _Stms(_Stms) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Exp : public Stm{
    public:
        Exp() {}
        ~Exp() {}
        virtual int GenGraphNode(GRAPHGEN_PARAMS) = 0;
    };

    class VarType : public Node{
    public:
        bool _isConst;

        enum TypeID {
			_Bool,
			_Short,
			_Int,
			_Long,
			_Char,
			_Float,
			_Double,
			_Void,
            _String
		};

        VarType() : _isConst(false) {};
        VarType(bool _isConst) : _isConst(_isConst) {};

        void SetConst(void) {
			this->_isConst = true;
		}
        virtual int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Variable : public Exp{
    public:
        std::string _Name;

        Variable(const std::string __Name): _Name(__Name){}
        ~Variable(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Constant : public Exp {
	public:
		VarType::TypeID _Type;
        bool _Bool;
        char _Character;
        int _Integer;
        double _Real;
        std::string _String;
        
		
		Constant(bool __Bool) :
			_Type(VarType::TypeID::_Bool), _Bool(__Bool), _Character('\0'), _Integer(0), _Real(0.0), _String("") {}
		Constant(char __Character) :
			_Type(VarType::TypeID::_Char), _Bool(false), _Character(__Character), _Integer(0), _Real(0.0), _String("") {}
		Constant(int __Integer) :
			_Type(VarType::TypeID::_Int), _Bool(false), _Character('\0'), _Integer(__Integer), _Real(0.0), _String("") {}
		Constant(double __Real) :
			_Type(VarType::TypeID::_Double), _Bool(false), _Character('\0'), _Integer(0), _Real(__Real), _String("") {}
        Constant(const std::string& __String) :
			_Type(VarType::TypeID::_String), _Bool(false), _Character('\0'), _Integer(0), _Real(0.0), _String(__String) {}
		~Constant(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class ArraySubscript : public Exp {
    public:
        Exp* _Array;
        Exp* _IndexVal;

        ArraySubscript(Exp* __Array, Exp* __IndexVal) : _Array(__Array), _IndexVal(__IndexVal) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class SizeOf : public Exp {
    public:
        Exp* _Exp;
        VarType* _VarType;
        std::string _Identifier;

        SizeOf(Exp* __Exp) : _Exp(__Exp), _VarType(NULL), _Identifier("") {}
        SizeOf(VarType* __VarType) : _Exp(NULL), _VarType(__VarType), _Identifier("") {}
        SizeOf(std::string __Identifier) : _Exp(NULL), _VarType(NULL), _Identifier(__Identifier) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class FuncCall : public Exp {
    public:
        std::string _FuncName;
        Exps* _ParmList;

        FuncCall(const std::string& __FuncName, Exps* __ParmList) : _FuncName(__FuncName), _ParmList(__ParmList) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class UnaryPlus : public Exp {
	public:
		Exp* _Operand;
		UnaryPlus(Exp* __Operand) : _Operand(__Operand) {}
		~UnaryPlus(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class UnaryMinus : public Exp {
	public:
		Exp* _Operand;
		UnaryMinus(Exp* __Operand) : _Operand(__Operand) {}
		~UnaryMinus(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class TypeCast : public Exp {
	public:
		VarType* _VarType;
		Exp* _Operand;
		TypeCast(VarType* __VarType, Exp* __Operand) : _VarType(__VarType), _Operand(__Operand) {}
		~TypeCast(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class PrefixInc : public Exp {
	public:
		Exp* _Operand;
		PrefixInc(Exp* __Operand) : _Operand(__Operand) {}
		~PrefixInc(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class PostfixInc : public Exp {
	public:
		Exp* _Operand;
		PostfixInc(Exp* __Operand) : _Operand(__Operand) {}
		~PostfixInc(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class PrefixDec : public Exp {
	public:
		Exp* _Operand;
		PrefixDec(Exp* __Operand) : _Operand(__Operand) {}
		~PrefixDec(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class PostfixDec : public Exp {
	public:
		Exp* _Operand;
		PostfixDec(Exp* __Operand) : _Operand(__Operand) {}
		~PostfixDec(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class Indirection : public Exp {
	public:
		Exp* _Operand;
		Indirection(Exp* __Operand) : _Operand(__Operand) {}
		~Indirection(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class AddressOf : public Exp {
	public:
		Exp* _Operand;
		AddressOf(Exp* __Operand) : _Operand(__Operand) {}
		~AddressOf(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class LogicNot : public Exp {
	public:
		Exp* _Operand;
		LogicNot(Exp* __Operand) : _Operand(__Operand) {}
		~LogicNot(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class BitwiseNot : public Exp {
	public:
		Exp* _Operand;
		BitwiseNot(Exp* __Operand) : _Operand(__Operand) {}
		~BitwiseNot(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Division : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        Division(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Multiplication : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        Multiplication(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Modulo : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        Modulo(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Addition : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        Addition(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class Subtraction : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        Subtraction(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LeftShift : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LeftShift(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class RightShift : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        RightShift(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LogicGT : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LogicGT(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LogicGE : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LogicGE(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LogicLT : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LogicLT(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LogicLE : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LogicLE(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LogicEQ : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LogicEQ(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };
    class LogicNEQ : public Exp{
    public:
        Exp* _LHS;
        Exp* _RHS;

        LogicNEQ(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class BitwiseAND : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		BitwiseAND(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~BitwiseAND(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class BitwiseXOR : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		BitwiseXOR(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~BitwiseXOR(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class BitwiseOR : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		BitwiseOR(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~BitwiseOR(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class LogicAND : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		LogicAND(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~LogicAND(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class LogicOR : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		LogicOR(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~LogicOR(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class TernaryCondition : public Exp {
	public:
		Exp* _Condition;
		Exp* _Then;
		Exp* _Else;
		TernaryCondition(Exp* __Condition, Exp* __Then, Exp* __Else) : _Condition(__Condition), _Then(__Then), _Else(__Else) {}
		~TernaryCondition(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class DirectAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		DirectAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~DirectAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class DivAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		DivAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~DivAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class MulAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		MulAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~MulAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class ModAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		ModAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~ModAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class AddAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		AddAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~AddAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class SubAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		SubAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~SubAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class SHLAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		SHLAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~SHLAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };
	class SHRAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		SHRAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~SHRAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class BitwiseANDAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		BitwiseANDAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~BitwiseANDAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class BitwiseXORAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		BitwiseXORAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~BitwiseXORAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

	class BitwiseORAssign : public Exp {
	public:
		Exp* _LHS;
		Exp* _RHS;
		BitwiseORAssign(Exp* __LHS, Exp* __RHS) : _LHS(__LHS), _RHS(__RHS) {}
		~BitwiseORAssign(void) {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };


    class Def : public Stm{
    public:
        Def() {}
        ~Def() {}
        virtual int GenGraphNode(GRAPHGEN_PARAMS) = 0;
    };

    class FuncDef: public Def{
    public:
        VarType* _RetType;
        std::string _Name;
        Parms* _ParmList;
        Block* _FuncBody;

        FuncDef( VarType* _RetType, const std::string _Name, Parms* _ParmList, Block* _FuncBody = NULL):
                _Name(_Name), _RetType(_RetType), _ParmList(_ParmList), _FuncBody(_FuncBody) {}

        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    //parameter 
    class Parm: public Node{
    public:
        std::string _Name;
        VarType* _Type;

        Parm(VarType* _Type, const std::string& _Name = ""): _Name(_Name), _Type(_Type) {}

        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class ParmList: public Node{
    public:
        Parms _Parms;

        ParmList(Parms _Parms): _Parms(_Parms){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class VarDef : public Def{
    public:
        VarType* _Type;
        VarList* _VarList;

        VarDef(VarType* _Type, VarList* _VarList): _Type(_Type),_VarList(_VarList) {};

        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class VarInit : public Node{
    public:
        std::string _Name;
        Exp* _InitialExp;

        VarInit(const std::string& _Name, Exp* _InitialExp = NULL): _Name(_Name), _InitialExp(_InitialExp) {}

        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class TypeDef : public Def {
	public:
		//Variable type
		VarType* _VarType;
		//Its alias
		std::string _Alias;

		TypeDef(VarType* __VarType, const std::string& __Alias) :
			_VarType(__VarType), _Alias(__Alias) {}
		~TypeDef() {}
	    int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class DefinedType : public VarType{
    public:
        std::string _Name;

        DefinedType(const std::string& __Name) : _Name(__Name) {}
		~DefinedType(void) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class PointerType : public VarType{
    public:
        VarType* _BaseType;

        PointerType(VarType* __BaseType) : _BaseType(__BaseType) {}
		~PointerType(void) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class ArrayType : public VarType{
    public:
        VarType* _BaseType;
        uint16_t _Length;

        ArrayType(VarType* __BaseType, uint16_t __Length) : _BaseType(__BaseType), _Length(__Length) {}
		ArrayType(VarType* __BaseType) : _BaseType(__BaseType), _Length(0) {}
		~ArrayType(void) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class StructType : public VarType{
    public:
        StructMembers* _Member;
        
        StructType(StructMembers* __Member) : _Member(__Member) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class StructMember : public Def{
    public:
        VarType* _Type;
        MemberList* _MemberList;

        StructMember(VarType* __Type, MemberList* __MemberList) : _Type(__Type), _MemberList(__MemberList) {}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class IntType : public VarType{
    public:
        IntType(){}
        ~IntType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class CharType : public VarType{
    public:
        CharType(){}
        ~CharType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class FloatType : public VarType{
    public:
        FloatType(){}
        ~FloatType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class DoubleType : public VarType{
    public:
        DoubleType(){}
        ~DoubleType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class StringType : public VarType{
    public:
        StringType(){}
        ~StringType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class BoolType : public VarType{
    public:
        BoolType(){}
        ~BoolType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    class VoidType : public VarType{
    public:
        VoidType(){}
        ~VoidType(){}
        int GenGraphNode(GRAPHGEN_PARAMS);
    };

    
}


#endif //_ASTNODE_H_