#include <superkarel.h>
#define SPEED 100

void turn_right();
void turn_back();
void turn();
void block();
void move();

int main(){
    set_step_delay(SPEED);
    turn_on("task_7.kw");
    
    while(front_is_clear()) {put_beeper(); step();}
    put_beeper();
    turn_back();
    //while(front_is_clear()) {step();}
    //turn_back();

    while(front_is_clear()) {block();}

    turn_back();
    while(front_is_clear()) {pick_beeper(); step();}
    pick_beeper();

    turn_off();
    return 0;
}

void block(){
    while(right_is_blocked() && front_is_clear()) {step();}
    if(front_is_blocked()) {return;}
    turn_right();
    step();
    put_beeper();
    step();
    move();
}

void move(){
    while(!beepers_present()){
        while(!beepers_present() && right_is_blocked() && front_is_clear())
            {step();}
        if(beepers_present()) {break;}
        turn();
        step();
    }
    if(front_is_clear()) {pick_beeper(); step();}
    else{turn_back(); step(); put_beeper(); turn_back(); step();}
    turn_right();
    if(front_is_clear()) {step();}
}

void turn(){
    if(right_is_clear()) {turn_right();}
    else if(left_is_clear()) {turn_left();}
    else if(front_is_blocked()) {turn_back();}
}

void turn_right(){
    set_step_delay(0);
    turn_left();
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}

void turn_back(){
    set_step_delay(0);
    turn_left();
    turn_left();
    set_step_delay(SPEED);
}
