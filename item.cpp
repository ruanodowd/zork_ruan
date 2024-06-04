#include "item.h"
#include "output.h"
Item::Item (string inDescription, int inWeightGrams, float inValue) {
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
}
Item::Item (string inDescription, int inWeightGrams, float inValue, int isTicket) {
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
    ticketBool = isTicket;
}
Item::Item(string inDescription) {
	description = inDescription;
}

void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
        cout << "";
        //output.takeInput("weight invalid, must be 0<weight<9999") ;
    else
	   weightGrams = inWeightGrams;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
        //output.takeInput("value invalid, must be 0<value<9999") ;
        cout << "";
    else
	   value = inValue;
}


string Item::getShortDescription()
{
	return description;
}

string Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}

