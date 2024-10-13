#include <superkarel.h>
#define SPEED 100

void turn_right();
void turn_back();
void jump_over();
void jump_over_left();

int main(){
    set_step_delay(SPEED);
    turn_on("task_1.kw");
    
    put_beeper();
    if(front_is_clear()) {step();}
    jump_over();

    pick_beeper();
    turn_back();
    while(!beepers_present() && front_is_clear()) {step();}

    jump_over_left();
    pick_beeper();

    turn_off();
    return 0;
}

void jump_over(){
    do{
        while(front_is_clear() && !beepers_present()) {step();}
        turn_left();
        while(right_is_blocked()) {step();}
        turn_right();
        do{step();} while(right_is_blocked());
        turn_right();
        while(front_is_clear()) {step();}
        turn_left();
        while(!beepers_present() && front_is_clear()) {step();}
    }while(!beepers_present());
}

void jump_over_left(){
    while(!beepers_present()){
        while(!beepers_present() && front_is_clear()) {step();}
        turn_right();
        while(left_is_blocked()) {step();}
        turn_left();
        do{step();} while(left_is_blocked());
        turn_left();
        while(front_is_clear()) {step();}
        turn_right();
        while(!beepers_present() && front_is_clear()) {step();}
    }
}

void turn_back(){
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED); 
}

void turn_right(){
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}
