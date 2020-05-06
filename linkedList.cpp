#include "linkedList.h"
#include <vector>
#include <iostream>

using namespace std;

linkedList* createNode(vector<int> input, int pathCost, linkedList *parent){
    linkedList *node;      
    
    node = new linkedList; 
    node->next = 0;  
    node->cost = pathCost;
    node->state = input;
    node->prev = parent;
     
    return node;
}

void setNext(linkedList *source, linkedList *nextNode){
    source->next = nextNode;
}
