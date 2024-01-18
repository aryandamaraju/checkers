// UMBC - CMSC 341 - Spring 2023 - Proj0
#include "checkers.h"
Checkers::Checkers() {
  m_numRows = DEFBOARDSIZE;
  m_numColumns = DEFBOARDSIZE;
  m_whiteDisks = 12;
  m_blackDisks = 12;
  m_currPlayer = BPLAYER;
  m_game = new CELL *[m_numRows];
  for (int i = 0; i < m_numRows; i++) {
    m_game[i] = new CELL[m_numColumns];
  }
}

Checkers::Checkers(int rows, int columns) {
  if ((rows == columns) && rows > 7 && (rows % 2 == 0) &&
      (rows > 0)) { // input validation
    m_numRows = rows;
    m_numColumns = columns;
  } else {
    m_numRows = 0;
    m_numColumns = 0;
  }

  m_whiteDisks = (columns / 2 * 3); // assigns disk
  m_blackDisks = (columns / 2 * 3);
  m_currPlayer = BPLAYER;
  m_game = new CELL *[m_numRows];
  for (int i = 0; i < m_numRows; i++) {
    m_game[i] = new CELL[m_numColumns];
  }
}

Checkers::~Checkers() {
  for (int i = 0; i < m_numRows; i++) {
    delete[] m_game[i];
  }
  delete[] m_game;
  m_game = NULL;
}

void Checkers::clear() {
  for (int i = 0; i < m_numRows; i++) {
    delete[] m_game[i];
  }
  delete[] m_game;
  m_numRows = DEFBOARDSIZE;
  m_numColumns = DEFBOARDSIZE;
  m_whiteDisks = 12;
  m_blackDisks = 12;
  m_currPlayer = BPLAYER;
  m_game = NULL;
}

void Checkers::initBoard() {
  for (int i = 0; i < m_numRows; i++) {
    for (int j = 0; j < m_numColumns; j++) {
      if (i % 2 == 0) {   // checks if row co ordinate is even
        if (j % 2 == 0) { // checks if column co ordinate is even
          m_game[i][j] = WCELL;
        } else {
          m_game[i][j] = BCELL;
        }
      } else {
        if (j % 2 == 0) {
          m_game[i][j] = BCELL;
        } else {
          m_game[i][j] = WCELL;
        }
      }
    }
  }
}

void Checkers::reportLostDisks() {
  cout << "White player lost the following: "
       << ((m_numColumns / 2 * 3) - m_whiteDisks) << endl;
  cout << "Black player lost the following: "
       << ((m_numColumns / 2 * 3) - m_blackDisks) << endl;
}

void Checkers::initGame() {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < m_numColumns; j++) {
      if (m_game[i][j] == BCELL) {
        m_game[i][j] = WDISK; // populates white disks
      }
    }
  }

  for (int i = m_numRows - 1; i > m_numRows - 4; i--) {
    for (int j = 0; j < m_numColumns; j++) {
      if (m_game[i][j] == BCELL) {
        m_game[i][j] = BDISK; // populates black disks
      }
    }
  }
}

