contract Bank {
   mapping(address=>uint) balances;


   function getUserBalance(address user) public view returns(uint u) {
     return balances[user];
   }

   function deposit() public payable {
     balances[msg.sender] += msg.value;
   }

   function receiveMondy() public payable {

   }

   function getMyBalance() public returns (uint b) {
       b = address(this).balance;
       return b;
   }


   function withdraw(uint amount) public {
     //balances[msg.sender]=p;

      //uint credit = balances[msg.sender];

      if( balances[msg.sender] >= amount) {
        balances[msg.sender] = balances[msg.sender] - amount;
        msg.sender.call.value(amount).gas(100)("");
      }
   }

    function _Main_() public payable {
        uint originalBalance = balances[msg.sender];
        require(balances[msg.sender] > 0);

        this.deposit.value(10).gas(20)();

        assert(balances[msg.sender] == originalBalance + 10);

        withdraw(10);

        assert(balances[msg.sender] == originalBalance);
    }

}
