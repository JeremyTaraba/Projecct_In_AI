#ifndef PROMPT_H_
#define PROMPT_H_

#include <iostream>

using namespace std;

int prompt(){

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



#endif