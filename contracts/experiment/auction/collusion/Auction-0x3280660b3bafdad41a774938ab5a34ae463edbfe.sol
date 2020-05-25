pragma solidity >=0.4.23;

// Deploying version: https://github.com/astralship/auction-ethereum/commit/1359e14e0319c6019eb9c7e57348b95c722e3dd6
// Timestamp Converter: 1529279999
// Is equivalent to: 06/17/2018 @ 11:59pm (UTC)
// Sunday midnight, in a week 😎

contract Auction {
  
  string public description;
  string public instructions; // will be used for delivery address or email
  uint public price;
  bool public initialPrice = true; // at first asking price is OK, then +25% required
  uint public timestampEnd;
  address payable public beneficiary;
  bool public finalized = false;

  address public owner;
  address public winner;
  mapping(address => uint) public bids;
  address payable[] public accountsList; // so we can iterate: https://ethereum.stackexchange.com/questions/13167/are-there-well-solved-and-simple-storage-patterns-for-solidity

  // THINK: should be (an optional) constructor parameter?
  // For now if you want to change - simply modify the code
  uint public increaseTimeIfBidBeforeEnd = 24 * 60 * 60; // Naming things: https://www.instagram.com/p/BSa_O5zjh8X/
  uint public increaseTimeBy = 24 * 60 * 60;

  event Bid(address indexed winner, uint indexed price, uint indexed timestamp);
  event Refund(address indexed sender, uint indexed amount, uint indexed timestamp);

  modifier onlyOwner { require(owner == msg.sender, "only owner"); _; }
  modifier onlyWinner { require(winner == msg.sender, "only winner"); _; }
  modifier ended { require(now > timestampEnd, "not ended yet"); _; }

  function setDescription(string memory _description) public onlyOwner() {
    description = _description;
  }

  function setInstructions(string memory _instructions) public ended() onlyWinner()  {
    instructions = _instructions;
  }

  constructor(uint _price, string memory _description, uint _timestampEnd, address payable _beneficiary) public {
    require(_timestampEnd > now, "end of the auction must be in the future");
    owner = msg.sender;
    price = _price;
    description = _description;
    timestampEnd = _timestampEnd;
    beneficiary = _beneficiary;
  }

  function() external payable {

    if (msg.value == 0) { // when sending `0` it acts as if it was `withdraw`
      refund();
      return;
    }

    require(now < timestampEnd, "auction has ended"); // sending ether only allowed before the end

    if (bids[msg.sender] > 0) { // First we add the bid to an existing bid
      bids[msg.sender] += msg.value;
    } else {
      bids[msg.sender] = msg.value;
      accountsList.push(msg.sender); // this is out first bid, therefore adding 
    }

    if (initialPrice) {
      require(bids[msg.sender] >= price, "bid too low, minimum is the initial price");
    } else {
      require(bids[msg.sender] >= (price * 5 / 4), "bid too low, minimum 25% increment");
    }

    if (now > timestampEnd - increaseTimeIfBidBeforeEnd) {
      timestampEnd = now + increaseTimeBy;
    }

    initialPrice = false;
    price = bids[msg.sender];
    winner = msg.sender;
    emit Bid(winner, price, now);
  }

  function finalize() public ended() onlyOwner() {
    require(finalized == false, "can withdraw only once");
    require(initialPrice == false, "can withdraw only if there were bids");

    finalized = true; // THINK: DAO hack reentrancy - does it matter which order? (just in case setting it first)
    beneficiary.send(price);

    bids[winner] = 0; // setting it to zero that in the refund loop it is skipped
    for (uint i = 0; i < accountsList.length;  i++) {
      if (bids[accountsList[i]] > 0) {
        accountsList[i].send( bids[accountsList[i]] ); // send? transfer? tell me baby: https://ethereum.stackexchange.com/a/38642/2524
        bids[accountsList[i]] = 0; // in case someone calls `refund` again
      }
    }
  }

  function refund() public {
    require(msg.sender != winner, "winner cannot refund");

    msg.sender.send( bids[msg.sender] );
    emit Refund(msg.sender, bids[msg.sender], now);
    bids[msg.sender] = 0;
  }


  function newbid(address msg_sender, uint256 msg_value, uint256 block_timestamp) public{
      if (msg_value == 0) { // when sending `0` it acts as if it was `withdraw`
        // refund();
        return;
      }
      require(block_timestamp < timestampEnd); // sending ether only allowed before the end

      if (bids[msg_sender] > 0) { // First we add the bid to an existing bid
        bids[msg_sender] += msg_value;
      } else {
        bids[msg_sender] = msg_value;
        // accountsList.push(msg_sender); // this is out first bid, therefore adding 
      }

      if (initialPrice) {
        if(bids[msg_sender] < price)return;
      } else {
        if(bids[msg_sender] < (price * 5 / 4)) return;
      }

      if (block_timestamp > timestampEnd - increaseTimeIfBidBeforeEnd) {
        timestampEnd = block_timestamp + increaseTimeBy;
      }

      initialPrice = false;
      price = bids[msg_sender];
      winner = msg_sender;
      // emit Bid(winner, price, now);
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
 
   function _Main_(address payable msg_sender1, uint p1, uint msg_value1, uint msg_gas1, uint block_timestamp1, address payable msg_sender2, uint p2, uint msg_value2, uint msg_gas2, uint block_timestamp2,address payable msg_sender3, uint p3, uint msg_value3, uint msg_gas3, uint block_timestamp3) public {
           require(!(msg_sender1==winner || msg_sender2 == winner || msg_sender3 == winner));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(initialPrice == false);
           require(price == 0);
           require(timestampEnd == 1000);
           require(increaseTimeBy==100);
           require(increaseTimeIfBidBeforeEnd==10);
      
           require(p1>100000000000 && p1< 900000000000);
           require(p2>100000000000 && p2< 900000000000);
           require(p3>100000000000 && p3< 900000000000);
           require(msg_value1>100000000000 && msg_value1< 900000000000);
           require(msg_value2>100000000000 && msg_value2< 900000000000);
           require(msg_value3>100000000000 && msg_value3< 900000000000);
           
           require(bids[msg_sender1] == 0);
           require(bids[msg_sender2] == 0);
           require(bids[msg_sender3] == 0);

           require(benefits[msg_sender1] == 0);
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
          //  require(msg_value2==p2);
           require(msg_value3==p3);

           // each role claims the 'bid' action.
            newbid(msg_sender1,msg_value1,block_timestamp1);
            newbid(msg_sender2,msg_value2,block_timestamp2);
            newbid(msg_sender3,msg_value3,block_timestamp3);

              // assert(msg_sender3 == winner);
            assert(msg_sender1 == winner || msg_sender2 == winner ||  msg_sender3 == winner );

            uint  winners_count = 0;
            if ( msg_sender1 == winner ){
                        sse_winner(msg_sender1);
                        winners_count ++;
                        utilities[msg_sender1] = p1 - msg_value1;
                        benefits[msg_sender1]  = p1;
                        payments[msg_sender1]  = msg_value1;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == winner ){
                        sse_winner(msg_sender2);
                        winners_count ++;
                        utilities[msg_sender2] = p2 - msg_value1;
                        benefits[msg_sender2]  = p2;
                        payments[msg_sender2]  = msg_value1;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == winner ){
                        sse_winner(msg_sender3);
                        winners_count ++;
                        utilities[msg_sender3] = p3 - msg_value1;
                        benefits[msg_sender3]  = p3;
                        payments[msg_sender3]  = msg_value1;
            }
            sse_utility(utilities[msg_sender3]);

            sse_collusion_violate_check(utilities[msg_sender1] + utilities[msg_sender2], msg_value1, p1, msg_value2, p2);
   }
}