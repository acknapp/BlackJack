//============================================================================
// Name        : BlackJack.cpp
// Author      : Andrew Knapp
// Version     : 1.0
// Copyright   : GPL
// Description : BlackJack game port to C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

void intro ();
bool playAgain();
bool decide(char ans);
int bet (int money);
string deck[52]= {"AC","2C","3C","4C","5C","6C","7C","8C","9C","0C","JC","QC",
		"KC","AD","2D","3D","4D","5D","6D","7D","8D","9D","0D","JD","QD","KD","AS","2S","3S","4S","5S",
		"6S","7S","8S","9S","0S","JS","QS","KS","AH","2H","3H","4H","5H","6H","7H","8H","9H","0H","JH","QH","KH"};
string drawCard(string deck[], vector<string> hand, vector<string> dealer);
string determineCardType(string card);
string determineSuiteType(string card);
bool aceCheck(vector<string> card);
int determineCardValue(string card, vector<string> hand);



int main(){
	int money = 100;
	bool play = true;
	int playerTotal;
	int dealerTotal;
	vector<string> playerHand;
	vector<string> dealerHand;
	intro();

	while (money > 0 && play == true){
		int roundBet = bet(money);

		//Initial deal.
		string playerCard1 = drawCard(deck, playerHand, dealerHand);
		playerTotal = determineCardValue(playerCard1, playerHand);
		playerHand.push_back(playerCard1);
		cout << determineCardType(playerCard1) << " of " << determineSuiteType(playerCard1) << endl;
		string playerCard2 = drawCard(deck, playerHand, dealerHand);
		playerTotal += determineCardValue(playerCard2, playerHand);
		playerHand.push_back(playerCard2);
		cout << determineCardType(playerCard2) << " of " << determineSuiteType(playerCard2) << endl;
		string dealerCard1 = drawCard(deck, playerHand, dealerHand);
		dealerHand.push_back(dealerCard1);
		dealerTotal = determineCardValue(dealerCard1, dealerHand);
		cout << determineCardType(dealerCard1) << " of " << determineSuiteType(dealerCard1) << endl;
		string dealerCard2 = drawCard(deck, playerHand, dealerHand);

		//Decide to hit.
		cout << "Dealer showing: " << dealerTotal << endl;
		char hit;
		do{
			cout << "You have: " << playerTotal << endl;
			cout << "Do you want to hit (y/n)?" << endl;
			cin >> hit;
			string playerCard = drawCard(deck, playerHand, dealerHand);
			playerTotal += determineCardValue(playerCard, playerHand);
			playerHand.push_back(playerCard);
			cout << determineCardType(playerCard) << " of " << determineSuiteType(playerCard) << endl;

		} while (decide(hit) && playerTotal <= 21);

		//Dealer's play
		cout << "Dealer's 2nd card: " <<
				determineCardType(dealerCard2) << " of " << determineSuiteType(dealerCard2) << endl;
		dealerHand.push_back(dealerCard2);
		dealerTotal += determineCardValue(dealerCard2, dealerHand);
		while(playerTotal < 21 && dealerTotal <= 17){
			string dealerCard = drawCard(deck, playerHand, dealerHand);
			cout << determineCardType(dealerCard) << " of " << determineSuiteType(dealerCard) << endl;
			dealerHand.push_back(dealerCard);
			dealerTotal += determineCardValue(dealerCard, dealerHand);
		}

		//Check who won -- finish this part
		cout << "You have: " << playerTotal << endl;
		cout << "Dealer has: " << dealerTotal << endl;
		play = playAgain();
	}
	cout << "You are no longer playing"; //debug

	return 0;
}

// finish this part ***
int checkWin(int playerTotal, int dealerTotal, int bet){
	if(playerTotal == dealerTotal){
		cout << "Push." << endl;
		return bet;
	} else if(playerTotal == 21){
		cout << "You got BlackJack!" << endl;
		cout << "You win!" << endl;
		return bet * 2;
	} else if(dealerTotal == 21){
		cout << "Dealer has BlackJack." << endl;
		cout << "House wins." << endl;
		return bet * -1;
	} else if(playerTotal > dealerTotal){
		cout << "You win!";
		return bet * 2;
	} else {
		cout << "House wins." << endl;
		return bet * -1;
	}
}

bool aceCheck(vector<string> hand){
	int size = hand.size();
	for(int i = 0; i < size; i++){
		string card = hand[i];
		return card[0] == 'A';
	}
	return false;
}

int determineCardValue(string card, vector<string> hand){
	switch(card[0]){
		case '0':
			return 10;
		case 'K':
			return 10;
		case 'Q':
			return 10;
		case 'J':
			return 10;
		case 'A':
			if(aceCheck(hand)){
				return 1;
			} else {
				return 11;
			}
		default:
			return card[0];
	}
}

string determineCardType(string card){
	string type;
	switch(card[0]){
		case 'A':
			type = "Ace";
			return type;
		case 'K':
			type = "King";
			return type;
		case 'Q':
			type = "Queen";
			return type;
		case 'J':
			type = "Jack";
			return type;
		case '0':
			type = "10";
			return type;
		default:
			type = card[0];
			return type;
	}
}

string determineSuiteType(string card){
	string suite;
	switch(card[1]){
		case 'H':
			suite = "Hearts";
			return suite;
		case 'D':
			suite = "Diamonds";
			return suite;
		case 'S':
			suite = "Spades";
			return suite;
		case 'C':
			suite = "Clubs";
			return suite;
		default:
			return "Suite undetermined.";
	}
}

void intro(){
	cout << "Welcome to BlackJack!" << endl;
}

bool decide(char ans){
	while (ans != 'y' && ans != 'n'){
		cout << "You must answer with a 'y' or 'n'" << endl;
		cout << "Would you like to play again (y/n)?" << endl;
		cin >> ans;
	}
	if(ans == 'y'){
		return true;
	} else {
		return false;
	}
}

bool playAgain(){
	cout << "Would you like to play again (y/n)?" << endl;
	char ans;
	cin >> ans;
	return decide(ans);
}

// may need to re-do ***
int bet(int money){
	if (money <= 0){
		cout << "Sorry you are out of money." << endl;
		return 0;
	}
	int bet;
	cout << "You have: $" << money << endl;
	while (bet < 10 || bet > money){
		cout << "How much would you like to bet?" << endl;
		cin >> bet;
		if (bet < 10){
			cout << "Bet must be greater than $10" << endl;
		}
		if (bet > money){
			cout << "You do not have enough money for that bet." << endl;

		}
		cout << endl;
	}
	money = money - bet;
	return money;
}

bool checkDuplicates(string card, vector<string> hand){
	int size = hand.size();
	for (int i = 0; i < size; i++){
		return card == hand[i];
	}
	return false;
}

string drawCard(string deck[], vector<string> hand, vector<string> dealer){
    int r = rand() % 52;
    string card;
    if((checkDuplicates(card, hand) || checkDuplicates(card, dealer)) && r != 52){
    	card = deck[r + 1];
    } else if ((checkDuplicates(card, hand) || checkDuplicates(card, dealer)) && r == 52){
    	int j = 0;
    	while(checkDuplicates(card, hand) || checkDuplicates(card, dealer)){
    		card = deck[j];
    		j++;
    	}
    } else {
    	card = deck[r];
    }
    return card;
}
