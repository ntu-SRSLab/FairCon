pragma solidity >=0.4.16;
// ////////////////////////////////////////////////////////////
// // Initiated by : Rimdeika Consulting and Coaching AB (RCC)
// //                Alingsas SWEDEN / VAT Nr. SE556825809801
// ////////////////////////////////////////////////////////////
// //
// // "Decentralized R&D organization on the blockchain with 
// // the mission to develop autonomous diagnostic, support 
// // and development system for any vehicle"
// //
// ////////////////////////////////////////////////////////////

// contract owned {
//     address public owner;

//     constructor() public {
//         owner = msg.sender;
//     }

//     modifier onlyOwner {
//         require(msg.sender == owner);
//         _;
//     }

//     function transferOwnership(address newOwner) onlyOwner public {
//         owner = newOwner;
//     }
// }

// contract tokenRecipient {
//     event receivedEther(address sender, uint amount);
//     event receivedTokens(address _from, uint256 _value, address _token, bytes _extraData);

//     function receiveApproval(address _from, uint256 _value, address _token, bytes _extraData) public {
//         Token t = Token(_token);
//         require(t.transferFrom(_from, this, _value));
//         emit receivedTokens(_from, _value, _token, _extraData);
//     }

//     function () payable public {
//         emit receivedEther(msg.sender, msg.value);
//     }
// }

// contract Token {
//     mapping (address => uint256) public balanceOf;
//     function transferFrom(address _from, address _to, uint256 _value) public returns (bool success);
// }

// /**
//  * The shareholder association contract itself
//  */
// contract Association is owned, tokenRecipient {

//     uint public minimumQuorum;
//     uint public debatingPeriodInMinutes;
//     struct Vote {
//         bool inSupport;
//         address voter;
//     }
//     struct Proposal {
//         address recipient;
//         uint amount;
//         string description;
//         uint minExecutionDate;
//         bool executed;
//         bool proposalPassed;
//         uint numberOfVotes;
//         bytes32 proposalHash;
//         Vote[] votes;
//         mapping (address => bool) voted;
//     }
//     Proposal[] public proposals;
//     uint public numProposals;
//     Token public sharesTokenAddress;

//     event ProposalAdded(uint proposalID, address recipient, uint amount, string description);
//     event Voted(uint proposalID, bool position, address voter);
//     event ProposalTallied(uint proposalID, uint result, uint quorum, bool active);
//     event ChangeOfRules(uint newMinimumQuorum, uint newDebatingPeriodInMinutes, address newSharesTokenAddress);



//     // Modifier that allows only shareholders to vote and create new proposals
//     modifier onlyShareholders {
//         require(sharesTokenAddress.balanceOf(msg.sender) > 0);
//         _;
//     }

//     /**
//      * Constructor function
//      *
//      * First time setup
//      */
//     constructor(Token sharesAddress, uint minimumSharesToPassAVote, uint minutesForDebate) payable public {
//         changeVotingRules(sharesAddress, minimumSharesToPassAVote, minutesForDebate);
//     }

//     /**
//      * Change voting rules
//      *
//      * Make so that proposals need to be discussed for at least `minutesForDebate/60` hours
//      * and all voters combined must own more than `minimumSharesToPassAVote` shares of token `sharesAddress` to be executed
//      *
//      * @param sharesAddress token address
//      * @param minimumSharesToPassAVote proposal can vote only if the sum of shares held by all voters exceed this number
//      * @param minutesForDebate the minimum amount of delay between when a proposal is made and when it can be executed
//      */
//     function changeVotingRules(Token sharesAddress, uint minimumSharesToPassAVote, uint minutesForDebate) onlyOwner public {
//         sharesTokenAddress = Token(sharesAddress);
//         if (minimumSharesToPassAVote == 0 ) minimumSharesToPassAVote = 1;
//         minimumQuorum = minimumSharesToPassAVote;
//         debatingPeriodInMinutes = minutesForDebate;
//         emit ChangeOfRules(minimumQuorum, debatingPeriodInMinutes, sharesTokenAddress);
//     }

