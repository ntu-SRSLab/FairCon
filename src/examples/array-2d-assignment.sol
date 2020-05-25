contract Test {
    uint[5][5] a;
    uint b;

    function test() public {
        a[0][0] = a[0][0] + 1;
    }

}