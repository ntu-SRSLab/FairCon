#include <solse/SolidityExprTranslator.h>
#include <solse/SymExecEngine.h>

#include <unordered_map>

using namespace dev::solidity;
void ContextInfo::collectContext(std::unordered_map<std::string, std::vector<std::string>>& state_variable_records,
    std::unordered_map<std::string, std::vector<std::string>>& local_variable_records){

    std::unordered_map<std::string, z3::expr>::const_iterator itr;
    for(itr = stateVarValueZ3ExprMap.begin(); itr != stateVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        z3::expr varInitExpr = stateVarValueZ3ExprMap.at(varName);
        std::string value ;
        std::ostringstream ss;
        ss<<varInitExpr;
        value = ss.str();
        state_variable_records[varName].push_back(value);
    }

    for(itr = localVarValueZ3ExprMap.begin(); itr != localVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        z3::expr varInitExpr = localVarValueZ3ExprMap.at(varName);
        std::string value ;
        std::ostringstream ss;
        ss<<varInitExpr;
        value = ss.str();
        local_variable_records[varName].push_back(value);
    }
    if (debugMode){
        std::cout<<"==============================================================================="<<std::endl;
        std::cout<<"|"<<std::setw(75)<<"Path Condition"<<"|"<<std::endl;
        std::cout<<"==============================================================================="<<std::endl;
        std::cout<<"-------------------------------------------------------------------------------"<<std::endl;
        for(unsigned i = 0; i < pathCondition.size(); i++) {
            std::cout<<"|"<<std::setw(75)<<pathCondition[i]<<"|"<<std::endl;
        }
        std::cout<<"-------------------------------------------------------------------------------"<<std::endl;
    }
}

void ContextInfo::
printContext(){
    std::cout<<"+++++++++++++ printing context +++++++++++++++"<<std::endl;

    std::cout<<"\tstate variables: "<<std::endl;
    std::unordered_map<std::string, z3::expr>::const_iterator itr;
    for(itr = stateVarValueZ3ExprMap.begin(); itr != stateVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        std::cout<<"\t\t"<<"varName: "<<varName;
        z3::expr varInitExpr = stateVarValueZ3ExprMap.at(varName);
    
        std::cout<<", value: "<<varInitExpr;
        std::cout<<", sort: "<<varInitExpr.get_sort()<<std::endl;
    }

    std::cout<<"\tlocal variables: "<<std::endl;
    for(itr = localVarValueZ3ExprMap.begin(); itr != localVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        std::cout<<"\t\t"<<"varName: "<<varName;
        z3::expr varInitExpr = localVarValueZ3ExprMap.at(varName);
    
        std::cout<<", value: "<<varInitExpr;
        std::cout<<", sort: "<<varInitExpr.get_sort()<<std::endl;
    }

    std::cout<<"\tpath conditions: "<<std::endl;
    for(unsigned i = 0; i < pathCondition.size(); i++) {
        std::cout<<"\t\t"<<pathCondition[i]<<std::endl;
    
    }

    std::cout<<"\tgoHead: "<<goHead<<std::endl;
    std::cout<<"\tabnormalTerminationCode: "<<abnormalTerminationCode<<std::endl;

    for(auto itr = funcCallDepthMap.begin(); itr != funcCallDepthMap.end(); itr++) {
        std::cout<<"\tfunction ["<<itr->first<<"]'s call depth: "<<itr->second<<std::endl;
    }
  
    std::cout<<"++++++++++++ end of printing context +++++++++++++++"<<std::endl;
}


