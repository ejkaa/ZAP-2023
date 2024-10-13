#include <superkarel.h>
#define SPEED 100

void turn_back();
void turn_right();
void step_down();
void step_up();
bool beepers_right();
void comeback();
void tidy_up();

int main(){
    set_step_delay(SPEED);
    turn_on("task_3.kw");
    
    tidy_up();

    turn_back();
    comeback();

    turn_off();
    return 0;
}

void tidy_up(){
    while(1){
    while(front_is_clear()){
        if(beepers_present()) {pick_beeper();}
        step();
    }
    if(beepers_present()) {pick_beeper();}
    turn_back();

    while(beepers_in_bag()){
        if(right_is_blocked()) {put_beeper();}
        else if(beepers_right()) {put_beeper();}
        step();
    }
    while(front_is_clear()) {step();}
    if(left_is_clear()) {step_down();}
    else {break;}
}}

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

void step_down(){
    //set_step_delay(0);
    turn_left();
    step();
    turn_left(); 
    //set_step_delay(SPEED);
}

void step_up(){
    //set_step_delay(0);
    turn_right();
    step();
    turn_right(); 
    //set_step_delay(SPEED);
}

bool beepers_right(){
    set_step_delay(0);
    turn_right();
    step();
    if(beepers_present()){
        turn_back();
        step();
        turn_right();
        return 1;
    }else{
        turn_back();
        step();
        turn_right();
        return 0;
    }
    set_step_delay(SPEED);
}

void comeback(){    
    while(front_is_clear() && !beepers_present()){
        step();
    }
    if(beepers_present()){
        while(!facing_north()) {turn_left();}
        while(front_is_clear()) {step();}
        turn_left();
        while(front_is_clear()) {step();}
        turn_back();
    }else{
        if(facing_east()) {step_down();}
        else if(facing_west()) {step_up();}
        comeback();
    } 
}
