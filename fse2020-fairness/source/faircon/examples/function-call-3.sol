contract Bank {
    uint a;
    uint b;
    uint c;
    uint d;

    function add(uint x, uint y) public returns (uint r, uint s){
        uint t;
        uint p;

        t = x + y;
        p = x * y;

        return (t,p);
    }

    function _Main_() public {
        (c,d) = add(a, b);
        (a,b) = add(c, d);
    }
}