std::string ContextInfo::
toString() {
    std::stringstream ss;

    ss<<"state variables: "<<std::endl;
    std::unordered_map<std::string, z3::expr>::const_iterator itr;
    for(itr = stateVarValueZ3ExprMap.begin(); itr != stateVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        ss<<"\t"<<"varName: "<<varName;
        z3::expr varInitExpr = stateVarValueZ3ExprMap.at(varName);
        ss<<", value: "<<varInitExpr;
        ss<<", sort: "<<varInitExpr.get_sort()<<std::endl;
    }

    ss<<"local variables: "<<std::endl;
    for(itr = localVarValueZ3ExprMap.begin(); itr != localVarValueZ3ExprMap.end(); ++itr){
        std::string varName = itr->first;
        ss<<"\t"<<"varName: "<<varName;
        z3::expr varInitExpr = localVarValueZ3ExprMap.at(varName);
        ss<<", value: "<<varInitExpr;
        ss<<", sort: "<<varInitExpr.get_sort()<<std::endl;
    }

    ss<<"\tpath conditions: "<<std::endl;
    for(unsigned i = 0; i < pathCondition.size(); i++) {
        ss<<"\t"<<pathCondition[i]<<std::endl;
    }

    ss<<"\tgoHead: "<<goHead<<std::endl;
    ss<<"\tabnormalTerminationCode: "<<abnormalTerminationCode<<std::endl;

    return ss.str();
}

SolidityExprTranslator::
SolidityExprTranslator(z3::context& ctx, SymExecEngine* engine): z3_ctx(ctx){
    assert(engine);
    symExecEngine = engine;

    debugMode = false;
}

void SolidityExprTranslator::
setDebugMode(bool mode) {
    debugMode = mode;
}


z3::expr SolidityExprTranslator::
translate(Expression const* aExpr, ContextInfo& ctxInfo){
    z3::expr resultExpr(z3_ctx);

    if(Identifier const* idExp = dynamic_cast<Identifier const*>(aExpr)) {
        resultExpr = translate(idExp, ctxInfo);
    }
    else if(Literal const* litPtr = dynamic_cast<Literal const*>(aExpr)) {
        resultExpr = translate(litPtr, ctxInfo);
    }
    else if(UnaryOperation const* unaryExp = dynamic_cast<UnaryOperation const*>(aExpr)) {
        resultExpr = translate(unaryExp, ctxInfo);
    }
    else if(BinaryOperation const* binaryExp = dynamic_cast<BinaryOperation const*>(aExpr)) {
        resultExpr = translate(binaryExp, ctxInfo);
    }
    else if(FunctionCall const* functioncallExp = dynamic_cast<FunctionCall const*>(aExpr)) {
        resultExpr = translate(functioncallExp, ctxInfo);
    }
    else if(MemberAccess const* memaccExp = dynamic_cast<MemberAccess const*>(aExpr)) {
        resultExpr = translate(memaccExp, ctxInfo);
    }
    else if(IndexAccess const* indexaccessExp = dynamic_cast<IndexAccess const*>(aExpr)) {
        resultExpr = translate(indexaccessExp, ctxInfo);
    }
    else if(TupleExpression const* tupleExp = dynamic_cast<TupleExpression const*>(aExpr)) {
        resultExpr = translate(tupleExp, ctxInfo);
    }
    else{
        std::cerr<<"The expression is not supported currently: "<<std::endl;
        assert(false);
    }

    assert(resultExpr.to_string() != "null");

    return resultExpr;
}

z3::expr SolidityExprTranslator::
translate(Identifier const* idExp, ContextInfo& ctxInfo) {
    if(debugMode) {
        std::cerr<<"translating <Identifier>"<<std::endl;
    }

    std::string varName = idExp->name();

    //assert(ctxInfo.funcScope);
    //std::string varFullName = varName + SymExecEngine::nameSeparator + ctxInfo.funcScope->name();
    std::string varFullName = symExecEngine->getVarFullName(idExp, ctxInfo);

    //std::cerr<<"var ["<<varName<<"], fullName: "<<symExecEngine->getVarFullName(idExp)<<std::endl;

    if(debugMode) {
        std::cerr<<"translating ["<<varName<<"], its fullName: "<<varFullName<<std::endl;
    }

    std::unordered_map<std::string, z3::expr>::const_iterator itr = ctxInfo.stateVarValueZ3ExprMap.find(varFullName);

    if(itr != ctxInfo.stateVarValueZ3ExprMap.end()){
        /** the variable is a state variable and found in stateVarZ3ExprMap **/
        if(debugMode) {
            std::cerr<<"found, returning: "<<itr->second<<std::endl;
        }

        return itr->second;
    }
    else{
        itr = ctxInfo.localVarValueZ3ExprMap.find(varFullName);

        if(itr != ctxInfo.localVarValueZ3ExprMap.end()){
            /** the variable is a local variable and found in localVarZ3ExprMap **/
            if(debugMode) {
                std::cerr<<"found, returning: "<<itr->second<<std::endl;
            }

            return itr->second;
        }
        else{
            TypePointer typePtr = idExp->annotation().type;

            z3::sort typeSort = symExecEngine->typeSortInZ3(typePtr);

            z3::expr varExpr = z3_ctx.constant(varFullName.c_str(), typeSort);

            std::pair<std::string, z3::expr> _pair(varFullName, varExpr);
            ctxInfo.localVarValueZ3ExprMap.insert(_pair);

            if(debugMode) {
                std::cerr<<"add a variable ["<<varFullName<<"] into localVarValueZ3ExprMap"<<std::endl;

                //std::cerr<<"Error! Cannot find z3::expr for the variable: "<<varName<<std::endl;
                //assert(false);
            }

            return varExpr;
        }
    }
}

