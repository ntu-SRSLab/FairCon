contract Bank {
    uint a;
    uint b;

    function _Main_() public {
        a = 5;
        b = 0;

        for(uint i = 0; i < a; i++){
            if(i == 3) {
                break;
            }

            for(uint j = 0; j < i; j++){
                if(j == 2) {
                    continue;
                }

                b = b + i + j;
            }
        }

        b = b + a;

        assert(b == 11);
    }
}