#include <superkarel.h>
#define SPEED 100

void turn_right();

int main(){
    set_step_delay(SPEED);
    turn_on("task_2.kw");

    while(!beepers_present()){ 
        while(front_is_clear() && !beepers_present()) {step();}
        turn_left();
    }

    pick_beeper();
    turn_left();
    
    while(front_is_clear()){
        while(front_is_clear()) {step();}
        turn_right();
    }

    turn_off();
    return 0;
}

void turn_right(){
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}
