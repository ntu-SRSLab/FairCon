pragma solidity >=0.4.21;

contract Auction {
    uint bidDivisor = 100;
    uint duration = 20 minutes;

    address payable owner;
    uint public prize;

    uint public bids;
    address public leader;
    uint public deadline;
    bool public claimed;

    constructor() public payable {
        owner = msg.sender;
        prize = msg.value;
        bids = 0;
        leader = msg.sender;
        deadline = now + duration;
        claimed = false;
    }

    function getNextBid() public view returns (uint ret) {
        return (bids + 1) * prize / bidDivisor;
    }

    function bid() public payable {
        require(now <= deadline);
        require(msg.value == getNextBid());
        owner.transfer(msg.value);
        bids++;
        leader = msg.sender;
        deadline = now + duration;
    }

    function claim() public {
        require(now > deadline);
        require(msg.sender == leader);
        require(!claimed);
        claimed = true;
        msg.sender.transfer(prize);
    }

    function newbid(address msg_sender, uint256 msg_value, uint256 block_timestamp) public payable{
        require(block_timestamp <= deadline);
        if(msg_value != (bids + 1) * prize / bidDivisor)return;
        owner.transfer(msg_value);
        bids++;
        leader = msg_sender;
        deadline = block_timestamp + duration;
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
           require(!(msg_sender1==leader || msg_sender2 == leader || msg_sender3 == leader));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(bidDivisor == 100);
           require(duration == 20);
           require(deadline==100);
           require(prize==10000000000000);

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
        //    require(msg_value2==p2);
        //    require(msg_value3==p3);

           // each role claims the 'bid' action.
            newbid(msg_sender1,msg_value1,block_timestamp1);
            newbid(msg_sender2,msg_value2,block_timestamp2);
            newbid(msg_sender3,msg_value3,block_timestamp3);

              // assert(msg_sender3 == leader);
            assert(msg_sender1 == leader || msg_sender2 == leader ||  msg_sender3 == leader );

            uint  winners_count = 0;
            if ( msg_sender1 == leader ){
                        sse_winner(msg_sender1);
                        winners_count ++;
                        utilities[msg_sender1] = p1 - msg_value1;
                        benefits[msg_sender1]  = p1;
                        payments[msg_sender1]  = msg_value1;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == leader ){
                        sse_winner(msg_sender2);
                        winners_count ++;
                        utilities[msg_sender2] = p2 - msg_value1;
                        benefits[msg_sender2]  = p2;
                        payments[msg_sender2]  = msg_value1;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == leader ){
                        sse_winner(msg_sender3);
                        winners_count ++;
                        utilities[msg_sender3] = p3 - msg_value1;
                        benefits[msg_sender3]  = p3;
                        payments[msg_sender3]  = msg_value1;
            }
            sse_utility(utilities[msg_sender3]);

            sse_optimal_payment_register(leader, msg_sender1, msg_value1);
            sse_optimal_payment_register(leader, msg_sender2, msg_value2);
            sse_optimal_payment_register(leader, msg_sender3, msg_value3);
            sse_optimal_violate_check(payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3],leader,msg_sender1);
            sse_optimal_violate_check(payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3],leader,msg_sender2);
            sse_optimal_violate_check(payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3],leader,msg_sender3);
   }
}