analyzing contract [ Auction ]
exit contract [ Auction ]
analyzing contract [ Auction ]
exit contract [ Auction ]
state variables: 
	varName: utilities@191, value: utilities@191_0_, sort: (Array String Int)
	varName: leader@15, value: leader@15_0_, sort: String
	varName: claimed@19, value: claimed@19_0_, sort: Bool
	varName: bids@13, value: bids@13_0_, sort: Int
	varName: prize@11, value: prize@11_0_, sort: Int
	varName: payments@199, value: payments@199_0_, sort: (Array String Int)
	varName: owner@9, value: owner@9_0_, sort: String
	varName: benefits@195, value: benefits@195_0_, sort: (Array String Int)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: deadline@17, value: deadline@17_0_, sort: Int
	varName: bidDivisor@4, value: bidDivisor@4_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: duration@7, value: duration@7_0_, sort: Int
local variables: 
	varName: block_timestamp3@323, value: block_timestamp3@323_0_, sort: Int
	varName: msg_gas3@321, value: msg_gas3@321_0_, sort: Int
	varName: msg_value3@319, value: msg_value3@319_0_, sort: Int
	varName: p3@317, value: p3@317_0_, sort: Int
	varName: msg_gas2@311, value: msg_gas2@311_0_, sort: Int
	varName: msg_value@144, value: msg_value@144_0_, sort: Int
	varName: v1@243, value: v1@243_0_, sort: Int
	varName: player@257, value: player@257_0_, sort: String
	varName: benefit@259, value: benefit@259_0_, sort: Int
	varName: msg_value2@309, value: msg_value2@309_0_, sort: Int
	varName: msg_value1@299, value: msg_value1@299_0_, sort: Int
	varName: a@225, value: a@225_0_, sort: Int
	varName: msg_sender@142, value: msg_sender@142_0_, sort: String
	varName: allocation@275, value: allocation@275_0_, sort: String
	varName: msg_sender3@315, value: msg_sender3@315_0_, sort: String
	varName: v_2@249, value: v_2@249_0_, sort: Int
	varName: block_timestamp1@303, value: block_timestamp1@303_0_, sort: Int
	varName: a@201, value: a@201_0_, sort: String
	varName: v2@247, value: v2@247_0_, sort: Int
	varName: u@231, value: u@231_0_, sort: Int
	varName: a@219, value: a@219_0_, sort: Int
	varName: ret@55, value: ret@55_0_, sort: Int
	varName: a@207, value: a@207_0_, sort: Int
	varName: a@233, value: a@233_0_, sort: Int
	varName: block_timestamp@146, value: block_timestamp@146_0_, sort: Int
	varName: block_timestamp2@313, value: block_timestamp2@313_0_, sort: Int
	varName: b@235, value: b@235_0_, sort: Int
	varName: u12@241, value: u12@241_0_, sort: Int
	varName: allocation@255, value: allocation@255_0_, sort: String
	varName: benefit@285, value: benefit@285_0_, sort: Int
	varName: other_allocation@289, value: other_allocation@289_0_, sort: String
	varName: winners_count@547, value: winners_count@547_0_, sort: Int
	varName: benefit@265, value: benefit@265_0_, sort: Int
	varName: v_1@245, value: v_1@245_0_, sort: Int
	varName: a@213, value: a@213_0_, sort: Int
	varName: allocation@267, value: allocation@267_0_, sort: String
	varName: other_allocation@269, value: other_allocation@269_0_, sort: String
	varName: player@277, value: player@277_0_, sort: String
	varName: allocation@287, value: allocation@287_0_, sort: String
	varName: payment@279, value: payment@279_0_, sort: Int
	varName: msg_sender1@295, value: msg_sender1@295_0_, sort: String
	varName: p1@297, value: p1@297_0_, sort: Int
	varName: msg_gas1@301, value: msg_gas1@301_0_, sort: Int
	varName: msg_sender2@305, value: msg_sender2@305_0_, sort: String
	varName: p2@307, value: p2@307_0_, sort: Int
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
symbolically execute function [_Main_]
CHECK PASS FAILED 0
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
|benefits[msg_sender1]+benefits[msg_sender2]+benefits[msg_sender3]|Uneffecient                             |
-------------------------------------------
|Uneffecient Case                         |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 2) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!3!" (- 100000000000)))|
|leader              |"!3!"               |
|bids                |2                   |
|prize               |10000000000000      |
|payments            |(let ((a!1 (store (store (store ((as const (Array String Int)) 4) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!3!" 200000000001))|
|benefits            |(let ((a!1 (store (store (store ((as const (Array String Int)) 3) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!3!" 100000000001))|
|deadline            |20                  |
|bidDivisor          |100                 |
|duration            |20                  |
----------------Local Variable-----------------------
|block_timestamp3    |0                   |
|msg_value3          |200000000000        |
|p3                  |100000000001        |
|msg_value           |200000000000        |
|msg_value2          |200000000001        |
|msg_value1          |200000000001        |
|msg_sender          |"!3!"               |
|msg_sender3         |"!3!"               |
|block_timestamp1    |0                   |
|block_timestamp     |0                   |
|block_timestamp2    |0                   |
|winners_count       |1                   |
|msg_sender1         |"!0!"               |
|p1                  |100000000002        |
|msg_sender2         |"!2!"               |
|p2                  |100000000001        |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |0                                       |
-------------------------------------------------------------------------
|utilities[msg_sender2]        |0                                       |
-------------------------------------------------------------------------
|utilities[msg_sender3]        |(- 100000000000)                        |
-------------------------------------------------------------------------
|revenue                       |value                                   |
-------------------------------------------------------------------------

|winner                        |value                                   |
-------------------------------------------------------------------------
|msg_sender3                   |"!3!"                                   |
-------------------------------------------------------------------------

hint
benefit:100000000001
optional benefit:100000000002
-------------------------------------------------------------------------
|optimal violate check         |value                                   |
**************************************
*    outcome pattern                 *
**************************************
*************************************
*         report                    *
*************************************
* model construction time: 2.329s
*  property checking time: 0.077s
*              total time: 2.406s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:7-0
*collusion-free:7-0
*       optimal:7-0
*     efficient:7-1
*************************************
