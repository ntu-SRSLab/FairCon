#pragma once

#include <z3.h>
#include <z3++.h>

#include <libsolidity/ast/ASTVisitor.h>
#include <libsolidity/ast/Types.h>
#include <unordered_map>
#include "mechanism.h"

#ifdef SOLC_0_5_0
#define CAST_POINTER(_var, _Type, _pointer) \
       std::shared_ptr<_Type const> _var = std::dynamic_pointer_cast<_Type const>(_pointer) 
#endif

#ifdef SOLC_0_5_10
#define CAST_POINTER(_var, _Type, _pointer) \
       _Type const* _var = dynamic_cast<_Type const*>(_pointer) 
#endif 

using namespace dev::solidity;
// #include "../solse/SolidityExprTranslator.h"


enum TerminationCode { NONE, RETURN, CONTINUE, BREAK, THROW };


class StructInfo{
public:
    std::string structName;
    std::vector<z3::sort> structSort;           // always has one element
    std::vector<z3::func_decl> structConstructor;    // always has one element
    std::vector<z3::sort> fieldSorts;
    std::vector<std::string> fieldNames;

    std::vector<z3::func_decl_vector> projectors;

    StructInfo& operator=(const StructInfo& other){
        structName = other.structName;
        assert(other.structSort.size() == 1);

        if(structSort.size() == 0){
            structSort.push_back(other.structSort[0]);
        }
        else{
            structSort[0] = other.structSort[0]; } 
        assert(structSort.size() == 1);

        if(structConstructor.size() == 0){
            structConstructor.push_back(other.structConstructor[0]);
        }
        else{
            structConstructor[0] = other.structConstructor[0];
        }

        assert(structConstructor.size() == 1);

        fieldSorts = other.fieldSorts;
        fieldNames = other.fieldNames;

        assert(projectors.size() == 1);
        assert(other.projectors.size() == 1);

        projectors[0] = other.projectors[0];

        return *this;
    }

    int getProjIndex(std::string fName){
        int result = -1;

        //std::cerr<<"fName: "<<fName<<std::endl;

        for(unsigned int index = 0; index < fieldNames.size(); ++index){
            if(fName.compare(fieldNames[index]) == 0){
                //std::cerr<<"index: "<<index<<std::endl;
                //std::cerr<<"fieldName["<<index<<"]: "<<fieldNames[index]<<std::endl;
                result = index;
                //std::cerr<<"proj: "<<projectors[0][result]<<std::endl;
                break;
            }
        }

        return result;
    }

    std::string toString(){
        std::stringstream info;

        info<<"Struct ["<<structName<<"]"<<std::endl;
        info<<"\t Sort in Z3: "<<structSort[0]<<std::endl;

        for(unsigned index = 0; index < fieldNames.size(); index++){
            info<<"\t"<<fieldNames[index]<<" : "<<projectors[0][index]<<std::endl;
        }

        return info.str();
    }
};

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

class SolidityExprTranslator;

class SymExecEngine: public dev::solidity::ASTConstVisitor {
public:
    SymExecEngine(std::string source, dev::solidity::ASTNode const& _node, bool mode, bool onlyExeMain, z3::context& _z3_ctx);
    ~SymExecEngine();

    void symbolicExecution();

    bool visit(dev::solidity::ContractDefinition const&) override;
    bool visit(dev::solidity::Literal const&) override;
    bool visit(dev::solidity::FunctionDefinition const&) override;
    bool visit(dev::solidity::VariableDeclaration const&) override;
    bool visit(dev::solidity::StructDefinition const&) override;

    bool visit(dev::solidity::BinaryOperation const& _node) override;

