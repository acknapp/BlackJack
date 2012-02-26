//============================================================================
// Name        : BlackJack.cpp
// Author      : Andrew Knapp
// Version     : 1.0
// Copyright   : GPL
// Description : BlackJack game port from Java in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

void intro ();
bool playAgain();
int bet (int money);
string deck[52]= {"AC","2C","3C","4C","5C","6C","7C","8C","9C","0C","JC","QC",
		"KC","AD","2D","3D","4D","5D","6D","7D","8D","9D","0D","JD","QD","KD","AS","2S","3S","4S","5S",
		"6S","7S","8S","9S","0S","JS","QS","KS","AH","2H","3H","4H","5H","6H","7H","8H","9H","0H","JH","QH","KH"};
string drawCard(string deck[], vector<string> hand);

int main(){
	int money = 100;
	bool play = true;
	vector<string> playerHand;
	vector<string> dealerHand;
	intro();

	while (money > 0 && play == true){
		money = bet(money);
		cout << money << endl;
		string playerCard1 = drawCard(deck, playerHand);

		play = playAgain();
	}
	cout << "You are no longer playing"; //debug

	return 0;
}

void intro(){
	cout << "Welcome to BlackJack!" << endl;
}

bool playAgain(){
	cout << "Would you like to play again (y/n)?" << endl;
	char ans;
	cin >> ans;
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
	for (int i = 0; i < hand.size(); i++){
		return card == hand[i];
	}
	return false;
}

string drawCard(string deck[], vector<string> hand){
    int r = rand() % 52;
    string card;
    if(checkDuplicates(card, hand) && r != 52){
    	card = deck[r + 1];
    } else if (checkDuplicates(card, hand) && r == 52){
    	int j = 0;
    	while(checkDuplicates(card, hand)){
    		card = deck[j];
    		j++;
    	}
    } else {
    	card = deck[r];
    }
    return card;
}







