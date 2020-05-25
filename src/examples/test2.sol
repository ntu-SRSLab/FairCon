contract Bank {
   mapping(address=>uint) balances;
   uint a = 2;
   bool temp = true;
   mapping(address=>bool) availables;
   bytes32 cc;

   struct NewTupe{
     uint f_1;
     uint f_2;
   }

   mapping(address=>NewTupe) vecs;

   address user = msg.sender;
   string str = "abcdefghijk";

   function getUserBalance(address user) public view returns(uint result1) {
     return balances[user];
   }

   function deposit() public payable {
     balances[msg.sender] += msg.value;
   }



   function receiveMondy() public payable {

   }

   function getMyBalance() public returns (uint result2) {
       return address(this).balance;
   }

   function getTemp() public returns (bool result3){
     bool t = !temp;
     return t;
   }

   function returnTrue() public returns (bool result4){
     //availables[0] = true;
     //bytes1 aaa = cc[2];
     string memory strVar = str;

     NewTupe memory nt;
     nt.f_1 = 1;
     nt.f_2 = 2;

     return true;
   }

   function setTupe(address addr) public returns (uint result5){
     vecs[addr].f_1 = 1;
     vecs[addr].f_2 = 2;

    if(vecs[addr].f_1 == a){
      return 10;
    }
    else{
      return 5;
    }

     //msg.sender.transfer(10);
     msg.sender.call.value(10);

     return a;
   }

   function withdraw(uint amount) public {
     //balances[msg.sender]=p;

      //uint credit = balances[msg.sender];

      if( balances[msg.sender] >= amount) {
        balances[msg.sender] = balances[msg.sender] - amount;
        msg.sender.call.value(amount)("");
      }
   }

   function ccc(uint ll) public returns(uint result6) {
     if(a > ll){
       return 1;
     }
     else {
         return 3;
     }

     if(a == 10) {
         a = a + 3;
     }
     else{
         a = a - 3;
     }

     a = a + 1;

     msg.sender.call.value(10);
     return a;
   }
}