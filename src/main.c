#include<ncurses.h>

#include "ui.h"
#include "mnu.h"
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

 struct Planet p=MakePlanet(5,5,"urth");
 int INVENTORY[]={3,0,10,0,0};
 //todo planets
// map[YMID][XMID-1]='0';

 int tmpY=0,tmpX=0;
 struct Planet* planets=malloc(sizeof(struct Planet)*PLANET_COUNT);
 for(int j=0;j<PLANET_COUNT;j++)
 {
//  tmpY=rand()%LIMIT;
//  tmpX=rand()%LIMIT;
  while(map[tmpY][tmpX]=='0')
//  {tmpY=rand()%LIMIT;tmpX=rand()%LIMIT;}
  {tmpX=tmpX+2;}
  planets[j]=MakePlanet(tmpY,tmpX,Planet_Names[j]);
  map[tmpY][tmpX]='0';
// printw("%s%d,%d",planets[j].Name,tmpY,tmpX);
// refresh();
// getch();
 }



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

 //handle planets
 if(map[YSHIP][XSHIP] == '0'){
   clear();
   move(YMID, XMID-10);
   printw("planets: %d!", PLANET_COUNT);

  //find planet
  for(int j=0;j<PLANET_COUNT;j++) {
   if(planets[j].X==XSHIP&&planets[j].Y==YSHIP){
    clear();
    move(YMID, XMID-10);
    printw("landed on a planet: %s!", planets[j].Name);
    //todo: menu what to do on planet
    timeout(-1);
    getch();
    //todo: dont assume trade
    Xfer(5, INVENTORY, planets[j].Inventory, planets[j].ExchangeRate, planets[j].Currency, Resource_Name);
  }
 }

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
