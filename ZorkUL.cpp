#include <iostream>
#include <output.h>
using namespace std;
#include "ZorkUL.h"



ZorkUL::ZorkUL() {
	createRooms();
    printWelcome();
}

void ZorkUL::createRooms()  {
    Room *lmk, *shn, *dub, *lon, *vie, *jes, *bgd, *zgb;
    //pointers
    lmk = new Room("Limerick");
        lmk->addItem(new Item("bus_ticket", 1, 11));
        lmk->addItem(new Item("knife", 2, 22));
    shn = new Room("Shannon");
        shn->addItem(new Item("plane_ticket", 3, 33));
        shn->addItem(new Item("duty_free_cigarettes", 4, 44));
    dub = new Room("Dublin");
    lon = new Room("London");
    vie = new Room("Vienna");
    jes = new Room("Jesenice");
    bgd = new Room("Belgrade");
    zgb = new Room("Zagreb");

//             (N, E, S, W)
    lmk->setExits(NULL, dub, NULL, shn);
    shn->setExits(NULL, NULL, lon, lmk);
    dub->setExits(NULL, lmk, vie, NULL);
    lon->setExits(shn, bgd, NULL, NULL);
    vie->setExits(dub, NULL, jes, NULL);
    jes->setExits(vie, NULL, zgb, NULL);
    bgd->setExits(lon, NULL, NULL, zgb);
    zgb->setExits(NULL, NULL, NULL, NULL);

        currentRoom = lmk;
}


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
    output.takeInput(
                    "(Based on a true story)\n"
                    "It's the 23rd of December\n"
                    "you need to get to Croatia by Christmas Eve\n"
                    "but you've overslept your direct flight...\n"
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
        output.takeInput(
"             ┌───Dublin               \n"
"             │     │                  \n"
"             │     │                  \n"
"Shannon───Limerick │                  \n"
"   │               │                  \n"
"   └───────────────┼───London─────┐   \n"
"                   │              │   \n"
"                   └─────Vienna   │   \n"
"                           │      │   \n"
"                      ─────┘      │   \n"
"                   Jesenice       │   \n"
"                      │           │   \n"
"                      │           │   \n"
"                   Zagreb─────Belgrade\n"
                         );
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
            output.takeInput("item is not in city");
        else
            output.takeInput("item is in city");
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
