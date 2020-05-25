contract Bank {
    uint a;
    uint b;
    uint c;

    function _Main_() public {
        uint i;
        a = 5;
        b = 0;
        uint c;
        c = 10;

        i = 0;
        while(i < a) {
            uint c;
            c = i;

            if(i == 3) {
                return;
            }

            b = b + i;
            i = i + 1;

            c = c + b;
        }

        assert(b == 3);
    }
}