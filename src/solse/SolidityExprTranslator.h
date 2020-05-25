#ifndef EXPR_H
#define EXPR_H

#include <z3.h>
#include <z3++.h>

#include <libsolidity/ast/AST.h>
using namespace dev::solidity;
#include <unordered_map>
#include <solse/mechanism.h>

class SymExecEngine;
enum TerminationCode { NONE, RETURN, CONTINUE, BREAK, THROW };

class ContextInfo {
public:
    Mechanism mechanism;
public:
    std::unordered_map<std::string, z3::expr> stateVarValueZ3ExprMap;
    std::unordered_map<std::string, z3::expr> localVarValueZ3ExprMap;
    std::vector<z3::expr> pathCondition;

    std::vector<z3::expr> z3_max_exps;
    std::vector<z3::expr> z3_min_exps;
    std::vector<ASTPointer<Expression const>> sol_max_exps;
    std::vector<ASTPointer<Expression const>> sol_min_exps;
    std::vector<z3::expr> z3_utilities;
    std::vector<ASTPointer<Expression const>> sol_utilities;
    std::vector<z3::expr> z3_revenue;
    std::vector<ASTPointer<Expression const>> sol_revenue;
    std::vector<z3::expr> z3_winners;
    std::vector<ASTPointer<Expression const>> sol_winners;

    std::vector< std::tuple<z3::expr, z3::expr, z3::expr> > z3_truth_check_exprs;
    std::vector<ASTPointer<Expression const>> sol_truth_check_exprs;
    std::vector< std::tuple<z3::expr, z3::expr,z3::expr, z3::expr, z3::expr> > z3_collusion_check_exprs;
    std::vector<std::tuple<ASTPointer<Expression const>,ASTPointer<Expression const> >> sol_collusion_check_exprs;

    std::vector< std::tuple<z3::expr, ASTPointer<Expression const >, ASTPointer<Expression const>> > z3_efficient_check_exprs;
    std::vector<ASTPointer<Expression const>> sol_efficient_check_exprs;
    std::vector< std::tuple<z3::expr,ASTPointer<Expression const >, ASTPointer<Expression const> > > z3_optimal_check_exprs;
    std::vector<ASTPointer<Expression const>> sol_optimal_check_exprs;

    std::map<std::pair<std::string, std::string>, z3::expr> z3_optimal_payment_register;
    std::map<std::pair<std::string, std::string>, z3::expr> z3_efficient_expectation_register;
 
    std::map<std::string, z3::expr> z3_validate_outcome_postconditions;

    dev::solidity::FunctionDefinition const* funcScope = nullptr;
    bool goHead = true;
    TerminationCode  abnormalTerminationCode = NONE;
    std::unordered_map<std::string, int> funcCallDepthMap;
    ContextInfo(bool _debugMode=false )
        :debugMode(_debugMode){
    }
    ContextInfo& operator=(const ContextInfo& other) {
        mechanism = other.mechanism; 
	    
        stateVarValueZ3ExprMap = other.stateVarValueZ3ExprMap;
        localVarValueZ3ExprMap = other.localVarValueZ3ExprMap;
        pathCondition = other.pathCondition;
        z3_max_exps = other.z3_max_exps;
        z3_min_exps = other.z3_min_exps;
        sol_max_exps = other.sol_max_exps;
        sol_min_exps = other.sol_min_exps;
        z3_utilities = other.z3_utilities;
        sol_utilities = other.sol_utilities;
        sol_revenue = other.sol_revenue;
        z3_revenue = other.z3_revenue;
        sol_revenue = other.sol_revenue;
        z3_winners = other.z3_winners;
        sol_winners = other.sol_winners;
        sol_truth_check_exprs = other.sol_truth_check_exprs;
        z3_truth_check_exprs = other.z3_truth_check_exprs;
        z3_collusion_check_exprs = other.z3_collusion_check_exprs;
        z3_efficient_check_exprs = other.z3_efficient_check_exprs;
        sol_efficient_check_exprs = other.sol_efficient_check_exprs;
        z3_optimal_check_exprs = other.z3_optimal_check_exprs;
        sol_optimal_check_exprs = other.sol_optimal_check_exprs;
        z3_optimal_payment_register = other.z3_optimal_payment_register;        
        z3_efficient_expectation_register = other.z3_efficient_expectation_register;        
	z3_validate_outcome_postconditions = other.z3_validate_outcome_postconditions;
	
        assert(other.funcScope);
        funcScope = other.funcScope;

        goHead = other.goHead;
        abnormalTerminationCode = other.abnormalTerminationCode;

        funcCallDepthMap = other.funcCallDepthMap;
        debugMode = other.debugMode;
        return *this;
    }

    void printContext();
    void collectContext(std::unordered_map<std::string, std::vector<std::string>>& state_variable_records,
    std::unordered_map<std::string, std::vector<std::string>>& local_variable_records);
    std::string toString();
private:
    bool debugMode;
};

class SolidityExprTranslator {
public:
    SolidityExprTranslator(z3::context& ctx, SymExecEngine* engine);

    void setDebugMode(bool mode);

    z3::expr translate(dev::solidity::Expression const* aExpr, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::Identifier const* idExpr, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::Literal const* litExpr, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::UnaryOperation const* unaryExp, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::BinaryOperation const* binaryExp, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::FunctionCall const* functioncallExp, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::MemberAccess const* memAccExp, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::IndexAccess const* indexAccessExp, ContextInfo& ctxInfo);
    z3::expr translate(dev::solidity::TupleExpression const* tupleExp, ContextInfo& ctxInfo);

private:
    z3::context& z3_ctx;
    SymExecEngine* symExecEngine;

    bool debugMode;
};
#endif