bool Checkers::play(pair<int, int> origin, pair<int, int> destination) {
  bool var = false;
  int x = origin.first;
  int y = origin.second;
  int a = destination.first;
  int b = destination.second;

  if (m_currPlayer == BPLAYER) {
    if (m_game[x][y] == BDISK) { // black disk
      if (y == 0) {
        if (y - 1 == b || y - 2 == b) {
          var = false;
        }
      } else if (y == m_numColumns - 1) {
        if (y + 1 == b || y + 2 == b) {
          var = false;
        }
      }
      if ((x >= 0 && x < m_numRows) && (y >= 0 && y < m_numColumns - 1) &&
          (a >= 0 && a < m_numRows) && (b >= 0 && b < m_numColumns - 1)) {
        if (x - 1 == a &&
            (y + 1 == b || y - 1 == b)) { // checks if move is possible
          if (m_game[a][b] != BDISK && m_game[a][b] != WDISK) {
            if (y == 0 && y + 1 == b)
              m_game[a][b] = BDISK;
            m_game[x][y] = BCELL;
            var = true;
          }
        } else if (x - 2 == a &&
                   (y + 2 == b)) { // checks to move towards top right capture
          if (m_game[x - 1][y + 1] == WDISK) {
            m_game[a][b] = BDISK;
            m_game[x][y] = BCELL;
            m_game[x - 1][y + 1] = BCELL;
            m_whiteDisks--;
            var = true;
          }
        } else if (x - 2 == a &&
                   (y - 2 == b)) { // checks to move towards top left capture
          if (m_game[x - 1][y - 1] == WDISK) {
            m_game[a][b] = BDISK;
            m_game[x][y] = BCELL;
            m_game[x - 1][y - 1] = BCELL;
            m_whiteDisks--;
            var = true;
          }
        }
        if (var == true) { // checks if move is possible and if the co-ordinate
                           // is 0 then promote it to king
          if (x == 0) {
            m_game[x][y] = BKING;
          } else if (a == 0) {
            m_game[a][b] = BKING;
          }
        }
      }
    } else if (m_game[x][y] == BKING) { // BLACK KING
      if ((x - 1 == a || x + 1 == a) &&
          (y + 1 == b || y - 1 == b)) { // checks for valid move
        if (m_game[a][b] != BDISK && m_game[a][b] != WDISK) {
          m_game[a][b] = BKING;
          m_game[x][y] = BCELL;
          var = true;
        }
      } else if (x - 2 == a && y + 2 == b) { // top right capture
        if (m_game[x - 1][y + 1] == WDISK) {
          m_game[a][b] = BKING;
          m_game[x][y] = BCELL;
          m_game[x - 1][y + 1] = BCELL;
          m_whiteDisks--;
          var = true;
        }
      } else if (x - 2 == a && y - 2 == b) { // top left capture
        if (m_game[x - 1][y - 1] == WDISK) {
          m_game[a][b] = BKING;
          m_game[x][y] = BCELL;
          m_game[x - 1][y - 1] = BCELL;
          m_whiteDisks--;
          var = true;
        }
      } else if (x + 2 == a && y + 2 == b) { // botton right capture
        if (m_game[x + 1][y + 1] == WDISK) {
          m_game[a][b] = BKING;
          m_game[x][y] = BCELL;
          m_game[x + 1][y + 1] = BCELL;
          m_whiteDisks--;
          var = true;
        }
      } else if (x + 2 == a && y - 2 == b) { // bottom left capture
        if (m_game[x + 1][y - 1] == WDISK) {
          m_game[a][b] = BKING;
          m_game[x][y] = BCELL;
          m_game[x + 1][y - 1] = BCELL;
          m_whiteDisks--;
          var = true;
        }
      }
    }
  } else if (m_currPlayer == WPLAYER) {
    if (y == 0) {
      if (y - 1 == b) {
        var = false;
      }
    } else if (y == m_numColumns - 1) {
      if (y + 1 == b) {
        var = false;
      }
    }
    if (m_game[x][y] == WDISK) { // white disk
      if ((x > 0 && x < m_numRows) && (y >= 0 && y < m_numColumns - 1) &&
          (a > 0 && a < m_numRows) && (b >= 0 && b < m_numColumns - 1)) {
        if (x + 2 == a && (y + 2 == b)) { // checks to move towards top right
                                          // capture
          if (m_game[x + 1][y + 1] == BDISK) {
            m_game[a][b] = WDISK;
            m_game[x][y] = BCELL;
            m_game[x + 1][y + 1] = BCELL;
            m_blackDisks--;
            var = true;
          }
        } else if (x + 2 == a &&
                   (y - 2 == b)) { // checks to move towards top left capture
          if (m_game[x + 1][y - 1] == BDISK) {
            m_game[a][b] = WDISK;
            m_game[x][y] = BCELL;
            m_game[x + 1][y - 1] = BCELL;
            m_blackDisks--;
            var = true;
          }
        } else if (x + 1 == a &&
                   (y + 1 == b || y - 1 == b)) { // checks if move is possible
          if (m_game[a][b] != BDISK && m_game[a][b] != WDISK) {
            m_game[a][b] = WDISK;
            m_game[x][y] = BCELL;
            var = true;
          }
        }
        if (var == true) { // if move is possible and if the co-ordinate is 0
                           // then promote it to king
          if (a == m_numRows - 1) {
            m_game[a][b] = WKING;
          }
        }
      }
    } else if (m_game[x][y] == WKING) { // WHITE KING
      if ((x - 1 == a || x + 1 == a) &&
          (y + 1 == b || y - 1 == b)) { // checks for valid move
        if (m_game[a][b] != BDISK && m_game[a][b] != WDISK) {
          m_game[a][b] = WKING;
          m_game[x][y] = BCELL;
          var = true;
        }
      } else if (x - 2 == a && y + 2 == b) { // botton right capture
        if (m_game[x - 1][y + 1] == BDISK) {
          m_game[a][b] = WKING;
          m_game[x][y] = BCELL;
          m_game[x - 1][y + 1] = BCELL;
          m_blackDisks--;
          var = true;
        }
      } else if (x - 2 == a && y - 2 == b) { // bottom left capture
        if (m_game[x - 1][y - 1] == BDISK) {
          m_game[a][b] = WKING;
          m_game[x][y] = BCELL;
          m_game[x - 1][y - 1] = BCELL;
          m_blackDisks--;
          var = true;
        }
      } else if (x + 2 == a && y + 2 == b) { // top right capture
        if (m_game[x + 1][y + 1] == BDISK) {
          m_game[a][b] = WKING;
          m_game[x][y] = BCELL;
          m_game[x + 1][y + 1] = BCELL;
          m_blackDisks--;
          var = true;
        }
      } else if (x + 2 == a && y - 2 == b) { // top left capture
        if (m_game[x + 1][y - 1] == BDISK) {
          m_game[a][b] = WKING;
          m_game[x][y] = BCELL;
          m_game[x + 1][y - 1] = BCELL;
          m_blackDisks--;
          var = true;
        }
      }
    }
  }
  if (m_currPlayer == WPLAYER) {
    m_currPlayer = BPLAYER;
  } else {
    m_currPlayer = WPLAYER;
  }
  return var;
}