//     /**
//      * Add Proposal
//      *
//      * Propose to send `weiAmount / 1e18` ether to `beneficiary` for `jobDescription`. `transactionBytecode ? Contains : Does not contain` code.
//      *
//      * @param beneficiary who to send the ether to
//      * @param weiAmount amount of ether to send, in wei
//      * @param jobDescription Description of job
//      * @param transactionBytecode bytecode of transaction
//      */
//     function newProposal(
//         address beneficiary,
//         uint weiAmount,
//         string jobDescription,
//         bytes transactionBytecode
//     )
//         onlyShareholders public
//         returns (uint proposalID)
//     {
//         proposalID = proposals.length++;
//         Proposal storage p = proposals[proposalID];
//         p.recipient = beneficiary;
//         p.amount = weiAmount;
//         p.description = jobDescription;
//         p.proposalHash = keccak256(abi.encodePacked(beneficiary, weiAmount, transactionBytecode));
//         p.minExecutionDate = now + debatingPeriodInMinutes * 1 minutes;
//         p.executed = false;
//         p.proposalPassed = false;
//         p.numberOfVotes = 0;
//         emit ProposalAdded(proposalID, beneficiary, weiAmount, jobDescription);
//         numProposals = proposalID+1;

//         return proposalID;
//     }

//     /**
//      * Add proposal in Ether
//      *
//      * Propose to send `etherAmount` ether to `beneficiary` for `jobDescription`. `transactionBytecode ? Contains : Does not contain` code.
//      * This is a convenience function to use if the amount to be given is in round number of ether units.
//      *
//      * @param beneficiary who to send the ether to
//      * @param etherAmount amount of ether to send
//      * @param jobDescription Description of job
//      * @param transactionBytecode bytecode of transaction
//      */
//     function newProposalInEther(
//         address beneficiary,
//         uint etherAmount,
//         string jobDescription,
//         bytes transactionBytecode
//     )
//         onlyShareholders public
//         returns (uint proposalID)
//     {
//         return newProposal(beneficiary, etherAmount * 1 ether, jobDescription, transactionBytecode);
//     }

//     /**
//      * Check if a proposal code matches
//      *
//      * @param proposalNumber ID number of the proposal to query
//      * @param beneficiary who to send the ether to
//      * @param weiAmount amount of ether to send
//      * @param transactionBytecode bytecode of transaction
//      */
//     function checkProposalCode(
//         uint proposalNumber,
//         address beneficiary,
//         uint weiAmount,
//         bytes transactionBytecode
//     )
//         constant public
//         returns (bool codeChecksOut)
//     {
//         Proposal storage p = proposals[proposalNumber];
//         return p.proposalHash == keccak256(abi.encodePacked(beneficiary, weiAmount, transactionBytecode));
//     }

//     /**
//      * Log a vote for a proposal
//      *
//      * Vote `supportsProposal? in support of : against` proposal #`proposalNumber`
//      *
//      * @param proposalNumber number of proposal
//      * @param supportsProposal either in favor or against it
//      */
//     function vote(
//         uint proposalNumber,
//         bool supportsProposal
//     )
//         onlyShareholders public
//         returns (uint voteID)
//     {
//         Proposal storage p = proposals[proposalNumber];
//         require(p.voted[msg.sender] != true);

//         voteID = p.votes.length++;
//         p.votes[voteID] = Vote({inSupport: supportsProposal, voter: msg.sender});
//         p.voted[msg.sender] = true;
//         p.numberOfVotes = voteID +1;
//         emit Voted(proposalNumber,  supportsProposal, msg.sender);
//         return voteID;
//     }

//     /**
//      * Finish vote
//      *
//      * Count the votes proposal #`proposalNumber` and execute it if approved
//      *
//      * @param proposalNumber proposal number
//      * @param transactionBytecode optional: if the transaction contained a bytecode, you need to send it
//      */
//     function executeProposal(uint proposalNumber, bytes transactionBytecode) public {
//         Proposal storage p = proposals[proposalNumber];

