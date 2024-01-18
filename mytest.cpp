#include "checkers.h"
using namespace std;
class Tester {
public:
  // The following is implemented as a sample test function.
  // This function tests whether the function play(...) performs
  //  a capturing move successfully or not.
  // Please note, before calling this test function we have set
  //  the state of the game to a certain state
  // Moreover note, After calling this test function the state
  //  of the of the game will change
  bool testCaptureSuccess(Checkers &checkers) {
    bool result = true;
    // before play we expect a BCELL in (3,2)
    result = result && (checkers.m_game[3][2] == BCELL);
    // before play we expect a WDISK in (1,4)
    result = result && (checkers.m_game[1][4] == WDISK);
    // before play we expect that it is WPLAYER turn to play
    result = result && (checkers.m_currPlayer == WPLAYER);
    // before play we expect a BDISK in (2,3), there is an opponent disk
    result = result && (checkers.m_game[2][3] == BDISK);
    // store the ccurrent opponent number if disks
    int opponentDisks = checkers.m_blackDisks;
    // now call the play(...) function
    result = checkers.play(pair<int, int>(1, 4), pair<int, int>(3, 2));
    // we are trying to move (1,4) to (3,2), we expect that move is successful
    // after play we expect a BCELL in (1,4)
    result = result && (checkers.m_game[1][4] == BCELL);
    // after play we expect a WDISK in (3,2)
    result = result && (checkers.m_game[3][2] == WDISK);
    // after play we expect that it is BPLAYER turn
    result = result && (checkers.m_currPlayer == BPLAYER);
    // after play we expect a BCELL in (2,3), an opponent disk is captured
    result = result && (checkers.m_game[2][3] == BCELL);
    // after play we expect one less disk for the opponent
    result = result && (checkers.m_blackDisks == (opponentDisks - 1));
    return result;
  }

  bool testConstructor(Checkers &checkers) {
    bool var = true;
    checkers.initBoard();
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    if (checkers.m_numRows > 0 && checkers.m_numColumns > 0 &&
        checkers.m_game != nullptr) {
      for (int i = 0; i < checkers.m_numRows; i++) {
        for (int j = 0; j < checkers.m_numColumns; j++) {
          if (checkers.m_game[i][j] != BCELL &&
              checkers.m_game[i][j] != WCELL) // makes sure there is atleast one
                                              // cell either black or white
            var = false;
        }
      }
    } else {
      var = false;
    }
    return var;
  }

