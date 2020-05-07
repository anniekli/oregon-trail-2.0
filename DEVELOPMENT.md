# Development

---
## Week 1 ##
- **4/21/2020** Created database and menu page
- **4/23/2020** Created Player class to hold player info, such as inventory
, name, and score
- **4/24/2020** Added motion of background using Choreograph library

## Week 2 ## 
- **4/27/2020** Start on logic for mini practice game
    - Created PracticeGame class to hold information for game
    - Added map containing path for audio files and name of pieces
- **4/28/2020** Finished logic for accepting user input in mini game and
 checking the answer
- **4/30/2020** Moved StartNewRound() and CheckAnswer() to PracticeGame class
 and created JSON file to represent checkpoints
    - [x] Add timer so each Practice Game is 1 minute long
    - [ ] Figure out how to print "Correct"/"Incorrect" message for longer
- **5/1/2020** Added Layout class and Checkpoint class so you can access the
 properties of each checkpoint(name, description, image, and distance)
    -[x] Figure out how to access JSON file correctly

## Week 3 ##
- **5/2/2020** Added tests for Layout class
- **5/3/2020** Added functionality for the store and gigs!
    - Allow user to select "Go to store" at start or when at a checkpoint
    - Also allow user to select "play a gig" when not at a checkpoint instead
     of "go to store" in order to have a random chance of earning money.
- **5/4/2020** Allow user to purchase items from store
    - Their purchase is reflected in the inventory
- **5/5/2020** Checkpoint is drawn automatically when reached and GameOver is
 drawn at the end of the game
    - Add player to leaderboard and show high scores and player's high scores
    - End game when gas, money, or hours practiced is too low
    - [x] Make animation smoother when traveling
- **5/6/2020** Finishing up the game
    - Limit number of gigs to 3 per day
    - Improve animation
    - Finish writing all tests
    
