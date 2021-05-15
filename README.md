# ProjectX

## Possible Names 

 * "Before The Sun Comes Up"
 * "The Blag"

## Overview
Rouge like where the player takes on the role of a archetypical burglar. A game involves the player moving from house to house stealing loot. Scores for the game are based on how much the player can steal in a given game. At the end of the game the player's score is reset and they must start again. If a player is good enough they will make it to the end of "Henderson St"(Working Name) and get a bonus added to their score. The player's game will end once they rob all the houses or get killed by the police. Players can also get killed by ghosts. Once a player is killed they must restart the game and loose all their items.

## Cast

 * Robber : Grabber Dan. A portly man with a scar on his face and a 5 o'clock shadow. Could also smoke cigars.
 * Resident:  Mrs. Battersby an elderly lady in a night dress who lives at the house being robbed.
 * Various Ghosts.
 * Police complete with their bobby hats.

## Graphics Treatment
ProjectX will be a pixel game. ProjectX will have a top down view like "A Link to The Past" for SNES. Houses will range form american style trailers to ornate mansions. The main player will wear a striped shirt and have a black mask. The resident of the house will always be the same old lady in her night dress.

## Systems

### Overview
The following is a list that provides an overview of all the required systems for the game. See each systems section for more information.

 * A tile Atlas for dealing with sprites and loading in animations.
 * A noise system where the player will have to remain quiet.
 * A room system that randomly generates new house layouts each game. 
 * A power up system where the player can collect a number of items allowing them to rob more loot. 
 * A. An AI system where ghosts and house residents attack the player. This will include police AI as well. See AI section
 * A loot system. This will control how much a player will score within a given game
 * A map editing system allowing for developers to design rooms while in the game

As the player moves around the game they loose health. A player starts with three points of health. If a player reatures zero health they die and their score is zero as they where unable to escape with any loot.

### Tile Atlas

### House System
Game will feature a pool of predefined hosues. Houses will consist of interconnected rooms. All interconnected rooms will have furniture placed randomly in them. The furniture will act as containers. The player can then interact with the furniture by searching the furniture. This will cause the player to make noise however this is how the player will find their loot and power ups. 

When moving from room to room the view port will scroll in much the same way that the legened of zelda does. This will happen when a player comes in to contact with a door entity. See maps section for more details on how entites work. Moving though doors will happen in three different phases. First the player will come in to contact with the door. At that point the player entity controller will be swapped out with a door transition controller entity. This door transition controller entity will move the player though the door with out any input from the player. Once the player has moved though the door the screen view port will be scrolled to the next room. At this point the door transition controller will move the player out in to the next room. At that point the door transition controller will be removed and the player will regain control.

### Noise
The game will feature a noise system. Making noise will attract unwanted attention to the player and may get them caught.

### Power ups
A list of power ups the player can get

 * Night Vision Goggles
 * Sneakers... for sneaking. Helps the player make less noise.
 * Gloves allows for searching containers more quickly.
 * Weapons which will allow the player to more easly fight both police and ghosts.

### AI
While moving though the house the player will have to contend with various computer controlled AI players. 

 * Ghosts: Stupid. Roam about.
 * Residents: Will walk in their house from room to room. Not activity looking for the player. Will call the police if they see the player. 
 * Police: Will activity hunt the player and arrest them to end the game.

### Loot
The loot system will determine the players final score in a given game. As the player moves though the house they collect different items. Each item has values with harder to get items having more value. An items value can only be claimed once the player exists safely from a given house though any kind of exit point. If a player dies all loot that is currently being held will be lost and not added to the players score.

### Maps
Maps will consist of both a tiling system as well as placed entites. The tiling system will allow rooms to be drawn by placing square tiles in a grid formation.

## Technical Details

### Entites
Entities describe any game object that exists on the map. Entities can be either static or move around the map. The entity class has an optional controller member that will allow it to move. If no controller member for the entity is defined it will be considered static. Entites also can collide by defining hitboxes. If an entity does not define a hitbox then there will be no collision. Some tiles can be marked as walls in this case both a tile and an entity with no sprite are placed on the map.

#### Types of Entites
 * Doors. Doors connect two differnt rooms. See house system on more details on how doors work.
 * Enemies. Enemies can be placed anywhere in a room. Each time the room is loaded the enemies will be reset tto their original positions.

### Bots
 * As well as enemies bots are placed around the house. These bots are activated conditionally and can move from room to room.

## Why
I don't know. Because. To learn C++. To make a fun game. Stop asking me so many questions.

# Resources
 * https://gamefromscratch.com/sfml-c-tutorial-spritesheets-and-animation/

