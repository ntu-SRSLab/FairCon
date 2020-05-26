analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: benefits@238, value: benefits@238_0_, sort: (Array String Int)
	varName: utilities@234, value: utilities@234_0_, sort: (Array String Int)
	varName: _winner@38, value: _winner@38_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: proposals@10, value: proposals@10_0_, sort: (Array Int Proposal)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: voteDates@14, value: voteDates@14_0_, sort: (Array String Int)
	varName: votes@18, value: votes@18_0_, sort: (Array String Int)
	varName: alreadyRefunded@22, value: alreadyRefunded@22_0_, sort: (Array String Int)
	varName: currentVotingDate@24, value: currentVotingDate@24_0_, sort: Int
	varName: currentVotingAmount@26, value: currentVotingAmount@26_0_, sort: Int
	varName: allowedWithdraw@28, value: allowedWithdraw@28_0_, sort: Int
	varName: allowedRefund@30, value: allowedRefund@30_0_, sort: Int
	varName: toAllow@32, value: toAllow@32_0_, sort: Int
	varName: voteCount@4, value: voteCount@4_0_, sort: (Array Int Int)
	varName: toCancel@34, value: toCancel@34_0_, sort: Int
	varName: toRefund@36, value: toRefund@36_0_, sort: Int
local variables: 
	varName: msg_value5@372, value: msg_value5@372_0_, sort: Int
	varName: p5_value@368, value: p5_value@368_0_, sort: Int
	varName: p5@366, value: p5@366_0_, sort: Int
	varName: msg_sender5@364, value: msg_sender5@364_0_, sort: String
	varName: p4@356, value: p4@356_0_, sort: Int
	varName: msg_value3@352, value: msg_value3@352_0_, sort: Int
	varName: p3_value@348, value: p3_value@348_0_, sort: Int
	varName: p3@346, value: p3@346_0_, sort: Int
	varName: msg_value2@342, value: msg_value2@342_0_, sort: Int
	varName: u@270, value: u@270_0_, sort: Int
	varName: a@264, value: a@264_0_, sort: Int
	varName: msg_sender4@354, value: msg_sender4@354_0_, sort: String
	varName: a@258, value: a@258_0_, sort: Int
	varName: v2@286, value: v2@286_0_, sort: Int
	varName: p2_rv_value@340, value: p2_rv_value@340_0_, sort: Int
	varName: a@252, value: a@252_0_, sort: Int
	varName: allocation@294, value: allocation@294_0_, sort: String
	varName: v1@282, value: v1@282_0_, sort: Int
	varName: p4_rv_value@360, value: p4_rv_value@360_0_, sort: Int
	varName: msg_sender2@334, value: msg_sender2@334_0_, sort: String
	varName: p4_value@358, value: p4_value@358_0_, sort: Int
	varName: b@274, value: b@274_0_, sort: Int
	varName: msg_sender1@324, value: msg_sender1@324_0_, sort: String
	varName: winner@762, value: winner@762_0_, sort: Int
	varName: msg_sender@52, value: msg_sender@52_0_, sort: String
	varName: a@240, value: a@240_0_, sort: String
	varName: msg_sender3@344, value: msg_sender3@344_0_, sort: String
	varName: u12@280, value: u12@280_0_, sort: Int
	varName: v_1@284, value: v_1@284_0_, sort: Int
	varName: proposal@54, value: proposal@54_0_, sort: Int
	varName: p2_value@338, value: p2_value@338_0_, sort: Int
	varName: numOfProposal@40, value: numOfProposal@40_0_, sort: Int
	varName: prop@57, value: prop@57_0_, sort: Int
	varName: winnerName@225, value: winnerName@225_0_, sort: Int
	varName: p3_rv_value@350, value: p3_rv_value@350_0_, sort: Int
	varName: allocation@306, value: allocation@306_0_, sort: String
	varName: p5_rv_value@370, value: p5_rv_value@370_0_, sort: Int
	varName: v_2@288, value: v_2@288_0_, sort: Int
	varName: benefit@304, value: benefit@304_0_, sort: Int
	varName: p2@336, value: p2@336_0_, sort: Int
	varName: player@296, value: player@296_0_, sort: String
	varName: benefit@298, value: benefit@298_0_, sort: Int
	varName: msg_value4@362, value: msg_value4@362_0_, sort: Int
	varName: a@246, value: a@246_0_, sort: Int
	varName: other_allocation@308, value: other_allocation@308_0_, sort: String
	varName: benefit@314, value: benefit@314_0_, sort: Int
	varName: allocation@316, value: allocation@316_0_, sort: String
	varName: a@272, value: a@272_0_, sort: Int
	varName: p1@326, value: p1@326_0_, sort: Int
	varName: p1_value@328, value: p1_value@328_0_, sort: Int
	varName: other_allocation@318, value: other_allocation@318_0_, sort: String
	varName: p1_rv_value@330, value: p1_rv_value@330_0_, sort: Int
	varName: msg_value1@332, value: msg_value1@332_0_, sort: Int
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
|utilities[msg_sender1]        |Colluded                                |
-------------------------------------------
|Colluded Case                            |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 13) "!3!" 0)
                         "!1!"
                         0)
                  "!0!"
                  0)))
