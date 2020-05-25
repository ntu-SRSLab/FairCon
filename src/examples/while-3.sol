contract Bank {
    uint a;
    uint b;

    function _Main_() public {
        uint i;
        a = 5;

        i = 0;
        while(i < a) {
            i = i + 1;

            if(i == 3) {
                continue;
            }

            b = b + i;
        }
    }
}