#include "OnlineDating.h"
#include "OnlineDating.cpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
void test(){
OnlineDating eliteSingles;
assert(eliteSingles.makeMatch("Kristin", "L", "kristinl@elitesingles.com"));
assert(eliteSingles.makeMatch("Mike", "W", "mikew@elitesingles.com"));
assert(eliteSingles.howManyMatches() == 2);
string first, last, e;
assert(eliteSingles.confirmMatch(0, first, last, e)&& e == "kristinl@elitesingles.com");
assert(eliteSingles.confirmMatch(1, first, last, e)  && (first == "Mike" && e == "mikew@elitesingles.com"));
    return;}
OnlineDating newlist;

int main(){

cout << "Passed all tests" << endl;
    return 0;}
