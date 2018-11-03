// John Lauer
//HW5 Due: April 15, Sunday, at 11:59pm
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

ofstream out("data1.txt");

class card
{
public:
    int number;
    int suit;
    static int uniquenumber;
    card();
    void showcard();
    card * next;
};


class collection
{
public:
    card * start;
    int numberofcards;
    collection(int x);
    collection() { start = nullptr; numberofcards = 0; }
    void showcollection();
    void shuffle();
    card deal();
    void add(card a);
};
card::card()
{
    number = uniquenumber % 13;
    suit = (uniquenumber / 13);
    uniquenumber++;
    next = nullptr;
}

void card::showcard()
{
    
    switch (number)
    {
        case 0: out << "A"; break;  // Ace is low
        case 10: out << "J"; break;
        case 11: out << "Q"; break;
        case 12: out << "K"; break;
        default: out << (number + 1); break;
    }
    
    switch (suit) {
        case 0: out << "S "; break;
        case 1: out << "H "; break;
        case 2: out << "D "; break;
        case 3: out << "C "; break;
    }
}

collection::collection(int x)
{
    
    start = nullptr;
    
    numberofcards = 0;
    for (int i = 0; i<x; i++)
    {
        card temp;
        add(temp);
    }
}
void collection::showcollection()
{
    int i;
    card * temp;
    temp = start;
    for (i = 0; i<numberofcards; i++)
    {
        temp->showcard();
        temp = temp->next;
    }
    
}


void collection::add(card a)
{
    while(numberofcards != 0) {         //While there are still cards
    card * temp = start;                //Create a pointer for the top card
    start = &a;
    start->next = temp;
    numberofcards++;                    //Increase the number of cards because another has been added
    }
}

void collection::shuffle()
{
    /*
     Randomize the sequence of cards in the deck.
     You can use my shuffle
     */
    card *temp2, *temp3;
    temp2 = start;
    temp3 = temp2;
    int i, j, k;
    char c1;
    int num;
    for (i = numberofcards; i>1; i--) {
        j = rand() % i;
        for (k = 0; k <= j - 1; k++)
            temp3 = temp3->next;
        c1 = temp2->suit;
        num = temp2->number;
        temp2->suit = temp3->suit;
        temp2->number = temp3->number;
        temp3->suit = c1;
        temp3->number = num;
        temp2 = temp2->next;
        temp3 = temp2;
    }
    
    // Reorganize cards in array randomly
}
card collection::deal()
{
    card * temp = start;        //Set temp card equal to the beginning of the players deck
    numberofcards--;            //Reduce the quantity of the cards by one because you are putting the card on the table
    start = temp->next;        //Set the start to the next card because you removed the top card
    return ( * temp);           //Return the card that was just placed on the table face up
}



int card::uniquenumber = 0;

void deal_cards(int k, int d, collection &deck, collection *hand);
void battle(int k, collection *hand, collection *table);
void Enter_Num_players_Dealer(int &k_players, int &dealer);
void Show_Initial_Deck_Hands(int &k_players, int &dealer, collection &deck, collection * hand, collection * table);

int main() {
    
    collection *hand, *table;
    int num_players, dealer, i, winner = 0;
    srand(time(0));
    Enter_Num_players_Dealer(num_players, dealer);
    collection deck(52);
    hand = new collection[num_players];
    table = new collection[num_players];
    Show_Initial_Deck_Hands(num_players, dealer, deck, hand, table);
    battle(num_players, hand, table);
    return 0;
}
void Show_Initial_Deck_Hands(int &k_players, int &dealer, collection &deck, collection * hand, collection * table) {
    out << "\n\n************** initial deck of cards before shuffle ****\n\n";
    deck.showcollection();
    deck.shuffle(); // Shuffle cards in deck
    out << "\n\n****************** after shuffle **************\n\n";
    deck.showcollection();
    out << "\n\n****************** after cards are dealt **************\n\n";
    deal_cards(k_players, dealer, deck, hand);
    for (int i = 0; i< k_players; i++)
    {
        out << "\ncards for player " << i + 1 << "\n";
        hand[i].showcollection();
    }
    
}
void Enter_Num_players_Dealer(int &num_players, int &dealer) {
    
    do {
        cout << "Enter the number (2-10) of players ";
        cin >> num_players;
        if (num_players > 10 || num_players < 2)
            out << "Illegal player number. Enter again\n\n";
    } while (num_players >10 || num_players < 2);
    
    do {
        cout << "Enter initial dealer (1-k)";
        cin >> dealer;
        if (dealer < 1 || dealer > num_players)
            out << "Illegal dealer ID. Enter again\n\n";
    } while (dealer < 1 || dealer > num_players);
}


