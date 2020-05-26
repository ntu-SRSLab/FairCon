analyzing contract [ hotPotatoAuction ]
exit contract [ hotPotatoAuction ]
analyzing contract [ hotPotatoAuction ]
exit contract [ hotPotatoAuction ]
state variables: 
	varName: payments@418, value: payments@418_0_, sort: (Array String Int)
	varName: startingPrice@5, value: startingPrice@5_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: currentBid@7, value: currentBid@7_0_, sort: Int
	varName: seller@15, value: seller@15_0_, sort: String
	varName: totalBids@3, value: totalBids@3_0_, sort: Int
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: auctionEnd@11, value: auctionEnd@11_0_, sort: Int
	varName: hotPotatoPrize@13, value: hotPotatoPrize@13_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: currentMinBid@9, value: currentMinBid@9_0_, sort: Int
	varName: balanceOf@60, value: balanceOf@60_0_, sort: (Array String Int)
	varName: highBidder@17, value: highBidder@17_0_, sort: String
	varName: loser@19, value: loser@19_0_, sort: String
	varName: utilities@410, value: utilities@410_0_, sort: (Array String Int)
	varName: benefits@414, value: benefits@414_0_, sort: (Array String Int)
local variables: 
	varName: msg_gas3@540, value: msg_gas3@540_0_, sort: Int
	varName: p3@536, value: p3@536_0_, sort: Int
	varName: msg_sender3@534, value: msg_sender3@534_0_, sort: String
	varName: msg_gas2@530, value: msg_gas2@530_0_, sort: Int
	varName: msg_value2@528, value: msg_value2@528_0_, sort: Int
	varName: p2@526, value: p2@526_0_, sort: Int
	varName: msg_sender2@524, value: msg_sender2@524_0_, sort: String
	varName: msg_gas1@520, value: msg_gas1@520_0_, sort: Int
	varName: msg_value1@518, value: msg_value1@518_0_, sort: Int
	varName: p1@516, value: p1@516_0_, sort: Int
	varName: a@426, value: a@426_0_, sort: Int
	varName: a@438, value: a@438_0_, sort: Int
	varName: a@420, value: a@420_0_, sort: String
	varName: u12@460, value: u12@460_0_, sort: Int
	varName: block_timestamp1@522, value: block_timestamp1@522_0_, sort: Int
	varName: allocation@494, value: allocation@494_0_, sort: String
	varName: block_timestamp@309, value: block_timestamp@309_0_, sort: Int
	varName: payment@498, value: payment@498_0_, sort: Int
	varName: msg_value@307, value: msg_value@307_0_, sort: Int
	varName: ret@134, value: ret@134_0_, sort: Bool
	varName: ret@295, value: ret@295_0_, sort: Int
	varName: a@444, value: a@444_0_, sort: Int
	varName: _auctionEnd@23, value: _auctionEnd@23_0_, sort: Int
	varName: _startingPrice@21, value: _startingPrice@21_0_, sort: Int
	varName: a@432, value: a@432_0_, sort: Int
	varName: other_allocation@508, value: other_allocation@508_0_, sort: String
	varName: block_timestamp2@532, value: block_timestamp2@532_0_, sort: Int
	varName: amount@62, value: amount@62_0_, sort: Int
	varName: ret@95, value: ret@95_0_, sort: Bool
	varName: msg_value3@538, value: msg_value3@538_0_, sort: Int
	varName: benefit@504, value: benefit@504_0_, sort: Int
	varName: amount@105, value: amount@105_0_, sort: Int
	varName: ret@65, value: ret@65_0_, sort: Bool
	varName: u@450, value: u@450_0_, sort: Int
	varName: b@454, value: b@454_0_, sort: Int
	varName: a@452, value: a@452_0_, sort: Int
	varName: v_1@464, value: v_1@464_0_, sort: Int
	varName: block_timestamp3@542, value: block_timestamp3@542_0_, sort: Int
	varName: benefit@484, value: benefit@484_0_, sort: Int
	varName: msg_sender@305, value: msg_sender@305_0_, sort: String
	varName: allocation@486, value: allocation@486_0_, sort: String
	varName: v2@466, value: v2@466_0_, sort: Int
	varName: v_2@468, value: v_2@468_0_, sort: Int
	varName: winners_count@802, value: winners_count@802_0_, sort: Int
	varName: allocation@474, value: allocation@474_0_, sort: String
	varName: v1@462, value: v1@462_0_, sort: Int
	varName: player@476, value: player@476_0_, sort: String
	varName: allocation@506, value: allocation@506_0_, sort: String
	varName: benefit@478, value: benefit@478_0_, sort: Int
	varName: other_allocation@488, value: other_allocation@488_0_, sort: String
	varName: msg_sender1@514, value: msg_sender1@514_0_, sort: String
	varName: player@496, value: player@496_0_, sort: String
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
|payments            |(store ((as const (Array String Int)) 0) "!0!" 100000000004)|
|startingPrice       |0                   |
|currentBid          |100000000004        |
|totalBids           |1                   |
|auctionEnd          |0                   |
|hotPotatoPrize      |5000000000          |
|currentMinBid       |150000000006        |
|balanceOf           |(store ((as const (Array String Int)) 0) "!0!" 105000000004)|
|highBidder          |"!0!"               |
|utilities           |((as const (Array String Int)) 0)|
|benefits            |(store ((as const (Array String Int)) 0) "!0!" 100000000004)|
----------------Local Variable-----------------------
|p3                  |100000000001        |
|msg_sender3         |"!3!"               |
|msg_value2          |100000000001        |
|p2                  |100000000001        |
|msg_sender2         |"!2!"               |
|msg_value1          |100000000004        |
|p1                  |100000000004        |
|block_timestamp1    |(- 1)               |
|block_timestamp     |(- 1)               |
|msg_value           |100000000001        |
|block_timestamp2    |(- 1)               |
|msg_value3          |100000000001        |
|block_timestamp3    |(- 1)               |
|msg_sender          |"!3!"               |
|winners_count       |1                   |
|msg_sender1         |"!0!"               |
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
msg_value1@518_0_: 100000000004
msg_value1@518_0_#2: 100000000002
a's utility::0
new a's utility:2
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
* model construction time: 5.443s
*  property checking time: 0.084s
*              total time: 5.527s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:12-1
*collusion-free:12-0
*       optimal:12-0
*     efficient:12-0
*************************************
