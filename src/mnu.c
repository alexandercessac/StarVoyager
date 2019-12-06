#include<ncurses.h>

#include<stdlib.h>
#include<string.h>

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

int Xfer(int total, int listLeft[total], int listRight[total], int exchange[total], int cIndex, char *names[]) {
 WINDOW *w;
 int ch, i=0, offset=0, YMAX, XMAX;
 int topPad=1,leftPad=2;

 //get bounds of main window
 getmaxyx(stdscr, YMAX, XMAX);

 w=newwin(YMAX/2, XMAX-10, YMAX/4, 5);
 keypad(w,TRUE);
 box(w,ACS_VLINE,ACS_HLINE);

 getmaxyx(w,YMAX,XMAX);

 int limit=(total>YMAX-topPad-1) ? YMAX-topPad-1 : total;
 int width=XMAX-leftPad-leftPad;

 ////////// print
 mvwprintw(w, topPad, leftPad, "%-*s%-*s%s", width/3, "Inventory", width/3, "Price", "Shop");
 for(int j=0;j<limit;j++) {
  if(j==i)
   wattron(w, A_STANDOUT);
  else
   wattroff(w, A_STANDOUT);
  //mvwprintw(w,j+1,1, "%s", names[j]);
  mvwprintw(w, topPad+j+1, leftPad, "%-*s:%-*d%-*d%-*s:%-*d", width/6, names[j], width/6, listLeft[j], width/3, exchange[j], width/6, names[j], width/6, listRight[j]);
//  wprintw(w,": %-*d",width/6, listLeft[j], " ");
 }
 wattroff(w,A_STANDOUT);
 wrefresh(w);
 ///////// end print

 //todo:


 while((ch=wgetch(w))!='q'){
  switch(ch){
   case KEY_DOWN:
    if(++i==total) i=0;
    break;
   case KEY_UP:
    if(i--==0) i=total-1;
    break;
   case KEY_LEFT:
     if(listLeft[cIndex]>=exchange[i]&&listRight[i]>=1){
      listLeft[i]++;
      listRight[i]--;
      listLeft[cIndex]-=exchange[i];
      listRight[cIndex]+=exchange[i];
     }
    break;
   case KEY_RIGHT:
     if(listLeft[i]>=1&&listRight[cIndex]>=exchange[i]){
      listLeft[i]--;
      listRight[i]++;
      listLeft[cIndex]+=exchange[i];
      listRight[cIndex]-=exchange[i];
     }
    break;
  }

  mvwprintw(w, topPad, leftPad, "%-*s%-*s%-*s%-*s%-*s", width/6, "Inventory", width/6, " ", width/3, "Price", width/6, "Shop", width/6, " ");
 for(int j=0;j<limit;j++) {
  if(j==i)
   wattron(w, A_STANDOUT);
  else
   wattroff(w, A_STANDOUT);

   mvwprintw(w, topPad+1+j, leftPad, "%-*s:%-*d%-*d%-*s:%-*d", width/6, names[j], width/6, listLeft[j], width/3, exchange[j], width/6, names[j], width/6, listRight[j]);
  }
  wattroff(w, A_STANDOUT);
  wrefresh(w);
 }



 //clear the window
 werase(w);
 //update the console screen
 wrefresh(w);
 //free resources held by the window
 delwin(w);
 return 0;
}

int SelectItem(int srcTotal, char **srcList) {
 WINDOW *w;
 int ch, i=0, offset=0, YMAX, XMAX;
 int topPad=1, leftPad=2;
 int total=srcTotal+1;

 char** list=malloc(total * sizeof(char*));
 for(;i<srcTotal;i++) {
  list[i]=srcList[i];
 }
 i=0;
 //memcpy(list, srcList, srcTotal * sizeof(char*));
 list[srcTotal]="cancel";
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
    //free resources held by the window and list
    delwin(w);
    free(list);
    //return the currently selected index
    return i == total-1 ? -1 : i;
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

