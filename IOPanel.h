#ifndef USERIOPANEL_H
#define USERIOPANEL_H

class IOPanel
{

/*IOPanel performs the input and output from and to the enigma machine. */
  public:

  IOPanel();
  /* initializes input and output variables to zero*/

  void getInputFromStream();
  /* Loads a single character from standard in, ready to be entered
   * into the enigma machine. */

  void storeLastOutput( char processedChar );
  /* Passes a character passed through the enigma machine as 
   * @processedChar and sets this to the value of @nextOutput, 
   * ready to be output to stdout*/

  char passInputToEnigma();
  /* Returns character stored in @nextInput, used to be passed to the
   * enigma machine.*/

  void printOutput();
  /* Prints @nextOutput to stdout*/

private:
  char nextInput;
  /* Contains the next input char from stdin */

  char nextOutput;
  /* Contains next char to be output via stdcout*/

};
#endif
