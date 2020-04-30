class ArrayExpression;
class AssignmentExpression;
class BinaryExpression;
class BlockStatement;
class BreakStatement;
class ClassDeclarationsStatement;
class ConditionalExpression;
class ContainerAccessExpression;
class ContainerAssignmentExpression;
class ContinueStatement;
class DoWhileStatement;
class ExprToStat;
class ForeachArrayStatement;
class ForeachMapStatement;
class ForStatement;
class FunctionDefineStatement;
class FunctionStatement;
class FunctionalExpression;
class FunctionReferenceExpression;
class IfStatement;
class ImportStatement;
class MapExpression;
class ObjectCreationExpression;
class PrintlnStatement;
class PrintStatement;
class ReturnStatement;
class SwitchStatement;
class TernaryExpression;
class ThrowStatement;
class TryStatement;
class UnaryExpression;
class ValueExpression;
class VariableExpression;
class WhileStatement;

#ifndef VISITOR_H_INCLUDED
#define VISITOR_H_INCLUDED

class Visitor{
public:
    void visit(ArrayExpression* v);
    virtual void visit(AssignmentExpression* v);
    void visit(BinaryExpression* v);
    void visit(BlockStatement* v);
    void visit(BreakStatement* v);
    void visit(ClassDeclarationsStatement* v);
    void visit(ConditionalExpression* v);
    void visit(ContainerAccessExpression* v);
    void visit(ContainerAssignmentExpression* v);
    void visit(ContinueStatement* v);
    void visit(DoWhileStatement* v);
    void visit(ExprToStat* v);
    void visit(ForeachArrayStatement* v);
    void visit(ForeachMapStatement* v);
    void visit(ForStatement* v);
    virtual void visit(FunctionDefineStatement* v);
    void visit(FunctionStatement* v);
    void visit(FunctionalExpression* v);
    void visit(FunctionReferenceExpression* v);
    void visit(IfStatement* v);
    virtual void visit(ImportStatement* v);
    void visit(MapExpression* v);
    void visit(ObjectCreationExpression* v);
    void visit(PrintlnStatement* v);
    void visit(PrintStatement* v);
    void visit(ReturnStatement* v);
    void visit(SwitchStatement* v);
    void visit(TernaryExpression* v);
    void visit(ThrowStatement* v);
    void visit(TryStatement* v);
    void visit(UnaryExpression* v);
    void visit(ValueExpression* v);
    virtual void visit(VariableExpression* v);
    void visit(WhileStatement* v);
};
#endif // VISITOR_H_INCLUDED
