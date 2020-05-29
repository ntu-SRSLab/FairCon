#include "mechanism.h"
#include "fort.hpp"
z3::context* Mechanism::p_z3_ctx=new z3::context();
bool Mechanism::isEmpty(){
	return model_type.get_numeral_int64()==-1;
}
bool Mechanism::check(){
	if (model_type.get_numeral_int64()==-1)
		return false;
	std::cout<<  "Mechanism model check" <<std::endl;
	check_property();
	check_invariant();
	return true;
}
bool Mechanism::check_property(){
	assert(Mechanism::p_z3_ctx!=NULL);
	z3::solver solver(*Mechanism::p_z3_ctx);
    solver.add(preCond);
	solver.add(price>0);
    for (auto assumption: assumptions){
		solver.add(assumption);
	}
	for (unsigned i=0; i<bidders.size(); i++)
	 for (unsigned j=i+1; j<bidders.size(); j++)
	 {
	  solver.add(bidders.at(i).at(0)!=bidders.at(j).at(0));
	 }
	auto bid_ids = allocation == bidders.at(0).at(0);
	for(auto bidder: bidders){
			 solver.add(bidder.at(1)>0);
			 solver.add(bidder.at(2)>0);
			 bid_ids = bid_ids || allocation == bidder.at(0);
	}
	solver.add(bid_ids);
	for(unsigned i=0; i<utilities.size(); i++){
			 utilities[i][1] = z3::ite(utilities[i].at(0)==allocation, utilities[i].at(1), (*Mechanism::p_z3_ctx).int_val(0));
			 solver.add(utilities[i][1]>=0);
		 }

	for(auto type: check_types)
	{
		bool truthful_flag = false;
		std::cout<<type << std::endl;
		solver.push();
		solver.add(type==0);
	    if (check_truthfulness(solver)){
			truthful_flag = true;
		}
		solver.pop();
		solver.push();
		solver.add(type==1);
		check_collusionfreeness(solver);
		solver.pop();	
		if(truthful_flag==true){
			for(auto bidder: bidders){
			  solver.add(bidder.at(1)==bidder.at(2));
		    }
		}	
		solver.push();
		solver.add(type==2);
		check_efficiency(solver);
		solver.pop();
  		solver.push();
   	        solver.add(type==3);
		check_optimality(solver);
		solver.pop();
	}
	return true;
}
bool Mechanism::check_invariant(){
	z3::solver solver(*Mechanism::p_z3_ctx);
        solver.add(preCond);
	for(auto type: invariant_types)
	{
		solver.push();
		solver.add(type==0);
		check_TopBidder(solver);
		solver.pop();
		solver.add(type==1);
		check_1stPrice(solver);
		solver.pop();
		solver.add(type==2);
		check_2ndPrice(solver);
		solver.pop();
	}
	return true;
}
bool Mechanism::check_truthfulness(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first bidder
         auto val = bidders.at(0).at(2);
		 auto bid = bidders.at(0).at(1);
         auto bid_mirror_name = bid.decl().name().str()+"#2";
         auto bid_mirror = (*Mechanism::p_z3_ctx).constant(bid_mirror_name.c_str(),bid.get_sort());
		 auto bid_ids = allocation == bidders.at(0).at(0);
	
		
		 for(auto bidder: bidders){
			
			 solver.add(bidder.at(1)==bidder.at(2));
		 }
		 solver.add(price>0);
		 solver.add(bid_mirror != val);
         z3::expr_vector from(*Mechanism::p_z3_ctx),to(*Mechanism::p_z3_ctx);
         from.push_back(bid);
         to.push_back(bid_mirror);
	
	     auto utility = utilities.at(0).at(1);
	     auto utility_mirror = utility.substitute(from, to);
	     auto property = utility_mirror<=utility;
	     solver.add(!property);
         if (z3::sat == solver.check())	
	 {
		 
		 auto model = solver.get_model(); 
		 std::cout<<"bidder" << "|" << "truthful bid" << "|" << "truthful utility" <<"|"<< "untruthful bid" << "|"  << "untruthful utility" << std::endl; 
		 std::cout<< model.eval(bidders.at(0).at(0)) <<" "<<model.eval(bid) << " "<<model.eval(utility)<< " "<< model.eval(bid_mirror) <<" "<< model.eval(utility_mirror) <<std::endl;
		 print_model(model, "untruthful");
		 return false;
	 }else{
	         std::cout<<"Truthfulness: "<<	"True" <<std::endl;
		 return true;
	 }
}
bool Mechanism::check_collusionfreeness(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first two bidder
         auto bid1 = bidders.at(0).at(1);
         auto bid1_mirror_name = bid1.decl().name().str()+"#2";
         auto bid1_mirror = (*Mechanism::p_z3_ctx).constant(bid1_mirror_name.c_str(),bid1.get_sort());
         auto bid2 = bidders.at(1).at(1);
         auto bid2_mirror_name = bid2.decl().name().str()+"#2";
         auto bid2_mirror = (*Mechanism::p_z3_ctx).constant(bid2_mirror_name.c_str(),bid2.get_sort());
		 solver.add(bid1 !=  bidders.at(0).at(2));
		 solver.add(bid2 !=  bidders.at(1).at(2));
		 solver.add(( (bid1_mirror ==  bidders.at(0).at(2)) &&  (bid2_mirror !=  bidders.at(1).at(2)) ) ||
		 ( (bid1_mirror !=  bidders.at(0).at(2)) &&  (bid2_mirror ==  bidders.at(1).at(2)) )
		 );
	
         z3::expr_vector from(*Mechanism::p_z3_ctx),to(*Mechanism::p_z3_ctx);
         from.push_back(bid1);
         from.push_back(bid2);
         to.push_back(bid1_mirror);
         to.push_back(bid2_mirror);
 	 auto utility1 = utilities.at(0).at(1);
  	 auto utility2 = utilities.at(1).at(1);
 	 auto utility1_mirror = utility1.substitute(from, to);
	 auto utility2_mirror = utility2.substitute(from, to);
	 auto allocation_mirror = allocation.substitute(from, to);
	 auto property = (utility1_mirror+utility2_mirror)<=(utility1+utility2);
	 solver.add(!property);
         if (z3::sat == solver.check()){
		 auto model = solver.get_model(); 
		 std::cout<< "comparison" << "|" << "p1"<<"|"<<"bid1" << "|" <<"p2"<<"|"<<"b2" << "|"<<"allocation" <<"|"<< "group utility" <<std::endl;  
		 std::cout<<"truthful:"<< model.eval(bidders.at(0).at(0)) << ":"<<model.eval(bid1) <<"  " << model.eval(bidders.at(1).at(0)) << ":"<<model.eval(bid2)<< " " <<model.eval(allocation) << " |"<<model.eval(utility1+utility2)<<std::endl;
		 std::cout<<"collusion:"<< model.eval(bidders.at(0).at(0)) << ":"<<model.eval(bid1_mirror) <<"  " << model.eval(bidders.at(1).at(0)) << ":"<<model.eval(bid2_mirror) << " "<<model.eval(allocation_mirror)<<" "<< model.eval(utility1_mirror+utility2_mirror)<<std::endl;
		 print_model(model, "collusion");
		 return false;
	 }else{
	         std::cout<<"Collusion-freeness: "<<	"True" <<std::endl;
		 return true;
	 }

}	

