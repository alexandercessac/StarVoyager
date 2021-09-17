#include "game.h"

#include<ncurses.h>

void init();
void fin();

int get_bg();

void DoSplashIntro(int YMAX, int XMAX, int YMID, int XMID);

void render(int ymax,int xmax,int ydiff,int xdiff,int limit,int map[limit][limit]);
void renderDiff(int ymax,int xmax,int ydiff,int xdiff,int limit,int map[limit][limit],char direction);

void WritePlanetDetails(struct Planet *p, int y, int x);

void PlanetInteraction(int inv[RESOURCE_TYPE_COUNT], struct Planet *p);
