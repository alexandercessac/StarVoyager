#include<ncurses.h>

void init();
void fin();

int get_bg();

void render(int ymax,int xmax,int ydiff,int xdiff, int map[1000][1000]);
void renderDiff(int ymax,int xmax,int ydiff,int xdiff, int map[1000][1000], char direction);

