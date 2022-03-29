// cardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include<ctime>

using std::vector;
using std::string;

enum Suit { Heart, Clubs, Diamond, Spade };
enum Rank { Two, Three, Four, Five, Six, Seven, Jack, Queen, King, Ace };

struct Card {
    Rank rank;
    Suit suit;
    int num_suits = 4;
    int num_ranks = 10;
};

struct Deck {
    vector<Card> cards;
    string card_back;

};

void initialize(Deck&);
void print_deck(const Deck&);
void print_card(const Card&);
void shuffle(Deck&);
void deal_cards(Deck&, vector<Card>&, vector<Card>&, int);
void print_hand(const vector<Card>&);
void add_card(vector<Card>& table, vector<Card>& hand, int cards);
void play_game();

int main()
{
    play_game();
}


void initialize(Deck& deck) {

    Card card; // Uporabi se struct in nato for loop. Prvi za barve in drugi, da se v vsaki barvi inicializirajo karte.
    for (int suit = 0; suit < card.num_suits; suit++) {
        for (int rank = 0; rank < card.num_ranks; rank++) {
            card.suit = Suit(suit);
            card.rank = Rank(rank);
            deck.cards.push_back(card);
        }
    }

}

// Funkcija, da izpisemo karte
void print_deck(const Deck& deck) {
    for (Card c : deck.cards) {
        print_card(c);
    }
}

void print_card(const Card& card) {
    //Karte

    if (card.rank == 0) {
        std::cout << "Two of ";
    }
    else if (card.rank == 1)
    {
        std::cout << "Three of ";
    }
    else if (card.rank == 2)
    {
        std::cout << "Four of ";
    }
    else if (card.rank == 3)
    {
        std::cout << "Five of ";
    }
    else if (card.rank == 4)
    {
        std::cout << "Six of ";
    }
    else if (card.rank == 5)
    {
        std::cout << "Seven of ";
    }
    else if (card.rank == 6)
    {
        std::cout << "Jack of ";
    }
    else if (card.rank == 7)
    {
        std::cout << "Queen of ";
    }
    else if (card.rank == 8)
    {
        std::cout << "King of ";
    }
    else if (card.rank == 9)
    {
        std::cout << "Ace of ";
    }

    // Barve kart
    if (card.suit == 0) {
        std::cout << "Hearts" << std::endl;
    }
    else if (card.suit == 1) {
        std::cout << "Clubs" << std::endl;
    }
    else if (card.suit == 2) {
        std::cout << "Diamonds" << std::endl;
    }
    else if (card.suit == 3) {
        std::cout << "Spades" << std::endl;
    }
    //    std::cout << "Rank = " << card.rank << "  " << "Suit = " << card.suit << std::endl;

}

//Funkcija da premesamo in dobimo nakljucne karte
void shuffle(Deck& deck) {
    Deck shuffled;
    while (!deck.cards.empty()) {
        srand(time(0));
        size_t rand_index = rand() % deck.cards.size();
        shuffled.cards.push_back(deck.cards[rand_index]);
        deck.cards.erase(deck.cards.begin() + rand_index);
    }
    deck = shuffled;
}

//Funkcija da podelimo igralcema karte
void deal_cards(Deck& deck, vector<Card>& hand_1, vector<Card>& hand_2, int num_cards) {
    for (int card = 0; card < num_cards; card++) {
        hand_1.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
        hand_2.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
    }
}

void print_hand(const vector<Card>& hand) {
    for (Card c : hand) {
        print_card(c);
    }
}

// Dodamo karte na mizo iz roke
void add_card(vector<Card>& table, vector<Card>& hand, int cards) {

    for (int i = 0; i < cards; i++) {
        table.push_back(hand[0]);
        hand.erase(hand.begin());
    }


}

