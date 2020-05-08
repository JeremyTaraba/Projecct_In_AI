#include "algorithms.h"
#include "linkedList.h"
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <stack>          

using namespace std;


//creates operator overloading for priority_queue
struct compare { 
    bool operator()(linkedList *lhs, linkedList *rhs) 
    { 
        // returns true when top of queue is less than what is under it
        return lhs->cost > rhs->cost;
    } 
}; 


const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

vector<int> costFunction(linkedList*, vector<int>, int);
vector<int> uniformCost(linkedList*);
vector<int> misplaceTile(linkedList*, vector<int>);
int misplaceTileCost(vector<int>, vector<int>);
int frontierCost(vector<int>, priority_queue <linkedList*, vector<linkedList*>, compare>);
vector<int> frontierCheckerAndCost(vector<int> nextState, priority_queue<linkedList*, vector<linkedList*>, compare> frontier);
bool frontierChecker(vector<int>, priority_queue<linkedList*, vector<linkedList*>, compare>);
priority_queue <linkedList*, vector<linkedList*>, compare> replaceFrontierElement(linkedList*, priority_queue <linkedList*, vector<linkedList*>, compare>);
void finalOutput(linkedList*, int, int);


bool generalAlgorithm(vector<int> puzzle, int algorithmType){
    linkedList *curNode = createNode(puzzle, 0, 0); //initial state with cost = 0 and parent = NULL

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
     int identicalFrontierCost;
     vector<int> possibleMoves;
     vector<int> nextState;
     int locationOfZero;
     bool inFrontier;
     bool inExplored;
     int nodeCost;
     int g_n;
     int h_n;
     vector<int> childNodeCost;
     int frontierMax = 0;

     //first iteration of while loop creates a copy of root node.
     //should create a deallocator function and manually delete root node so no leaks

    while(1){
        if(frontier.empty()){
            return false;
        }
        curNode = frontier.top();
        parentNode = frontier.top();
        if(frontierMax < frontier.size()){
            frontierMax = frontier.size();
        }

        frontier.pop();
        if(goalChecker(curNode->state, goal)){
            finalOutput(curNode, explored.size(), frontierMax);
            return true;
        }
        explored.push_back(curNode->state);

        locationOfZero = findLocationOfZero(curNode->state);
        possibleMoves = findMoves(locationOfZero, curNode->state.size());
        
        for(int i = 0; i < possibleMoves.size(); i++){

            nextState = possibleStates(parentNode->state, possibleMoves, i, locationOfZero); //one of the next states we can create 

            inFrontier = frontierChecker(nextState, frontier); 
            inExplored = exploredChecker(nextState, explored);


            if(!inFrontier && !inExplored){   //if child node is not in frontier and not in explored
                childNode = createNode(nextState, 0, 0);
                childNode->prev = parentNode;
                childNodeCost = costFunction(childNode, goal, algorithmType);
                childNode->gn = childNodeCost.at(0);  
                childNode->hn = childNodeCost.at(1);  
                childNode->cost = childNodeCost.at(2);
                frontier.push(childNode);
            }
            else if(inFrontier){     //else if in frontier but the one in frontier has a higher path cost then replace it with this childNode
                childNode = createNode(nextState, 0, 0);
                childNode->prev = parentNode;
                childNodeCost = costFunction(childNode, goal, algorithmType);
                nodeCost = childNodeCost.at(2);
                identicalFrontierCost = frontierCost(nextState, frontier);
                if(nodeCost < identicalFrontierCost){
                    childNode->gn = childNodeCost.at(0);  
                    childNode->hn = childNodeCost.at(1);  
                    childNode->cost = childNodeCost.at(2);
                    frontier = replaceFrontierElement(childNode, frontier);
                   
                }
            }
           
        }
    }

    //never reached
    return true;
}

