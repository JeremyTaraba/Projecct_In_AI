#include <iostream>
#include <vector>
#include "puzzleMaker.h"

using namespace std;

vector<int> puzzleMakerCustom(){

    vector<int> puzzleToSolve;
    int num;

    cout << "Enter your puzzle, use numbers 0 - 8, no repeating numbers." << endl;
    cout << "Use a zero to represent the blank" << endl;
    cout << "Enter the first row (3 numbers), use spaces between the numbers: ";
    for(int i = 0; i < 3; i++){
        cin >> num;
        puzzleToSolve.push_back(num);
    }
   
    cout << "Enter the second row (3 numbers), use spaces between the numbers: ";
    for(int i = 0; i < 3; i++){
        cin >> num;
        puzzleToSolve.push_back(num);
    }

    cout << "Enter the third row (3 numbers), use spaces between numbers: ";
    for(int i = 0; i < 3; i++){
        cin >> num;
        puzzleToSolve.push_back(num);
    }

    //output the entered puzzle
    cout << "The puzzle you entered is: " << endl << endl;
    for(int i = 0; i < puzzleToSolve.size(); i++){
        cout << puzzleToSolve.at(i) << " ";

        if( ((i + 1) % 3) == 0){
            cout << endl;
        }
    }

    cout << endl << endl;
    return puzzleToSolve;
}

vector<int> puzzleMakerDefault(){

    vector<int> puzzleToSolve = {1, 2, 3, 4, 0, 5, 7, 8, 6};

    //output the default puzzle
    cout << "The default puzzle is: " << endl << endl;
    for(int i = 0; i < puzzleToSolve.size(); i++){
        cout << puzzleToSolve.at(i) << " ";

        if( ((i + 1) % 3) == 0){
            cout << endl;
        }
        
    }

    cout << endl << endl;
    return puzzleToSolve;
}