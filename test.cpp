#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>

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
    std::cout << "+horizontal: " <<val << std::endl;
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
    std::cout << "+vertical: " <<val << std::endl;
    /*
    //  (/)
    for(int i = 0; i < SIZE*2 - 1; i ++){
        empty = 0;
        serial_cnt = 0;
        for(int j = 0; j < i; j ++){
            if(j < 0 || j  >= SIZE || (i-j) < 0 || (i - j)  >=SIZE)
                continue;
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
    //(\)
    for(int i = -(SIZE - 1); i < SIZE; i ++){
        empty = 0;
        serial_cnt = 0;
        for(int j = i;j < SIZE; j ++){
            if(j < 0 || j  >= SIZE || (i-j) < 0 || (i - j)  >=SIZE)
                continue;
            if(board[j - i][j] == chess){
                serial_cnt ++;
            }
            else if(board[j - i][j] == EMPTY){
                if(serial_cnt == 0){
                    empty = 1;
                }
                else{
                    val +=score_table(serial_cnt, empty + 1);
                    empty = 1;
                    serial_cnt = 0;
                }
            }
            else if(board[j - i][j] == op){
                val += score_table(serial_cnt, empty);
                empty = 0;
                serial_cnt = 0;
            }
        }
        val += score_table(serial_cnt, empty);
    }
    */
    
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
    std::cout << "+top positive slash: " << val << std::endl;
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
    std::cout << "+down positive slash: " << val << std::endl;
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
    std::cout << "+top negative slash: " << val << std::endl;
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
    std::cout << "+down negative slash: " << val << std::endl;
    return val;
}

int main(){
    for(int i = 0; i < SIZE; i ++){
        for (int j = 0; j < SIZE; j++)
        {
            std::cin >> board[i][j];
        }
        
    }
   
    std::cout << value(1);
        
        
    
}