#include <boost/algorithm/string.hpp>
#ifdef SOLC_0_5_0
#include <libevmasm/SourceLocation.h>
typedef dev::SourceLocation SourceLocation;
#else 
#include <liblangutil/SourceLocation.h>
using namespace langutil;
#endif 

#ifdef SOLC_0_5_0
#include <libsolidity/parsing/Scanner.h>
#define _Scaner_ Scanner
#endif 


#include "../solse/SymExecEngine.h"
#include "mechanism.h"
using namespace dev::solidity;

#include<chrono>

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
uint64_t start_time;
//mid_time: record the starting time of property checking.
uint64_t mid_time;
uint64_t mid2_time;
uint64_t end_time;
unsigned truth_count = 0;
unsigned collusion_count = 0;
unsigned optimal_count = 0;
unsigned efficient_count = 0;

const std::string SymExecEngine::initSuffix = "_0_";
const std::string SymExecEngine::nameSeparator = "@";
const std::string SymExecEngine::scopeSpecifier = "$";
const std::string SymExecEngine::mainFuncName = "_Main_";
int check_fail_count = 0;
bool checkCondPass(ContextInfo& cond){
        if (cond.abnormalTerminationCode == THROW){
            std::cout<< "CHECK PASS FAILED "<<check_fail_count++<<std::endl;
            return false;
        }
        else
            return true;
}
// record global utility and global revenue 
std::vector<z3::expr> g_utilities;
std::vector<z3::expr> g_collude_utilities;

std::vector<z3::expr> g_payments;
std::vector<z3::expr> g_optional_payments;

std::vector<z3::expr> g_benefits;
std::vector<z3::expr> g_optional_benefits;

std::vector<z3::expr> g_revenues;
std::vector<z3::expr> truth_assertions;
std::vector<z3::expr> collusion_assertions;
std::vector<z3::expr> optimal_assertions;
std::vector<z3::expr> efficient_assertions;

Mechanism g_mechanism;
void SymExecEngine::synthesis(std::vector<ContextInfo>& contexts ){
    std::vector<z3::expr> conditions;  
    
    g_revenues.emplace_back(z3_ctx.int_val(0));
    auto& g_revenue = g_revenues[0];

    auto size = contexts[0].z3_utilities.size();
    for (unsigned i=0;i<size;i++){
        g_utilities.emplace_back(z3_ctx.int_val(0));
    }
    size = contexts[0].z3_truth_check_exprs.size();
    for (unsigned i=0;i<size;i++){
        truth_assertions.emplace_back(z3_ctx.bool_val(true));
    }

    size = contexts[0].z3_efficient_check_exprs.size();
    for (unsigned i=0;i<size;i++){
        g_benefits.emplace_back(z3_ctx.int_val(0));
        g_optional_benefits.emplace_back(z3_ctx.int_val(0));
    }

    size = contexts[0].z3_optimal_check_exprs.size();
    for (unsigned i=0;i<size;i++){
        g_payments.emplace_back(z3_ctx.int_val(0));
        g_optional_payments.emplace_back(z3_ctx.int_val(0));
    }


    size = contexts[0].z3_collusion_check_exprs.size();
    for (unsigned i=0;i<size;i++){
        collusion_assertions.emplace_back(z3_ctx.bool_val(true));
        g_collude_utilities.emplace_back(z3_ctx.int_val(0));
    }
    
    size = contexts[0].z3_optimal_check_exprs.size();
    for (unsigned i=0;i<size;i++){
        optimal_assertions.emplace_back(z3_ctx.bool_val(true));
    }
    
    size = contexts[0].z3_efficient_check_exprs.size();
    for (unsigned i=0;i<size;i++){
        efficient_assertions.emplace_back(z3_ctx.bool_val(true));
    }
    

    for (unsigned i=0; i<contexts.size(); i++){
        auto& context = contexts[i];
        z3::expr condition = z3_ctx.bool_val(true);
        for(unsigned j = 0; j < context.pathCondition.size(); j++) {
            condition = condition && context.pathCondition[j];
        }
        conditions.emplace_back(condition);
    }
    for (unsigned i=0; i<contexts.size(); i++){
       auto& context = contexts[i];
       for(unsigned j=0; j<context.z3_utilities.size();j++){
           g_utilities[j] = z3::ite(conditions[i],context.z3_utilities[j], g_utilities[j]);
       }
       for(unsigned j=0; j<context.z3_revenue.size();j++){
           g_revenue = z3::ite(conditions[i],context.z3_revenue[j], g_revenue);
       }
       for(unsigned j=0; j<context.z3_collusion_check_exprs.size();j++){
            z3::expr a(z3_ctx), b(z3_ctx), c(z3_ctx), d(z3_ctx), e(z3_ctx);
            std::tie(a,b,c,d,e) = context.z3_collusion_check_exprs[j];
            g_collude_utilities[j] = z3::ite(conditions[i], a, g_collude_utilities[j]);
       }

        
        for (unsigned j=0;j<context.z3_efficient_check_exprs.size();j++){
             z3::expr benefit(z3_ctx);
             ASTPointer<Expression const> a;
             ASTPointer<Expression const> b;
             std::tie(benefit, a, b) =context.z3_efficient_check_exprs[j];
             g_benefits[j] = z3::ite(conditions[i], benefit, g_benefits[j]);
             auto optional_benefit = context.z3_efficient_expectation_register.at(std::make_pair(nodeString(*a),nodeString(*b)));
             g_optional_benefits[j] = z3::ite(conditions[i], optional_benefit, g_optional_benefits[j]);
        }

         for (unsigned j=0;j<context.z3_optimal_check_exprs.size();j++){
             z3::expr payment(z3_ctx);
             ASTPointer<Expression const> a;
             ASTPointer<Expression const> b;
             std::tie(payment, a, b) =context.z3_optimal_check_exprs[j];
             g_payments[j] = z3::ite(conditions[i], payment, g_payments[j]);
             auto optional_payment = context.z3_optimal_payment_register.at(std::make_pair(nodeString(*a),nodeString(*b)));
             g_optional_payments[j] = z3::ite(conditions[i], optional_payment, g_optional_payments[j]);
        }
    } 
    g_mechanism = contexts[0].mechanism;
    if (!g_mechanism.isEmpty()){
            unsigned index = 0;
            for(auto& condition: conditions) {
                if(index!=0){
                g_mechanism.allocation = z3::ite(condition, contexts[index].mechanism.allocation, g_mechanism.allocation); 
                g_mechanism.price = z3::ite(condition, contexts[index].mechanism.price, g_mechanism.price); 
                for(unsigned j =0; j< contexts[index].mechanism.utilities.size();j++){
                    g_mechanism.utilities[j][1] = z3::ite(condition, contexts[index].mechanism.utilities.at(j).at(1), g_mechanism.utilities.at(j).at(1)); 
                }
                for(unsigned j =0; j< contexts[index].mechanism.variables.size();j++){
                        g_mechanism.variables[j] = z3::ite(condition, contexts[index].mechanism.variables.at(j), g_mechanism.variables.at(j)); 
                }
                for(unsigned j =0; j< contexts[index].mechanism.variables_smt.size();j++){
                    g_mechanism.variables_smt[j] = z3::ite(condition, contexts[index].mechanism.variables_smt.at(j), g_mechanism.variables_smt.at(j)); 
                }
                }
                index ++;
            }
    }
    z3::expr branch_conds = z3_ctx.bool_val(0);
    z3::solver solver(z3_ctx);
    solver.reset();
    for (auto& condition: conditions){
         solver.push();
         branch_conds = branch_conds || condition;
         solver.add(condition);
          if (debugMode)
            if (solver.check() == z3::sat){
                std::cout<<"feasible path:" << condition<<std::endl;
            }
         solver.pop();
    }
    if (!g_mechanism.isEmpty())
            g_mechanism.preCond = branch_conds;
   
}
void SymExecEngine::print_model (z3::model z3_model, ContextInfo& current_ctx, std::string title){
    std::cout<< "-------------------------------------------"<<std::endl;
    std::cout<< "|"<<std::setw(41)<<title<<"|"<<std::endl;
    std::cout<< "-------------------------------------------"<<std::endl;
    std::cout<< "----------------State Variable-----------------------"<<std::endl;
    std::cout<<"|"<<std::left<<std::setw(20)<<"name"<<"|"<<std::left<<std::setw(20)<<"value"<<"|"<<std::endl;
    try{
    for(auto itr = current_ctx.stateVarValueZ3ExprMap.begin(); itr != current_ctx.stateVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        z3::expr& varInitExpr = current_ctx.stateVarValueZ3ExprMap.at(varName);
	if(std::string::npos == z3_model.eval(varInitExpr).to_string().find(varName))
        std::cout<<"|"<<std::left<<std::setw(20)<<varName.substr(0, varName.find('@'))<<"|"<<std::left<<std::setw(20)<<z3_model.eval(varInitExpr)<<"|"<<std::endl;
    }

    std::cout<< "----------------Local Variable-----------------------"<<std::endl;
    for(auto itr = current_ctx.localVarValueZ3ExprMap.begin(); itr != current_ctx.localVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        z3::expr& varInitExpr = current_ctx.localVarValueZ3ExprMap.at(varName);
	if(std::string::npos == z3_model.eval(varInitExpr).to_string().find(varName))
        //std::cout<<"|"<<std::left<<std::setw(20)<<varName<<"|"<<std::left<<std::setw(20)<<z3_model.eval(varInitExpr)<<"|"<<std::endl;
        std::cout<<"|"<<std::left<<std::setw(20)<<varName.substr(0, varName.find('@'))<<"|"<<std::left<<std::setw(20)<<z3_model.eval(varInitExpr)<<"|"<<std::endl;
    }
    std::cout<< "-------------------------------------------"<<std::endl<<std::endl;
    std::cout<< "|"<<std::left<<std::setw(30)<<"utilities"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
    for ( unsigned i = 0; i<current_ctx.z3_utilities.size(); i++ ){
            Expression const& expr = *current_ctx.sol_utilities[i];
            SourceLocation const& location(expr.location());
            std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
            std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) <<z3_model.eval(current_ctx.z3_utilities[i]) <<"|"<< std::endl;
    }
    std::cout<< "-------------------------------------------------------------------------"<<std::endl;
    std::cout<< "|"<<std::left<<std::setw(30)<<"revenue"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
    for ( unsigned i = 0; i<current_ctx.z3_revenue.size(); i++ ){
            Expression const& expr = *current_ctx.sol_revenue[i];
            SourceLocation const& location(expr.location());
            std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
            std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) <<z3_model.eval(current_ctx.z3_revenue[i]) <<"|"<< std::endl;
    }
    std::cout<< "-------------------------------------------------------------------------"<<std::endl<<std::endl;
    std::cout<< "|"<<std::left<<std::setw(30)<<"winner"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
    for ( unsigned i = 0; i<current_ctx.z3_winners.size(); i++ ){
            Expression const& expr = *current_ctx.sol_winners[i];
            SourceLocation const& location(expr.location());
            std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
            std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) <<z3_model.eval(current_ctx.z3_winners[i]) <<"|"<< std::endl;
    }
    std::cout<< "-------------------------------------------------------------------------"<<std::endl<<std::endl;
    }catch(std::exception& e){
	    std::cout<< __LINE__<< e.what() << std::endl;
    }
}

SymExecEngine:: SymExecEngine(std::string _source, ASTNode const& _node, bool mode, bool onlyExeMain, z3::context& _z3_ctx):
    m_source(_source), 
    z3_ctx(_z3_ctx),
    root(_node),
    debugMode(mode),
    onlyExecuteMain(onlyExeMain)
{
    solExprTranslator = new SolidityExprTranslator(z3_ctx, this);
    
    if(debugMode) {
        solExprTranslator->setDebugMode(true);
    }

    isInStructDefinition =false;
    currentFuncDef = NULL;

    visitNumber = 0;

    std::string msgSender = "msg.sender";
    std::string msgValue = "msg.value";
    std::string balance = "this.balance";
    std::string blockTimeStamp = "block.timestamp";

    std::string msgSender_init = msgSender + initSuffix;
    std::string msgValue_init = msgValue + initSuffix;
    std::string balance_init = balance + initSuffix;
    std::string blockTimeStamp_init = blockTimeStamp + initSuffix;

    z3::sort stringSort = z3_ctx.string_sort();

    std::pair<std::string, z3::expr> pair1(msgSender, z3_ctx.constant(msgSender.c_str(), stringSort));
    std::pair<std::string, z3::expr> pair2(msgValue, z3_ctx.int_const(msgValue.c_str()));
    std::pair<std::string, z3::expr> pair3(balance, z3_ctx.int_const(balance.c_str()));
    std::pair<std::string, z3::expr> pair4(blockTimeStamp, z3_ctx.int_const(blockTimeStamp.c_str()));

    stateVarZ3ExprMap.insert(pair1);
    stateVarZ3ExprMap.insert(pair2);
    stateVarZ3ExprMap.insert(pair3);
    stateVarZ3ExprMap.insert(pair4);

    std::pair<std::string, z3::expr> init_pair1(msgSender, z3_ctx.constant(msgSender_init.c_str(), stringSort));
    std::pair<std::string, z3::expr> init_pair2(msgValue, z3_ctx.int_const(msgValue_init.c_str()));
    std::pair<std::string, z3::expr> init_pair3(balance, z3_ctx.int_const(balance_init.c_str()));
    std::pair<std::string, z3::expr> init_pair4(blockTimeStamp, z3_ctx.int_const(blockTimeStamp_init.c_str()));

    stateVarValuesZ3ExprMap.insert(init_pair1);
    stateVarValuesZ3ExprMap.insert(init_pair2);
    stateVarValuesZ3ExprMap.insert(init_pair3);
    stateVarValuesZ3ExprMap.insert(init_pair4);

    root.accept(*this);
    visitNumber++;

    root.accept(*this);
    visitNumber++;
}

SymExecEngine::
~SymExecEngine(){
    delete solExprTranslator;
}

 std::unordered_map<std::string, std::vector<std::string>> state_variable_records;