void battle(int k, collection *hand, collection *table) { //k is num_players
    int pwinners = k;                               //The number of potential winners (Players who still have over 5 cards)
    int winner;                                     //The number of the player who has over 5 cards while everyone else 0
    int battleWinner;                               //The number of the player who won each individual battle
    int tie;                                        //In case of a tie, this integer holds the value of the cards that are tied
    int tiePlayer;                                  //The number of the player who tied for the lowest (best) card during the battle
    int lowestCard = 12;                            //Keeps track of which player has the lowest (best) card during each battle
    while(pwinners > 1) {                           //While there is more than one potential winner, continue to battle
        for(int i = 1; i < k; i++){
            if(hand[i].numberofcards < 5) {         //If a player has less than 5 cards, reduce the number of potential winners by one because that player can no longer win
                pwinners--;
            }
            for(int i = 1; i < k; i++) {            //Loop through all of the players
                card a = hand[i].deal();            //Each player will place a card on the table
                a.showcard();
                table[i].add(a);
                if(lowestCard > a.number){     //Compare each card's value with one another and set the lowest value(best card) to lowest Card
                    lowestCard = a.number;
                    battleWinner = i;          //Assign the number of the player who won the battle to battleWinner
                    for(int i=1; i< k; i++){
                        hand[battleWinner].add(a); //The winner gets all of the cards that were on the table
                    }
                }
                if(lowestCard == a.number) {
                    tie = a.number;
                    tiePlayer = i;
                }
            }
            if(tie == lowestCard) {                                 //In case of a tie
                card battleWinnerCard = hand[battleWinner].deal();  //Have the first player who tied place another card on the table
                card tiePlayerCard = hand[tiePlayer].deal();        //Have the second player who tied place another card on the table
                battleWinnerCard.showcard();
                tiePlayerCard.showcard();
                if(battleWinnerCard.number < tiePlayerCard.number) {//Compare the newly placed cards
                    lowestCard = battleWinnerCard.number;
                } else {
                    lowestCard = tiePlayerCard.number;
                }
            }
            for(int i = 1; i < k; i++) {            //This section of the function removes players who have less than five cards from the "potential winners" count
                if(hand[i].numberofcards < 5) {         //If a player has less than 5 cards
                    while(hand[i].numberofcards != 0){  //Put cards back on the table
                        card a = hand[i].deal();
                        a.showcard();
                        table[i].add(a);
                    }
                    pwinners--;
                }
                while(pwinners == 1){
                for (int i = 1; i < k; i++) {           //Loop through all of the players
                    if(hand[i].numberofcards != 0) {    //The last player who still has cards is declared the winner
                        winner = i;                     //Assign the integer winner the number of the player
                    }
                }
                }
            }
        }
    }
    cout<< "Game Over!! The winner is player " << winner << endl;   //Output the number of the player who won the game
    return;                                                         //Return to the main function and then end the game
}

void deal_cards(int k, int d, collection &deck, collection *hand) {
    card * start = deck.start;                     //Start at the top of the deck
    int i = d+1;                                   //Start dealing to the person after you
    while(deck.numberofcards != 0) {               //Until there are no more cards in the deck
        start = deck.start;                        //Begin the loop by always setting the top card to the start(Once a card is delt, we need to make the new top card the start card)
        hand[i].add(deck.deal());                  //Deal the top card
        if(i==k){                                  //Once you reach the last player(k), set i to the first player so you keep dealing to the players
            i = 1;
        } else{                                    //If you arent at the last player, set I to the next player
            i++;
        }
    }
}
