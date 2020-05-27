pragma solidity >=0.4.0;
contract Ballot {

    struct Voter {
        uint weight;
        bool voted;
        uint8 vote;
        address delegate;
    }
    struct Proposal {
        uint voteCount;
    }

    address chairperson;
    mapping(address => Voter) voters;
    Proposal[] proposals;

    /// Create a new ballot with $(_numProposals) different proposals.
    constructor(uint8 _numProposals) public {
        chairperson = msg.sender;
        voters[chairperson].weight = 1;
        proposals.length = _numProposals;
    }
  
    /// Give $(toVoter) the right to vote on this ballot.
    /// May only be called by $(chairperson).
    function giveRightToVote(address toVoter) public {
        if (msg.sender != chairperson || voters[toVoter].voted) return;
        voters[toVoter].weight = 1;
    }

    /// Delegate your vote to the voter $(to).
    function delegate(address to) public {
        Voter storage sender = voters[msg.sender]; // assigns reference
        if (sender.voted) return;
        while (voters[to].delegate != address(0) && voters[to].delegate != msg.sender)
            to = voters[to].delegate;
        if (to == msg.sender) return;
        sender.voted = true;
        sender.delegate = to;
        Voter storage delegateTo = voters[to];
        if (delegateTo.voted)
            proposals[delegateTo.vote].voteCount += sender.weight;
        else
            delegateTo.weight += sender.weight;
    }

    /// Give a single vote to proposal $(toProposal).
    function vote(address msg_sender, uint8 toProposal) public {
        if (voters[msg_sender].voted || toProposal >= proposals.length) return;
        voters[msg_sender].voted = true;
        voters[msg_sender].vote = toProposal;
        proposals[toProposal].voteCount += voters[msg_sender].weight;
    }

    function winningProposal() public returns (uint8 _winningProposal) {
        uint256 winningVoteCount = 0;
        for (uint8 prop = 0; prop < proposals.length; prop++)
            if (proposals[prop].voteCount > winningVoteCount) {
                winningVoteCount = proposals[prop].voteCount;
                _winningProposal = prop;
            }
    }
    function newProposal(uint8 _numProposals) public {
        // chairperson = msg.sender;
        // voters[chairperson].weight = 1;
        proposals.length = _numProposals;
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
    function sse_efficient_expectation_register(bool allocation, bool new_allocation, uint benefit) public view {}
    function sse_efficient_violate_check(uint benefit, bool allocation, bool other_allocation) public view {}
    function _Main_(address payable msg_sender1, uint8 p1, uint p1_value, uint p1_rv_value, uint8  msg_value1,
     address payable msg_sender2, uint8 p2, uint p2_value, uint p2_rv_value, uint8 msg_value2, 
     address payable msg_sender3, uint8 p3, uint p3_value, uint p3_rv_value, uint8 msg_value3,
     address payable msg_sender4, uint8 p4, uint p4_value, uint p4_rv_value, uint8 msg_value4,
     address payable msg_sender5, uint8 p5, uint p5_value, uint p5_rv_value, uint8 msg_value5) public {
           require(!(msg_sender1==msg_sender2 || msg_sender1 == msg_sender3 || msg_sender2 == msg_sender3));
           require(!(msg_sender1==msg_sender4 || msg_sender2 == msg_sender4 || msg_sender3 == msg_sender4));
           require(!(msg_sender1==msg_sender5 || msg_sender2 == msg_sender5 || msg_sender3 == msg_sender5));
           require(!(msg_sender4==msg_sender5));
           require(p1_value > p1_rv_value && p1_rv_value > 0);
           require(p2_value > p2_rv_value && p2_rv_value > 0);
           require(p3_value > p3_rv_value && p3_rv_value > 0);
           require(p4_value > p4_rv_value && p4_rv_value > 0);
           require(p5_value > p5_rv_value && p5_rv_value > 0);

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
        
           require(voters[msg_sender1].weight == 1);
           require(voters[msg_sender2].weight == 1);
           require(voters[msg_sender3].weight == 1);
           require(voters[msg_sender4].weight == 1);
           require(voters[msg_sender5].weight == 1);
           require(voters[msg_sender1].voted == false);
           require(voters[msg_sender2].voted == false);
           require(voters[msg_sender3].voted == false);
           require(voters[msg_sender4].voted == false);
           require(voters[msg_sender5].voted == false);
        
        //    require(msg_value1!=p1);
        //    require(msg_value2==p2);
        //    require(msg_value3==p3);
        //    require(msg_value4==p4);
        //    require(msg_value5==p5);

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

            //execute Proposal
            winner = winningProposal();     
            assert(winner == 0||winner==1);

            uint g_false;
            require(g_false == 0);
            if (winner == msg_value1){
                if (msg_value1 == p1){
                    utilities[msg_sender1]  = p1_value;
                }else{
                    utilities[msg_sender1]  = p1_rv_value;
                }
            }else{
                if (msg_value1 == p1){
                    g_false  =  g_false + p1_value;
                }else{
                    g_false  =  g_false + p1_rv_value;
                }
            }
            if (winner == msg_value2){
                if (msg_value2 == p2){
                    utilities[msg_sender2]  = p2_value;
                }else{
                    utilities[msg_sender2]  = p2_rv_value;
                }
            }else{
                if (msg_value2 == p2){
                    g_false  =  g_false + p2_value;
                }else{
                    g_false  =  g_false + p2_rv_value;
                }
            }
            if (winner == msg_value3){
                if (msg_value3 == p3){
                    utilities[msg_sender3]  = p3_value;
                }else{
                    utilities[msg_sender3]  = p3_rv_value;
                }
            }else{
                if (msg_value3 == p3){
                    g_false  =  g_false + p3_value;
                }else{
                    g_false  =  g_false + p3_rv_value;
                }
            }
            if (winner == msg_value4){
                if (msg_value4 == p4){
                    utilities[msg_sender4]  = p4_value;
                }else{
                    utilities[msg_sender4]  = p4_rv_value;
                }
            }else{
                if (msg_value4 == p4){
                    g_false  =  g_false + p4_value;
                }else{
                    g_false  =  g_false + p4_rv_value;
                }
            }
            if ( winner == msg_value5){
                if (msg_value5 == p5){
                    utilities[msg_sender5]  = p5_value;
                }else{
                    utilities[msg_sender5]  = p5_rv_value;
                }
            }else{
                if (msg_value5 == p5){
                    g_false  =  g_false + p5_value;
                }else{
                    g_false  =  g_false + p5_rv_value;
                }
            }
            sse_utility(utilities[msg_sender1]);
            sse_utility(utilities[msg_sender2]);
            sse_utility(utilities[msg_sender3]);
            sse_utility(utilities[msg_sender4]);
            sse_utility(utilities[msg_sender5]);

            sse_efficient_expectation_register((winner==1), !(winner==1), g_false);


            sse_efficient_violate_check(utilities[msg_sender1] +
                                        utilities[msg_sender2] + utilities[msg_sender3] + 
                                        utilities[msg_sender4] + utilities[msg_sender5], 
                                   (winner==1), !(winner==1));

     }
}
