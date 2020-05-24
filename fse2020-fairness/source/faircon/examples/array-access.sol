contract Test {
    uint[5] a;
    uint b;

    function getUserBalance() public {
        a[0] = a[0] + 1;

        if(a[0] > b) {
            a[1] = a[0] + 5;
        }
        else {
            a[2] = a[2] + b;
        }

        (uint c, uint d) = (2,2);
    }

}