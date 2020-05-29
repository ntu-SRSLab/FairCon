#ifndef  MECHANISM_H
#define  MECHANISM_H
#include <z3.h>
#include <z3++.h>
#include <vector>
#include "fort.hpp"
class Mechanism;
class Mechanism{
	public:
		static z3::context* p_z3_ctx;
public:
		z3::expr preCond;
public:
		unsigned size=0;
		// model type: 0 auction 1 voting
		z3::expr model_type;
  	std::vector<z3::expr> variables;
   
    std::vector<std::string> variables_str;

    std::vector<z3::expr> variables_smt;

    std::vector<std::string> variables_smt_str;
		// check type: 0 truthfulness 2 collusion-free  3 optimal 4 efficient
		std::vector<z3::expr> check_types;
		// invariant type: 0 TopBidder 2 1st-Price  3 2nd-Price
		std::vector<z3::expr> invariant_types;
		std::vector<std::vector<z3::expr> > bidders;
		std::vector<z3::expr> assumptions; 
		z3::expr allocation;
		z3::expr price;
		std::vector<std::vector<z3::expr> > utilities; 
    Mechanism():preCond((*Mechanism::p_z3_ctx).bool_val(1)),model_type((*Mechanism::p_z3_ctx).int_val(-1)),allocation((*Mechanism::p_z3_ctx)),price((*Mechanism::p_z3_ctx).int_val(0)){
    }
    Mechanism& operator=(const Mechanism& other) {
	    size = other.size;
	    model_type = other.model_type;
	    check_types = other.check_types;
	    invariant_types = other.invariant_types;
	    bidders = other.bidders;
	    assumptions = other.assumptions;
	    allocation = other.allocation;
	    price = other.price;
	    utilities = other.utilities;
      variables = other.variables;
      variables_str = other.variables_str;
      variables_smt = other.variables_smt;
      variables_smt_str = other.variables_smt_str;
	    return *this;
    }
    bool isEmpty();
    bool check();
    bool check_property();
    bool check_invariant();
 private:
    bool check_truthfulness(z3::solver& solver);
    bool check_collusionfreeness(z3::solver& solver);
    bool check_efficiency(z3::solver& solver);
    bool check_optimality(z3::solver& solver);
 private:
    bool check_TopBidder(z3::solver& solver);
    bool check_1stPrice(z3::solver& solver);
    bool check_2ndPrice(z3::solver& solver);
	  
 public:
    void print_model(z3::model& model, std::string desc){
      fort::char_table table;
      table.set_border_style(FT_FRAME_STYLE);
      table.column(0).set_cell_text_align(fort::text_align::center);
      table.column(1).set_cell_text_align(fort::text_align::center);

      std::cout<<desc<<std::endl;
     // std::cout<<"bidders"<<std::endl;
      table << fort::header << "bidder" << "bid" <<  "valuation" << "utility" << "price" << "allocation" << fort::endr;
      unsigned i = 0;
      for (auto bidder: bidders)
      {
      //  std::cout<<model.eval(bidder.at(0)) << " "<< model.eval(bidder.at(1)) << " "<< model.eval(bidder.at(2))<<std::endl;
       table<<model.eval(bidder.at(0)) << model.eval(bidder.at(1))<< model.eval(bidder.at(2))<<model.eval(utilities.at(i++).at(1)) << model.eval(price) << model.eval(allocation==bidder.at(0)) << fort::endr;
      }
      std::cout<< table.to_string() << std::endl;
      // std::cout<<"allocation: "<<model.eval(allocation)<<std::endl;
      // std::cout<<"price: "<<model.eval(price)<<std::endl;
      // std::cout<<"utilities"<<std::endl;
      // for (auto utility: utilities)
      // {
      //  std::cout<<model.eval(utility.at(0)) << " " << model.eval(utility.at(1))<<std::endl;
      // }
      std::cout<<"variables"<<std::endl;
      auto index = 0;
      for (auto var: variables)
      {
        std::cout<<variables_str.at(index++)<<model.eval(var) <<std::endl;
      }
      //std::cout<<"SMTs" <<std::endl;
      //index = 0;
      //for (auto var: variables_smt)
      // {
       // std::cout<<variables_smt_str.at(index++)<<var<<std::endl;
       // } 
    }
};

#endif
