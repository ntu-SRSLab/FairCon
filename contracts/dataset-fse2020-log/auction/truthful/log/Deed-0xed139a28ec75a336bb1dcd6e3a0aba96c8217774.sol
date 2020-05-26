analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
analyzing contract [ Rewrite ]
exit contract [ Rewrite ]
state variables: 
	varName: payments@76, value: payments@76_0_, sort: (Array String Int)
	varName: benefits@72, value: benefits@72_0_, sort: (Array String Int)
	varName: winner@8, value: winner@8_0_, sort: String
	varName: secondhighestBid@6, value: secondhighestBid@6_0_, sort: Int
	varName: msg.value, value: msg.value_0_, sort: Int
	varName: utilities@68, value: utilities@68_0_, sort: (Array String Int)
	varName: minPrice@2, value: minPrice@2_0_, sort: Int
	varName: msg.sender, value: msg.sender_0_, sort: String
	varName: this.balance, value: this.balance_0_, sort: Int
	varName: block.timestamp, value: block.timestamp_0_, sort: Int
	varName: highestBid@4, value: highestBid@4_0_, sort: Int
local variables: 
	varName: winners_count@484, value: winners_count@484_0_, sort: Int
	varName: block_timestamp3@200, value: block_timestamp3@200_0_, sort: Int
	varName: msg_price3@198, value: msg_price3@198_0_, sort: Int
	varName: msg_value3@196, value: msg_value3@196_0_, sort: Int
	varName: p3@194, value: p3@194_0_, sort: Int
	varName: msg_sender3@192, value: msg_sender3@192_0_, sort: String
	varName: msg_price2@188, value: msg_price2@188_0_, sort: Int
	varName: msg_value2@186, value: msg_value2@186_0_, sort: Int
	varName: v2@124, value: v2@124_0_, sort: Int
	varName: payment@156, value: payment@156_0_, sort: Int
	varName: v_1@122, value: v_1@122_0_, sort: Int
	varName: b@112, value: b@112_0_, sort: Int
	varName: v1@120, value: v1@120_0_, sort: Int
	varName: u@108, value: u@108_0_, sort: Int
	varName: a@90, value: a@90_0_, sort: Int
	varName: a@102, value: a@102_0_, sort: Int
	varName: msg_value@12, value: msg_value@12_0_, sort: Int
	varName: value@18, value: value@18_0_, sort: Int
	varName: a@84, value: a@84_0_, sort: Int
	varName: benefit@136, value: benefit@136_0_, sort: Int
	varName: a@96, value: a@96_0_, sort: Int
	varName: msg_price@14, value: msg_price@14_0_, sort: Int
	varName: a@110, value: a@110_0_, sort: Int
	varName: a@78, value: a@78_0_, sort: String
	varName: msg_sender@10, value: msg_sender@10_0_, sort: String
	varName: player@134, value: player@134_0_, sort: String
	varName: v_2@126, value: v_2@126_0_, sort: Int
	varName: other_allocation@146, value: other_allocation@146_0_, sort: String
	varName: p1@174, value: p1@174_0_, sort: Int
	varName: allocation@144, value: allocation@144_0_, sort: String
	varName: msg_sender2@182, value: msg_sender2@182_0_, sort: String
	varName: u12@118, value: u12@118_0_, sort: Int
	varName: benefit@142, value: benefit@142_0_, sort: Int
	varName: allocation@152, value: allocation@152_0_, sort: String
	varName: block_timestamp1@180, value: block_timestamp1@180_0_, sort: Int
	varName: block_timestamp2@190, value: block_timestamp2@190_0_, sort: Int
	varName: allocation@132, value: allocation@132_0_, sort: String
	varName: benefit@162, value: benefit@162_0_, sort: Int
	varName: allocation@164, value: allocation@164_0_, sort: String
	varName: other_allocation@166, value: other_allocation@166_0_, sort: String
	varName: msg_sender1@172, value: msg_sender1@172_0_, sort: String
	varName: player@154, value: player@154_0_, sort: String
	varName: msg_value1@176, value: msg_value1@176_0_, sort: Int
	varName: msg_price1@178, value: msg_price1@178_0_, sort: Int
	varName: p2@184, value: p2@184_0_, sort: Int
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
|utilities[msg_sender1]        |Truthful                                |
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
* model construction time: 5.829s
*  property checking time: 0.063s
*              total time: 5.892s
*  pattern [ fairness:(contexts)-(violates) ] 
*      truthful:15-0
*collusion-free:15-0
*       optimal:15-0
*     efficient:15-0
*************************************