//         require(now > p.minExecutionDate                                             // If it is past the voting deadline
//             && !p.executed                                                          // and it has not already been executed
//             && p.proposalHash == keccak256(abi.encodePacked(p.recipient, p.amount, transactionBytecode))); // and the supplied code matches the proposal...


//         // ...then tally the results
//         uint quorum = 0;
//         uint yea = 0;
//         uint nay = 0;

//         for (uint i = 0; i <  p.votes.length; ++i) {
//             Vote storage v = p.votes[i];
//             uint voteWeight = sharesTokenAddress.balanceOf(v.voter);
//             quorum += voteWeight;
//             if (v.inSupport) {
//                 yea += voteWeight;
//             } else {
//                 nay += voteWeight;
//             }
//         }

//         require(quorum >= minimumQuorum); // Check if a minimum quorum has been reached

//         if (yea > nay ) {
//             // Proposal passed; execute the transaction

//             p.executed = true;
//             require(p.recipient.call.value(p.amount)(transactionBytecode));

//             p.proposalPassed = true;
//         } else {
//             // Proposal failed
//             p.proposalPassed = false;
//         }

//         // Fire Events
//         emit ProposalTallied(proposalNumber, yea - nay, quorum, p.proposalPassed);
//     }

   
// }

contract Rewrite{
    struct Vote {
        bool inSupport;
        address voter;
    }
    struct Proposal {
        bool executed;
        bool proposalPassed;
        uint numberOfVotes;
        Vote[] votes;
        mapping(address=>bool) voted;
    }
    Proposal proposal;
    uint voteCount;
    function newProposal() public{
            proposal.executed = false;
            proposal.proposalPassed = false;
            proposal.numberOfVotes = 0;
    }
    function vote(address msg_sender, bool supportsProposal) public{
        require(proposal.voted[msg_sender] != true);
        // proposal.votes[voteCount] = Vote({inSupport: supportsProposal, voter: msg_sender});
        proposal.votes[voteCount].inSupport =  supportsProposal;
        proposal.votes[voteCount].voter = msg_sender;
        proposal.voted[msg_sender] = true;
        voteCount = voteCount + 1;
        proposal.numberOfVotes = voteCount;
    }
    function executeProposal() public {
        uint quorum = 0;
        uint yea = 0;
        uint nay = 0;
        require( quorum == 0);
        require( yea == 0);
        require( nay == 0);
        for (uint i = 0; i <  voteCount; ++i) {
            uint voteWeight = 1;
            quorum += voteWeight;
            if (proposal.votes[i].inSupport) {
                yea += voteWeight;
            } else {
                nay += voteWeight;
            }
        }
        if (yea > nay ) {
            // Proposal passed; execute the transaction
            proposal.proposalPassed = true;
        } else {
            // Proposal failed
            proposal.proposalPassed = false;
        }
        proposal.executed = true;
    }
    mapping(address=>uint) utilities;
    mapping(address=>uint) benefits;
    function sse_winner(bool a) public view {}
    function sse_revenue(uint a) public view {}
    function sse_utility(uint a) public view {}
    function sse_maximize(uint a) public view {}
    function sse_minimize(uint a) public view {}
    function sse_truthful_violate_check(uint u, bool a, bool b) public view {}
    function sse_collusion_violate_check(uint u12, uint v1, uint v_1, uint v2, uint v_2) public view{}
    function sse_efficient_expectation_register(address allocation, address player, uint benefit) public view {}
    function sse_efficient_violate_check(uint benefit, address allocation, address other_allocation) public view {}
    function sse_optimal_violate_check(uint benefit, address allocation, address other_allocation) public view {}
    function _Main_(address payable msg_sender1, bool p1, uint p1_value, uint p1_rv_value, bool msg_value1,
     address payable msg_sender2, bool p2, uint p2_value, uint p2_rv_value, bool msg_value2, 
     address payable msg_sender3, bool p3, uint p3_value, uint p3_rv_value, bool msg_value3,
     address payable msg_sender4, bool p4, uint p4_value, uint p4_rv_value, bool msg_value4,
     address payable msg_sender5, bool p5, uint p5_value, uint p5_rv_value, bool msg_value5) public {
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(!(msg_sender1==msg_sender4 || msg_sender2 == msg_sender4 || msg_sender3 == msg_sender4));
           require(!(msg_sender1==msg_sender5 || msg_sender2 == msg_sender5 || msg_sender3 == msg_sender5));
           require(!(msg_sender4==msg_sender5));
           require(p1_value==1&&p1_value > p1_rv_value && p1_rv_value ==0);
           require(p2_value==1&&p2_value > p2_rv_value && p2_rv_value ==0);
           require(p3_value==1&&p3_value > p3_rv_value && p3_rv_value ==0);
           require(p4_value==1&&p4_value > p4_rv_value && p4_rv_value ==0);
           require(p5_value==1&&p5_value > p5_rv_value && p5_rv_value ==0);
         
           require(voteCount==0);
           require(proposal.executed  == false);


           require(utilities[msg_sender1] == 0);
           require(utilities[msg_sender2] == 0);
           require(utilities[msg_sender3] == 0);
           require(utilities[msg_sender4] == 0);
           require(utilities[msg_sender5] == 0);
        
        
        //    require(msg_value1!=p1);
           require(msg_value2==p2);
           require(msg_value3==p3);
           require(msg_value4==p4);
           require(msg_value5==p5);

           // new proposal first
           newProposal();
           // votes
        //    if (msg_value1==false){
        //         vote(msg_sender1, false);
        //    }else{
        //         vote(msg_sender1, true);
        //    }
        //    if (msg_value2==false){
        //         vote(msg_sender2, false);
        //    }else{
        //         vote(msg_sender2, true);
        //    }
        //    if (msg_value3==false){
        //         vote(msg_sender3, false);
        //    }else{
        //         vote(msg_sender3, true);
        //    }
        //    if (msg_value4==false){
        //         vote(msg_sender4, false);
        //    }else{
        //         vote(msg_sender4, true);
        //    }
        //    if (msg_value5==false){
        //         vote(msg_sender5, false);
        //    }else{
        //         vote(msg_sender5, true);
        //    }
           vote(msg_sender1, msg_value1);
           vote(msg_sender2, msg_value2);
           vote(msg_sender3, msg_value3);
           vote(msg_sender4, msg_value4);
           vote(msg_sender5, msg_value5);  
           //execute Proposal
           executeProposal();     
                  
           assert(proposal.executed  == true);

       
          if ((proposal.proposalPassed==true) == msg_value1){
                if (msg_value1 == p1){
                    utilities[msg_sender1]  = p1_value;
                }else{
                    utilities[msg_sender1]  = p1_rv_value;
                }
            }
            if (proposal.proposalPassed == msg_value2){
                if (msg_value2 == p2){
                    utilities[msg_sender2]  = p2_value;
                }else{
                    utilities[msg_sender2]  = p2_rv_value;
                }
            }
            if (proposal.proposalPassed == msg_value3){
                if (msg_value1 == p3){
                    utilities[msg_sender3]  = p3_value;
                }else{
                    utilities[msg_sender3]  = p3_rv_value;
                }
            }
            if (proposal.proposalPassed == msg_value4){
                if (msg_value1 == p4){
                    utilities[msg_sender4]  = p4_value;
                }else{
                    utilities[msg_sender4]  = p4_rv_value;
                }
            }
            if (proposal.proposalPassed == msg_value5){
                if (msg_value5 == p5){
                    utilities[msg_sender5]  = p5_value;
                }else{
                    utilities[msg_sender5]  = p5_rv_value;
                }
            }
            sse_utility(utilities[msg_sender1]);
            sse_utility(utilities[msg_sender2]);
            sse_utility(utilities[msg_sender3]);
            sse_utility(utilities[msg_sender4]);
            sse_utility(utilities[msg_sender5]);
            sse_winner(proposal.proposalPassed);

            sse_truthful_violate_check(utilities[msg_sender1],msg_value1, p1);

     }
}
