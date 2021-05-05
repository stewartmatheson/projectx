# ProjectX

## Possible Names 

 * "Before The Sun Comes Up"
 * "The Blag"

## Overview
Rouge like where the player takes on the role of a archetypical burglar. A game involves the player moving from house to house stealing loot. Scores for the game are based on how much the player can steal in a given game. At the end of the game the player's score is reset and they must start again. If a player is good enough they will make it to the end of "Henderson St"(Working Name) and get a bonus added to their score. The player's game will end once they rob all the houses or get killed by the police. Players can also get killed by ghosts.

## Cast

 * Robber : Grabber Dan. A portly man with a scar on his face and a 5 oclock shadow. Could also smoke cigars.
 * Resident:  Mrs. Battersby an elderly lady in a night dress who lives at the house being robbed.
 * Various Ghosts
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

### Tile Atlas

### Room System
Game will feature a pool of predefined rooms. Houses will consist of interconnected rooms. All interconnected rooms will have furniture placed randomly in them. The furniture will act as containers. The player can then interact with the furniture by searching the furniture. This will cause the player to make noise however this is how the player will find their loot and power ups.

### Noise
The game will feature a noise system. Making noise will attract unwanted attention to the player and may get them caught.

### Power ups
A list of power ups the player can get

 * Night Vision Goggles
 * Sneakers... for sneaking. Helps the player make less noise.
 * Gloves allows for searching containers more quickly.

### AI
While moving though the house the player will have to contend with various computer controlled AI players. 

 * Ghosts: Stupid. Roam about.
 * Residents: Will walk in their house from room to room. Not activity looking for the player. Will call the police if they see the player. 
 * Police: Will activity hunt the player and arrest them to end the game.

### Loot
The loot system will determine the players final score in a given game.

## Why
I don't know. Because. To learn C++. To make a fun game. Stop asking me so many questions.

# Resources
 * https://gamefromscratch.com/sfml-c-tutorial-spritesheets-and-animation/

# Next Time
 * Render at 60fps locked and render on own thread
 * Refactor tick and update methods