std::unordered_map<std::string, std::vector<std::string>> local_variable_records;
void SymExecEngine::
symbolicExecution() {
    start_time = timeSinceEpochMillisec();

    std::cout<<"state variables: "<<std::endl;
    std::unordered_map<std::string, z3::expr>::const_iterator itr;
    for(itr = stateVarZ3ExprMap.begin(); itr != stateVarZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        std::cout<<"\t"<<"varName: "<<varName;
        z3::expr varInitExpr = stateVarValuesZ3ExprMap.at(varName);
        std::cout<<", value: "<<varInitExpr;
        std::cout<<", sort: "<<varInitExpr.get_sort()<<std::endl;
        std::vector<std::string> tmp;
        std::string value ;
        std::ostringstream ss;
        ss<<varInitExpr;
        value = ss.str();
        tmp.push_back(value);
        state_variable_records.emplace(varName, tmp);
    }

    std::cout<<"local variables: "<<std::endl;
    for(itr = localVarZ3ExprMap.begin(); itr != localVarZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        std::cout<<"\t"<<"varName: "<<varName;
        z3::expr varInitExpr = localVarValuesZ3ExprMap.at(varName);
        std::cout<<", value: "<<varInitExpr;
        std::cout<<", sort: "<<varInitExpr.get_sort()<<std::endl;
        std::vector<std::string> tmp;
        std::string value;
        std::ostringstream ss;
        ss<<varInitExpr;
        value = ss.str();
        tmp.push_back(value);
        local_variable_records.emplace(varName, tmp);
    }

    std::cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<std::endl;
    
    std::map<std::string, unsigned int> pattern_count;
    for(unsigned int i = 0; i < funcVec.size(); ++i) {
        std::string funcName = funcVec[i]->name();

        if(onlyExecuteMain && funcName.compare(mainFuncName) != 0) {
            continue;
        }

        std::cout<<"symbolically execute function ["<<funcName<<"]"<<std::endl;

        ContextInfo initContext;
        initContext.stateVarValueZ3ExprMap = stateVarValuesZ3ExprMap;
        initContext.localVarValueZ3ExprMap = localVarValuesZ3ExprMap;
        initContext.funcScope = funcVec[i];

        // if(funcName.compare(mainFuncName) == 0) {
        //     z3::expr msgSender = z3_ctx.string_val("FFFFFFFFFFFFFFFF");
        //     initContext.stateVarValueZ3ExprMap.at("msg.sender") = msgSender;
        // }

        std::vector<ContextInfo> resultVec = strongestPostcondition(funcVec[i], initContext);
        synthesis(resultVec);
        mid_time = timeSinceEpochMillisec();
        if(!g_mechanism.isEmpty()){
            auto ret = g_mechanism.check();
            if (ret){
                auto tmp = timeSinceEpochMillisec();
                std::cout<<"*************************************"<<std::endl;
                std::cout<<"*         report                    *"<<std::endl;
                std::cout<<"*************************************"<<std::endl;
                std::cout<<"* model construction time: "<<(mid_time-start_time)/1000.0<<"s"<<std::endl;
                std::cout<<"* property/invariant checking time: "<<(tmp-mid_time)/(1000.0)<<"s"<<std::endl;
                std::cout<<"*              total time: "<<(tmp-start_time)/1000.0<<"s"<<std::endl;
                std::cout<<"*************************************"<<std::endl;
                return;
            }
        }
        // find invariants
        if ( resultVec.size()>0 && resultVec[0].z3_validate_outcome_postconditions.size()>0 ){
            for(unsigned j = 0; j < resultVec.size(); j++) {
                std::cerr<<"result context ["<<j+1<<"]: "<<std::endl;
                auto current_ctx = resultVec[j];
                z3::solver solver(z3_ctx);
                solver.reset();
                // solver.add(true);
                for(unsigned i = 0; i < current_ctx.pathCondition.size(); i++) {
                    // std::cout<<"\t\t"<<current_ctx.pathCondition[i]<<std::endl;
                    solver.add(current_ctx.pathCondition[i] );
                }
                if (solver.check() == z3::sat){
                    for ( auto iter = current_ctx.z3_validate_outcome_postconditions.begin();iter != current_ctx.z3_validate_outcome_postconditions.end();iter++ ){
                                        auto desc = iter->first;
                                        auto cond = iter->second;
                                        solver.push();
                                        solver.add(!cond);
                                        if(solver.check()==z3::sat){
                                            std::cout<< desc<<" unsastifiable" <<std::endl;
                                            if (pattern_count.find(desc)==pattern_count.end()){
                                                pattern_count.insert(std::make_pair(desc,-1));
                                            }else{
                                                pattern_count[desc]--;
                                            }
                                        }else{
                                            std::cout<< desc<<" sastifiable!" <<std::endl;
                                            if (pattern_count.find(desc)==pattern_count.end()){
                                                pattern_count.insert(std::make_pair(desc,1));
                                            }else{
                                                pattern_count[desc]++;
                                            }
                                        }
                                        solver.pop();				
                                    }
                }
            }
        }
        mid2_time = timeSinceEpochMillisec();
        //  check property
        for(unsigned j = 0; j < resultVec.size(); j++) {
            std::cerr<<"result context ["<<j+1<<"]: "<<std::endl;
            auto current_ctx = resultVec[j];
            z3::solver solver(z3_ctx);
            solver.reset();
            // solver.add(true);
            for(unsigned i = 0; i < current_ctx.pathCondition.size(); i++) {
                // std::cout<<"\t\t"<<current_ctx.pathCondition[i]<<std::endl;
                solver.add(current_ctx.pathCondition[i] );
            }
            if (solver.check() == z3::sat){
                //current_ctx.printContext();
                        current_ctx.collectContext(state_variable_records,local_variable_records);
                         // if (current_ctx.z3_max_exps.size()>0){
                        std::cout<<"Using Z3 solver to optimize value expression"<< std::endl;
                        z3::solver  slv(z3_ctx);
                        z3::optimize opt(z3_ctx);
                        for(unsigned i = 0; i < current_ctx.pathCondition.size(); i++) {
                            opt.add(current_ctx.pathCondition[i] );
                            // slv.add(current_ctx.pathCondition[i] );
                        }
                        std::vector<z3::optimize::handle> handles;
                        std::vector<z3::optimize::handle> uhandles;
                        std::vector<z3::optimize::handle> rhandles;
                        for (unsigned i = 0; i<current_ctx.z3_max_exps.size();i++){
                            handles.push_back(opt.maximize(current_ctx.z3_max_exps[i]));
                        }
                        for (unsigned i = 0; i<current_ctx.z3_min_exps.size();i++){
                            handles.push_back(opt.minimize(current_ctx.z3_min_exps[i]));
                        }
                        for (unsigned i = 0; i<current_ctx.z3_utilities.size();i++){
                            uhandles.push_back(opt.maximize(current_ctx.z3_utilities[i]));
                        }
                        for (unsigned i = 0; i<current_ctx.z3_revenue.size();i++){
                            rhandles.push_back(opt.maximize(current_ctx.z3_revenue[i]));
                        }

                        if (z3::sat == opt.check()){
                            // std::cout<< "SMT-Max&Min Model:\n"<< opt.get_model()<<std::endl;
                            unsigned i = 0;
                            std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                            if (current_ctx.z3_max_exps.size()>0)
                                std::cout<< "|"<<std::left<<std::setw(50)<<"max expression"<<"|"<<std::left<<std::setw(20)<<"value"<<"|"<<std::endl;
                            for (i = 0; i<current_ctx.z3_max_exps.size();i++){
                                // opt.lower(handles[i]);
                                Expression const& max_exp = *current_ctx.sol_max_exps[i];
                                SourceLocation const& location(max_exp.location());
                                std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                                std::cout<< "|"<<std::left<<std::setw(50)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(20) << opt.lower(handles[i])<<"|"<< std::endl;
                            }
                        std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                            if (current_ctx.z3_min_exps.size()>0)
                                std::cout<< "|"<<std::left<<std::setw(50)<<"min expression"<<"|"<<std::setw(20)<<std::left<<"value"<<"|"<<std::endl;
                            for (unsigned k = 0; k <current_ctx.z3_min_exps.size(); k++,i++){
                                //  opt.upper(handles[i]);
                                Expression const& min_exp = *current_ctx.sol_min_exps[k];
                                SourceLocation const& location(min_exp.location());
                                std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                                std::cout<< "|"<<std::left<<std::setw(50)<<m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(20) <<opt.upper(handles[i]) <<"|"<< std::endl;
                            }
                        }
                        std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;

                        std::cout<< "--------------------------------OUTCOME-------------------------------------"<<std::endl;
                        std::cout<< "|"<<std::left<<std::setw(30)<<"truthful violate check"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
                        for ( unsigned i = 0; i<current_ctx.z3_truth_check_exprs.size(); i++ ){
				                slv.push();
                                z3::expr utility(z3_ctx);
                                z3::expr a(z3_ctx);
                                z3::expr b(z3_ctx);
                                try{
                                    std::tie(utility, a, b ) =current_ctx.z3_truth_check_exprs[i];
                                    auto global_utility = g_utilities[i];
                                    assert(a.is_const());
                                    assert(b.is_const());
                                    // std::cout<<"a.decl().name():"<<a.decl().name().str()<<std::endl;
                                    auto name = a.decl().name().str()+"#2";
                                    auto new_a = z3_ctx.constant(name.c_str(),a.get_sort());
                                    // std::cout<<"new_a.decl().name():"<<new_a.decl().name().str()<<std::endl;
                                    z3::expr_vector from(z3_ctx),to(z3_ctx);
                                    from.push_back(a);
                                    to.push_back(new_a);
                                    auto new_global_utility = global_utility.substitute(from,to);   
                                  
                                    // add constraints
                                    slv.add(a==b);
                                    slv.add(new_a!=b);
                                    // add truthful assertion
                                    // check every path
                                    // auto property = utility >= new_global_utility;
                                    // check once
                                    auto property = global_utility >= new_global_utility;
                                    slv.add(!property);
                                   

                                    Expression const& expr = *current_ctx.sol_truth_check_exprs[i];
                                    SourceLocation const& location(expr.location());
                                    std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                                    // std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << value <<"|"<< std::endl;
                                    if (z3::sat == slv.check()){
                                        auto model = slv.get_model();
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << "Untruthful" <<"|"<< std::endl;
                                        print_model(model, current_ctx, "Untruthful Case");
                                        std::cout<<"hint"<<std::endl;
                                        std::cout<< a.decl().name().str()<< ": " <<model.eval(a) <<std::endl;
                                        std::cout<< new_a.decl().name().str()<<": "<<model.eval(new_a)<<std::endl;
                                        std::cout<< "a's utility:" <<":"<< model.eval(global_utility) << std::endl;
                                        std::cout<< "new a's utility" << ":" << model.eval(new_global_utility) << std::endl;
                                        truth_count++;
                                    }
                                    else{
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << "Truthful" <<"|"<< std::endl;
                                         slv.pop();
                                         slv.push();
                                         slv.add(property);
                                         if(slv.check()==z3::sat){
                                             std::cout<<"for voting"<<std::endl;
                                             print_model(slv.get_model(),current_ctx,"truthful voting case");
                                         }
                                    }
                                }catch(z3::exception e){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" exception happened: "<<e<<std::endl;
                                }catch(...){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" default exception"<<std::endl;
                                }
                                slv.pop();

                        }
                        std::cout<< "-------------------------------------------------------------------------"<<std::endl;

                        std::cout<< "|"<<std::left<<std::setw(30)<<"collusion violate check"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
                        for ( unsigned i = 0; i<current_ctx.z3_collusion_check_exprs.size(); i++ ){
				                slv.push();
                                z3::expr u12(z3_ctx);
                                z3::expr v1(z3_ctx);
                                z3::expr v_1(z3_ctx);
                                z3::expr v2(z3_ctx);
                                z3::expr v_2(z3_ctx);
                                try{
                                    std::tie(u12, v1, v_1,  v2, v_2 ) =current_ctx.z3_collusion_check_exprs[i];
                                    auto global_collude_utility = g_collude_utilities[i];
                                    assert(v1.is_const());
                                    assert(v_1.is_const());
                                    assert(v2.is_const());
                                    assert(v_2.is_const());
                                    auto name = v1.decl().name().str()+"#2";
                                    auto new_v1 =  z3_ctx.constant(name.c_str(),v1.get_sort());
                                    name = v2.decl().name().str()+"#2";
                                    auto new_v2 =  z3_ctx.constant(name.c_str(),v2.get_sort());
                                    // std::cout<<"v1.decl().name()" << v1.decl().name().str()<<std::endl;       
                                    // std::cout<<"new_v1.decl().name()" << new_v1.decl().name().str()<<std::endl;
                                    // std::cout<<"v2.decl().name()" << v2.decl().name().str()<<std::endl;
                                    // std::cout<<"new_v2.decl().name()" << new_v2.decl().name().str()<<std::endl;
                                    z3::expr_vector from(z3_ctx),to(z3_ctx);
                                    from.push_back(v1);
                                    from.push_back(v2);
                                    to.push_back(new_v1);
                                    to.push_back(new_v2);
                                    auto new_global_collude_utility = global_collude_utility.substitute(from,to);
                                    //constraints
                                    slv.add(v1==v_1);
                                    slv.add(v2==v_2);
                                    slv.add(new_v1!=v_1);
                                    slv.add(new_v2!=v_2);
                                    //property
                                    // auto property = u12>=new_global_collude_utility;
                                    auto property = global_collude_utility>=new_global_collude_utility;
                                    slv.add(!property);


                                    // auto oldu12 = u12;
                                    // z3::expr_vector av(z3_ctx),bv(z3_ctx);
                                    // av.push_back(v1);
                                    // av.push_back(v2);
                                    // bv.push_back(v_1);
                                    // bv.push_back(v_2);
                                    // auto newu12 = u12.substitute(av,bv);

                                    // slv.add( oldu12 > newu12 );
                                    // std::string value;
                                    // std::ostringstream ss;
                                    // ss<< oldu12;
                                    // value =  boost::replace_all_copy(boost::replace_all_copy(boost::replace_all_copy(ss.str(),"\n","#"), "  ", ""),"#"," ");
                                    Expression const& expr1 = *std::get<0>(current_ctx.sol_collusion_check_exprs[i]);
                                    SourceLocation const& location1(expr1.location());
                                    std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                                    // std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location1.start, location1.end - location1.start).c_str()<<"|"<<std::left<<std::setw(40) << value <<"|"<< std::endl;
                                    if (z3::sat == slv.check()){
                                        collusion_count++;
                                        auto model = slv.get_model();
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location1.start, location1.end - location1.start).c_str()<<"|"<<std::left<<std::setw(40) << "Colluded" <<"|"<< std::endl;
                                        print_model(model, current_ctx, "Colluded Case");
                                        std::cout<< "hint"<< std::endl;
                                        std::cout<<v1.decl().name().str() << ":" <<model.eval(v1)<<std::endl;
                                        std::cout<<v2.decl().name().str() << ":" <<model.eval(v2)<<std::endl;
                                        std::cout<<new_v1.decl().name().str() << ":" <<model.eval(new_v1)<<std::endl;
                                        std::cout<<new_v2.decl().name().str() << ":" <<model.eval(new_v2)<<std::endl;
                                        std::cout<<"v1&v2's utility" << ":" <<model.eval(u12) <<std::endl;
                                        std::cout<<"new v1&v2's colluded utility" << ":" <<model.eval(new_global_collude_utility) <<std::endl;
                                    }
                                    else
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location1.start, location1.end - location1.start).c_str()<<"|"<<std::left<<std::setw(40) << "Noncolluded" <<"|"<< std::endl;
                                }catch(z3::exception e){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" exception happened: "<<e<<std::endl;
                                }catch(...){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" default exception"<<std::endl;
                                }
				              slv.pop();
				        
                         
                        }
                        std::cout<< "-------------------------------------------------------------------------"<<std::endl;
                        std::cout<< "|"<<std::left<<std::setw(30)<<"effecient violate check"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
                        for ( unsigned i = 0; i<current_ctx.z3_efficient_check_exprs.size(); i++ ){
                                slv.push();
                                z3::expr benefit(z3_ctx);
                                ASTPointer<Expression const> a;
                                ASTPointer<Expression const> b;
                                try{
                                    std::tie(benefit, a, b) =current_ctx.z3_efficient_check_exprs[i];
                                    auto optional_benefit = current_ctx.z3_efficient_expectation_register.at(std::make_pair(nodeString(*a),nodeString(*b)));
                                     //property
                                     // check every path
                                    //auto property = benefit >= optional_benefit;
                                    //check once
                                    auto property = g_benefits[i] >= g_optional_benefits[i];
                                    // consider other benefits together
                                    for (unsigned j=i+1;j<g_optional_benefits.size();j++)
                                        property =  property && (g_benefits[i] >= g_optional_benefits[i]);
                                    slv.add(!property);

                                    Expression const& expr = *current_ctx.sol_efficient_check_exprs[i];
                                    SourceLocation const& location(expr.location());
                                    std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                                    if (z3::sat == slv.check()){
                                        efficient_count++;
                                        auto model  = slv.get_model();
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << "Uneffecient" <<"|"<< std::endl;
                                        print_model(model, current_ctx, "Uneffecient Case");
                                        std::cout<<"hint"<<std::endl;
                                        std::cout<<"benefit"<<":"<<model.eval(benefit)<<std::endl;
                                        std::cout<<"optional benefit" << ":" << model.eval(optional_benefit)<<std::endl;
					                    slv.pop();
                                        break;
                                    }else{
                                        slv.pop();
                                        slv.push();
                                        slv.add( benefit != optional_benefit);
                                        if(z3::sat==slv.check())std::cerr<<"benefit greater than optional benefit"<<std::endl;
                                        else{
                                            std::cerr<<"benefit equal to optional benefit"<<std::endl;
                                        }
                                        slv.pop();
                                        // print_model(slv.get_model(), current_ctx, "efficient Case");
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << "Effecient" <<"|"<< std::endl;
                                    }
                                }catch(z3::exception e){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" exception happened: "<<e<<std::endl;
                                }catch(...){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" default exception"<<std::endl;
                                }
                        }
                        std::cout<< "-------------------------------------------------------------------------"<<std::endl;
                        std::cout<< "|"<<std::left<<std::setw(30)<<"optimal violate check"<<"|"<<std::left<<std::setw(40)<<"value"<<"|"<<std::endl;
                        for ( unsigned i = 0; i<current_ctx.z3_optimal_check_exprs.size(); i++ ){
                                z3::expr payment(z3_ctx);
                                ASTPointer<Expression const> a;
                                ASTPointer<Expression const> b;
                                try{
                                    std::tie(payment, a, b) =current_ctx.z3_optimal_check_exprs[i];
                                    auto optional_payment = current_ctx.z3_optimal_payment_register.at(std::make_pair(nodeString(*a),nodeString(*b)));
                                    // std::cout<<"payment:smt->"<<payment<<std::endl;
                                    // std::cout<<"optional payment:smt->"<<optional_payment<<std::endl;
                                    slv.push();
                                    //property
                                    // check every path
                                    //auto property = payment >= optional_payment;
                                    //check once
                                    auto property = g_payments[i] >= g_optional_payments[i];
                                     // consider other payments together
                                    for (unsigned j=i+1;j<g_optional_payments.size();j++)
                                        property =  property && (g_payments[i] >= g_optional_payments[i]);
                                    slv.add(!property);
                                    // slv.add(property);

                                    Expression const& expr = *current_ctx.sol_optimal_check_exprs[i];
                                    SourceLocation const& location(expr.location());
                                    std::cout<< "----------------------------------------------------"<<"---------------------"<<std::endl;
                                    if (z3::sat == slv.check()){
                                        optimal_count++;
                                        auto model = slv.get_model();
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << "Unoptimal" <<"|"<< std::endl;
                                        print_model(model, current_ctx, "Unoptimal Case");
                                        std::cout<<"hint"<<std::endl;
                                        std::cout<<"payment"<<":"<<model.eval(payment)<<std::endl;
                                        std::cout<<"optional payment" << ":" << model.eval(optional_payment)<<std::endl;
					                    slv.pop();
                                        break;
                                    }else{
                                        slv.pop();
                                        slv.push();
                                        slv.add( payment != optional_payment);
                                        if(z3::sat==slv.check())std::cerr<<"payment greater than optional payment"<<std::endl;
                                        else{
                                            std::cerr<<"payment equal to optional payment"<<std::endl;
                                        }
                                        slv.pop();
                                        std::cout<< "|"<<std::left<<std::setw(30)<< m_source.substr(location.start, location.end - location.start).c_str() <<"|"<<std::left<<std::setw(40) << "Optimal" <<"|"<< std::endl;    
                                    }
                                }catch(z3::exception e){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" exception happened: "<<e<<std::endl;
                                }catch(...){
                                    std::cout<<__FILE__<<":"<<__LINE__<<" default exception"<<std::endl;
                                }
                        }
                break;         
                  
            
            }else{
                std::cout<<" result is not available"<< std::endl;
            }

           
        }
        std::cout<<"**************************************"<<std::endl;
        std::cout<<"*    outcome pattern                 *"<<std::endl;
        std::cout<<"**************************************"<<std::endl;
        for ( auto iter = pattern_count.begin();iter != pattern_count.end();iter++ ){
                          	auto desc = iter->first;
				auto count = iter->second;
				std::cout<< desc<<":"<<(count==resultVec.size()?"satisfiable":"unsatisfiable")<<std::endl;
	     }
        end_time = timeSinceEpochMillisec();
        std::cout<<"*************************************"<<std::endl;
        std::cout<<"*         report                    *"<<std::endl;
        std::cout<<"*************************************"<<std::endl;
        std::cout<<"* model construction time: "<<(mid_time-start_time)/1000.0<<"s"<<std::endl;
        std::cout<<"*  property checking time: "<<(end_time-mid2_time)/1000.0<<"s"<<std::endl;
        std::cout<<"*              total time: "<<((end_time-start_time)-(mid2_time-mid_time))/1000.0<<"s"<<std::endl;
        std::cout<<"*  pattern [ fairness:(contexts)-(violates) ] " << std::endl;
        std::cout<<"*      truthful:"<< resultVec.size() << "-"<<truth_count<<std::endl;
        std::cout<<"*collusion-free:"<< resultVec.size() << "-"<<collusion_count<<std::endl;
        std::cout<<"*       optimal:"<< resultVec.size() << "-"<<optimal_count<<std::endl;
        std::cout<<"*     efficient:"<< resultVec.size() << "-"<<efficient_count<<std::endl;
        std::cout<<"*************************************"<<std::endl;
   }

}
bool SymExecEngine::visit(ContractDefinition const& _node){
    std::string name = _node.name();
    std::cout<<"analyzing contract [ "<< name << " ]"<<std::endl;
    return true;
}
void SymExecEngine::endVisit(ContractDefinition const& _node){
    std::string name = _node.name();
    std::cout<<"exit contract [ "<< name << " ]"<<std::endl;
}
bool SymExecEngine::
visit(Literal const& _node) {
    if(visitNumber > 0) {
        std::ignore = _node;
        //z3::expr litExpr = solExprTranslator->translate(&_node);
        //std::cerr<<"litExpr: "<<litExpr<<std::endl;
    }
    return true;
}

