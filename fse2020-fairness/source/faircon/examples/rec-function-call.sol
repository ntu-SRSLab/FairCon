contract Bank {
    uint a;

    function factorial(uint x) public returns (uint r){
        if(x == 1) {
            return 1;
        }
        else {
            uint temp;
            temp = factorial(x-1);
            return x * temp;
        }
    }

    function _Main_() public {
        a  = factorial(5);

        assert(a == 120);
    }
}