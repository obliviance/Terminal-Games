//Awwab Mahdi 
//February 24th, 2020

//Remember to address EACH major section

import java.util.Scanner;

class Main {
  
  public static void main (String[] args) {
    //Executing the game method
    game();
  }

  static void game () {
    //Creating a Scanner input variable
    Scanner input = new Scanner(System.in);
    
    //A welcome message and some information on the game
    System.out.println("Welcome to Mastermind!\n");
    System.out.println("Use V for Violet.");
    System.out.println("Use B for Blue.");
    System.out.println("Use G for Green.");
    System.out.println("Use R for Red.");
    System.out.println("Use Y for Yellow.");
    System.out.println("Use T for Tan.");
    System.out.println("Use O for Orange.");
    System.out.println("Use I for Indigo.");
    
    //Array for the possible colours
    String[] colours = {"V", "B", "G", "R", "Y", "T", "O", "I"};

    //Creating a String variable that holds the computer code
    String code = colours[randomize(0, colours.length-1)] + colours[randomize(0, colours.length-1)] + colours[randomize(0, colours.length)] + colours[randomize(0, colours.length)];

    //Outputing the code so that I know it
    System.out.println(code);
    
    //Asking for and taking in user input
    System.out.println("Choose your mode. Type in easy, medium or hard for 12, 8, or 5 turns.");
    String modechoice = input.nextLine();
    
    //Creating a variable to keep track of how many turns the user is allowed
    int turns = 0;

    //Using the user's choice to determine the amount of turns
    if (modechoice == "easy") {
      turns = 12;
    } else if (modechoice == "medium") {
      turns = 8;
    } else if (modechoice == "hard") {
      turns = 5;
    }
    
    //Variable to keep track of turn
    int numturn = 0;
    
    //String array to hold guesses of user
    String[] guesses = {"", "", "", "", "", "", "", "", "", "", "", ""};

    //A do-while loop to execute the player turns
    do {
      //Storing usercode by calling the turn function
      guesses[numturn] = turn(numturn);

      //Storing input into an array
      format(guesses, code, numturn);

      //Adding to the counter
      numturn++;
    }
    //While the user still has guesses and is still incorrect
    while (checkState(code, guesses[numturn - 1], turns, numturn) != "won");

    //If the user has guesses correctly
    if (checkState(code, guesses[numturn - 1], turns, numturn) == "won") {
      //SoP a win message
      System.out.println("You guessed the correct code, " + code + "!");
      System.out.println("Congratulations, you won in " + numturn + " turns  on " + modechoice + " mode!");

    //Otherwise...
    } else {
      //SoP a loss message
      System.out.println("You didn't guess it right. The correct code was " + code + "!");
      System.out.println("You lost after " + numturn + " turns  on " + modechoice + " mode.");
    }
    
    //Play Again
    System.out.println("Would you like to play again? Please type yes or no.");
    String playagain = input.nextLine();
    if (playagain == "yes") {
      //Rerunning the main function to restart the game.
      game();
    } else {
      System.out.println("Thank you for playing MASTERMIND.");
    }
  }
  
  //Method to take in input and return
  public static String turn (int numberofturn) {
    Scanner input = new Scanner(System.in);
    //Taking in user code
    System.out.println("\nEnter Code");
    
    //Taking in user code
    String x = input.nextLine();

    return x;
  }
  
  //Method to format each turn's output
  public static void format (String[] usercodes, String realcode, int numberofturn) {
    //SoP-ing a line and Current Board
    line();
    System.out.println("Current Board");

    //SoP-ing each guess and its accuracy
    for (int i = 0; i <= numberofturn; i++) {
      System.out.println(usercodes[numberofturn - i] + "|" + checkCode(realcode, usercodes[numberofturn - i]));
    }
  }
  
  //Method to print out a series of dashes
  public static void line () {
    System.out.println("-------------");
  }
  
  //Method that creates random numbers
  public static int randomize (int start, int end) {
    return (int) Math.floor(start + Math.random() * end);
  }
  
  //Method to check game state
  public static String checkState (String realcode, String usercode, int amountofturns, int numberofturn) {
    //Checking if the guess is correct and storing it in a variable
    String accuracy = checkCode(realcode, usercode);

    //Checking if the usercode is correct
    if (accuracy.equals("xxxx")) {
      return "won";
    //If the user is out of turns
    } else if (numberofturn == amountofturns) {
      return "lost";
    //Otherwise...
    } else {
      return "keep going";
    }
  }
  
  //Method to check if user code is the same as the computer code, and to return the string showing accuracy of guesses
  public static String checkCode (String realcode, String inputcode) {
    //Creating accuracy string
    String check = "";
    
    //Looping through string checking if colours and positions are correct
    for (int i = 0; i < 4; i++) {
      //If colour AND position are correct
      if (inputcode.charAt(i) == realcode.charAt(i)) {
        check = check.concat("x");
      //If colour is correct
      } else if (realcode.contains(Character.toString(inputcode.charAt(i)))) {
        check = check.concat("o");
      }
    }

    //Returning accuracy string
    return check;
  }
}