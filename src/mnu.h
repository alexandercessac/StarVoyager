#pragma once

#include<ncurses.h>

void wPrintRange(WINDOW *w, int top, int left, int len, int width, int offset, int selected, char **list);

int Xfer(int total, int listLeft[total], int listRight[total], int exchange[total], int cIndex, char* names[total]);

int SelectItem(int total, char **list);
