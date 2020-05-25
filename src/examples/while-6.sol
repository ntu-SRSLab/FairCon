contract Bank {
/* Seems like the global variables initial value
   can't be properly captured */
    uint a = 2;
    uint b;

    function _Main_() public {
        uint i;
    /* Uncommenting this assignment will restore
       the operation back to normal
        a = 2; */

        i = 0;

    // Thus, z3 cannot reason about this while
        while(i < a) {
            b = b + i;
            i = i + 1;
        }
    }
}