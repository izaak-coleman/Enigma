#include <iostream>

#include "errors.h"
#include "Errors.h"
#include "IOPanel.h"

using namespace std;

IOPanel::IOPanel()
{
  nextInput = 0;                            // set attribute to 0
  nextOutput = 0;                           // set attribute to 0
}

void IOPanel::getInputFromStream()
{
  cin.get(nextInput);                         // store class attribute
}

char IOPanel::passInputToEnigma()
{
  return nextInput;                         // return stored value
}

void IOPanel::storeLastOutput( char processedChar )
{
  nextOutput = processedChar;        // after encryption store cypher character
}

void IOPanel::printOutput()
{
  cout << nextOutput;               // print cypher text to stdout
}
