//pragma solidity ^0.4.0;

contract Sha3 {
    uint a = 2;
    bool c0 = true;
    mapping(address => mapping(address => uint)) credits;

    struct NewType{
        uint intOne;
        bool boolTwo;
        uint intThree;
    }

    function getUserBalance(uint x) public returns(uint result1) {
        uint b = 3;
        a = b + a;
        // bytes32 tmp = keccak256("hello world");// not supported by sse now.
        a = add(2, a+1);

        return a;
    }

    function add(uint y, uint m) public returns(uint result2) {
        //for(uint t = 0; t <= m; t = t + 1)[t <= m]{
        //    if(t == 3){
        //        break;
        //    }

        //    a = a + 1;
        //}

        a = a + y + m;

        return a;
    }

    function test(uint up) public {
        uint i = 0;
        uint[2] memory b0;
        uint[4][3] memory c;

        b0[0] = 1;
        i = i + b0[0];
        c[0][1] = 3;

        //while(i < up)[i == 1]{
        //    a = a + 1;
        //}

        msg.sender.call.value(300);
    }

    function test2() public returns (uint result3){
        NewType memory nt;
        nt.intOne = 1;
        nt.boolTwo = true;
        nt.intThree = 3;

        assert(nt.intOne == 1);
    }


    function test3() public returns (uint r3){
        uint k;
        uint r1 = 1;

        if(r1 > k){
            return r1 + 1;
        }

        r1 = r1 + r3;

        r3 = 3;
    }

    function test4() public {
        msg.sender.transfer(10);
        a = a + 2;

    }
}
