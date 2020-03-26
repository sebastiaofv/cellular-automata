#include <iostream>
#include <ncurses.h>

/* My includes */
#include "gameOfLife.h"


void menu(){
        
        bool waitForInput = true;

        clear();
        mvprintw(3, 27, "---------------------------------");
        mvprintw(4, 27, "CELLULAR AUTOMATA EXPERIMENTATION");
        mvprintw(5, 27, "---------------------------------");
        mvprintw(7, 11, "C++ Implementation of Different Cellular Automata States");
        mvprintw(8, 11, "Author: Sebastiao Vicente");
        mvprintw(10, 24, "Press 1 to proceed...");
        mvprintw(11, 22, "Press ESC to quit the program...");
        refresh();

        while(waitForInput){
            switch(getch()){
                case 49:
                    waitForInput = false;
                    load_file();
                    run_simulation();
                    break;
                case 27:
                    waitForInput = false;
                    break;
                default:
                    mvprintw(1, 27, "Enter an option...");
                    refresh();
                    break;
            }
        }

}


int main(){
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    
    menu();
    //load_file();
    //run_simulation();
    return 0;
}
