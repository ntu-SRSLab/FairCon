
contract CryptoRomeAuction {

    // Reference to contract tracking NFT ownership
   

    uint256 public auctionStart;
    uint256 public startingPrice;
    uint256 public endingPrice;
    uint256 public auctionEnd;
    uint256 public extensionTime;
    uint256 public highestBid;
    address payable public  highestBidder;
    bytes32 public highestBidderCC;
    bool public highestBidIsCC;
    address payable public  paymentAddress;
    uint256 public tokenId;
    bool public ended;
    
    mapping(address=>uint) refunds;
    
    event Bid(address from, uint256 amount);
    constructor() public {
        // nonFungibleContract = ERC721(_nftAddress);
    }
    // msg_value < (highestBid+duration)
    // highestBid = msg_value
       // highestBid increase pattern 
    
    // highestBidder =  msg_sender
     function bid(address payable msg_sender, uint msg_value, uint msg_gas, uint block_timestamp) public payable{
        if (block_timestamp < auctionStart)
            // return;
            revert();
        if(block_timestamp >= auctionEnd)
            // return;
            revert();
        uint duration = 10000000000;
        // require(msg_value >= (highestBid + duration));
        if (msg_value < (highestBid + duration)){
            return;
            // revert();
        }
        if (highestBid != 0) {
            refunds[highestBidder] += highestBid;
        }

        if (block_timestamp > auctionEnd - extensionTime) {
            auctionEnd = block_timestamp + extensionTime;
        }

        highestBidder = msg_sender;
        highestBid = msg_value;
        highestBidIsCC = false;
        highestBidderCC = "";
        emit Bid(msg_sender, msg_value);
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
           require(!(msg_sender1==highestBidder || msg_sender2 == highestBidder || msg_sender3 == highestBidder));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(extensionTime > 0);
           require(highestBid==0);

           require(p1>100000000000 && p1< 200000000000);
           require(p2>100000000000 && p2< 200000000000);
           require(p3>100000000000 && p3< 200000000000);
           require(msg_value1>100000000000 && msg_value1< 200000000000);
           require(msg_value2>100000000000 && msg_value2< 200000000000);
           require(msg_value3>100000000000 && msg_value3< 200000000000);

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
           require(msg_value3==p3);

           // each role claims the 'bid' action.
            bid(msg_sender1,msg_value1,msg_gas1,block_timestamp1);
            bid(msg_sender2,msg_value2,msg_gas2,block_timestamp2);
            bid(msg_sender3,msg_value3,msg_gas3,block_timestamp3);

              // assert(msg_sender3 == highestBidder);
            assert(msg_sender1 == highestBidder || msg_sender2 == highestBidder ||  msg_sender3 == highestBidder );

            uint  winners_count = 0;
            if ( msg_sender1 == highestBidder ){
                        sse_winner(msg_sender1);
                        winners_count ++;
                        utilities[msg_sender1] = p1 - msg_value1;
                        benefits[msg_sender1]  = p1;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == highestBidder ){
                        sse_winner(msg_sender2);
                        winners_count ++;
                        utilities[msg_sender2] = p2 - msg_value2;
                        benefits[msg_sender2]  = p2;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == highestBidder ){
                        sse_winner(msg_sender3);
                        winners_count ++;
                        utilities[msg_sender3] = p3 - msg_value3;
                        benefits[msg_sender3]  = p3;
            }
            sse_utility(utilities[msg_sender3]);
            sse_collusion_violate_check(utilities[msg_sender1] + utilities[msg_sender2], msg_value1, p1, msg_value2, p2);
            // sse_maximize(utilities[msg_sender1]+utilities[msg_sender2] + highestBid*winners_count);
            // sse_maximize(utilities[msg_sender1]+utilities[msg_sender2]);
            // sse_revenue(highestBid*winners_count);
      }
}