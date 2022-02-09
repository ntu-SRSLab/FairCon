#include <iostream>
#include<fstream>
#include <string>
#include <memory>
#include <boost/filesystem.hpp>

#include <libsolidity/interface/CompilerStack.h>
#include <json/json.h>
#include "SymExecEngine.h"
#if defined(SOLC_0_6_10) || defined(SOLC_0_7_6)  || defined(SOLC_0_8_11)
using namespace solidity::frontend;
using namespace solidity::util;
#else 
using namespace dev;
using namespace solidity;
#endif 

using namespace std;


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
    #if defined(SOLC_0_6_0) || defined(SOLC_0_6_10) || defined(SOLC_0_7_6)  || defined(SOLC_0_8_11)
    ReadCallback::Callback fileReader = [](string const& _kind, string const& _path){
    #else 
    ReadCallback::Callback fileReader = [](string const& _path){
    #endif 
    // ReadCallback::Callback fileReader = [](string const& _kind, string const& _path)
	// {
		try
		{
            #if defined(SOLC_0_6_0) 
			if (_kind != ReadCallback::kindString(ReadCallback::Kind::ReadFile))
				BOOST_THROW_EXCEPTION(langutil::InternalCompilerError() << errinfo_comment(
					"ReadFile callback used as callback kind " +
					_kind
				));
            #endif 

            #if defined(SOLC_0_6_10) || defined(SOLC_0_7_6) || defined(SOLC_0_8_11)
			if (_kind != ReadCallback::kindString(ReadCallback::Kind::ReadFile))
				BOOST_THROW_EXCEPTION(solidity::langutil::InternalCompilerError() << errinfo_comment(
					"ReadFile callback used as callback kind " +
					_kind
				));
            #endif 

			auto path = boost::filesystem::path(_path);
			auto canonicalPath = boost::filesystem::weakly_canonical(path);
		
		
			if (!boost::filesystem::exists(canonicalPath))
				return ReadCallback::Result{false, "File not found."};

			if (!boost::filesystem::is_regular_file(canonicalPath))
				return ReadCallback::Result{false, "Not a valid file."};

			auto contents = readFileAsString(canonicalPath.string());
			return ReadCallback::Result{true, contents};
		}
		catch (Exception const& _exception)
		{
			return ReadCallback::Result{false, "Exception in read callback: " + boost::diagnostic_information(_exception)};
		}
		catch (...)
		{
			return ReadCallback::Result{false, "Unknown exception in read callback."};
		}
	};


    
    #ifdef SOLC_0_5_0
    CompilerStack compilerStack(fileReader);
    ReadCallback::Result readResult = readInputFile(arg2);
    if(!readResult.success){
        std::cerr<<readResult.responseOrErrorMessage<<std::endl;
        return -1;
    }
    compilerStack.addSource(arg2, readResult.responseOrErrorMessage);
    #endif

    #if defined(SOLC_0_5_10) || defined(SOLC_0_5_17) || defined(SOLC_0_6_0) || defined(SOLC_0_6_10) || defined(SOLC_0_7_6) || defined(SOLC_0_8_11)
    CompilerStack compilerStack(fileReader);
    auto infile = boost::filesystem::path(arg2);
   	std::map<std::string, std::string> sources;
    sources[infile.generic_string()] = readFileAsString(infile.string());
    compilerStack.setSources(sources);
    #endif

    bool successful = compilerStack.parseAndAnalyze();

    if(!successful){
        std::cerr<<"parsing error!!"<<std::endl;
        return -1;
    }

    SourceUnit const& srcUnit = compilerStack.ast(arg2);

    if(arg1.compare("-symexe") == 0){
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

