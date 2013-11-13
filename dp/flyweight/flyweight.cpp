#include "stdio.h"
#include <vector>

class Chess
{
public:
    Chess(int color):color_(color) {
        x_ = 0;
        y_ = 0;
    }

    void SetPos(int x, int y) {
        x_ = x;
        y_ = y;
    }

    int Color() const {
        return color_;
    }

    void Show() {
        printf("pos:(%d, %d) color: %d\n", x_, y_, color_);
    }
private:
    int color_;

    int x_;
    int y_;
};

class ChessBoard
{
public:
    Chess* Create(int color) {
        auto iter = chesss_.begin();
        while (iter < chesss_.end()) {
            if((*iter)->Color() == color) {
                return *iter;
            }
            iter++;
        }
        Chess* chess = new Chess(color);
        chesss_.push_back(chess);
        return chess;
    }

private:
    std::vector<Chess*> chesss_;
};

int main() {
    ChessBoard chess_board;
    Chess* chessA = chess_board.Create(0);
    chessA->Show();
    Chess* chessB =chess_board.Create(1);
    chessB->Show();

    chessA->SetPos(1,1);
    chessA->Show();
    chessA = chess_board.Create(0);
    chessA->Show();

    return 0;
}
