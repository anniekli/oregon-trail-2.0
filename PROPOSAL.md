# Oregon Trail 2.0

Author: Annie Li

---

# Project Description
I want to create a game similar to Oregon Trail, where most of the game is
just travelling, but every so often a random event happens that affects the
user, and the user must keep track of their inventory. My game would be
music themed, so the player is travelling to different music venues. For
example, some of the venues might be Carnegie Hall, the Met, La Scala, the
Sydney Opera House, the Royal Albert Hall, the Royal Opera House, etc.

## Motivation
I am a musician myself, and I'm going to be doing a dual degree in music
performance starting in the fall, so I'm excited to be doing a music-themed
game. Obviously, a lot of the parts of the game won't be incredibly realistic,
but I'll be taking a few creative liberties. I also just really like the game
Oregon Trail, so it'll be fun to be able to put my own twist on it.

## Library
One type of library I'll use is an animation library. I will be using
Cinder's Choreograph library(https://github.com/sansumbrella/Choreograph), which
is a simple animation library. My animations don't need to be incredibly
detailed, so something like Choreograph will work fine.

## Weekly Plan
### Week 1
For week 1, I will work on the basics of the game, which would include
setting up the GUI and allowing the user to manipulate their player in the
same way the original Oregon Trail does--ex: pressing the space bar pulls up
a menu of options for the player. I'll also create a database that holds the
leaderboard, similar to the snake game. I'll work on adding logic for keeping
track of the player's "stats"(i.e. practice time, amount of gas in the car,
amount of money, etc.). Finally, I'll add the library to my game and show a
basic example of its usage; for example, drawing a car with a moving background
so it looks like the user is driving along a road.

### Week 2
For week 2, I will start implementing the "mini" game
throughout the main game--this is analogous to "hunting" in Oregon Trail,
except mine will obviously be music based. I will also add in various
checkpoints in the game representing the user reaching a certain music
destination. These various checkpoints will be represented by either a json
file or a map, which will map the name of the destination to the piece to be
played once that destination is reached, along with an image and any other
necessary information(maybe a description of the venue and some other choices
for the user).

### Week 3
For week 3, I will focus on the details of the animation and making it smoother.
. I'll also add the background music and any other sound
effects that might play at various checkpoints. I will also add the player's
 stats at the bottom of the screen while they are traveling, and create the
  "start game" page.

### Extension
If I finish the project early, I could add in more variations of the "mini games", or make the animation
 more detailed. I might also try implementing the library verovio
 (https://github.com/rism-ch/verovio), which allows for music notation.