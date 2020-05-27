analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: benefits@203, value: benefits@203_0_, sort: (Array String Int)
	varName: utilities@199, value: utilities@199_0_, sort: (Array String Int)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: voteCount@24, value: voteCount@24_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: proposal@22, value: proposal@22_0_, sort: Proposal
local variables: 
	varName: msg_value5@337, value: msg_value5@337_0_, sort: Bool
	varName: p5_rv_value@335, value: p5_rv_value@335_0_, sort: Int
	varName: p5_value@333, value: p5_value@333_0_, sort: Int
	varName: p5@331, value: p5@331_0_, sort: Bool
	varName: msg_sender5@329, value: msg_sender5@329_0_, sort: String
	varName: p4_rv_value@325, value: p4_rv_value@325_0_, sort: Int
	varName: msg_sender4@319, value: msg_sender4@319_0_, sort: String
	varName: p3@311, value: p3@311_0_, sort: Bool
	varName: msg_value2@307, value: msg_value2@307_0_, sort: Bool
	varName: u12@245, value: u12@245_0_, sort: Int
	varName: msg_value3@317, value: msg_value3@317_0_, sort: Bool
	varName: a@237, value: a@237_0_, sort: Bool
	varName: p3_rv_value@315, value: p3_rv_value@315_0_, sort: Int
	varName: a@229, value: a@229_0_, sort: Int
	varName: a@223, value: a@223_0_, sort: Int
	varName: benefit@269, value: benefit@269_0_, sort: Int
	varName: a@211, value: a@211_0_, sort: Int
	varName: benefit@263, value: benefit@263_0_, sort: Int
	varName: a@205, value: a@205_0_, sort: Bool
	varName: v_2@253, value: v_2@253_0_, sort: Int
	varName: msg_value4@327, value: msg_value4@327_0_, sort: Bool
	varName: msg_sender1@289, value: msg_sender1@289_0_, sort: String
	varName: b@239, value: b@239_0_, sort: Bool
	varName: supportsProposal@50, value: supportsProposal@50_0_, sort: Bool
	varName: other_allocation@273, value: other_allocation@273_0_, sort: String
	varName: p3_value@313, value: p3_value@313_0_, sort: Int
	varName: msg_sender@48, value: msg_sender@48_0_, sort: String
	varName: p2_value@303, value: p2_value@303_0_, sort: Int
	varName: p1@291, value: p1@291_0_, sort: Bool
	varName: nay@113, value: nay@113_0_, sort: Int
	varName: a@217, value: a@217_0_, sort: Int
	varName: p4_value@323, value: p4_value@323_0_, sort: Int
	varName: v_1@249, value: v_1@249_0_, sort: Int
	varName: i@135, value: i@135_0_, sort: Int
	varName: p4@321, value: p4@321_0_, sort: Bool
	varName: u@235, value: u@235_0_, sort: Int
	varName: allocation@271, value: allocation@271_0_, sort: String
	varName: p1_value@293, value: p1_value@293_0_, sort: Int
	varName: yea@109, value: yea@109_0_, sort: Int
	varName: msg_sender3@309, value: msg_sender3@309_0_, sort: String
	varName: p2@301, value: p2@301_0_, sort: Bool
	varName: voteWeight@145, value: voteWeight@145_0_, sort: Int
	varName: v2@251, value: v2@251_0_, sort: Int
	varName: allocation@259, value: allocation@259_0_, sort: String
	varName: p2_rv_value@305, value: p2_rv_value@305_0_, sort: Int
	varName: player@261, value: player@261_0_, sort: String
	varName: p1_rv_value@295, value: p1_rv_value@295_0_, sort: Int
	varName: quorum@105, value: quorum@105_0_, sort: Int
	varName: v1@247, value: v1@247_0_, sort: Int
	varName: benefit@279, value: benefit@279_0_, sort: Int
	varName: allocation@281, value: allocation@281_0_, sort: String
	varName: other_allocation@283, value: other_allocation@283_0_, sort: String
	varName: msg_value1@297, value: msg_value1@297_0_, sort: Bool
	varName: msg_sender2@299, value: msg_sender2@299_0_, sort: String
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
symbolically execute function [_Main_]
Using Z3 solver to optimize value expression
-------------------------------------------------------------------------
-------------------------------------------------------------------------
-------------------------------------------------------------------------
--------------------------------OUTCOME-------------------------------------
|truthful violate check        |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |Truthful                                |
for voting
-------------------------------------------
|truthful voting case                     |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 6)
                                "\x10"
                                (- 8365))
                         ""
                         (- 8855))
                  "\x00"
                  (- 449))))
  (store (store a!1 "\x02" (- 1236)) "\x10" (- 1796)))|
|voteCount           |3                   |
|proposal            |(let ((a!1 (store (store ((as const (Array Int Vote)) (Vote false "!0!"))
                         4
                         (Vote false ""))
                  3
                  (Vote false "\x00")))
      (a!3 (store (store (store ((as const (Array String Bool)) false)
                                "\x10"
                                true)
                         ""
                         true)
                  "\x00"
                  true)))
(let ((a!2 (store (store (store a!1 (- 2) (Vote true "\x10"))
                         (- 1)
                         (Vote false ""))
                  0
                  (Vote false "\x00"))))
  (Proposal true
            true
            3
            (store (store a!2 1 (Vote false "\x02")) 2 (Vote false "\x10"))
            (store (store a!3 "\x02" true) "\x10" true))))|
----------------Local Variable-----------------------
|msg_value5          |false               |
|p5_value            |(- 1796)            |
|msg_sender5         |"\x10"              |
|p4_rv_value         |(- 2438)            |
|msg_sender4         |"\x02"              |
|msg_value2          |false               |
|msg_value3          |false               |
|p3_rv_value         |(- 7720)            |
|msg_value4          |false               |
|msg_sender1         |"\x10"              |
|supportsProposal    |false               |
|p3_value            |(- 449)             |
|msg_sender          |"\x10"              |
|p2_value            |(- 8855)            |
|nay                 |0                   |
|p4_value            |(- 1236)            |
|i                   |5                   |
|p1_value            |(- 8365)            |
|yea                 |5                   |
|msg_sender3         |"\x00"              |
|voteWeight          |1                   |
|p1_rv_value         |(- 2283)            |
|quorum              |5                   |
|msg_value1          |true                |
|msg_sender2         |""                  |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |(- 1796)                                |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |(- 8855)                                |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |(- 449)                                 |
-------------------------------------------------------------------------
|utilities[msg_sender4]        |(- 1236)                                |
-------------------------------------------------------------------------
|utilities[msg_sender5]        |(- 1796)                                |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------
|proposal.proposalPassed       |true                                    |
-------------------------------------------------------------------------

-------------------------------------------------------------------------
|collusion violate check       |value                                   |
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
* model construction time: 48.208s
*  property checking time: 0.512s
*              total time: 48.72s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:54-0
*collusion-free:54-0
*       optimal:54-0
*     efficient:54-0
*************************************
