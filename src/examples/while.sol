contract Bank {
    uint a;
    uint b;

    function _Main_() public {
        uint i;
        a = 2;

        i = 0;
        while(i < a) {
            b = b + i;
            i = i + 1;
        }
    }
}