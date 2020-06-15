#ifndef CONDITIONALOPERATOR_H_INCLUDED
#define CONDITIONALOPERATOR_H_INCLUDED

enum class ConditionalOperator{
    EQUALS,     /// ==
    NOT_EQUALS, /// !=

    LT,         /// <
    LTEQ,       /// <=
    GT,         /// >
    GTEQ,       /// >=

    AND,        /// &&
    OR          /// ||
};

#endif // CONDITIONALOPERATOR_H_INCLUDED
