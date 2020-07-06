#pragma once

// Max number of planet Types
static const int PLANET_TYPE_COUNT=5;
// Types of planets
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

// Max number of resource types
static const int RESOURCE_TYPE_COUNT=5;
// Types of resources
enum ResourceType {
 Gold=0, Silver=1, Ore=2, Oil=3, Tech=4
};
static char *Resource_Name[]={
 "Gold", "Silver", "Ore", "Oil", "Tech"
};

// Max number of planets
static const int PLANET_COUNT=7;
// Names that can be assigned to planets
static char *Planet_Names[]={
 "Earth",
 "Mars",
 "Venus",
 "Aphrodite",
 "Jupiter",
 "Saturn",
 "Athena"
};

// Planet definition
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

// Constructs a new planet
struct Planet MakePlanet(int y, int x, char* name);

// Exchange resources and currency
void DoLocalTrade(struct Planet* p);
// Exchange currency for resource at exchange rate
void Buy(struct Planet* p, int resource);
// Exchange resource for currency at exchange rate
void Sell(struct Planet* p, int resource);

// Generate currency resource based on population
void GenerateCurrency(struct Planet *p);

// Trade a resource from buying planet for selling planet's currency at
//+the exchange rate of selling planet
void PlanetTrade(struct Planet* pSell, struct Planet* pBuy, int resource);