z3::expr SolidityExprTranslator::
translate(Literal const* litExpr, ContextInfo& ctxInfo){
    std::string valueStr = litExpr->value();

    if(debugMode) {
        std::cerr<<"translating <Literal>: "<<valueStr<<std::endl;
    }

    std::ignore = ctxInfo;

    z3::expr resultExpr(z3_ctx);

    if(valueStr.compare("true") == 0){
        resultExpr = z3_ctx.bool_val(true);
    }
    else if (valueStr.compare("false") == 0){
        resultExpr = z3_ctx.bool_val(false);
    }
    else if (valueStr.find("0x") == 0) {
        //std::cerr<<"the literal is hex"<<std::endl;
        std::string subStr = valueStr.substr(2);
        //std::cerr<<"the literal: "<<subStr<<std::endl;

        try {
            std::string::size_type sz;

            int hexValue =  std::stol(subStr, &sz, 16);

            //std::cerr<<"sz: "<<sz<<std::endl;

            if(sz == subStr.size()){  /** the string can be converted into integers **/
                //std::cerr<<"hexValue: "<<hexValue<<std::endl;

                resultExpr = z3_ctx.int_val(hexValue);

                //std::cerr<<"resultExpr: "<<resultExpr<<std::endl;
            }
        }
        catch(std::invalid_argument& e){     /** the string is actually string literal **/
            //std::cerr<<"string literal"<<std::endl;
            resultExpr = z3_ctx.string_val(valueStr.c_str());
        }// in case that literal is constant address and std::stoi or std::stol would fail to parse it.
        catch(...){
            std::cerr<<"The literal ["<<valueStr<<"] is not supported yet!!"<<std::endl;
            resultExpr = z3_ctx.string_val(valueStr.c_str());
            // assert(false);
        }
    }
    else{
        std::string::size_type sz;

        try{
             std::stol(valueStr, &sz);

            //std::cerr<<"sz: "<<sz<<std::endl;

            if(sz == valueStr.size()){  /** the string can be converted into integers **/
                resultExpr = z3_ctx.int_val(valueStr.c_str());
            }
            else{
                //std::cerr<<"string literal"<<std::endl;
                resultExpr = z3_ctx.string_val(valueStr.c_str());
            }
        }
        catch(std::invalid_argument& e){     /** the string is actually string literal **/
            //std::cerr<<"string literal"<<std::endl;
            resultExpr = z3_ctx.string_val(valueStr.c_str());
        }
        catch(...){
            std::cerr<<"The literal ["<<valueStr<<"] is not supported yet!!"<<std::endl;
            resultExpr = z3_ctx.string_val(valueStr.c_str());
            // assert(false);
        }
    }

    return resultExpr;
}