bool Mechanism::check_efficiency(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first two bidder
         auto val1 = bidders.at(0).at(2);
	 auto bidder_id1 = bidders.at(0).at(0);	 
	 auto TopBidder = bidder_id1;
	 auto TopVal = val1;
	 for (auto bidder:bidders)
	 {
		TopBidder =  z3::ite(TopVal<bidder.at(2),bidder.at(0),TopBidder);
		TopVal =  z3::ite(TopVal<bidder.at(2),bidder.at(2),TopVal);
	 }
	 auto property = TopBidder==allocation;
	 solver.add(!property);
         if (z3::sat == solver.check()){
		 auto model = solver.get_model(); 
		 std::cout << "Highest Valuation Bidder:" << model.eval(TopBidder)<< " is not the winner" << std::endl;
		 print_model(model, "not efficient");
		 return false;
	 }else{
	         std::cout<<"Efficiency: "<<	"True" <<std::endl;
		 return true;
	 }
}
bool Mechanism::check_optimality(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first two bidder
     auto bid1 = bidders.at(0).at(1);
	 auto bidder_id1 = bidders.at(0).at(0);	 
	 auto TopBidder = bidder_id1;
	 auto TopBid = bid1;
	 for (auto bidder:bidders)
	 {
		TopBidder =  z3::ite(TopBid<bidder.at(1),bidder.at(0),TopBidder);
		TopBid =  z3::ite(TopBid<bidder.at(1),bidder.at(1),TopBid);
	 }
	 
	 auto property = TopBid==price;
	 solver.add(!property);
         if (z3::sat == solver.check()){
		 auto model = solver.get_model(); 
		 std::cout << "Highest Price Bidder:" << model.eval(TopBid)<< " is not the clear price" << std::endl;
		 print_model(model, "not optimal");
		 return false;
	 }else{
	         std::cout<<"Optimality: "<<	"True" <<std::endl;
		 return true;
	 }
}
bool Mechanism::check_TopBidder(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first two bidder
         auto bid1 = bidders.at(0).at(1);
	 auto bidder_id1 = bidders.at(0).at(0);	 
	 auto TopBidder = bidder_id1;
	 auto TopBid = bid1;
	 for (auto bidder:bidders)
	 {
		TopBidder =  z3::ite(TopBid<bidder.at(1),bidder.at(0),TopBidder);
		TopBid =  z3::ite(TopBid<bidder.at(1),bidder.at(1),TopBid);
	 }
	 auto property = TopBidder==allocation;
	 solver.add(!property);
         if (z3::sat == solver.check()){
		 auto model = solver.get_model(); 
		 print_model(model, "not TopBidder");
		 return false;
	 }else{
	         std::cout<<"TopBidder: "<<	"True" <<std::endl;
		 return true;
	 }
}
bool Mechanism::check_1stPrice(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first two bidder
         auto bid1 = bidders.at(0).at(1);
	 auto bidder_id1 = bidders.at(0).at(0);	 
	 auto TopBidder = bidder_id1;
	 auto TopBid = bid1;
	 for (auto bidder:bidders)
	 {
		TopBidder =  z3::ite(TopBid<bidder.at(1),bidder.at(0),TopBidder);
		TopBid =  z3::ite(TopBid<bidder.at(1),bidder.at(1),TopBid);
	 }
	 auto property = TopBid==price;
	 solver.add(!property);
         if (z3::sat == solver.check()){
		 auto model = solver.get_model(); 
		 print_model(model, "not 1st-Price");
		 return false;
	 }else{
	         std::cout<<"1st-Price: "<<	"True" <<std::endl;
		 return true;
	 }
}
bool Mechanism::check_2ndPrice(z3::solver& solver)
{
	if (z3::sat != solver.check())
	{
		return false;
	}
	//select first two bidder
         auto bid1 = bidders.at(0).at(1);
	 auto bidder_id1 = bidders.at(0).at(0);	 
	 auto TopBidder = bidder_id1;
	 auto TopBid = bid1;
	 auto SecBid = (*Mechanism::p_z3_ctx).int_val(0);
	 for (auto bidder:bidders)
	 {
		TopBidder =  z3::ite(TopBid<bidder.at(1),bidder.at(0),TopBidder);
		TopBid =  z3::ite(TopBid<bidder.at(1),bidder.at(1),TopBid);
		SecBid =  z3::ite(TopBid<bidder.at(1),TopBid,z3::ite(SecBid<bidder.at(1),bidder.at(1),SecBid));
	 }
	 auto property = SecBid!=0 && SecBid==price;
	 solver.add(!property);
         if (z3::sat == solver.check()){
		 auto model = solver.get_model(); 
		 print_model(model, "not 2nd-Price");
		 return false;
	 }else{
	         std::cout<<"2nd-Price: "<<	"True" <<std::endl;
		 return true;
	 }
}
