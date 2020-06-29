#pragma once

#include<ncurses.h>

//print a range of char* within the provided limits on the provided window
void wPrintRange(WINDOW *w, int top, int left, int len, int width, int offset, int selected, char **list);

//transfer item from on list to the other based on the exchange rate at that index
int Xfer(int total, int listLeft[total], int listRight[total], int exchange[total], int cIndex, char* names[total]);

//Select an item from the list
int SelectItemBasic(int srcTotal, char **srcList);

//Select an item from the list with a title for the menu
int SelectItem(int srcTotal, char **srcList, char *title, int titleLen);
