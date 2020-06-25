#pragma once

static const int PLANET_TYPE_COUNT=5;
enum PlanetType {
 Greedy=0,
 Spiritual=1,
 Crafty=2,
 Agressive=3,
 Advanved=4
};
static char *PlanetTypeNames[]={
 "Greedy",
 "Spiritual",
 "Crafty",
 "Agressive",
 "Advanved"
};

static const int RESOURCE_TYPE_COUNT=5;
enum ResourceType {
 Gold=0, Silver=1, Ore=2, Oil=3, Tech=4
};
static char *Resource_Name[]={
 "Gold", "Silver", "Ore", "Oil", "Tech"
};

static const int PLANET_COUNT=7;
static char *Planet_Names[]={
 "Earth",
 "Mars",
 "Venus",
 "Aphrodite",
 "Jupiter",
 "Saturn",
 "Athena"
};

struct Planet {
 int   X;
 int   Y;
 char* Name;
 enum  PlanetType Type;
 enum  ResourceType Currency;
 int   ExchangeRate[5];
 int   Inventory[5];
 int   Population;
};

struct Planet MakePlanet(int y, int x, char* name);
struct Resource* MakeResources();
void DoLocalTrade(struct Planet* p);
void Buy(struct Planet* p, int resource);
void Sell(struct Planet* p, int resource);

void PlanetTrade(struct Planet pSell, struct Planet pBuy, int resource);
