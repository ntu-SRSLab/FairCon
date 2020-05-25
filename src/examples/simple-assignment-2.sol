contract Bank {
    uint a;
    uint b;

    function getUserBalance() public {
        a = 10;
        b = 2;

        a += b;
        b *= a;

        assert(a == 12);
        assert(b == 24);
    }

}