pragma solidity >=0.4.11;

contract AuctionItem {
    
    string public auctionName;
    address payable public  owner; 
    bool auctionEnded = false;
    
    event NewHighestBid(
        address newHighBidder,
        uint newHighBid,
        string squak
    );
    
    uint public currentHighestBid = 0;
    address payable public  highBidder; 
    string public squak;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
    modifier higherBid {
        require(msg.value > currentHighestBid);
        _;
    }
    
    modifier auctionNotOver {
        require(auctionEnded == false);
        _;
    }
    
    constructor(string memory name, uint startingBid) public{
        auctionName = name; 
        owner = msg.sender;
        currentHighestBid = startingBid;
    }
    
    //allow people using MetaMask/Cipher et. al. to specifically set a taunting message ;)
    function bid(string memory _squak) public payable higherBid auctionNotOver {
        highBidder.transfer(currentHighestBid);
        currentHighestBid = msg.value;
        highBidder = msg.sender;
        squak = _squak;
        emit NewHighestBid(msg.sender, msg.value, _squak);

        }
    //allow people with basic wallets to send a bid (QR scan etc.), but no squaking for them 
    function() external payable higherBid auctionNotOver{
        highBidder.transfer(currentHighestBid);
        currentHighestBid = msg.value;
        highBidder = msg.sender;
        emit NewHighestBid(msg.sender, msg.value, '');
        
    }
    //The owner should be able to end the auction
    function endAuction() public onlyOwner{
        selfdestruct(owner);
        auctionEnded = true;
    }
    function newbid(address payable msg_sender, uint msg_value) public {
        if (msg_value <= currentHighestBid)return;
        highBidder.transfer(currentHighestBid);
        currentHighestBid = msg_value;
        highBidder = msg_sender;
    }
   
   
    mapping(address=>uint) utilities;
    mapping(address=>uint) benefits;
    mapping(address=>uint) payments;
    function sse_winner(address a) public view {}
    function sse_revenue(uint a) public view {}
    function sse_utility(uint a) public view {}
    function sse_maximize(uint a) public view {}
    function sse_minimize(uint a) public view {}
    function sse_truthful_violate_check(uint u, uint a, uint b) public view {}
    function sse_collusion_violate_check(uint u12, uint v1, uint v_1, uint v2, uint v_2) public view{}
    function sse_efficient_expectation_register(address allocation, address player, uint benefit) public view {}
    function sse_efficient_violate_check(uint benefit, address allocation, address other_allocation) public view {}
    function sse_optimal_payment_register(address allocation, address player, uint payment) public view {}
    function sse_optimal_violate_check(uint benefit, address allocation, address other_allocation) public view {}
    function sse_validate_outcome_postcondition(string memory desc, bool condition) public view {}
 
   function _Main_(address payable msg_sender1, uint p1, uint msg_value1, uint msg_gas1, uint block_timestamp1, 
		   address payable msg_sender2, uint p2, uint msg_value2, uint msg_gas2, uint block_timestamp2,
		   address payable msg_sender3, uint p3, uint msg_value3, uint msg_gas3, uint block_timestamp3,
		   address payable msg_sender4, uint p4, uint msg_value4, uint msg_gas4, uint block_timestamp4
		  ) public {
           require(!(msg_sender1==highBidder || msg_sender2 == highBidder || msg_sender3 == highBidder));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(!(msg_sender4==msg_sender1 || msg_sender4 == msg_sender2 || msg_sender4 == msg_sender3));
           require(currentHighestBid==0);
         

           require(p1>100000000000 && p1< 200000000000);
           require(p2>100000000000 && p2< 200000000000);
           require(p3>100000000000 && p3< 200000000000);
           require(p4>100000000000 && p4< 200000000000);
           require(msg_value1>100000000000 && msg_value1< 200000000000);
           require(msg_value2>100000000000 && msg_value2< 200000000000);
           require(msg_value3>100000000000 && msg_value3< 200000000000);
           require(msg_value4>100000000000 && msg_value4< 200000000000);

           require(utilities[msg_sender1] == 0);
           require(utilities[msg_sender2] == 0);
           require(utilities[msg_sender3] == 0);
           require(utilities[msg_sender4] == 0);

           require(benefits[msg_sender1] == 0);
           require(benefits[msg_sender2] == 0);
           require(benefits[msg_sender3] == 0);
           require(benefits[msg_sender4] == 0);

           require(payments[msg_sender1] == 0);
           require(payments[msg_sender2] == 0);
           require(payments[msg_sender3] == 0);
           require(payments[msg_sender4] == 0);

        //    require(msg_value1!=p1);
        //    require(msg_value2==p2);
        //    require(msg_value3==p3);

           // each role claims the 'bid' action.
            newbid(msg_sender1,msg_value1);
            newbid(msg_sender2,msg_value2);
            newbid(msg_sender3,msg_value3);
            newbid(msg_sender4,msg_value4);

              // assert(msg_sender3 == highBidder);
            assert(msg_sender1 == highBidder || msg_sender2 == highBidder ||  msg_sender3 == highBidder||  msg_sender4 == highBidder );

	    uint winner_value=0;
	    uint clear_price=0;
	    uint highest_price = 0;
	    uint secondhighest_price = 0;

            uint  winners_count = 0;
            if(highest_price<msg_value1){
		    secondhighest_price = highest_price;
		    highest_price = msg_value1;
	    }else if (secondhighest_price < msg_value1){
		    secondhighest_price = msg_value1;
	    }
	   
            if(highest_price<msg_value2){
		    secondhighest_price = highest_price;
		    highest_price = msg_value2;
	    }
	    else if (secondhighest_price < msg_value2){
		    secondhighest_price = msg_value2;
	    }
            if(highest_price<msg_value3){
		    secondhighest_price = highest_price;
		    highest_price = msg_value3;
	    }
	    else if (secondhighest_price < msg_value3){
		    secondhighest_price = msg_value3;
	    }
            if(highest_price<msg_value4){
		    secondhighest_price = highest_price;
		    highest_price = msg_value4;
	    }
	    else if (secondhighest_price < msg_value4){
		    secondhighest_price = msg_value4;
	    }
            if ( msg_sender1 == highBidder ){
                        sse_winner(msg_sender1);
                        winners_count ++;
			winner_value = msg_value1;
                        utilities[msg_sender1] = p1 - currentHighestBid;
                        benefits[msg_sender1]  = p1;
                        payments[msg_sender1]  =currentHighestBid;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == highBidder ){
                        sse_winner(msg_sender2);
                        winners_count ++;
			winner_value = msg_value2;
                        utilities[msg_sender2] = p2 - currentHighestBid;
                        benefits[msg_sender2]  = p2;
                        payments[msg_sender2]  =currentHighestBid;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == highBidder ){
                        sse_winner(msg_sender3);
                        winners_count ++;
			winner_value = msg_value3;
                        utilities[msg_sender3] = p3 - currentHighestBid;
                        benefits[msg_sender3]  = p3;
                        payments[msg_sender3]  = currentHighestBid;
            }
            sse_utility(utilities[msg_sender3]);
            if ( msg_sender4 == highBidder ){
                        sse_winner(msg_sender4);
                        winners_count ++;
			winner_value = msg_value4;
                        utilities[msg_sender4] = p4 - currentHighestBid;
                        benefits[msg_sender4]  = p4;
                        payments[msg_sender4]  = currentHighestBid;
            }
            sse_utility(utilities[msg_sender4]);
	    clear_price = currentHighestBid ;  

            sse_optimal_payment_register(highBidder, msg_sender1, msg_value1);
            sse_optimal_payment_register(highBidder, msg_sender2, msg_value2);
            sse_optimal_payment_register(highBidder, msg_sender3, msg_value3);
            sse_optimal_payment_register(highBidder, msg_sender4, msg_value4);
	    uint payment = payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3]+payments[msg_sender4];
            sse_optimal_violate_check(payment, highBidder,msg_sender1);
            sse_optimal_violate_check(payment, highBidder,msg_sender2);
            sse_optimal_violate_check(payment, highBidder,msg_sender3);
            sse_optimal_violate_check(payment, highBidder,msg_sender4);

	    sse_validate_outcome_postcondition("Allocation: 1st highest bidder", winner_value==highest_price);

	    sse_validate_outcome_postcondition("Payment: 1st highest bid", clear_price==highest_price);
	    sse_validate_outcome_postcondition("Payment: 2nd highest bid", clear_price==secondhighest_price);
	    sse_validate_outcome_postcondition("highest_price!=secondhighest_price", highest_price!=secondhighest_price);

   }
}
