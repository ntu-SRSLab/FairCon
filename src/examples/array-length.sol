contract Test {
    uint[] a;
    uint b;

    function getLength() public returns (uint length) {

        // Assertion `funcDef != nullptr' failed (just as for .pop())
        a.push(1);

        // This member access is not supported currently
        length = a.length;
        return length;
    }

    function _Main_() public {
        b = getLength();
    }
}