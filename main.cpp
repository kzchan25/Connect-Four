#include <iostream>
#include <cstring>

using namespace std;

class GameBoard {
private:
    int width, height;
    int board[6][7];
    int piecesPlaced = 0;
    int gameOver = false;
    int winner = 0;
    
public:
    GameBoard(int width, int height) {
        this -> width = width;
        this -> height = height;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                board[y][x] = 0;
            }
        }
    }
    
    void addPiece(int playerNumber) {
        bool placed = false;
        while (!placed) {
            int column;
            cout <<"Player " << playerNumber << ", What column do you want to place your piece(1 - 7)?" << endl;
            cin >> column;
            column -= 1;
            for (int i = 0; i < height; i++) {
                if (board[i][column] == 0) {
                    board[i][column] = playerNumber;
                    placed = true;
                    piecesPlaced++;
                    checkForFour(playerNumber, column, i);
                    break;
                }
            }
        }
        cout << displayBoard() << endl;
    }
    
    bool checkForFour(int player, int x, int y) {
        int vertical = 0;
        int horizontal = 0;
        int diagonalRight = 0;
        int diagonalLeft = 0;
        for (int i = -3; i < 4; i++) {
            if (x + i >= 0 && x + i < width) {
                if (board[y][x + i] == player)
                    horizontal++;
                else
                    horizontal = 0;
            }
            if (y + i >= 0 && y + i < height) {
                if (board[y + i][x] == player)
                    vertical++;
                else
                    vertical = 0;
            }
            if ((x + i >= 0 && x + i < width) && (y + i >= 0 && y + i < height)) {
                if (board[y + i][x + i] == player)
                    diagonalRight++;
                else
                    diagonalRight = 0;
            }
            if ((x + i >= 0 && x + i < width) && (y - i >= 0 && y - i < height)) {
                if (board[y - i][x + i] == player)
                    diagonalLeft++;
                else
                    diagonalLeft = 0;
            }
            if (vertical >= 4 || horizontal >= 4 || diagonalLeft >= 4 || diagonalRight >= 4) {
                gameOver = true;
                winner = player;
                return true;
                
            }
        }
        return false;
    }
    
    int getWinner() {
        return winner;
    }
    
    bool gameIsOver() {
        if (piecesPlaced == 42) {
            cout << "Board Filled!" << endl;
            resetBoard();
        }
        return gameOver;
    }
    
    void resetBoard() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                board[y][x] = 0;
            }
        }
        piecesPlaced = 0;
    }
    
    string displayBoard() {
        string ret = "";
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                ret +="|";
                if (board[y][x] != 0) {
                    ret += to_string(board[y][x]);
                }
                else {
                    ret += " ";
                }
            }
            ret += "|\n";
        }
        for (int x = 0; x < 15; x++) {
            ret += "-";
        }
        ret += "\n ";
        for (int x = 0; x < width; x++) {
            ret += to_string(x + 1) + " ";
        }
        ret += "\n";
        return ret;
    }
    
    string toString() {
        string ret = "";
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                ret += " " + to_string(board[y][x]);
            }
            ret += "\n";
        }
        return ret;
    }
};



int main() {
    GameBoard board = *new GameBoard(7,6);
    cout << board.displayBoard() << endl;
    while (!board.gameIsOver()) {
        board.addPiece(1);
        if (!board.gameIsOver()) {
            board.addPiece(2);
        }
    }
    cout << "The Winner is Player " << board.getWinner() << "!" << endl;
    return 0;
}
