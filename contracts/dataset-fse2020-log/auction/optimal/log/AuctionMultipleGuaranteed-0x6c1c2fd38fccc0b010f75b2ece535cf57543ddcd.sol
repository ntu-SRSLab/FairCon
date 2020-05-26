analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: payments@115, value: payments@115_0_, sort: (Array String Int)
	varName: increaseTimeBy@17, value: increaseTimeBy@17_0_, sort: Int
	varName: increaseTimeIfBidBeforeEnd@15, value: increaseTimeIfBidBeforeEnd@15_0_, sort: Int
	varName: bids@13, value: bids@13_0_, sort: (Array String Int)
	varName: benefits@111, value: benefits@111_0_, sort: (Array String Int)
	varName: winner@9, value: winner@9_0_, sort: String
	varName: price@7, value: price@7_0_, sort: Int
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: utilities@107, value: utilities@107_0_, sort: (Array String Int)
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: timestampEnd@5, value: timestampEnd@5_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: initialPrice@3, value: initialPrice@3_0_, sort: Bool
local variables: 
	varName: msg_sender3@231, value: msg_sender3@231_0_, sort: String
	varName: block_timestamp2@229, value: block_timestamp2@229_0_, sort: Int
	varName: block_timestamp3@239, value: block_timestamp3@239_0_, sort: Int
	varName: msg_price3@237, value: msg_price3@237_0_, sort: Int
	varName: v_2@165, value: v_2@165_0_, sort: Int
	varName: benefit@201, value: benefit@201_0_, sort: Int
	varName: v2@163, value: v2@163_0_, sort: Int
	varName: msg_price1@217, value: msg_price1@217_0_, sort: Int
	varName: u12@157, value: u12@157_0_, sort: Int
	varName: b@151, value: b@151_0_, sort: Int
	varName: a@149, value: a@149_0_, sort: Int
	varName: u@147, value: u@147_0_, sort: Int
	varName: a@141, value: a@141_0_, sort: Int
	varName: payment@195, value: payment@195_0_, sort: Int
	varName: msg_price2@227, value: msg_price2@227_0_, sort: Int
	varName: a@135, value: a@135_0_, sort: Int
	varName: block_timestamp@23, value: block_timestamp@23_0_, sort: Int
	varName: other_allocation@185, value: other_allocation@185_0_, sort: String
	varName: a@123, value: a@123_0_, sort: Int
	varName: a@129, value: a@129_0_, sort: Int
	varName: msg_sender@19, value: msg_sender@19_0_, sort: String
	varName: msg_sender2@221, value: msg_sender2@221_0_, sort: String
	varName: a@117, value: a@117_0_, sort: String
	varName: allocation@171, value: allocation@171_0_, sort: String
	varName: player@173, value: player@173_0_, sort: String
	varName: benefit@175, value: benefit@175_0_, sort: Int
	varName: allocation@191, value: allocation@191_0_, sort: String
	varName: benefit@181, value: benefit@181_0_, sort: Int
	varName: block_timestamp1@219, value: block_timestamp1@219_0_, sort: Int
	varName: msg_value2@225, value: msg_value2@225_0_, sort: Int
	varName: msg_value@21, value: msg_value@21_0_, sort: Int
	varName: player@193, value: player@193_0_, sort: String
	varName: allocation@203, value: allocation@203_0_, sort: String
	varName: v_1@161, value: v_1@161_0_, sort: Int
	varName: v1@159, value: v1@159_0_, sort: Int
	varName: other_allocation@205, value: other_allocation@205_0_, sort: String
	varName: winners_count@523, value: winners_count@523_0_, sort: Int
	varName: msg_value3@235, value: msg_value3@235_0_, sort: Int
	varName: p3@233, value: p3@233_0_, sort: Int
	varName: msg_sender1@211, value: msg_sender1@211_0_, sort: String
	varName: allocation@183, value: allocation@183_0_, sort: String
	varName: p1@213, value: p1@213_0_, sort: Int
	varName: msg_value1@215, value: msg_value1@215_0_, sort: Int
	varName: p2@223, value: p2@223_0_, sort: Int
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
|optimal violate check         |value                                   |
-------------------------------------------------------------------------
|payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3]|Optimal                                 |
-------------------------------------------------------------------------
|payments[msg_sender1]+payments[msg_sender2]+payments[msg_sender3]|Unoptimal                               |
-------------------------------------------
|Unoptimal Case                           |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|payments            |(let ((a!1 (store (store (store ((as const (Array String Int)) 6) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!0!" 100000000004))|
|increaseTimeBy      |100                 |
|increaseTimeIfBidBeforeEnd|10                  |
|bids                |(let ((a!1 (store (store (store ((as const (Array String Int)) 1) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store (store (store a!1 "!0!" 100000000004) "!2!" 100000000005)
         "!3!"
         100000000001))|
|benefits            |(let ((a!1 (store (store (store ((as const (Array String Int)) 3) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!0!" 100000000001))|
|winner              |"!0!"               |
|price               |100000000004        |
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 2) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!0!" (- 3)))|
|timestampEnd        |1000091             |
|initialPrice        |false               |
----------------Local Variable-----------------------
|msg_sender3         |"!3!"               |
|block_timestamp2    |0                   |
|block_timestamp3    |0                   |
|msg_price3          |100000000001        |
|msg_price1          |100000000001        |
|msg_price2          |100000000001        |
|block_timestamp     |0                   |
|msg_sender          |"!3!"               |
|msg_sender2         |"!2!"               |
|block_timestamp1    |999991              |
|msg_value2          |100000000005        |
|msg_value           |100000000001        |
|winners_count       |1                   |
|msg_value3          |100000000001        |
|p3                  |100000000001        |
|msg_sender1         |"!0!"               |
|p1                  |100000000001        |
|msg_value1          |100000000004        |
|p2                  |100000000001        |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |(- 3)                                   |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |0                                       |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |0                                       |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------
|msg_sender1                   |"!0!"                                   |
-------------------------------------------------------------------------

hint
payment:100000000004
optional payment:100000000005
**************************************
*    outcome pattern                 *
**************************************
*************************************
*         report                    *
*************************************
* model construction time: 7.549s
*  property checking time: 0.108s
*              total time: 7.657s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:18-0
*collusion-free:18-0
*       optimal:18-1
*     efficient:18-0
*************************************
