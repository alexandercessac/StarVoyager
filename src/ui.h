#include<ncurses.h>

//const int SV_MAP_SIZE = 10000;

void init();
void fin();

int get_bg();

void render(int ymax,int xmax,int ydiff,int xdiff, int map[1000][1000]);

typedef struct Coordinate Coordinate;

struct Coordinate{
 int x;
 int y;
 Coordinate* up;
 Coordinate* down;
 Coordinate* left;
 Coordinate* right;
};

typedef struct {
  Coordinate* min;
  Coordinate* max;
} Grid;

Coordinate* mkcoord(int x, int y);
Grid* mkgrid(Coordinate* min, Coordinate* max);
