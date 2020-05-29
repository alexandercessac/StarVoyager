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
  Gold,        //currency
  {0,0,0,0,0}, //inventory
  {0,0,0,0,0}  //exchange rate
 };
 //seed for random number
 //srand(time(0)); //todo: seed once

 //Inventory holds the quantity of resource at index
 //ExchangeRate holds the value of resource at index
 p.Inventory[0]=rand() % 100000;
 p.ExchangeRate[0]=1;             //gold

 p.Inventory[1]=rand() % 1000;
 p.ExchangeRate[1]=rand() % 25;   //silver

 p.Inventory[2]=rand() % 5000;
 p.ExchangeRate[2]=rand() % 25;  //ore

 p.Inventory[3]=rand() % 5000;
 p.ExchangeRate[3]=rand() % 100;  //oil

 p.Inventory[4]=rand() % 2500;
 p.ExchangeRate[4]=rand() % 100;  //tech

 //resource used for trades
 p.Currency=Gold;
 //ensure 1:1 exchange rate for currency
 p.ExchangeRate[p.Currency]=1;

 return p;
}

void DoActivity(struct Planet* p, int times) {
 for(int i=0;i<times;i++){
  //random resource 1-4
  int index=(rand() % 3) + 1;

 }
}
