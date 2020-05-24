contract Test {
    uint[5] a;
    uint b;

    struct Happy {
        uint cc;
        uint dd;
    }

    Happy gg;

    function getUserBalance() public {
        Happy memory happy;
        happy.cc = 1;
        happy.dd = 2;

        gg.cc = happy.cc;
        gg.dd = 4;
    }

}