    void endVisit(dev::solidity::StructDefinition const&) override;
    void endVisit(dev::solidity::FunctionDefinition const&) override;
    void endVisit(dev::solidity::ContractDefinition const&) override;

    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Statement const* stmt, std::vector<ContextInfo>);

    std::vector<ContextInfo> strongestPostcondition(dev::solidity::FunctionDefinition const* funcDef, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::FunctionCall const* funCall, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Statement const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Block const *stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::UnaryOperation const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::ExpressionStatement const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Assignment const* stmt, ContextInfo& preCond);
    
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Break const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Continue const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Return const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::Throw const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::VariableDeclarationStatement const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::IfStatement const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::WhileStatement const* stmt, ContextInfo& preCond);
    std::vector<ContextInfo> strongestPostcondition(dev::solidity::ForStatement const* stmt, ContextInfo& preCond);

    // std::vector<ContextInfo> strongestPostcondition(dev::solidity::IfStatement const* stmt, ContextInfo& preCond, bool& success);
    // std::vector<ContextInfo> strongestPostcondition(dev::solidity::WhileStatement const* stmt, ContextInfo& preCond, bool& success);
    // std::vector<ContextInfo> strongestPostcondition(dev::solidity::ForStatement const* stmt, ContextInfo& preCond, bool& success);

    void print_model(z3::model, ContextInfo&,  std::string);

    void synthesis(std::vector<ContextInfo>& contexts);

protected:
    z3::sort typeSortInZ3(dev::solidity::TypePointer const typePtr);

    std::string getArrayName(dev::solidity::Expression const* aExpr, ContextInfo& ctxInfo);

    dev::solidity::FunctionDefinition const* getFuncDefinition(std::string funcName);

    void updateContextInfo(dev::solidity::Expression const* exp, z3::expr rightExpr, ContextInfo& preCond);

    bool checkValidity(z3::expr property, ContextInfo& ctxInfo);
    bool checkSatisfiability(z3::expr property, ContextInfo& ctxInfo);

    std::string getVarFullName(dev::solidity::Identifier const* idExp, ContextInfo& ctxInfo);
    std::string getVarFullName(dev::solidity::VariableDeclaration const* varDec, ContextInfo& ctxInfo);

    std::string getRealFuncCallName(dev::solidity::Expression const* funcCall);
    std::string nodeString(Expression const & a) {
        return m_source.substr(a.location().start, a.location().end-a.location().start);
        // return a.location().source->source().substr(a.location().start, a.location().end-a.location().start);
    }
private:
    std::string m_source;

    z3::context& z3_ctx;
    SolidityExprTranslator* solExprTranslator;

    std::vector<dev::solidity::FunctionDefinition const*> funcVec;
    std::unordered_map<std::string, z3::expr> stateVarZ3ExprMap;
    std::unordered_map<std::string, z3::expr> stateVarValuesZ3ExprMap;
    std::unordered_map<std::string, z3::expr> localVarZ3ExprMap;
    std::unordered_map<std::string, z3::expr> localVarValuesZ3ExprMap;
    std::unordered_map<std::string, std::shared_ptr<StructInfo>> structsMap;

    // typedef struct{
    //     std::vector<dev::solidity::FunctionDefinition const*> funcVec;
    //     std::unordered_map<std::string, z3::expr> stateVarZ3ExprMap;
    //     std::unordered_map<std::string, z3::expr> stateVarValuesZ3ExprMap;
    //     std::unordered_map<std::string, z3::expr> localVarZ3ExprMap;
    //     std::unordered_map<std::string, z3::expr> localVarValuesZ3ExprMap;
    //     std::unordered_map<std::string, std::shared_ptr<StructInfo>> structsMap;
    // } ContractStateStats;
    // // contractA -> ContractStateStats;
    // // contractB -> ContractStateStats;
    // std::unordered_map<std::string, ContractStateStats>  contractStateStatsMap;
    // // contractA a,b
    // // a-> ContractStateStats
    // // b-> ContractStateStats
    // std::unordered_map<std::string, ContractStateStats>  contract_entityStateStatsMap;


    bool isInStructDefinition;
    dev::solidity::ASTNode const& root;

    bool debugMode;
    bool onlyExecuteMain;

    friend class SolidityExprTranslator;

    unsigned int visitNumber;

    dev::solidity::FunctionDefinition const* currentFuncDef;
    static const std::string initSuffix;
    static const std::string nameSeparator;
    static const std::string scopeSpecifier;
    static const std::string mainFuncName;

    std::unordered_map<size_t, int> astNodeVisitMap;
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