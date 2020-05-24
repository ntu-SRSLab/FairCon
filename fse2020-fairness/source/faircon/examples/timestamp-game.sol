contract game {
  uint registerDuration;
  uint endRegisterTime;
  address payable[] players;
  address payable owner;

  // constructor sets default registration duration to 180s
  constructor() public {
    registerDuration = 180;

    // Cannot get the name of the function call []
     owner = address(this);

    /*
    In case of a hardcoded address:
    owner = 0xf6E914D07d12636759868a61E52973d17ED7111B; --
    The literal [0xf6E914D07d12636759868a61E52973d17ED7111B] is not supported yet!! */
  }

  function () external payable {
     // Error! Cannot find z3::expr for the variable: block
     endRegisterTime = block.timestamp + registerDuration;

    // 'now' is an alias for 'block.timestamp'
    if (now > endRegisterTime) {
      // Neither the blockhash() function, nor block.number variable are supported
      uint winner = uint(blockhash(block.number - 1)) % players.length;


    /* This unary operation is not supported yes!
       'delete' applied to a variable to set all its bits to 0,
       to a dynamic array -- deletes all the elements and the length will become 0.
       But it's not that commonly used. */
      delete players;
     } else {
      // Assertion `funcDef != nullptr' failed
      revert();
    }
  }

  function destruct() private {
    if (msg.sender == owner) {
      // Assertion `funcDef != nullptr' failed
      selfdestruct(owner);
    }
  }
}