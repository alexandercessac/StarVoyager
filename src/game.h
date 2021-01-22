#pragma once

//Max amount of curency resource allowed
static const int MAX_CURRENCY=2000000000;

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
// TODO: move some types to motive
//+new types that influence motives
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

// Max number of motive types
static const int MOTIVE_TYPE_COUNT=5;
// Types of motives
enum MotiveTypes {
 Trade=0, Peace=1, Build=2, War=3, Learn=4
};
static char *Motive_Names[]={
 "Trade", "Peace", "Build", "War", "Learn"
};

// Max number of planets per galaxy
static const int PLANET_COUNT=7;
// Max number of galaxies
static const int GALAXY_COUNT=3;
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
 int            X;
 int            Y;
 char*          Name;
 enum           PlanetType Type;
 enum           ResourceType Currency;
 int            ExchangeRate[5];
 int            Inventory[5];
 int            Population;
 int            Army;
 int            Monuments;
 int            Motive;
 int            Motivation;
 struct Planet* Target;
};

//static const int GALAXY_MAP_SIZE=100;
struct Galaxy {
 int            X;
 int            Y;
// int            Map[100][100];
 char*          Name;
 int            PlanetCount;
 struct Planet* Planets;
};

// Constructs a new planet
struct Planet MakePlanet(int y, int x, char* name);

// Do actions to increase motivation
void DoMotivation(struct Planet* p);
// Do action related to motive (assuming full motivation)
void DoMotive(struct Planet* p, struct Planet planets[PLANET_COUNT]);

// Exchange resources and currency
void DoLocalTrade(struct Planet* p);

// Exchange currency for resource at exchange rate
bool Buy(struct Planet* p, int resource, int count);
// Exchange resource for currency at exchange rate
bool Sell(struct Planet* p, int resource, int count);

// Generate currency resource based on population
void GenerateCurrency(struct Planet *p);

//
void GrowPopulation(struct Planet *p);

// Trade a resource from buying planet for selling planet's currency at
//+the exchange rate of selling planet
void PlanetTrade(struct Planet* pSell, struct Planet* pBuy, int resource, int count);
// Attack target planet attempting to take resources
void PlanetWar(struct Planet* p);
// Greatly reduce targe planet's motivation
//+if target planet's motivation is war
void PlanetPeace(struct Planet* p);

// Allow planet to perform day to day actions
//+such as local commerce and trade
void DoPlanetActions(struct Planet* p);
