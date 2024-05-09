#include "output.h"
#include "mainwindow.h"
#include <vector>
#include <string>
using std::string;

Output::Output() {
    vector<string> stringVector({});
    stringVector.push_back("Welcome to Zork");
    stringVector.push_back("Type a command in to enter");
}
void Output::takeInput(string s){
    stringVector.push_back(s);
}
string Output::lastString() {
    return stringVector[stringVector.size()];
}
string Output::toString(){
    string r;
    for (string s:stringVector){
        r = r + "\n" + s;
    }
    return r;
}
