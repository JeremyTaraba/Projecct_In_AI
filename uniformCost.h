#ifndef UNIFORMCOST_H_
#define UNIFORMCOST_H_

#include <vector>
#include <queue>
#include <functional>

using namespace std;

bool uniformCostSearch(vector<int>);
void finalOutput(int, int);
bool goalChecker(vector<int>, vector<int>);
bool exploredChecker(vector<int>, vector<vector<int>>);
int findLocationOfZero(vector<int>);
vector<int> findMoves(int zeroLocation, int puzzleSize);
vector<int> possibleStates(vector<int>, vector<int>, int, int);


#endif