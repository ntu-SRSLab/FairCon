pragma solidity >=0.4.22 <0.7.0;

// /// @title Voting with delegation.
// contract Ballot {
//     // This declares a new complex type which will
//     // be used for variables later.
//     // It will represent a single voter.
//     struct Voter {
//         uint weight; // weight is accumulated by delegation
//         bool voted;  // if true, that person already voted
//         address delegate; // person delegated to
//         uint vote;   // index of the voted proposal
//     }

//     // This is a type for a single proposal.
//     struct Proposal {
//         bytes32 name;   // short name (up to 32 bytes)
//         uint voteCount; // number of accumulated votes
//     }

//     address public chairperson;

//     // This declares a state variable that
//     // stores a `Voter` struct for each possible address.
//     mapping(address => Voter) public voters;

//     // A dynamically-sized array of `Proposal` structs.
//     Proposal[] public proposals;

//     /// Create a new ballot to choose one of `proposalNames`.
//     constructor(bytes32[] memory proposalNames) public {
//         chairperson = msg.sender;
//         voters[chairperson].weight = 1;

//         // For each of the provided proposal names,
//         // create a new proposal object and add it
//         // to the end of the array.
//         for (uint i = 0; i < proposalNames.length; i++) {
//             // `Proposal({...})` creates a temporary
//             // Proposal object and `proposals.push(...)`
//             // appends it to the end of `proposals`.
//             proposals.push(Proposal({
//                 name: proposalNames[i],
//                 voteCount: 0
//             }));
//         }
//     }

//     // Give `voter` the right to vote on this ballot.
//     // May only be called by `chairperson`.
//     function giveRightToVote(address voter) public {
//         // If the first argument of `require` evaluates
//         // to `false`, execution terminates and all
//         // changes to the state and to Ether balances
//         // are reverted.
//         // This used to consume all gas in old EVM versions, but
//         // not anymore.
//         // It is often a good idea to use `require` to check if
//         // functions are called correctly.
//         // As a second argument, you can also provide an
//         // explanation about what went wrong.
//         require(
//             msg.sender == chairperson,
//             "Only chairperson can give right to vote."
//         );
//         require(
//             !voters[voter].voted,
//             "The voter already voted."
//         );
//         require(voters[voter].weight == 0);
//         voters[voter].weight = 1;
//     }

//     /// Delegate your vote to the voter `to`.
//     function delegate(address to) public {
//         // assigns reference
//         Voter storage sender = voters[msg.sender];
//         require(!sender.voted, "You already voted.");

//         require(to != msg.sender, "Self-delegation is disallowed.");

//         // Forward the delegation as long as
//         // `to` also delegated.
//         // In general, such loops are very dangerous,
//         // because if they run too long, they might
//         // need more gas than is available in a block.
//         // In this case, the delegation will not be executed,
//         // but in other situations, such loops might
//         // cause a contract to get "stuck" completely.
//         while (voters[to].delegate != address(0)) {
//             to = voters[to].delegate;

//             // We found a loop in the delegation, not allowed.
//             require(to != msg.sender, "Found loop in delegation.");
//         }

//         // Since `sender` is a reference, this
//         // modifies `voters[msg.sender].voted`
//         sender.voted = true;
//         sender.delegate = to;
//         Voter storage delegate_ = voters[to];
//         if (delegate_.voted) {
//             // If the delegate already voted,
//             // directly add to the number of votes
//             proposals[delegate_.vote].voteCount += sender.weight;
//         } else {
//             // If the delegate did not vote yet,
//             // add to her weight.
//             delegate_.weight += sender.weight;
//         }
//     }

//     /// Give your vote (including votes delegated to you)
//     /// to proposal `proposals[proposal].name`.
//     function vote(uint proposal) public {
//         Voter storage sender = voters[msg.sender];
//         require(sender.weight != 0, "Has no right to vote");
//         require(!sender.voted, "Already voted.");
//         sender.voted = true;
//         sender.vote = proposal;

//         // If `proposal` is out of the range of the array,
//         // this will throw automatically and revert all
//         // changes.
//         proposals[proposal].voteCount += sender.weight;
//     }

//     /// @dev Computes the winning proposal taking all
//     /// previous votes into account.
//     function winningProposal() public view
//             returns (uint winningProposal_)
//     {
//         uint winningVoteCount = 0;
//         for (uint p = 0; p < proposals.length; p++) {
//             if (proposals[p].voteCount > winningVoteCount) {
//                 winningVoteCount = proposals[p].voteCount;
//                 winningProposal_ = p;
//             }
//         }
//     }

//     // Calls winningProposal() function to get the index
//     // of the winner contained in the proposals array and then
//     // returns the name of the winner
//     function winnerName() public view
//             returns (bytes32 winnerName_)
//     {
//         winnerName_ = proposals[winningProposal()].name;
//     }


// }

