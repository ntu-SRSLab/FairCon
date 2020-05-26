analyzing contract [ Ballot ]
exit contract [ Ballot ]
analyzing contract [ Ballot ]
exit contract [ Ballot ]
state variables: 
	varName: utilities@254, value: utilities@254_0_, sort: (Array String Int)
	varName: proposals@22, value: proposals@22_0_, sort: (Array Int Proposal)
	varName: benefits@258, value: benefits@258_0_, sort: (Array String Int)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: chairperson@15, value: chairperson@15_0_, sort: String
	varName: voters@19, value: voters@19_0_, sort: (Array String Voter)
local variables: 
	varName: p5_rv_value@390, value: p5_rv_value@390_0_, sort: Int
	varName: p5_value@388, value: p5_value@388_0_, sort: Int
	varName: p5@386, value: p5@386_0_, sort: Int
	varName: msg_sender5@384, value: msg_sender5@384_0_, sort: String
	varName: p4_rv_value@380, value: p4_rv_value@380_0_, sort: Int
	varName: p4_value@378, value: p4_value@378_0_, sort: Int
	varName: p4@376, value: p4@376_0_, sort: Int
	varName: msg_sender4@374, value: msg_sender4@374_0_, sort: String
	varName: msg_value3@372, value: msg_value3@372_0_, sort: Int
	varName: msg_sender3@364, value: msg_sender3@364_0_, sort: String
	varName: msg_value2@362, value: msg_value2@362_0_, sort: Int
	varName: p2_rv_value@360, value: p2_rv_value@360_0_, sort: Int
	varName: p2_value@358, value: p2_value@358_0_, sort: Int
	varName: p2@356, value: p2@356_0_, sort: Int
	varName: msg_sender2@354, value: msg_sender2@354_0_, sort: String
	varName: msg_value1@352, value: msg_value1@352_0_, sort: Int
	varName: p3_rv_value@370, value: p3_rv_value@370_0_, sort: Int
	varName: a@278, value: a@278_0_, sort: Int
	varName: a@272, value: a@272_0_, sort: Int
	varName: msg_value5@392, value: msg_value5@392_0_, sort: Int
	varName: prop@207, value: prop@207_0_, sort: Int
	varName: a@266, value: a@266_0_, sort: Int
	varName: benefit@324, value: benefit@324_0_, sort: Int
	varName: a@260, value: a@260_0_, sort: Int
	varName: sender@76, value: sender@76_0_, sort: Voter
	varName: winner@622, value: winner@622_0_, sort: Int
	varName: _numProposals@240, value: _numProposals@240_0_, sort: Int
	varName: toProposal@158, value: toProposal@158_0_, sort: Int
	varName: benefit@318, value: benefit@318_0_, sort: Int
	varName: p3@366, value: p3@366_0_, sort: Int
	varName: winningVoteCount@203, value: winningVoteCount@203_0_, sort: Int
	varName: other_allocation@328, value: other_allocation@328_0_, sort: String
	varName: _numProposals@24, value: _numProposals@24_0_, sort: Int
	varName: u@290, value: u@290_0_, sort: Int
	varName: a@284, value: a@284_0_, sort: Int
	varName: to@72, value: to@72_0_, sort: String
	varName: delegateTo@129, value: delegateTo@129_0_, sort: Voter
	varName: a@292, value: a@292_0_, sort: Int
	varName: _winningProposal@200, value: _winningProposal@200_0_, sort: Int
	varName: allocation@336, value: allocation@336_0_, sort: String
	varName: p3_value@368, value: p3_value@368_0_, sort: Int
	varName: v1@302, value: v1@302_0_, sort: Int
	varName: v2@306, value: v2@306_0_, sort: Int
	varName: msg_value4@382, value: msg_value4@382_0_, sort: Int
	varName: toVoter@48, value: toVoter@48_0_, sort: String
	varName: p1_value@348, value: p1_value@348_0_, sort: Int
	varName: p1_rv_value@350, value: p1_rv_value@350_0_, sort: Int
	varName: v_1@304, value: v_1@304_0_, sort: Int
	varName: v_2@308, value: v_2@308_0_, sort: Int
	varName: allocation@314, value: allocation@314_0_, sort: String
	varName: b@294, value: b@294_0_, sort: Int
	varName: player@316, value: player@316_0_, sort: String
	varName: u12@300, value: u12@300_0_, sort: Int
	varName: msg_sender1@344, value: msg_sender1@344_0_, sort: String
	varName: benefit@334, value: benefit@334_0_, sort: Int
	varName: allocation@326, value: allocation@326_0_, sort: String
	varName: msg_sender@156, value: msg_sender@156_0_, sort: String
	varName: other_allocation@338, value: other_allocation@338_0_, sort: String
	varName: p1@346, value: p1@346_0_, sort: Int
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
symbolically execute function [_Main_]
CHECK PASS FAILED 0
CHECK PASS FAILED 1
CHECK PASS FAILED 2
CHECK PASS FAILED 3
CHECK PASS FAILED 4
CHECK PASS FAILED 5
CHECK PASS FAILED 6
CHECK PASS FAILED 7
CHECK PASS FAILED 8
CHECK PASS FAILED 9
CHECK PASS FAILED 10
CHECK PASS FAILED 11
CHECK PASS FAILED 12
CHECK PASS FAILED 13
CHECK PASS FAILED 14
CHECK PASS FAILED 15
CHECK PASS FAILED 16
CHECK PASS FAILED 17
CHECK PASS FAILED 18
CHECK PASS FAILED 19
CHECK PASS FAILED 20
CHECK PASS FAILED 21
CHECK PASS FAILED 22
CHECK PASS FAILED 23
CHECK PASS FAILED 24
CHECK PASS FAILED 25
CHECK PASS FAILED 26
CHECK PASS FAILED 27
CHECK PASS FAILED 28
CHECK PASS FAILED 29
CHECK PASS FAILED 30
CHECK PASS FAILED 31
Using Z3 solver to optimize value expression
-------------------------------------------------------------------------
-------------------------------------------------------------------------
-------------------------------------------------------------------------
--------------------------------OUTCOME-------------------------------------
|truthful violate check        |value                                   |
-------------------------------------------------------------------------
|collusion violate check       |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |Noncolluded                             |
-------------------------------------------------------------------------
|effecient violate check       |value                                   |
-------------------------------------------------------------------------
|optimal violate check         |value                                   |
**************************************
*    outcome pattern                 *
**************************************
*************************************
*         report                    *
*************************************
* model construction time: 1203.91s
*  property checking time: 3.919s
*              total time: 1207.83s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:3279-0
*collusion-free:3279-0
*       optimal:3279-0
*     efficient:3279-0
*************************************
