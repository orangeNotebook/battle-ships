# Assignment Description

Use an object-oriented design approach for the creation, development and testing of AdaShip (a REPL.IT C++ computer console version/adaptation of the classic paper-based Battleships game). You are expected to adopt an agile and iterated approach to decomposing, designing and developing your game; ideally with a test early and fail fast approach.

## How AdaShip Is Played
Essentially, AdaShip is a clone of the classic ‘Battleship’ game – as a default, AdaShip is a two-player, turn based game of sea warfare. You and an opponent each place a number of ships on your own board, and you then alternate turns "firing" torpedoes at each other’s ships. The game is won when one player has destroyed/sunk all of the other player’s ships.
### Setup:
By default, each player uses two 10x10 boards (a shipboard and a targetboard). Ship boards are used to initially position and hold a record of the location of your ships and any hits made by opponents. The target board is used to keep track of where you have fired (i.e., guessed) and the outcome; for example – hit or miss. Board locations are referenced using a single notation type coordinate system (‘A1’, ‘F4’, etc). The coordinate system must be designed to use alphabetic letters (A, B, ...) to represent columns and numbers (1, 2, ...) to represent rows.

When placing ships, each player must place all their ships on their shipboard; ships have different sizes and can be either placed horizontally or vertically; a player’s ships cannot be placed such that any of their ships are either partly or entirely outside their board’s boundaries, across one (or occupy the same space as) a
previously positioned ship. 

#### By default, there are five types of ships:
1. Carrier - Length 5
2. Battleship - Length 4
3. Destroyer - Length 3
4. Submarine - Length 3
5. Patrol Boat - Length 2

### A typical, two player game (player v computer)
In a typical two-player game, each player would set up his own shipboard. Since your default opponent for this assignment will be the computer, you should set up your own board first, and have the computer decide where to place its ships (legally of course).

### Typical game play
The game is played in turns, where each player ‘fires a torpedo’ (by calling out a board coordinate) and the opponent indicates whether the ‘torpedo’ resulted in a "hit" or "miss". A "hit" indicates that the called position corresponded to a valid ship coordinate, otherwise it is a "miss". Players record their called positions using their targetboard; a record of both “hits” and “misses” should be recorded.


### Winning
Turns are repeated until all of your opponent’s ships have been ‘sunk/destroyed’; players must indicate as part of the response to each hit whether an entire ship has been sunk or just a single hit; for example, if our Carrier is located at B2, B3, B4, B5 and B6 and each position has been hit we need to indicate that the opponent sunk our ship.

## Marking Scheme 
In addition to development, you are also required to provide a well-structured README document; details on the structure have been provided in the submission section.

### Pass level your game is expected to support:
#### 1. A run-time read, single file called ‘adaship_config.ini’ that defines the game’s configuration; your file should be setup to match the following structure:

```
Board,10x10
Boat,Carrier,5
Boat,Battleship,4
Boat,Destroyer,3
Boat,Submarine,3
Boat,Patrol Boat,2
```

#### 2. A usable, intuitive and highly efficient Set-Up interface in which a player can with minimal effort:

• Select from a game menu to a start a:

- One player v computer game
- Quit

• Select and place any of their non-placed or placed ships (as provided via the config file) at any valid position on their shipboard.

• Clearly indicate the current non-placed and placed ships.

• See their current shipboard.

• Be robust enough to prevent any invalid behaviours, prevent or correct any illegal placements and avoid system issues or errors related to user input.

• Allow any non-placed ships to be ‘auto-placed’.

• Auto-place all ships.

• Support a ‘quit’ game and ‘reset’ shipboard option.

• Support a ‘continue’ option if all ships have been placed and the user has confirmed they are happy with the current placements.

#### 3. A computer-based opponent than can automatically complete a valid setup process using a random strategy (i.e., place all their ships at valid but ,constantly differing positions on their own shipboard); essentially this should utilise the auto-place feature outlined above.

#### 4. A usable, intuitive and highly efficient Turn based process supported with a minimal user effort interface in which game turns are played:

• Player’s turn:

- Their own, current and up to date ship and targetboards are displayed as well aligned tables (rows and columns).
- Players are able to ‘fire’ a single torpedo at a valid location (i.e., not previously targeted and within the board boundary) using the single notation coordinate (e.g., F2, etc.); if the location is invalid the player is asked to re-try.
- Auto ‘fire’ option; this option targets and ‘fires’ at valid locations.
- Players are clearly notified of a ‘hit’ or ‘miss’ (or win) based on the outcome of their turn.
- Players are able to quit the game (if not already won).
- Players are required to ‘press a key’ to end their turn.

• Computer’s turn:

- Its own, current and up to date ship and target boards are displayed as well aligned tables (rows and columns).
- It uses its own up to date ‘targetboard’ to randomly ‘fire’ a torpedo at a valid location (i.e., not previously targeted and within the board boundary).
- A clear notification of a ‘hit’ or ‘miss’ (or win) based on the outcome is shown.
- A user based ‘press a key’ interaction is required to end the computer’s turn.

### Merit level (in addition to the pass) your game is expected to support:
#### 5. Improved customised game and configuration settings (based on changing the ‘adaship_config.ini’ file):

• Any valid size of board (valid ranges are: 5x5 to 80x80)

#### 6. An extended Set-Up interface in which a player can with minimal effort:

• Select from a game menu to a start a:
- One player v computer game
- Two player game; essentially replacing the computer with a second player
- One player v computer (salvo) game
- Two player game (salvo) game
- Quit

#### 7. Improved game play “salvo” variation:

