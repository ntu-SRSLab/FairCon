contract Bank {
    uint a;
    uint b;

    function _Main_() public {
        uint i;
        a = 5;

        i = 0;
        while(i < a) {

            if(i == 3) {
                break;
            }

            b = b + i;
            i = i + 1;
        }
    }
}