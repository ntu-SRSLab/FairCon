contract Test {
    uint[5] a;
    uint b;

    struct Happy {
        uint cc;
        uint dd;
    }

    struct Mary {
        uint tt;
        Happy hh;
    }

    function getUserBalance() public {
        Happy memory happy;
        happy.cc = 1;
        happy.dd = 2;

        Mary memory mary;
        mary.tt = 3;
        mary.hh = happy;

        mary.hh.cc = 7;
    }

}