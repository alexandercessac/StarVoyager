# StarVoyager
Travel the stars on your console

## Requires ncurses dev libraries to compile
If running a debian based distro:
`sudo apt-get install libncurses5-dev libncursesw5-dev`


# Controls

Use arrow keys to move. Holding down an arrow will move faster.

`q` to quit


## Planets

Flying into a planet will cause you to land on it. When on a planet you have the following options:

- Trade
- Cancel

### Trading
Planets will have a specific resource use as currency as noted at the top of the trade menu. The price of this resource in the planet's shop will always be 1.

Using the up/down arrows you can select a resource for trading.
Pressing the right arrow when a given resource is selected will attempt to sell 1 unit of that resource to the planet in exchange for the associated price of that resource in the planets currency resource.
Pressing the left arrow when a given resource is selected will attempt to purchase 1 unit of that resource for the associated price.

Pressing the `>` key will attempt to sell as much of the selected resource as possible.
Pressing the `<` key will attempt to buy as much of the selected resource as possible.

Pressing the `q` key will exit the planet's trade menu
```
     ┌────────────────────────────────────────────────────────────────┐
     │ Inventory           Price in Gold                Shop          │
     │ ────────────────────────────────────────────────────────────── │
     │ Gold      :10        1                   Gold      :1,760      │
     │ Silver    :0         17                  Silver    :49         │
     │ Ore       :3         29                  Ore       :18         │
     │ Oil       :0         18                  Oil       :50         │
     │ Tech      :0         10                  Tech      :86         │
     │                                                                │
     └────────────────────────────────────────────────────────────────┘
```
In the above Trading menu, selling 1 unit of `Ore` would result in 29 units of gold moved to the player's inventory from the planet's shop.

# Objective

Visit all 5 planets. Buy low and sell high to become the most wealthy voyager in the stars!

More features coming soon!
