#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>
#include <climits>

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};
enum SEQUENCE {
    
    ALIVE_1 = 50,
    DEAD_1 = 10,
    ALIVE_2 = 500,
    DEAD_2 = 100,
    ALIVE_3 = 10000,
    DEAD_3 = 4000,
    ALIVE_4 = 75000,
    DEAD_4 = 30000,
    WIN_5 = 2000000,
    DOUBLE_DEAD = 0,
};
int player;
int opponent;
const int SIZE = 15;
bool first = true;
std::array<std::array<int, SIZE>, SIZE> board;
bool check_neighbor(int x, int y){
    for(int i = -1; i <= 1; i ++){
        for(int j = -1; j <= 1; j ++){
            if(i == 0 && j == 0)
                continue;
            if(x + i < 0 || x + i >= SIZE || y + j < 0 || y + j >= SIZE)
                continue;
            if(board[x + i][y + j]!= EMPTY)
                return true;
        }
    }
    return false;
}
int score_table(int num, int empty){
    if(num >= 5)
        return WIN_5;
    if(empty == 0)
        return DOUBLE_DEAD;

    if(num == 4){
        if(empty == 2)
            return ALIVE_4;
        else
            return DEAD_4;
    }
    if(num == 3){
        if(empty == 2)
            return ALIVE_3;
        else
            return DEAD_3;
    }
    if(num == 2){
        if(empty == 2)
            return ALIVE_2;
        else
            return DEAD_2;
    }
    if(num == 1){
        if(empty == 2)
            return ALIVE_1;
        else
            return DEAD_1;
    }

}
int value(int chess){
    int op;
    if(chess == BLACK)
        op = WHITE;
    else
        op = BLACK;
    int val = 0;
    int serial_cnt = 0;
    int tmp = 0;
    int empty = 0;//0, 1, 2
    int i, j, k;
    //橫排
    for(i = 0; i < 15; i ++){
        empty = 0;
        serial_cnt = 0;
        for(j = 0; j < 15; j ++){
                if(board[i][j] == chess){
                   serial_cnt ++;
                }
                else if(board[i][j] == EMPTY){
                    if(serial_cnt == 0){
                        empty = 1;
                    }
                    else{
                        val +=score_table(serial_cnt, empty + 1);
                        empty = 1;
                        serial_cnt = 0;
                    }
                }
                else if(board[i][j] == op){
                    val += score_table(serial_cnt, empty);
                    empty = 0;
                    serial_cnt = 0;
                }
        }
        val += score_table(serial_cnt, empty);
    }
    //直排
    for(j = 0; j < 15; j ++){
        empty = 0;
        serial_cnt = 0;
        for(i = 0; i < 15; i ++){
            if(board[i][j] == chess){
                serial_cnt ++;
            }
            else if(board[i][j] == EMPTY){
                if(serial_cnt == 0){
                    empty = 1;
                }
                else{
                    val +=score_table(serial_cnt, empty + 1);
                    empty = 1;
                    serial_cnt = 0;
                }
            }
            else if(board[i][j] == op){
                val += score_table(serial_cnt, empty);
                empty = 0;
                serial_cnt = 0;
            }
        }
    val += score_table(serial_cnt, empty);
    }   
    //上半正斜含中間  (/)
    for(i = 0; i < SIZE; i ++){
        empty = 0;
        serial_cnt = 0;
        for(j = 0; j <= i; j ++){
            if(board[j][i - j] == chess){
                serial_cnt ++;
            }
            else if(board[j][i - j] == EMPTY){
                if(serial_cnt == 0){
                    empty = 1;
                }
                else{
                    val +=score_table(serial_cnt, empty + 1);
                    empty = 1;
                    serial_cnt = 0;
                }
            }
            else if(board[j][i - j] == op){
                val += score_table(serial_cnt, empty);
                empty = 0;
                serial_cnt = 0;
            }
        }
        val += score_table(serial_cnt, empty);
    }
    //下半正斜  (/)
     for(i = (SIZE - 1)*2; i >= SIZE; i --){
        empty = 0;
        serial_cnt = 0;
        for(j = SIZE - 1; j >= i - (SIZE - 1); j --){
            if(board[j][i - j] == chess){
                serial_cnt ++;
            }
            else if(board[j][i - j] == EMPTY){
                if(serial_cnt == 0){
                    empty = 1;
                }
                else{
                    val +=score_table(serial_cnt, empty + 1);
                    empty = 1;
                    serial_cnt = 0;
                }
            }
            else if(board[j][i - j] == op){
                val += score_table(serial_cnt, empty);
                empty = 0;
                serial_cnt = 0;
            }
        }
        val += score_table(serial_cnt, empty);
    }
    //上半反斜  (\)
    for(i = -1; i >= -(SIZE - 1); i --){
        empty = 0;
        serial_cnt = 0;
        for(j = 0; j < i + SIZE; j ++){
            if(board[j][j - i] == chess){
                serial_cnt ++;
            }
            else if(board[j][j - i] == EMPTY){
                if(serial_cnt == 0){
                    empty = 1;
                }
                else{
                    val +=score_table(serial_cnt, empty + 1);
                    empty = 1;
                    serial_cnt = 0;
                }
            }
            else if(board[j][j - i] == op){
                val += score_table(serial_cnt, empty);
                empty = 0;
                serial_cnt = 0;
            }
        }
        val += score_table(serial_cnt, empty);
    }
    //下半反斜含中間  (\)
    for(i = 0; i < SIZE; i ++){
        empty = 0;
        serial_cnt = 0;
        for(j = 0; j < SIZE - i; j ++){
            if(board[i + j][j] == chess){
                serial_cnt ++;
            }
            else if(board[i + j][j] == EMPTY){
                if(serial_cnt == 0){
                    empty = 1;
                }
                else{
                    val +=score_table(serial_cnt, empty + 1);
                    empty = 1;
                    serial_cnt = 0;
                }
            }
            else if(board[i + j][j] == op){
                val += score_table(serial_cnt, empty);
                empty = 0;
                serial_cnt = 0;
            }
        }
        val += score_table(serial_cnt, empty);
    }
    return val;
}