  bool testPromoteWhiteKing(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BCELL, "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "",    BDISK, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "",    WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "",    "",    "", "",    WDISK, "",
        BCELL, "", BCELL, "",    "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    BCELL, "",    "", "",
    };

    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(5, 2), pair<int, int>(7, 4));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (result && checkers.m_game[7][4] ==
                      WKING) { // checks if the given element is BKING
      var = true;
    }

    return var;
  }

  bool testPromoteBlackKing(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BCELL, "",    "",    "",    "", "",    "",    BDISK,
        "",    "", "",    "",    "",    "",    BDISK, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "",    WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "",    "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    BCELL, "",    "", "",
    };

    checkers.setGameState(game, size, BPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(1, 2), pair<int, int>(0, 3));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (result && checkers.m_game[0][3] ==
                      BKING) { // checks if the given element is BKING
      var = true;
    }

    return var;
  }

  bool testBlackKingCaptureBR(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BKING, "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", "",    "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "", WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "", "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", "",    "", "",
    };

    checkers.setGameState(game, size, BPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(0, 3), pair<int, int>(2, 5));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (result && checkers.m_game[2][5] == BKING &&
        checkers.m_game[1][4] ==
            BCELL) { // checks if grid 2,5 is still BKING and checks if the
                     // captured disk is removed from the board
      var = true;
    }

    return var;
  }

  bool testBlackKingCaptureBL(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BKING, "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", BCELL, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "", WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "", "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", "",    "", "",
    };

    checkers.setGameState(game, size, BPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(0, 3), pair<int, int>(2, 1));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (result && checkers.m_game[2][1] == BKING &&
        checkers.m_game[1][2] ==
            BCELL) { // checks if grid 2,1 is still BKING and checks if the
                     // captured disk is removed from the board
      var = true;
    }

    return var;
  }

  bool testMovePlayerError(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BKING, "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", BCELL, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "", WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "", "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", "",    "", "",
    };

    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(0, 3), pair<int, int>(2, 1));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (!result && checkers.m_game[0][3] == BKING &&
        checkers.m_game[2][1] ==
            BCELL) { // checks if the board is same as initial stage because
                     // this is error case
      var = true;
    }

    return var;
  }

  bool testMoveInputError(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BKING, "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", BCELL, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "", WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "", "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "", "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "", "",    "", "",
    };

    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(1, 0), pair<int, int>(0, -1));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (!result && checkers.m_game[1][0] ==
                       WDISK) { // checks if  2,1 is still BKING and checks if
                                // the captured disk is removed from the board
      var = true;
    }

    return var;
  }

  bool testGameState(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = 72;
    CELL game[size] = {"", "",    "", BKING, "", "", "",    "", "",
                       "", "",    "", "",    "", "", "",    "", BCELL,
                       "", BDISK, "", BCELL, "", "", WDISK, "", "",
                       "", WDISK, "", WDISK, "", "", "",    "", BDISK,
                       "", BDISK, "", "",    "", "", BCELL, "", BCELL,
                       "", BCELL, "", "",    "", "", "",    "", "",
                       "", "",    "", "",    "", "", "",    "", "",
                       "", "",    "", "",    "", "", "",    "", ""};

    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    if (checkers.m_numRows == DEFBOARDSIZE &&
        checkers.m_numColumns == DEFBOARDSIZE) {
      var = true;
    }

    return var;
  }

  bool testCountDisks(Checkers &checkers) {
    checkers.initBoard();
    checkers.initGame();
    int wd = 0, bd = 0;
    bool var = true;
    for (int i = 0; i < checkers.m_numRows; i++) {
      for (int j = 0; j < checkers.m_numColumns; j++) {
        if (checkers.m_game[i][j] == WDISK) {
          wd++;
        } else if (checkers.m_game[i][j] == BDISK) {
          bd++;
        }
      }
    }
    if ((wd != bd) && (wd != checkers.m_whiteDisks) &&
        (bd != checkers.m_blackDisks)) {
      var = false; // updates the number white disks
    }
    if (var) {
      cout << "White disks: " << wd << endl;
      cout << "Black disks: " << bd << endl;
    }
    return var;
  }






bool testWhiteKingCaptureBL(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
        "",    "", "",    BCELL, "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "",    BDISK, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "",    WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "",    "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    WKING, "",    "", "",
    };

    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(7, 4), pair<int, int>(5, 6));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (result && checkers.m_game[5][6] == WKING &&
        checkers.m_game[6][5] ==
            BCELL) { // checks if grid 2,5 is still BKING and checks if the
                     // captured disk is removed from the board
      var = true;
    }

    return var;
  }



bool testWhiteKingCaptureBR(Checkers &checkers) {
    bool var = false;
    checkers.initBoard();
    checkers.initGame();
    const int size = DEFBOARDSIZE * DEFBOARDSIZE;
    CELL game[size] = {
      "",    "", "",    BCELL, "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    "",    BDISK, "", BDISK, "",    BCELL,
        "",    "", WDISK, "",    "",    "",    WDISK, "", WDISK, "",    "",
        "",    "", BDISK, "",    BDISK, "",    "",    "", "",    BCELL, "",
        BCELL, "", BCELL, "",    "",    "",    "",    "", "",    "",    "",
        "",    "", "",    "",    "",    WKING, "",    "", "",
    };

    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    cout << "INTIAL BOARD:\n" << endl;
    checkers.dumpGame();
    bool result = checkers.play(pair<int, int>(7, 4), pair<int, int>(5, 2));
    cout << "AFTER MOVE:\n" << endl;
    checkers.dumpGame();
    if (result && checkers.m_game[5][2] == WKING &&
        checkers.m_game[6][3] ==
            BCELL) { // checks if grid 2,5 is still BKING and checks if the
                     // captured disk is removed from the board
      var = true;
    }

    return var;
  }
  /******************************************
   * Test function declarations go here! *
   ******************************************/
};

