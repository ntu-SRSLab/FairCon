contract Bank {
    uint a;

    function fibonacci(uint x) public returns (uint r){
        if(x == 1) {
            return 1;
        }
        else if(x == 2){
            return 1;
        }
        else {
            uint num1;
            uint num2;
            num1 = fibonacci(x-1);
            num2 = fibonacci(x-2);
            return num1 + num2;
        }
    }

    function _Main_() public {
        a  = fibonacci(7);

        assert(a == 13);
    }
}