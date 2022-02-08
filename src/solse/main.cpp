#include <iostream>
#include<fstream>

#include <string>
#include <memory>

#include <libsolidity/interface/CompilerStack.h>
#include <json/json.h>
#include "SymExecEngine.h"
using namespace dev::solidity;
using namespace std;

ReadCallback::Result readInputFile(std::string const& _path);

void assignmentZ3Test();
void arrayZ3Test();
void arrayZ3Test2();
void arrayZ3Test3();
void arrayUpdateZ3Test();
void arrayUpdateZ3Test2();
void stringZ3Test();
void tupleZ3Test();
void functionAppTest();

int main(int argc, char **argv){
    if(argc != 3){
        std::cerr<<"The number of arguments is wrong!"<<std::endl;
        std::cerr<<"The command should be: sees [-opt] file"<<std::endl;
        return -1;
    }

    std::string arg0(argv[0]);
    std::string arg1(argv[1]);
    std::string arg2(argv[2]);

    //size_t index = arg0.rfind("ssee");
    //cout<<"index: "<<index<<endl;
    //std::string filePrefix = arg0.substr(0, index);

    std::ifstream inputFile(arg2);

    if(!inputFile){
        std::cerr<<"Error: unable to open the input file: "<<arg2<<std::endl;
        return -1;
    }
    ostringstream ss;
    ss<<inputFile.rdbuf();
    std::string source=ss.str();

   
    CompilerStack compilerStack(readInputFile);
    
    #ifdef SOLC_0_5_0
    ReadCallback::Result readResult = readInputFile(arg2);
    if(!readResult.success){
        std::cerr<<readResult.responseOrErrorMessage<<std::endl;
        return -1;
    }
    compilerStack.addSource(arg2, readResult.responseOrErrorMessage);
    #endif

    #if defined(SOLC_0_5_10) || defined(SOLC_0_5_17)
    auto infile = boost::filesystem::path(arg2);
   	std::map<std::string, std::string> sources;
    sources[infile.generic_string()] = dev::readFileAsString(infile.string());
    compilerStack.setSources(sources);
    #endif

    bool successful = compilerStack.parseAndAnalyze();

    if(!successful){
        std::cerr<<"parsing error!!"<<std::endl;

        // unique_ptr<SourceReferenceFormatter> formatter;

        // #ifdef SOLC_0_5_0
		// auto scannerFromSourceName = [&](string const& _sourceName) -> dev::solidity::Scanner const& { return compilerStack.scanner(_sourceName); };
		// formatter = make_unique<SourceReferenceFormatter>(cerr, scannerFromSourceName);
		// #else 
		// formatter = make_unique<SourceReferenceFormatterHuman>(cerr, true);
		// #endif 

        // for (auto const& error: compilerStack.errors()) {

		// 	formatter->printExceptionInformation(
		// 		*error,
		// 		(error->type() == Error::Type::Warning) ? "Warning" : "Error"
		// 	);
		// }

        return -1;
    }

    SourceUnit const& srcUnit = compilerStack.ast(arg2);

    if(arg1.compare("-test") == 0){
        stringZ3Test();
        tupleZ3Test();
        arrayZ3Test();
        arrayUpdateZ3Test();
        arrayUpdateZ3Test2();
        assignmentZ3Test();
        arrayZ3Test2();
        functionAppTest();
    }
    else if(arg1.compare("-symexe") == 0){
        SymExecEngine symExecEngine(source, srcUnit, false, false, *Mechanism::p_z3_ctx);

        symExecEngine.symbolicExecution();

        //z3::expr result = exprTranslator.translate(srcUnit);
    }
    else if(arg1.compare("-symexe-dbg") == 0){
        SymExecEngine symExecEngine(source, srcUnit, true, false, *Mechanism::p_z3_ctx);

        symExecEngine.symbolicExecution();

        //z3::expr result = exprTranslator.translate(srcUnit);
    }
    else if(arg1.compare("-symexe-main") == 0){
        SymExecEngine symExecEngine(source, srcUnit, false, true, *Mechanism::p_z3_ctx);

        symExecEngine.symbolicExecution();

        //z3::expr result = exprTranslator.translate(srcUnit);
    }
    else if(arg1.compare("-symexe-main-dbg") == 0){
        SymExecEngine symExecEngine(source, srcUnit, true, true,*Mechanism::p_z3_ctx);

        symExecEngine.symbolicExecution();

        //z3::expr result = exprTranslator.translate(srcUnit);
    }
    else{
        std::cerr<<"the option is wrong!"<<std::endl;
        std::cerr<<"It should be: "<<std::endl;
        std::cerr<<"\t-ast: print the abstract syntax tree (ast)"<<std::endl;
        return -1;
    }

}


