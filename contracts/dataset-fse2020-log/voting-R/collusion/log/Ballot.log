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
	varName: a@163, value: a@163_0_, sort: Int
	varName: msg_value4@267, value: msg_value4@267_0_, sort: Bool
	varName: winningVoteCount@97, value: winningVoteCount@97_0_, sort: Int
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
	varName: u@175, value: u@175_0_, sort: Int
	varName: v2@191, value: v2@191_0_, sort: Bool
	varName: v_2@193, value: v_2@193_0_, sort: Bool
	varName: v_1@189, value: v_1@189_0_, sort: Bool
	varName: allocation@211, value: allocation@211_0_, sort: String
	varName: a@151, value: a@151_0_, sort: Int
	varName: player@201, value: player@201_0_, sort: String
	varName: p1_rv_value@235, value: p1_rv_value@235_0_, sort: Int
	varName: benefit@209, value: benefit@209_0_, sort: Int
	varName: p2_value@243, value: p2_value@243_0_, sort: Int
	varName: other_allocation@213, value: other_allocation@213_0_, sort: String
	varName: benefit@219, value: benefit@219_0_, sort: Int
	varName: allocation@221, value: allocation@221_0_, sort: String
	varName: p3@251, value: p3@251_0_, sort: Bool
	varName: msg_sender1@229, value: msg_sender1@229_0_, sort: String
	varName: msg_sender4@259, value: msg_sender4@259_0_, sort: String
	varName: other_allocation@223, value: other_allocation@223_0_, sort: String
	varName: p1@231, value: p1@231_0_, sort: Bool
	varName: msg_value1@237, value: msg_value1@237_0_, sort: Bool
	varName: winner@387, value: winner@387_0_, sort: Int
	varName: allocation@199, value: allocation@199_0_, sort: String
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
|utilities[msg_sender1]        |Colluded                                |
-------------------------------------------
|Colluded Case                            |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 21) "" 0)
                         "\x01"
                         0)
                  "\x01\x08"
                  0)))
(let ((a!2 (store (store (store (store a!1 "\x80" 0) "\x00" 0) "" 10163)
                  "\x01"
                  2439)))
  (store (store (store a!2 "\x01\x08" 7721) "\x80" 8857) "\x00" 2)))|
|proposals           |2                   |
|proposals           |(let ((a!1 (store ((as const (Array Int Proposal))
                    (Proposal ((as const (Array Int Int)) 20) 12))
                  0
                  (Proposal (store ((as const (Array Int Int)) 17) 16 15) 0))))
(let ((a!2 (store a!1
                  1
                  (Proposal (store ((as const (Array Int Int)) 19) 16 18) 0))))
  (store a!2 0 (Proposal (store ((as const (Array Int Int)) 17) 16 15) 5))))|
|voters              |(let ((a!1 (store (store ((as const (Array String Voter)) (Voter 9 false "" 2))
                         ""
                         (Voter 1 false "" 8))
                  "\x01"
                  (Voter 1 false "\x01" 7))))
(let ((a!2 (store (store (store a!1 "\x01\x08" (Voter 1 false "\x01\x08" 6))
                         "\x80"
                         (Voter 1 false "\x80" 4))
                  "\x00"
                  (Voter 1 false "\x00" 3))))
(let ((a!3 (store (store (store a!2 "" (Voter 1 true "" 0))
                         "\x01"
                         (Voter 1 true "\x01" 0))
                  "\x01\x08"
                  (Voter 1 true "\x01\x08" 0))))
  (store (store a!3 "\x80" (Voter 1 true "\x80" 0))
         "\x00"
         (Voter 1 true "\x00" 0)))))|
----------------Local Variable-----------------------
|msg_value5          |true                |
|p5_rv_value         |1                   |
|p5_value            |2                   |
|p5                  |true                |
|p4_rv_value         |8856                |
|msg_value3          |true                |
|p3_rv_value         |7720                |
|p3_value            |7721                |
|msg_sender5         |"\x00"              |
|msg_sender3         |"\x01\x08"          |
|msg_value2          |false               |
|p2_rv_value         |2438                |
|p4_value            |8857                |
|msg_value4          |true                |
|winningVoteCount    |5                   |
|p4                  |true                |
|numOfProposal       |2                   |
|proposal            |0                   |
|msg_sender          |"\x00"              |
|p                   |2                   |
|p1_value            |10163               |
|winningProposal_    |0                   |
|msg_sender2         |"\x01"              |
|p1_rv_value         |8366                |
|p2_value            |2439                |
|p3                  |true                |
|msg_sender1         |""                  |
|msg_sender4         |"\x80"              |
|p1                  |false               |
|msg_value1          |false               |
|winner              |0                   |
|p2                  |false               |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |10163                                   |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |2439                                    |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |7721                                    |
-------------------------------------------------------------------------
|utilities[msg_sender4]        |8857                                    |
-------------------------------------------------------------------------
|utilities[msg_sender5]        |2                                       |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------

hint
msg_value1@237_0_:false
msg_value2@247_0_:false
msg_value1@237_0_#2:true
msg_value2@247_0_#2:true
v1&v2's utility:10163
new v1&v2's colluded utility:8366
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
* model construction time: 115.271s
*  property checking time: 0.432s
*              total time: 115.703s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:90-0
*collusion-free:90-1
*       optimal:90-0
*     efficient:90-0
*************************************
