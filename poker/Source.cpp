#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string dealCard();
bool checkDuplicate(string hand[], string aCard);
void dealHand(string hand[]);
void swapCards(string hand[]);
void convertToInt(string hand[], int numHand[2][5]);
int findWinner(string hand[]);
int countpoints(string hand[]);
int gethigher(string hand[]);


int main()
{
    // Generate new random numbers each time the program is run
    srand(time(NULL));

    // Creates an option menu
    int option = 0;
    bool stop = false;

    while (stop != true)
    {
        cout << "*********" << endl;
        cout << "POKER" << endl;
        cout << "*********" << endl << endl;
        cout << "1. Play" << endl;
        cout << "2. Exit" << endl << endl;
        cout << "Choose your option: ";
        cin >> option;

        if (option != 2) {
            // Deal 5 cards to the player
            string hand[5] = { "", "", "", "", "" };
            dealHand(hand);
            for (int i = 0; i < 5; i++)
                cout << endl << (i + 1) << " - " << hand[i];

            // Give the player the option to swap their cards
            char yesOrNo;
            cout << endl << endl << "Do you want to change cards? (y/n): ";
            cin >> yesOrNo;
            if (yesOrNo == 'y') {
                swapCards(hand);
                cout << endl << "Your new cards are:" << endl;
                for (int i = 0; i < 5; i++)
                    cout << (i + 1) << " - " << hand[i] << endl;
                cout << endl;
            }



      
            // Opponent's hand
            string opphand[5] = { "", "", "", "", "" };

            dealHand(opphand);
            
            cout << endl << "Opponents cards are:" << endl;
            for (int i = 0; i < 5; i++)
                cout << endl << (i + 1) << " - " << opphand[i];


           // see points for determening winner
          //  cout << endl << findWinner(hand) <<"  " << findWinner(opphand) << "  " <<gethigher(hand)  << endl;

            //find winner
            if (findWinner(hand) == findWinner(opphand)) {
                if(gethigher(hand) > gethigher(opphand)) cout << "YOU WIN" << endl;
                else if (gethigher(hand) < gethigher(opphand)) cout << "YOU LOSE" << endl;
                else if (gethigher(hand) == gethigher(opphand)) {
                    if (countpoints(hand) > countpoints(opphand)) cout << "YOU WIN" << endl;
                    else if (countpoints(hand) < countpoints(opphand))   cout << "YOU LOSE" << endl;
                    else if (countpoints(hand) == countpoints(opphand)) cout << "TIE" << endl;
                }
            }

            else if (findWinner(hand) > findWinner(opphand)) {
                cout << "YOU WIN" << endl;
            }
            else if (findWinner(hand) < findWinner(opphand)) {
                cout << "YOU LOSE" << endl;
            }






            // Pause program
            cin.ignore(256, '\n');
            cout << endl << "Hit enter to continue...";
            cin.get();
            system("CLS");
        }
        else {
            stop = true;
        }
    }

    return 0;
}

// Returns a card from the deck
string dealCard()
{
    string card;

    int aSuit = (rand() % (4 - 1 + 1)) + 1;
    int aCard = (rand() % (13 - 1 + 1)) + 1;

    string face;

    switch (aSuit)
    {
    case 1: face = " of Hearts"; break;
    case 2: face = " of Spades"; break;
    case 3: face = " of Diamonds"; break;
    case 4: face = " of Clubs"; break;
    }

    string value;

    switch (aCard)
    {
    case 1: value = "Ace"; break;
    case 2: value = "2"; break;
    case 3: value = "3"; break;
    case 4: value = "4"; break;
    case 5: value = "5"; break;
    case 6: value = "6"; break;
    case 7: value = "7"; break;
    case 8: value = "8"; break;
    case 9: value = "9"; break;
    case 10: value = "10"; break;
    case 11: value = "Jack"; break;
    case 12: value = "Queen"; break;
    case 13: value = "King"; break;
    }

    card = (value + face);


    return card;
}

// Returns true when a given cards already exists within the hand
bool checkDuplicate(string hand[], string aCard)
{
    bool duplicate = false;

    for (int i = 0; i < 5; i++) {
        if (hand[i] == aCard)
            duplicate = true;
    }

    return duplicate;
}

// Deals five random cards to player
void dealHand(string hand[])
{
    for (int i = 0; i < 5; i++) {
        string j = dealCard();
        if (checkDuplicate(hand, j) == true)
            i--;
        else
            hand[i] = j;
    }
}

