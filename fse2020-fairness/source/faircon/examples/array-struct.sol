contract Test {

    struct Happy {
        uint cc;
        uint dd;
    }

    Happy[5] happyArray;

    function getUserBalance() public {
        Happy memory happy0;
        happy0.cc = 1;
        happy0.dd = 2;

        happyArray[0] = happy0;

        Happy memory happy1;
        happy1.cc = 3;
        happy1.dd = 4;

        happyArray[1] = happy1;

        assert(happyArray[0].cc == 1);
    }
}