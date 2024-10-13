#include <superkarel.h>

bool count();

int main(){
    set_step_delay(50);
    turn_on("task_6.kw");
    
    while(!beepers_present()) {step();}
    while(count()){
        while(!beepers_present()) {step();}
    }

    turn_off();
    return 0;
}

bool count(){
    pick_beeper();
    if(beepers_present()){
        pick_beeper();
    } else {while(!facing_north()) {turn_left();} return 1;}

    if(beepers_present()){
        pick_beeper();    
    } else {while(!facing_west()) {turn_left();} return 1;}
        
    if(beepers_present()){
        pick_beeper();
    } else {while(!facing_south()) {turn_left();} return 1;}
        
    if(beepers_present()){
        pick_beeper();
        return 0;
    } else {while(!facing_east()) {turn_left();} return 1;} 
}
