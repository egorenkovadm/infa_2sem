#include <iostream>
#include <random>


const int n = 9;
int array[n][n]{0};

// random library
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> dist(0, 3);
std::uniform_int_distribution<int> dist_n(0, n-1);


int print(int arr[n][n]){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cout << array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int check(int x, int y, int c){
    if ((x == 0) or (y == 0) or (x == n - 1) or (y == n - 1)){
        return 2;
    } else{
        if ((array[x][y+1] == c) or (array[x+1][y] == c) or (array[x-1][y] == c) or (array[x][y-1] == c)){
            return 0;
        } else {
            return 1;
        }
    }
}

void spawn(int dis_val){
    int x, y;
    int val = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = 0;
        }
    }
    do{
        x = dist_n(rng);
        y = dist_n(rng);
        if (array[x][y] != 1){
            array[x][y] = 1;
            val++;
        }

    }while(val < dis_val);

}

int change_value(int (&arr)[n][n], int a, int b) {
    int val = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == a) {
                arr[i][j] = b;
                val++;
            }
        }
    }
    return val;
}



void check_after_move(int &dis_val, int c){
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (array[x][y] == c){
                if (array[x][y+1] == c) {
                    array[x][y + 1] = 2;
                    array[x][y] = 2;
                    dis_val = dis_val - 2;
                }
                if (array[x][y-1] == c) {
                    array[x][y-1] = 2;
                    array[x][y] = 2;
                    dis_val = dis_val - 2;
                }
                if (array[x+1][y] == c) {
                    array[x+1][y] = 2;
                    array[x][y] = 2;
                    dis_val = dis_val - 2;
                }
                if (array[x-1][y] == c) {
                    array[x-1][y] = 2;
                    array[x][y] = 2;
                    dis_val = dis_val - 2;
                }
            }
            if ((array[x][y] == 3) and (check(x, y, 2) == 0)){
                array[x][y] = 2;
                dis_val--;
            }
        }
    }
}

void check_before(int &val){
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (array[x][y] == 1){
                if ((check(x, y,1) == 0) or (check(x, y,2) == 0)){
                    if (array[x+1][y] == 1){
                        array[x+1][y] = 2;
                        val--;}
                    if (array[x-1][y] == 1){
                        array[x-1][y] = 2;
                        val--;}
                    if (array[x][y+1] == 1){
                        array[x][y+1] = 2;
                        val--;}
                    if (array[x][y-1] == 1){
                        array[x][y-1] = 2;
                        val--;}
                    array[x][y] = 2;
                    val--;
                    //std::cout << x << y << std::endl;
                }
                if (check(x, y, 1) == 2){
                    array[x][y] = 2;
                    val--;
                }
            }

        }
    }
}

void move(int &dis_val, int x, int y){
    int dir = dist(rng);
    int x_new = x;
    int y_new = y;
    if (dir == 0) {
        x_new = x + 1;}
    if (dir == 1){
        x_new = x - 1;}
    if (dir == 2){
        y_new = y + 1;}
    if (dir == 3){
        y_new = y - 1;}
    if ((x_new == n-1) or (y_new == n-1) or (x_new == 0) or (y_new == 0) or
        (check(x_new, y_new, 2) == 0)){
        array[x_new][y_new] = 2;
        dis_val--;
        array[x][y] = 0;
    } else { if (array[x_new][y_new] == 0){
            array[x_new][y_new] = 3;
            array[x][y] = 0;
        } else { if (array[x_new][y_new] == 3){
                array[x_new][y_new] = 2;
                array[x][y] = 2;
                dis_val = dis_val - 2;
            }

        }


    }

    //std::cout << x << y << ' '  << x_new << y_new <<  std::endl;
}





int main() {
    int dis_val, average;
    int rounds = 1000;

    for (int square = 1; square < 2; square = square + 1){
        //std::cout << square << "= ";
        average = 0;
        for (int count = 0; count < rounds; count++){
            dis_val = square;
            spawn(dis_val);
            int steps = 0;
            //print(array);
            check_before(dis_val);
            //print(array);
            //std::cout << dis_val << std::endl;

            while (dis_val > 0){
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++) {
                        if (array[i][j] == 1){
                            move(dis_val, i, j);
                        }
                    }
                }
                check_after_move(dis_val, 3);
                dis_val = change_value(array, 3, 1);
                //if (steps < 10){
                //print(array);
                //std::cout << dis_val << std::endl;
                //}
                //std::cout << dis_val << std::endl;
                steps++;
            }
            average = average + steps;
            //std::cout << steps << ' ';

        }
        std::cout << average << std::endl;

    }
    return 0;
}
