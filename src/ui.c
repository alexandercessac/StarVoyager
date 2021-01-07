#include<ncurses.h>

#include "ui.h"
#include "game.h"

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

void DoSplashIntro(int YMAX, int XMAX, int YMID, int XMID) {
 //get screen size
 getmaxyx(stdscr, YMAX, XMAX);
 //find screen center
 YMID=YMAX/2;XMID=XMAX/2;

 //create background
 for(int y=YMID/2;y<YMAX-(YMID/2);y++){
 for(int x=XMID/2;x<XMAX-(XMID/2);x++){
   mvaddch(y,x, get_bg());
 }}
 //print 'star voyager'
 mvaddch(YMID-2,XMID-2,'s');
 mvaddch(YMID-2,XMID-1,'t');
 mvaddch(YMID-2,XMID  ,'a');
 mvaddch(YMID-2,XMID+1,'r');
 mvaddch(YMID-1,XMID-3,'v');
 mvaddch(YMID-1,XMID-2,'o');
 mvaddch(YMID-1,XMID-1,'y');
 mvaddch(YMID-1,XMID  ,'a');
 mvaddch(YMID-1,XMID+1,'g');
 mvaddch(YMID-1,XMID+2,'e');
 mvaddch(YMID-1,XMID+3,'r');
 refresh();
 //set game speed
 timeout(550);
 //move ship image across the screen
 for(int i=0;i<8;i++) {
  mvaddch(YMID,XMID-3+i, '>');
  refresh();
  getch();
  mvaddch(YMID,XMID-3+i, '-');
 }
 clear();
 refresh();
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

void WritePlanetDetails(struct Planet p, int y, int x){
 move(y, x);
 printw(p.Name);
 move(y+1, x);
 printw(" - %-*s%'d", 15, "Population: ", p.Population);
 move(y+2, x);
 printw(" - %-*s%s", 15, "Motive: ", Motive_Names[p.Motive]);
 move(y+3, x);
 printw(" - %-*s%s", 15, "Inhabitants: ", PlanetTypeNames[p.Type]);
}
