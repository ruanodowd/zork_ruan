#include <iostream>
#include <output.h>
using namespace std;
#include "ZorkUL.h"

/*int main(int argc, char* argv[]) {
	ZorkUL temp;
	temp.play();
	return 0;
}*/

ZorkUL::ZorkUL() {
	createRooms();
    printWelcome();
}

void ZorkUL::createRooms()  {
	Room *a, *b, *c, *d, *e, *f, *g, *h, *i;

    a = new Room("a");
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
	b = new Room("b");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
	c = new Room("c");
	d = new Room("d");
	e = new Room("e");
	f = new Room("f");
	g = new Room("g");
	h = new Room("h");
	i = new Room("i");

//             (N, E, S, W)
	a->setExits(f, b, d, c);
	b->setExits(NULL, NULL, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
	d->setExits(a, e, NULL, i);
	e->setExits(NULL, NULL, NULL, d);
	f->setExits(NULL, g, a, h);
	g->setExits(NULL, NULL, NULL, f);
	h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);

        currentRoom = a;
}

/**
 *  Main play routine.  Loops until end of play.
 */
/*
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
    output.takeInput("end");
}
*/

bool ZorkUL::update(std::string buffer) {
    // Create pointer to command and give it a command.
    Command* command = parser.getCommand(buffer);
    // Pass dereferenced command and check for end of game.
    bool finished = processCommand(*command);
    // Free the memory allocated by "parser.getCommand()"
    //   with ("return new Command(...)")
    delete command;

    return finished;
}

string ZorkUL::getLastOutput() {
    return output.toString();
}

void ZorkUL::printWelcome() {
    output.takeInput("Welcome to Mia's Adventure\n"
                     "click info for help\n"
                     + currentRoom->longDescription());

}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
        output.takeInput("What???");
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        output.takeInput("[h] --- [f] --- [g]\n"
                        "         |         \n"
                        "         |         \n"
                        "[c] --- [a] --- [b]\n"
                        "         |         \n"
                        "         |         \n"
                        "[i] --- [d] --- [e]\n");
		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
            output.takeInput("incomplete input");
        }
        else
         if (command.hasSecondWord()) {
            output.takeInput("you're trying to take " + command.getSecondWord());

        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            output.takeInput("item is not in room");
        else
            output.takeInput("item is in room");
            output.takeInput("index number " + location);
            output.takeInput(currentRoom->longDescription());
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
        output.takeInput("incomplete input");
        }
        else
            if (command.hasSecondWord()) {
            output.takeInput("you're adding " + command.getSecondWord());
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
            output.takeInput("overdefined input");
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
    output.takeInput("valid inputs are; ");
	parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
        output.takeInput("incomplete input");
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
        output.takeInput("underdefined input");
	else {
		currentRoom = nextRoom;
        output.takeInput(currentRoom->longDescription());
	}
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}
