#pragma once

#include <z3.h>
#include <z3++.h>

#include <libsolidity/ast/ASTVisitor.h>
#include <libsolidity/ast/Types.h>

#include <unordered_map>

#include <solse/SolidityExprTranslator.h>
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
