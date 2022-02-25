#include <iostream>
#include <random>


const int n = 3;
int array[n]{0};

// random library
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<int> dist(0, 1);
std::uniform_int_distribution<int> dist_n(0, n-1);


int print(int arr[n]){
    for (int i = 0; i < n; i++){
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}


void spawn(int dis_val){
    int x;
    int val = 0;
    for (int i = 0; i < n; i++) {
        array[i] = 0;
    }

    do{
        x = dist_n(rng);
        if (array[x]!= 1){
            array[x] = 1;
            val++;
        }
        //print(array);
    }while(val < dis_val);

}

int change_value(int (&arr)[n], int a, int b) {
    int val = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == a) {
            arr[i] = b;
            val++;
        }
    }
    return val;
}

void check_before(int &val){
    for (int x = 0; x < n; x++) {
            if (array[x] == 1){
                    if (array[x+1] == 1){
                        array[x+1] = 2;
                        array[x] = 2;
                        val = val - 2;}
                    if (array[x-1] == 1){
                        array[x-1] = 2;
                        array[x] = 2;
                        val = val - 2;}
                    if ((array[x+1] == 2) or (array[x-1] == 2)){
                        array[x] = 2;
                        val--;}
            }
    }
}


void move(int &dis_val, int x){
    int dir = dist(rng);
    int x_new = x;
    if (dir == 0) {
        x_new = x + 1;}
    if (dir == 1){
        x_new = x - 1;}
    if ((x_new == n-1) or (x_new == 0) or (array[x_new + 1] == 2) or (array[x_new - 1] == 2) or (array[x_new + 1] == 3)
    or (array[x_new - 1] == 3)){
        array[x_new]= 2;
        dis_val--;
        array[x] = 0;
    } else { if (array[x_new] == 0){
            array[x_new]= 3;
            array[x]= 0;
        } else { if (array[x_new]== 3){
                array[x_new]= 2;
                array[x] = 2;
                dis_val = dis_val - 2;
            }

        }


    }

    //std::cout << x << ' '  << x_new <<  std::endl;
}





int main() {
    int dis_val, average;
    int rounds = 1000;

    for (int square = 1; square < 2; square++){
        //std::cout << square << "= ";
        average = 0;
        //std::cout << square << std::endl;
        for (int count = 0; count < rounds; count++){
            dis_val = square;
            spawn(dis_val);
            int steps = 0;
            print(array);
            check_before(dis_val);
            //std::cout << dis_val << std::endl;

            do{
                for (int i = 0; i < n; i++){
                    if (array[i] == 1){
                        move(dis_val, i);
                    }
                }
                dis_val = change_value(array, 3, 1);
                //if (steps < 10){
                //print(array);
                //std::cout << dis_val << std::endl;
                //}
                //std::cout << dis_val << std::endl;
                steps++;
            }
            while (dis_val > 0);
            average = average + steps;
            //std::cout << steps << ' ';

        }
        std::cout << average << std::endl;

    }
    return 0;
}
