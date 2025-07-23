# StarVoyager
Travel the stars on your console!

## Requires ncurses dev libraries to compile
If running a debian based distro:
`sudo apt-get install libncurses5-dev libncursesw5-dev`

running `make` using the make file should result in a StarVoyager file that can be run

## Building/Running with Docker

### Docker/rebuildDocker
running this script will build a `starvoyager` image that contains the compiled application

### Docker/runDocker
running this script will run the built `starvoyager` image

# Controls

Use arrow keys to move. Holding down an arrow will move faster.

`q` to quit


## Galaxies

Galaxies are designated by a `@` symbol

Flying into a galaxy will cause you to enter that galaxy and enable you to visit any of the planets there.

Entering a galaxy:
```
.     .    .  
    > @    
 .          .
   .      .
```

### Leaving a galaxy

After entering a galaxy, the exit will be designated by a `*` symbol.

Flying into a galaxy exit will cause you to leave the galaxy and enable you to enter any other galaxy, or re-enter the same one.

Exiting a galaxy
```
   .       .
     > *     .
.      .   .
```
## Planets

Planets are designated by a `0` symbol.

Flying into a planet will cause you to land on it. When on a planet you have the following options:

- Trade
- Cancel

Entering a planet
```
   .     .
     > 0   .
 .     . 
```

### Trading
Planets will have a specific resource used as currency as noted at the top of the trade menu. The price of this resource in the planet's shop will always be 1.

Using the up/down arrows you can select a resource for trading.
Pressing the right arrow when a given resource is selected will attempt to sell 1 unit of that resource to the planet in exchange for the associated price of that resource in the planet's currency resource.
Pressing the left arrow when a given resource is selected will attempt to purchase 1 unit of that resource for the associated price.

Pressing the `>` key will attempt to sell as much of the selected resource as possible.
Pressing the `<` key will attempt to buy as much of the selected resource as possible.

Pressing the `q` key will exit the planet's trade menu.
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

 - Explore the planets in each galaxy
 - Buy and sell to become a wealthy intergalactic trader
 - Aid or thwart the motives of a planets inhabitants for personal gain

More features coming soon!
