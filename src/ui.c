#include<ncurses.h>

#include "ui.h"
#include "game.h"

#include "mnu.h"

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
 int sy, sx;
 char name[25] = "   Star Voyager--------  ";
 //set game speed
 timeout(450);
 for(int i=0;i<24;i++) {
  //create background
  for(int y=YMID/4;y<YMAX-(YMID/4);y++){
  for(int x=XMID/4;x<XMAX-(XMID/4);x++){
   mvaddch(y,x, get_bg());
  }}
  //print 'star voyager'
  sy=YMID;sx=XMID-2;
  for(int j=0;j<i;j++) {
   if(j==8){sy=YMID+1;sx=XMID-2;}
   if(j==15){sy=YMID+2;sx=XMID-2;}
   mvaddch(sy, sx++, name[j]);
  }
  //move ship image across the screen
  mvaddch(sy,sx, ' ');
  mvaddch(sy,sx+1, '>');
  refresh();
  getch();
 }
 clear();
 refresh();
}

//print section of the map
void render(int ymax,int xmax,int ydiff,int xdiff, int limit, int map[limit][limit]){
 int ystop=ymax;
 int xstop=xmax;

 for(int y=0;y<ystop;y++){
 for(int x=0;x<xstop;x++){
   mvaddch(y, x, map[(y+ydiff)%limit][(x+xdiff)%limit]);
 }}
  //write position of diff
  //move(0,0); printw("x:%d y:%d",xdiff,ydiff);
}

void renderDiff(int ymax,int xmax,int ydiff,int xdiff,int limit, int map[limit][limit], char direction){
 int xIndex, yIndex,prev;
 switch(direction){
  case '<':
   for(int y=0;y<ymax;y++){
   for(int x=0;x<xmax;x++){
    xIndex=(x+xdiff)%limit;
    yIndex=(y+ydiff)%limit;
    prev=(x+xdiff+1)%limit;
    if(map[yIndex][prev] != map[yIndex][xIndex]){
     mvaddch(y, x, map[yIndex][xIndex]);
     mvaddch(y, x+1, map[yIndex][prev]);
    }
   }}
   break;
  case '>':
    for(int y=0;y<ymax;y++){
    for(int x=0;x<xmax;x++){
     xIndex=(x+xdiff)%limit;
     yIndex=(y+ydiff)%limit;
     prev=(x+xdiff-1)%limit;
     if(map[yIndex][prev] != map[yIndex][xIndex]){
      mvaddch(y, x-1, map[yIndex][prev]);
      mvaddch(y, x, map[yIndex][xIndex]);
     }
    }}
    break;
  case '^':
    for(int y=0;y<ymax;y++){
    for(int x=0;x<xmax;x++){
     xIndex=(x+xdiff)%limit;
     yIndex=(y+ydiff)%limit;
     prev=(y+ydiff+1)%limit;
     if(map[prev][xIndex] != map[yIndex][xIndex]){
      mvaddch(y, x, map[yIndex][xIndex]);
      mvaddch(y+1, x, map[prev][xIndex]);
     }
    }}
    break;
  case 'v':
    for(int y=0;y<ymax;y++){
    for(int x=0;x<xmax;x++){
      xIndex=(x+xdiff)%limit;
      yIndex=(y+ydiff)%limit;
      prev=(y+ydiff-1)%limit;
      if(map[prev][xIndex] != map[yIndex][xIndex]){
       mvaddch(y, x, map[yIndex][xIndex]);
       mvaddch(y-1, x, map[prev][xIndex]);
      }
     }}
    break;
 }
}

void WritePlanetDetails(struct Planet *p, int y, int x){
 move(y, x);
 printw(p->Name);
 move(y+1, x);
 printw(" - %-*s%'d", 15, "Population: ", p->Population);
 move(y+2, x);
 printw(" - %-*s%s", 15, "Inhabitants: ", PlanetTypeNames[p->Type]);
 move(y+3, x);
 printw(" - %-*s%s %d/10", 15, "Motive: ", Motive_Names[p->Motive], p->Motivation);

 if(p->Target) {
  move(y+4, x);
  printw(" - %-*s%s", 20, "Target: ", p->Target->Name);
 }
}

void PlanetInteraction(int inv[RESOURCE_TYPE_COUNT], struct Planet *p) {
 //clear main window to show planet detail
 clear();
 //Write details about current plant
 WritePlanetDetails(p, 1, 3);
 //refresh changes to main window
 refresh();

 char* options[] = { "Trade" };
 char* title = " Select an Action ";
 int titleLen = 18;
 //present options for how to interact with planet
 //this happens in a sub window
 int sel = SelectItem(1, options, title, titleLen);

 //clear planet info from main window or leave to be shown with trade menu?
 //clear(); refresh();

 //Trade
 if(sel == 0)
 { Xfer(RESOURCE_TYPE_COUNT, inv, p->Inventory, p->ExchangeRate, p->Currency, Resource_Name); }

}
