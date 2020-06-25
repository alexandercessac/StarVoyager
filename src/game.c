#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

struct Planet MakePlanet(int y, int x, char* name) {

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

 p.Type=rand() % 4;

 //Resource used for trades
 p.Currency=p.Type;
 p.Population=(rand() % 50000) + 1;

 for(int i=0;i<RESOURCE_TYPE_COUNT;i++)
 {
   //Inventory holds the quantity of resource at index
   p.Inventory[i]=rand() % ((p.Type +1) * 100);
   //ExchangeRate holds the value of resource at index
   p.ExchangeRate[i]=rand() % ((p.Type + 1) * 100);
 }

 //ensure 1:1 exchange rate for currency
 p.ExchangeRate[p.Currency]=1;
 p.Inventory[p.Currency]+=10000;
 return p;
}

void DoLocalTrade(struct Planet* p) {
 int times=(p->Population / ((rand() % 4) + 1));
 for(int i=0;i<times;i++){
  int r=(rand() % RESOURCE_TYPE_COUNT);
  if(i%2==0) { Sell(p, r); }
  else       { Buy(p, r); }
 }
}

void Sell(struct Planet* p, int resource){
 if(p->Inventory[resource]>=1){
  //remove 1 resorce from inventory
  p->Inventory[resource]--;
  //add currency for resource at exchange rate
  p->Inventory[p->Currency]+=p->ExchangeRate[resource];
 }
}

void Buy(struct Planet* p, int resource){
 if(p->Inventory[p->Currency]>=p->ExchangeRate[resource]){
  //add 1 resorce to inventory
  p->Inventory[resource]++;
  //remove currency for resource at exchange rate
  p->Inventory[p->Currency]-=p->ExchangeRate[resource];
 }
}

void PlanetTrade(struct Planet pSell, struct Planet pBuy, int resource) {
 if(pSell.Inventory[resource] >= 1
  && pBuy.Inventory[pSell.Currency] >= pSell.ExchangeRate[resource]){
  //remove 1 resorce from inventory
  pSell.Inventory[resource]--;
  pBuy.Inventory[resource]++;
  //add currency for resource at exchange rate
  pSell.Inventory[pSell.Currency]+=pSell.ExchangeRate[resource];
  pBuy.Inventory[pSell.Currency]-=pSell.ExchangeRate[resource];
 }
}

