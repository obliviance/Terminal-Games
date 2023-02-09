import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    
    System.out.println("Welcome to the Rock Paper Scissors simulator.");
    //Welcome statement

    //Allowing user to enter a name
    System.out.println("Please enter your name.");
    String username = input.nextLine(); 

    //Intializing variables to hold user and computer scores
    int userscore = 0;
    int compscore = 0;

    System.out.println("\n\n----------------------------------------------------");

    //Creating a for loop that will run three times, one for each round
    for (int i = 0; i < 3; i++) {
      //Round title
      System.out.println("Round " + (i + 1));
      System.out.println("_______\n\n");
      //Inital message
      System.out.println("Please enter R for rock, P for paper, or S for scissors.");
      //Taking in user choice
      char user_choice = input.next().charAt(0);

      //A while loop that ensures that the user choice is a R, P, or S. If not, it repeats the question until it recieves the correct response
      while ((user_choice != 'R') && (user_choice != 'S') && (user_choice != 'P')) {
        System.out.println("Invalid input. Please enter R for rock, P for paper, or S for scissors.");
        user_choice = input.next().charAt(0);
      }

      //Random variable that holds a number between 1 and 3
      int compchoice = (int) Math.round(Math.random() * 3);

      //Changing of the compchoice number to a corresponding letter
      char completter = 'R';
      if (compchoice == 2) {
        completter = 'S';
      } else if (compchoice == 3) {
        completter = 'P';
      }

      //Comparing user and computer choices
      //First if statement is for a tie
      if (user_choice == completter) {
        System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " tied.");
      //If user chooses R...
      } else if (user_choice == 'R') {
        //And if computer chooses S...
        if (completter == 'S') {
          //Output this message and increment the user score
          System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " won.");
          userscore += 1;
        //And if computer chooses P...
        } else {
          //Output this message and increment the computer score
          System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " lost.");
          compscore += 1;
        }
      //If user chooses S...
      } else if (user_choice == 'S') {
        //And if computer chooses R...
        if (completter == 'R') {
          //Output this message and increment the computer score
          System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " lost.");
          compscore += 1;
        //And if computer chooses P...
        } else {
          //Output this message and increment the user score
          System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " won.");
          userscore += 1;
        }
      //If user chooses P...
      } else if (user_choice == 'P') {
        //And if computer chooses R...
        if (completter == 'R') {
          //Output this message and increment the user score
          System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " won.");
          userscore += 1;
        //And if computer chooses S...
        } else {
          //Output this message and increment the computer score
          System.out.println(username + " played " + user_choice + " and computer played " + completter + ". \n" + username + " lost.");
          compscore += 1;
        }
      }
      //A line to divide rounds from one another
      System.out.println("---------------------------------------------");
    }

    //Finding the winner of the match
    //If user had a greater score than the computer
    if (userscore > compscore) {
      //You won. YAYYYYY
      System.out.println(username + " won the match. \nCongratulations!");
    //If user had a score less than what the computer got
    } else if (userscore < compscore) {
      //You lost. Very sad
      System.out.println(username + " lost the match. \nBetter luck next time!");
    //Otherwise..
    } else {
      //You tied. DO BETTER.
      System.out.println(username + " tied with the computer. Well, I guess you two were equally matched.");
    }  
  }
}