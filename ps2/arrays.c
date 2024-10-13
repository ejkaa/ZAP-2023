#include <stdio.h>
#include <math.h>

//1 ok
float lift_a_car (const int stick_length, const int human_weight, const int car_weight){
    float weight = human_weight + car_weight;
    return round((stick_length * human_weight / weight) *100) / 100;
}

//2 ok
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    return round(10000 * pack_price / rolls_count / pieces_count)/100;
}

//3 ok 
int bank_notes(const int price){
    if(price<10) {return -1;}

    int amount[5]={10,20,50,100,200};
    int remaining = price;
    int count = 0;
    
    for(int i=4; i>=0; i--){
        while(remaining >= amount[i]){
            remaining-=amount[i];
            count++;
        }
    }
    return count;
}

//4 ok 
int euler(const int n){
    int count = n-1;
    for(int cislo=2; cislo<n; cislo++){
        for(int delitel=2; delitel<=cislo; delitel++){
            if(n%delitel == 0 && cislo%delitel == 0){
                count--;
                break;
            }
        }
    }
    return count;
}

//5 ok
int find_missing_number(const int n, const int arr[]){
    int num = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] < num) {num = arr[i];}
    }

    int change = 1;

    while(change){
        change = 0;
        for(int i=0; i<n; i++){
            if(arr[i] == num+1) {change = 1; break;}
        }
        num++;
    }
    return num;
}

//6 ok
unsigned long sum_squared(const int line){
    if(line == 0) {return 1;}

    unsigned long sum = 1;
    unsigned long koeficient = 1;

    for(int i=1; i<=line; i++){
        koeficient = koeficient * (line-i+1) / i;
        sum+= koeficient * koeficient;
    }
    return sum;
}

//7 ok
int array_min(const int input_array[], const int array_size){
    if(input_array == NULL) {return -1;}
    int min = input_array[0];
    for(int i=1; i<array_size; i++){
        if(input_array[i] < min) {min = input_array[i];}
    }
    return min;
}

int array_max(const int input_array[], const int array_size){
    if(input_array == NULL) {return -1;}
    int max = input_array[0];
    for(int i=1; i<array_size; i++){
        if(input_array[i] > max) {max = input_array[i];}
    }
    return max;
}
//8 neok 
int factorize_count(const int n){
    int cislo = n;
    int count = 0;
    for(int i=2; i<=n; i++){
        if(cislo%i == 0){
            printf("%d %d\n", cislo, i);
            count++;
            while(cislo%i == 0) {cislo /= i;}
        }
        if(cislo == 1) {return count;}
    }
    printf("\n");
    return count;
}

//9 ok
void podium(const int n, int arr[]){
    int num = n;
    int zvysok = 0;
    while(num%3 != 0){
        num--;
        zvysok++;
    }

    if(zvysok == 2) {arr[0] = num/3 +1;}    else {arr[0] = num/3;}
    if(zvysok > 0) {arr[1] = num/3 +2;}     else {arr[1] = num/3 +1;}
    arr[2] = num/3 -1;
}

int main(){
    //int num;
    //scanf("%d\n", &num);
    printf("%d\n", factorize_count(84));
    return 0;
}
