#include <superkarel.h>
#define SPEED 100

void turn_back();
void frame();
void find_corner();
void center();

int main(){
    set_step_delay(SPEED);
    turn_on("task_5.kw");
    
    frame();
    step();
    turn_left();
    step();
    center();
    turn_left();
    center();
    while(!facing_north()) {turn_left();}

    turn_off();
    return 0;
}

void center(){
    while(!beepers_present()){
        put_beeper();
        do{step();} while(!beepers_present());
        turn_back();
        step(); 
    }
    put_beeper();
    while(front_is_clear()) {step();}
    turn_back();
    step();
    while(front_is_clear()) {pick_beeper(); step();}
    turn_back();
    do{step();} while(!beepers_present());
    pick_beeper();
}

void frame(){
    find_corner();
    while(!beepers_present()){
        while(front_is_clear()){
            put_beeper();
            step();
        }
        turn_left();
    }
}

void find_corner(){
    while(!facing_south()) {turn_left();}
    while(front_is_clear()) {step();}
    while(!facing_west()) {turn_left();}
    while(front_is_clear()) {step();}
    turn_left();
}

void turn_back(){
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}