bool SymExecEngine::
visit(FunctionDefinition const& _node) {
    if(visitNumber != 0)
        return true;

    currentFuncDef = &_node;

    std::string funcName = _node.name();

    std::cerr<<"analyzing function [ "<<funcName<<" ]"<<std::endl;

    funcVec.push_back(&_node);

    std::vector<ASTPointer<VariableDeclaration>> paramVec = _node.parameters();

    for(unsigned index = 0; index < paramVec.size(); index++){
        std::shared_ptr<VariableDeclaration> varDecPtr = paramVec[index];

        std::string varName = varDecPtr->name();

        //std::string varFullName = varName + nameSeparator + funcName;
        ContextInfo tempCtxInfo;
        std::string varFullName = getVarFullName(paramVec[index].get(), tempCtxInfo);

        if(varName.length() == 0){
            std::cerr<<"parameter "<<index+1<<" does not have a name!"<<std::endl;
            assert(false);
        }

        TypePointer typePtr = varDecPtr->annotation().type;
        z3::sort typeSort = typeSortInZ3(typePtr);

        std::unordered_map<std::string, z3::expr>::const_iterator itr = localVarZ3ExprMap.find(varFullName);

        if(itr == localVarZ3ExprMap.end()){ /** the variable is not in the map**/
            z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

            std::pair<std::string, z3::expr> _pair(varFullName, varExpr);
            localVarZ3ExprMap.insert(_pair);

            std::string varInitName = varFullName + initSuffix;
            z3::expr varValueExpr = z3_ctx.constant(varInitName.c_str(), typeSort);
            std::pair<std::string, z3::expr> initPair(varFullName, varValueExpr);
            localVarValuesZ3ExprMap.insert(initPair);

            //std::cout<<"insert a local variable: "<<varName<<std::endl;
        }
        else{
            std::cerr<<"ERROR!! the variable name ["<<varName<<"] is dupilicated in different function definitions."<<std::endl;
            assert(false);
        }
    }

    std::vector<ASTPointer<VariableDeclaration>> returnParamVec = _node.returnParameters();

    for(unsigned index = 0; index < returnParamVec.size(); index++){
        std::shared_ptr<VariableDeclaration> varDecPtr = returnParamVec[index];

        std::string varName = varDecPtr->name();
        //std::string varFullName = varName + nameSeparator + funcName;
        ContextInfo tempCtxInfo;
        std::string varFullName = getVarFullName(returnParamVec[index].get(), tempCtxInfo);

        if(varName.length() == 0){
            std::cerr<<"return parameter "<<index+1<<" does not have a name!"<<std::endl;
            assert(false);
        }

        TypePointer typePtr = varDecPtr->annotation().type;
        z3::sort typeSort = typeSortInZ3(typePtr);

        std::unordered_map<std::string, z3::expr>::const_iterator itr = localVarZ3ExprMap.find(varFullName);

        if(itr == localVarZ3ExprMap.end()){ /** the variable is not in the map**/
            z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

            std::pair<std::string, z3::expr> _pair(varFullName, varExpr);
            localVarZ3ExprMap.insert(_pair);

            std::string varInitName = varFullName + initSuffix;
            z3::expr varValueExpr = z3_ctx.constant(varInitName.c_str(), typeSort);
            std::pair<std::string, z3::expr> initPair(varFullName, varValueExpr);
            localVarValuesZ3ExprMap.insert(initPair);

            //std::cout<<"insert a local variable: "<<varName<<std::endl;
        }
        else{
            std::cerr<<"ERROR!! the variable name ["<<varName<<"] is dupilicated in different function definitions."<<std::endl;
            assert(false);
        }
    }

    return true;
}

