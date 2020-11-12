#include <stdio.h>
#include <stdlib.h>
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
  0            //population
 };

 //seed for random number
 //srand(time(0)); //todo: seed once

 //set planet type within limit
 p.Type=rand() % PLANET_TYPE_COUNT;

 //set inital motive within limit
 p.Motive=rand() % MOTIVE_TYPE_COUNT;

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
  if(i%2==0) { Sell(p, r); }
  else       { Buy(p, r); }
 }
}

// Exchange resource for planet's currency
//+at exchange rate if planet has at least 1
void Sell(struct Planet* p, int resource){
 if(p->Inventory[resource]>=1){
  //remove 1 resorce from inventory
  p->Inventory[resource]--;
  //add currency for resource at exchange rate
  p->Inventory[p->Currency]+=p->ExchangeRate[resource];
 }
}

// Exchange planet's currency for resource
//+at exchange rate if planet has enough currency
void Buy(struct Planet* p, int resource){
 if(p->Inventory[p->Currency]>=p->ExchangeRate[resource]){
  //add 1 resorce to inventory
  p->Inventory[resource]++;
  //remove currency for resource at exchange rate
  p->Inventory[p->Currency]-=p->ExchangeRate[resource];
 }
}

// Exchange selling planet's currency type from buying planet for 1
//+of selling planet's resource at selling planet's exchange rate
void PlanetTrade(struct Planet* pSell, struct Planet* pBuy, int resource) {
 if(pSell->Inventory[resource] >= 1
  && pBuy->Inventory[pSell->Currency] >= pSell->ExchangeRate[resource]){
  //remove 1 resorce from inventory
  pSell->Inventory[resource]--;
  pBuy->Inventory[resource]++;
  //add currency for resource at exchange rate
  pSell->Inventory[pSell->Currency]+=pSell->ExchangeRate[resource];
  pBuy->Inventory[pSell->Currency]-=pSell->ExchangeRate[resource];
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