int MinMax(int depth, int maxminplayer, std::ostream &fout){
    if(depth == 0){
        return value(player) - 1.1*value(opponent);
    }
    if(first == true && player == BLACK){
        fout << 7 << " " << 7 << std::endl;
        fout.flush();
        first = false;
        return 0;
    }
    if(maxminplayer == player){
        int val = INT_MIN;
        int tmp;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                if(board[i][j] == EMPTY){
                    if(check_neighbor(i, j) == false)
                        continue;
                    board[i][j] = maxminplayer;
                    tmp = MinMax(depth - 1, opponent, fout);
                    if(tmp > val){
                        val = tmp;
                        if(depth == 3){
                             fout << i << " " << j << std::endl;
                            fout.flush();
                        }
                    }
                    board[i][j] = EMPTY;
                }
            }
        }
        return val;   
    }
    else{
        int val = INT_MAX;
        int tmp;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if(board[i][j] == EMPTY ){
                    if(check_neighbor(i, j) == false)
                        continue;
                    board[i][j] = maxminplayer;
                    tmp = MinMax(depth - 1, player, fout);
                    val = std::min(val, tmp);
                    board[i][j] = EMPTY;
                }
            }
        }
        return val;
    }
}
int alpha_beta(int depth, int maxminplayer,int alpha, int beta,std::ostream &fout){
    if(depth == 0){
        return value(player) - 1.1*value(opponent);
    }
    if(first == true && player == BLACK){
        fout << 7 << " " << 7 << std::endl;
        fout.flush();
        first = false;
        return 0;
    }
    if(maxminplayer == player){
        int val = INT_MIN;
        int tmp;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                if(board[i][j] == EMPTY){
                    if(check_neighbor(i, j) == false)
                        continue;
                    board[i][j] = maxminplayer;
                    tmp = alpha_beta(depth - 1, opponent,alpha, beta, fout);
                    board[i][j] = EMPTY;
                    if(tmp > val){
                        val = tmp;
                        if(depth == 3){
                             fout << i << " " << j << std::endl;
                            fout.flush();
                        }
                    }
                    alpha = std::max(alpha, val);
                    if(alpha >= beta){
                        return val;
                    }
                }
            }
        }
        return val;   
    }
    else{
        int val = INT_MAX;
        int tmp;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if(board[i][j] == EMPTY ){
                    if(check_neighbor(i, j) == false)
                        continue;
                    board[i][j] = maxminplayer;
                    tmp = alpha_beta(depth - 1, player,alpha, beta, fout);
                    board[i][j] = EMPTY;
                    val = std::min(val, tmp);
                    beta = std::min(beta, val);
                    if(alpha >= beta){
                        return val;
                    }
                }
            }
        }
        return val;
    }
}
void read_board(std::ifstream& fin) {
    fin >> player;
    if(player == WHITE)
        opponent = BLACK;
    else
        opponent = WHITE;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
            if(board[i][j] != EMPTY)
                first = false;
        }
    }
}

void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    int x, y;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.
        int x = (rand() % SIZE);
        int y = (rand() % SIZE);
        if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}


int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    //MinMax(3, player, fout);
    alpha_beta(3, player,INT_MIN, INT_MAX, fout);
    //write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
    
}
//./main ./myAI ./baseline1
//./main ./baseline1 ./myAI
//./main ./myAI ./baseline2
//./main ./baseline2 ./myAI 
