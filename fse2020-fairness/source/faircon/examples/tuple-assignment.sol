contract Test {
    uint a;
    uint b;
    uint c;

    function test() public {
        (a,b,c) = (1,2,3);
        (a,b,c) = (a + 1, b + 1, c + 1);
    }

}