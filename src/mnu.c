#include<ncurses.h>

void wPrintRange(WINDOW *w, int top, int left, int len, int width, int offset, int selected, char **list) {
 int item=offset;
 for(int i=0;i<len;i++) {
  if(item==selected)
   wattron(w, A_STANDOUT);
  else
   wattroff(w, A_STANDOUT);

  mvwprintw(w, top+i, left, "%-*s", width, list[item++]);
 }
 wattroff(w, A_STANDOUT);
}

int SelectItem(int total, char **list) {
 WINDOW *w;
 int ch, i=0, offset=0, YMAX, XMAX;
 int topPad=1, leftPad=2;

 //get bounds of main window
 getmaxyx(stdscr, YMAX, XMAX);
 //create a new window within the main window
 w = newwin(YMAX/4, XMAX-10, YMAX-(YMAX/4), 5 );
 //enable keyboard for the new window
 keypad(w, TRUE );
 //get the bounds for the new window
 getmaxyx(w, YMAX, XMAX);
 //create an outline for the new window
 box(w, ACS_VLINE, ACS_HLINE );

 //declare the max number of items to show
 int limit=(total > YMAX-topPad-1) ? YMAX-topPad-1 : total;
 int width=(XMAX-leftPad-leftPad);
 //print {limit} number of items from the list
 //starting with item number {offset} and select item {i}
 wPrintRange(w, topPad, leftPad, limit, width, offset, i, list);
 wrefresh(w);

// loop through user input until a selection is made
 while(true){
  switch(wgetch(w)) {
   case KEY_UP:
   case 65: //maybe dont need
    if( --i<0 )//loop around to bottom
    { i=total-1; offset=total-limit; }
    else if(i<offset) //move offset up
     offset=i;
    break;
   case KEY_DOWN:
   case 66: //maybe dont need
    if(++i>total-1)//loop around to top
     offset=i=0;
    else if(i+topPad>offset+limit)
    { offset=i+topPad-limit; }//move offset down
    break;
   case 10://Enter button
    //clear the window
    werase(w);
    //update the console screen
    wrefresh(w);
    //free resources held by the window
    delwin(w);
    //return the currently selected index
    return i;
    break;
   default:// debug
   // mvwprintw(w,YMAX-2, XMAX/2-10, "pressed: %d, %d, %d", ch, KEY_UP, KEY_DOWN);
    continue;
    break;
   }
  //print selection
  wPrintRange(w, topPad, leftPad, limit, width, offset, i, list);
  wrefresh( w );
 }
 return -1;
}