//distance from initial state
vector<int> costFunction(linkedList *childNode, vector<int> goal, int algorithmType){
    vector<int> nodeCost;
   switch(algorithmType){
       case 1:
            nodeCost = uniformCost(childNode);
            break;
        case 2:
            nodeCost = misplaceTile(childNode, goal);
            break;
        case 3:
            //A*
            break;
        default:
            cout << "error in algorithmType" << endl;
   }
   return nodeCost;
}

vector<int> uniformCost(linkedList *childNode){
    vector<int> nodeCost;
    nodeCost.push_back(childNode->prev->gn + 1);
    nodeCost.push_back(0);
    nodeCost.push_back(childNode->prev->gn + 1 + childNode->prev->hn);
    return nodeCost;
}

vector<int> misplaceTile(linkedList *childNode, vector<int> goal){
    vector<int> nodeCost;
    int hn = misplaceTileCost(childNode->state, goal);
    nodeCost.push_back(childNode->prev->gn + 1);
    nodeCost.push_back(hn);
    nodeCost.push_back(childNode->prev->gn + 1 + hn);
    return nodeCost;
}

int misplaceTileCost(vector<int> puzzle, vector<int> goal){
    int misplaced = 0;     
    for(int i = 0; i < goal.size(); i++){
        if(puzzle.at(i) != goal.at(i)){
            misplaced++;
        }
    }

    return misplaced;
}

vector<int> possibleStates(vector<int> puzzle, vector<int> possibleMoves, int index, int locationOfZero){
    int indexOfZero = locationOfZero - 1;
    vector<int> changedPuzzle = puzzle;
    int blankSpace = changedPuzzle.at(indexOfZero);
    
    switch(possibleMoves.at(index)){    //checking if we move left, right, up, or down next
        case 0:     //case for moving 0 left
            changedPuzzle.at(indexOfZero) = changedPuzzle.at(indexOfZero - 1);
            changedPuzzle.at(indexOfZero - 1) = blankSpace;
            break;
        case 1:     //case for moving zero up
            changedPuzzle.at(indexOfZero) = changedPuzzle.at(indexOfZero - sqrt(changedPuzzle.size()));
            changedPuzzle.at(indexOfZero - sqrt(changedPuzzle.size())) = blankSpace;
            break;
        case 2:     //case for moving zero right
            changedPuzzle.at(indexOfZero) = changedPuzzle.at(indexOfZero + 1);
            changedPuzzle.at(indexOfZero + 1) = blankSpace;
            break;
        case 3:     //case for moving zero down
            changedPuzzle.at(indexOfZero) = changedPuzzle.at(indexOfZero + sqrt(changedPuzzle.size()));
            changedPuzzle.at(indexOfZero + sqrt(changedPuzzle.size())) = blankSpace;
            break;
        default:
            cout << "error!" << endl;
    }

    return changedPuzzle;
}

