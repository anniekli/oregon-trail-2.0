# Final Project: Oregon Trail 2.0

Author: Annie Li

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

---
## The Game ##
The beloved childhood computer game gets revamped with Oregon Trail 2.0. This
 time, you are a talented musician about to set off on a trip to visit the
  world's most famous music venues. Perform at places like Walt Disney
   Concert Hall, La Scala, and The Met!

![alt text](assets/krannert_checkpoint.png?raw=true)

   
## How To Play##
You start at Krannert Center, UIUC. Before you leave, you need to buy some items
from the store. To figure out how much of each item you should buy, each day
you consume 1 unit of food, 2 units of water, and 10 gallons of gas. If you
run out of food, you have to buy food on the road. This costs $7 per day. If
you run out of water, it costs $10 per day -- so it's better to buy these
at the store beforehand.

![alt text](assets/start_page.jpg?raw=true "Start page")

![alt text](assets/store_page.jpg?raw=true)
  
Don't worry if you find yourself low on money, because while traveling, you can
try to find a gig to play and earn money. However, you might not get a
gig every time, so be careful!

![alt text](assets/gig_page.jpg?raw=true)

     
While traveling, you need to make sure that you are practicing enough. You
need to have practiced a certain number of hours by the time you reach each
checkpoint. To practice, simply type in the name of the piece that is
being played. Every correct answer amounts to 5 hours of practicing. You
get 20 seconds to "practice" as many hours as possible.

![alt text](assets/practice_page.jpg?raw=true)

 
If you make it to the final checkpoint, you win! If you run out of gas, or
 run out of food or water and have no money left to
buy more on the road, or if you haven't practiced enough hours by the time
you reach the next checkpoint, you lose! This may seem tough, but that's
life for a musician on the road.

![alt text](assets/travel_page.jpg?raw=true)


Your final score is the sum of all of the items in your inventory, aside
from the number of hours you've practiced, which gets doubled. You also get
an extra 500 points if you make it to the end.

![alt text](assets/game_over_page.jpg?raw=true)

## Dependencies and External Libraries ##
- Cinder (https://libcinder.org/docs/guides/tour/hello_cinder_chapter1.html)
- Choreograph (https://github.com/sansumbrella/Choreograph).
- SqliteModernCpp library (https://www.sqlitetutorial.net/download-install-sqlite/)
- Cmake (https://cmake.org/install/)
- Catch2 (https://github.com/catchorg/Catch2)