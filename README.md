# Blackjack Game

**Author**: Hasan Bukhari

## Description
This program simulates a blackjack game where the player competes against the dealer. The game generates random cards and suits for both the player and the dealer, calculates the values of the hands, and determines the winner based on the rules of blackjack.

The player starts with a default amount of money and can place bets on each round. The program continues until the player chooses to exit or runs out of money. Recursion is utilized to handle the player's decision to hit or stand.

## Features
* **Player vs Dealer**: The player competes against the dealer in blackjack.
* **Random Card Generator**: The game generates random cards and suits for both players.
* **Bet Placement**: The player can place a bet on each round, with an initial balance of $1000.
* **Card Value Calculation**: Cards 2-10 have their face value, face cards (Jack, Queen, King) are worth 10 points, and Aces are worth either 1 or 11 points based on the situation.
* **Bust and Win Conditions**: If a player's hand value exceeds 21, they bust and lose the bet. If the dealer busts, the player wins.
* **Hit or Stand**: The player can choose to "hit" (take another card) or "stand" (keep their current hand).
* **Dealer Rules**: The dealer automatically hits if their hand is below 17 and stands if it is 17 or higher.

## How to Play
1. Start the game by selecting "1" from the main menu to play blackjack, or select "2" to exit the game.
2. The player will be asked to place a bet, which must be between $1 and the current balance.
3. Two cards will be dealt to the player and the dealer. The dealer's second card will remain hidden until later.
4. The player chooses whether to hit or stand:
   * If they hit, they are dealt another card.
   * If they stand, the dealer plays according to the dealer rules.
5. If either the player or the dealer busts (exceeds 21), the game ends, and the winner is determined.
6. The game will continue until the player either runs out of money or chooses to exit.

## Controls
* **h** or **H** to hit (take another card)
* **s** or **S** to stand (keep current hand)
* Use the menu to start the game or exit the program.

## Rules
* The goal is to get as close to 21 points as possible without exceeding 21.
* Cards 2 through 10 are worth their face value, face cards (Jack, Queen, King) are worth 10 points, and Aces can be worth either 1 or 11 points.
* The dealer must hit if their hand value is below 17, and must stand if it's 17 or higher.
* If the player's hand exceeds 21, they bust and lose the bet. If the dealer busts, the player wins.

## Dependencies
* This program is written in C++ and requires a C++ compiler to run.
* The game supports Unicode and may require UTF-8 encoding.

## Implementation Details

### Global Variables
* `player_money`: The initial balance for the player ($1000).
* `bet`: The amount wagered in each round.
* `dealer_value`: The total card value for the dealer.
* `player_value`: The total card value for the player.
* `player_card_count`: Keeps track of the number of cards the player has drawn.
* `hole_card`, `hole_suit`: Used for the dealer's hidden card.

### Functions
* `menu()`: Displays the main menu and asks the player to select an option.
* `execute()`: Runs the game based on the selected option from the menu.
* `blackjack()`: Handles the flow of the blackjack game, including dealing cards and checking busts.
* `place_bet()`: Prompts the player to place a bet.
* `first_two_cards()`: Deals the first two cards to both the player and dealer.
* `card_ran_gen()`: Generates a random card based on the suit.
* `card_disp()`: Displays the card dealt, including the suit and card face.
* `calc_deck_value()`: Updates the player's or dealer's total hand value based on the card drawn.
* `check_bust()`: Checks if the player or dealer has busted.
* `ace()`: Determines the value of an Ace (either 1 or 11) to avoid busting.
* `hitorstand()`: Prompts the player to hit or stand.
* `disp_deck_value()`: Displays the total value of the player's and dealer's hands.

## Contact
For questions or feedback, please contact the author: Hasan Bukhari
