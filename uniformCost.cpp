#include "uniformCost.h"
//#include "linkedList.h"
#include <iostream>
#include <vector>
#include <queue>
#include <functional> //need for priority_queue to be used as min heap (greater<int>)

using namespace std;


bool uniformCostSearch(vector<int> puzzle){
    //linkedList *root = createNode(puzzle, 0); //initial state with cost = 0

    //min cost queue
    priority_queue <int, vector<int>, greater<int> > frontier;  
    frontier.push(10); 
    frontier.push(30); 
    frontier.push(20); 
    frontier.push(5); 
    frontier.push(1); 
    cout << "\ngquiz.top() : " << frontier.top(); 
    frontier.pop();

    //keep track of past puzzle states so we dont revisit them
    vector<int> explored;   

     //generate goal state for differing sizes of puzzles
     vector<int> goal;
     for(int i = 0; i < puzzle.size(); i++){
         if(i == puzzle.size() - 1){
            goal.push(0);
         }
         else{
            goal.push(i+1);
         }
     }

    //loop 
        //if frontier empty then return failure
        //pop frontier (lowest node cost in frontier is popped)
        //if node.state = solution then return solution
        //add node.state to explored

        //for each action you can do in the current state
            //child = child.node(problem,node,action)
            //if child.state is not in explored or frontier
                //frontier insert child into appropriate position
            //else if child.state is in frontier with higher cost
                //replace that frontier node with child

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