

// contract for implementing the auction in Hot Potato format
contract hotPotatoAuction {
    // The token that is going up for auction

    
    // The total number of bids on the current starship
    uint256 public totalBids;
    
    // starting bid of the starship
    uint256 public startingPrice;
    
    // current Bid amount
    uint256 public highestBid;
    
    // Minimum amount needed to bid on this item
    uint256 public currentMinBid;
    
    // The time at which the auction will end
    uint256 public auctionEnd;
    
    // Variable to store the hot Potato prize for the loser bid
    uint256 public hotPotatoPrize;
    
    // The seller of the current item
    address public seller;
    
    mapping(address=>uint) utilities;
    address public highBidder;
    address public loser;

    constructor(
        uint256 _startingPrice,
        uint256 _auctionEnd
    )
        public
    {
        startingPrice = _startingPrice;
        currentMinBid = _startingPrice;
        totalBids = 0;
        seller = msg.sender;
        auctionEnd = _auctionEnd;
        hotPotatoPrize = _startingPrice;
        highestBid = 0;
    }
    
    mapping(address => uint256) public balanceOf;

    function bid(address msg_sender, uint msg_value, uint msg_gas, uint blocktimestamp) public payable returns(bool ret) {
        require(blocktimestamp < auctionEnd);
        require(msg_value >= startingPrice);
        require (msg_value >= currentMinBid);
        if(totalBids !=0)
        {
            loser = highBidder;

        }
        highBidder = msg_sender;
        
        highestBid = msg_value;
        
        hotPotatoPrize = highestBid/20;
        
        balanceOf[msg_sender] = msg_value + hotPotatoPrize;
        
        if(highestBid < 1000000000000000000)
        {
            currentMinBid = msg_value + highestBid/2;
            hotPotatoPrize = highestBid/20; 
        }
        else
        {
            currentMinBid = msg_value + highestBid/5;
            hotPotatoPrize = highestBid/20;
        }
        
        totalBids = totalBids + 1;
        
        return true;
    }
    function sse_trustful_violate_check(bool expr) public view{}
    function sse_winner(address a) public view {}
    function sse_revenue(uint a) public view {}
    function sse_utility(uint a) public view {}
    function sse_maximize(uint a) public view {}
    function sse_minimize(uint a) public view {}
     function _Main_(address payable msg_sender1, uint p1, uint msg_value1, uint msg_gas1, uint block_timestamp1, address payable msg_sender2, uint p2, uint msg_value2, uint msg_gas2, uint block_timestamp2,address payable msg_sender3, uint p3, uint msg_value3, uint msg_gas3, uint block_timestamp3) public {
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(highestBid==0);
           require(p1 == 600000000000);
           require(p2 == 610000000000);

           utilities[msg_sender1] = 0;
           utilities[msg_sender2] = 0;
           utilities[msg_sender3] = 0;

           // each role claims the 'bid' action at the same time.
            bid(msg_sender1,msg_value1,msg_gas1,block_timestamp1);
            bid(msg_sender2,msg_value2,msg_gas2,block_timestamp2);
            bid(msg_sender3,msg_value3,msg_gas3,block_timestamp3);
            require(msg_value3 == highestBid || msg_value2 == highestBid || msg_value1 == highestBid);
            uint  winners_count = 0;
            if (highestBid>0){
                    if ( msg_value1 == highestBid ){
                        sse_winner(msg_sender1);
                        utilities[msg_sender1] = p1 - highestBid;
                        winners_count ++;
                    }
                    sse_utility(utilities[msg_sender1]);
                    if (msg_value2 == highestBid ){
                        sse_winner(msg_sender2);
                        utilities[msg_sender2] = p2 - highestBid;
                        winners_count ++;
                    }
                    sse_utility(utilities[msg_sender2]);
                    if (msg_value3 == highestBid ){
                        sse_winner(msg_sender3);
                        utilities[msg_sender3] = p3 - highestBid;
                        winners_count ++;
                    }
                    sse_utility(utilities[msg_sender3]);
            }
            if (msg_value1<p1)
                sse_trustful_violate_check(utilities[msg_sender1]>0);
            if (msg_value2<p2)
                sse_trustful_violate_check(utilities[msg_sender2]>0);
            sse_maximize(utilities[msg_sender1]+utilities[msg_sender2] + highestBid*winners_count);
            sse_maximize(utilities[msg_sender1]+utilities[msg_sender2]);
            sse_revenue(highestBid*winners_count);
      }
}