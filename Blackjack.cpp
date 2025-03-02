/*
Program: Blackjack Game
Author: Hasan Bukhari
Description: This program simulates a blackjack game where the player competes against the dealer.
             The game generates random cards and suits for both the player and the dealer,
             calculates the values of the hands, and determines the winner based on the rules of blackjack.
             The player starts with a default amount of money and can place bets on each round.
             The program continues until the player chooses to exit or runs out of money.
             Recursion is utilized on line 268 to handle the player's decision to hit or stand.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::setw;
using std::setprecision;
using std::fixed;
using std::random_device;
using std::uniform_int_distribution;
using std::to_string;
using std::vector;
using std::wcout;
using std::setlocale;

// Function prototypes
int menu();
int blackjack();
void execute();
void first_two_cards();
void exit_game();
int card_ran_gen(int suit);
int suit_ran_gen();
void check_bust();
void calc_deck_value(int card, bool isPlayer);
string card_classify(int card);
string suit_classify(int suit);
void card_disp(int suit, int card, int card_num, bool isPlayer);
int ace(int player_value);
int place_bet();
void hitorstand();
void hole_play(int hole_suit, int hole_card);
void dealers_play();
void player_hit();
void disp_deck_value(int player_value, int dealer_value);

// Global variables
int dealer_value = 0;
int player_value = 0;
int player_card_count = 3;
int bet = 0;
int player_money = 1000; // Player starts with $1000
int hole_card = 0;
int hole_suit = 0;
vector<int> hearts   = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
vector<int> spades   = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
vector<int> clubs    = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
vector<int> diamonds = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

// Main function
int main()
{
    // Accomodate unicode
    #ifdef _WIN32
        system("chcp 65001"); // Change Windows console code page to UTF-8
    #endif
    setlocale(LC_ALL, "en_US.UTF-8");  // Set the locale for UTF-8

    execute(); // Run the game menu
    return 0;
}

// Run the game based on menu selection
void execute()
{
    int opt = menu();
    while (opt != 1 && opt != 2)
    {
        cout << "Invalid Option! Enter option: " << endl;
        opt = 2; //FORCE EXIT
        cin >> opt;
    }
    while (opt == 1)
    {
        // Check if the player has money before printing rules and playing another round,
        if (player_money <= 0)
        {
            cout << "You have $" << player_money << endl;
            cout << "Well, that didn’t go as planned—you've lost all your money! Looks like Lady Luck's off duty. " << endl;
            cout << "Maybe it's time to leave the table... or grab a fresh bankroll and give it another whirl?" << endl;
            break;
        }

        cout << "Rules of Blackjack: \n";
        cout << "1. You and the dealer are dealt two cards each. The goal is to get as close as possible to 21 without going over.\n";
        cout << "2. Cards 2 through 10 are worth their face value; face cards (Jack, Queen, King) are worth 10 points; and Aces can be worth 1 or 11 points.\n";
        cout << "3. After receiving your cards, choose to 'hit' (get another card) or 'stand' (keep your current hand).\n";
        cout << "4. The dealer must hit if their hand is below 17 and stand if it's 17 or higher.\n";
        cout << "5. If you bust (go over 21), you lose your bet. If the dealer busts, you win. If neither busts, the hand closest to 21 wins.\n\n";

        int is_active = blackjack();
        if (is_active == -1) // there was an error
        {
            break; // exit game
        }

        if (player_money > 0)
        {
            cout << "Enter 1 to play another round: " << endl;
            cin >> opt;
        }
    }
    // exit_game();
    cout << "Thanks for playing!\n" << endl;
}

// Display menu and return choice
int menu()
{
    int opt;
    cout << "\nWelcome to Hasan's C++ Game Dojo \n" << endl;
    cout << "  Main Menu  " << endl;
    cout << "============" << endl;
    cout << "1. Blackjack" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter option:" << endl;
    cin >> opt;
    cout << endl;
    return opt;
}

// Start Blackjack
int blackjack()
{
    srand(time(0));

    dealer_value = 0;
    player_value = 0;
    player_card_count = 3;

    bet = place_bet();
    if (bet == -1 || bet > player_money) // If place_bet returned -1 (an error): exit program
    {
        exit_game();
        return -1; // return up that there was an error
    }

    // Step 1
    first_two_cards();
    // Check bust now only if totals exceed 21 (not when equal to 21)
    check_bust();
    disp_deck_value(player_value, dealer_value);

    // Step 2
    hitorstand();
    return 0; // no problems
}

// Exit game
void exit_game()
{
    cout << "\nExiting Program" << endl;
}

// Place bet and return bet amount
int place_bet()
{
    {
        int bet;
        cout << "You have $" << player_money << endl;
        cout << "Enter your bet: " << endl;
        cin >> bet;
        cout << endl;

        if ((bet < 1) || (bet > player_money))
        {
            cout << "Invalid bet. Exiting game." << endl;
            return -1; // THERE WERE PROBLEMS
        }
        return bet;
    }
}

// Deal two cards to player
void first_two_cards()
{
    // Deal two cards to the player
    for (int i = 1; i <= 2; i++)
    {
        int suit = suit_ran_gen();
        int card = card_ran_gen(suit);
        card_disp(suit, card, i, true);
        calc_deck_value(card, true);
    }

    // Deal two cards to dealer
    int upcard_suit = suit_ran_gen();
    int upcard = card_ran_gen(upcard_suit);  // Dealer's first card (visible)
    card_disp(upcard_suit, upcard, 1, false);
    calc_deck_value(upcard, false);  // Add only upcard value

    hole_suit = suit_ran_gen();  // Dealer's second card (hidden)
    hole_card = card_ran_gen(hole_suit);
}

// Generate a random card (2-14)
int card_ran_gen(int suit)
{
    vector<int> deck;

    switch (suit)
    {
    case 1: deck = spades; break;
    case 2: deck = hearts; break;
    case 3: deck = clubs; break;
    case 4: deck = diamonds; break;
    }

    if (deck.empty())
        return -1;  // Return -1 if the deck is empty

    // Generate a random index within the range of the deck size
    int random_index = rand() % deck.size();

    // Get the selected card
    int selected_card = deck[random_index];

    // Remove the selected card from the deck
    deck.erase(deck.begin() + random_index);

    // Return the selected card
    return selected_card;
}

// Generate a random suit (1-4)
int suit_ran_gen()
{
    random_device rds;
    uniform_int_distribution<int> randSuit(1, 4);
    return randSuit(rds);
}

// Display player card
void card_disp(int suit, int card, int i, bool isPlayer)
{
    string suitName = suit_classify(suit);
    string cardFace = card_classify(card);

    if (isPlayer)
    {
        cout << "Your Card " << i << ": " << cardFace << " of " << suitName << endl;
        cout << "***********" << endl;
        cout << "*   " << setw(2) << cardFace << "    *" << endl;
        cout << "*         *" << endl;
        cout << "*    " << suitName << "    *" << endl;
        cout << "***********" << endl;
    }
    else
    {
        if (i < 2)
        {
            cout << "\nDealer Upcard: " << cardFace << " of " << suitName << endl;
            cout << "***********" << endl;
            cout << "*   " << setw(2) << cardFace << "    *" << endl;
            cout << "*         *" << endl;
            cout << "*    " << suitName << "    *" << endl;
            cout << "***********" << endl;

            cout << endl;
            cout << "Dealer Hole Card: ~ Hidden " << endl;  // Do not reveal hole card yet
            cout << "***********" << endl;
            cout << "*         *" << endl;
            cout << "*    $    *" << endl;
            cout << "*         *" << endl;
            cout << "***********" << endl;
        }
        else if (i == 3)
        {
            cout << "\nDealer Hole Card: " << cardFace << " of " << suitName << endl;
            cout << "***********" << endl;
            cout << "*   " << setw(2) << cardFace << "    *" << endl;
            cout << "*         *" << endl;
            cout << "*    " << suitName << "    *" << endl;
            cout << "***********" << endl;
        }
        else if (i > 3)
        {
            cout << "\nDealer New Card: " << cardFace << " of " << suitName << endl;
            cout << "***********" << endl;
            cout << "*   " << setw(2) << cardFace << "    *" << endl;
            cout << "*         *" << endl;
            cout << "*    " << suitName << "    *" << endl;
            cout << "***********" << endl;
        }
    }
}

// Get suit name
string suit_classify(int suit)
{
    switch (suit)
    {
    case 1: return "\u2660";
    case 2: return "\u2665";
    case 3: return "\u2666";
    case 4: return "\u2663";
    default: return "";
    }
}

// Get card face and update deck value
string card_classify(int card)
{
    switch (card)
    {
    case 11: return "J";
    case 12: return "Q";
    case 13: return "K";
    case 14: return "A";
    default: return to_string(card);
    }
}

void disp_deck_value(int player_value, int dealer_value)
{
    cout << "\nPlayer deck value: " << player_value << endl;
    cout << "Dealer deck value: " << dealer_value << endl;
}

// Check bust = now only if totals exceed 21 (since 21 is a winning total)
void check_bust()
{
    if (player_value > 21)
    {
        cout << "\nPlayer Bust! You lose!" << endl;
        player_money -= bet;
    }
    else if (dealer_value > 21)
    {
        cout << "\nDealer Bust! You win!" << endl;
        player_money += bet;
    }
}

// Update deck value based on card drawn
void calc_deck_value(int card, bool isPlayer)
{
    if (isPlayer)
    {
        if (card == 14)
            player_value += ace(player_value);
        else if (card > 10)
            player_value += 10;
        else
            player_value += card;
    }
    else
    {
        if (card == 14)
            dealer_value += ace(dealer_value);
        else if (card > 10)
            dealer_value += 10;
        else
            dealer_value += card;
    }
}

// Handle Ace value = returns 11 if it doesn?t bust the hand; otherwise, returns 1
int ace(int player_value)
{
    if ((player_value + 11) > 21)
        return 1;
    else
        return 11;
}

void hitorstand()
{
    char choice;
    // Use a loop to ensure valid input
    cout << "\nWould you like to hit (h) or stand (s)?" << endl;
    cin >> choice;
    while (choice != 'h' && choice != 'H' && choice != 's' && choice != 'S')
    {
        cout << "Invalid input. Please enter 'h' or 's': " << endl;
        cin >> choice;
    }

    if (choice == 'h' || choice == 'H')
    {
        // Hit
        if (player_value <= 21)
        {
            player_hit();
            disp_deck_value(player_value, dealer_value);

            if (player_value > 21)
            {
                check_bust();
            }
            // Auto-stand if player reaches 21.
            else if (player_value == 21)
            {
                cout << "You've reached 21! Standing automatically." << endl;
                if (player_card_count == 3)
                    hole_play(hole_suit, hole_card);
                else
                    dealers_play();
            }
            else
            {
                if (player_card_count == 3)
                {
                    hole_play(hole_suit, hole_card);
                }
                else
                    dealers_play();
            }
        }
        else if (player_value > 21)
        {
            check_bust();
        }
    }
    else if (choice == 's' || choice == 'S')
    {
        // Stand
        if (dealer_value >= 17)
        {
            if (player_value == dealer_value)
            {
                disp_deck_value(player_value, dealer_value);
                cout << "\nTie! Game ends" << endl;
            }
            else if (player_value > dealer_value)
            {
                disp_deck_value(player_value, dealer_value);
                cout << "\nPlayer has a higher score! You Win!" << endl;
                player_money += bet;
            }
            else if (player_value < dealer_value)
            {
                disp_deck_value(player_value, dealer_value);
                cout << "\nDealer has a higher score! You lose!" << endl;
                player_money -= bet;

            }
            return;
        }
        dealers_play();
    }
}

void player_hit()
{
    cout << endl;
    int suit = suit_ran_gen();
    int card = card_ran_gen(suit);
    card_disp(suit, card, player_card_count, true);
    calc_deck_value(card, true);
}

void hole_play(int hole_suit, int hole_card)
{
    card_disp(hole_suit, hole_card, player_card_count, false);
    calc_deck_value(hole_card, false);
    disp_deck_value(player_value, dealer_value);
    check_bust();
    player_card_count += 1;
    hitorstand(); // Recursion loop
}

void dealers_play()
{
    if (dealer_value < 17)
    {
        int suit = suit_ran_gen();
        int card = card_ran_gen(suit);
        card_disp(suit, card, player_card_count, false);
        calc_deck_value(card, false);
        disp_deck_value(player_value, dealer_value);
    }
    player_card_count += 1;
    if (dealer_value <= 21)
        hitorstand(); // Recursion loop
    else
        check_bust();
}