bool SymExecEngine::
visit(VariableDeclaration const& _node) {
    if(visitNumber != 0)
        return true;

    if(isInStructDefinition){
        //std::cerr<<"skip!!"<<std::endl;
        return true;
    }
    std::string varName = _node.name();
    // std::cout<< "test:"<<m_source.substr(location.start, location.end - location.start).c_str();
    // std::cout<< "test:"<<varName;
    ContextInfo tempCtxInfo;
    std::string varFullName = getVarFullName(&_node, tempCtxInfo);

    size_t varId = _node.id();

    if(debugMode) {
        std::cerr<<"variable ["<<varName<<"] declared in "<<"("<<varId<<")"<<std::endl;
    }

    TypePointer typePtr = _node.annotation().type;

    //std::cerr<<"determing the type of variable ["<<varName<<"]"<<std::endl;
    z3::sort typeSort = typeSortInZ3(typePtr);
    //std::cerr<<varName<<" is of type: "<<typeSort<<std::endl;

    if(_node.isStateVariable()){
        std::unordered_map<std::string, z3::expr>::const_iterator itr = stateVarZ3ExprMap.find(varFullName);

        if(itr == stateVarZ3ExprMap.end() && varName.length() > 0){ /** the variable is not in the map**/
            z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

            std::pair<std::string, z3::expr> _pair(varFullName, varExpr);
            stateVarZ3ExprMap.insert(_pair);

            std::string varInitName = varFullName + initSuffix;
            z3::expr varValueExpr = z3_ctx.constant(varInitName.c_str(), typeSort);
            std::pair<std::string, z3::expr> initPair(varFullName, varValueExpr);
            stateVarValuesZ3ExprMap.insert(initPair);
            // std::cout<< "varFullName" << varFullName <<std::endl;
          
            if(CAST_POINTER(arrayType, ArrayType, typePtr)){
            // if(std::shared_ptr<ArrayType const> arrayType = std::dynamic_pointer_cast<ArrayType const>(typePtr)){
                // std::cout<<"Length in arrayType:"<<varFullName+".length"<<std::endl;
                z3::expr length_of_arr = z3_ctx.constant((varInitName+".length").c_str(),z3_ctx.int_sort());
                stateVarValuesZ3ExprMap.insert(std::make_pair(varFullName+".length", length_of_arr));
            }
        }
    }
    else if(_node.isLocalVariable()){
        if (currentFuncDef == NULL)
            return true;
        assert(currentFuncDef);
        std::string nameSpace = currentFuncDef->name();
         
        //std::string varFullName = varName + nameSeparator + nameSpace;
        //std::string varFullName = getVarFullName(&_node);

        std::unordered_map<std::string, z3::expr>::const_iterator itr = localVarZ3ExprMap.find(varFullName);

        if(itr == localVarZ3ExprMap.end() && varName.length() > 0){ /** the variable is not in the map**/
            z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

            std::pair<std::string, z3::expr> _pair(varFullName, varExpr);
            localVarZ3ExprMap.insert(_pair);

            std::string varInitName = varFullName + initSuffix;
            z3::expr varValueExpr = z3_ctx.constant(varInitName.c_str(), typeSort);
            std::pair<std::string, z3::expr> initPair(varFullName, varValueExpr);
            localVarValuesZ3ExprMap.insert(initPair);
            if(CAST_POINTER(arrayType, ArrayType, typePtr)){
            // if(std::shared_ptr<ArrayType const> arrayType = std::dynamic_pointer_cast<ArrayType const>(typePtr)){
                z3::expr length_of_arr = z3_ctx.constant((varInitName+".length").c_str(),z3_ctx.int_sort());
                stateVarValuesZ3ExprMap.insert(std::make_pair(varFullName+".length", length_of_arr));
            }

            if(debugMode) {
                std::cerr<<"insert a local variable: "<<varFullName<<std::endl;
                std::cerr<<"insert a local variable: "<<varInitName<<std::endl;
            }
        }
    }
    else{
        std::cerr<<"not handled case."<<std::endl;
        assert(false);
    }

    return true;
}

bool SymExecEngine::
visit(StructDefinition const& _node) {
    if(visitNumber != 0)
        return true;

    isInStructDefinition = true;

    std::string structName = _node.name();
    std::vector<const char*> nameVec;
    std::vector<std::string> stdStringVec;
    std::vector<z3::sort> sortVec;

    z3::func_decl_vector projectors(z3_ctx);

    std::vector<ASTPointer<VariableDeclaration>> varDecs = _node.members();

    for(unsigned int index = 0; index < varDecs.size(); index++){
        std::string varName = varDecs[index]->name();

        //std::cerr<<"determing the type of variable ["<<varName.c_str()<<"]"<<std::endl;

        nameVec.push_back(varDecs[index]->name().c_str());
        stdStringVec.push_back(varName);

        TypePointer typePtr = varDecs[index]->annotation().type;
        z3::sort typeSort = typeSortInZ3(typePtr);

        //std::cerr<<varName<<" is of type: "<<typeSort<<std::endl;

        sortVec.push_back(typeSort);
    }

    assert(nameVec.size() == sortVec.size());

//    std::cerr<<"-----------nameVec----------------"<<std::endl;
//    for(int i = 0; i < nameVec.size(); i++){
//        std::cerr<<"nameVec["<<i<<"]: "<<nameVec[i]<<std::endl;
//    }
//    std::cerr<<"----------------------------------"<<std::endl;

    z3::func_decl structFuncDecl = z3_ctx.tuple_sort(structName.c_str(), nameVec.size(), nameVec.data(), sortVec.data(), projectors);

    //std::cerr<<"projectors: "<<projectors<<std::endl;

    std::unordered_map<std::string, std::shared_ptr<StructInfo>>::iterator structItr = structsMap.find(structName);

    if(structItr == structsMap.end()){
        std::shared_ptr<StructInfo> structInfo(new StructInfo());

        structInfo->structName = structName;
        structInfo->structSort.push_back(structFuncDecl.range());
        structInfo->structConstructor.push_back(structFuncDecl);
        structInfo->fieldSorts = sortVec;
        structInfo->fieldNames = stdStringVec;
        structInfo->projectors.push_back(projectors);

        assert(structInfo->structSort.size() == 1);
        assert(structInfo->projectors.size() == 1);

        //std::cerr<<"structInfo: "<<structInfo->toString()<<std::endl;

        std::pair<std::string, std::shared_ptr<StructInfo>> pairTmp(structName, structInfo);
        structsMap.insert(pairTmp);

        //std::cerr<<"pairTmp.second: "<<pairTmp.second->toString()<<std::endl;

        //std::cerr<<"structure sort: "<<pairTmp.second->structSort[0]<<std::endl;
    }
    else{
        std::cerr<<"Duplicated definition of structure ["<<structName<<"]"<<std::endl;
        assert(false);
    }

    return true;

}

bool SymExecEngine::
visit(BinaryOperation const& _node) {
    std::ignore = _node;
    if(visitNumber != 0) {
        //z3::expr binaryExpr = solExprTranslator->translate(&_node);
        //std::cout<<"binaryExpr: "<<binaryExpr<<std::endl;
    }

    return true;
}

void SymExecEngine::
endVisit(StructDefinition const&) {
    isInStructDefinition = false;
}

void SymExecEngine::
endVisit(dev::solidity::FunctionDefinition const&){
    currentFuncDef = NULL;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Statement const* stmt, std::vector<ContextInfo> preCondVec) {
    int preCondNum = preCondVec.size();
    std::vector<ContextInfo> postCondVec;

    if(debugMode) {
        std::cerr<<"invoking sp for <Statement> -- vector version: "<<preCondNum<<std::endl;
    }

    for(int i = 0; i < preCondNum; i++) {
        if(debugMode) {
            std::cerr<<"preCond["<<i<<"]"<<std::endl;
        }
        if (checkCondPass(preCondVec[i])){
            std::vector<ContextInfo> resultVec = strongestPostcondition(stmt, preCondVec[i]);
            postCondVec.insert(postCondVec.end(), resultVec.begin(), resultVec.end());
        }
        if(debugMode) {
            std::cerr<<"*********************************************"<<std::endl;
        }
    }
    return postCondVec;
}


