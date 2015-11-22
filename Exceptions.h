#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class ExceptionBase
{
/* ExceptionBase contains contains exception error messages that are
 * output to the stderror stream. Derived classes contain the specific
 * error messages for the various exceptions that can be raised.
 * Upon identification of an error by various Errors class functions,
 * these derived classes are thrown and then caught in main.
 * The correct error handling routine is then carried out in main. */
  
public:

  ExceptionBase( int exception ); // sets @exceptionCode
  /* sets @exceptionCode only. This construtor is called for 
   * exceptions where the file name is not required. */

  ExceptionBase( int exception, const char *fileName ); 
  /* Sets @execeptionCode and initializes the @fileName attribute.
   * This construtor is called where the exception requires the file
   * to be specified. */
  
  virtual void exceptionMsg();
  /* Outputs an error message dependent on the derived class
   * and requires no file name.*/

  virtual void exceptionMsg( const char *fileName );
  /* Outputs an exception message dependant on the derived class
   * and requires a file name. */
  
  int getExceptionCode();
  /* Returns the value assigned to @exceptionCode */

  const char* getFileName();
  /* Returns the string assigned to @fileName*/

  int exceptionCode; 
  /* Value corresponding to the exception thrown, that needs to 
   * be returned to main. */

  const char *fileName;
  /*File name which caused the exception to be thrown*/
};



class InsuffParamsExptn: public ExceptionBase
{
  /* Thrown with:
   *  INSUFFICIENT_NUMBER_OF_PARAMETERS*/

public:
  InsuffParamsExptn( int exception, bool rotorError );
  InsuffParamsExptn( int exception, const char *fileName );
  
  void exceptionMsg();
  void noRotExceptionMsg();
  /* Outputs an error message specific to the case
   * where a .pos file was given, but no/not enough
   * .rot files were given */

  bool insuffRotor;
};



class ImposConfigExptn: public ExceptionBase
{
  /* Thrown with:
   *  IMPOSSIBLE_PLUGBOARD_CONFIGURATION
   *  INVALID_ROTOR_MAPPING
   *  INVALID_REFLECTOR_MAPPING*/
public:
  ImposConfigExptn( int exception, const char *fileName );

private:
  void exceptionMsg( const char *fileName );
  /* Used when file contains a self or double connection*/
};



class IncorNumParamsExptn: public ExceptionBase
{
  /* Thrown with:
   *  INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
   *  INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS*/
public:
  IncorNumParamsExptn( int exception, const char *fileName );

private:
  void exceptionMsg( const char *fileName );
  /* Called when reflector file or plugboard file contain
   * an unpaired contact*/
};



class NoRotStartPosExptn: public ExceptionBase
{
  /* Thrown with:
   *  NO_ROTOR_STARTING_POSITION*/
public:
  NoRotStartPosExptn( int exception );

private:
  void exceptionMsg();
  /* Message describes that the .pos file does not contain
   * enough rotor values*/
};



class InvalidIndexExptn: public ExceptionBase
{
  /* Thrown with:
   *  INVALID_INDEX*/
public:
  InvalidIndexExptn( int exception, const char *fileName );

private:
  void exceptionMsg( const char *fileName );
  /* Message describes that a value read in from @fileName contains
   * an integer value that was out of range 0-25.*/
};



class NonNumCharExptn: public ExceptionBase
{
  /*Thrown with:
   * NON_NUMERIC_CHARACTER*/
public:
  NonNumCharExptn( int exception, const char *fileName );

private:
  void exceptionMsg( const char *fileName );
   /* Message describes that a value read in from @fileName was
    * not a digit.*/
};



class FileOpenErrExptn: public ExceptionBase
{
  /*Thrown with:
   * ERROR_OPENING_FILE_CONFIGURATION*/
public:
  FileOpenErrExptn( int exception, const char *fileName );

private:
  void exceptionMsg( const char *fileName );
  /* Message describes that the file could not be opened. */
};



class InvUserInputExptn: public ExceptionBase
  /*Thrown with:
   * INVALID_INPUT_CHARACTER*/
{
public:
  InvUserInputExptn( int exception );

private:
  void exceptionMsg();
 /* Message descibes that the input was not uppercase Alpha*/
};

#endif
