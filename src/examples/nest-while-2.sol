contract Bank {
    uint a;
    uint b;

    function _Main_() public {
        uint i;
        uint j;

        a = 4;
        b = 0;

        i = 0;
        while(i < a) {
            i = i + 1;

            j = 0;
            while(j < i) {
                if(j == 2) {
                    break;
                }

                j = j + 1;
                b = b + i + j;
            }
        }

        b = b + a;

        assert(b == 33);
    }
}