z3::expr SolidityExprTranslator::
translate(UnaryOperation const* unaryExp, ContextInfo& ctxInfo) {
    if(debugMode) {
        std::cerr<<"translating <UnaryOperation>"<<std::endl;
    }

    Expression const& operandExp = unaryExp->subExpression();
    Token opToken = unaryExp->getOperator();
    z3::expr operand = translate(&operandExp, ctxInfo);

    switch (opToken) {
        case Token::Not:
            return (!operand);
        case Token::BitNot:
            return (~operand);
        case Token::Delete:
            if(operandExp.annotation().type->category() == Type::Category::Integer){
                return (operand = z3_ctx.int_val(0));
            }
            else if(operandExp.annotation().type->category() == Type::Category::Array) {
                auto const& type = dynamic_cast<ArrayType const&>(*operandExp.annotation().type);
                for(int i=0; i<type.length(); i++){
                    z3::store(operand, z3_ctx.int_val(i), 0);
                }

                return operand;
            }
            else if(operandExp.annotation().type->category() == Type::Category::Struct){
                auto const& type = dynamic_cast<StructDefinition const&>(*operandExp.annotation().type);
                std::vector <ASTPointer<VariableDeclaration>> const& Members = type.members();

                for(unsigned int i=0; i<Members.size(); i++){
                    VariableDeclaration const& memberExp = *Members[i];
                    Identifier const& membername = dynamic_cast<Identifier const&>(memberExp);
                    z3::expr member = translate(&membername, ctxInfo);
                    member = z3_ctx.int_val(0);
                }
                return operand;
            }
            else{
                assert(false);
            }
        case Token::Inc:
            return (operand = (operand) + 1);
        case Token::Dec:
            return (operand = (operand) - 1);
        case Token::Add:
            if(operand >= 0)
                return (operand);
            else
                return (operand * (-1));
        case Token::Sub:
            if(operand >= 0)
                return (operand * (-1));
            else
                return (operand);
        default:
            std::string opstring = TokenTraits::toString(opToken);
            std::cerr<<"["<<opstring<<"]"<<": this unary operation is not supported yet!"<<std::endl;
            assert(false);
    }
}

z3::expr SolidityExprTranslator::
translate(BinaryOperation const* binaryExp, ContextInfo& ctxInfo) {

    if(debugMode){
        std::cerr<<"translating <BinaryOperation>"<<std::endl;
    }

    Expression const& leftExpression = binaryExp->leftExpression();
    Expression const& rightExpression = binaryExp->rightExpression();
    Token opToken = binaryExp->getOperator();

    z3::expr leftoperand = translate(&leftExpression, ctxInfo);

    z3::expr rightoperand = translate(&rightExpression, ctxInfo);

    switch (opToken) {
        case Token::And:
            return (leftoperand && rightoperand);
        case Token::Or:
            return (leftoperand || rightoperand);
        case Token::BitOr:
            return (leftoperand | rightoperand);
        case Token::BitAnd:
            return (leftoperand & rightoperand);
        case Token::BitXor:
            return (leftoperand ^ rightoperand);
        case Token::SHL:
            return (leftoperand * (2 ^ rightoperand));
        case Token::SAR:
            return (leftoperand / (2 ^ rightoperand));
        // case Token::SHR:
        //     break;
        case Token::Equal:
            return (leftoperand == rightoperand);
        case Token::NotEqual:
            return (!(leftoperand == rightoperand));
        case Token::GreaterThanOrEqual:
            return (leftoperand >= rightoperand);
        case Token::LessThanOrEqual:
            return (leftoperand <= rightoperand);
        case Token::GreaterThan:
            return (leftoperand > rightoperand);
        case Token::LessThan:
            return (leftoperand < rightoperand);
        case Token::Add:
            return (leftoperand + rightoperand);
        case Token::Sub:
            return (leftoperand - rightoperand);
        case Token::Mul:
            return (leftoperand * rightoperand);
        case Token::Div:
            return (leftoperand / rightoperand);
        case Token::Exp:
            return (leftoperand ^ rightoperand);
        case Token::Mod: {
            Z3_ast result = Z3_mk_mod(z3_ctx, leftoperand, rightoperand);
            return z3::expr(z3_ctx,result);
        }
        default: {
            std::string opstring = TokenTraits::toString(opToken);
            std::cerr<<"["<<opstring<<"]"<<": this binary operation is not supported yet!"<<std::endl;
            assert(false);
        }
    }
}

