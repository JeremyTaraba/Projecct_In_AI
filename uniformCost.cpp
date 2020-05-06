#include "uniformCost.h"
#include "linkedList.h"
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

//creates operator overloading for priority_queue
struct compare { 
    bool operator()(linkedList *lhs, linkedList *rhs) 
    { 
        // returns true where top of queue is less than what is under it
        return lhs->cost > rhs->cost;
    } 
}; 


bool uniformCostSearch(vector<int> puzzle){
    linkedList *curNode = createNode(puzzle, 0, NULL); //initial state with cost = 0 and parent = NULL

    //min cost queue
    priority_queue <linkedList*, vector<linkedList*>, compare> frontier;  

    //keep track of past puzzle states so we dont revisit them
    vector<vector<int>> explored;   

     //generate goal state based on differing sizes of puzzles
     vector<int> goal;
     for(int i = 0; i < puzzle.size(); i++){
         if(i == puzzle.size() - 1){
            goal.push_back(0);
         }
         else{
            goal.push_back(i+1);
         }
     }


     frontier.push(curNode);
     linkedList *parentNode = NULL;
     linkedList *childNode;

     //first iteration of while loop creates a copy of root node.
     //should create a deallocator function and manually delete root node so no leaks

    // while(1){
    //     if(frontier.empty()){
    //         return false;
    //     }
    //     curNode = createNode(frontier.top()->state, 0, parentNode);
    //     frontier.pop();
    //     if(goalChecker(curNode->state, goal)){
    //         return true;
    //     }
    //     explored.push_back(curNode->state);
    //     for(//each different move we can do based on 0){
    //         childNode = ;//one of the next states we can create
    //         //for loop to check if child node is in frontier or if it is in explored
    //         //else frontier.push(childNode);
    //         //else if in frontier but the one in frontier has a higher path cost then replace it with this childNode
    //     }


    return true;
}

void finalOutput(int expandNodes, int queueNodes){
    cout << "goal!" << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << expandNodes << " nodes" << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << queueNodes << endl;
}

bool exploredChecker(vector<int> curNode, vector<vector<int>> explored){
    int exploreCounter = 0;     //keeps track of how many puzzles we checked

    for(int i = 0; i < explored.size(); i++){
        for(int j = 0; j < explored.at(i).size(); j++){
            if(curNode.at(j) != explored.at(i).at(j)){
                exploreCounter++;
                break;
            }
        }
    }

    //we went through all puzzles in explored. if not equal then we had a match so return true
    return exploreCounter != explored.size();
}


bool goalChecker(vector<int> puzzle, vector<int> goal){
    bool goalReached = true;
    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle.at(i) != goal.at(i)){
            goalReached = false;
            break;
        }
    }
    return goalReached;
}

int findLocationOfZero(vector<int> puzzle){
    int moveCase = 1;

    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle.at(i) == 0){
            break;
        }
        moveCase++;
    }

    return moveCase;
}

vector<int> findMoves(int zeroLocation, int puzzleSize){
    vector<int> possibleMoves;

    if(zeroLocation == 1){          //means if 0 is in top left corner
        possibleMoves.push_back(RIGHT);
        possibleMoves.push_back(DOWN);
    }
    else if(zeroLocation == puzzleSize){       //if 0 is in bottom right corner
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(UP);
    }
    else if(zeroLocation == sqrt(puzzleSize)){     //if 0 is at the end of the first row
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(DOWN);
    }
    else if( (zeroLocation > 1) && (zeroLocation < sqrt(puzzleSize)) ){     //if 0 is between the top left corner and end of first row
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(DOWN);
        possibleMoves.push_back(RIGHT);
    }
    else if(zeroLocation == (puzzleSize - sqrt(puzzleSize)) ){     //if 0 is at the start of the last row
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(DOWN);
    }
    else if( (zeroLocation > (puzzleSize - sqrt(puzzleSize)) ) && (zeroLocation < puzzleSize) ){     //if 0 is between the bottom right corner and bottom left corner
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(UP);
        possibleMoves.push_back(RIGHT);
    }
    else{   //zero is not in the first or last rows and is somewhere in the rows between
        for(int i = 1; i < (1-sqrt(puzzleSize)); i++){
            if(zeroLocation == (i*sqrt(puzzleSize) + 1) ){    //if 0 is start of a row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(RIGHT);
                possibleMoves.push_back(DOWN);
                break;
            }
            else if(zeroLocation == ((i+1)*sqrt(puzzleSize)) ){   //if 0 is end of a row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(LEFT);
                possibleMoves.push_back(DOWN);
            }
            else if(zeroLocation > (i*sqrt(puzzleSize) + 1) && zeroLocation < ((i+1)*sqrt(puzzleSize))){    //if 0 is between start and end of row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(LEFT);
                possibleMoves.push_back(RIGHT);
                possibleMoves.push_back(DOWN);
            }
        }
    }
    

    return possibleMoves;
}




int main(){
    vector<int> puzzle = {1,2,3,4,5,6,7,8,0};
    vector<int> puzzle2 = {0,2,3,4,5,6,7,8,1};

    vector<vector<int>> explored;      

    linkedList* curNode = createNode(puzzle, 5, NULL);
    linkedList* curNode2 = createNode(puzzle2, 7, NULL);
    linkedList* curNode3 = createNode(puzzle, 3, NULL);
    priority_queue <linkedList*, vector<linkedList*>, compare> frontier;  
    frontier.push(curNode);
    frontier.push(curNode2);
    frontier.push(curNode3);
    cout << "top = " << frontier.top()->cost << endl;
    frontier.pop();
    cout << "next = " << frontier.top()->cost << endl;
    frontier.pop();
    cout << "last = " << frontier.top()->cost << endl;

    explored.push_back(curNode->state);
    if(exploredChecker(curNode2->state, explored)){
        cout << "we explored puzzle2 already" << endl;
    }
    else{
        cout << "we have -not- explored puzzle2 already" << endl;
    }
    if(exploredChecker(curNode3->state, explored)){
        cout << "we explored puzzle already" << endl;
    }
    else{
        cout << "we have -not- explored puzzle already" << endl;
    }


    


    if(goalChecker(curNode->state, puzzle)){
        cout << "Goal!!" << endl;
    }
    else{
        cout << "no goal" << endl;
    }



    return 0;
}