void finalOutput(linkedList* finalNode, int expandNodes, int queueNodes){
    stack<linkedList*> solutionPath;
    solutionPath.push(finalNode);
    vector<int> stateToPrint;

    while(finalNode->prev){
        finalNode = finalNode->prev;
        solutionPath.push(finalNode);
    }
    stateToPrint = solutionPath.top()->state;
    cout << endl <<"expanding state: " << endl;
    for(int i = 0; i < stateToPrint.size(); i++){
        cout << stateToPrint.at(i) << " ";
        if( ((i + 1) % 3) == 0){
            cout << endl;
        }
    }
    solutionPath.pop();
    cout << endl;

    while(!solutionPath.empty()){
        stateToPrint = solutionPath.top()->state;
        cout << "The best state to expand with g(n) = " << solutionPath.top()->gn << " and h(n) = " << solutionPath.top()->hn << " is " << endl;
        for(int i = 0; i < stateToPrint.size(); i++){
            cout << stateToPrint.at(i) << " ";
            if( ((i + 1) % 3) == 0){
                cout << endl;
            }
        }
        cout << endl;
        solutionPath.pop();
    }


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

bool frontierChecker(vector<int> nextState, priority_queue<linkedList*, vector<linkedList*>, compare> frontier){    //check that frontier doesnt get mess up when returned
    vector<int> inFrontier = frontierCheckerAndCost(nextState, frontier);
    return inFrontier.at(0);
}

int frontierCost(vector<int> nextState, priority_queue <linkedList*, vector<linkedList*>, compare> frontier){
    vector<int> cost = frontierCheckerAndCost(nextState, frontier);
    return cost.at(1);
}

vector<int> frontierCheckerAndCost(vector<int> nextState, priority_queue <linkedList*, vector<linkedList*>, compare> frontier){
    int countNotEqual = 0;
    vector<int> inFrontierAndCost;
    int sameStateCost;
    int frontierSize = frontier.size();
    priority_queue <linkedList*, vector<linkedList*>, compare> frontierCopy = frontier;

    vector<int> frontierState;
    for(int i = 0; i < frontierSize; i++){
        frontierState = frontierCopy.top()->state;
        for(int j = 0; j < frontierState.size(); j++){
            if(nextState.at(j) != frontierState.at(j)){
                countNotEqual++;
                break;
            }
        }
        if(i+1 != countNotEqual){
            sameStateCost = frontierCopy.top()->cost;
            break;
        }
        frontierCopy.pop();       
    }

    //if counter is  the same as frontier.size() then there was no 100% match
    if(countNotEqual == frontierSize){
        inFrontierAndCost.push_back(0);
    }
    else{
        inFrontierAndCost.push_back(1);
    }
    inFrontierAndCost.push_back(sameStateCost);

    return inFrontierAndCost;
}

//could use pass by reference here
priority_queue <linkedList*, vector<linkedList*>, compare> replaceFrontierElement(linkedList *childNode, priority_queue <linkedList*, vector<linkedList*>, compare> frontier){
    priority_queue <linkedList*, vector<linkedList*>, compare> changedFrontier;
    vector<int> nextState = childNode->state;

    int countNotEqual = 0;
    vector<int> frontierState;
    for(int i = 0; i < frontier.size(); i++){
        frontierState = frontier.top()->state;
        for(int j = 0; j < frontierState.size(); j++){
            if(nextState.at(j) != frontierState.at(j)){
                countNotEqual++;
                break;
            }
        }
        if(i != countNotEqual-1){
            frontier.pop();
        }
        else{
            changedFrontier.push(frontier.top());
            frontier.pop();
        }       
    }
    changedFrontier.push(childNode);


    return changedFrontier;
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
        possibleMoves.push_back(RIGHT);
        possibleMoves.push_back(DOWN);
    }
    else if(zeroLocation == (puzzleSize - sqrt(puzzleSize) + 1) ){     //if 0 is at the start of the last row
        possibleMoves.push_back(UP);
        possibleMoves.push_back(RIGHT);
    }
    else if( (zeroLocation > (puzzleSize - sqrt(puzzleSize) + 1) ) && (zeroLocation < puzzleSize) ){     //if 0 is between the bottom right corner and bottom left corner
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(UP);
        possibleMoves.push_back(RIGHT);
    }
    else{   //zero is not in the first or last rows and is somewhere in the rows between
        for(int i = 1; i < (sqrt(puzzleSize) - 1); i++){
            if(zeroLocation == (i*sqrt(puzzleSize) + 1) ){    //if 0 is start of a row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(RIGHT);
                possibleMoves.push_back(DOWN);
                break;
            }
            else if(zeroLocation == ((i+1)*sqrt(puzzleSize)) ){   //if 0 is end of a row
                possibleMoves.push_back(LEFT);
                possibleMoves.push_back(UP);
                possibleMoves.push_back(DOWN);
            }
            else if( (zeroLocation > (i*sqrt(puzzleSize) + 1)) && (zeroLocation < ((i+1)*sqrt(puzzleSize))) ){    //if 0 is between start and end of row
                possibleMoves.push_back(LEFT);
                possibleMoves.push_back(UP);
                possibleMoves.push_back(RIGHT);
                possibleMoves.push_back(DOWN);
            }
        }
    }
    

    return possibleMoves;
}