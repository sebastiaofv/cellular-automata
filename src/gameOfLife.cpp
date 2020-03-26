#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>

/* My includes */
#include "gameOfLife.h"

const int BOARD_Y = 21;
const int BOARD_X = 80;

const char ALIVE = 'X';
const char DEAD  = '.'; 

char board[BOARD_Y][BOARD_X];

std::string FILES[] = {"../states/explosion.txt", "../states/spaceship.txt"};


void load_file(){
    std::ifstream file;
    clear();
    bool waitForInput = true;
    int choice;

    while(waitForInput){
        mvprintw(5, 19, "Type the number of the initial state file");
        mvprintw(8, 28, "1: Explosion");
        mvprintw(9, 28, "2: Spaceship");
        refresh();
        switch(getch()){
            case 49:
                choice = 0; 
                waitForInput = false;
                break;
            case 50:
                choice = 1;
                waitForInput = false;
                break;
            default:
                mvprintw(12, 28, "You didn't type an option");
                refresh();
                break;
        }
    }

    file.open(FILES[choice].c_str());
    
    if(!file){
        std::cout << "lel" << std::endl;
    } else {
        for(int y = 0; y < BOARD_Y; y++ ){
            for(int x = 0; x < BOARD_X; x++){
                file >> board[y][x];
            }
        }
    }

    /* Close file stream */
    file.close();

}

void run_simulation(){
    
    int round_n = 0;

    clear();
    mvprintw(0, 0, "Press any key to start the simulation... or ESC to quit...");
    refresh();
    
    while(getch() != 27){
        clear();
        
        for(int y = 0; y < BOARD_Y; y++){
            for(int x = 0; x < BOARD_X; x++){
                mvaddch(y, x, board[y][x]);
            }
        }
        
        round_n++;
        mvprintw(BOARD_Y, 0, "Press any key to progress the rounds. ESC to quit.                 Round: %d", round_n);
        update();
        refresh();
    }
    
    clear();
    return;

}


void update(){
    /* Create a temporary board */
    
    char temp[BOARD_Y][BOARD_X];

    for(int y = 0; y < BOARD_Y; y++){
        for(int x = 0; x < BOARD_X; x++){
             temp[y][x] = DEAD;
         }
     }

    /*            Algorithm for life
     * 1. If cell has < 2 living neighbours --> DIE
     * 2. If cell has > 2 living neighbours --> LIVE
     * 3. If cell has > 3 living neighbours  --> DIE
     * 4. If cell is dead and > 3 living neibours --> COME ALIVE
     */

    for(int y = 0; y < BOARD_Y; y++){
        for(int x = 0; x < BOARD_X; x++){
            int neighbours_alive = 0;
            
            /* Top Left */
            if(board[y - 1][x - 1] == ALIVE){
                neighbours_alive++;
            }
            /* Top */
            if(board[y - 1][x] == ALIVE){
                neighbours_alive++;
            }
            /* Top Right */
            if(board[y - 1][x + 1] == ALIVE){
                neighbours_alive++;
            }
            /* Left */
            if(board[y][x - 1] == ALIVE){
                neighbours_alive++;
            }
            /* Right */
            if(board[y][x + 1] == ALIVE){
                neighbours_alive++;
            }
            /* Bottom Left */
            if(board[y + 1][x - 1] == ALIVE){
                neighbours_alive++;
            }
            /* Bottom */
            if(board[y + 1][x] == ALIVE){
                neighbours_alive++;
            }
            /* Bottom Right */
            if(board[y + 1][x + 1] == ALIVE){
                neighbours_alive++;
            }

            /* Rule 1 */
            if(board[y][x] == ALIVE && neighbours_alive < 2){
                temp[y][x] = DEAD;
            }
            /* Rule 2 */
            if(board[y][x] == ALIVE && (neighbours_alive == 2 || neighbours_alive == 3)){
                temp[y][x] = ALIVE;
            }
            /* Rule 3 */
            if(board[y][x] == ALIVE && neighbours_alive > 3){
                temp[y][x] = DEAD;
            }
            /* Rule 4 */
            if(board[y][x] == DEAD && neighbours_alive == 3){
                temp[y][x] = ALIVE;
            }

        }
    }

    /* Update main board */

    for(int y = 0; y < BOARD_Y; y++){
        for(int x = 0; x < BOARD_X; x++){
             board[y][x] = temp[y][x];
         }
     }


}