std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(FunctionDefinition const* funcDef, ContextInfo& preCond) {
    std::string funcName = funcDef->name();

    if(debugMode) {
        std::cerr<<"invoking sp for <FunctionDefinition> of ["<<funcName<<"]"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    try{
        preCond.funcCallDepthMap.at(funcName) = preCond.funcCallDepthMap.at(funcName) + 1;
    }
    catch(...){
        preCond.funcCallDepthMap.emplace(funcName, 1);
    }

    if(debugMode) {
        std::cerr<<"increase ["<<funcName<<"]'s call depth to: "<<preCond.funcCallDepthMap.at(funcName)<<std::endl;
    }

    std::vector<ContextInfo> preCondVec;
    preCondVec.push_back(preCond);

    postCondVec = preCondVec;

    std::vector<ASTPointer<Statement>> const& stmtVec = funcDef->body().statements();

    for(unsigned index = 0; index < stmtVec.size(); ++index){
        Statement const* stmt = (stmtVec[index]).get();
        postCondVec = strongestPostcondition(stmt, postCondVec);
    }

    for(unsigned i = 0; i < postCondVec.size(); i++) {
        if(postCondVec[i].goHead == false && postCondVec[i].abnormalTerminationCode == RETURN) {
            postCondVec[i].goHead = true;
            postCondVec[i].abnormalTerminationCode = NONE;
        }

        if(debugMode) {
            std::cerr<<"["<<funcName<<"]'s call depth: "<<preCond.funcCallDepthMap.at(funcName)<<std::endl;
        }

        try{
            postCondVec[i].funcCallDepthMap.at(funcName) = postCondVec[i].funcCallDepthMap.at(funcName) - 1;
            assert(postCondVec[i].funcCallDepthMap.at(funcName) >= 0);
        }
        catch(...){
            std::cerr<<"This should not happen!"<<std::endl;
            assert(false);
        }

        if(debugMode) {
            std::cerr<<"decrease ["<<funcName<<"]'s call depth to: "<<postCondVec[i].funcCallDepthMap.at(funcName)<<std::endl;
        }
    }

    if(debugMode) {
        std::cerr<<"========================================================"<<std::endl;
    }

    return postCondVec;
}


std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(FunctionCall const* funCall, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <FunctionCall>"<<std::endl;
    }
    
    std::vector<ContextInfo> postCondVec;
    
    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    Expression const& funExp = funCall->expression();

    std::string funcName;

    if(Identifier const* id = dynamic_cast<Identifier const*>(&funExp)) {
        funcName = id->name();

        if(debugMode) {
            std::cerr<<"Direct function call: "<<funcName<<std::endl;
        }

        if(funcName.compare("value") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funCall->arguments();
            assert(argumentsExp.size() == 1);
            z3::expr valueExpr = solExprTranslator->translate(argumentsExp[0].get(), preCond);

            preCond.stateVarValueZ3ExprMap.at("msg.value") = valueExpr;

            std::cerr<<"update_ msg.value: "<<valueExpr<<std::endl;

            postCondVec.push_back(preCond);

            return postCondVec;
        } else if(funcName.compare("timestamp") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funCall->arguments();
            assert(argumentsExp.size() == 1);
            z3::expr valueExpr = solExprTranslator->translate(argumentsExp[0].get(), preCond);

            preCond.stateVarValueZ3ExprMap.at("block.timestamp") = valueExpr;

            std::cerr<<"update_ block.timestamp: "<<valueExpr<<std::endl;

            postCondVec.push_back(preCond);

            return postCondVec;
        }

        else if(funcName.compare("gas") == 0) {
            postCondVec.push_back(preCond);

            return postCondVec;
        }
        else if(funcName.compare("assert") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funCall->arguments();
            assert(argumentsExp.size() == 1);

            Expression const& property = *argumentsExp[0];
            z3::expr propertyExpr = solExprTranslator->translate(&property, preCond);

            bool checkResult = checkValidity(propertyExpr, preCond);
            if (debugMode)
                std::cout<<"assertion: "<<propertyExpr<<std::endl;
            if(checkResult) {
                if (debugMode)
                    std::cout<<"Result: satisfied!"<<std::endl;
            }
            else {
                if (debugMode)
                    std::cout<<"Result: VIOLATED!!"<<std::endl;
                preCond.abnormalTerminationCode = THROW;
                preCond.goHead = false;
            }
            postCondVec.push_back(preCond);
            return postCondVec;
        }
        else if(funcName.compare("require") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funCall->arguments();
            assert(argumentsExp.size() == 1 ||argumentsExp.size() == 2 );

            Expression const& property = *argumentsExp[0];
            z3::expr propertyExpr = solExprTranslator->translate(&property, preCond);
            // g_mechanism.assumptions.push_back(propertyExpr);

            preCond.pathCondition.push_back(propertyExpr);

            postCondVec.push_back(preCond);

            return postCondVec;
        } else if(funcName.compare("revert") == 0) {
                preCond.abnormalTerminationCode = THROW;
                preCond.goHead = false;
                postCondVec.push_back(preCond);
                return postCondVec;
        }
    }
    else if(MemberAccess const* funExpId = dynamic_cast<MemberAccess const*>(&funExp)) {
        funcName = dynamic_cast<std::string const&>(funExpId->memberName());

        if(debugMode) {
            std::cerr<<"member function call: "<<funcName<<std::endl;
        }

        Expression const& motherExpr = funExpId->expression();

        if(funcName.compare("value") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funCall->arguments();
            assert(argumentsExp.size() == 1);
            z3::expr valueExpr = solExprTranslator->translate(argumentsExp[0].get(), preCond);

            preCond.stateVarValueZ3ExprMap.at("msg.value") = valueExpr;

            std::cerr<<"update msg.value: "<<valueExpr<<std::endl;

            if(FunctionCall const* childCall = dynamic_cast<FunctionCall const*>(&motherExpr)) {
                std::vector<ContextInfo> subCallResultVec = strongestPostcondition(childCall, preCond);
                assert(subCallResultVec.size() == 1);
                preCond = subCallResultVec[0];
            }

            postCondVec.push_back(preCond);

            return postCondVec;
        }
        else if(funcName.compare("gas") == 0) {
            if(FunctionCall const* childCall = dynamic_cast<FunctionCall const*>(&motherExpr)) {
                std::vector<ContextInfo> subCallResultVec = strongestPostcondition(childCall, preCond);
                assert(subCallResultVec.size() == 1);
                preCond = subCallResultVec[0];
            }

            postCondVec.push_back(preCond);

            return postCondVec;
        }
        else if(funcName.compare("transfer") == 0) {
            postCondVec.push_back(preCond);

            return postCondVec;
        }
        else if(funcName.compare("send") == 0) {
            postCondVec.push_back(preCond);

            return postCondVec;
        }
    }
    else if(FunctionCall const* childCall = dynamic_cast<FunctionCall const*>(&funExp)) {
        if(debugMode) {
            std::cerr<<"call childCall"<<std::endl;
        }

        std::vector<ContextInfo> subCallResultVec = strongestPostcondition(childCall, preCond);

        //return subCallResultVec;

        assert(subCallResultVec.size() == 1);
        preCond = subCallResultVec[0];

        funcName = getRealFuncCallName(childCall);
    }
    else{
        std::cerr<<"Cannot get the name of the function call ["<<funcName<<"]"<<std::endl;
        assert(false);
    }

    if(debugMode) {
        std::cerr<<"calling function: "<<funcName<<std::endl;
    }

    if(funcName.compare("call") == 0) {
        if(debugMode) {
            std::cerr<<"skip: "<<funcName<<std::endl;
        }

        postCondVec.push_back(preCond);

        return postCondVec;
    }

    FunctionDefinition const* funcDef = getFuncDefinition(funcName);
    assert(funcDef != nullptr);

    std::vector<ASTPointer<VariableDeclaration>> paraVec = funcDef->CallableDeclaration::parameters();;
    std::vector<ASTPointer<Statement>> statements = funcDef->body().statements();

    std::vector<ASTPointer<Expression const>> argumentsExp = funCall->arguments();

    assert(argumentsExp.size() == paraVec.size());

    std::vector<z3::expr> argsExprVec;
    for(unsigned i = 0; i < argumentsExp.size(); i++) {
        Expression const& RHS = *(argumentsExp[i]);
        z3::expr rightExpr = solExprTranslator->translate(&RHS, preCond);
        argsExprVec.push_back(rightExpr);
    }

    try{
        preCond.funcCallDepthMap.at(funcName) = preCond.funcCallDepthMap.at(funcName) + 1;
    }
    catch(...){
        preCond.funcCallDepthMap.emplace(funcName, 1);
    }

    if(debugMode) {
        std::cerr<<"increase ["<<funcName<<"]'s call depth to: "<<preCond.funcCallDepthMap.at(funcName)<<std::endl;
    }

    for(unsigned i = 0; i < paraVec.size(); i++) {

        std::string varFullName = getVarFullName(paraVec[i].get(), preCond);

        try {
            preCond.localVarValueZ3ExprMap.at(varFullName) = argsExprVec[i];
        }
        catch(...) {
            TypePointer typePtr = paraVec[i]->type();

            z3::sort typeSort = typeSortInZ3(typePtr);

            z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

            std::pair<std::string, z3::expr> _pair(varFullName, argsExprVec[i]);
            preCond.localVarValueZ3ExprMap.insert(_pair);

            if(debugMode) {
                std::cerr<<"add a variable ["<<varFullName<<"] into localVarValueZ3ExprMap"<<std::endl;
            }
        }

        if(debugMode) {
            std::cerr<<"rightExpr: "<<argsExprVec[i]<<std::endl;
        }
    }


    postCondVec.push_back(preCond);
    assert(postCondVec.size() == 1);

    for(unsigned i = 0; i < postCondVec.size(); i++) {
        if(debugMode) {
            std::cerr<<"before function call: "<<std::endl;
            postCondVec[i].printContext();
        }
    }

    assert(postCondVec.size() == 1);

    FunctionDefinition const* originalFuncDef = postCondVec[0].funcScope;
    postCondVec[0].funcScope = funcDef;

    for(unsigned i = 0; i < statements.size(); i++) {
        Statement const* conStmt = statements[i].get();
        postCondVec = strongestPostcondition(conStmt, postCondVec);
    }

    assert(originalFuncDef);

    for(unsigned i = 0; i < postCondVec.size(); i++) {
        postCondVec[i].funcScope = originalFuncDef;

        if(postCondVec[i].goHead == false && postCondVec[i].abnormalTerminationCode == RETURN) {
            postCondVec[i].goHead = true;
            postCondVec[i].abnormalTerminationCode = NONE;
        }

        if(debugMode) {
            std::cerr<<"["<<funcName<<"]'s call depth: "<<preCond.funcCallDepthMap.at(funcName)<<std::endl;
        }

        try{
            postCondVec[i].funcCallDepthMap.at(funcName) = postCondVec[i].funcCallDepthMap.at(funcName) - 1;
            assert(postCondVec[i].funcCallDepthMap.at(funcName) >= 0);
        }
        catch(...){
            std::cerr<<"This should not happen!"<<std::endl;
            assert(false);
        }

        if(debugMode) {
            std::cerr<<"decrease ["<<funcName<<"]'s call depth to: "<<postCondVec[i].funcCallDepthMap.at(funcName)<<std::endl;
        }

        if(debugMode) {
            std::cerr<<"after function call: "<<std::endl;
            postCondVec[i].printContext();
        }
    }

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Statement const* stmt, ContextInfo& preCond) {

    if(debugMode) {
        std::cerr<<"invoking sp for <Statement>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    if(ExpressionStatement const* conStmt = dynamic_cast<ExpressionStatement const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(IfStatement const* conStmt = dynamic_cast<IfStatement const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(Continue const* conStmt = dynamic_cast<Continue const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(Return const* conStmt = dynamic_cast<Return const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(Break const* conStmt = dynamic_cast<Break const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(Throw const* conStmt = dynamic_cast<Throw const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(VariableDeclarationStatement const* conStmt = dynamic_cast<VariableDeclarationStatement const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(WhileStatement const* conStmt = dynamic_cast<WhileStatement const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(ForStatement const* conStmt = dynamic_cast<ForStatement const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else if(Block const* conStmt = dynamic_cast<Block const*>(stmt)){
        postCondVec = strongestPostcondition(conStmt, preCond);
    }
    else{
        if (debugMode){
            std::cerr<<"The statement is not currently supported: "<<stmt->location()<<std::endl;
            // assert(false);
            std::cerr<<"Now tolerate all failure"<<std::endl;
        }
        postCondVec.push_back(preCond);
    }

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Block const *stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <Block>"<<std::endl;
    }

    std::vector<ContextInfo> resultVec;

    if(preCond.goHead == false) {
        resultVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return resultVec;
    }

    std::vector<ASTPointer<Statement>> const& stmtVec = stmt->statements();

    resultVec.push_back(preCond);

    for(unsigned int index = 0; index < stmtVec.size(); ++index){
        Statement const* stmt = (stmtVec[index]).get();
        resultVec = strongestPostcondition(stmt, resultVec);
    }
    return resultVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(UnaryOperation const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <UnaryOperation>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    Expression const& Operand = stmt->subExpression();

    if(Identifier const* idOperand = dynamic_cast<Identifier const*>(&Operand)){
        z3::expr idExpr = solExprTranslator->translate(idOperand, preCond);
        Token opToken = stmt->getOperator();

        if(opToken == Token::Inc) {
            z3::expr updatedExpr = (idExpr + 1);
            updateContextInfo(idOperand, updatedExpr, preCond);
        }
        else if(opToken == Token::Dec){
            z3::expr updatedExpr = (idExpr - 1);
            updateContextInfo(idOperand, updatedExpr, preCond);
        }
        else {
            std::string opstring = dev::solidity::TokenTraits::toString(opToken);
            std::cerr<<"["<<opstring<<"]"<<": this unary operation is not supported yet!"<<std::endl;
            assert(false);
        }
    }
    else {
        std::cerr<<"This should not happen! Operand is not an Idendifier!"<<std::endl;
        assert(false);
    }

    postCondVec.push_back(preCond);
    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(ExpressionStatement const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <ExpressionStatement>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    Expression const* expStmt = &(stmt->expression());

    if(Assignment const* assignmentExpr = dynamic_cast<Assignment const*>(expStmt)){
        postCondVec = strongestPostcondition(assignmentExpr, preCond);
    }
    else if(FunctionCall const* funcCallExpr = dynamic_cast<FunctionCall const*>(expStmt)){
        auto funcName = getRealFuncCallName(funcCallExpr);
    
    if(funcName.find("declare_smt")!=std::string::npos){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr var = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.variables_smt.emplace_back(var);
        postCondVec[postCondVec.size()-1].mechanism.variables_smt_str.emplace_back(nodeString(expr));

 	}
	else if(funcName.find("declare_variable")!=std::string::npos){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr var = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.variables.emplace_back(var);
        postCondVec[postCondVec.size()-1].mechanism.variables_str.emplace_back(nodeString(expr));
	}
	else if(funcName.compare("declare_type")==0){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr type = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.model_type=type;
	}
	else    if(funcName.compare("declare_bidder")==0){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 3);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr id = solExprTranslator->translate(&expr,preCond);
	    Expression const& expr2 = *argumentsExp[1];
	    z3::expr bid = solExprTranslator->translate(&expr2,preCond);
	    Expression const& expr3 = *argumentsExp[2];
	    z3::expr valuation = solExprTranslator->translate(&expr3,preCond);
	    std::vector<z3::expr> bidder;
	    bidder.push_back(id) ;
	    bidder.push_back(bid) ;
	    bidder.push_back(valuation) ;
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.bidders.push_back(bidder);
	}
	else	if(funcName.compare("declare_allocation")==0){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr allocation = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.allocation=allocation;
	}
	else	if(funcName.compare("declare_clearprice")==0)
	{
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr price = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.price=price;
	}
	else	if(funcName.compare("declare_utility")==0){

            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 2);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr id = solExprTranslator->translate(&expr,preCond);
	    Expression const& expr2 = *argumentsExp[1];
	    z3::expr utility = solExprTranslator->translate(&expr2,preCond);
	    std::vector<z3::expr> id_utility;
	    id_utility.push_back(id);
	    id_utility.push_back(utility);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.utilities.push_back(id_utility);
	}
	else	if(funcName.compare("declare_check")==0){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr check_type = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.check_types.push_back(check_type);
	}
	else	if(funcName.compare("declare_invariant")==0){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);
	    Expression const& expr = *argumentsExp[0];
	    z3::expr invariant_type = solExprTranslator->translate(&expr,preCond);
	    postCondVec.push_back(preCond);
	    postCondVec[postCondVec.size()-1].mechanism.invariant_types.push_back(invariant_type);
	}
    else if (funcName.compare("declare_assumption")==0){
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1||argumentsExp.size() == 2);
            Expression const& expr = *argumentsExp[0];
            z3::expr assumption = solExprTranslator->translate(&expr,preCond);
            assert(assumption.is_bool());
            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].mechanism.assumptions.push_back(assumption);
	}
	else
        if(funcName.compare("sse_maximize") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);

            Expression const& max_exp = *argumentsExp[0];
            z3::expr z3_max_exp = solExprTranslator->translate(&max_exp, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_max_exps.push_back(z3_max_exp);
            postCondVec[postCondVec.size()-1].sol_max_exps.emplace_back(argumentsExp[0]);
            return postCondVec;
        }else if(funcName.compare("sse_minimize") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);

            Expression const& min_exp = *argumentsExp[0];
            z3::expr z3_min_exp = solExprTranslator->translate(&min_exp, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_min_exps.push_back(z3_min_exp);
            postCondVec[postCondVec.size()-1].sol_min_exps.emplace_back(argumentsExp[0]);
            return postCondVec;
        }else if(funcName.compare("sse_utility") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);

            Expression const& min_exp = *argumentsExp[0];
            z3::expr z3_min_exp = solExprTranslator->translate(&min_exp, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_utilities.push_back(z3_min_exp);
            postCondVec[postCondVec.size()-1].sol_utilities.emplace_back(argumentsExp[0]);
            return postCondVec;
        }else if(funcName.compare("sse_revenue") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);

            Expression const& min_exp = *argumentsExp[0];
            z3::expr z3_min_exp = solExprTranslator->translate(&min_exp, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_revenue.push_back(z3_min_exp);
            postCondVec[postCondVec.size()-1].sol_revenue.emplace_back(argumentsExp[0]);
            return postCondVec;
        }else if(funcName.compare("sse_winner") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 1);

            Expression const& min_exp = *argumentsExp[0];
            z3::expr z3_min_exp = solExprTranslator->translate(&min_exp, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_winners.push_back(z3_min_exp);
            postCondVec[postCondVec.size()-1].sol_winners.emplace_back(argumentsExp[0]);
            return postCondVec;
        }else if(funcName.compare("sse_optimal_violate_check") == 0) {
            assert(preCond.z3_optimal_payment_register.size()>0);
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 3);

            Expression const& payment = *argumentsExp[0];
            auto a = argumentsExp[1];
            auto b = argumentsExp[2];
            z3::expr z3_payment= solExprTranslator->translate(&payment, preCond);
            // z3::expr z3_a = solExprTranslator->translate(&a, preCond);
            // z3::expr z3_b = solExprTranslator->translate(&b, preCond);
            assert(preCond.z3_optimal_payment_register.end()!=preCond.z3_optimal_payment_register.find(std::make_pair(nodeString(*a),nodeString(*b))));
            // auto& optional_payment = preCond.z3_optimal_payment_register[std::make_pair(nodeString(a),nodeString(b))];
            
            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_optimal_check_exprs.emplace_back(std::make_tuple(z3_payment, a , b));
            postCondVec[postCondVec.size()-1].sol_optimal_check_exprs.emplace_back(argumentsExp[0]);
    }else if(funcName.compare("sse_efficient_violate_check") == 0) {
            assert(preCond.z3_efficient_expectation_register.size()>0);
            //  function sse_efficient_violate_check(uint benefit, address allocation, address other_allocation) public view {}
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();
            assert(argumentsExp.size() == 3);
            Expression const& benefit = *argumentsExp[0];
            auto a = argumentsExp[1];
            auto b = argumentsExp[2];
            // std::cout<<"sse_efficient_violate_check"<<std::endl;
            // std::cout<<nodeString(a)<<":"<<nodeString(b)<<std::endl;
            z3::expr z3_benefit= solExprTranslator->translate(&benefit, preCond);
            // z3::expr z3_a = solExprTranslator->translate(&a, preCond);
            // z3::expr z3_b = solExprTranslator->translate(&b, preCond);
            assert(preCond.z3_efficient_expectation_register.end()!=preCond.z3_efficient_expectation_register.find(std::make_pair(nodeString(*a),nodeString(*b))));
            // auto& optional_benefit = preCond.z3_efficient_expectation_register[std::make_pair(nodeString(a),nodeString(b))];
            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_efficient_check_exprs.emplace_back(std::make_tuple(z3_benefit, a, b)); 
            postCondVec[postCondVec.size()-1].sol_efficient_check_exprs.emplace_back(argumentsExp[0]);
    }else if(funcName.compare("sse_collusion_violate_check") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();       
            assert(argumentsExp.size() == 5);

            Expression const& u12 = *argumentsExp[0];
            Expression const& u1_v1 = *argumentsExp[1];
            Expression const& u1_v_1 = *argumentsExp[2];
            Expression const& u2_v2 = *argumentsExp[3];
            Expression const& u2_v_2 = *argumentsExp[4];

            z3::expr z3_colusion_u12 = solExprTranslator->translate(&u12, preCond);
            z3::expr z3_u1_v1 = solExprTranslator->translate(&u1_v1, preCond);
            z3::expr z3_u1_v_1 = solExprTranslator->translate(&u1_v_1, preCond);
            z3::expr z3_u2_v2 = solExprTranslator->translate(&u2_v2, preCond);
            z3::expr z3_u2_v_2 = solExprTranslator->translate(&u2_v_2, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_collusion_check_exprs.push_back(std::make_tuple(z3_colusion_u12, z3_u1_v1, z3_u1_v_1, z3_u2_v2, z3_u2_v_2)); 
            postCondVec[postCondVec.size()-1].sol_collusion_check_exprs.emplace_back(std::make_tuple(argumentsExp[0],argumentsExp[1]));
    }else if(funcName.compare("sse_truthful_violate_check") == 0) {
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();       
            assert(argumentsExp.size() == 3);

            Expression const& expr = *argumentsExp[0];
            Expression const& a = *argumentsExp[1];
            Expression const& b = *argumentsExp[2];
            z3::expr z3_check_expr = solExprTranslator->translate(&expr, preCond);
            z3::expr z3_a = solExprTranslator->translate(&a, preCond);
            z3::expr z3_b = solExprTranslator->translate(&b, preCond);

            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_truth_check_exprs.push_back(std::make_tuple(z3_check_expr, z3_a, z3_b));
            postCondVec[postCondVec.size()-1].sol_truth_check_exprs.emplace_back(argumentsExp[0]);
            return postCondVec;
        }else if(funcName.compare("sse_optimal_payment_register") == 0) {
            //sse_optimal_payment_register(allocation, player, payment)
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();       
            assert(argumentsExp.size() == 3);

            Expression const& allocation = *argumentsExp[0];
            Expression const& player = *argumentsExp[1];
            Expression const& payment = *argumentsExp[2];
            z3::expr z3_payment = solExprTranslator->translate(&payment, preCond);
            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_optimal_payment_register.insert(std::make_pair(std::make_pair(nodeString(allocation), nodeString(player)), z3_payment));
            return postCondVec;

        }else if(funcName.compare("sse_efficient_expectation_register") == 0) { 
            // std::cout<<"sse_efficient_expectation_register"<<std::endl;
            //ss_efficient_expectation_register(allocation, player, expectation)
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();       
            assert(argumentsExp.size() == 3);

            Expression const& allocation = *argumentsExp[0];
            Expression const& player = *argumentsExp[1];
            Expression const& expectation = *argumentsExp[2];
            z3::expr z3_expectation = solExprTranslator->translate(&expectation, preCond);
            //std::cout<<nodeString(allocation)<<":"<<nodeString(player)<<std::endl;
            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_efficient_expectation_register.insert(std::make_pair(std::make_pair(nodeString(allocation), nodeString(player)), z3_expectation));
            return postCondVec;
        }else if(funcName.compare("sse_validate_outcome_postcondition") == 0){
	   // TO DO 
	   // sse_validate_outcome_postcondition(bool cond, string description)
	    std::cout<< "sse_validate_outcome_postcondition"<<std::endl;
            std::vector<ASTPointer<Expression const>> argumentsExp = funcCallExpr->arguments();       
            assert(argumentsExp.size() == 2);
  	    
            Expression const& cond = *argumentsExp[1];
            Expression const& desc = *argumentsExp[0];
            z3::expr z3_cond = solExprTranslator->translate(&cond, preCond);
	    std::string str_desc = nodeString(desc);
            postCondVec.push_back(preCond);
            postCondVec[postCondVec.size()-1].z3_validate_outcome_postconditions.insert(std::make_pair(str_desc, z3_cond));
            return postCondVec;
	    }	
        else{
            postCondVec = strongestPostcondition(funcCallExpr, preCond);
        }
    }
    else if(UnaryOperation const* unaryOpExpr = dynamic_cast<UnaryOperation const*>(expStmt)){
        postCondVec = strongestPostcondition(unaryOpExpr, preCond);
    }
    else{
        std::cerr<<"Un-supported <ExpressionStatement> currently!"<<std::endl;
        assert(false);
    }
    return postCondVec;
}


