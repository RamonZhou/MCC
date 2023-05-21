#include "ast.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace AST;

int Program::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ Program | |{";
    ss << "<c1>_Defs";
    ss << "}}\n";

    if (_Defs) {
        int ch = _Defs->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    
    return id;
}

int IfStm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ IfStm | |{";
    ss << "<c1>_Condition |";
    ss << "<c2>_Then |";
    ss << "<c3>_Else";
    ss << "}}\n";

    if (_Condition) {
        int ch = _Condition->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_Then) {
        int ch = _Then->GenGraphNode();
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    if (_Else) {
        int ch = _Else->GenGraphNode();
        ss << "N" << id << ":c3->N" << ch << "\n";
    }
    
    return id;
}

int WhileStm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ WhileStm | |{";
    ss << "<c1>_Condition |";
    ss << "<c2>_LoopBody |";
    ss << "}}\n";

    if (_Condition) {
        int ch = _Condition->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_LoopBody) {
        int ch = _LoopBody->GenGraphNode();
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    
    return id;
}

int ForStm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ ForStm | |{";
    ss << "<c1>_Initial |";
    ss << "<c2>_Condition |";
    ss << "<c3>_ExecuteInst |";
    ss << "<c4>_LoopBody";
    ss << "}}\n";

    if (_Initial) {
        int ch = _Initial->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_Condition) {
        int ch = _Condition->GenGraphNode();
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    if (_ExecuteInst) {
        int ch = _ExecuteInst->GenGraphNode();
        ss << "N" << id << ":c3->N" << ch << "\n";
    }
    if (_LoopBody) {
        int ch = _LoopBody->GenGraphNode();
        ss << "N" << id << ":c4->N" << ch << "\n";
    }

    return id;
}

int BreakStm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ BreakStm | | }\n";
    return id;
}

int ContinueStm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ ContinueStm | | }\n";
    return id;
}

int ReturnStm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ ReturnStm | |{";
    ss << "<c1>_ReturnValue";
    ss << "}}\n";

    if (_ReturnValue) {
        int ch = _ReturnValue->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    
    return id;
}

int Block::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ Block | |{";
    ss << "<c1>_Stms";
    ss << "}}\n";

    if (_Stms) {
        int ch = _Stms->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    
    return id;
}

int Variable::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ Block | ";
    ss << "_Name = \"" << _Name << "\"";
    ss << " | }\n";
    
    return id;
}

int Constant::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ Constant | ";
    ss << "_Type = \"" << _Type << "\"\n";
    ss << "_Bool = \"" << _Bool << "\"\n";
    ss << "_Character = \"" << _Character << "\"\n";
    ss << "_Integer = \"" << _Integer << "\"\n";
    ss << "_Real = \"" << _Real << "\"";
    ss << " | }\n";
    
    return id;
}

int FuncDef::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ FuncDef | ";
    ss << "_Name = \"" << _Name << "\"";
    ss << " |{";
    ss << "<c1>_RetType |";
    ss << "<c2>_ParmList |";
    ss << "<c3>_FuncBody |";
    ss << "}\n";
    
    if (_RetType) {
        int ch = _RetType->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_ParmList) {
        int ch = _ParmList->GenGraphNode();
        ss << "N" << id << ":c2->N" << ch << "\n";
    }
    if (_FuncBody) {
        int ch = _FuncBody->GenGraphNode();
        ss << "N" << id << ":c3->N" << ch << "\n";
    }

    return id;
}

int Parm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ Parm | ";
    ss << "_Name = \"" << _Name << "\"";
    ss << " |{";
    ss << "<c1>_Type";
    ss << "}\n";
    
    if (_Type) {
        int ch = _Type->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int ParmList::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ ParmList | |{";
    ss << "<c1>_Parms(size = " << _Parms.size() << ")";
    ss << "}\n";
    
    if (_Parms.size() > 0) {
        for (auto i: _Parms) {
            int ch = i->GenGraphNode();
            ss << "N" << id << ":c1->N" << ch << "\n";
        }
    }

    return id;
}

int VarDef::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ VarDef | |{";
    ss << "<c1>_Type | ";
    ss << "<c2>_VarList";
    ss << "}\n";
    
    if (_Type) {
        int ch = _Type->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_VarList) {
        int ch = _VarList->GenGraphNode();
        ss << "N" << id << ":c2->N" << ch << "\n";
    }

    return id;
}

int Parm::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ Parm | ";
    ss << "_Name = \"" << _Name << "\"";
    ss << " |{";
    ss << "<c1>_InitialExp";
    ss << "}\n";
    
    if (_InitialExp) {
        int ch = _InitialExp->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int VarType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ VarType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int TypeDef::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ TypeDef | ";
    ss << "_Alias = \"" << _Alias << "\"";
    ss << " |{";
    ss << "<c1>_VarType";
    ss << "}\n";
    
    if (_VarType) {
        int ch = _VarType->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int DefinedType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ DefinedType | ";
    ss << "_isConst = \"" << _isConst << "\"\n";
    ss << "_Name = \"" << _Name << "\"";
    ss << " |\n";

    return id;
}

int PointerType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ PointerType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |{";
    ss << "<c1>_BaseType";
    ss << "}\n";
    
    if (_BaseType) {
        int ch = _BaseType->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int ArrayType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ ArrayType | ";
    ss << "_isConst = \"" << _isConst << "\"\n";
    ss << "_Length = \"" << _Length << "\"";
    ss << " |{";
    ss << "<c1>_BaseType";
    ss << "}\n";
    
    if (_BaseType) {
        int ch = _BaseType->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int StructType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ StructType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |{";
    ss << "<c1>_Member";
    ss << "}\n";
    
    if (_Member) {
        int ch = _Member->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }

    return id;
}

int StructMember::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ StructMember | |{";
    ss << "<c1>_Type | ";
    ss << "<c2>_MemberList";
    ss << "}\n";
    
    if (_Type) {
        int ch = _Type->GenGraphNode();
        ss << "N" << id << ":c1->N" << ch << "\n";
    }
    if (_MemberList) {
        int ch = _MemberList->GenGraphNode();
        ss << "N" << id << ":c2->N" << ch << "\n";
    }

    return id;
}

int IntType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ IntType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int CharType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ CharType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int FloatType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ FloatType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int DoubleType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ DoubleType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int StringType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ StringType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int BoolType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ BoolType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}

int VoidType::GenGraphNode() {
    int id = ++ counter;
    ss << "N" << id << "{ VoidType | ";
    ss << "_isConst = \"" << _isConst << "\"";
    ss << " |\n";

    return id;
}