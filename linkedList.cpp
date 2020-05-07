#include "linkedList.h"
#include <vector>
#include <iostream>

using namespace std;

linkedList* createNode(vector<int> input, int g_n, int h_n){
    linkedList *node;      
    
    node = new linkedList; 
    node->next = NULL;      //actually dont need this
    node->gn = g_n;
    node->hn = h_n;
    node->cost = g_n + h_n;
    node->state = input;
    node->prev = NULL;
     
    return node;
}

void setNext(linkedList *source, linkedList *nextNode){
    source->next = nextNode;
}
