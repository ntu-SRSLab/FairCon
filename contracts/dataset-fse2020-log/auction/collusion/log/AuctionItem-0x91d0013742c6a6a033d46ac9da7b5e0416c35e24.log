analyzing contract [ AuctionItem ]
exit contract [ AuctionItem ]
analyzing contract [ AuctionItem ]
exit contract [ AuctionItem ]
state variables: 
	varName: payments@199, value: payments@199_0_, sort: (Array String Int)
	varName: utilities@191, value: utilities@191_0_, sort: (Array String Int)
	varName: squak@23, value: squak@23_0_, sort: String
	varName: auctionEnded@8, value: auctionEnded@8_0_, sort: Bool
	varName: benefits@195, value: benefits@195_0_, sort: (Array String Int)
	varName: highBidder@21, value: highBidder@21_0_, sort: String
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: currentHighestBid@19, value: currentHighestBid@19_0_, sort: Int
	varName: owner@5, value: owner@5_0_, sort: String
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: auctionName@3, value: auctionName@3_0_, sort: String
local variables: 
	varName: winners_count@532, value: winners_count@532_0_, sort: Int
	varName: block_timestamp3@323, value: block_timestamp3@323_0_, sort: Int
	varName: msg_gas3@321, value: msg_gas3@321_0_, sort: Int
	varName: p3@317, value: p3@317_0_, sort: Int
	varName: msg_gas2@311, value: msg_gas2@311_0_, sort: Int
	varName: p2@307, value: p2@307_0_, sort: Int
	varName: v1@243, value: v1@243_0_, sort: Int
	varName: player@257, value: player@257_0_, sort: String
	varName: benefit@259, value: benefit@259_0_, sort: Int
	varName: msg_value2@309, value: msg_value2@309_0_, sort: Int
	varName: msg_value1@299, value: msg_value1@299_0_, sort: Int
	varName: u@231, value: u@231_0_, sort: Int
	varName: a@219, value: a@219_0_, sort: Int
	varName: block_timestamp2@313, value: block_timestamp2@313_0_, sort: Int
	varName: b@235, value: b@235_0_, sort: Int
	varName: a@207, value: a@207_0_, sort: Int
	varName: a@225, value: a@225_0_, sort: Int
	varName: a@233, value: a@233_0_, sort: Int
	varName: startingBid@59, value: startingBid@59_0_, sort: Int
	varName: name@57, value: name@57_0_, sort: String
	varName: allocation@275, value: allocation@275_0_, sort: String
	varName: msg_value3@319, value: msg_value3@319_0_, sort: Int
	varName: msg_value@164, value: msg_value@164_0_, sort: Int
	varName: msg_sender3@315, value: msg_sender3@315_0_, sort: String
	varName: v_2@249, value: v_2@249_0_, sort: Int
	varName: block_timestamp1@303, value: block_timestamp1@303_0_, sort: Int
	varName: a@201, value: a@201_0_, sort: String
	varName: v2@247, value: v2@247_0_, sort: Int
	varName: u12@241, value: u12@241_0_, sort: Int
	varName: allocation@255, value: allocation@255_0_, sort: String
	varName: benefit@285, value: benefit@285_0_, sort: Int
	varName: other_allocation@289, value: other_allocation@289_0_, sort: String
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
	varName: msg_sender@162, value: msg_sender@162_0_, sort: String
	varName: _squak@78, value: _squak@78_0_, sort: String
	varName: msg_gas1@301, value: msg_gas1@301_0_, sort: Int
	varName: msg_sender2@305, value: msg_sender2@305_0_, sort: String
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
|utilities[msg_sender1] + utilities[msg_sender2]|Colluded                                |
-------------------------------------------
|Colluded Case                            |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|payments            |(let ((a!1 (store (store (store ((as const (Array String Int)) 4) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!0!" 199999991144))|
|utilities           |(let ((a!1 (store (store (store ((as const (Array String Int)) 2) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!0!" 0))|
|benefits            |(let ((a!1 (store (store (store ((as const (Array String Int)) 3) "!3!" 0)
                         "!0!"
                         0)
                  "!2!"
                  0)))
  (store a!1 "!0!" 199999991144))|
|highBidder          |"!0!"               |
|squak               |squak@23_0_.length  |
|currentHighestBid   |199999991144        |
|auctionName         |auctionName@3_0_.length|
----------------Local Variable-----------------------
|winners_count       |1                   |
|p3                  |100000000002        |
|p2                  |199999991144        |
|msg_value2          |199999991144        |
|msg_value1          |199999991144        |
|msg_value3          |100000000002        |
|msg_value           |100000000002        |
|msg_sender3         |"!3!"               |
|msg_sender1         |"!0!"               |
|p1                  |199999991144        |
|msg_sender          |"!3!"               |
|msg_sender2         |"!2!"               |
-------------------------------------------

|utilities                     |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |0                                       |
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
msg_value1@299_0_:199999991144
msg_value2@309_0_:199999991144
msg_value1@299_0_#2:100000000001
msg_value2@309_0_#2:100000000002
v1&v2's utility:0
new v1&v2's colluded utility:99999991142
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
* model construction time: 1.322s
*  property checking time: 0.083s
*              total time: 1.405s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:4-0
*collusion-free:4-1
*       optimal:4-0
*     efficient:4-0
*************************************
