#pragma once

enum ResourceType {
 Gold=0,
 Silver=1,
 Ore=2,
 Oil=3,
 Tech=4
};
static char *Resource_Name[]={
 "Gold","Silver","Ore","Oil","Tech"
};

static const int PLANET_COUNT=7;
static char *Planet_Names[]={
 "Earth","Mars","Venus","Aphrodite","Jupiter","Saturn","Athena"
};

struct Planet {
 int X;
 int Y;
 char* Name;
 enum ResourceType Currency;
 int ExchangeRate[5];
 int Inventory[5];
};

struct Planet MakePlanet(int y, int x, char* name);
struct Resource* MakeResources();
