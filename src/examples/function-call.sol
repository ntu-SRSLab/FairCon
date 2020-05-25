contract Bank {
    uint a;
    uint b;
    uint c;

    function add(uint x, uint y) public returns (uint r){
        r = x + y;

        return r;
    }

    function _Main_() public {
        c = add(a, b);
    }
}