z3::expr SolidityExprTranslator::
translate(FunctionCall const* functioncallExp, ContextInfo& ctxInfo) {

    if(debugMode){
        std::cerr<<"translating <FunctionCall>"<<std::endl;
    }

    z3::expr resultExpr(z3_ctx);

    Expression const& funExp = functioncallExp->expression();

    std::string funcName;

    if(Identifier const* id = dynamic_cast<Identifier const*>(&funExp)) {
        funcName = id->name();
    }
    else if(MemberAccess const* funExpId = dynamic_cast<MemberAccess const*>(&funExp)) {
        funcName = dynamic_cast<std::string const&>(funExpId->memberName());
    }
    /* else if(FunctionCall const* childCall = dynamic_cast<FunctionCall const*>(&funExp)) {

    } */
    else{
        std::cerr<<"Cannot get the name of the function call ["<<funcName<<"]"<<std::endl;
        assert(false);
    }

    if(debugMode) {
        std::cerr<<"translating FunctionCall of ["<<funcName<<"]"<<std::endl;
    }

    FunctionDefinition const* funcDef = symExecEngine->getFuncDefinition(funcName);

    std::vector<ASTPointer<VariableDeclaration>> returnVec = funcDef->returnParameters();

    z3::expr_vector resultExprVec(z3_ctx);
    z3::sort_vector sortVec(z3_ctx);

    for(unsigned i = 0; i < returnVec.size(); i++) {
        VariableDeclaration const& varDec = *returnVec[i];
        std::string varFullName = symExecEngine->getVarFullName(&varDec, ctxInfo);

        try {
            resultExprVec.push_back(ctxInfo.localVarValueZ3ExprMap.at(varFullName));
            sortVec.push_back(ctxInfo.localVarValueZ3ExprMap.at(varFullName).get_sort());
        }
        catch(...) {
            std::cerr<<"variable ["<<varFullName<<"]'s key not found."<<std::endl;
            assert(false);
        }
    }

    if(returnVec.size() == 1) {
        resultExpr = resultExprVec[0];
    }
    else {
        z3::func_decl container = z3_ctx.function("tuple", sortVec, z3_ctx.int_sort());
        assert(container.to_string() != "null");

        resultExpr = container(resultExprVec);
    }

    return resultExpr;
}

