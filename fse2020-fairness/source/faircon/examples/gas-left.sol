contract Gas {
    uint gasLeft;
    uint a;

    function getGasLeft() public returns (uint gas) {
        // Assertion `funcDef != nullptr' failed.
        gasLeft = gasleft();
        return gasLeft;
    }

    function _Main_() public {
        a = getGasLeft();
    }
}