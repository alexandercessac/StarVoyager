#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "game.h"

// Construct a new planet with the provided y/x coordinates
//+using the provided name. Type is generated randomly.
//+currency is based on type and exchange rate is random
//+but is influenced by planet type.
struct Planet MakePlanet(int y, int x, char* name) {

 //create empty planet with provided params
 struct Planet p =
 {
  x,           //x coordinate
  y,           //y coodinate
  name,        //name
  0,           //type
  0,           //currency
  {0,0,0,0,0}, //inventory
  {0,0,0,0,0}, //exchange rate
  0,           //population
  0,           //monuments
  0,           //army
  0,           //motive
  0,           //motivation
  NULL         //target
 };

 //seed for random number
 //srand(time(0)); //todo: seed once

 //set planet type within limit
 p.Type=rand() % PLANET_TYPE_COUNT;

 //set inital motive within limit
 p.Motive=rand() % MOTIVE_TYPE_COUNT;
 p.Motivation=0;
 //set currency based on planet type
 p.Currency=p.Type;

 //set population
 p.Population=(rand() % 50000) + 1;

 //set quantity and value of each resource
 for(int i=0;i<RESOURCE_TYPE_COUNT;i++)
 {
   //Inventory holds the quantity of resource at index
   p.Inventory[i]=rand() % 100;

   //set value based on difference from currency index
   int diff = p.Type > i ? p.Type - i : i - p.Type;
   //ExchangeRate holds the value of resource at index
   p.ExchangeRate[i]=(rand() % ((PLANET_TYPE_COUNT * 11) - (diff * 10))) + 2;
 }

 //ensure 1:1 exchange rate for currency
 p.ExchangeRate[p.Currency]=1;
 //add extra currency as this will be the main resource
 p.Inventory[p.Currency]+=1000;
 return p;
}

bool BuyMotivation(struct Planet* p, int resource, int cost) {
 if(p->Inventory[resource] >= cost) {
    p->Inventory[resource] -= cost;
    p->Motivation++;
    return true;
 }
 return false;
}

void DoMotivation(struct Planet* p) {
 if(!p || p->Population==0) {return;}
 switch(p->Motive) {
  case Trade:
  { //Generate currency to prepare for trade
   GenerateCurrency(p);
   p->Motivation++;
   break;
  }
  case Peace:
  {
   GrowPopulation(p);
   p->Motivation++;
   break;
  }
  case Build:
  { //Purchase motivation with Ore
   if(false == BuyMotivation(p, Ore, 1000))
   { //Not enough Ore; attempt to get more
    if(p->Currency == Ore) { GenerateCurrency(p); }
    else                   { Buy(p, Ore, 1000); }
   }
   break;
  }
  case War:
  {
   //TODO: scale based on planet type
   p->Army+=p->Population/4;

   if(false == BuyMotivation(p, Oil, 1000))
   { //Not enough oil; attempt to get more
    if(p->Currency == Oil) { GenerateCurrency(p); }
    else                    { Buy(p, Oil, 1000); }
   }
   break;
  }
  case Learn:
  { //Purchase motivation with Tech
   if(false == BuyMotivation(p, Tech, 1000))
   { //Not enough Tech; attempt to get more
    if(p->Currency == Tech) { GenerateCurrency(p); }
    else                    { Buy(p, Tech, 1000); }
   }
   break;
  }
 }
}

void FindTradeTarget(struct Planet* p, struct Planet planets[PLANET_COUNT]) {
 for(int i=0; i<PLANET_COUNT; i++) {
  p->Target=&planets[rand()%PLANET_COUNT];
  if(p->Target->Currency!=p->Currency)
  { return; }
 }
 //no suitable planet found; clear Target
 p->Target=NULL;
}

void FindWarTarget(struct Planet* p, struct Planet planets[PLANET_COUNT]) {
 for(int i=0; i<PLANET_COUNT; i++) {
  p->Target=&planets[rand()%PLANET_COUNT];
  if(p->Target->Population>0)
  { return; }
 }
 //no suitable planet found; clear Target
 p->Target=NULL;
}

void FindPeaceTarget(struct Planet* p, struct Planet planets[PLANET_COUNT]) {
 for(int i=0; i<PLANET_COUNT; i++) {
  p->Target=&planets[rand()%PLANET_COUNT];
  if(p->Target->Motive==War)
  { return; }
 }
 //no suitable planet found; clear Target
 p->Target=NULL;
}