z3::expr SolidityExprTranslator::
translate(MemberAccess const* memAccExp, ContextInfo& ctxInfo) {

    if(debugMode){
        std::cerr<<"translating <MemberAccess>"<<std::endl;
    }

    Expression const& Exp = memAccExp->expression();
    ASTString const& memnameExp = memAccExp->memberName();

    std::string const& memnameExpName = dynamic_cast<std::string const&>(memnameExp);

    if(debugMode) {
        std::cerr<<"memberName: "<<memnameExpName;

        TypePointer wholeType = memAccExp->annotation().type;
        std::cerr<<", Type: "<<wholeType->toString()<<std::endl;
    }

    TypePointer expType = Exp.annotation().type;

    if(memnameExpName.compare("balance") == 0) {
        /*** could be address(this).balance or addr.balnce  ***/

        if(Identifier const* ExpId = dynamic_cast<Identifier const*>(&Exp)) {
            std::string ExpName = ExpId->name();

            std::string const& varName = ExpName + "." + memnameExpName;

            if(debugMode) {
                std::cerr<<"varName: "<<varName<<std::endl;
            }

            std::unordered_map<std::string, z3::expr>::const_iterator itr = ctxInfo.stateVarValueZ3ExprMap.find(varName);

            if(itr != ctxInfo.stateVarValueZ3ExprMap.end()){
                /** the variable is a state variable and found in stateVarZ3ExprMap **/
                return itr->second;
            }
            else{
                std::cerr<<"Error! Cannot find z3::expr for the variable: "<<varName<<std::endl;
                assert(false);
            }
        }
        else if(FunctionCall const* funCallExp = dynamic_cast<FunctionCall const*>(&Exp)) {
            std::vector<ASTPointer<Expression const>> args =  funCallExp->arguments();
            assert(args.size() == 1);

            Expression const& thisPointer = *args[0];

            if(Identifier const* ExpId = dynamic_cast<Identifier const*>(&thisPointer)) {
                if(ExpId->name() == "this") {
                    return ctxInfo.stateVarValueZ3ExprMap.at("this.balance");
                }
            }
            else{
                std::cerr<<"This should not happen!"<<std::endl;
                assert(false);
            }
        }
        else {
            std::cerr<<"This should not happen!"<<std::endl;
            assert(false);
        }
    }else  if(memnameExpName.compare("length") == 0){
        std::string fullName;
        Identifier const* idExp = dynamic_cast<Identifier const*>(&Exp);
        std::string varName = idExp->name();
        IdentifierAnnotation& idInfo = idExp->annotation();
        Declaration const* dec = idInfo.referencedDeclaration;

        assert(dec);

        fullName.append(varName);
        fullName.append(SymExecEngine::nameSeparator);
        fullName.append(std::to_string(dec->id()));
       
        varName = fullName + "." + memnameExpName;

        if(debugMode) {
            std::cerr<<"varName: "<<varName<<std::endl;
        }
        std::unordered_map<std::string, z3::expr>::const_iterator itr = ctxInfo.stateVarValueZ3ExprMap.find(varName);
        if(itr != ctxInfo.stateVarValueZ3ExprMap.end()){
            /** the variable is a state variable and found in stateVarZ3ExprMap **/
            return itr->second;
        }
        else{
            std::cerr<<"Error! Cannot find z3::expr for the variable: "<<varName<<std::endl;
            assert(false);
        }
    }
    else if(expType->toString().compare("msg") == 0) {
        /*** could be msg.xxx  ***/

        Identifier const* ExpId = dynamic_cast<Identifier const*>(&Exp);
        std::string ExpName = ExpId->name();

        std::string const& varName = ExpName + "." + memnameExpName;

        if(debugMode) {
            std::cerr<<"varName: "<<varName<<std::endl;
        }

        std::unordered_map<std::string, z3::expr>::const_iterator itr = ctxInfo.stateVarValueZ3ExprMap.find(varName);

        if(itr != ctxInfo.stateVarValueZ3ExprMap.end()){
            /** the variable is a state variable and found in stateVarZ3ExprMap **/
            return itr->second;
        }
        else{
            std::cerr<<"Error! Cannot find z3::expr for the variable: "<<varName<<std::endl;
            assert(false);
        }
    }


    //std::cerr<<"varName: "<<varName<<std::endl;
    //std::cerr<<"Of type: "<<expType->toString()<<std::endl;

//        if(varName.compare("msg.value") == 0 || varName.compare("msg.sender") == 0 || varName.compare("this.balance") == 0){
//            /*** could be msg.xxx   ***/
//
//            std::unordered_map<std::string, z3::expr>::const_iterator itr = stateVarZ3ExprMap.find(varName);
//
//            if(itr != stateVarZ3ExprMap.end()){
//                /** the variable is a state variable and found in stateVarZ3ExprMap **/
//                return itr->second;
//            }
//            else{
//                itr = localVarZ3ExprMap.find(varName);
//
//                if(itr != localVarZ3ExprMap.end()){
//                    /** the variable is a local variable and found in localVarZ3ExprMap **/
//                    return itr->second;
//                }
//                else{
//                    std::cerr<<"Error! Cannot find z3::expr for the variable: "<<varName<<std::endl;
//                    assert(false);
//                }
//            }
//        }

    z3::expr motherExpr = translate(&Exp, ctxInfo);

    if(debugMode) {
        std::cerr<<"motherExpr: "<<motherExpr<<std::endl;
    }

    z3::expr resultExpr(z3_ctx);

    if(std::shared_ptr<StructType const> structType = std::dynamic_pointer_cast<StructType const>(expType)){
        std::string structName = structType->structDefinition().name();

        //std::cerr<<"Struct Type: "<<structName<<std::endl;
        //std::cerr<<"fileName: "<<memnameExpName<<std::endl;

        std::unordered_map<std::string, std::shared_ptr<StructInfo>>::iterator structItr = symExecEngine->structsMap.find(structName);

        if(structItr != symExecEngine->structsMap.end()){
            int fieldIndex = structItr->second->getProjIndex(memnameExpName);
            //std::cerr<<"fieldIndex: "<<fieldIndex<<std::endl;

            assert(fieldIndex != -1);

            if(IndexAccess const* idAccess = dynamic_cast<IndexAccess const*>(&Exp)) {
                resultExpr = (((structItr->second->projectors[0])[fieldIndex])(motherExpr));
                std::ignore = idAccess;
            }
            else {
                try{
                    assert(motherExpr.is_app());
                    resultExpr = motherExpr.arg(fieldIndex);

                    assert(motherExpr.num_args() == structItr->second->fieldNames.size());
                }
                catch(...) {
                    resultExpr = (((structItr->second->projectors[0])[fieldIndex])(motherExpr));
                }
            }

            /* if(Identifier const* ExpId = dynamic_cast<Identifier const*>(&Exp)) {
                try{
                    assert(motherExpr.is_app());
                    resultExpr = motherExpr.arg(fieldIndex);

                    assert(motherExpr.num_args() == structItr->second->fieldNames.size());
                }
                catch(...) {
                    resultExpr = (((structItr->second->projectors[0])[fieldIndex])(motherExpr));
                }
            }
            else {
                resultExpr = (((structItr->second->projectors[0])[fieldIndex])(motherExpr));
            } */

            //std::cerr<<"resultExpr: "<<resultExpr<<std::endl;
        }
        else{
            std::cerr<<"Undefined struct ["<<structName<<"]"<<std::endl;
            assert(false);
        }
    }
    else{
        std::cerr<<"This member access is not supported currently."<<std::endl;
        assert(false);
    }

    if(debugMode) {
        std::cerr<<"mother.member: "<<resultExpr<<std::endl;
    }

    return (resultExpr);
}

