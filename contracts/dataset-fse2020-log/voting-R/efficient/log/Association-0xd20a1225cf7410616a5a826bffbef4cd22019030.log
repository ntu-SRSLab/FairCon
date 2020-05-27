analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: utilities@176, value: utilities@176_0_, sort: (Array String Int)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: voteCount@24, value: voteCount@24_0_, sort: Int
	varName: benefits@180, value: benefits@180_0_, sort: (Array String Int)
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: proposal@22, value: proposal@22_0_, sort: Proposal
local variables: 
	varName: g_false@668, value: g_false@668_0_, sort: Int
	varName: g_true@665, value: g_true@665_0_, sort: Int
	varName: p5_rv_value@312, value: p5_rv_value@312_0_, sort: Int
	varName: p5@308, value: p5@308_0_, sort: Bool
	varName: p4_rv_value@302, value: p4_rv_value@302_0_, sort: Int
	varName: msg_value3@294, value: msg_value3@294_0_, sort: Bool
	varName: msg_value4@304, value: msg_value4@304_0_, sort: Bool
	varName: p3_rv_value@292, value: p3_rv_value@292_0_, sort: Int
	varName: p4_value@300, value: p4_value@300_0_, sort: Int
	varName: p3_value@290, value: p3_value@290_0_, sort: Int
	varName: p2_value@280, value: p2_value@280_0_, sort: Int
	varName: u12@222, value: u12@222_0_, sort: Int
	varName: a@200, value: a@200_0_, sort: Int
	varName: msg_value5@314, value: msg_value5@314_0_, sort: Bool
	varName: u@212, value: u@212_0_, sort: Int
	varName: voteWeight@122, value: voteWeight@122_0_, sort: Int
	varName: a@188, value: a@188_0_, sort: Int
	varName: a@194, value: a@194_0_, sort: Int
	varName: v_2@230, value: v_2@230_0_, sort: Bool
	varName: a@182, value: a@182_0_, sort: String
	varName: msg_value2@284, value: msg_value2@284_0_, sort: Bool
	varName: a@206, value: a@206_0_, sort: Int
	varName: v_1@226, value: v_1@226_0_, sort: Bool
	varName: msg_sender5@306, value: msg_sender5@306_0_, sort: String
	varName: msg_sender@48, value: msg_sender@48_0_, sort: String
	varName: p5_value@310, value: p5_value@310_0_, sort: Int
	varName: i@112, value: i@112_0_, sort: Int
	varName: yea@104, value: yea@104_0_, sort: Int
	varName: p2_rv_value@282, value: p2_rv_value@282_0_, sort: Int
	varName: nay@108, value: nay@108_0_, sort: Int
	varName: msg_value1@274, value: msg_value1@274_0_, sort: Bool
	varName: v1@224, value: v1@224_0_, sort: Bool
	varName: p3@288, value: p3@288_0_, sort: Bool
	varName: v2@228, value: v2@228_0_, sort: Bool
	varName: msg_sender3@286, value: msg_sender3@286_0_, sort: String
	varName: b@216, value: b@216_0_, sort: Bool
	varName: supportsProposal@50, value: supportsProposal@50_0_, sort: Bool
	varName: allocation@236, value: allocation@236_0_, sort: Bool
	varName: new_allocation@238, value: new_allocation@238_0_, sort: Bool
	varName: p4@298, value: p4@298_0_, sort: Bool
	varName: p1_rv_value@272, value: p1_rv_value@272_0_, sort: Int
	varName: benefit@240, value: benefit@240_0_, sort: Int
	varName: benefit@246, value: benefit@246_0_, sort: Int
	varName: allocation@258, value: allocation@258_0_, sort: String
	varName: msg_sender4@296, value: msg_sender4@296_0_, sort: String
	varName: quorum@100, value: quorum@100_0_, sort: Int
	varName: allocation@248, value: allocation@248_0_, sort: Bool
	varName: other_allocation@250, value: other_allocation@250_0_, sort: Bool
	varName: benefit@256, value: benefit@256_0_, sort: Int
	varName: p2@278, value: p2@278_0_, sort: Bool
	varName: other_allocation@260, value: other_allocation@260_0_, sort: String
	varName: msg_sender1@266, value: msg_sender1@266_0_, sort: String
	varName: p1@268, value: p1@268_0_, sort: Bool
	varName: a@214, value: a@214_0_, sort: Bool
	varName: msg_sender2@276, value: msg_sender2@276_0_, sort: String
	varName: p1_value@270, value: p1_value@270_0_, sort: Int
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
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 9) "\x00" 0)
                         ""
                         0)
                  "\x08"
                  0)))
(let ((a!2 (store (store (store (store a!1 "\x00\x00" 0) "\x00\x08" 0)
                         "\x00\x00"
                         6285)
                  "\x00\x08"
                  27685)))
  (store (store (store a!2 "\x08" 9727) "" 8458) "\x00" 976)))|
|voteCount           |0                   |
|proposal            |(let ((a!1 (store (store (store ((as const (Array String Bool)) false)
                                "\x00\x00"
                                true)
                         "\x00\x08"
                         true)
                  "\x08"
                  true)))
  (Proposal true
            false
            1
            (store ((as const (Array Int Vote)) (Vote false ""))
                   0
                   (Vote false "\x00"))
            (store (store a!1 "" true) "\x00" true)))|
----------------Local Variable-----------------------
|g_false             |0                   |
|g_true              |53131               |
|p5_rv_value         |975                 |
|p5                  |false               |
|p4_rv_value         |8457                |
|msg_value3          |false               |
|p3_rv_value         |9726                |
|p4_value            |8458                |
|p3_value            |9727                |
|p2_value            |27685               |
|msg_value5          |false               |
|msg_value2          |true                |
|msg_sender5         |"\x00"              |
|msg_sender          |"\x00"              |
|p5_value            |976                 |
|i                   |0                   |
|yea                 |0                   |
|p2_rv_value         |8880                |
|nay                 |0                   |
|msg_value1          |false               |
|p3                  |true                |
|msg_sender3         |"\x08"              |
|supportsProposal    |false               |
|p4                  |true                |
|p1_rv_value         |6284                |
|msg_sender4         |""                  |
|quorum              |0                   |
|p2                  |true                |
|msg_sender1         |"\x00\x00"          |
|p1                  |false               |
|msg_sender2         |"\x00\x08"          |
|p1_value            |6285                |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |6285                                    |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |27685                                   |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |9727                                    |
-------------------------------------------------------------------------
|utilities[msg_sender4]        |8458                                    |
-------------------------------------------------------------------------
|utilities[msg_sender5]        |976                                     |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------

hint
benefit:53131
optional benefit:0
-------------------------------------------------------------------------
|optimal violate check         |value                                   |
**************************************
*    outcome pattern                 *
**************************************
*************************************
*         report                    *
*************************************
* model construction time: 126.005s
*  property checking time: 0.344s
*              total time: 126.349s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:256-0
*collusion-free:256-0
*       optimal:256-0
*     efficient:256-1
*************************************
