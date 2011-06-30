import java.util.*;

/** Small BlackJack game to test out and maintain skills I learned 
 * from a Programming 101 (CSE142) course I took.
 * @author Andrew Knapp
 * @version 1.0
 */
public class blackjack {

	public static final int INITIAL_MONEY = 100; 
	 
	public static void main(String[] arg)	{
		Random draw = new Random();
		Scanner console = new Scanner(System.in);
		int money =	INITIAL_MONEY;
		intro(money);
		boolean play = true;
		
		while (money > 0 && play == true) {
			int card2 = 0;
			int dealer = 0;
			int total = 0;
			boolean ace = false;
			int to_play = betAmount(money, console);
			System.out.print("First card: ");
			total = dealCards(total, card2, dealer, draw, ace);
			System.out.print("Second card: ");
			card2 = dealCards(total, card2, dealer, draw, ace);
			System.out.print("Dealer gets: ");
			dealer = dealCards(total, card2, dealer, draw, ace);
			int dealer1 = dealer;
			total += card2;
			ace = aceCheck(total, card2, dealer1, dealer);
			boolean another_card = true;
			while (total < 21 && another_card == true){
					another_card = Hit(total, console);
					if (total > 21 || total == 21 || another_card == false) {
						break;
					}	
					total += dealCards(total, card2, dealer, draw, ace);
					if (ace == true && total > 21) {
						total -= 10;
					}
			}
			while (dealer < 17 && total < 21) {
				System.out.println("Dealer showing: " + dealer);
				dealer += dealCards(total, card2, dealer, draw, ace);
				boolean dealer_ace = aceCheck(total, card2, dealer1, dealer);
				if (dealer_ace == true && dealer > 21) {
					dealer -= 10;
				} 
			}
			money += winCheck(total, dealer, to_play);
			play = playAgain(console, money);
		}
	}
	
	/** Ace exception call to see if the ace should be a 1 or 11
	 * 
	 * @param total running total of players cards
	 * @param card2 card that is an ace
	 * @param dealer1 dealer amount 
	 * @param dealer running total of dealer amount
	 * @return a boolean
	 */
	public static boolean aceCheck(int total, int card2, int dealer1, int dealer){
		if (total - card2 == 11 || dealer1 == 11 || dealer - 11 == dealer1) {
			return true;
		} else {
			return false;
		}
	}
	
	/** Checks to see if the player or the dealer won
	 * 
	 * @param total running total of player's cards
	 * @param dealer running total of dealer's cards
	 * @param to_play
	 * @return the money amount that the player has
	 */
	public static int winCheck(int total, int dealer, int to_play) {
		int gains_losses = 0;
		if (total == 21) {
			System.out.println("You have: " + total);
			System.out.println("You got BlackJack!  You win!");
			gains_losses = 2 * to_play;
		} else if (total > 21) {
			System.out.println("You have: " + total);
			System.out.println("You bust");
			gains_losses = -1 * to_play;
		} else if (total == dealer) {
			System.out.println("You have: " + total);
			System.out.println("Dealer has: " + dealer);
			System.out.println("Push.");
			gains_losses = 0;
		} else if (dealer > 21) {
			System.out.println("Dealer has: " + dealer);
			System.out.println("Dealer busts.  You win!");
			gains_losses = 2 * to_play;
		} else if (total < dealer) {
			System.out.println("You have: " + total);
			System.out.println("Dealer has: " + dealer);
			System.out.println("Dealer wins.");
			gains_losses = -1 * to_play;
		} else {
			System.out.println("You have: " + total);
			System.out.println("Dealer has: " + dealer);
			System.out.println("You beat the dealer!  You win!");
			gains_losses = 2 * to_play;
		}
		return gains_losses;
	}
	
    /** The bet amount for each round, subtracting from total
     * 
     * @param money money for each round
     * @param console allow for user interaction
     * @return the bet on the game
     */
   public static int betAmount(int money, Scanner console) {
		System.out.println("How much would you like to bet?");
		int bet = Math.abs(console.nextInt());
		while(bet > money || bet < 10){
			if (bet < 10) {
				System.out.println("There is a minimum bet of $10");
			} else {
		   	System.out.println("You don't have that much money.");
			}
			System.out.println("How much would you like to bet?");
			bet = console.nextInt();
		}
		return bet;
	}
   
	/** Deals the cards for each round
	 * 
	 * @param total running total of player's cards
	 * @param card2 value of 2nd card dealt
	 * @param dealer running total of dealer's cards
	 * @param draw chooses a random value between 1-13 as a simple card value
	 * @param ace boolean to decide if the aceCheck method needs to be called
	 * @return the card drawn
	 */
	public static int dealCards(int total, int card2, int dealer, 
											Random draw, boolean ace) {
		int card = draw.nextInt(12) + 1;
		if (card == 11) {
			System.out.println("Jack");
			card = 10;
		} else if (card == 12) {
			System.out.println("Queen");
			card = 10;
		} else if (card == 13) {
			System.out.println("King");
			card = 10;
		} else if (card == 1) {
			System.out.println("Ace");
			if (dealer <= 10 && card2 > 0 || total <= 10) {
				card = 11;
				return card;
			} else if (ace == true && total > 21 || total > 11) {
				card = 1;
			} else {
				card = 1;
			}		
		} else {
			System.out.println(card);
		}
		return card;
	}
	
	/** To decide if they want to hit or not
	 * 
	 * @param running total of player's cards
	 * @param console user interaction
	 * @return true or false if the player wants to hit
	 */
	public static boolean Hit(int total, Scanner console){
		boolean ans = false;
		System.out.println();
		System.out.println("You have: " + total); 
		System.out.println("Do you want to hit?");
      String answer = console.next();
        if (answer.indexOf("y") == 0 || answer.indexOf("Y") == 0) {
            ans = true;
        } else if (answer.indexOf("n") == 0 || answer.indexOf("N") == 0) {
            ans = false;
        }	else {
            System.out.println();
            ans = false;
        }
		return ans;
	}	
	
	/** Allows the user to decide if they are going to play again
	 * 
	 * @param console user interaction
	 * @param money total money the player has
	 * @return true or false if the user wants to play again
	 */
	public static boolean playAgain(Scanner console, int money){
		boolean ans;
		System.out.println("You have: $" + money);
		if (money == 0) {
			System.out.println("You're out of money.  House wins.");
			ans = false;
			return ans;
		} 
		System.out.println("Do you want to play again?");
		String answer = console.next();
      if (answer.indexOf("y") == 0 || answer.indexOf("Y") == 0) {
      	ans = true;
			return ans;
      } else if (answer.indexOf("n") == 0 || answer.indexOf("N") == 0) {
            ans = false;
				if (money > 100) {
					System.out.println("Congratulations! You won: $" + (money - 100));
				} else {
					System.out.println("You lost: $" + (100 - money));
				}
				return ans;
      } else {
      	System.out.println();
         ans = false;
      }
		return ans;
	}
	
	/** Prints the introduction to the game
	 * 
	 * @param money total money that the user is given
	 */
   public static void intro(int money) {
		System.out.println("Welcome to BlackJack!");
		System.out.println();
		System.out.println("You have: $" + money);
   }
}