z3::expr SolidityExprTranslator::
translate(IndexAccess const* indexAccessExp, ContextInfo& ctxInfo) {
    if(debugMode){
        std::cerr<<"translating <IndexAccess>"<<std::endl;
    }

    Expression const& baseExp = indexAccessExp->baseExpression();
    Expression const* baseName = dynamic_cast<Expression const*>(&baseExp);

    z3::expr base = translate(baseName, ctxInfo);

    if(debugMode) {
        std::cerr<<"base: "<<base<<std::endl;
    }

    Expression const* indexExp = indexAccessExp->indexExpression();
    z3::expr index = translate(indexExp, ctxInfo);

    if(debugMode) {
        std::cerr<<"index: "<<index<<std::endl;
    }

    z3::expr indaccExp = z3::select(base,index);

    if(debugMode) {
        std::cerr<<"base[index]: "<<indaccExp<<std::endl;
    }

    return indaccExp;
}

z3::expr SolidityExprTranslator::
translate(TupleExpression const* tupleExp, ContextInfo& ctxInfo) {
    if(debugMode){
        std::cerr<<"translating <TupleExpression>"<<std::endl;
    }

    std::vector<ASTPointer<Expression>> const& componentsExp = tupleExp->components();

    z3::expr_vector resultVec(z3_ctx);
    z3::sort_vector sortVec(z3_ctx);

    for(unsigned i = 0; i < componentsExp.size(); i++) {
        Expression const& exp = *componentsExp[i];
        z3::expr expInZ3 = translate(&exp, ctxInfo);
        if (componentsExp.size()==1){
            return expInZ3;
        }
        resultVec.push_back(expInZ3);
        sortVec.push_back(expInZ3.get_sort());

        if(debugMode) {
            std::cerr<<"["<<i<<"]"<<expInZ3<<", sort: "<<expInZ3.get_sort()<<std::endl;
        }
    }

    z3::func_decl container = z3_ctx.function("tuple", sortVec, z3_ctx.int_sort());
    assert(container.to_string() != "null");

    z3::expr tupleExpr = container(resultVec);

    assert(tupleExpr.to_string() != "null");

    if(debugMode) {
        std::cerr<<"tupleExpr: "<<tupleExpr<<std::endl;
    }

    return tupleExpr;
}
