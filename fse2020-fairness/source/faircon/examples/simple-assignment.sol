contract Bank {
    uint a;
    uint b;

    function getUserBalance() public {
        a = a + 2;

        if(a > b) {
            a = a + 5;
        }
        else {
            a = a + b;
        }
    }

}