analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: highestBidder@15, value: highestBidder@15_0_, sort: String
	varName: previousHighestBidder@13, value: previousHighestBidder@13_0_, sort: String
	varName: highestBid@11, value: highestBid@11_0_, sort: Int
	varName: payments@99, value: payments@99_0_, sort: (Array String Int)
	varName: auctionsStartBid@9, value: auctionsStartBid@9_0_, sort: Int
	varName: auctionEnd@7, value: auctionEnd@7_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: benefits@95, value: benefits@95_0_, sort: (Array String Int)
	varName: utilities@91, value: utilities@91_0_, sort: (Array String Int)
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: percentageBidIncrease@5, value: percentageBidIncrease@5_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: ended@3, value: ended@3_0_, sort: Bool
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
local variables: 
	varName: winners_count@453, value: winners_count@453_0_, sort: Int
	varName: block_timestamp3@223, value: block_timestamp3@223_0_, sort: Int
	varName: msg_gas3@221, value: msg_gas3@221_0_, sort: Int
	varName: block_timestamp2@213, value: block_timestamp2@213_0_, sort: Int
	varName: msg_gas2@211, value: msg_gas2@211_0_, sort: Int
	varName: p2@207, value: p2@207_0_, sort: Int
	varName: msg_sender2@205, value: msg_sender2@205_0_, sort: String
	varName: msg_value3@219, value: msg_value3@219_0_, sort: Int
	varName: block_timestamp1@203, value: block_timestamp1@203_0_, sort: Int
	varName: b@135, value: b@135_0_, sort: Int
	varName: a@133, value: a@133_0_, sort: Int
	varName: a@101, value: a@101_0_, sort: String
	varName: v_2@149, value: v_2@149_0_, sort: Int
	varName: msg_sender3@215, value: msg_sender3@215_0_, sort: String
	varName: allocation@167, value: allocation@167_0_, sort: String
	varName: u@131, value: u@131_0_, sort: Int
	varName: a@125, value: a@125_0_, sort: Int
	varName: msg_value@19, value: msg_value@19_0_, sort: Int
	varName: previousHighestBidder@75, value: previousHighestBidder@75_0_, sort: String
	varName: claimBidPrice@37, value: claimBidPrice@37_0_, sort: Int
	varName: p3@217, value: p3@217_0_, sort: Int
	varName: a@107, value: a@107_0_, sort: Int
	varName: amountRequiredToOutBid@48, value: amountRequiredToOutBid@48_0_, sort: Int
	varName: u12@141, value: u12@141_0_, sort: Int
	varName: bidValue@66, value: bidValue@66_0_, sort: Int
	varName: allocation@155, value: allocation@155_0_, sort: String
	varName: a@113, value: a@113_0_, sort: Int
	varName: block_timestamp@21, value: block_timestamp@21_0_, sort: Int
	varName: v_1@145, value: v_1@145_0_, sort: Int
	varName: v1@143, value: v1@143_0_, sort: Int
	varName: v2@147, value: v2@147_0_, sort: Int
	varName: other_allocation@189, value: other_allocation@189_0_, sort: String
	varName: msg_gas1@201, value: msg_gas1@201_0_, sort: Int
	varName: msg_sender@17, value: msg_sender@17_0_, sort: String
	varName: player@157, value: player@157_0_, sort: String
	varName: allocation@175, value: allocation@175_0_, sort: String
	varName: benefit@165, value: benefit@165_0_, sort: Int
	varName: other_allocation@169, value: other_allocation@169_0_, sort: String
	varName: msg_value2@209, value: msg_value2@209_0_, sort: Int
	varName: a@119, value: a@119_0_, sort: Int
	varName: player@177, value: player@177_0_, sort: String
	varName: payment@179, value: payment@179_0_, sort: Int
	varName: benefit@185, value: benefit@185_0_, sort: Int
	varName: p1@197, value: p1@197_0_, sort: Int
	varName: allocation@187, value: allocation@187_0_, sort: String
	varName: benefit@159, value: benefit@159_0_, sort: Int
	varName: msg_sender1@195, value: msg_sender1@195_0_, sort: String
	varName: msg_value1@199, value: msg_value1@199_0_, sort: Int
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
symbolically execute function [_Main_]
Using Z3 solver to optimize value expression
-------------------------------------------------------------------------
-------------------------------------------------------------------------
-------------------------------------------------------------------------
--------------------------------OUTCOME-------------------------------------
|truthful violate check        |value                                   |
-------------------------------------------------------------------------
|utilities[msg_sender1]        |Untruthful                              |
-------------------------------------------
|Untruthful Case                          |
-------------------------------------------
----------------State Variable-----------------------
|name                |value               |
|highestBidder       |"!0!"               |
|highestBid          |100000000020        |
|payments            |((as const (Array String Int)) 0)|
|auctionsStartBid    |100000000000        |
|auctionEnd          |0                   |
|benefits            |(store ((as const (Array String Int)) 0) "!0!" 100000000020)|
|utilities           |((as const (Array String Int)) 0)|
|percentageBidIncrease|10                  |
|ended               |false               |
----------------Local Variable-----------------------
|winners_count       |1                   |
|block_timestamp3    |0                   |
|block_timestamp2    |0                   |
|p2                  |100000000001        |
|msg_sender2         |"!2!"               |
|msg_value3          |100000000001        |
|block_timestamp1    |0                   |
|msg_sender3         |"!3!"               |
|msg_value           |100000000001        |
|previousHighestBidder|"!1!"               |
|claimBidPrice       |110000000022        |
|p3                  |100000000001        |
|amountRequiredToOutBid|110000000022        |
|bidValue            |100000000001        |
|block_timestamp     |0                   |
|msg_sender          |"!3!"               |
|msg_value2          |100000000001        |
|p1                  |100000000020        |
|msg_sender1         |"!0!"               |
|msg_value1          |100000000020        |
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
msg_value1@199_0_: 100000000020
msg_value1@199_0_#2: 100000000010
a's utility::0
new a's utility:10
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
* model construction time: 1.569s
*  property checking time: 0.099s
*              total time: 1.668s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:4-1
*collusion-free:4-0
*       optimal:4-0
*     efficient:4-0
*************************************
