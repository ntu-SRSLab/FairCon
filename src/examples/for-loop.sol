contract Bank {
    uint a;
    uint b;

    function _Main_() public {
        a = 3;
        b = 0;

        for(uint i = 0; i < a; i++){
            for(uint j = 0; j < i; j++){
                b = b + i + j;
            }
        }

        b = b + a;

        assert(b == 9);
    }
}