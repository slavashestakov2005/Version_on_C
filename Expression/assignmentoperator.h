#ifndef ASSIGNMENTOPERATOR_H_INCLUDED
#define ASSIGNMENTOPERATOR_H_INCLUDED

enum class AssignmentOperator{
    ASSIGN,         /// =
    ADD,            /// +=
    SUBSTRACT,      /// -=
    MULTIPLY,       /// *=
    DIVIDE,         /// /=
    REMAINDER,      /// %=
    POWER,          /// **=

    AND,            /// &=
    OR,             /// |=
    XOR,            /// ^=
    LSHIFT,         /// <<=
    RSHIFT,         /// >>=

    PLUSPLUS_,      /// ++_
    MINUSMINUS_,    /// --_
    _PLUSPLUS,      /// _++
    _MINUSMINUS     /// _--
};

#endif // ASSIGNMENTOPERATOR_H_INCLUDED
