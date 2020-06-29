#include<ncurses.h>

#include "ui.h"

#include<stdlib.h>

void init() {
 initscr();            //start ncurses
 cbreak();
 noecho();             //turn off echo
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

 for(int y=0;y<ystop;y++){
 for(int x=0;x<xstop;x++){
   mvaddch(y, x, map[(y+ydiff)%1000][(x+xdiff)%1000]);
 }}
  //write position of diff
  //move(0,0); printw("x:%d y:%d",xdiff,ydiff);
}

void renderDiff(int ymax,int xmax,int ydiff,int xdiff, int map[1000][1000], char direction){
 int xIndex, yIndex,prev;
 switch(direction){
  case '<':
   for(int y=0;y<ymax;y++){
   for(int x=0;x<xmax;x++){
    xIndex=(x+xdiff)%1000;
    yIndex=(y+ydiff)%1000;
    prev=(x+xdiff+1)%1000;
    if(map[yIndex][prev] != map[yIndex][xIndex]){
     mvaddch(y, x, map[yIndex][xIndex]);
     mvaddch(y, x+1, map[yIndex][prev]);
    }
   }}
   break;
  case '>':
    for(int y=0;y<ymax;y++){
    for(int x=0;x<xmax;x++){
     xIndex=(x+xdiff)%1000;
     yIndex=(y+ydiff)%1000;
     prev=(x+xdiff-1)%1000;
     if(map[yIndex][prev] != map[yIndex][xIndex]){
      mvaddch(y, x-1, map[yIndex][prev]);
      mvaddch(y, x, map[yIndex][xIndex]);
     }
    }}
    break;
  case '^':
    for(int y=0;y<ymax;y++){
    for(int x=0;x<xmax;x++){
     xIndex=(x+xdiff)%1000;
     yIndex=(y+ydiff)%1000;
     prev=(y+ydiff+1)%1000;
     if(map[prev][xIndex] != map[yIndex][xIndex]){
      mvaddch(y, x, map[yIndex][xIndex]);
      mvaddch(y+1, x, map[prev][xIndex]);
     }
    }}
    break;
  case 'v':
    for(int y=0;y<ymax;y++){
    for(int x=0;x<xmax;x++){
      xIndex=(x+xdiff)%1000;
      yIndex=(y+ydiff)%1000;
      prev=(y+ydiff-1)%1000;
      if(map[prev][xIndex] != map[yIndex][xIndex]){
       mvaddch(y, x, map[yIndex][xIndex]);
       mvaddch(y-1, x, map[prev][xIndex]);
      }
     }}
    break;
 }
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
