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
// DoSplashIntro(YMAX, XMAX, YMID, XMID);
 /////////////////////////////////

 //set map
 int LIMIT = 1000;
 int map[LIMIT][LIMIT];
 for(int y=0;y<LIMIT;y++){
 for(int x=0;x<LIMIT;x++){
  map[y][x]=get_bg();//get '.' or ' ' randomly
 }}

 //Player starting inventory
 int INVENTORY[]={10,0,3,0,0};

 //Begin Set Galaxies
 struct Galaxy galaxies[GALAXY_COUNT];
 //Pointer to current galaxy
 struct Galaxy* galaxy = NULL;// = malloc(sizeof(struct Galaxy) * GALAXY_COUNT);

 for(int i=0;i<GALAXY_COUNT;i++) {
  galaxies[i].X = 5 + (i*10);
  galaxies[i].Y = 5 + (i*10);
  galaxies[i].Name = "Milky Way";
  galaxies[i].PlanetCount = PLANET_COUNT;
  galaxies[i].Planets = malloc(sizeof(struct Planet)*PLANET_COUNT);

  int tmpY=0,tmpX=0;
  for(int j=0;j<PLANET_COUNT;j++)
  {
   galaxies[i].Planets[j]=MakePlanet(5+(5*j),10+(5*j),Planet_Names[j]);
  }

  map[galaxies[i].Y][galaxies[i].X] = '@';
 }

 //set screen size
 getmaxyx(stdscr, YMAX, XMAX);
 //find screen center
 YMID=YMAX/2;XMID=XMAX/2;
 //set ship
 XSHIP=XMID;YSHIP=YMID;
 //set screen position
 YDIFF=XDIFF=0;
 render(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map);
 refresh();

 //set game speed
 timeout(250);
  getch();

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
     XSHIP=(XMID+XDIFF)%LIMIT;YSHIP=(YMID+YDIFF)%LIMIT;
     render(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map);
    refresh();
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
 XSHIP=(XMID+XDIFF)%LIMIT;YSHIP=(YMID+YDIFF)%LIMIT;
  if(galaxy) {
   if(map[YSHIP][XSHIP] == '*') { //leaving galaxy
    //remove planets on map from galaxy
    for(int j=0;j<PLANET_COUNT;j++)
    { map[galaxy->Planets[j].Y][galaxy->Planets[j].X]=get_bg(); }
    //remove galaxies from map
    for(int j=0;j<GALAXY_COUNT;j++)
    { map[galaxies[j].Y][galaxies[j].X]='@'; }

    XDIFF=(galaxy->X-XMID+LIMIT)%LIMIT;YDIFF=(galaxy->Y-YMID+LIMIT)%LIMIT;
    //track ship position on map
    XSHIP=(XMID+XDIFF)%LIMIT;YSHIP=(YMID+YDIFF)%LIMIT;

    //remove escape vector on map
    map[0][0] = ' ';
    //no longer in a galaxy
    galaxy=NULL;
    //redraw upadated map
    clear();
    render(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map);
   }
   else if(map[YSHIP][XSHIP] == '0') { //entering planet
    //allow each planet in galaxy to perform actions
    //and interact with the planet the user has reached
    for(int j=0;j<PLANET_COUNT;j++) {

     //each planet performs local actions
     DoPlanetActions(&galaxy->Planets[j]);

     //planet performs motive if enough motivation is present
     if(galaxy->Planets[j].Motivation>=10)
     { DoMotive(&galaxy->Planets[j], galaxy->Planets); }

     //TODO: randomize exchange rates on planets
     //found the planet matching current location
     if(galaxy->Planets[j].X==XSHIP&&galaxy->Planets[j].Y==YSHIP)
     { PlanetInteraction(INVENTORY, &galaxy->Planets[j]); }

    } //end planet loop

    //leaving planet; render entire map as window has changed
    render(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map);
   }
   else //moving through current galaxy
   { renderDiff(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map,direction); }
  }
  else { //not in a galaxy
   if(map[YSHIP][XSHIP] == '@') { //entering a galaxy
    for(int i=0;i<GALAXY_COUNT;i++) {
     if(galaxies[i].X==XSHIP&&galaxies[i].Y==YSHIP) {
      //set pointer to galaxy with matching coordinates
      galaxy=&galaxies[i];

      //set planets on map from galaxy
      for(int j=0;j<PLANET_COUNT;j++)
      { map[galaxy->Planets[j].Y][galaxy->Planets[j].X]='0'; }
      //remove galaxies from map
      for(int j=0;j<GALAXY_COUNT;j++)
      { map[galaxies[j].Y][galaxies[j].X]=get_bg(); }
      //Set position to galaxy entrance
      XDIFF=(LIMIT-XMID);YDIFF=(LIMIT-YMID);
      //track ship position on map
      XSHIP=(XMID+XDIFF)%LIMIT;YSHIP=(YMID+YDIFF)%LIMIT;
      //set galaxy entrance on map
      map[0][0] = '*';
      //redraw upadated map
      clear();
      render(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map);
     }
    }
   }
   else //moving through universe
   { renderDiff(YMAX,XMAX,YDIFF,XDIFF,LIMIT,map,direction); }
  }
  //map is rendered behind ship
  //ship is written to the middle of the screen
  mvaddch(YMID,XMID,direction);
  //debug: write location of ship
  move(0,0); printw("x:%d y:%d    ",XSHIP,YSHIP);
  //move(1,0); printw("x:%d y:%d",galaxy->X,galaxy->Y);
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
