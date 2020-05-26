analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: utilities@181, value: utilities@181_0_, sort: (Array String Int)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: benefits@185, value: benefits@185_0_, sort: (Array String Int)
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: voteCount@24, value: voteCount@24_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: proposal@22, value: proposal@22_0_, sort: Proposal
local variables: 
	varName: p5_rv_value@317, value: p5_rv_value@317_0_, sort: Int
	varName: p5_value@315, value: p5_value@315_0_, sort: Int
	varName: p5@313, value: p5@313_0_, sort: Bool
	varName: p4_rv_value@307, value: p4_rv_value@307_0_, sort: Int
	varName: p4_value@305, value: p4_value@305_0_, sort: Int
	varName: msg_sender4@301, value: msg_sender4@301_0_, sort: String
	varName: msg_value3@299, value: msg_value3@299_0_, sort: Bool
	varName: msg_sender5@311, value: msg_sender5@311_0_, sort: String
	varName: p4@303, value: p4@303_0_, sort: Bool
	varName: p3@293, value: p3@293_0_, sort: Bool
	varName: msg_sender3@291, value: msg_sender3@291_0_, sort: String
	varName: msg_value2@289, value: msg_value2@289_0_, sort: Bool
	varName: p2_value@285, value: p2_value@285_0_, sort: Int
	varName: u12@227, value: u12@227_0_, sort: Int
	varName: b@221, value: b@221_0_, sort: Bool
	varName: p3_rv_value@297, value: p3_rv_value@297_0_, sort: Int
	varName: u@217, value: u@217_0_, sort: Int
	varName: msg_sender@48, value: msg_sender@48_0_, sort: String
	varName: a@187, value: a@187_0_, sort: Bool
	varName: a@211, value: a@211_0_, sort: Int
	varName: voteWeight@127, value: voteWeight@127_0_, sort: Int
	varName: benefit@261, value: benefit@261_0_, sort: Int
	varName: supportsProposal@50, value: supportsProposal@50_0_, sort: Bool
	varName: quorum@105, value: quorum@105_0_, sort: Int
	varName: i@117, value: i@117_0_, sort: Int
	varName: yea@109, value: yea@109_0_, sort: Int
	varName: allocation@263, value: allocation@263_0_, sort: String
	varName: nay@113, value: nay@113_0_, sort: Int
	varName: p2_rv_value@287, value: p2_rv_value@287_0_, sort: Int
	varName: v_1@231, value: v_1@231_0_, sort: Bool
	varName: v2@233, value: v2@233_0_, sort: Bool
	varName: v_2@235, value: v_2@235_0_, sort: Bool
	varName: a@205, value: a@205_0_, sort: Int
	varName: allocation@253, value: allocation@253_0_, sort: String
	varName: player@243, value: player@243_0_, sort: String
	varName: benefit@245, value: benefit@245_0_, sort: Int
	varName: benefit@251, value: benefit@251_0_, sort: Int
	varName: a@219, value: a@219_0_, sort: Bool
	varName: a@193, value: a@193_0_, sort: Int
	varName: a@199, value: a@199_0_, sort: Int
	varName: other_allocation@255, value: other_allocation@255_0_, sort: String
	varName: p3_value@295, value: p3_value@295_0_, sort: Int
	varName: msg_sender2@281, value: msg_sender2@281_0_, sort: String
	varName: p1_rv_value@277, value: p1_rv_value@277_0_, sort: Int
	varName: msg_sender1@271, value: msg_sender1@271_0_, sort: String
	varName: p1@273, value: p1@273_0_, sort: Bool
	varName: v1@229, value: v1@229_0_, sort: Bool
	varName: p2@283, value: p2@283_0_, sort: Bool
	varName: msg_value5@319, value: msg_value5@319_0_, sort: Bool
	varName: msg_value4@309, value: msg_value4@309_0_, sort: Bool
	varName: other_allocation@265, value: other_allocation@265_0_, sort: String
	varName: p1_value@275, value: p1_value@275_0_, sort: Int
	varName: allocation@241, value: allocation@241_0_, sort: String
	varName: msg_value1@279, value: msg_value1@279_0_, sort: Bool
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
symbolically execute function [_Main_]
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
* model construction time: 64.969s
*  property checking time: 0.372s
*              total time: 65.341s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:90-0
*collusion-free:90-0
*       optimal:90-0
*     efficient:90-0
*************************************
