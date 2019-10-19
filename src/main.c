#include<ncurses.h>

#include "ui.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
 //ui
 init();

 int YMAX, XMAX, XMID, YMID, YDIFF, XDIFF, XSHIP, YSHIP;
 //set screen size
 getmaxyx(stdscr, YMAX, XMAX);
 //find screen center
 YMID=YMAX/2;XMID=XMAX/2;
 //set ship
 XSHIP=XMID;YSHIP=YMID;
 //set screen position
 YDIFF=XDIFF=0;
 //set map
 int LIMIT = 1000;
 int map[LIMIT][LIMIT];
 for(int y=0;y<LIMIT;y++){
 for(int x=0;x<LIMIT;x++){
  map[y][x]=get_bg();//get '.' or ' ' randomly
 }}



 //todo planets
 map[5][5]='0';

 //todo delay with tics
 timeout(150);

//main
 int direction = '>';
 int input;
 while((input = getch()) != 'q') {
  switch(input){
   case KEY_RIGHT:direction='>'; break;
   case KEY_LEFT: direction='<'; break;
   case KEY_DOWN: direction='v'; break;
   case KEY_UP:   direction='^'; break;
   case 'z':
    //if(delay>25){delay-=25;}
    break;
   case 'x':
    //if(delay<150){delay+=25;}
    break;
  }

  switch (direction){
   case '>': if(++XDIFF==LIMIT){XDIFF=0;}
    break;
   case '<': if(--XDIFF==-1){XDIFF=LIMIT-1;}
    break;
   case 'v': if(++YDIFF==LIMIT){YDIFF=0;}
    break;
   case '^': if(--YDIFF==-1){YDIFF=LIMIT-1;}
    break;
  }
  //track ship position on map
  XSHIP=(XMID+XDIFF)%1000;YSHIP=(YMID+YDIFF)%1000;

//todo: handle planets
  if(map[YSHIP][XSHIP] == '0'){
   clear();
   move(YMID, XMID-10);
   printw("landed on a planet!");
   move(YMID+1, XMID-10);
   printw("there is nothing here...");
   timeout(-1);
   getch();
   timeout(150);
  }
  //map is rendered behind ship
  render(YMAX,XMAX,YDIFF,XDIFF,map);
  //ship is written to the middle of the screen
  mvaddch(YMID,XMID,direction);
  //debug: write location of ship
  move(0,0);
  printw("x:%d y:%d",XSHIP,YSHIP);

  //draw changes to screen
  refresh();
 }

//end
 timeout(-1);
 move(2, XMID-9);
 printw("ANY KEY TO EXIT...");

 getch();
 fin();
// free(map);
 return 0;
}