(let ((a!2 (store (store (store (store a!1 "!4!" 0) "!2!" 0) "!0!" 2)
                  "!4!"
                  1238)))
  (store (store (store a!2 "!2!" 2439) "!3!" 8857) "!1!" 1798)))|
|_winner             |1                   |
|toAllow             |0                   |
|toRefund            |0                   |
|toCancel            |0                   |
|voteCount           |voteCount@4_0_.length|
|proposals           |2                   |
|voteDates           |(let ((a!1 (store (store (store ((as const (Array String Int)) 4) "!3!" 0)
                         "!1!"
                         0)
                  "!0!"
                  0)))
(let ((a!2 (store (store (store (store a!1 "!4!" 0) "!2!" 0) "!0!" 100)
                  "!4!"
                  100)))
  (store (store (store a!2 "!2!" 100) "!3!" 100) "!1!" 100)))|
|votes               |(let ((a!1 (store (store (store ((as const (Array String Int)) 11) "!2!" 0)
                         "!3!"
                         0)
                  "!0!"
                  0)))
(let ((a!2 (store (store (store (store a!1 "!4!" 0) "!1!" 0) "!0!" 3) "!4!" 1)))
  (store (store (store a!2 "!2!" 2) "!3!" 2) "!1!" 1)))|
|alreadyRefunded     |(let ((a!1 (store (store (store ((as const (Array String Int)) 12) "!3!" 0)
                         "!1!"
                         0)
                  "!0!"
                  0)))
(let ((a!2 (store (store (store (store a!1 "!4!" 0) "!2!" 0) "!0!" 0) "!4!" 0)))
  (store (store (store a!2 "!2!" 0) "!3!" 0) "!1!" 0)))|
|currentVotingDate   |0                   |
|currentVotingAmount |0                   |
|allowedWithdraw     |currentVotingAmount@26_0_|
|allowedRefund       |0                   |
----------------Local Variable-----------------------
|msg_value5          |1                   |
|p5_value            |1798                |
|p5                  |1                   |
|msg_sender5         |"!1!"               |
|p4                  |2                   |
|msg_value3          |2                   |
|p3_value            |2439                |
|p3                  |2                   |
|msg_value2          |1                   |
|msg_sender4         |"!3!"               |
|p2_rv_value         |1237                |
|p4_rv_value         |8856                |
|msg_sender2         |"!4!"               |
|p4_value            |8857                |
|msg_sender1         |"!0!"               |
|winner              |1                   |
|msg_sender          |"!1!"               |
|msg_sender3         |"!2!"               |
|proposal            |1                   |
|p2_value            |1238                |
|numOfProposal       |2                   |
|prop                |1                   |
|winnerName          |1                   |
|p3_rv_value         |2438                |
|p5_rv_value         |1797                |
|p2                  |1                   |
|msg_value4          |2                   |
|p1                  |3                   |
|p1_value            |2                   |
|p1_rv_value         |1                   |
|msg_value1          |3                   |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |2                                       |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |1238                                    |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |2439                                    |
-------------------------------------------------------------------------
|utilities[msg_sender4]        |8857                                    |
-------------------------------------------------------------------------
|utilities[msg_sender5]        |1798                                    |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------

hint
msg_value1@332_0_:3
msg_value2@342_0_:1
msg_value1@332_0_#2:2
msg_value2@342_0_#2:3
v1&v2's utility:2
new v1&v2's colluded utility:1
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
* model construction time: 483.948s
*  property checking time: 1.569s
*              total time: 485.517s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:966-0
*collusion-free:966-1
*       optimal:966-0
*     efficient:966-0
*************************************