// Allows player to swap cards within their hand
void swapCards(string hand[])
{
    char yesOrNo;

    for (int i = 0; i < 5; i++) {
        cout << "Change card " << (i + 1) << "? (y/n): ";
        cin.ignore(256, '\n');
        cin >> yesOrNo;

        if (yesOrNo == 'y') {
            string j;
            do {
                j = dealCard();
            } while (checkDuplicate(hand, j) == true);
            hand[i] = j;
        }
        else {
            continue;
        }
    }
}
// Translates hand into an integer array
void convertToInt(string hand[], int numHand[2][5])
{
    stringstream stream;


    for (int i = 0; i < 5; i++) {
        if (hand[i].substr(0, 2) == "10") {
            numHand[0][i] = 10;
        }
        else if (hand[i].substr(0, 1) == "A") {
            numHand[0][i] = 14;
        }
        else if (hand[i].substr(0, 1) == "J") {
            numHand[0][i] = 11;
        }
        else if (hand[i].substr(0, 1) == "Q") {
            numHand[0][i] = 12;
        }
        else if (hand[i].substr(0, 1) == "K") {
            numHand[0][i] = 13;
        }
        else {
            stream << hand[i].substr(0, 1);
            stream >> numHand[0][i];
            stream.str("");
            stream.clear();
        }
    }

    enum { HEARTS, SPADES, DIAMONDS, CLUBS };

    for (int i = 0; i < 5; i++) {
        if (hand[i].find("Hearts") != -1) {
            numHand[1][i] = HEARTS;
        }
        else if (hand[i].find("Spades") != -1) {
            numHand[1][i] = SPADES;
        }
        else if (hand[i].find("Diamonds") != -1) {
            numHand[1][i] = DIAMONDS;
        }
        else {
            numHand[1][i] = CLUBS;
        }
    }
}

// Evaluate whether there is a winner in the hand
int findWinner(string hand[])
{
    int score = 0;

    bool straightFlush = false;
    bool fourOfAKind = false;
    bool fullHouse = false;
    bool flush = false;
    bool straight = false;
    bool threeOfAKind = false;
    bool twoPair = false;
    bool onePair = false;

    enum {
        PAIR = 1,
        TWO_PAIR,
        THREE_OF_A_KIND,
        FULL_HOUSE,
        FOUR_OF_A_KIND = 6
    };

    int cards[2][5];
    convertToInt(hand, cards);

    // Looks for a pair, two pair, three of a kind,
    // full house and four of a kind.
    vector<int> winners(0);
    for (int i = 0; i < 4; i++) {
        for (int j = i; j < 4; j++) {
            if (cards[0][i] == cards[0][j + 1]){
                winners.push_back(cards[0][i]);
            }
        }
    }
    if (winners.size() == FOUR_OF_A_KIND)
        fourOfAKind = true;
    else if (winners.size() == FULL_HOUSE)
        fullHouse = true;
    else if (winners.size() == THREE_OF_A_KIND)
        threeOfAKind = true;
    else if (winners.size() == TWO_PAIR)
        twoPair = true;
    else if (winners.size() == PAIR)
        onePair = true;

    // Looks for a straight
    vector<int> orderCards(0);
    for (int i = 0; i < 5; i++)
        orderCards.push_back(cards[0][i]);
    // Bubble sort algorithm
    bool swapped = true;
    int j = 0;
    int tmp;
    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < (orderCards.size() - j); i++) {
            if (orderCards[i] > orderCards[i + 1]) {
                tmp = orderCards[i];
                orderCards[i] = orderCards[i + 1];
                orderCards[i + 1] = tmp;
                swapped = true;
            }
        }
    }
    int checkStraight = orderCards.back();
    while (checkStraight != orderCards.front()) {
        checkStraight--;
    }
    if (checkStraight == (orderCards.back() - (orderCards.size() - 1))) {
        straight = true;
    }
    else if ((orderCards[0] == 1) &&
        (orderCards[1] == 10) &&
        (orderCards[2] == 11) &&
        (orderCards[3] == 12) &&
        (orderCards[4] == 13)) {
        straight = true;
    }

    // Looks for a flush
    for (int i = 0; i < 4; i++) {
        if (cards[1][i] == cards[1][i + 1]) {
            flush = true;
        }
        else {
            flush = false;
            break;
        }
    }

    // Looks for a straight flush
    if ((straight == true) && (flush == true))
        straightFlush = true;

    if (straightFlush == true) {
        score = 800;
    }
    else if (fourOfAKind == true)
        score += 700;
    else if (fullHouse == true)
        score += 600;
    else if (flush == true)
        score += 500;
    else if (straight == true)
        score += 400;
    else if (threeOfAKind == true)
        score += 300;
    else if (twoPair == true)
        score += 200;
    else if (onePair == true) {
        score += 100;
    }

    return score;
}


// find the strength of the hand by the cards
int countpoints(string hand[]) {
    int points = 0;
    string s;
    int value;
    for (int i = 0; i < 5; i++) {
        istringstream iss(hand[i]);
        getline(iss,s,' ');
       
        if (s == "Ace") points += 14;
        else if (s == "2") points += 2;
        else if (s == "3") points += 3;
        else if (s == "4") points += 4;
        else if (s == "5") points += 5;
        else if (s == "6") points += 6;
        else if (s == "7") points += 7;
        else if (s == "8") points += 8;
        else if (s == "9") points += 9;
        else if (s == "10") points += 10;
        else if (s == "Jack") points += 11;
        else if (s == "Queen") points += 12;
        else if (s == "King") points += 13;

    }

    return points;
}

int gethigher(string hand[]) {
    int cards[2][5];
    convertToInt(hand, cards);

    // Looks for a pair, two pair, three of a kind,
    // full house and four of a kind.
    vector<int> winners(0);
    for (int i = 0; i < 4; i++) {
        for (int j = i; j < 4; j++) {
            if (cards[0][i] == cards[0][j + 1]) {
                winners.push_back(cards[0][i]);
                int v = cards[0][i];
                return v;
            }
        }
    }
}