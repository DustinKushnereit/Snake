Description and Important Information:

This game was made using Visual Studio as the IDE and Allegro 5 as the graphics library and game engine. In my version of "Snake", you have two different power ups, the purple power ups that cause your snake to grow by two and the yellow powers ups that cause your snake to grow by one. Both power ups have rotating sprites that change by rotating through a sprite spread sheet. The levels are generated by the game reading in each level from a text document prior to the game loop being called. In addition to this there is an event listener system in place that calls every event triggered into a queue or first in first out. This event listener system keeps the game from getting clogged up with function calls to one another within the game's update loop. The game also utilizes Dean Lawson's "Memory Allocation" library to keep track of memory leaks. This game was made March 2015.

 

Controls:

Arrow Keys

Space Bar to start new level

Escape to Exit