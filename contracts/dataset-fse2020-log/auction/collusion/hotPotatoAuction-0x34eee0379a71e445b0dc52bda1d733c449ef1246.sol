pragma solidity >=0.4.21;

// contract for implementing the auction in Hot Potato format
contract hotPotatoAuction {
    // The token that is going up for auction
    // starShipToken public token;
    
    // The total number of bids on the current starship
    uint256 public totalBids;
    
    // starting bid of the starship
    uint256 public startingPrice;
    
    // current Bid amount
    uint256 public currentBid;
    
    // Minimum amount needed to bid on this item
    uint256 public currentMinBid;
    
    // The time at which the auction will end
    uint256 public auctionEnd;
    
    // Variable to store the hot Potato prize for the loser bid
    uint256 public hotPotatoPrize;
    
    // The seller of the current item
    address payable public seller;
    
    
    address payable public highBidder;
    address payable public loser;

    constructor(
        // starShipToken _token,
        uint256 _startingPrice,
        uint256 _auctionEnd
    )
        public
    {
        // token = _token;
        startingPrice = _startingPrice;
        currentMinBid = _startingPrice;
        totalBids = 0;
        seller = msg.sender;
        auctionEnd = _auctionEnd;
        hotPotatoPrize = _startingPrice;
        currentBid = 0;
    }
    
    mapping(address => uint256) public balanceOf;

    /** 
     *  @dev withdrawBalance from the contract address
     *  @param amount that you want to withdrawBalance
     * 
     */
     
    function withdrawBalance(uint256 amount) public returns(bool ret) {
        require(amount <= address(this).balance);
        require (msg.sender == seller);
        seller.transfer(amount);
        return true;
    }

    /** 
     *  @dev withdraw from the Balance array
     * 
     */
    function withdraw() public returns(bool ret) {
        require(msg.sender != highBidder);
        
        uint256 amount = balanceOf[loser];
        balanceOf[loser] = 0;
        loser.transfer(amount);
        return true;
    }
    

    event Bid(address highBidder, uint256 highBid);

    function bid() public payable returns(bool ret) {
        require(now < auctionEnd);
        require(msg.value >= startingPrice);
        require (msg.value >= currentMinBid);
        
        if(totalBids !=0)
        {
            loser = highBidder;
        
            require(withdraw());
        }
        
        highBidder = msg.sender;
        
        currentBid = msg.value;
        
        hotPotatoPrize = currentBid/20;
        
        balanceOf[msg.sender] = msg.value + hotPotatoPrize;
        
        if(currentBid < 1000000000000000000)
        {
            currentMinBid = msg.value + currentBid/2;
            hotPotatoPrize = currentBid/20; 
        }
        else
        {
            currentMinBid = msg.value + currentBid/5;
            hotPotatoPrize = currentBid/20;
        }
        
        totalBids = totalBids + 1;
        
        return true;
        emit Bid(highBidder, msg.value);
    }

    function resolve() public {
        require(now >= auctionEnd);
        require(msg.sender == seller);
        require (highBidder != address(0));
        
        // require (token.transfer(highBidder));

        balanceOf[seller] += balanceOf[highBidder];
        balanceOf[highBidder] =  0;
        highBidder = address(0);
    }
    /** 
     *  @dev view balance of contract
     */
     
    function getBalanceContract() view public returns(uint ret){
        return address(this).balance;
    }
    
    function newbid(address payable msg_sender, uint msg_value, uint block_timestamp) public payable{
        require(block_timestamp < auctionEnd);
        if (msg_value < startingPrice) return;
        if (msg_value < currentMinBid) return;
        
        if(totalBids !=0)
        {
            loser = highBidder;
        
            // require(withdraw());
        }
        
        highBidder = msg_sender;
        
        currentBid = msg_value;
        
        hotPotatoPrize = currentBid/20;
        
        balanceOf[msg_sender] = msg_value + hotPotatoPrize;
        
        if(currentBid < 400000000000)
        {
            currentMinBid = msg_value + currentBid/2;
            hotPotatoPrize = currentBid/20; 
        }
        else
        {
            currentMinBid = msg_value + currentBid/5;
            hotPotatoPrize = currentBid/20;
        }
        totalBids = totalBids + 1;

        emit Bid(highBidder, msg_value);
        return;
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
           require(!(msg_sender1==highBidder || msg_sender2 == highBidder || msg_sender3 == highBidder));
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(startingPrice==0);
           require(currentMinBid==0);
           require(currentBid==0);
           require(totalBids==0);
           require(balanceOf[msg_sender1] == 0);
           require(balanceOf[msg_sender2] == 0);
           require(balanceOf[msg_sender3] == 0);

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
           require(msg_value3==p3);

           // each role claims the 'bid' action.
            newbid(msg_sender1,msg_value1,block_timestamp1);
            newbid(msg_sender2,msg_value2,block_timestamp2);
            newbid(msg_sender3,msg_value3,block_timestamp3);

              // assert(msg_sender3 == highBidder);
            assert(msg_sender1 == highBidder || msg_sender2 == highBidder ||  msg_sender3 == highBidder );

            uint  winners_count = 0;
            if ( msg_sender1 == highBidder ){
                        sse_winner(msg_sender1);
                        winners_count ++;
                        utilities[msg_sender1] = p1 - currentBid;
                        benefits[msg_sender1]  = p1;
                        payments[msg_sender1]  = currentBid;
                    }
            sse_utility(utilities[msg_sender1]);
            if ( msg_sender2 == highBidder ){
                        sse_winner(msg_sender2);
                        winners_count ++;
                        utilities[msg_sender2] = p2 - currentBid;
                        benefits[msg_sender2]  = p2;
                        payments[msg_sender2]  = currentBid;
            }
            sse_utility(utilities[msg_sender2]);
            if ( msg_sender3 == highBidder ){
                        sse_winner(msg_sender3);
                        winners_count ++;
                        utilities[msg_sender3] = p3 - currentBid;
                        benefits[msg_sender3]  = p3;
                        payments[msg_sender3]  = currentBid;
            }
            sse_utility(utilities[msg_sender3]);

            sse_collusion_violate_check(utilities[msg_sender1] + utilities[msg_sender2], msg_value1, p1, msg_value2, p2);
   }

}