ReadCallback::Result readInputFile(std::string const& _path){
    //std::cout<<"readInputFile() is called!"<<std::endl;
    try {
        auto path = boost::filesystem::path(_path);

        auto canonicalPath = boost::filesystem::canonical(path);

        if (!boost::filesystem::exists(path)){
            return ReadCallback::Result{false, "File not found."};
        }
        else if (!boost::filesystem::is_regular_file(canonicalPath)){
            return ReadCallback::Result{false, "Not a valid file."};
        }
        else {
            auto contents = dev::readFileAsString(canonicalPath.string());
            //m_sourceCodes[path.string()] = contents;
            //std::cout<<"ccccc"<<std::endl;
            return ReadCallback::Result{true, contents};
        }
    }
    #ifdef SOLC_0_5_0 
    catch (dev::Exception const& _exception) {
    #else 
    catch (dev::Exception const& _exception) {
    #endif 
        // return ReadCallback::Result{false, "Exception in read callback: " + boost::diagnostic_information(_exception)};
        return ReadCallback::Result{false, "Exception in read callback: "};
    }
    catch (boost::filesystem::filesystem_error& e) {
        return ReadCallback::Result{false, "cannot open the file."};
    }
}

void assignmentZ3Test(){

    // ******************************
    // We want to calculate the symbolic states after the following
    // program is executed.
    /*
    int x;
    int y;

    x = x + y;

    if(x < n){
        x = x + 3;
        y = y + 1;
    }
    else{
        x = 2 * x;
        y = y - 1;
    }
    */
    //*********************************

    std::cout<<"==============================="<<std::endl;
    std::cout<<"assignmentZ3Test()"<<std::endl;

    z3::context ctx;

    z3::expr x = ctx.int_const("x");    // variable x
    z3::expr y = ctx.int_const("y");    // variable y
    z3::expr n = ctx.int_const("n");    // variable n

    z3::expr x0 = ctx.int_const("x0");  // initial symbolic value for x
    z3::expr y0 = ctx.int_const("y0");  // initial symbolic value for y

    struct ContextInfo {
        std::unordered_map<std::string, z3::expr> varsMap;
        std::vector<z3::expr> pathCondition;
    };

    z3::expr x_ = ctx.int_const("x_");
    z3::expr y_ = ctx.int_const("y_");

    x_ = x0;
    y_ = y0;

    ContextInfo ctxCurrent;     // ContextInfo before the If-Else
    ContextInfo ctxAfter1;      // ContextInfo after the If branch
    ContextInfo ctxAfter2;      // ContextInfo after the Else branch

    x_ = x_ + y_;      // x := x + y

    ctxCurrent.varsMap.emplace("x", x_);
    ctxCurrent.varsMap.emplace("y", y_);

    std::cout<<"x: "<<ctxCurrent.varsMap.at("x")<<std::endl;
    std::cout<<"y: "<<ctxCurrent.varsMap.at("y")<<std::endl;

    z3::expr xt = ctxCurrent.varsMap.at("x");
    z3::expr yt = ctxCurrent.varsMap.at("y");

    z3::expr cond = (xt < n);
    ctxAfter1.pathCondition.push_back(cond);

    xt = xt + 3;
    yt = yt + 1;
    ctxAfter1.varsMap.emplace("x", xt);
    ctxAfter1.varsMap.emplace("y", yt);

    z3::expr xf = ctxCurrent.varsMap.at("x");
    z3::expr yf = ctxCurrent.varsMap.at("y");

    z3::expr negCond = (! cond);
    ctxAfter2.pathCondition.push_back(negCond);

    xf = 2 * xf;
    yf = yf -1;

    ctxAfter2.varsMap.emplace("x", xf);
    ctxAfter2.varsMap.emplace("y", yf);

    std::cout<<"xt: "<<ctxAfter1.varsMap.at("x")<<std::endl;
    std::cout<<"yt: "<<ctxAfter1.varsMap.at("y")<<std::endl;
    std::cout<<"TRUE path condition: "<<ctxAfter1.pathCondition[0]<<std::endl;

    std::cout<<"xf: "<<ctxAfter2.varsMap.at("x")<<std::endl;
    std::cout<<"yf: "<<ctxAfter2.varsMap.at("y")<<std::endl;
    std::cout<<"FALSE path condition: "<<ctxAfter2.pathCondition[0]<<std::endl;

    z3::expr condition1 = (x == ctxAfter1.varsMap.at("x"));
    z3::expr condition2 = (y == ctxAfter1.varsMap.at("y"));
    z3::expr condition3 = (x0 == ctx.int_val("1"));
    z3::expr condition4 = (y0 == ctx.int_val("1"));

    //z3::expr property = (x < y);
    z3::expr property = (ctxAfter1.varsMap.at("x") < ctxAfter1.varsMap.at("y"));

    z3::solver s(ctx);

    //s.add(condition1);
    //s.add(condition2);
    s.add(condition3);
    s.add(condition4);
    //s.add(ctxAfter1.pathCondition[0]);
    s.add(property);

    std::cout << s << "\n";

    switch (s.check()) {
        case z3::unsat:   std::cout << "unsat"<<std::endl; break;
        case z3::sat:     std::cout << "sat"<<std::endl; break;
        case z3::unknown: std::cout << "unknown\n"; break;
    }

    z3::expr k = ctx.int_const("k");
    std::cerr<<"k: "<<k<<std::endl;
    k = k + 1;
    std::cerr<<"k: "<<k<<std::endl;


    std::cout<<"==============================="<<std::endl;
}

z3::expr qeZ3(z3::context &c, z3::expr_vector qeVec, z3::expr formula, bool forAll);

void arrayZ3Test2(){
    std::cout<<"==============================="<<std::endl;
    std::cout<<"arrayZ3Test()"<<std::endl;

    z3::context c;
    z3::sort arr_sort = c.array_sort(c.int_sort(), c.int_sort());   // sort (type) of 1-D array
    z3::sort arr_sort2 = c.array_sort(c.int_sort(), arr_sort);      // sort (type) of 2-D array
    z3::expr some_array_1 = c.constant("some_array_1", arr_sort);   // some_array_1 is a 1-D array
    z3::expr some_array_1_init = c.constant("some_array_1_init", arr_sort);   // some_array_1 is a 1-D array
    z3::expr some_array_2 = c.constant("some_array_2", arr_sort);   // some_array_2 is a 2-D array
    z3::expr array2D = c.constant("array2D", arr_sort2);            // array2D is a 2-D array

    some_array_1 = some_array_1_init;
    std::cout<<"some_array_1: "<<some_array_1<<std::endl;

    some_array_1 = store(some_array_1, 0, 0);      //some_array_1[0] == 0

    std::cout<<"some_array_1: "<<some_array_1<<std::endl;

    // some_array_1[0] = some_array_1[0] + 1
    some_array_1 = store(some_array_1, 0, select(some_array_1, 0) + 1);

    std::cout<<"some_array_1: "<<some_array_1<<std::endl;

    z3::sort arr_sort_string2Int = c.array_sort(c.string_sort(), c.int_sort());
    z3::expr str2Int_array = c.constant("str2Int_array", arr_sort_string2Int);

    //z3::sort stringSort = c.string_sort();
    //z3::expr str1 = c.constant("str1", stringSort);
    z3::expr strVal1 = c.string_val("Index1");
    str2Int_array = store(str2Int_array, strVal1, 1);

    std::cout<<"strVal1: "<<strVal1<<std::endl;
    std::cout<<"str2Int_array: "<<str2Int_array<<std::endl;

    z3::solver s(c);

    s.add(select(some_array_1, 0) < 0);

    std::cout << s << "\n";

    switch (s.check()) {
        case z3::unsat:   std::cout << "unsat"<<std::endl; break;
        case z3::sat:     std::cout << "sat"<<std::endl; break;
        case z3::unknown: std::cout << "unknown\n"; break;
    }

    std::cout<<"==============================="<<std::endl;
}

void arrayZ3Test3() {
    z3::context c;
    z3::sort arr_sort = c.array_sort(c.int_sort(), c.int_sort());   // sort (type) of 1-D array
    z3::sort arr_sort2 = c.array_sort(c.int_sort(), arr_sort);      // sort (type) of 2-D array

    z3::expr array2D = c.constant("array2D", arr_sort2);
}

void arrayZ3Test() {
    std::cout<<"==============================="<<std::endl;
    std::cout<<"arrayZ3Test()"<<std::endl;

    z3::context c;
    z3::sort arr_sort = c.array_sort(c.int_sort(), c.int_sort());   // sort (type) of 1-D array
    z3::sort arr_sort2 = c.array_sort(c.int_sort(), arr_sort);      // sort (type) of 2-D array
    z3::expr some_array_1 = c.constant("some_array_1", arr_sort);   // some_array_1 is a 1-D array
    z3::expr some_array_2 = c.constant("some_array_2", arr_sort);   // some_array_2 is a 2-D array
    z3::expr array2D = c.constant("array2D", arr_sort2);            // array2D is a 2-D array

    z3::expr formu1 = (select(some_array_1, 0) == 0);      //some_array_1[0] == 0
    z3::expr pivot = c.int_const("p");

    z3::expr_vector exprVecSource(c);
    z3::expr_vector exprDestination(c);

    exprVecSource.push_back(select(some_array_1, 0));
    exprDestination.push_back(pivot);

    z3::expr newFormula = formu1.substitute(exprVecSource, exprDestination);

    std::cout<<"after substitute: "<<newFormula<<std::endl;

    z3::expr formu2 = (select(some_array_1, 0) == (pivot + 1));
    formu2 = (newFormula && formu2);

    formu2 = z3::exists(exprDestination, formu2);

    std::cout<<"before qe: "<<formu2<<std::endl;

    z3::goal g(c);
    g.add(formu2);
    z3::tactic qe(c,"qe");

    z3::apply_result result = qe.apply(g);

    if(result.size() == 1){
        z3::goal gg = result[0];
        z3::expr rr = gg.as_expr();

        std::cout<<"after qe: "<<rr<<std::endl;
    }
    else{
        std::cerr<<"This should not happen!"<<std::endl;
        assert(false);
    }

    z3::solver s(c);

    s.add(formu1);    // some_array_1[0] == 0
    s.add(select(some_array_2, 5) == -4);   // some_array_2[5] == -4
    s.add(some_array_1 == some_array_2);
    s.add(select(select(array2D, 0), 0) == 1);  // array2D[0][0] == 1
    std::cout << s.check() << "\n";

    z3::model m = s.get_model();
    std::cout << m << "\n";

    z3::expr v = c.constant("v", arr_sort);
    z3::expr v0 = c.constant("v0", arr_sort);
    z3::expr t = c.constant("t", arr_sort);

    z3::expr stmt1 = (v == v0);
    z3::expr stmt2 = (select(v,1) + 1);

//    v = store(v,0,6);
//    v = store(v,0, (select(v,0) + 1));
//
//    std::cout<<"lala:: "<<v<<std::endl;
//
//    z3::solver ccChecker(c);
//    ccChecker.add(t == v);
//    ccChecker.check();
//    std::cout<<"result: "<<ccChecker.get_model()<<std::endl;

    z3::expr_vector srcVec(c);
    z3::expr_vector desVec(c);

    srcVec.push_back(v);
    desVec.push_back(t);

    z3::expr stmt1_ = stmt1.substitute(srcVec, desVec);
    z3::expr stmt2_ = stmt2.substitute(srcVec, desVec);

    z3::expr conjExpr = ((stmt1_) && (select(v, 1) == stmt2_));

    std::cout<<"conjExpr: "<<conjExpr<<std::endl;

    z3::expr fExpr = exists(desVec, conjExpr);

    std::cout<<"fExpr: "<<fExpr<<std::endl;

    z3::goal g1(c);
    g1.add(fExpr);

    z3::apply_result result_ = qe.apply(g1);

    if(result_.size() == 1){
        z3::goal gg = result_[0];
        z3::expr rr = gg.as_expr();

        std::cout<<"after qe: "<<rr<<std::endl;
    }
    else{
        std::cerr<<"This should not happen!"<<std::endl;
        assert(false);
    }

    std::cout<<"==============================="<<std::endl;
}

void arrayUpdateZ3Test(){
    std::cout<<"==============================="<<std::endl;
    std::cout<<"arrayUpdateZ3Test()"<<std::endl;

    z3::context c;
    z3::sort array_sort = c.array_sort(c.int_sort(), c.int_sort());

    z3::expr v = c.constant("v", array_sort);
    z3::expr v0 = c.constant("v0", array_sort);
    z3::expr v_ = c.constant("v_", array_sort);

    z3::expr x = c.int_const("x");
    z3::expr x0 = c.int_const("x0");
    z3::expr x_ = c.int_const("x_");

    x = x0;
    v = v0;

    v = store(v, 0, x + 2);
    std::cout<<"v: "<<v<<std::endl;

    z3::expr stmtV1 = (v_ == v);
    z3::expr stmtX1 = (x_ == x);
    std::cout<<"stmtV1: "<<stmtV1<<std::endl;
    std::cout<<"stmtX1: "<<stmtX1<<std::endl;

    z3::expr cond1 = (stmtV1 && stmtX1);

    x = x + 1;
    std::cout<<"x: "<<x<<std::endl;


    z3::expr stmtV2 = (v_ == v);
    z3::expr stmtX2 = (x_ == x);
    std::cout<<"stmtV2: "<<stmtV2<<std::endl;
    std::cout<<"stmtX2: "<<stmtX2<<std::endl;

    z3::expr cond2 = (stmtV2 && stmtX2);

    v = store(v, 0, select(v, 0) + x);

    std::cout<<"v: "<<v<<std::endl;

    z3::expr stmtV3 = (v_ == v);
    z3::expr stmtX3 = (x_ == x);
    std::cout<<"stmtV3: "<<stmtV3<<std::endl;
    std::cout<<"stmtX3: "<<stmtX3<<std::endl;

    z3::expr cond3 = (stmtV3 && stmtX3);

    z3::expr prop = (x == x0 + 1);

    //z3::expr testExpr = (select(v,0) == 8);

    z3::solver s(c);
    //s.add(cond1);
    //s.add(cond2);
    s.add(cond1 && !(prop));
    std::cout<<"result: "<<s.check()<<std::endl;
    //std::cout<<"model: "<<s.get_model()<<std::endl;



//    z3::expr stmt1_ = exists(desVec, stmt1);
//
//    std::cout<<"before qe: "<<stmt1_<<std::endl;
//
//    z3::goal g(c);
//    z3::tactic qe(c,"qe");
//    g.add(stmt1_);
//
//
//    z3::apply_result result_ = qe.apply(g);
//
//    z3::expr resultExpr(c);
//
//    if(result_.size() == 1){
//        z3::goal gg = result_[0];
//        z3::expr rr = gg.as_expr();
//
//        std::cout<<"after qe: "<<rr<<std::endl;
//
//        resultExpr = rr;
//    }
//    else{
//        std::cerr<<"This should not happen!"<<std::endl;
//        assert(false);
//    }
//
//    z3::solver s(c);
//    s.add(resultExpr);
//    s.check();
//
//    std::cout<<"model: "<<s.get_model()<<std::endl;

    std::cout<<"==============================="<<std::endl;
}

void arrayUpdateZ3Test2(){
    std::cout<<"==============================="<<std::endl;
    std::cout<<"arrayUpdateZ3Test2()"<<std::endl;

    z3::context c;
    z3::sort array_sort = c.array_sort(c.int_sort(), c.int_sort());

    z3::expr v = c.constant("v", array_sort);
    z3::expr v0 = c.constant("v0", array_sort);
    z3::expr v_ = c.constant("v_", array_sort);

    z3::expr x = c.int_const("x");
    z3::expr x0 = c.int_const("x0");
    z3::expr x_ = c.int_const("x_");

    z3::expr_vector srcVec(c);
    z3::expr_vector desVec(c);

    srcVec.push_back(v);


    desVec.push_back(v_);

    z3::expr initExpr = (v == v0) && (x == x0);

    /*** v[0] = x; ***/
    z3::expr initExpr_ = initExpr.substitute(srcVec, desVec);
    z3::expr assg1 = store(v, 0, x);
    z3::expr assg1_ = assg1.substitute(srcVec, desVec);
    z3::expr stmt1 = (v == assg1_);
    z3::expr conj1 = stmt1 && initExpr_;

    z3::expr postCond1 = qeZ3(c, desVec, conj1, false);
    std::cout<<"postCond1: "<<postCond1<<std::endl;

    z3::expr_vector srcVec1(c);
    z3::expr_vector desVec1(c);

    srcVec1.push_back(x);
    desVec1.push_back(x_);

    /****** x = x + x; *********/
    z3::expr postCond1_ = postCond1.substitute(srcVec1, desVec1);
    z3::expr assg2 = (x + x);
    z3::expr assg2_ = assg2.substitute(srcVec1, desVec1);
    z3::expr stmt2 = (x == assg2_);

    z3::expr conj2 = stmt2 && postCond1_;
    z3::expr postCond2 = qeZ3(c, desVec1, conj2, false);
    std::cout<<"postCond2: "<<postCond2<<std::endl;

    /***** v[0] = v[0] + x *****/
    z3::expr postCond2_ = postCond2.substitute(srcVec, desVec);
    z3::expr assg3 = store(v, 0, select(v, 0) + x);
    z3::expr assg3_ = assg3.substitute(srcVec, desVec);
    z3::expr stmt3 = (v == assg3_);
    z3::expr conj3 = stmt3 && postCond2_;

    z3::expr postCond3 = qeZ3(c, desVec, conj3, false);
    std::cout<<"postCond3: "<<postCond3<<std::endl;

    /**** x = x + 3 ****/
    z3::expr postCond3_ = postCond3.substitute(srcVec1, desVec1);
    z3::expr assg4 = (x + 3);
    z3::expr assg4_ = assg4.substitute(srcVec1, desVec1);
    z3::expr stmt4 = (x == assg4_);

    z3::expr conj4 = stmt4 && postCond3_;
    z3::expr postCond4 = qeZ3(c, desVec1, conj4, false);
    std::cout<<"postCond4: "<<postCond4<<std::endl;

    std::cout<<"==============================="<<std::endl;
}

void stringZ3Test(){
    std::cout<<"==============================="<<std::endl;
    std::cout<<"stringZ3Test()"<<std::endl;

    z3::context c;

    z3::sort stringSort = c.string_sort();
    z3::expr str1 = c.constant("str1", stringSort);
    z3::expr strVal1 = c.string_val("This is the content of str1");
    z3::expr formula1 = (str1 == strVal1);

    std::cout<<"formula1: "<<formula1<<std::endl;

    std::cout<<"==============================="<<std::endl;
}


void tupleZ3Test() {
    std::cout<<"==============================="<<std::endl;
    std::cout<<"tupleZ3Test()"<<std::endl;

    z3::context ctx;
    const char * names[] = { "first", "second" };
    z3::sort sorts[2] = { ctx.int_sort(), ctx.bool_sort() };
    z3::func_decl_vector projs(ctx);
    z3::func_decl pair = ctx.tuple_sort("pair", 2, names, sorts, projs);
    sorts[1] = pair.range();
    z3::func_decl pair2 = ctx.tuple_sort("pair2", 2, names, sorts, projs);

    std::cout<< "pair.range: "<<pair.range()<<std::endl;
    std::cout<< "pair.domain(0): "<<pair.domain(0)<<", pair.domain(1): "<<pair.domain(1)<<std::endl;

    std::cout<< pair <<std::endl;
    std::cout << pair2 <<std::endl<<std::endl;

    z3::expr tupleExpr = ctx.constant("aPair", pair.range());
    std::cout<<"aPair: "<<tupleExpr<<std::endl;

    z3::expr a1 = projs[0](tupleExpr);

    std::cout<<"a1: "<<a1<<std::endl;

    z3::expr t1 = (a1 == 1);

    std::cout<<"t1: "<<t1<<std::endl;

    std::vector<const char*> nameVec;
    std::string name1 = "field1";
    std::string name2 = "field2";
    std::string name3 = "field3";

    nameVec.push_back(name1.c_str());
    nameVec.push_back(name2.c_str());
    nameVec.push_back(name3.c_str());

    //char const* const* nameArray = nameVec.data();

    std::vector<z3::sort> sortVec;
    sortVec.push_back(ctx.int_sort());
    sortVec.push_back(ctx.bool_sort());
    sortVec.push_back(ctx.string_sort());

    //z3::sort* sortArray = sortVec.data();

    z3::func_decl_vector getElement(ctx);

    z3::func_decl threeD = ctx.tuple_sort("3D", nameVec.size(), nameVec.data(), sortVec.data(), getElement);

    z3::sort threeDSort = threeD.range();

    z3::expr field1 = ctx.int_const("fieldOne");
    field1 = ctx.int_val("10");

    z3::expr f0 = ctx.int_const("init_1");
    z3::expr f1 = ctx.bool_const("init_2");
    z3::expr f2 = ctx.constant("init_3", ctx.string_sort());

    z3::expr_vector values(ctx);
    values.push_back(f0);
    values.push_back(f1);
    values.push_back(f2);

    z3::expr pointX = ctx.constant("pointX", threeDSort);
    pointX = threeD(values);
    std::cerr<<"pointX: "<<pointX<<std::endl;

    f0 = ctx.int_val("50");

    std::cerr<<"pointX.field1: "<<pointX.arg(0)<<std::endl;
    std::cerr<<"pointX.field2: "<<pointX.arg(1)<<std::endl;
    std::cerr<<"pointX.field3: "<<pointX.arg(2)<<std::endl;

    z3::expr_vector values2(ctx);
    values2.push_back(f0);
    values2.push_back(f1);
    values2.push_back(f2);

    pointX = threeD(values2);
    std::cerr<<"pointX: "<<pointX<<std::endl;
    std::cerr<<"pointX.field1: "<<pointX.arg(0)<<std::endl;

    std::cerr<<"pointX.field1: "<<getElement[0](pointX)<<std::endl;
    field1 = ctx.int_val("100");
    std::cout<<"pointX.field1: "<<getElement[0](pointX)<<std::endl;
    std::cout<<"field1: "<<field1<<std::endl;

    z3::expr point3 = ctx.constant("point3", threeDSort);
    point3 = pointX;
    std::cout<<"point3: "<<point3<<std::endl;

    z3::expr point1 = ctx.constant("point1", threeDSort);

    std::cout<<"point1: "<<point1<<std::endl;

    z3::expr cond1 = (getElement[0](point1) == ctx.int_val("10"));
    z3::expr cond2 = (getElement[1](point1) == ctx.bool_val(true));
    z3::expr cond3 = (getElement[2](point1) == ctx.string_val("Test"));

    std::cout<<"cond1: "<<cond1<<std::endl;
    std::cout<<"cond2: "<<cond2<<std::endl;
    std::cout<<"cond3: "<<cond3<<std::endl;

    z3::expr point2 = ctx.constant("point2", threeDSort);

    z3::expr x = ctx.int_const("x");
    x = ctx.int_val("20");

    getElement[0](point2) = ctx.int_val("20");
    getElement[1](point2) = ctx.bool_val(true);
    getElement[2](point2) = ctx.string_val("Testing");

    std::cout<<"point2.field1: "<<getElement[0](point2)<<std::endl;
    std::cout<<"point2.field2: "<<getElement[1](point2)<<std::endl;
    std::cout<<"point2.field3: "<<getElement[2](point2)<<std::endl;

    //z3::expr y = ctx.int_const("y");
    z3::expr y = getElement[0](point2);
    y = (getElement[0](point2) * x);

    std::cout<<"y: "<<y<<std::endl;
    std::cout<<"point2.field1: "<<getElement[0](point2)<<std::endl;

    z3::solver s(ctx);

    //z3::expr condition1 = (getElement[0](point2) > y);
    z3::expr condition1 = (getElement[0](point3) < 5);

    s.add(condition1);

    std::cout << s << "\n";

    switch (s.check()) {
        case z3::unsat:   std::cout << "unsat"<<std::endl; break;
        case z3::sat: {
            std::cout << "sat"<<std::endl;

            z3:: model m = s.get_model();
            std::cout << m << "\n";
            // traversing the model
            for (unsigned i = 0; i < m.size(); i++) {
                z3::func_decl v = m[i];
                // this problem contains only constants
                assert(v.arity() == 0);
                std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
            }

            break;
        }
        case z3::unknown: std::cout << "unknown\n"; break;
    }

    std::cout<<"==============================="<<std::endl;
}

void functionAppTest(){

    std::cout<<"==============================="<<std::endl;
    std::cout<<"functionAppTest()"<<std::endl;

    z3::context ctx;

    std::string funcName = "Foo";
    z3::sort_vector sortVec(ctx);

    sortVec.push_back(ctx.int_sort());
    sortVec.push_back(ctx.bool_sort());
    sortVec.push_back(ctx.string_sort());

    z3::sort RANGE = ctx.int_sort();

    z3::func_decl funcFoo = ctx.function(funcName.c_str(), sortVec, ctx.int_sort());

    z3::expr int_1 = ctx.int_const("int_1");
    z3::expr bool_2 = ctx.bool_const("bool_2");
    z3::expr string_3 = ctx.constant("string_3", ctx.string_sort());

    int_1 = ctx.int_val(10);
    bool_2 = ctx.bool_val(true);
    string_3 = ctx.string_val("abc");


    z3::expr result = funcFoo(int_1, bool_2, string_3);

    std::cerr<<"result: "<<result<<std::endl;

    int_1 = ctx.int_val("20");
    bool_2 = ctx.bool_val(false);
    string_3 = ctx.string_val("def");

    z3::expr result2 = funcFoo(int_1, bool_2, string_3);

    std::cerr<<"result2: "<<result2<<std::endl;

    result = result2;

    std::cerr<<"result: "<<result<<std::endl;

    result.arg(0) = ctx.int_val("50");
    std::cerr<<"result.int_1: "<<result.arg(0)<<std::endl;

    std::cerr<<"result: "<<result<<std::endl;

    std::cout<<"==============================="<<std::endl;

}

z3::expr qeZ3(z3::context &c, z3::expr_vector qeVec, z3::expr formula, bool forAll){
    z3::expr fExpr(c);

    if(forAll){
        fExpr = forall(qeVec, formula);
    }
    else{
        fExpr = exists(qeVec, formula);
    }

    std::cout<<"fExpr: "<<fExpr<<std::endl;

    z3::goal g(c);
    g.add(fExpr);
    z3::tactic qe(c,"qe");
    //z3::tactic soleq(c,"solve-eqs");
    //z3::tactic sim(c, "simplify");
    //z3::tactic proof(c, "proof");
    z3::tactic t = qe;

    z3::apply_result result = t.apply(g);

    if(result.size() == 1){
        z3::goal gg = result[0];
        z3::expr rr = gg.as_expr();

        std::cout<<"after qe: "<<rr<<std::endl;
        return rr;
    }
    else{
        std::cerr<<"This should not happen!"<<std::endl;
        assert(false);
    }
}


