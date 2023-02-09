#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

//Function to create random numbers
int randomizer (int min, int max) {
  return rand() % max + min;
}

//Function to switch index values in an array
vector <string> Switch (int index1, int index2, vector <string> mainarray) {
	string storage = mainarray[index1];
	mainarray[index1] = mainarray[index2];
	mainarray[index2] = storage;
  return mainarray;
}

//Function to create a deck based on two arrays
vector <string> createDeck (string faces[], string suits[]) {
  vector <string> deck;
  for (int i = 0; i < 13; i++) {
	  for (int z = 0; z < 4; z++) {
	  	deck.push_back(faces[i] + " of " + suits[z]);
	  }
  }
  return deck;
}

//Function to process input by checking its suitability and giving out error messages if the input is not appropriate
string inputProcessing(vector <string> userinput, string errormsg) {
  string input;
  cin >> input;
  transform(input.begin(), input.end(), input.begin(), ::tolower);
  while (std::find(userinput.begin(), userinput.end(), input) == userinput.end()) {
    cout << errormsg;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
  };
  return input;
}

//Function to split individual card names into arrays
vector <string> split(string card) {
  vector <string> cardArray;
  istringstream stream(card);
  string word;
  while (stream >> word) {
    cardArray.push_back(word);
  }
  return cardArray;
}

//Function to merge two different card piles
vector <string> merge(vector <string> deck1, vector <string> deck2) {
  for (int i = 0; i < deck2.size(); i++) {
    deck1.push_back(deck2[i]);
  }
  return deck1;
}

//Function used by sort to compare the suit ranking of similar cards with their alphabetical ranking
bool sortVector(vector <string> a, vector <string> b) {
  if (stoi(a[0]) < stoi(b[0])) {
    return true;
  } else if (stoi(a[0]) > stoi(b[0])) {
    return false;
  } else if (a[2].at(0) > b[2].at(0)) {
    return true;
  }
  return false;
}

//Function used to order hands of cards
vector <string> order(vector <string> hand) {
  string faces[13] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
  vector <vector <string>> orderedHand;
  for (int i = 0; i < 4; i++) {
    vector <string> card = split(hand[i]);
    int value = distance(faces, find(begin(faces), end(faces), card[0]));
    orderedHand.push_back(vector <string> {to_string(value), hand[i], card[2]});
  }
  sort(orderedHand.begin(), orderedHand.end(), sortVector);
  return vector <string> {orderedHand[3][1], orderedHand[2][1], orderedHand[1][1], orderedHand[0][1]};
}