The salvo implementation updates the basic game play by allowing the current ‘player’ (player or computer) to ‘fire’ one torpedo per their remaining ships. For example, if the ‘player’ has three ‘non-destroyed’ ships instead of a single valid coordinate (e.g., F2) they could enter F2 E2 G2 (one coordinate per ship) – once entered, details on any ‘hits’ and/or ‘misses’ are clearly provided, and all appropriate boards are updated to reflect this salvo.

### Distinction level (in addition to the merit) your game is expected to support:
#### 8. Improved customised game and configuration setting (based on changing the ‘adaship_config.ini’ file):

• Unlimited additional boats: each additional boat should follow the file’s existing structure; for the purpose of this assessment and as there is a logical and rational limit ‘unlimited’ simply means your solution’s design and logic technically supports any number of boats.

#### 9. An extended Set-Up interface in which a player can with minimal effort:

• Select from a game menu to a start a:
- One player v computer game
- Two player game; essentially replacing the computer with a second player
- One player v computer (salvo) game
- Two player game (salvo) game
- One player v computer (hidden mines) game
- Two player game (hidden mines) game
- Computer v computer (hidden mines)
- Quit

#### 10. Improved game play “hidden mines” variation:

The hidden mines implementation updates the basic game play with five randomly dropped mines. The hidden mines are essentially added to each ‘players’ shipboard and remain ‘hidden’ during the set-up phase (optionally they could be added on completion of each set-up). However, they should be clearly displayed during game turns as part of each ‘players’ shipboard.

If an opponent’s torpedo ‘hits’ a hidden mine that location and the eight immediately surrounding it ‘explode’. If any of the players ships directly intersect with the ‘explosion’ they are ‘hit’ as per normal play. Positions ‘outside’ the board can be ignored. 11: Improved ‘computer player’ targeting problem: Design and implement a separate, optimised search and/or targeting algorithm, it is likely that your solution has implemented a generally random or basic algorithm to ‘pick’ targets; research and implement a better than random solution to this problem.

## Submission
You are required to submit a single, complete and tested GitHub linked repo via Google Classroom by the appropriate submission date (see cover) – 
### Your repo is expected to demonstrate multiple commits and provide:

- A formatted well-structured and planned, academic and professional README.md; see Structuring and completing your Readme document (below for more information).

- A REPL.IT compatible and testable C++ project, i.e., your GitHub’s repository URL can be directly imported for review, execution and testing on the REPL platform (see issues likely to impact your grade below for more information).

### Structuring and completing your README document
The three titles below provide and outline the structure and subsections expected as part of your submission; in addition to previous notes or discussions, for more information on achieving higher grades in written work please review the AdaHelp document available via the Google Classroom. It is suggested that these sections are in order.

#### 1. Challenge Outline (academic standard: pass level detail: section required for pass)
>a. Summary and review of the problem, overall proposed solution.
b. UML style diagram illustrating initial overall solution (linked to 1a)
c. Initial working plan, overall approach, development strategy and approach to quality (linked to 1a, 1b).
d. Analysis and decomposition of the overall problem into key ‘epic’ style tasks (linked to 1b, 1c).
e. Initial object-oriented design ideas and plan of phased breakdown into smaller tasks (linked to 1d).

#### 2. Development (academic standard: merit level detail: section required for merit)
>a. Adoption and use of ‘good’ standards (linked to 1a, 1b, 1c).
b. Phase 1 development: tasks, code review and changes (linked to 1d,1e).
c. ..repeated for each development phase.
d. Phase n development: tasks, code review and changes (linked to 1d,1e).
e. Ensuring quality through testing and resolving bugs (linked to 1a, 1b, 2a, 2b..2c).
f. Reflection on key design challenges, innovations and how I solved them (with examples).

#### 3. Evaluation (academic standard: distinction level detail: section required for distinction)
>a. Analysis with embedded examples of key code refactoring, reuse, smells.
b. Implementation and effective use of ‘advanced’ programming principles (with examples).
c. Features showcase and embedded innovations (with examples) - opportunity to ‘highlight’ best bits.
d. Improved targeting algorithm – research, design, implementation and tested confirmation (with examples).
e. Reflective review, opportunities to improve and continued professional development.

### Issues likely to impact your grade:
• Commits made after the submission date and time.
• Incompatibility and/or issues with GitHub and Repl.IT importing
• Errors preventing compilation, execution, etc.
• Incomplete implementations.
• Missing evidence.
• Inconsistent and/or missing standards in coding and documentation.
• Poor refactoring - Code refactoring is the rewriting of code for clarity and efficiency rather than bug fixing; in essence, this is similar to writing or improving academic ‘paper’ drafts

## Appendix A.Expected programming Standards

### Adoption and use of good programming standards:
• Include good quality, clear, jargon free and up to date internal documentation / comments; adopt the philosophy of writing comments for non-programmers.
• Eliminate or minimise code duplication & any unnecessary redundancy.
• Strive for simplicity in logic and flow.
• Use a consistent naming convention for functions, variables, objects, etc to provide clear contextual value, improved comprehension and quick readability.
• Use appropriate and consistent indentation, logical grouping and spaced blocks within your codebases; adopt tabs or a set number of spaces (ideally tabs) for indenting.
• Use spaces consistently to separate operators and delimiters.
• Be consistent when aligning braces; use a vertically or slanted style.
• Avoid deep nested conditionals.
• Avoid single (long) lines of code containing multiple operations; consider ‘one line one instruction”.
• Keep variable lifetimes and scope as short and as small as possible.
• Avoid multipurpose functions and variables.
• Conserve system resources.
• Minimise forced type conversion, coercion or casting.
• Know and test your code: adopt a personal and rigorous testing strategy; don’t just see it if works - test and fix its limits.
• Test early and often, fail fast and resolve effectively.