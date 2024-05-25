#include "output.h"
#include "mainwindow.h"
#include <vector>
#include <string>
using std::string;

Output::Output() {
    vector<string> stringVector({});
}
void Output::takeInput(string s){
    stringVector.push_back(s);
}
string Output::lastString() {
    return stringVector[stringVector.size()-1];
}
string Output::toString(){
    string r;
    for (string s:stringVector){
        r = r + "\n" + s;
    }
    for (auto it = stringVector.rbegin(); it != stringVector.rend(); ++it) {
        cout << *it << " ";
    }
    return r;
}
