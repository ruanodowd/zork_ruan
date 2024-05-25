#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include "output.h"
#include <iostream>
#include <string>
using namespace std;
// pres namespace
class ZorkUL {
private:
	Parser parser;
	Room *currentRoom;
    Output output;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
	void goRoom(Command command);
    void createItems();
    void displayItems();

public:
	ZorkUL();
    //void play();
    bool update(std::string buffer);
	string go(string direction);
    string getLastOutput();
};

#endif /*ZORKUL_H_*/
