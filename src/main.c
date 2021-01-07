#include<ncurses.h>

#include "ui.h"
#include "mnu.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include <locale.h>//formatting

int main()
{

 setlocale(LC_NUMERIC,"");//formatting
 init();//ui.h
 int YMAX, XMAX, YMID, XMID, YDIFF, XDIFF, YSHIP, XSHIP;

 /////////////////////////////////
 DoSplashIntro(YMAX, XMAX, YMID, XMID);
 /////////////////////////////////

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

 //Player starting inventory
 int INVENTORY[]={10,0,3,0,0};

 int tmpY=0,tmpX=0;
 struct Planet* planets=malloc(sizeof(struct Planet)*PLANET_COUNT);
 for(int j=0;j<PLANET_COUNT;j++)
 {
  while(map[tmpY][tmpX]=='0')
  { tmpX=tmpX+4;tmpY=tmpY+4; }

  planets[j]=MakePlanet(tmpY,tmpX,Planet_Names[j]);
  map[tmpY][tmpX]='0';
 }

 //set game speed
 timeout(250);

 //main
 int direction = '>';
 int input;
 while((input = getch()) != 'q') {
  //set direction based on input
  switch(input){
   case KEY_RIGHT:direction='>'; break;
   case KEY_LEFT: direction='<'; break;
   case KEY_DOWN: direction='v'; break;
   case KEY_UP:   direction='^'; break;
   case KEY_RESIZE: //Window has been resized;
    //clear previous location of ship
    mvaddch(YMID,XMID,' '); //todo: draw correct character from map
    //set new screen size
    getmaxyx(stdscr, YMAX, XMAX);
    //find new screen center
    YMID=YMAX/2;XMID=XMAX/2;
    break;
   case 'z':
    //increase speed
    //if(delay>25){delay-=25;}
    break;
   case 'x':
    //decrease speed
    //if(delay<150){delay+=25;}
    break;
  }
  //move based on direction
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

   //find planet
   for(int j=0;j<PLANET_COUNT;j++) {
    //generate each planet's currency resource
    GenerateCurrency(&planets[j]);
    //local trade happens for all planets
    DoLocalTrade(&planets[j]);

    //todo: randomize exchange rates on planets

    if(planets[j].X==XSHIP&&planets[j].Y==YSHIP){
     //found the planet matching current location

     //clear main window to show planet detail
     clear();
     //Write details about current plant
     WritePlanetDetails(planets[j], 1, 3);
     //refresh changes to main window
     refresh();

     //todo: move options somewhere else

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
     { Xfer(5, INVENTORY, planets[j].Inventory, planets[j].ExchangeRate, planets[j].Currency, Resource_Name); }

   } //end planet interaction

  } //end planet loop

   //render entire map as window has changed
   render(YMAX,XMAX,YDIFF,XDIFF,map);
  }
  else //just moving; only render diffs
  { renderDiff(YMAX,XMAX,YDIFF,XDIFF,map,direction); }

  //map is rendered behind ship
  //ship is written to the middle of the screen
  mvaddch(YMID,XMID,direction);
  //debug: write location of ship
  move(0,0); printw("x:%d y:%d",XSHIP,YSHIP);
  //draw changes to screen
  refresh();
 }
 //pressed 'q'; end input loop

 //end
 timeout(-1);
 move(2, XMID-9);
 printw("ANY KEY TO EXIT...");

 getch();
 fin();//ui.h
 //free(map);
 return 0;
}
