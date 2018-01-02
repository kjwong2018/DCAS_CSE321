#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <map>
#include <utility>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>


char map[40][40];
std::pair<int,int> coordinates;
std::map<int,std::pair<int,int>> dest;
std::map<int,std::pair<int,int>> curr;
void updateMap();
void initialization();
bool check(int, int);
void move(int, int, char);
void *threading(void *threadID);
  // void setMap(int , int);