int main() {
  Tester tester;
  Checkers checkers(DEFBOARDSIZE, DEFBOARDSIZE);
  checkers.initBoard();
  cout << "\nthe following is the rendering of the board:\n\n";
  checkers.dumpGame(); // render the board
  checkers.initGame();
  cout << "\nthe following shows the initial state of the game:\n\n";
  checkers.dumpGame(); // render the initial state of the game
  cout << "________________________________________________________\n" << endl;
  const int size = DEFBOARDSIZE * DEFBOARDSIZE;
  CELL game[size] = {
      "",    "",    "",    "", "",    "", "",    "", "",    "",    "",
      "",    "",    "",    "", "",    "", BCELL, "", BDISK, "",    BCELL,
      "",    BCELL, WDISK, "", "",    "", WDISK, "", WDISK, "",    "",
      "",    "",    BDISK, "", BDISK, "", "",    "", "",    BCELL, "",
      BCELL, "",    BCELL, "", "",    "", "",    "", "",    "",    "",
      "",    "",    "",    "", "",    "", "",    "", "",
  };
  // set the current state of the game to a certain pre-defined state
  checkers.setGameState(game, size, WPLAYER);
  cout << "\nthe following shows the current state of the game:\n\n";
  checkers.dumpGame(); // render the current state of the game
  cout << "\nthe following tests a capturing move for which we expect "
          "success:\n\n";
  if (tester.testCaptureSuccess(checkers))
    cout << "\ttestCaptureSuccess() returned true." << endl;
  else
    cout << "\ttestCaptureSuccess() returned false." << endl;
  cout << "\nthe following shows the state of the game after the capturing "
          "move:\n\n";
  checkers.dumpGame(); // render the current state of the game
  checkers.reportLostDisks();
  cout << endl;

  cout << "________________________________________________________\n" << endl;

  // testing creating a normal case
  Checkers checker(10, 10);
  cout << "Testing normal case constructor: \n\n";
  cout << "Provided with input 10, 10 ---> should print empty board of size "
          "10*10: \n\n";

  if (tester.testConstructor(checker))
    cout << "\tNormal case constructor passed!\n";
  else
    cout << "\tNormal case constructor failed!\n";

  cout << "________________________________________________________\n" << endl;

  // testing error case
  Checkers checkers1(-3, 7);
  cout << "Testing error case constructor: \n\n";
  cout << "Provided with input -3, 7 ---> should print nothing \n\n";

  if (!tester.testConstructor(checkers1))
    cout << "\tError case constructor passed!\n";
  else
    cout << "\tError case constructor failed!\n";

  cout << "________________________________________________________\n" << endl;

  // testing error case
  Checkers checkers9(2, 3);
  cout << "Testing error case constructor: \n\n";
  cout << "Provided with input 2, 3 ---> should print nothing \n\n";

  if (!tester.testConstructor(checkers1))
    cout << "\tError case constructor passed!\n";
  else
    cout << "\tError case constructor failed!\n";

  cout << "________________________________________________________\n" << endl;
  // testing if disk promotes to king
  Checkers checkers10(12, 12);

  cout << "Testing initGame(): \n\n";
  cout << "Provided with input of (12,12) --> should print 18: \n\n";

  if (tester.testCountDisks(checkers10)) {
    cout << "Disks are tallied! Test passed!\n" << endl;
  } else {
    cout << "Disks are not tallied! Test failed!\n" << endl;
  }
  cout << "________________________________________________________\n" << endl;
  // testing if disk promotes to king
  Checkers checkers2(DEFBOARDSIZE, DEFBOARDSIZE);

  cout << "Testing king promotion: \n\n";
  cout << "Provided with input of (5,2) AND (7,4) ---> should print WK at "
          "(7,4): \n\n";

  if (tester.testPromoteWhiteKing(checkers2)) {
    cout << "Promoting to king! Test passed!\n" << endl;
  } else {
    cout << "Not promoting to king! Test failed!\n" << endl;
  }

  cout << "________________________________________________________\n" << endl;

  Checkers checkers8(DEFBOARDSIZE, DEFBOARDSIZE);

  cout << "Testing black king promotion: \n\n";
  cout << "Provided with input of (1,2) AND (0,3) ---> should print BK at "
          "(0,3): \n\n";

  if (tester.testPromoteBlackKing(checkers8)) {
    cout << "Promoting to king! Test passed!\n" << endl;
  } else {
    cout << "Not promoting to king! Test failed!\n" << endl;
  }

  cout << "________________________________________________________\n" << endl;

  // testing if king capture bottom right
  Checkers checkers3(DEFBOARDSIZE, DEFBOARDSIZE);
  cout << "Testing black king capture (bottom right): \n" << endl;
  cout << "Provided with input of (0,3) AND (2,5) ---> should capture WD at "
          "(1,4): \n\n";
  if (tester.testBlackKingCaptureBR(checkers3)) {
    cout << "Capture successful! Test passed!\n" << endl;
  } else {
    cout << "Capture unsuccessful! Test failed!\n" << endl;
  }


   cout << "________________________________________________________\n" << endl;

  // testing if king capture bottom right
  Checkers checkers11(DEFBOARDSIZE, DEFBOARDSIZE);
  cout << "Testing white king capture (bottom right): \n" << endl;
  cout << "Provided with input of (7,4) AND (5, 2) ---> should capture BD at (6,3)\n\n";
  if (tester.testWhiteKingCaptureBR(checkers11)) {
    cout << "Capture successful! Test passed!\n" << endl;
  } else {
    cout << "Capture unsuccessful! Test failed!\n" << endl;
  }



   cout << "________________________________________________________\n" << endl;

  // testing if king capture bottom right
  Checkers checkers12(DEFBOARDSIZE, DEFBOARDSIZE);
  cout << "Testing white king capture (bottom left): \n" << endl;
  cout << "Provided with input of (7,4) AND (5,6) ---> should capture BD at (6,5)\n\n";
  if (tester.testWhiteKingCaptureBL(checkers12)) {
    cout << "Capture successful! Test passed!\n" << endl;
  } else {
    cout << "Capture unsuccessful! Test failed!\n" << endl;
  }

  cout << "________________________________________________________\n" << endl;

  // testing if king captures bottom left
  Checkers checkers4(DEFBOARDSIZE, DEFBOARDSIZE);
  cout << "Testing black king capture (bottom right): \n" << endl;
  cout << "Provided with input of (0,3) AND (2,1) ---> should capture WD at "
          "(1,2): \n\n";
  if (tester.testBlackKingCaptureBL(checkers4)) {
    cout << "Capture successful! Test passed!\n" << endl;
  } else {
    cout << "Capture unsuccessful! Test failed!\n" << endl;
  }

  cout << "________________________________________________________\n" << endl;

  // testing error when given wrong player
  Checkers checkers5(DEFBOARDSIZE, DEFBOARDSIZE);

  cout << "Testing move when wrong player input. \n" << endl;
  cout << "Provided with input of WPLAYER; (0,3); (2,1) ---> should not "
          "change: \n\n";
  if (tester.testMovePlayerError(checkers5)) {
    cout << "Move failed! Test passed!\n" << endl;
  } else {
    cout << "Move passed! Test failed!\n" << endl;
  }

  cout << "________________________________________________________\n" << endl;

  // testing move when wromg co-ordinates are given
  Checkers checkers6(DEFBOARDSIZE, DEFBOARDSIZE);
  cout << "Testing move when wrong co-ordinates are given. \n" << endl;
  cout << "Provided with input of WPLAYER; (1,0); (0,-1) ---> should not "
          "change: \n\n";
  if (tester.testMoveInputError(checkers6)) {
    cout << "Move failed! Test passed!\n" << endl;
  } else {
    cout << "Move passed! Test failed!\n" << endl;
  }
  cout << "________________________________________________________\n" << endl;

  // testing error if given non square number
  Checkers checkers7(DEFBOARDSIZE, DEFBOARDSIZE);
  cout << "Testing setGameState when wrong input. \n" << endl;
  cout << "Provided with input of size as 72 ---> should print default board: "
          "\n\n";
  if (tester.testGameState(checkers7)) {
    cout << "Default set correctly! Test passed!\n" << endl;
  } else {
    cout << "Default set incorrectly! Test failed!\n" << endl;
  }
  cout << "________________________________________________________\n" << endl;

  return 0;
}