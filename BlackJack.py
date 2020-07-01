#!/usr/bin/python
# BlackJack v1.0 By Andrew Knapp
# This is a port (with some changes) of the Java version of BlackJack I wrote
import random

money = 100
deck = ['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C',
        '0C', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D',
        '6D', '7D', '8D', '9D', '0D', 'JD', 'QD', 'KD', 'AS',
        '2S', '3S', '4S', '5S', '6S', '7S', '8S', '9S', '0S',
        'JS', 'QS', 'KS', 'AH', '2H', '3H', '4H', '5H', '6H',
        '7H', '8H', '9H', '0H', 'JH', 'QH', 'KH']


def intro():
    """Intro function"""
    print("Welcome to Black Jack!")
    print("You have: ${}".format(str(money)))


def choice(ans):
    """Determine the choice a player made"""
    if ans[0].lower() == 'y':
        return True
    else:
        return False


def check_money():
    """Check to see if the player has money to play"""
    if money == 0:
        print("You're out of money. House wins.")
        return False


def get_card_value(card, total):
    """Determine the value of the card"""
    if card[0].isdigit() and int(card[0]) != 0:
        return int(card[0])
    elif card[0] == "A" and total + 11 <= 21:
        return 11
    elif card[0] == "A" and total + 11 > 21:
        return 1
    else:
        return 10


def get_card_type(card):
    """Determine card type"""
    if card[0].isalpha():
        faceCards = ["Ace", "Jack", "Queen", "King"]
        for get_card_type in faceCards:
            if get_card_type[0] == card[0]:
                return get_card_type
    elif card[0] == '0':
        return "10"
    else:
        return str(card[0])


def get_suit_type(card):
    """Determine suit type of a card"""
    suits = ["Spades", "Hearts", "Clubs", "Diamonds"]
    for types in suits:
        if card[1] == types[0]:
            return types


def find_winner(player_total, dealer_total, bet, money):
    """Determine the winner of a hand"""
    if player_total <= 21 and dealer_total <= 21:
        print("You have {} dealer has {}".format(str(player_total), str(dealer_total)))
        if player_total == dealer_total:
            print("Push")
        elif player_total > dealer_total:
            print("You won!")
            money = money + bet
        else:
            print("House wins.")
            money = money - bet
    elif dealer_total > 21:
        print("Dealer Busts.  You win!")
        money = money + bet
    else:
        print("House wins.")
        money = money - bet
    return money


def play_game(bet, money):
    """Steps in playing a blackjack game"""
    player_total = 0
    dealer_total = 0
    cards = []
    random.shuffle(deck)
    player_card1 = deck.pop()
    cards.append(player_card1)
    print("1st card: {} of {}".format(get_card_type(player_card1), get_suit_type(player_card1)))
    player_total += get_card_value(player_card1, player_total)
    player_card2 = deck.pop()
    cards.append(player_card2)
    print("2nd card: {} of {}".format(get_card_type(player_card2), get_suit_type(player_card2))) 
    player_total += get_card_value(player_card2, player_total)
    dealer_card1 = deck.pop()
    dealer_total += get_card_value(dealer_card1, dealer_total)
    cards.append(dealer_card1)
    print("Dealer gets: {} of {}".format(get_card_type(dealer_card1), get_suit_type(dealer_card1)))
    print("Dealer showing: {}".format(str(dealer_total)))
    print("You have: {}".format(str(player_total)))
    ans = raw_input('Do you want to hit? ')
    while choice(ans) and player_total < 21:
        player_card = deck.pop()
        cards.append(player_card)
        print("{} of {}".format(get_card_type(player_card),  get_suit_type(player_card)))
        player_total += get_card_value(player_card, player_total)
        if player_total == 21:
            print("You got 21!")
        elif player_total > 21:
            print("You have: {}".format(str(player_total)))
            print("You Busted.")
        else:
            print("You have: {}".format(str(player_total)))
            ans = raw_input('Do you want to hit? ')
    while dealer_total <= 17 and player_total < 21:
        dealer_card = deck.pop()
        cards.append(dealer_card)
        print("Dealer gets: {} of {}".format(get_card_type(dealer_card), get_suit_type(dealer_card)))
        dealer_total += get_card_value(dealer_card, dealer_total)
        print("Dealer has {}".format(str(dealer_total)))
    money = find_winner(player_total, dealer_total, bet, money)
    for item in cards:
        deck.append(item)
    return money


def win_loss():
    """Determine if a player has won or lost money"""
    if money > 100:
        print("You won ${}".format(str(money - 100)))
    else:
        print("You lost ${}".format(str(100 - money)))


intro()
ans = 'y'
while choice(ans):
    amount = raw_input("How much do you want to bet? ")
    while amount.isalpha():
        print("That is not a number")
        amount = raw_input("How much do you want to bet? ")
    bet = int(amount)
    money = play_game(bet, money)
    print("You have ${}".format(str(money)))
    if money <= 0:
        print("You are out of money.")
        break;
    else:
        ans = raw_input('Do you want to play again? ')
win_loss() 