void Checkers::setGameState(CELL game[], int n, PLAYER player) {
  if (n < 0) {
    n = DEFBOARDSIZE * DEFBOARDSIZE;
  }

  int rows = sqrt(n);
  int col = sqrt(n);

  if (rows * col == n) {
    int index = 0;
    int wd = 0;
    int bd = 0;
    m_currPlayer = player;
    while (index < n) { // loops runs until the size of the game array
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
          if (game[index] != "") {
            m_game[i][j] = game[index]; // populates the m_game array
            index++;
          } else {
            index++;
            continue;
          }
        }
      }
    }
    // searches for current number of disks on the board
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < col; j++) {
        if (m_game[i][j] == WDISK) {
          wd++;
        } else if (m_game[i][j] == BDISK) {
          bd++;
        }
      }
    }
    if (wd < m_whiteDisks) {
      m_whiteDisks = wd; // updates the number white disks
    }
    if (bd < m_blackDisks) {
      m_blackDisks = bd; // updates the number of black disks
    }
  }
}

void Checkers::dumpGame() {
  if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr) {
    cout << "  ";
    for (int k = 0; k < m_numColumns; k++) {
      cout << k << " ";
    }
    cout << endl;
    for (int i = 1; i <= m_numRows; i++) {
      cout << i - 1 << " ";
      for (int j = 1; j <= m_numColumns; j++) {
        cout << m_game[i - 1][j - 1];
      }
      cout << endl;
    }
    cout << endl;
  }
}
