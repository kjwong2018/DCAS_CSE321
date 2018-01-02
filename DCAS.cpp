#include "DCAS.h"
// using namespace std;

//Global variable
pthread_t upthread[10];
pthread_t printhread;
pthread_mutex_t mutexdrone;
bool printMap = true;
// Initialization
void initialization(){
  for(int y=0;y<40;y++){
    for(int x=0;x<40;x++){
      if (x==0&&y==0){
        map[x][y]= 'A';
      }else{
        map[x][y]='*';
      }
    }
  }
  srand(time(NULL));
  for(int i=0;i<10;i++){
    // int z = rand() % 1000;
    // srand(z);
    int x = rand() % 40;
    int y = rand() % 40;
    map[x][y] = 'd';
    coordinates = std::make_pair(x,y);
    dest[i] = coordinates;            // destination for each drones set
    coordinates = std::make_pair(0,0);
    curr[i] = coordinates;            // current position for each drones set
  }
};
// end of Initialization

void *updateMap(void* ){
  while(printMap){
    std::cout<< "\f\n";
    for(int y=0;y<40;y++){
      for(int x=0;x<40;x++){
        std::cout << map[x][y];
      }
      std::cout << "\n";
    }
    // pthread_mutex_lock(&mutexdrone);
    // std::ofstream output;
    // output.open("output.txt", std::ios_base::app);
    // output<<"\n";
    // output.close();
    // pthread_mutex_unlock(&mutexdrone);
    usleep(1300000);
  }
  pthread_exit(0);
}
bool check(int x, int y){
  char c = map[x][y];
  if(c == '>'||c == '<'||c == 'v'||c == '^'||c == '\0'){
    return false;
  }
  else{
    return true;
  }
}
void move(int x, int y, char d){
  if(map[x][y]!= 'A' && map[x][y]!= 'D' && map[x][y]!='d'){
    map[x][y] = d;
  }
  if(d == '>'){
    if(map[x-1][y]!='A'&& map[x-1][y]!='D' && map[x-1][y]!='d'){
      map[x-1][y] = '*';
    }
  }
  else if(d == '<'){
    if(map[x+1][y]!='A' && map[x+1][y]!='D' && map[x+1][y]!='d'){
      map[x+1][y] = '*';
    }
  }
  else if(d == '^'){
    if(map[x][y+1]!='A' && map[x][y+1]!='D' && map[x][y+1]!='d'){
      map[x][y+1] = '*';
    }
  }
  else if(d == 'v'){
    if(map[x][y-1]!='A' && map[x][y-1]!='D' && map[x][y-1]!='d'){
      map[x][y-1] = '*';
    }
  }
}
void *threading(void *threadID){
  int id = (intptr_t)threadID;
  bool moved = false;
  for(int i = 0; i < 2; i++){
    while(dest[id].second - curr[id].second != 0){
      if(dest[id].second - curr[id].second > 0){
        pthread_mutex_lock(&mutexdrone);
        if(check(curr[id].first,curr[id].second+1)){
          move(curr[id].first,curr[id].second+1,'v');
          moved = true;
        }
        pthread_mutex_unlock(&mutexdrone);
        if(moved){
          curr[id].second = curr[id].second + 1;
          moved = false;
        }
        else{
          if(dest[id].first - curr[id].first >0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first+1,curr[id].second)){
              move(curr[id].first+1,curr[id].second,'>');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first + 1;
              moved = false;
            }
          }
          else if(dest[id].first - curr[id].first<0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first-1,curr[id].second)){
              move(curr[id].first-1,curr[id].second,'<');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first - 1;
              moved = false;
            }
          }
        }
      }
      else if(dest[id].second - curr[id].second < 0){
        pthread_mutex_lock(&mutexdrone);
        if(check(curr[id].first,curr[id].second-1)){
          move(curr[id].first,curr[id].second-1,'^');
          moved = true;
        }
        pthread_mutex_unlock(&mutexdrone);
        if(moved){
          curr[id].second = curr[id].second - 1;
          moved = false;
        }
        else{
          if(dest[id].first - curr[id].first >0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first+1,curr[id].second)){
              move(curr[id].first+1,curr[id].second,'>');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first + 1;
              moved = false;
            }
          }
          else if(dest[id].first - curr[id].first<0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first-1,curr[id].second)){
              move(curr[id].first-1,curr[id].second,'<');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first - 1;
              moved = false;
            }
          }
        }
      }
      pthread_mutex_lock(&mutexdrone);
      std::ofstream output;
      output.open("output.txt", std::ios_base::app);
      output<<"Drone: "<<id<<" ("<<curr[id].first<<" , "<<curr[id].second<<")\n";
      output.close();
      pthread_mutex_unlock(&mutexdrone);
      usleep(1000000);
    }
    while(dest[id].first - curr[id].first !=0){
      if(dest[id].first - curr[id].first >0){
        pthread_mutex_lock(&mutexdrone);
        if(check(curr[id].first+1,curr[id].second)){
          move(curr[id].first+1,curr[id].second,'>');
          moved = true;
        }
        pthread_mutex_unlock(&mutexdrone);
        if(moved){
          curr[id].first = curr[id].first + 1;
          moved = false;
        }
        else{
          if(dest[id].first - curr[id].first >0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first+1,curr[id].second)){
              move(curr[id].first+1,curr[id].second,'>');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first + 1;
              moved = false;
            }
          }
          else if(dest[id].first - curr[id].first<0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first-1,curr[id].second)){
              move(curr[id].first-1,curr[id].second,'<');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first - 1;
              moved = false;
            }
          }
        }
      }
      else if(dest[id].first - curr[id].first<0){
        pthread_mutex_lock(&mutexdrone);
        if(check(curr[id].first-1,curr[id].second)){
          move(curr[id].first-1,curr[id].second,'<');
          moved = true;
        }
        pthread_mutex_unlock(&mutexdrone);
        if(moved){
          curr[id].first = curr[id].first - 1;
          moved = false;
        }
        else{
          if(dest[id].first - curr[id].first >0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first+1,curr[id].second)){
              move(curr[id].first+1,curr[id].second,'>');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first + 1;
              moved = false;
            }
          }
          else if(dest[id].first - curr[id].first<0){
            pthread_mutex_lock(&mutexdrone);
            if(check(curr[id].first-1,curr[id].second)){
              move(curr[id].first-1,curr[id].second,'<');
              moved = true;
            }
            pthread_mutex_unlock(&mutexdrone);
            if(moved){
              curr[id].first = curr[id].first - 1;
              moved = false;
            }
          }
        }
      }
      pthread_mutex_lock(&mutexdrone);
      std::ofstream output;
      output.open("output.txt", std::ios_base::app);
      output<<"Drone: "<<id<<" ("<<curr[id].first<<" , "<<curr[id].second<<")\n";
      output.close();
      pthread_mutex_unlock(&mutexdrone);
      usleep(1000000);
    }
    if(i == 0){
      pthread_mutex_lock(&mutexdrone);
      map[curr[id].first][curr[id].second]= 'D';
      pthread_mutex_unlock(&mutexdrone);
      dest[id].first = 0;
      dest[id].second = 0;
    }
  }
  pthread_exit(0);
}
int main(){
  initialization();
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_mutex_init(&mutexdrone,NULL);

  pthread_create(&printhread,&attr,updateMap,NULL);
  for(int i = 0; i < 10; i++){
    pthread_create(&upthread[i], &attr, threading, (void *) (intptr_t) i);
  }
  pthread_attr_destroy(&attr);
  for(int i = 0; i < 10; i++){
    pthread_join(upthread[i], NULL);
  }
  printMap = false;
  pthread_join(printhread,NULL);
  pthread_mutex_destroy(&mutexdrone);
  pthread_exit(0);
}
