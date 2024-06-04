//fun project challenge developed by me
//A minimnal cmatrix style program named flashmatrix
//Distributed under GPLv3
#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

using namespace std;

unsigned int ms = 40000; //animation speed, higher value for slower motion
int chars = 90; //total number of characters, excluding Japanese characters

const char* inject[90] = {
    "q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k",
    "l","z","x","c","v","b","n","m","1","2","3","4","5","6","7","8","9","0",
    "?","@","#","*","[","]","<",">","/","!","$","%","^","&","(",")","_","+",
    "=","-","`","~","|","Q","W","E","R","T","Y","U","I","O","P","A","S","D",
    "F","G","H","J","K","L","Z","X","C","V","B","N","M"
};

struct Column {
    int position;
    int length;
    int speed;
    int head;
    int tail;
    bool active;
    const char* characters[20];
};

int main() {
    srand(time(NULL));
    initscr();
    start_color();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    int mx, my;
    getmaxyx(stdscr, my, mx);

    //initialize color pairs
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    //create an array of columns
    Column columns[mx];
    for (int i = 0; i < mx; ++i) {
        columns[i].position = 0;
        columns[i].length = 5 + rand() % 15;
        columns[i].speed = 1 + rand() % 3;
        columns[i].head = rand() % my;
        columns[i].tail = (columns[i].head - columns[i].length + my) % my;
        columns[i].active = rand() % 2; // Randomly activate columns

        //init char on column
        for (int j = 0; j < 20; ++j) {
            columns[i].characters[j] = inject[rand() % chars];
        }
    }

    while (1) {
        clear();

        for (int i = 0; i < mx; ++i) {
            if (!columns[i].active && rand() % 100 < 2) {
                columns[i].active = true;
                columns[i].length = 5 + rand() % 15;
                columns[i].speed = 1 + rand() % 3;
                columns[i].head = 0;
                columns[i].tail = (columns[i].head - columns[i].length + my) % my;

                //assign new characters when column becomes active
                for (int j = 0; j < 20; ++j) {
                    columns[i].characters[j] = inject[rand() % chars];
                }
            }

            if (columns[i].active) {
                for (int j = 0; j < columns[i].length; ++j) {
                    int y = (columns[i].head - j + my) % my;
                    const char* ch = columns[i].characters[j % 20]; 
                    if (j == 0) {
                        attron(COLOR_PAIR(2)); //head of the stream in white
                        mvaddstr(y, i, ch);
                        attroff(COLOR_PAIR(2));
                    } else {
                        attron(COLOR_PAIR(1)); //body of the stream in green
                        mvaddstr(y, i, ch);
                        attroff(COLOR_PAIR(1));
                    }
                }

                //update head and tail positions
                if (rand() % 10 < columns[i].speed) {
                    columns[i].head = (columns[i].head + 1) % my;
                    columns[i].tail = (columns[i].tail + 1) % my;
                }

                //deactivate column randomly
                if (columns[i].head == columns[i].tail && rand() % 10 < 1) {
                    columns[i].active = false;
                }
            }
        }

        refresh();
        usleep(ms);

        //exit on 'q' key press
        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }
    }

    endwin();
    return 0;
}