std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Assignment const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <Assignment>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    std::vector<z3::expr> rightExprVec;

    if(debugMode) {
        preCond.printContext();
    }

    Expression const& leftOperand = stmt->leftHandSide();

    Expression const& rightOperand = stmt->rightHandSide();

    z3::expr rightExpr(z3_ctx);

    if(FunctionCall const* funcCallExpr = dynamic_cast<FunctionCall const*>(&rightOperand)) {
        std::string funcName = getRealFuncCallName(&rightOperand);

        postCondVec = strongestPostcondition(funcCallExpr, preCond);

        for(unsigned i = 0; i < postCondVec.size(); i++) {
            postCondVec[i].funcCallDepthMap.at(funcName) = postCondVec[i].funcCallDepthMap.at(funcName) + 1;

            rightExprVec.push_back(solExprTranslator->translate(&rightOperand, postCondVec[i]));

            postCondVec[i].funcCallDepthMap.at(funcName) = postCondVec[i].funcCallDepthMap.at(funcName) - 1;
        }
    }
    else {
        rightExpr = solExprTranslator->translate(&rightOperand, preCond);
        rightExprVec.push_back(rightExpr);
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"rightExpr: "<<rightExpr<<std::endl;
        }
    }

    assert(postCondVec.size() == rightExprVec.size());

    for(unsigned index = 0; index < postCondVec.size(); index++) {
        if(TupleExpression const* tupleExp = dynamic_cast<TupleExpression const*>(&leftOperand)) {
            std::vector<ASTPointer<Expression>> const& componentsExp = tupleExp->components();
            //z3::expr leftTupleExpr = solExprTranslator->translate(tupleExpr, postCondVec[index]);
            z3::expr rightExpr = rightExprVec[index];

            assert(rightExpr.is_app());
            assert(componentsExp.size() == rightExpr.num_args());
            for(unsigned i = 0; i < rightExpr.num_args(); i++) {
                    Expression const& leftExpr = *(componentsExp[i]);
                    updateContextInfo(&leftExpr, rightExpr.arg(i), postCondVec[index]);
            }
        }
        else {
            Token Op = stmt->assignmentOperator();
            z3::expr rightOpInZ3(z3_ctx);

            z3::expr leftOpInZ3 = solExprTranslator->translate(&leftOperand, postCondVec[index]);

            if(Op == Token::Assign){
                rightOpInZ3 = rightExprVec[index];
            }
            else if(Op == Token::AssignAdd){
                rightOpInZ3 = leftOpInZ3 + rightExprVec[index];
            }
            else if(Op == Token::AssignSub){
                rightOpInZ3 = leftOpInZ3 - rightExprVec[index];
            }
            else if(Op == Token::AssignMul){
                rightOpInZ3 = leftOpInZ3 * rightExprVec[index];
            }
            else if(Op == Token::AssignDiv){
                rightOpInZ3 = leftOpInZ3 / rightExprVec[index];
            }

            else if(Op == Token::AssignBitOr){
                rightOpInZ3 = leftOpInZ3 | rightExprVec[index];
            }
            else if(Op == Token::AssignBitXor){
                rightOpInZ3 = leftOpInZ3 ^ rightExprVec[index];
            }
            else if(Op == Token::AssignBitAnd){
                rightOpInZ3 = leftOpInZ3 & rightExprVec[index];
            }
            else{
                std::cerr<<"Sorry, this assignment is not supported currently!"<<std::endl;
                assert(false);
            }

            assert(rightOpInZ3.to_string() != "null");

            //updateContextInfo(&leftOperand, rightExprVec[index], postCondVec[index]);
            updateContextInfo(&leftOperand, rightOpInZ3, postCondVec[index]);
        }
    }

    if(debugMode) {
        std::cerr<<"after assignment: "<<std::endl;
        for(unsigned i = 0; i < postCondVec.size(); i++) {
            std::cerr<<"postCondVec["<<i<<"]: "<<std::endl;
            postCondVec[i].printContext();
        }
    }

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(IfStatement const* stmt, ContextInfo& preCond) {
  
    if(debugMode) {
        std::cerr<<"------------------------------------"<<std::endl;
        std::cerr<<"invoking sp for <IfStatement>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }
        std::cout<<__LINE__<< "go ahead = false" <<std::endl;
        return postCondVec;
    }

    Expression const& ifCondition = stmt->condition();

    std::ignore = preCond;

    z3::expr ifCondZ3Expr = solExprTranslator->translate(&ifCondition, preCond);
    z3::expr negIfCondZ3Expr = !(ifCondZ3Expr);

    Statement const* trueBody = &(stmt->trueStatement());
    Statement const* falseBody = stmt->falseStatement();
   // std::cout<<__LINE__<< "If statement" <<std::endl;
    // std::cout<<__LINE__<< "If statement" << stmt->location().source->source().substr(stmt->location().start, stmt->location().end - stmt->location().start)<<std::endl;
    if(trueBody) {
        if(debugMode) {
            std::cerr<<"executing TRUE branch"<<std::endl;
        }

        if(checkSatisfiability(ifCondZ3Expr, preCond)) {
            if(debugMode) {
                std::cerr<<"TRUE branch is feasible! Follow it."<<std::endl;
            }

            ContextInfo truePathCtxInfo = preCond;
            truePathCtxInfo.pathCondition.push_back(ifCondZ3Expr);

            std::vector<ContextInfo> truePathCondVec;

            truePathCondVec = strongestPostcondition(trueBody, truePathCtxInfo);
            postCondVec.insert(postCondVec.end(), truePathCondVec.begin(), truePathCondVec.end());
        }
        else {
            if(debugMode) {
                std::cerr<<"TRUE branch is not feasible! Skipped."<<std::endl;
            }
        }
        // std::cout<<__LINE__<< "trueBody" <<std::endl;
    }

    if(falseBody) {
        //std::cout<<__LINE__<< "falseBody" <<std::endl;
        if(debugMode) {
            std::cerr<<"executing FALSE branch"<<std::endl;
        }

        if(checkSatisfiability(negIfCondZ3Expr, preCond)) {
            if(debugMode) {
                std::cerr<<"FALSE branch is feasible! Follow it."<<std::endl;
            }

            ContextInfo falsePathCtxInfo = preCond;
            falsePathCtxInfo.pathCondition.push_back(negIfCondZ3Expr);

            std::vector<ContextInfo> falsePathCondVec;

            falsePathCondVec = strongestPostcondition(falseBody, falsePathCtxInfo);
            postCondVec.insert(postCondVec.end(), falsePathCondVec.begin(), falsePathCondVec.end());
            return postCondVec;
        }
        else {
            if(debugMode) {
                std::cerr<<"FALSE branch is not feasible! Skipped."<<std::endl;
            }
        }

    }
    else {
        // std::cout<<__LINE__<< "falseBody empty" <<std::endl;
        if(checkSatisfiability(negIfCondZ3Expr, preCond)) {
            if(debugMode) {
                std::cerr<<"FALSE branch is feasible! Follow it."<<std::endl;
            }
            ContextInfo falsePathCtxInfo = preCond;
            falsePathCtxInfo.pathCondition.push_back(negIfCondZ3Expr);
            postCondVec.push_back(falsePathCtxInfo);
        }
        else {
            if(debugMode) {
                std::cerr<<"FALSE branch is not feasible! Skipped."<<std::endl;
            }
        }
    }

    if(debugMode) {
        std::cerr<<"------------------------------------"<<std::endl;
    }

    return postCondVec;
}


