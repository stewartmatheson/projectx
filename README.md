# Before The Sun Comes Up

## Overview
Rouge-like, where the player takes on the role of an archetypical burglar. A game involves the player moving from house to house stealing loot. Scores for the game are based on how much the player can steal in a given game. At the end of the game, the player's score is reset, and they must start again. If a player is good enough, they will make it to the end of "Henderson St"(Working Name) and get a bonus added to their score. The player's game will end once they rob all the houses or get killed by the police. Players can also get killed by ghosts. Once a player is killed, they must restart the game and lose all their items.

## Cast

 * Robber: Grabber Dan. A portly man with a scar on his face and a 5 o'clock shadow. Could also smoke cigars.
 * Resident: Mrs Battersby, an elderly lady in a nightdress who lives at the house being robbed.
 * Various Ghosts.
 * Police complete with their bobby hats.

## Graphics Treatment
ProjectX will be a pixel game. ProjectX will have a top-down view like "A Link to The Past" for SNES. Houses will range from American-style trailers to ornate mansions. The main player will wear a striped shirt and have a black mask. The resident of the house will always be the same old lady in her nightdress.

## Systems

### Overview
The following is a list that provides an overview of all the required systems for the game. See each system section for more information.

 * A tile Atlas for dealing with sprites and loading in animations.
 * A noise system where the player will have to remain quiet.
 * A room system that randomly generates new house layouts for each game. 
 * A powerup system where the player can collect several items allowing them to rob more loot. 
 * A. An AI system where ghosts and house residents attack the player. This will include police AI as well. See AI section
 * A loot system. This will control how much a player will score within a given game
 * A map editing system allowing for developers to design rooms while in the game

As the player moves around the game, they lose health. A player starts with three points of health. If a player arrives zero health, they die, and their score is zero as they could not escape with any loot.

### Tile Atlas

### House System
The game will feature predefined houses. Houses will consist of interconnected rooms with furniture placed randomly in them. The furniture will act as containers. The player can then interact with the furniture by searching the furniture. This will cause the player to make noise; however, they will find their loot and powerups. 

When moving from room to room, the viewport will scroll in much the same way that the legend of Zelda does. This will happen when a player comes in to contact with a door entity. See the maps section for more details on how entities work. Moving through doors will occur in three different phases. First, the player will come in contact with the door. At that point, the player entity controller will be swapped out with a door transition controller entity. This door transition controller entity will move the player through the door without any input from the player. Once the player has moved through the door, the screen viewport will be scrolled to the next room. At this point, the door transition controller will move the player out into the next room. At that point, the door transition controller will be removed, and the player will regain control.

### Noise
The game will feature a noise system. Making noise will attract unwanted attention to the player and may get them caught.

### Power-ups
A list of powerups the player can get

 * Night Vision Goggles
 * Sneakers... for sneaking. Helps the player make less noise. These will reduce the effectiveness of the hearing sensors of ghosts
 * Gloves allows for searching containers more quickly.
 * Weapons, which will allow the player to more efficiently fight both police and ghosts.
 * PK Flux: A special agent that will soothe the aggressiveness of ghosts

### AI
While moving through the house, the player will have to contend with various computer-controlled AI players. A director will be responsible for the following: 
 * Adding AI elements to the game.
 * Figuring out how much HP the AI elements have.
 * Calculating the current menace. How much the player is under.
 * Backing off menace when required.
 * Increasing menace when required

Pressure at any time in the game.  When the player is under a higher amount of "pressure", they will have less ability to steal loot; however, when the "pressure" is reduced, the player will have more scope and space to complete the game's actions.

#### AI Type: Ghosts
The first level adversary of the game that the player will face is the ghost. These phantasms represent the stock enemy of the player.
 * Ears. In this world, ghosts have ears. When a player is searching for items, this will make noise
 * Sight Cone. They will have limited vision in front of them.

Ghost Attributes:
 * Hitpoints: How many hit points a ghost has before it dies
 * Aggression: How aggressive the ghost is.

#### AI Type: Cops
Will activity hunt the player and arrest them to end the game. When one cop spots the player, he will alert the others via radio. These cops may start activity hunting the player depending on their aggressiveness and menace.

#### AI Type: Residents
Will walk in their house from room to room. Not activity looking for the player. Will call the police if they see the player.  This will then cause the police to spawn in the current map and start hunting the player.

#### Jobs
Jobs will happen with a tree. More advanced jobs will be added to the tree when game events happen so enemies will do new things to the player.
 * Patrolling. While in this mode, enemies will move around across their nav meshes with no patterns. 
 * Attacking: Enemy has its sensors activated and is currently trying to attack the player.
 * Swarming: Ghosts will look to group up against the player. This node will only be added when there is a low level of menace.

#### Menance
A menace value will be calculated at all times to tell the AI director how to build up the AI and what enemies to inject and what hitpoints and aggression the enemies have. Factors that will affect the "menace score" are:
 * Current enemy count on the map
 * Current Player Health
 * Player Powerups
During the game, the menace factor will modulate up and down. This modulation will be handled by a leaky bucket algorithm. The higher the player scores, the more the bucket will fill. The more full the bucket, the harder it will be to complete game goals. Menace floor value will increase as game time progresses, meaning that the game will get harder and harder the more further the player can proceed.

### Loot
The loot system will determine the players' final score in a given game. As the player moves through the house, they collect different items. Each item has values, with more challenging to get items having more value. An item's value can only be claimed once the player exists safely from a given house through any kind of exit point. If a player dies, all loot currently being held will be lost and not added to the player's score.

### Maps
Maps will consist of both a tiling system as well as placed entities. The tiling system will allow rooms to be drawn by putting square tiles in a grid formation.

## Technical Details

### Entites
Entities describe any game object that exists on the map. Entities can be either static or move around the map. The entity class has an optional controller member that will allow it to move. If no controller member for the entity is defined, it will be considered static. Entities also can collide by defining hitboxes. If an entity does not specify a hitbox, then there will be no collision. Some tiles can be marked as walls. In this case, both a tile and an entity with no sprite are placed on the map.

#### Types of Entities
 * Doors. Doors connect two different rooms. See house system for more details on how doors work.
 * Enemies. Enemies can be placed anywhere in a room. Each time the room is loaded, the enemies will be reset to their original positions.

### Bots
 * As well as enemies, bots are placed around the house. These bots are activated conditionally and can move from room to room.

## Why
I don't know... Because. To learn C++. To make a fun game. Stop asking me so many questions.

# Resources
 * https://gamefromscratch.com/sfml-c-tutorial-spritesheets-and-animation/


## Actions 
 * Loot an object
 * Attack
 * Walk though door

## Goals 
 * Get Loot
 * Get Power ups

## Rules
 * Player has several hit points. When all these hit points run out, the player dies.
 * Player's total loot is added up at the end of the game. This is the players' final score
 * 

## Objects

## Play Space
The play space is whatever house the player is in. The houses will be set out as a series of interconnected rooms.

## Players