void play_game() {

    Deck my_deck;

    initialize(my_deck);
    shuffle(my_deck);

    vector<Card> player_1_hand;
    vector<Card> player_2_hand;
    deal_cards(my_deck, player_1_hand, player_2_hand, 20);
    std::cout << "Hand of Player 1: \n\n";
    print_hand(player_1_hand);
    std::cout << "\n\n";
    std::cout << "Hand of Player 2: \n\n";
    print_hand(player_2_hand);
    std::cout << "\n";
    vector<Card> table_player_1;
    vector<Card> table_player_2;
    int round_count = 0;

    while ((player_1_hand.size() > 0 && player_2_hand.size() > 0) && round_count < 10000) {

        table_player_1.clear();
        table_player_2.clear();
        table_player_1.push_back(player_1_hand[0]);
        table_player_2.push_back(player_2_hand[0]);
        std::cout << "Player 1 has: \n";
        print_hand(table_player_1);
        std::cout << "\n";
        std::cout << "Player 2 has: \n";
        print_hand(table_player_2);
        std::cout << "\n";
        player_1_hand.erase(player_1_hand.begin());
        player_2_hand.erase(player_2_hand.begin());


        if (table_player_1[0].rank > table_player_2[0].rank) {
            std::cout << "Player 1 have a bigger card and wins this round!\n\n";
            player_1_hand.push_back(table_player_1[0]);
            player_1_hand.push_back(table_player_2[0]);
            table_player_1.erase(table_player_1.begin());
            table_player_2.erase(table_player_2.begin());
        }
        else if (table_player_1[0].rank < table_player_2[0].rank) {
            std::cout << "Player 2 have a bigger card and wins this round!\n\n";
            player_2_hand.push_back(table_player_1[0]);
            player_2_hand.push_back(table_player_2[0]);
            table_player_1.erase(table_player_1.begin());
            table_player_2.erase(table_player_2.begin());
        }
        else {
            std::cout << "Its a draw! Each player must draw four more cards on the table!\n\n";

            do {
                if (player_1_hand.size() < 4) {
                    player_1_hand.clear();
                    break;
                }
                else if (player_2_hand.size() < 4) {
                    player_2_hand.clear();
                    break;
                }
                else {

                    // razdelijo se vsakemu igralcu 4 karte
                    add_card(table_player_1, player_1_hand, 4);
                    add_card(table_player_2, player_2_hand, 4);

                    std::cout << "Player 1 have: \n\n";
                    print_hand(table_player_1);
                    std::cout << "\n\n";
                    std::cout << "Player 2 have: \n\n";
                    print_hand(table_player_2);

                    if (table_player_1.back().rank > table_player_2.back().rank) {
                        std::cout << "\nPlayer 1 have a bigger last card and wins this round!\n\n";
                        for (int i = 0; i < table_player_1.size(); i++) {
                            player_1_hand.push_back(table_player_1[i]);
                        }
                        for (int j = 0; j < table_player_2.size(); j++) {
                            player_1_hand.push_back(table_player_2[j]);
                        }


                    }
                    else if (table_player_1.back().rank < table_player_2.back().rank) {
                        std::cout << "\nPlayer 2 have a bigger last card and wins this round!\n";
                        for (int i = 0; i < table_player_1.size(); i++) {
                            player_2_hand.push_back(table_player_1[i]);
                        }
                        for (int j = 0; j < table_player_2.size(); j++) {
                            player_2_hand.push_back(table_player_2[j]);
                        }

                    }
                    else {
                        std::cout << "\nPlayer 1 hand: \n";
                        print_hand(table_player_1);
                        std::cout << "\n";
                        std::cout << "\nPlayer 2 hand: \n";
                        print_hand(table_player_2);
                        std::cout << "\nIts a draw! Each player must draw four more cards!\n\n";

                    }
                }

            } while (table_player_1.back().rank == table_player_2.back().rank);
            // loop se ponavlja dokler imata igralca iste karte

        }

        round_count++;

    }
    if (player_1_hand.size() == 0) {
        std::cout << "\nPlayer 1 is out of cards! Player 2 is a winner!\n";
    }
    else if (player_2_hand.size() == 0) {
        std::cout << "\nPlayer 2 is out of cards! Player 1 is a winner!\n";

    }
    else {
        std::cout << "It's a draw, we have no winner!";
    }
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
