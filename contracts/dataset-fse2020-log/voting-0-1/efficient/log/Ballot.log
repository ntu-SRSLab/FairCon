analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: benefits@143, value: benefits@143_0_, sort: (Array String Int)
	varName: utilities@139, value: utilities@139_0_, sort: (Array String Int)
	varName: proposals@24, value: proposals@24_0_, sort: (Array Int Proposal)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: chairperson@17, value: chairperson@17_0_, sort: String
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: voters@21, value: voters@21_0_, sort: (Array String Voter)
local variables: 
	varName: g_false@683, value: g_false@683_0_, sort: Int
	varName: msg_value5@277, value: msg_value5@277_0_, sort: Bool
	varName: p5_rv_value@275, value: p5_rv_value@275_0_, sort: Int
	varName: p5_value@273, value: p5_value@273_0_, sort: Int
	varName: p5@271, value: p5@271_0_, sort: Bool
	varName: p4_rv_value@265, value: p4_rv_value@265_0_, sort: Int
	varName: msg_value3@257, value: msg_value3@257_0_, sort: Bool
	varName: p3_rv_value@255, value: p3_rv_value@255_0_, sort: Int
	varName: p3_value@253, value: p3_value@253_0_, sort: Int
	varName: msg_sender5@269, value: msg_sender5@269_0_, sort: String
	varName: msg_sender3@249, value: msg_sender3@249_0_, sort: String
	varName: msg_value2@247, value: msg_value2@247_0_, sort: Bool
	varName: p2_rv_value@245, value: p2_rv_value@245_0_, sort: Int
	varName: v1@187, value: v1@187_0_, sort: Bool
	varName: a@177, value: a@177_0_, sort: Bool
	varName: a@169, value: a@169_0_, sort: Int
	varName: p4_value@263, value: p4_value@263_0_, sort: Int
	varName: a@157, value: a@157_0_, sort: Int
	varName: msg_value4@267, value: msg_value4@267_0_, sort: Bool
	varName: winningVoteCount@97, value: winningVoteCount@97_0_, sort: Int
	varName: a@151, value: a@151_0_, sort: Int
	varName: p4@261, value: p4@261_0_, sort: Bool
	varName: a@145, value: a@145_0_, sort: String
	varName: b@179, value: b@179_0_, sort: Bool
	varName: numOfProposal@26, value: numOfProposal@26_0_, sort: Int
	varName: proposal@40, value: proposal@40_0_, sort: Int
	varName: msg_sender@38, value: msg_sender@38_0_, sort: String
	varName: p@101, value: p@101_0_, sort: Int
	varName: u12@185, value: u12@185_0_, sort: Int
	varName: benefit@203, value: benefit@203_0_, sort: Int
	varName: p1_value@233, value: p1_value@233_0_, sort: Int
	varName: winningProposal_@94, value: winningProposal_@94_0_, sort: Int
	varName: msg_sender2@239, value: msg_sender2@239_0_, sort: String
	varName: winner@407, value: winner@407_0_, sort: Int
	varName: u@175, value: u@175_0_, sort: Int
	varName: v2@191, value: v2@191_0_, sort: Bool
	varName: v_2@193, value: v_2@193_0_, sort: Bool
	varName: v_1@189, value: v_1@189_0_, sort: Bool
	varName: allocation@211, value: allocation@211_0_, sort: Bool
	varName: a@163, value: a@163_0_, sort: Int
	varName: other_allocation@201, value: other_allocation@201_0_, sort: Bool
	varName: benefit@219, value: benefit@219_0_, sort: Int
	varName: p1_rv_value@235, value: p1_rv_value@235_0_, sort: Int
	varName: benefit@209, value: benefit@209_0_, sort: Int
	varName: p2_value@243, value: p2_value@243_0_, sort: Int
	varName: other_allocation@213, value: other_allocation@213_0_, sort: Bool
	varName: allocation@221, value: allocation@221_0_, sort: String
	varName: p3@251, value: p3@251_0_, sort: Bool
	varName: msg_sender1@229, value: msg_sender1@229_0_, sort: String
	varName: msg_sender4@259, value: msg_sender4@259_0_, sort: String
	varName: other_allocation@223, value: other_allocation@223_0_, sort: String
	varName: p1@231, value: p1@231_0_, sort: Bool
	varName: msg_value1@237, value: msg_value1@237_0_, sort: Bool
	varName: allocation@199, value: allocation@199_0_, sort: Bool
	varName: p2@241, value: p2@241_0_, sort: Bool
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
|effecient violate check       |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1] +
                                        utilities[msg_sender2] + utilities[msg_sender3] + 
                                        utilities[msg_sender4] + utilities[msg_sender5]|Uneffecient                             |
