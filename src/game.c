#include "game.h"
//#include <string.h>
//#include <stdlib.h>

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
  //todo: set at random
  p.Inventory[0]=10;
  p.ExchangeRate[0]=1;      //gold
  p.Inventory[1]=2;
  p.ExchangeRate[1]=2;      //silver
  p.Inventory[2]=25;
  p.ExchangeRate[2]=3;      //ore
  p.Inventory[3]=100;
  p.ExchangeRate[3]=5;      //oil
  p.Inventory[4]=10;
  p.ExchangeRate[4]=100;    //tech
  //resource used for trades
  p.Currency=Gold;
  //ensure 1:1 exchange rate for currency
  p.ExchangeRate[p.Currency]=1;

return p;
}

