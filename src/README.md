# Solidity-SEE
Solidity-SEE is a Symbolic Execution Engine (SEE) for the Solidity programming language.

### System Dependencies

The following are needed for building/running Solidity-SEE:

-   [z3](https://github.com/Z3Prover/z3) (version >= 4.4)
-   boost (version >= 1.5) (sudo apt install libboost-all-dev)
-   [jsoncpp](https://github.com/open-source-parsers/jsoncpp)


### How to Build

Get into the `Solidity-SEE/` directory and enter the following command:

`mkdir build & cd build`

`cmake .. & make`

Building may take a while.


### How to Run

After building successfully, get into the `/Solidity-SEE/build/solse` directory and enter the following command to run examples in the `examples/` directory

`./solse -symexe ../../examples/function-call.sol`

To only symbolically execute the `_Main_` function of a smart contract, use the `-symexe-main` option. For example,

 `./solse -symexe-main ../../examples/function-call.sol`
