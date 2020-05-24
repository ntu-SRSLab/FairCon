contract Bank {
    uint a;
    uint b;
    uint c;
    uint d;

    function add(uint x, uint y) public returns (uint r, uint s){

        if(x > y) {
            r = x + y;
            s = x * y;
        }
        else {
            r = x + 3;
            s = y + 3;
        }

        return (r,s);
    }

    // function _Main_() public {
    //     a = 5;
    //     b = 4;

    //     (c, d) = add(a, b);

    // }
}