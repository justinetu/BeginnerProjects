#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

static const string regChars[] = 
{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
const int REG_CHARS_LENGTH = 62;

string generatePassword(string s) { // Method that will generate the password
    return s;
}

string generatePassword(int length, int numOfSC) {
    int numOfRands = length - numOfSC;
    string uniquePass = "";
    srand(time(0));
    for(int i = 0; i < numOfRands; i++) { // we loop for the amount of random regular characters we need
        int r = (rand() % REG_CHARS_LENGTH - 1); // our random number
        uniquePass += regChars[0].at(r); // append the randomly selected character from our array to the password string
    }
    return uniquePass;
}

string generatePassword(int length) {
    string pass = "";
    srand(time(0));
    for(int i = 0; i < length; i++) {
        int ran = (rand() % REG_CHARS_LENGTH - 1);
        pass += regChars[0].at(ran);
    }
    return pass;
}

int main() {
    int length;
    char c;
    cout << "==========================================" << endl;
    cout << "Hi welcome to this Password Generator.\n";
    cout << "Enter the length of your password >> ";
    cin >> length;
    cout << "If you would like any special characters, type y otherwise type n >> ";
    cin >> c;
    c = tolower(c);
    switch(c) {
        case 'n':
            cout << "Your generated password is: " <<
            generatePassword(length) << endl;
            break;
        case 'y': 
            int numOfSC;
            string specialChars;
            cout << "How many special characters do you want? ";
            cin >> numOfSC;
            while(numOfSC > length) {
                cout << "Error! The number of special chracters can't be larger than password length. Try again. "
                     << endl << "How many special characters do you want?\n";
                cin >> numOfSC;     
            }
            char arr[numOfSC]; // This char array will be used to append special characters to the password
            cout << "Enter the special characters you'd like in your password >> ";
            cin >> specialChars;
            for(int i = 0; i < numOfSC; i++) {
                arr[i] = specialChars.at(i);
            }
            if(numOfSC == length)
                generatePassword(specialChars);
            else {
                cout << "Your generated password is: " << 
                generatePassword(length, numOfSC) + specialChars << endl << "==========================================";
            }
            break;
    }
    return 0;
}

// length  -> 6
// num of special chars -> 2
// special chars -> #$
// In this example we need to generate 4 random regular characters then append the special characters
// I need to write an algorithm that generates random numbers based on the length - number of special characters.
