FUNCTIONS IN THE PROGRAM:

Initialization():
Generate a char map[40][40] with 'A' on the top left as airport and all '*' then generate 10 random destination to put on the map and then store them into a std::map with its corresponding drone as std::map<int, pair<int,int>> name dest. The function also store the 10 drones initial location as (0,0) and stores it into a std::map<int, pair<int,int>> name curr.

updateMap():
Form feed then print out a 40x40 world using from char map[40][40].
(**updateMap update output on screen every 1.3 sec**)

check():
The function has input of (int x, int y) where x and y is the coordinate that a drone wants to move. It checks for character '>','<','^','v' and '\0' where null is to prevent the drones from flying off the map and it returns a boolean.

move():
The function is void and it takes in (int x, int y, char d) where x and y is the coordinate that the drone wants to move and d is the character('>','<','^','v') that will be inserted into the map. It will also check if the location that the drone wants to move is either a Airport, or destination so that it will still move to the location but instead of displaying the drones, it will display the airport or destination.

threading():
This is the thread function in pthread_create. Its a complex function with a bunch of if else statement that handles avoid collision, drone movement from airport to destination and back. Each thread uses its id to find the path to destination and update the length of the path every move. It checks if a drone is in its next path and base on the boolean return by check, changes its course so that it doesn't collide with other drones.After the drone arrive at its location, it sets its new location as the airport and start moving to the airport.
(**Thread uses 2 while loop to move x axis first then y axis second if possible. It also wait for 1 sec after every move and ofstream its position into a output.txt file.**)

main():
This is the main function where the magic happens. It first call initialization() then create a thread for updateMap() then create 10 drones thread, wait for 10 drones thread to finish then stop printing and let updateMap's thread exit then free everything before closing the program.


EXECUTING THE PROGRAM:

To run the simulation:
-Type in "make clean" to clean everything that was created before. The make file uses rm -rf dcas output.txt to clean remove dcas and output.txt
-Type in "make" to compile and create an executable call dcas for you to run. The make file uses g++ -std=c++11 -O2 -Wall DCAS.cpp -o dcas -lpthread to compile.
-Type in "./dcas" to run the simulation and the coordinates of the drones will be in the output.txt with ASCII World display in prompt.
-To kill the program at any time, you can just do CTRL + C. The simulation will automatically stop running when all drones did a full cycle.