-------------------------------------------
|Uneffecient Case                         |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 14) "\x00@" 0)
                         ""
                         0)
                  "\x00\x01"
                  0)))
(let ((a!2 (store (store (store (store a!1 "\x00\x00" 0) "\x00" 0) "\x00\x00" 1)
                  "\x00"
                  1)))
  (store (store (store a!2 "" 1) "\x00@" 1) "\x00\x01" 1)))|
|proposals           |2                   |
|proposals           |(let ((a!1 (store ((as const (Array Int Proposal))
                    (Proposal ((as const (Array Int Int)) 20) 2))
                  0
                  (Proposal (store ((as const (Array Int Int)) 17) 16 15) 0))))
(let ((a!2 (store a!1
                  1
                  (Proposal (store ((as const (Array Int Int)) 19) 16 18) 0))))
  (store a!2 0 (Proposal (store ((as const (Array Int Int)) 17) 16 15) 5))))|
|voters              |(let ((a!1 (store (store ((as const (Array String Voter)) (Voter 8 false "" 2))
                         ""
                         (Voter 1 false "" 5))
                  "\x00@"
                  (Voter 1 false "" 4))))
(let ((a!2 (store (store (store a!1 "\x00\x01" (Voter 1 false "" 3))
                         "\x00\x00"
                         (Voter 1 false "" 7))
                  "\x00"
                  (Voter 1 false "" 6))))
(let ((a!3 (store (store (store a!2 "\x00\x00" (Voter 1 true "" 0))
                         "\x00"
                         (Voter 1 true "" 0))
                  ""
                  (Voter 1 true "" 0))))
  (store (store a!3 "\x00@" (Voter 1 true "" 0)) "\x00\x01" (Voter 1 true "" 0)))))|
----------------Local Variable-----------------------
|g_false             |0                   |
|msg_value5          |true                |
|p5_rv_value         |0                   |
|p5_value            |1                   |
|p5                  |false               |
|p4_rv_value         |0                   |
|msg_value3          |false               |
|p3_rv_value         |0                   |
|p3_value            |1                   |
|msg_sender5         |"\x00\x01"          |
|msg_sender3         |""                  |
|msg_value2          |false               |
|p2_rv_value         |0                   |
|p4_value            |1                   |
|msg_value4          |true                |
|winningVoteCount    |5                   |
|p4                  |true                |
|numOfProposal       |2                   |
|proposal            |0                   |
|msg_sender          |"\x00\x01"          |
|p                   |2                   |
|p1_value            |1                   |
|winningProposal_    |0                   |
|msg_sender2         |"\x00"              |
|winner              |0                   |
|p1_rv_value         |0                   |
|p2_value            |1                   |
|p3                  |false               |
|msg_sender1         |"\x00\x00"          |
|msg_sender4         |"\x00@"             |
|p1                  |false               |
|msg_value1          |true                |
|p2                  |false               |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |1                                       |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |1                                       |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |1                                       |
-------------------------------------------------------------------------
|utilities[msg_sender4]        |1                                       |
-------------------------------------------------------------------------
|utilities[msg_sender5]        |1                                       |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------

hint
benefit:5
optional benefit:0
-------------------------------------------------------------------------
|optimal violate check         |value                                   |
**************************************
*    outcome pattern                 *
**************************************
*************************************
*         report                    *
*************************************
* model construction time: 401.544s
*  property checking time: 1.908s
*              total time: 403.452s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:1024-0
*collusion-free:1024-0
*       optimal:1024-0
*     efficient:1024-1
*************************************
