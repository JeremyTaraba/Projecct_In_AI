#include <iostream>
#include "prompt.h"

using namespace std;

int promptPuzzleType(){

    int pType;
    bool inputError = true;
    cout << "Welcome to jtara006, SID: 862008946,  8-puzzle solver." << endl;
    
    while(inputError){
        inputError = false;
       
        cout << "Type \"1\" to use a default puzzle or \"2\" to enter your own puzzle." << endl;
        cin >> pType;

        if(pType == 1){
            cout << "You selected default puzzle" << endl;
        }
        else if(pType == 2){
            cout << "You selected custom puzzle" << endl;
        }
        else{
            cout << "Error: You did not enter \"1\" or \"2\". Try again" << endl << endl;
            inputError = true;
        }
    }


    return pType;
}

int promptAlgorithmType(){

    int aType;
    bool inputError = true;
    while(inputError){

        cout << "Enter your choice of algorithm: " << endl;
        cout << "Uniform Cost Search. Enter a \"1\"" << endl;
        cout << "A* with the Misplaced Tile heuristic. Enter a \"2\"" << endl;
        cout << "A* with the Eucledian distance heuristic. Enter a \"3\"" << endl;
        cin >> aType;
        if( (aType == 1) || (aType == 2) || (aType == 3) ){
            inputError = false;
        }
        else{
            cout << "Error: You did not enter a valid algorithm choice. Try again." << endl << endl;
            cout << "aType is: " << aType << endl;
        }
         
    }

    return aType;
}
