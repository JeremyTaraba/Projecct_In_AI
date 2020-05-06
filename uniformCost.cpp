#include "uniformCost.h"
#include "linkedList.h"
#include <iostream>
#include <vector>
#include <queue>
#include <functional> //need for priority_queue to be used as min heap (greater<int>)

using namespace std;

bool compare(linkedList *lhs, linkedList *rhs){
    return lhs->cost < rhs->cost;
}

// this is an strucure which implements the 
// operator overlading 
struct compare { 
    bool operator()(linkedList *lhs, linkedList *rhs) 
    { 
        // return true if lhs is less than rhs
        return lhs->cost < rhs->cost;
    } 
}; 


bool uniformCostSearch(vector<int> puzzle){
    linkedList *curNode = createNode(puzzle, 0, NULL); //initial state with cost = 0 and parent = NULL

    //min cost queue
    priority_queue <linkedList, vector<linkedList>, compare> frontier;  

    //keep track of past puzzle states so we dont revisit them
    vector<int> explored;   

     //generate goal state for differing sizes of puzzles
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

    // while(1){
    //     if(frontier.empty()){
    //         return false;
    //     }
    //     curNode = createNode(frontier.top(), 0, parentNode);
    //     frontier.pop();
    //     if(goalChecker(curNode, goal)){
    //         return true;
    //     }
    //     explored.push(curNode);
    //     for(//each different move we can do based on 0){
    //         childNode = ;//one of the next actions we can do
    //         //for loop to check if child node is in frontier or if it is in explored
    //         //else frontier.push(childNode);
    //         //else if in frontier but the one in frontier has a higher path cost then replace it with this childNode
    //     }



    // }

    return true;
}

void finalOutput(int expandNodes, int queueNodes){
    cout << "goal!" << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << expandNodes << " nodes" << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << queueNodes << endl;

    return 0;
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

int main(){


    return 0;
}