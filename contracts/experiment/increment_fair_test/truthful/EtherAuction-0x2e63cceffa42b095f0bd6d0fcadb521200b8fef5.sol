pragma solidity >=0.4.18;

contract EtherAuction {

  // The address that deploys this auction and volunteers 1 eth as price.
  address public auctioneer;
  uint public auctionedEth = 0;

  uint public highestBid = 0;
  uint public secondHighestBid = 0;

  address public highestBidder;
  address public secondHighestBidder;

  uint public latestBidTime = 0;
  uint public auctionEndTime;

  mapping (address => uint) public balances;

  bool public auctionStarted = false;
  bool public auctionFinalized = false;

  event E_AuctionStarted(address _auctioneer, uint _auctionStart, uint _auctionEnd);
  event E_Bid(address _highestBidder, uint _highestBid);
  event E_AuctionFinished(address _highestBidder,uint _highestBid,address _secondHighestBidder,uint _secondHighestBid,uint _auctionEndTime);

  constructor() public{
    auctioneer = msg.sender;
  }

  // The auctioneer has to call this function while supplying the 1th to start the auction
  function startAuction() public payable{
    require(!auctionStarted);
    require(msg.sender == auctioneer);
    require(msg.value == (1 * 10 ** 18));
    
    auctionedEth = msg.value;
    auctionStarted = true;
    auctionEndTime = now + (3600 * 24 * 7); // Ends 7 days after the deployment of the contract

    emit E_AuctionStarted(msg.sender,now, auctionEndTime);
  }

  //Anyone can bid by calling this function and supplying the corresponding eth
  function bid() public payable {
    require(auctionStarted);
    require(now < auctionEndTime);
    require(msg.sender != auctioneer);
    require(highestBidder != msg.sender); //If sender is already the highest bidder, reject it.

    address _newBidder = msg.sender;

    uint previousBid = balances[_newBidder];
    uint _newBid = msg.value + previousBid;

    require (_newBid  == highestBid + (5 * 10 ** 16)); //Each bid has to be 0.05 eth higher

    // The highest bidder is now the second highest bidder
    secondHighestBid = highestBid;
    secondHighestBidder = highestBidder;

    highestBid = _newBid;
    highestBidder = _newBidder;

    latestBidTime = now;
    //Update the bidder's balance so they can later withdraw any pending balance
    balances[_newBidder] = _newBid;

    //If there's less than an hour remaining and someone bids, extend end time.
    if(auctionEndTime - now < 3600)
      auctionEndTime += 3600; // Each bid extends the auctionEndTime by 1 hour

    emit E_Bid(highestBidder, highestBid);

  }
  // Once the auction end has been reached, we distribute the ether.
  function finalizeAuction() public {
    require (now > auctionEndTime);
    require (!auctionFinalized);
    auctionFinalized = true;

    if(highestBidder == address(0)){
      //If no one bid at the auction, auctioneer can withdraw the funds.
      balances[auctioneer] = auctionedEth;
    }else{
      // Second highest bidder gets nothing, his latest bid is lost and sent to the auctioneer
      balances[secondHighestBidder] -= secondHighestBid;
      balances[auctioneer] += secondHighestBid;

      //Auctioneer gets the highest bid from the highest bidder.
      balances[highestBidder] -= highestBid;
      balances[auctioneer] += highestBid;

      //winner gets the 1eth being auctioned.
      balances[highestBidder] += auctionedEth;
      auctionedEth = 0;
    }

    emit E_AuctionFinished(highestBidder,highestBid,secondHighestBidder,secondHighestBid,auctionEndTime);

  }

  //Once the auction has finished, the bidders can withdraw the eth they put
  //Winner will withdraw the auctionedEth
  //Auctioneer will withdraw the highest bid from the winner
  //Second highest bidder will already have his balance at 0
  //The rest of the bidders get their money back
  function withdrawBalance() public{
    require (auctionFinalized);

    uint ethToWithdraw = balances[msg.sender];
    if(ethToWithdraw > 0){
      balances[msg.sender] = 0;
      msg.sender.transfer(ethToWithdraw);
    }

  }

  //Call thisfunction to know how many seconds remain for the auction to end
  function timeRemaining() public view returns (uint ret){
      require (auctionEndTime > now);
      return auctionEndTime - now;
  }

  function myLatestBid() public view returns (uint ret){
    return balances[msg.sender];
  }

   function newbid(address payable msg_sender, uint msg_value, uint block_timestamp) public payable{
      require(auctionStarted);
      require(block_timestamp < auctionEndTime);
      require(msg_sender != auctioneer);
      require(highestBidder != msg_sender); //If sender is already the highest bidder, reject it.

      address _newBidder = msg_sender;

      uint previousBid = balances[_newBidder];
      uint _newBid = msg_value + previousBid;

      // require (_newBid  == highestBid + (5 * 10 ** 16)); //Each bid has to be 0.05 eth higher
      if (_newBid  != highestBid + 120000000000) return; //Each bid has to be 0.05 eth higher

      // The highest bidder is now the second highest bidder
      secondHighestBid = highestBid;
      secondHighestBidder = highestBidder;

      highestBid = _newBid;
      highestBidder = _newBidder;

      latestBidTime = block_timestamp;
      //Update the bidder's balance so they can later withdraw any pending balance
      balances[_newBidder] = _newBid;

      //If there's less than an hour remaining and someone bids, extend end time.
      if(auctionEndTime - block_timestamp < 3600)
        auctionEndTime += 3600; // Each bid extends the auctionEndTime by 1 hour

      emit E_Bid(highestBidder, highestBid);

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
		   address payable msg_sender3, uint p3, uint msg_value3, uint msg_gas3, uint block_timestamp3
		  ) public {
           require(!(msg_sender1==highestBidder || msg_sender2 == highestBidder || msg_sender3 == highestBidder));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(highestBid==0);
           require(balances[msg_sender1] == 0);
           require(balances[msg_sender2] == 0);
           require(balances[msg_sender3] == 0);

           require(p1>100000000000 && p1< 900000000000);
           require(p2>100000000000 && p2< 900000000000);
           require(p3>100000000000 && p3< 900000000000);
           require(msg_value1>100000000000 && msg_value1< 900000000000);
           require(msg_value2>100000000000 && msg_value2< 900000000000);
           require(msg_value3>100000000000 && msg_value3< 900000000000);

           require(utilities[msg_sender1] == 0);
           require(utilities[msg_sender2] == 0);
           require(utilities[msg_sender3] == 0);

           require(benefits[msg_sender1] == 0);
           require(benefits[msg_sender2] == 0);
           require(benefits[msg_sender3] == 0);

           require(payments[msg_sender1] == 0);
           require(payments[msg_sender2] == 0);
           require(payments[msg_sender3] == 0);

        //    require(msg_value1!=p1);
           require(msg_value2==p2);
           require(msg_value3==p3);

           // each role claims the 'bid' action.
            newbid(msg_sender1,msg_value1,block_timestamp1);
            newbid(msg_sender2,msg_value2,block_timestamp2);
            newbid(msg_sender3,msg_value3,block_timestamp3);

              // assert(msg_sender3 == highestBidder);
            assert(msg_sender1 == highestBidder || msg_sender2 == highestBidder ||  msg_sender3 == highestBidder );
            assert(msg_sender1 == secondHighestBidder || msg_sender2 == secondHighestBidder ||  msg_sender3 == secondHighestBidder );

	    uint winner_value=0;
	    uint clear_price=0;
	    uint highest_price = 0;
	    uint secondhighest_price = 0;

            uint  winners_count = 0;
            if(highest_price<msg_value1){
		    secondhighest_price = highest_price;
		    highest_price = msg_value1;
	    }
	    else if (secondhighest_price < msg_value1){
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

            if ( msg_sender1 == highestBidder ){
                        sse_winner(msg_sender1);
                        winners_count ++;
			winner_value = msg_value1;
                        utilities[msg_sender1] = p1 - secondHighestBid;
                        benefits[msg_sender1]  = p1;
                        payments[msg_sender1]  = secondHighestBid;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == highestBidder ){
                        sse_winner(msg_sender2);
			winner_value = msg_value2;
                        winners_count ++;
                        utilities[msg_sender2] = p2 - secondHighestBid;
                        benefits[msg_sender2]  = p2;
                        payments[msg_sender2]  = secondHighestBid;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == highestBidder ){
                        sse_winner(msg_sender3);
			winner_value = msg_value3;
                        winners_count ++;
                        utilities[msg_sender3] = p3 - secondHighestBid;
                        benefits[msg_sender3]  = p3;
                        payments[msg_sender3]  = secondHighestBid;
            }
            sse_utility(utilities[msg_sender3]);

	    clear_price = secondHighestBid;  
            sse_truthful_violate_check(utilities[msg_sender1],msg_value1, p1);

	    sse_validate_outcome_postcondition("Allocation: 1st highest bidder", winner_value==highest_price);

	    sse_validate_outcome_postcondition("Payment: 1st highest bid", clear_price==highest_price);
	    sse_validate_outcome_postcondition("Payment: 2nd highest bid", clear_price==secondhighest_price);
	    sse_validate_outcome_postcondition("highest_price!=secondhighest_price", highest_price!=secondhighest_price);
   }
}
