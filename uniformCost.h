#ifndef UNIFORMCOST_H_
#define UNIFORMCOST_H_

#include <vector>
#include <queue>
#include <functional>

using namespace std;

int expandedTotal;
int maxNodesinQueue;
bool uniformCostSearch(vector<int>);
void finalOutput(int, int);
bool goalChecker(vector<int>, vector<int>);




#endif