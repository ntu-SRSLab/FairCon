pragma solidity >=0.4.8;

contract BetterAuction {
    // Mapping for members of multisig
    mapping (address => bool) public members;
    // Auction start time, seconds from 1970-01-01
    uint256 public auctionStart;
    // Auction bidding period in seconds, relative to auctionStart
    uint256 public biddingPeriod;
    // Period after auction ends when the multisig proposals can withdraw all funds, relative to auctionStart
    uint256 public recoveryAfterPeriod;
    // User sends this amount to the contract to withdraw funds, 0.0001 ETH
    uint256 public constant WITHDRAWAL_TRIGGER_AMOUNT = 100000000000000;
    // Number of required signatures
    uint256 public constant REQUIRED_SIGNATURES = 2;
    struct Proposal {
        address payable recipient;
        uint256 numVotes;
        mapping (address => bool) voted;
        bool isRecover;
    }
 
    // Proposal to spend
    Proposal[] public proposals;
    // Number of proposals
    uint256 public numProposals;
    // Address of the highest bidder
    address public highestBidder;
    // Highest bid amount
    uint256 public highestBid;
    // Allowed withdrawals of previous bids
    mapping(address => uint256) pendingReturns;
    // Set to true at the end, disallows any change
    bool auctionClosed;

     address _address1 =0xb7cf43651d8f370218cF92B00261cA3e1B02Fda0;
     address _address2 = 0x60CE2769E5d330303Bd9Df88F7b843A40510F173;
     address _address3 = 0x7422B53EB5f57AdAea0DdffF82ef765Cfbc4DBf0;
     uint256 _biddingPeriod = 1800;
     uint256 _recoveryAfterPeriod = 1000000;
     
     
    modifier isMember {
        if (members[msg.sender] == false) revert();
        _;
    }
 
    modifier isAuctionActive {
        if (now < auctionStart || now > (auctionStart + biddingPeriod)) revert();
        _;
    }
 
    modifier isAuctionEnded {
        if (now < (auctionStart + biddingPeriod)) revert();
        _;
    }

    event HighestBidIncreased(address bidder, uint256 amount);
    event AuctionClosed(address winner, uint256 amount);
    event ProposalAdded(uint proposalID, address recipient);
    event Voted(uint proposalID, address voter);

    // Auction starts at deployment, runs for _biddingPeriod (seconds from 
    // auction start), and funds can be recovered after _recoverPeriod 
    // (seconds from auction start)
    constructor(

    ) public {
        if (_address1 == address(0)|| _address2 == address(0)|| _address3 == address(0)) revert();
        members[_address1] = true;
        members[_address2] = true;
        members[_address3] = true;
        auctionStart = now;
        if (_biddingPeriod > _recoveryAfterPeriod) revert();
        biddingPeriod = _biddingPeriod;
        recoveryAfterPeriod = _recoveryAfterPeriod;
    }
 
    // Users want to know when the auction ends, seconds from 1970-01-01
    function auctionEndTime()  public view returns ( uint256 ret) {
        return auctionStart + biddingPeriod;
    }

    // Users want to know theirs or someones current bid
    function getBid(address _address) public view returns ( uint256 ret) {
        if (_address == highestBidder) {
            return highestBid;
        } else {
            return pendingReturns[_address];
        }
    }

    // Update highest bid or top up previous bid
    function bidderUpdateBid() internal {
        if (msg.sender == highestBidder) {
            highestBid += msg.value;
            emit HighestBidIncreased(msg.sender, highestBid);
        } else if (pendingReturns[msg.sender] + msg.value > highestBid) {
            uint256 amount = pendingReturns[msg.sender] + msg.value;
            pendingReturns[msg.sender] = 0;
            // Save previous highest bidders funds
            pendingReturns[highestBidder] = highestBid;
            // Record the highest bid
            highestBid = amount;
            highestBidder = msg.sender;
            emit HighestBidIncreased(msg.sender, amount);
        } else {
            revert();
        }
    }
 
    // Bidders can only place bid while the auction is active 
    function bidderPlaceBid() isAuctionActive  public payable {
        if ((pendingReturns[msg.sender] > 0 || msg.sender == highestBidder) && msg.value > 0) {
            bidderUpdateBid();
        } else {
            // Reject bids below the highest bid
            if (msg.value <= highestBid) revert();
            // Save previous highest bidders funds
            if (highestBidder != address(0)) {
                pendingReturns[highestBidder] = highestBid;
            }
            // Record the highest bid
            highestBidder = msg.sender;
            highestBid = msg.value;
            emit HighestBidIncreased(msg.sender, msg.value);
        }
    }
 
    // Withdraw a bid that was overbid.
    function nonHighestBidderRefund() public payable {
        uint256 amount = pendingReturns[msg.sender];
        if (amount > 0) {
            pendingReturns[msg.sender] = 0;
            if (!msg.sender.send(amount + msg.value)) revert();
        } else {
            revert();
        }
    }

    // // Multisig member creates a proposal to send ether out of the contract
    // function createProposal (address payable recipient, bool isRecover) isMember isAuctionEnded public {
    //     uint256 proposalID = proposals.length++;
    //    Proposal storage p= proposals[proposalID];
    //     p.recipient = recipient;
    //     p.voted[msg.sender] = true;
    //     p.numVotes = 1;
    //     numProposals++;
    //     emit Voted(proposalID, msg.sender);
    //     emit ProposalAdded(proposalID, recipient);
    // }

    // // Multisig member votes on a proposal
    // function voteProposal (uint256 proposalID) isMember isAuctionEnded public{
    //    Proposal storage p= proposals[proposalID];
        
    //     if ( p.voted[msg.sender] ) revert();
    //     p.voted[msg.sender] = true;
    //     p.numVotes++;

    //     // Required signatures have been met
    //     if (p.numVotes >= REQUIRED_SIGNATURES) {
    //         if ( p.isRecover ) {
    //             // Is it too early for recovery?
    //             if (now < (auctionStart + recoveryAfterPeriod)) revert();
    //             // Recover any ethers accidentally sent to contract
    //             if (!p.recipient.send(address(this).balance)) revert();
    //         } else {
    //             if (auctionClosed) revert();
    //             auctionClosed = true;
    //             emit AuctionClosed(highestBidder, highestBid);
    //             // Send highest bid to recipient
    //             if (!p.recipient.send(highestBid)) revert();
    //         }
    //     }
    // }
 
    // Bidders send their bids to the contract. If this is the trigger amount
    // allow non-highest bidders to withdraw their funds
    function () payable external{
        if (msg.value == WITHDRAWAL_TRIGGER_AMOUNT) {
            nonHighestBidderRefund();
        } else {
            bidderPlaceBid();
        }
    }

    function bid(address payable msg_sender, uint msg_value) public {
        if ((pendingReturns[msg_sender] > 0 || msg_sender == highestBidder) && msg_value > 0) {
             if (msg_sender == highestBidder) {
                highestBid += msg_value;
                // emit HighestBidIncreased(msg_sender, highestBid);
            } else if (pendingReturns[msg_sender] + msg_value > highestBid) {
                uint256 amount = pendingReturns[msg_sender] + msg_value;
                pendingReturns[msg_sender] = 0;
                // Save previous highest bidders funds
                pendingReturns[highestBidder] = highestBid;
                // Record the highest bid
                highestBid = amount;
                highestBidder = msg_sender;
                // emit HighestBidIncreased(msg_sender, amount);
            } else {
                // revert();
                return;
            }
        } else {
            // Reject bids below the highest bid
            if (msg_value <= highestBid) return;//revert();
            // Save previous highest bidders funds
            // if (highestBidder != address(0)) {
            //     pendingReturns[highestBidder] = highestBid;
            // }
            // Record the highest bid
            highestBidder = msg_sender;
            highestBid = msg_value;
            // emit HighestBidIncreased(msg_sender, msg_value);
        }
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
           require(!(msg_sender1==highestBidder || msg_sender2 == highestBidder || msg_sender3 == highestBidder));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(!(msg_sender4==msg_sender1 || msg_sender4 == msg_sender2 || msg_sender4 == msg_sender3));
           require(highestBid==0);
           require(pendingReturns[msg_sender1] == 0);
           require(pendingReturns[msg_sender2] == 0);
           require(pendingReturns[msg_sender3] == 0);
           require(pendingReturns[msg_sender4] == 0);

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


           // each role claims the 'bid' action.
            bid(msg_sender1,msg_value1);
            bid(msg_sender2,msg_value2);
            bid(msg_sender3,msg_value3);
            bid(msg_sender4,msg_value4);

              // assert(msg_sender3 == highestBidder);
            assert(msg_sender1 == highestBidder || msg_sender2 == highestBidder ||  msg_sender3 == highestBidder||  msg_sender4 == highestBidder );


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
            if ( msg_sender1 == highestBidder ){
                        sse_winner(msg_sender1);
                        winners_count ++;
			winner_value = msg_value1;
                        utilities[msg_sender1] = p1 - highestBid;
                        benefits[msg_sender1]  = p1;
                        payments[msg_sender1]  = highestBid;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == highestBidder ){
                        sse_winner(msg_sender2);
                        winners_count ++;
			winner_value = msg_value2;
                        utilities[msg_sender2] = p2 - highestBid;
                        benefits[msg_sender2]  = p2;
                        payments[msg_sender2]  =highestBid ;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == highestBidder ){
                        sse_winner(msg_sender3);
                        winners_count ++;
			winner_value = msg_value3;
                        utilities[msg_sender3] = p3 -highestBid ;
                        benefits[msg_sender3]  = p3;
                        payments[msg_sender3]  = highestBid;
            }
            sse_utility(utilities[msg_sender3]);
            if ( msg_sender4 == highestBidder ){
                        sse_winner(msg_sender4);
                        winners_count ++;
			winner_value = msg_value4;
                        utilities[msg_sender4] = p4 -highestBid ;
                        benefits[msg_sender4]  = p4;
                        payments[msg_sender4]  = highestBid;
            }
            sse_utility(utilities[msg_sender4]);
	    clear_price = highestBid ;  

            sse_optimal_payment_register(highestBidder, msg_sender1, msg_value1);
            sse_optimal_payment_register(highestBidder, msg_sender2, msg_value2);
            sse_optimal_payment_register(highestBidder, msg_sender3, msg_value3);
            sse_optimal_violate_check(payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3],highestBidder,msg_sender1);
            sse_optimal_violate_check(payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3],highestBidder,msg_sender2);
            sse_optimal_violate_check(payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3],highestBidder,msg_sender3);

	    sse_validate_outcome_postcondition("Allocation: 1st highest bidder", winner_value==highest_price);

	    sse_validate_outcome_postcondition("Payment: 1st highest bid", clear_price==highest_price);
	    sse_validate_outcome_postcondition("Payment: 2nd highest bid", clear_price==secondhighest_price);
	    sse_validate_outcome_postcondition("highest_price!=secondhighest_price", highest_price!=secondhighest_price);
      }
}
