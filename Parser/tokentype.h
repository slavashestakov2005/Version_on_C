#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

enum class TokenType{
    NUMBER,
    HEX_NUMBER,
    WORD,
    TEXT,

    ///keywords
    PRINT,
    PRINTLN,
    IF,
    ELIF,
    ELSE,
    WHILE,
    FOR,
    DO,
    BREAK,
    CONTINUE,
    DEF,
    RETURN,
    IMPORT,
    SWITCH,
    CASE,
    DEFAULT,
    TRY,
    THROW,
    CATCH,
    CLASS,
    NEW,

    PLUS,       /// +
    MINUS,      /// -
    STAR,       /// *
    SLASH,      /// /
    PERCENT,    /// %

    PLUSEQ,     /// +=
    MINUSEQ,    /// -=
    STAREQ,     /// *=
    SLASHEQ,    /// /=
    PERCENTEQ,  /// %=

    LTLT,       /// <<
    LTLTEQ,     /// <<=
    GTGT,       /// >>
    GTGTEQ,     /// >>=

    PLUSPLUS,   /// ++
    MINUSMINUS, /// --

    EQ,         /// =
    EQEQ,       /// ==
    EXCL,       /// ОТРИЦАНИЕ
    EXCLEQ,     /// !=
    LT,         /// <
    LTEQ,       /// <=
    GT,         /// >
    GTEQ,       /// >=

    BAR,        /// |
    BARBAR,     /// ||
    AMP,        /// &
    AMPAMP,     /// &&
    CARET,      /// ^
    TILDE,      /// ~

    BAREQ,      /// |=
    AMPEQ,      /// &=
    CARETEQ,    /// ^=

    QUESTION,   /// ?
    COLON,      /// :
    COLONCOLON, /// ::
    COMMA,      /// ,
    DOT,        /// .

    LPAREN,     /// (
    RPAREN,     /// )
    LBRACE,     /// {
    RBRACE,     /// }
    LBRACKET,   /// [
    RBRACKET,   /// ]

    END_OF_FILE
};

#endif // TOKENTYPE_H_INCLUDED