void GrowPopulation(struct Planet* p) {
 p->Population+=p->Population/4;
}

void DoMotive(struct Planet* p, struct Planet planets[PLANET_COUNT]) {
 if(p->Motivation >= 10) {
  //Population increases
  GrowPopulation(p);
  switch(p->Motive) {
   case Trade:
   {
    if(p->Target)
    { PlanetTrade(p, p->Target, p->Currency, 1000); p->Target=NULL; }
    else
    { FindTradeTarget(p, planets); }
    break;
   }
   case Peace:
   {
    if(p->Target)
    { PlanetPeace(p); p->Target=NULL; }
    else
    { FindPeaceTarget(p, planets); }
    break;
   }
   case Build:
   {
    p->Monuments++;
    break;
   }
   case War:
   {
    if(p->Target)
    { PlanetWar(p); p->Target=NULL; }
    else
    { FindWarTarget(p, planets); }
    break;
   }
   case Learn:
   { //TODO:
     //      Invention that sheilds agianst war attempt?
     //      Invention that generates resources?
    if(p->Inventory[Tech] >= 1000) {
       p->Inventory[Tech] -= 1000;
       p->Motivation++;
    }
    else if(p->Currency == Tech)
     { GenerateCurrency(p); }
    else { Buy(p, Tech, 1000); }
    break;
   }
  }
  //Motivation achieved; set motivation back to 0
  p->Motivation=0;
 }
}

// Convert resources to and from currency at random
//+based on population to simmulate local commerce
void DoLocalTrade(struct Planet* p) {
 //times to buy or sell
 //either all, 1/2, 1/3, or 1/4 of population
 int times=(p->Population / ((rand() % 4) + 1));
 for(int i=0;i<times;i++){
  //random resource to buy or sell
  int r=(rand() % RESOURCE_TYPE_COUNT);
  //alternate between buying and selling
  if(i%2==0) { Sell(p, r, 1); }
  else       { Buy(p, r, 1); }
 }
}

// Exchange resource for planet's currency
//+at exchange rate if planet has enough of the resource
bool Sell(struct Planet* p, int resource, int count){
 if(p->Inventory[resource]>=count){
  //remove 1 resorce from inventory
  p->Inventory[resource]--;
  //add currency for resource at exchange rate
  p->Inventory[p->Currency]+=p->ExchangeRate[resource]*count;
  //purchase made
  return true;
 }
 return false;
}

// Exchange planet's currency for resource
//+at exchange rate if planet has enough currency
bool Buy(struct Planet* p, int resource, int count) {
 if(p->Inventory[p->Currency]>=p->ExchangeRate[resource]*count) {
  //add purchased resources to inventory
  p->Inventory[resource]+=count;
  //remove currency for resource at exchange rate
  p->Inventory[p->Currency]-=p->ExchangeRate[resource]*count;
  //purchase made
  return true;
 }
 return false;
}

// Exchange selling planet's currency type from buying planet for 1
//+of selling planet's resource at selling planet's exchange rate
void PlanetTrade(struct Planet* pSell, struct Planet* pBuy, int resource, int count) {
 if(Sell(pSell, resource, count)) {
  //pSell sucessfully exchanged resource for currency
  if(false == Buy(pBuy, resource, count)) {
   //pBuy failed to exchange currency for resource
   //pSell must exchange currency for resource again
   Buy(pSell, resource, count);
  }
 }
}

void PlanetWar(struct Planet* p) {
 if(!p->Target) {return;}
 int x=p->Army-p->Target->Army;

 if(x>0) {
  //win
  p->Inventory[p->Target->Currency]+=x;
  p->Target->Inventory[p->Target->Currency]-=x;
  p->Target->Population-=x;
  p->Target->Army=0;
  p->Army-=x;
 }
 else {
  p->Target->Army-=x;
  p->Army=0;
  p->Inventory[p->Currency]-=x;
  p->Target->Inventory[p->Currency]+=x;
 }
}

void PlanetPeace(struct Planet* p) {
 if(p->Target->Motive==War) {
  p->Target->Motivation-=20;
 }
}

// Generate planet's currency resource based on population
void GenerateCurrency(struct Planet *p) {
 int gains = ((rand() % p->Population) + 1) /2;
 if(MAX_CURRENCY - gains > p->Inventory[p->Currency])
 { p->Inventory[p->Currency]+=gains; }
 else //Planet has too much currency; trigger event?
 { p->Inventory[p->Currency]=MAX_CURRENCY; }
}