//Main function
int main () {
  //Entire game loop
  bool gameOver = false;
  while (!gameOver) {
    //Two unchangeable arrays
    string faces[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    //Creating the deck
    vector <string> deck = createDeck(faces, suits);

    //Shuffling the deck
    for (int i = 0; i < 26; i++) {
      deck = Switch(randomizer(0, 51), randomizer(0, 51), deck);
    }

    //Halving the deck into 2 piles
    vector <string> pile1 = vector <string> (deck.begin(), deck.begin() + 26);
    vector <string> pile2 = vector <string> (deck.end() - 26, deck.end());

    //Initializing discard piles
    vector <string> discard1;
    vector <string> discard2;

    //Welcoming player
    cout << "Welcome to" << endl;
    cout << "__      ____ _ _ __ " << endl;
    cout << "\\ \\ /\\ / / _` | '__|" << endl;
    cout << " \\ V  V / (_| | |   " << endl;
    cout << "  \\_/\\_/ \\__,_|_|   " << endl << endl;;

    //Determining game type choice
    cout << "Do you want to play with a computer or another player? Type c for computer or p for player." << endl;
    vector <string> beginInputTypes = {"p", "player", "c", "computer"};
    string versionChoice = inputProcessing(beginInputTypes, "Please enter c for computer or p for player.");
    string player2Name;
    bool computerPlaying;
    computerPlaying = ((versionChoice == "c") || (versionChoice == "computer"));
    if (computerPlaying) {
      player2Name = "The Computer";
    } else {
      player2Name = "Player 2";
    }
    bool gameComplete = false;
    int turnnum = 1;

    //BEGINNING OF GAME LOOP
    while (!gameComplete) {
      cout << "__________________________________________________\n\n" << "Turn " << turnnum << endl << "__________________________________________________\n"; 

      //Creating card choices array
      vector <string> cardChoices = {"1", "2", "3", "4"};

      //Creating individual hand arrays
      vector <string> draw1;
      vector <string> orderedDraw1;
      vector <string> draw2;
      vector <string> orderedDraw2;

      //Outputting deck and discard pile sizes
      cout << endl << "Player 1 Deck: " << pile1.size() << " cards." << endl;
      cout << "Player 1 Discard Pile: " << discard1.size() << " cards." << endl;
      cout << endl << player2Name << " Deck: " << pile2.size() << " cards." << endl;
      cout << player2Name << " Discard Pile: " << discard2.size() << " cards." << endl;

      //Player 1 turn
      cout << endl << "Player 1 draws 4 cards\nThey are:" << endl;
      for (int i = 0; i < 4; i++) {
        string storage1 = pile1[0];
        draw1.push_back(storage1);
        pile1.erase(pile1.begin());
        cout << i + 1 << ". " << storage1 << endl;
      }

      //Processing user card order
      cout << "Pick your card order by typing your preferred card numbers and pressing enter." << endl;
      for (int i = 0; i < 4; i++) {
        string cardChoice;
        cout << to_string(i + 1) << ": ";
        i == 0 ? cardChoice = inputProcessing(cardChoices, "Please enter a number between 1 and 4.") : cardChoice = inputProcessing(cardChoices, "Please enter a number between 1 and 4 you did not already enter:");
        cardChoices.erase(remove(cardChoices.begin(), cardChoices.end(), cardChoice), cardChoices.end());
        orderedDraw1.push_back(draw1[stoi(cardChoice) - 1]);
      }

      //Resetting array values
      cardChoices = {"1", "2", "3", "4"};

      //Player 2 turn
      cout << endl << player2Name << " draws 4 cards.\nThey are:" << endl;
      for (int i = 0; i < 4; i++) {
        string storage2 = pile2[0];
        draw2.push_back(storage2);
        pile2.erase(pile2.begin());
        cout << i + 1 << ". " << storage2 << endl;
      }

      //Processing Player 2 card order
      if (!computerPlaying) {
        cout << "Pick your card order by typing your preferred card numbers and pressing enter." << endl;
        for (int i = 0; i < 4; i++) {
          string cardChoice;
          cout << to_string(i + 1) << ": ";
          i == 0 ? cardChoice = inputProcessing(cardChoices, "Please enter a number between 1 and 4.") : cardChoice = inputProcessing(cardChoices, "Please enter a number between 1 and 4 you did not already enter:");
          cardChoices.erase(remove(cardChoices.begin(), cardChoices.end(), cardChoice), cardChoices.end());
          orderedDraw2.push_back(draw2[stoi(cardChoice) - 1]);
        }
      //Setting Computer card order
      } else {
        orderedDraw2 = order(draw2);
      }

      //Establishing individual matchup winners
      for (int i = 0; i < 4; i++) {
        vector <string> player1Card;
        vector <string> player2Card;
        player1Card = split(orderedDraw1[i]);
        player2Card = split(orderedDraw2[i]);
        int player1val = distance(faces, find(begin(faces), end(faces), player1Card[0]));
        int player2val = distance(faces, find(begin(faces), end(faces), player2Card[0]));
        if (player1val > player2val) {
          discard1.push_back(orderedDraw1[i]);
          discard1.push_back(orderedDraw2[i]);
          cout << "Player 1 wins matchup " << i + 1 << " (" << orderedDraw1[i] << " vs " << orderedDraw2[i] << ")" << endl;
        } else if (player2val > player1val) {
          discard2.push_back(orderedDraw1[i]);
          discard2.push_back(orderedDraw2[i]);
          cout << player2Name << " wins matchup " << i + 1 << " (" << orderedDraw1[i] << " vs " << orderedDraw2[i] << ")" << endl;
        } 
        else if (player1Card[2].at(0) < player2Card[2].at(0)) {
          discard1.push_back(orderedDraw1[i]);
          discard1.push_back(orderedDraw2[i]);
          cout << "Player 1 wins matchup " << i + 1 << " (" << orderedDraw1[i] << " vs " << orderedDraw2[i] << ")" << endl;
        } else {
          discard2.push_back(orderedDraw1[i]);
          discard2.push_back(orderedDraw2[i]);
          cout << player2Name << " wins matchup " << i + 1 << " (" << orderedDraw1[i] << " vs " << orderedDraw2[i] << ")" << endl;
        }
      }

      //Determining whether to shuffle cards back in and winner
      if (pile1.size() + discard1.size() < 4) {
        gameComplete = true;
        cout << endl << endl << player2Name << " won in " << turnnum << " turns." << endl;
      } else if (pile2.size() + discard2.size() < 4) {
        gameComplete = true;
        cout << endl << endl << "Player 1 won in " << turnnum << " turns." << endl;
      }

      //Asking for play again
      if (gameComplete == true) {
        vector <string> endInputTypes = {"y", "yes", "n", "no"};
        cout << "Would you like to play again? Type y for yes or n for no." << endl;
        string choice = inputProcessing(endInputTypes, "Please enter y for yes or n for no.");
        if ((choice == "n") || (choice == "no")) {
          cout << "Thank you for playing War!";
          gameOver = true;
          break;
        }
      }
      
			//Shuffling discard cards back into deck
      if (pile1.size() < 4) {
        pile1 = merge(pile1, discard1);
        discard1 = {};
      }
      if (pile2.size() < 4) {
        pile2 = merge(pile2, discard2);
        discard2 = {};
      }

      //Incrementing turn counter
      turnnum++;
    }
  }
  return 0;
}