contract Rewrite{
     // This declares a new complex type which will
    // be used for variables later.
    // It will represent a single voter.
    struct Voter {
        uint weight; // weight is accumulated by delegation
        bool voted;  // if true, that person already voted
        address delegate; // person delegated to
        uint vote;   // index of the voted proposal
    }

    // This is a type for a single proposal.
    struct Proposal {
        bytes32 name;   // short name (up to 32 bytes)
        uint voteCount; // number of accumulated votes
    }

    address public chairperson;

    // This declares a state variable that
    // stores a `Voter` struct for each possible address.
    mapping(address => Voter) public voters;

    // A dynamically-sized array of `Proposal` structs.
    Proposal[] public proposals;
    
    function newProposal(uint numOfProposal) public {
        proposals.length = numOfProposal;
    }

    function vote(address msg_sender, uint proposal) public {
        // Voter storage sender = voters[msg_sender];
        require(voters[msg_sender].weight != 0);
        require(voters[msg_sender].voted == false);
        voters[msg_sender].voted = true;
        voters[msg_sender].vote = proposal;

        // If `proposal` is out of the range of the array,
        // this will throw automatically and revert all
        // changes.
        proposals[proposal].voteCount = proposals[proposal].voteCount  + voters[msg_sender].weight;
    }


    function winningProposal() public view
            returns (uint winningProposal_)
    {
        uint winningVoteCount = 0;
        for (uint p = 0; p < proposals.length; ) {
            if (proposals[p].voteCount > winningVoteCount) {
                winningVoteCount = proposals[p].voteCount;
                winningProposal_ = p;
                p = p + 1; 
            }
        }
        return winningProposal_;
    }

    mapping(address=>uint) utilities;
    mapping(address=>uint) benefits;
    function sse_winner(int a) public view {}
    function sse_revenue(uint a) public view {}
    function sse_utility(uint a) public view {}
    function sse_maximize(uint a) public view {}
    function sse_minimize(uint a) public view {}
    function sse_truthful_violate_check(uint u, uint8 a, uint8 b) public view {}
    function sse_collusion_violate_check(uint u12, uint v1, uint v_1, uint v2, uint v_2) public view{}
    function sse_efficient_expectation_register(address allocation, address player, uint benefit) public view {}
    function sse_efficient_violate_check(uint benefit, address allocation, address other_allocation) public view {}
    function sse_optimal_violate_check(uint benefit, address allocation, address other_allocation) public view {}
    function _Main_(address payable msg_sender1, uint8 p1, uint p1_value, uint p1_rv_value, uint8  msg_value1,
     address payable msg_sender2, uint8 p2, uint p2_value, uint p2_rv_value, uint8 msg_value2, 
     address payable msg_sender3, uint8 p3, uint p3_value, uint p3_rv_value, uint8 msg_value3,
     address payable msg_sender4, uint8 p4, uint p4_value, uint p4_rv_value, uint8 msg_value4,
     address payable msg_sender5, uint8 p5, uint p5_value, uint p5_rv_value, uint8 msg_value5) public {
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(!(msg_sender1==msg_sender4 || msg_sender2 == msg_sender4 || msg_sender3 == msg_sender4));
           require(!(msg_sender1==msg_sender5 || msg_sender2 == msg_sender5 || msg_sender3 == msg_sender5));
           require(!(msg_sender4==msg_sender5));
           require(p1_value==1&&p1_value > p1_rv_value && p1_rv_value ==0);
           require(p2_value==1&&p2_value > p2_rv_value && p2_rv_value ==0);
           require(p3_value==1&&p3_value > p3_rv_value && p3_rv_value ==0);
           require(p4_value==1&&p4_value > p4_rv_value && p4_rv_value ==0);
           require(p5_value==1&&p5_value > p5_rv_value && p5_rv_value ==0);

           require(p1 ==0||p1==1);
           require(p2 ==0||p2==1);
           require(p3 ==0||p3==1);
           require(p4 ==0||p4==1);
           require(p5 ==0||p5==1);

           require(msg_value1 ==0||msg_value1==1);
           require(msg_value2 ==0||msg_value2==1);
           require(msg_value3 ==0||msg_value3==1);
           require(msg_value4 ==0||msg_value4==1);
           require(msg_value5 ==0||msg_value5==1);
        
           int winner;
           require(winner==-1);

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
           newProposal(2);
           require(proposals[0].voteCount == 0);
           require(proposals[1].voteCount == 0);
           // votes
          
           vote(msg_sender1,msg_value1);
           vote(msg_sender2,msg_value2);
           vote(msg_sender3,msg_value3);
           vote(msg_sender4,msg_value4);
           vote(msg_sender5,msg_value5);
           
            // assert(winner == 0 || winner == 1);   

            if (winner == msg_value1){
                if (msg_value1 == p1){
                    utilities[msg_sender1]  = p1_value;
                }else{
                    utilities[msg_sender1]  = p1_rv_value;
                }
            }
            if (winner== msg_value2){
                if (msg_value2 == p2){
                    utilities[msg_sender2]  = p2_value;
                }else{
                    utilities[msg_sender2]  = p2_rv_value;
                }
            }
            if (winner== msg_value3){
                if (msg_value3 == p3){
                    utilities[msg_sender3]  = p3_value;
                }else{
                    utilities[msg_sender3]  = p3_rv_value;
                }
            }
            if (winner== msg_value4){
                if (msg_value4 == p4){
                    utilities[msg_sender4]  = p4_value;
                }else{
                    utilities[msg_sender4]  = p4_rv_value;
                }
            }
            if (winner== msg_value5){
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

            sse_truthful_violate_check(utilities[msg_sender1],msg_value1, p1);

     }
}
