#include<ncurses.h>

#include "ui.h"

#include<stdlib.h>

void init() {
 initscr();            //start ncurses
 cbreak();
 noecho();             //turn of echo
 keypad(stdscr, TRUE); //handle special keys
 curs_set(0);          // hide cursor
 //timeout(100);
 refresh();
}

//clean up ncurses
void fin() {endwin();}

//randomly return a dot
int get_bg(){
 if(rand() % 64 == 0) {return '.';}
 else {return ' ';}
}

//print section of the map
void render(int ymax,int xmax,int ydiff,int xdiff, int map[1000][1000]){
 int ystop=ymax;
 int xstop=xmax;
 int ystart=0,xstart=0;

 for(int y=0;y<ystop;y++){
 for(int x=0;x<xstop;x++){
   mvaddch(y, x, map[(y+ydiff)%1000][(x+xdiff)%1000]);
 }}
  //write position of diff
  //move(0,0); printw("x:%d y:%d",xdiff,ydiff);
}


Coordinate* mkcoord(int x, int y) {
 Coordinate* c = malloc(sizeof(*c));
  c->x = x;
  c->y = y;
  //cell->next = NULL;
  return c;
}

Grid* mkgrid(Coordinate* min, Coordinate* max){
 Grid* g = malloc(sizeof(*g));
 g->min = min;
 g->max = max;
 return g;
}