std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Break const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <Break>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    preCond.goHead = false;
    preCond.abnormalTerminationCode = BREAK;

    std::ignore = stmt;

    postCondVec.push_back(preCond);


    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Continue const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <Continue>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    preCond.goHead = false;
    preCond.abnormalTerminationCode = CONTINUE;

    std::ignore = stmt;

    postCondVec.push_back(preCond);

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Return const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <Return>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    preCond.goHead = false;
    preCond.abnormalTerminationCode = RETURN;

    Expression const* returnedExp = stmt->expression();
    FunctionDefinition const* funcDef = preCond.funcScope;


    if(returnedExp) {
        std::vector<ASTPointer<VariableDeclaration>> returnParamVec = funcDef->returnParameters();

        if (FunctionCall const* funCallExpr = dynamic_cast<FunctionCall const*>(returnedExp)) {
            std::ignore = funCallExpr;
            std::cerr<<"Please assign the return value of a function to a variable, and then return the value of the variable."<<std::endl;
            assert(false);
        }

        z3::expr returnExprInZ3 = solExprTranslator->translate(returnedExp, preCond);

        if(returnParamVec.size() == 1) {
            //std::string const& varName = dynamic_cast<std::string const&>(returnParamVec[0]->Declaration::name());
            //std::string varFullName = varName + nameSeparator + funcDef->name();
            std::string varFullName = getVarFullName(returnParamVec[0].get(), preCond);

            if(debugMode) {
                std::cerr<<"returnExprInZ3: "<<returnExprInZ3<<std::endl;
            }

            try {
                preCond.localVarValueZ3ExprMap.at(varFullName) = returnExprInZ3;
            }
            catch(...) {
                TypePointer typePtr = returnParamVec[0]->type();

                z3::sort typeSort = typeSortInZ3(typePtr);

                z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

                std::pair<std::string, z3::expr> _pair(varFullName, returnExprInZ3);
                preCond.localVarValueZ3ExprMap.insert(_pair);

                if(debugMode) {
                    std::cerr<<"add a variable ["<<varFullName<<"] into localVarValueZ3ExprMap"<<std::endl;
                }
            }
        }
        else {
            for(unsigned i = 0; i < returnParamVec.size(); i++) {
                std::string varFullName = getVarFullName(returnParamVec[i].get(), preCond);

                if(debugMode) {
                    std::cerr<<"returnExprInZ3: "<<returnExprInZ3.arg(i)<<std::endl;
                }

                try{
                    preCond.localVarValueZ3ExprMap.at(varFullName) = returnExprInZ3.arg(i);
                }
                catch(...) {
                    TypePointer typePtr = returnParamVec[i]->type();

                    z3::sort typeSort = typeSortInZ3(typePtr);

                    z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

                    std::pair<std::string, z3::expr> _pair(varFullName, returnExprInZ3.arg(i));
                    preCond.localVarValueZ3ExprMap.insert(_pair);

                    if(debugMode) {
                        std::cerr<<"add a variable ["<<varFullName<<"] into localVarValueZ3ExprMap"<<std::endl;
                    }
                }
            }
        }
    }

    postCondVec.push_back(preCond);


    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(Throw const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <Throw>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }
        preCond.abnormalTerminationCode = THROW;
        postCondVec.push_back(preCond);
        return postCondVec;
    }

    //****************************************
    // This needs to be refined.
    //@author liuye. revised. set abnormalTerminationCode to THROW.

    std::ignore = stmt;
    preCond.goHead = false;
    preCond.abnormalTerminationCode = THROW;
    postCondVec.push_back(preCond);

    //****************************************

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(VariableDeclarationStatement const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <VariableDeclarationStatement>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }


    std::vector<ASTPointer<VariableDeclaration>> const& varDecVec = stmt->declarations();

    Expression const* initialValue = stmt->initialValue();

    if(initialValue){
        if(FunctionCall const* funcCallExpr = dynamic_cast<FunctionCall const*>(initialValue)) {
            std::ignore = funcCallExpr;
            std::cerr<<"Initialization by a function call is not supported currently"<<std::endl;
            assert(false);
        }

        z3::expr rightExpr = solExprTranslator->translate(initialValue, preCond);

        if(varDecVec.size() == 1){
            std::string varFullName = getVarFullName(varDecVec[0].get(), preCond);

            std::unordered_map<std::string, z3::expr>::const_iterator itr = preCond.stateVarValueZ3ExprMap.find(varFullName);

            if(itr != preCond.stateVarValueZ3ExprMap.end()) {
                preCond.stateVarValueZ3ExprMap.at(varFullName) = rightExpr;
            }
            else {
                itr = preCond.localVarValueZ3ExprMap.find(varFullName);

                if(itr != preCond.localVarValueZ3ExprMap.end()) {
                    preCond.localVarValueZ3ExprMap.at(varFullName) = rightExpr;
                }
                else {
                    assert(false);
                }
            }
        }
        else{
            assert(rightExpr.is_app());
            assert(varDecVec.size() == rightExpr.num_args());

            for(unsigned i = 0; i < varDecVec.size(); i++) {
                std::string varFullName = getVarFullName(varDecVec[i].get(), preCond);

                std::unordered_map<std::string, z3::expr>::const_iterator itr = preCond.stateVarValueZ3ExprMap.find(varFullName);

                if(itr != preCond.stateVarValueZ3ExprMap.end()) {
                    preCond.stateVarValueZ3ExprMap.at(varFullName) = rightExpr.arg(i);
                }
                else {
                    itr = preCond.localVarValueZ3ExprMap.find(varFullName);

                    if(itr != preCond.localVarValueZ3ExprMap.end()) {
                        preCond.localVarValueZ3ExprMap.at(varFullName) = rightExpr.arg(i);
                    }
                    else {
                        assert(false);
                    }
                }
            }
        }
    }

    //****************************************
    // This needs to be refined.

    postCondVec.push_back(preCond);

    //****************************************

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(WhileStatement const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <WhileStatement>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    Expression const& whileCondition = stmt->condition();
    z3::expr condition = solExprTranslator->translate(&whileCondition, preCond);
    z3::expr negationPart = !(condition);


    Statement const& Body = stmt->body();
    if(checkSatisfiability(condition, preCond)){
        if(debugMode) {
            std::cerr<<"loop condition is feasible!"<<std::endl;
        }

        ContextInfo trueBranchCtxInfo = preCond;
        trueBranchCtxInfo.pathCondition.push_back(condition);

        //std::vector<ContextInfo> truePathCtxVec;

        postCondVec = strongestPostcondition(&Body, trueBranchCtxInfo);

        for(unsigned i = 0; i < postCondVec.size(); i++) {
            if(postCondVec[i].goHead == false && postCondVec[i].abnormalTerminationCode == CONTINUE) {
                postCondVec[i].goHead = true;
                postCondVec[i].abnormalTerminationCode = NONE;
            }
        }

        postCondVec = strongestPostcondition(stmt, postCondVec);

        for(unsigned i = 0; i < postCondVec.size(); i++) {
            if(postCondVec[i].goHead == false && postCondVec[i].abnormalTerminationCode == BREAK) {
                postCondVec[i].goHead = true;
                postCondVec[i].abnormalTerminationCode = NONE;
            }
        }
    }
    else{
        if(debugMode) {
            std::cerr<<"loop condition is NOT feasible! Terminating the loop!"<<std::endl;
        }

        //ContextInfo falseBranchCtxInfo = preCond;
        //falseBranchCtxInfo.pathCondition.push_back(negationPart);

        //postCondVec.push_back(falseBranchCtxInfo);

        preCond.pathCondition.push_back(negationPart);
        postCondVec.push_back(preCond);
    }

    return postCondVec;
}

std::vector<ContextInfo> SymExecEngine::
strongestPostcondition(ForStatement const* stmt, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"invoking sp for <ForStatement>"<<std::endl;
    }

    std::vector<ContextInfo> postCondVec;

    if(preCond.goHead == false) {
        postCondVec.push_back(preCond);

        if(debugMode) {
            std::cerr<<"skipped"<<std::endl;
        }

        return postCondVec;
    }

    int visitNum = -1;
    try{
        //std::cerr<<"for's id: "<<stmt->id()<<std::endl;
        visitNum = astNodeVisitMap.at(stmt->id());
        //std::cerr<<"visiNum: "<<visitNum<<std::endl;
    }
    catch(...){
        astNodeVisitMap.emplace(stmt->id(), 0);
        visitNum = 0;
    }

    assert(visitNum >= 0);

    if(visitNum == 0) {
        Statement const* initStmt = stmt->initializationExpression();

        std::vector<ContextInfo> initCondVec;
        initCondVec = strongestPostcondition(initStmt, preCond);
        assert(initCondVec.size() == 1);

        preCond = initCondVec[0];
    }

    astNodeVisitMap.at(stmt->id()) = astNodeVisitMap.at(stmt->id()) + 1;
    //std::cerr<<"+astNodeVisitMap.at("<<stmt->id()<<"): "<<astNodeVisitMap.at(stmt->id())<<std::endl;

    Expression const* loopCondition = stmt->condition();
    z3::expr condition = solExprTranslator->translate(loopCondition, preCond);
    z3::expr negationPart = !(condition);

    Statement const& Body = stmt->body();

    ExpressionStatement const* loopExp = stmt->loopExpression();


    if(checkSatisfiability(condition, preCond)){
        if(debugMode) {
            std::cerr<<"loop condition is feasible!"<<std::endl;
        }

        ContextInfo trueBranchCtxInfo = preCond;
        trueBranchCtxInfo.pathCondition.push_back(condition);

        postCondVec = strongestPostcondition(&Body, trueBranchCtxInfo);

        for(unsigned i = 0; i < postCondVec.size(); i++) {
            if(postCondVec[i].goHead == false && postCondVec[i].abnormalTerminationCode == CONTINUE) {
                postCondVec[i].goHead = true;
                postCondVec[i].abnormalTerminationCode = NONE;
            }
        }

        postCondVec = strongestPostcondition(loopExp, postCondVec);

        postCondVec = strongestPostcondition(stmt, postCondVec);

        for(unsigned i = 0; i < postCondVec.size(); i++) {
            if(postCondVec[i].goHead == false && postCondVec[i].abnormalTerminationCode == BREAK) {
                postCondVec[i].goHead = true;
                postCondVec[i].abnormalTerminationCode = NONE;
            }
        }
    }
    else{
        if(debugMode) {
            std::cerr<<"loop condition is NOT feasible! Terminating the loop!"<<std::endl;
        }

        //ContextInfo falseBranchCtxInfo = preCond;
        //falseBranchCtxInfo.pathCondition.push_back(negationPart);

        //postCondVec.push_back(falseBranchCtxInfo);

        preCond.pathCondition.push_back(negationPart);
        postCondVec.push_back(preCond);
    }

    astNodeVisitMap.at(stmt->id()) = astNodeVisitMap.at(stmt->id()) - 1;
    if (debugMode)
        std::cerr<<"-astNodeVisitMap.at("<<stmt->id()<<"): "<<astNodeVisitMap.at(stmt->id())<<std::endl;
    return postCondVec;

}


z3::sort SymExecEngine::
typeSortInZ3(TypePointer const typePtr){
    z3::sort typeSort(z3_ctx);
    if(CAST_POINTER(intTypeExpr, IntegerType, typePtr)){
    // if(std::shared_ptr<IntegerType const> intTypeExpr = std::dynamic_pointer_cast<IntegerType const>(typePtr)){
        typeSort = z3_ctx.int_sort();
    }
    else if(CAST_POINTER(boolType, BoolType, typePtr)){
    // else if(std::shared_ptr<BoolType const> boolType = std::dynamic_pointer_cast<BoolType const>(typePtr)){
        typeSort = z3_ctx.bool_sort();
    }
    else if(CAST_POINTER(arrayType, ArrayType, typePtr)){
    // else if(std::shared_ptr<ArrayType const> arrayType = std::dynamic_pointer_cast<ArrayType const>(typePtr)){
        if(arrayType->isString()){
            typeSort = z3_ctx.string_sort();
        }
        else{
            TypePointer baseType = arrayType->baseType();

            z3::sort baseSort = typeSortInZ3(baseType);

            typeSort = z3_ctx.array_sort(z3_ctx.int_sort(), baseSort);
        }
    }
    else if(CAST_POINTER(fixedBytesType, FixedBytesType, typePtr)){
    // else if(std::shared_ptr<FixedBytesType const> fixedBytesType = std::dynamic_pointer_cast<FixedBytesType const>(typePtr)){
        typeSort = z3_ctx.array_sort(z3_ctx.int_sort(), z3_ctx.int_sort());
    }
    else if(CAST_POINTER(mappingType, MappingType, typePtr)){
    // else if(std::shared_ptr<MappingType const> mappingType = std::dynamic_pointer_cast<MappingType const>(typePtr)){
        TypePointer keyType = mappingType->keyType();

        z3::sort keyTypeSort(z3_ctx);

        keyTypeSort = typeSortInZ3(keyType);

        TypePointer valueType = mappingType->valueType();

        z3::sort valueTypeSort(z3_ctx);

        valueTypeSort = typeSortInZ3(valueType);

        typeSort = z3_ctx.array_sort(keyTypeSort, valueTypeSort);
    }
    else if(CAST_POINTER(structType, StructType, typePtr)){
    // else if(std::shared_ptr<StructType const> structType = std::dynamic_pointer_cast<StructType const>(typePtr)){
        std::string structName = structType->structDefinition().name();
        //std::cerr<<"Struct Type: "<<structName<<std::endl;

        std::unordered_map<std::string, std::shared_ptr<StructInfo>>::iterator structItr = structsMap.find(structName);

        if(structItr != structsMap.end()){
            typeSort = structItr->second->structSort[0];
        }
        else{
            std::cerr<<"Undefined struct ["<<structName<<"]"<<std::endl;
            assert(false);
        }
    }
    else if(CAST_POINTER(addressType, AddressType, typePtr)){
    // else if(std::shared_ptr<AddressType const> addressType = std::dynamic_pointer_cast<AddressType const>(typePtr)){
        typeSort = z3_ctx.string_sort();
    }
    // else if (std::shared_ptr<ContractType const> contractType = std::dynamic_pointer_cast<ContractType const>(typePtr)){
    //     /**
    //     TO DO
    //     */
    //     std::cout<< __FILE__<< " "<<__LINE__ << ": found contract type of "<< contractType->contractDefinition().name() << std::endl; 

    // }
    else{
        std::string typeStr = typePtr->toString();
        std::cerr<<"The type ["<<typeStr<<"] is not supported currently."<<std::endl;
        assert(false);
    }

    assert(typeSort);

    return typeSort;
}

std::string SymExecEngine::
getArrayName(dev::solidity::Expression const* aExpr, ContextInfo& ctxInfo) {
    if(Identifier const* idExp = dynamic_cast<Identifier const*>(aExpr)){
        std::string varFullName = getVarFullName(idExp, ctxInfo);

        return varFullName;
    }
    else if(IndexAccess const* indexaccessExp = dynamic_cast<IndexAccess const*>(aExpr)){
        Expression const& baseExp = indexaccessExp->baseExpression();
        std::string varFullName = getArrayName(&baseExp, ctxInfo);

        return varFullName;
    }
    // else if (MemberAccess const* memAccExp = dynamic_cast<MemberAccess const*>(aExpr)){
    //     Expression const& Exp = memAccExp->expression();
    //     ASTString const& memnameExp = memAccExp->memberName();
    //     std::string const& memnameExpName = dynamic_cast<std::string const&>(memnameExp);
    //     return getArrayName(&Exp, ctxInfo)+"?"+memnameExpName;
    // }
    else{
        std::cerr<<"The expression is not supported currently: "<<std::endl;
        assert(false);
    }
}

FunctionDefinition const* SymExecEngine::
getFuncDefinition(std::string funcName){
    for(unsigned int i = 0; i < funcVec.size(); ++i){
        std::string const& funName_ = dynamic_cast<std::string const&>(funcVec[i]->CallableDeclaration::name());
        if(funcName == funName_){
           return funcVec[i];
        }
    }

    return nullptr;
}

