#include <superkarel.h>

void turn_back();
bool check();
void column();


int main(){
    set_step_delay(50);
    turn_on("task_4.kw");

    while(front_is_clear()){
        column();
    }
    column();

    turn_off();
    return 0;
}

void turn_back(){
    turn_left();
    turn_left();
}

bool check(){
    turn_left();
    while(front_is_clear()){
        step();
        if(beepers_present()) {
            while(front_is_clear()) {step();}
            return 1;
        }
    }
    return 0;
}

void column(){
    if(check()){
        turn_back();
        while(front_is_clear()){
            if(!beepers_present()) {put_beeper();}
            step();
        }
        if(!beepers_present()) {put_beeper();}
    }else{
        turn_back();
        while(front_is_clear()) {step();}
    }
    turn_left();
    if(front_is_clear()) {step();}
}
