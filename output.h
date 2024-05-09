#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>
#include <vector>

using namespace std;

class Output
{
public:
    Output();
    void takeInput(string);
    string lastString();
    string toString();
private:
    vector<string> stringVector;
};

#endif // OUTPUT_H