void SymExecEngine::
updateContextInfo(Expression const* exp, z3::expr rightExpr, ContextInfo& preCond) {
    if(debugMode) {
        std::cerr<<"updating Context Information..."<<std::endl;
    }

    if(Identifier const* idExpr = dynamic_cast<Identifier const*>(exp)) {

        std::string varName = idExpr->name();
        std::string varFullName = getVarFullName(idExpr, preCond);

        if(debugMode) {
            std::cerr<<"updating Identifier: "<<varFullName<<std::endl;
        }

        std::unordered_map<std::string, z3::expr>::const_iterator itr = preCond.stateVarValueZ3ExprMap.find(varFullName);

        if(itr != preCond.stateVarValueZ3ExprMap.end()) {
            preCond.stateVarValueZ3ExprMap.at(varFullName) = rightExpr;
        }
        else {
            //assert(preCond.funcScope);
            //std::string varFullName = varName + nameSeparator + preCond.funcScope->name();
            //std::string varFullName = getVarFullName(idExpr);

            itr = preCond.localVarValueZ3ExprMap.find(varFullName);

            if(itr != preCond.localVarValueZ3ExprMap.end()) {
                preCond.localVarValueZ3ExprMap.at(varFullName) = rightExpr;
            }
            else {
                assert(false);
            }
        }
    }
    else if(IndexAccess const* indexAccessExpr = dynamic_cast<IndexAccess const*>(exp)) {
        Expression const& baseExp = indexAccessExpr->baseExpression();
        Expression const* basePtr = dynamic_cast<Expression const*>(&baseExp);
        z3::expr baseExpr = solExprTranslator->translate(basePtr, preCond);

        if(debugMode) {
            std::cerr<<"updating IndexAccess: "<<std::endl;
        }

        if(debugMode) {
            std::cerr<<"baseExp:" <<  nodeString(baseExp) <<std::endl; 
            std::cerr<<"baseExpr: "<<baseExpr<<std::endl;
        }

        Expression const* indexExp = indexAccessExpr->indexExpression();
        z3::expr indexExpr = solExprTranslator->translate(indexExp, preCond);

        if(debugMode) {
            std::cerr<<"indexExpr: "<<indexExpr<<std::endl;
        }

        //z3::expr indaccExp = z3::select(base,index);

        z3::expr updatedArrayExpr = z3::store(baseExpr, indexExpr, rightExpr);

        if(MemberAccess const* memAccessExpr = dynamic_cast<MemberAccess const*>(basePtr)){
            Expression const& Exp = memAccessExpr->expression();
            ASTString const& memnameExp = memAccessExpr->memberName();
            std::string const& memnameExpName = dynamic_cast<std::string const&>(memnameExp);

            if(debugMode) {
                std::cerr<<"updating MemberAccess: "<<std::endl;
            }

            TypePointer expType = Exp.annotation().type;

            CAST_POINTER(structType, StructType, expType);
            // std::shared_ptr<StructType const> structType = std::dynamic_pointer_cast<StructType const>(expType);

            std::string structName = structType->structDefinition().name();

            std::unordered_map<std::string, std::shared_ptr<StructInfo>>::iterator structItr = structsMap.find(structName);
            z3::expr motherExpr = solExprTranslator->translate(&Exp, preCond);

            if(structItr != structsMap.end()){
                int fieldIndex = structItr->second->getProjIndex(memnameExpName);
                assert(fieldIndex != -1);

                z3::expr_vector resultVec(z3_ctx);

                for(int i = 0; i < (int)structItr->second->fieldNames.size(); i++) {
                    if(i == fieldIndex) {
                        resultVec.push_back(updatedArrayExpr);
                    }
                    else {
                        if(IndexAccess const* idAccess = dynamic_cast<IndexAccess const*>(&Exp)) {
                            std::vector<z3::func_decl_vector> projectors = structItr->second->projectors;
                            z3::expr fieldExpr = projectors[0][i](motherExpr);
                            resultVec.push_back(fieldExpr);
                            std::ignore = idAccess;
                        }
                        else {
                            try{
                                assert(motherExpr.is_app());
                                z3::expr fieldExpr = motherExpr.arg(i);
                                resultVec.push_back(fieldExpr);

                                assert(motherExpr.num_args() == structItr->second->fieldNames.size());
                            }
                            catch(...) {
                                std::vector<z3::func_decl_vector> projectors = structItr->second->projectors;
                                z3::expr fieldExpr = projectors[0][i](motherExpr);
                                resultVec.push_back(fieldExpr);
                            }
                        }
                    }
                }

                z3::func_decl structConstructor = structItr->second->structConstructor[0];

                assert(structConstructor.to_string() != "null");

                z3::expr updatedStruct = structConstructor(resultVec);

                if(debugMode) {
                    std::cerr<<"updatedStruct: "<<updatedStruct<<std::endl;
                }

                updateContextInfo(&Exp, updatedStruct, preCond);
            }
            else{
                std::cerr<<"Undefined struct ["<<structName<<"]"<<std::endl;
                assert(false);
            }
        }
        else{
            if(debugMode) {
                std::cerr<<"updatedArrayExpr: "<<updatedArrayExpr<<std::endl;
            }

            std::string arrayName = getArrayName(basePtr, preCond);

            if(debugMode) {
                std::cerr<<"arrayName: "<<arrayName<<std::endl;
            }

            std::unordered_map<std::string, z3::expr>::const_iterator itr = preCond.stateVarValueZ3ExprMap.find(arrayName);

            if(itr != preCond.stateVarValueZ3ExprMap.end()) {
                preCond.stateVarValueZ3ExprMap.at(arrayName) = updatedArrayExpr;
            }
            else {
                assert(preCond.funcScope);
                std::string arrayFullName = arrayName + nameSeparator + preCond.funcScope->name();

                itr = preCond.localVarValueZ3ExprMap.find(arrayFullName);

                if(itr != preCond.localVarValueZ3ExprMap.end()){
                    preCond.localVarValueZ3ExprMap.at(arrayFullName) = updatedArrayExpr;
                }
                else {
                    assert(false);
                }
            }
        }
    }
    else if(MemberAccess const* memAccessExpr = dynamic_cast<MemberAccess const*>(exp)) {

        Expression const& Exp = memAccessExpr->expression();
        ASTString const& memnameExp = memAccessExpr->memberName();
        std::string const& memnameExpName = dynamic_cast<std::string const&>(memnameExp);
        if (memnameExpName.compare("length")==0){
            if(Identifier const* idExpr = dynamic_cast<Identifier const*>(&Exp)){
                std::string varFullName = getVarFullName(idExpr, preCond)+".length";
                if(debugMode) {
                    std::cerr<<"updating Length: "<<varFullName<<std::endl;
                }

                std::unordered_map<std::string, z3::expr>::const_iterator itr = preCond.stateVarValueZ3ExprMap.find(varFullName);

                if(itr != preCond.stateVarValueZ3ExprMap.end()) {
                    preCond.stateVarValueZ3ExprMap.at(varFullName) = rightExpr;
                }
                else {
                    //assert(preCond.funcScope);
                    //std::string varFullName = varName + nameSeparator + preCond.funcScope->name();
                    //std::string varFullName = getVarFullName(idExpr);

                    itr = preCond.localVarValueZ3ExprMap.find(varFullName);

                    if(itr != preCond.localVarValueZ3ExprMap.end()) {
                        preCond.localVarValueZ3ExprMap.at(varFullName) = rightExpr;
                    }
                    else {
                        assert(false);
                    }
                }
            }else{
                assert(false);
            }
            return;
        }
        if(debugMode) {
            std::cerr<<"updating MemberAccess: "<<std::endl;
        }

        TypePointer expType = Exp.annotation().type;

        CAST_POINTER(structType, StructType, expType);
        // std::shared_ptr<StructType const> structType = std::dynamic_pointer_cast<StructType const>(expType);

        std::string structName = structType->structDefinition().name();

        std::unordered_map<std::string, std::shared_ptr<StructInfo>>::iterator structItr = structsMap.find(structName);

        z3::expr motherExpr = solExprTranslator->translate(&Exp, preCond);

        if(structItr != structsMap.end()){
            int fieldIndex = structItr->second->getProjIndex(memnameExpName);
            //std::cerr<<"fieldIndex: "<<fieldIndex<<std::endl;

            assert(fieldIndex != -1);

            //resultExpr = (((structItr->second->projectors[0])[fieldIndex])(motherExpr));

            z3::expr_vector resultVec(z3_ctx);

            for(int i = 0; i < (int)structItr->second->fieldNames.size(); i++) {
                if(i == fieldIndex) {
                    resultVec.push_back(rightExpr);
                }
                else {
                    if(IndexAccess const* idAccess = dynamic_cast<IndexAccess const*>(&Exp)) {
                        std::vector<z3::func_decl_vector> projectors = structItr->second->projectors;
                        z3::expr fieldExpr = projectors[0][i](motherExpr);
                        resultVec.push_back(fieldExpr);
                        std::ignore = idAccess;
                    }
                    else {
                        try{
                            assert(motherExpr.is_app());
                            z3::expr fieldExpr = motherExpr.arg(i);
                            resultVec.push_back(fieldExpr);

                            assert(motherExpr.num_args() == structItr->second->fieldNames.size());
                        }
                        catch(...) {
                            std::vector<z3::func_decl_vector> projectors = structItr->second->projectors;
                            z3::expr fieldExpr = projectors[0][i](motherExpr);
                            resultVec.push_back(fieldExpr);
                        }
                    }


                    /* if(Identifier const* ExpId = dynamic_cast<Identifier const*>(&Exp)) {
                        try{
                            assert(motherExpr.is_app());
                            z3::expr fieldExpr = motherExpr.arg(i);
                            resultVec.push_back(fieldExpr);

                            assert(motherExpr.num_args() == structItr->second->fieldNames.size());
                        }
                        catch(...) {
                            std::vector<z3::func_decl_vector> projectors = structItr->second->projectors;
                            z3::expr fieldExpr = projectors[0][i](motherExpr);
                            resultVec.push_back(fieldExpr);
                        }
                    }
                    else {
                        std::vector<z3::func_decl_vector> projectors = structItr->second->projectors;
                        z3::expr fieldExpr = projectors[0][i](motherExpr);
                        resultVec.push_back(fieldExpr);
                    } */
                }
            }

            z3::func_decl structConstructor = structItr->second->structConstructor[0];

            assert(structConstructor.to_string() != "null");

            z3::expr updatedStruct = structConstructor(resultVec);

            if(debugMode) {
                std::cerr<<"updatedStruct: "<<updatedStruct<<std::endl;
            }

            updateContextInfo(&Exp, updatedStruct, preCond);
        }
        else{
            std::cerr<<"Undefined struct ["<<structName<<"]"<<std::endl;
            assert(false);
        }


    }
    else {
        std::cerr<<"The LHS of this Assignment is not supported currentyly."<<std::endl;
        assert(false);
    }

    if(debugMode) {
        std::cerr<<"after updating ContextInfo: "<<std::endl;
        preCond.printContext();
    }
}

bool SymExecEngine::
checkValidity(z3::expr property, ContextInfo& ctxInfo) {
    bool result = true;
    z3::expr negProperty = !(property);

    z3::solver s(z3_ctx);

    s.add(negProperty);

   

    std::vector<z3::expr> pathCondVec = ctxInfo.pathCondition;

    for(unsigned j = 0; j < pathCondVec.size(); j++) {
        s.add(pathCondVec[j]);
    }
    
    switch (s.check()) {
        case z3::unsat: {
            break;
        }
        case z3::sat: {
            return false;
        }
        case z3::unknown: {
            std::cerr<<"Z3 cannot solve the formula!"<<std::endl;
            assert(false);
            break;
        }
    }
    // std::cout<< "Validation SMT:\n"<<s.to_smt2()<<std::endl;
    return result;
}

bool SymExecEngine::
checkSatisfiability(z3::expr property, ContextInfo& ctxInfo) {
    if (!checkCondPass(ctxInfo))
        return false;
    bool result = false;

    z3::solver s(z3_ctx);

    s.add(property);

    std::vector<z3::expr> pathCondVec = ctxInfo.pathCondition;

    for(unsigned j = 0; j < pathCondVec.size(); j++) {
        s.add(pathCondVec[j]);
    }

    switch (s.check()) {
        case z3::unsat: {
            break;
        }
        case z3::sat: {
            return true;
        }
        case z3::unknown: {
            std::cerr<<"Z3 cannot solve the formula!"<<std::endl;
            assert(false);
            break;
        }
    }
    // std::cout<< "Satification SMT:\n"<<s.to_smt2()<<std::endl;
    return result;
}

std::string SymExecEngine::
getVarFullName(dev::solidity::Identifier const* idExp, ContextInfo& ctxInfo) {
    std::string fullName;

    std::string varName = idExp->name();
    IdentifierAnnotation& idInfo = idExp->annotation();
    Declaration const* dec = idInfo.referencedDeclaration;

    assert(dec);

    fullName.append(varName);
    fullName.append(SymExecEngine::nameSeparator);
    fullName.append(std::to_string(dec->id()));

    FunctionDefinition const* funcScope = ctxInfo.funcScope;

    if(funcScope) {
        std::string funcName = funcScope->name();

        try{
            int callDepth = ctxInfo.funcCallDepthMap.at(funcName);
            assert(callDepth >= 0);

            if(callDepth > 1) {
                fullName.append(SymExecEngine::scopeSpecifier);
                fullName.append(std::to_string(callDepth));
            }
        }
        catch(...) {
            std::cerr<<"This should not happend!"<<std::endl;
            assert(false);
        }
    }

    if(debugMode) {
        std::cerr<<"variable ["<<varName<<"], fullName: "<<fullName<<std::endl;
    }

    return fullName;
}

std::string SymExecEngine::
getVarFullName(dev::solidity::VariableDeclaration const* varDec, ContextInfo& ctxInfo) {
    std::string fullName;

    std::string varName = varDec->name();

    fullName.append(varName);
    fullName.append(SymExecEngine::nameSeparator);
    fullName.append(std::to_string(varDec->id()));

    FunctionDefinition const* funcScope = ctxInfo.funcScope;

    if(funcScope){
        std::string funcName = funcScope->name();

        try{
            int callDepth = ctxInfo.funcCallDepthMap.at(funcName);
            assert(callDepth >= 0);

            if(callDepth > 1) {
                fullName.append(SymExecEngine::scopeSpecifier);
                fullName.append(std::to_string(callDepth));
            }
        }
        catch(...) {
            std::cerr<<"This should not happend!"<<std::endl;
            assert(false);
        }
    }

    if(debugMode) {
        std::cerr<<"variable ["<<varName<<"], fullName: "<<fullName<<std::endl;
    }

    return fullName;
}

std::string SymExecEngine::
getRealFuncCallName(Expression const* funcCall) {
    if(Identifier const* id = dynamic_cast<Identifier const*>(funcCall)) {
        return id->name();
    }
    else if(MemberAccess const* funExpId = dynamic_cast<MemberAccess const*>(funcCall)) {
        std::string memberFuncName = dynamic_cast<std::string const&>(funExpId->memberName());

        if(memberFuncName.compare("gas") == 0 || memberFuncName.compare("value") == 0) {
            Expression const& motherExpr = funExpId->expression();

            return getRealFuncCallName(&motherExpr);
        }
        else {
            return memberFuncName;
        }
    }
    else if(FunctionCall const* childCall = dynamic_cast<FunctionCall const*>(funcCall)) {
        return getRealFuncCallName(&childCall->expression());
    }
    else {
        std::cerr<<"Cannot get the real name of a function call."<<std::endl;
        assert(false);
    }
}
