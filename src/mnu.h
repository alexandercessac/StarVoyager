#include<ncurses.h>

void wPrintRange(WINDOW *w, int top, int left, int len, int width, int offset, int selected, char **list);

int SelectItem(int total, char **list);
