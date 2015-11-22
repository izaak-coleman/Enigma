#include <iostream>

#include "Exceptions.h"

using namespace std;

/*------------------- ExceptionBase Class -----------------------------------*/
ExceptionBase::ExceptionBase( int exception ): exceptionCode(exception)
{
  fileName = NULL;                // safe point to NULL
}

ExceptionBase::ExceptionBase( int exception,  const char *fileName ): 
  exceptionCode(exception), fileName(fileName){}


/* Base exception messages are empty, usually only one is overwritten
   per derived class, so when the non-overwritten @exptionMsg(...)
   is called in the catch statment nothing is output*/
void ExceptionBase::exceptionMsg(){}
void ExceptionBase::exceptionMsg( const char *fileName ){}


int ExceptionBase::getExceptionCode(){

  return exceptionCode; // has value of error code in errors.h
}

const char* ExceptionBase::getFileName()
{
  return fileName;  // filename of file that caused error
}



/*------------------- InsuffParamsExptn Class -------------------------------*/
InsuffParamsExptn::InsuffParamsExptn( int exception, bool rotorError ): 
  ExceptionBase( exception ), insuffRotor( rotorError )
{
}

InsuffParamsExptn::InsuffParamsExptn( int exception,  const char *fileName ):
  ExceptionBase( exception, fileName ){}

void InsuffParamsExptn::exceptionMsg()
{
  cerr << endl << endl;
  cerr << "Insufficient config files provided." << endl
       << "Please provide at least plugboard and reflector files."
       << endl;
  cerr << "usage: ./enigma <plugboard.pl> <reflector.rf> <rotor.rot>"
       << "... <rotorConfig.pos>" << endl;
  cerr << "Program terminating." << endl;
}

void InsuffParamsExptn::noRotExceptionMsg()
{
  cerr << endl << endl;
  cerr << "Insufficient rotor files provided." << endl
       << "If .pos file provided, please provide a rotor" << endl
       << "file for each rotor configuration value in .pos" << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- ImposConfigExptn Class --------------------------------*/
ImposConfigExptn::ImposConfigExptn( int exception, const char *fileName ): 
  ExceptionBase( exception, fileName ){}

void ImposConfigExptn::exceptionMsg( const char *fileName )
{
  cerr << endl << endl;
  cerr <<  fileName << " contains either too few mappings, or" << endl
       << "contains a contact that are mapped incorrectly." << endl;
  cerr << "Each contact can only map to one other contact" << endl
       << "and not with itself." << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- IncorNumParamsExptn Class -----------------------------*/
IncorNumParamsExptn::IncorNumParamsExptn(int exception, const char *fileName): 
  ExceptionBase( exception, fileName ){}

void IncorNumParamsExptn::exceptionMsg( const char *fileName )
{
  cerr << endl << endl;
  cerr << fileName << " file contains a contact without a" << endl
       << "partner contact. All contacts must be paired." << endl
       << "File should contain 13 pairs in total." << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- NoRotStartPosExptn Class ------------------------------*/
NoRotStartPosExptn::NoRotStartPosExptn( int exception ): 
  ExceptionBase( exception ){}

void NoRotStartPosExptn::exceptionMsg()
{
  cerr << endl << endl;
  cerr << "The provided rotor config does not contain" << endl
       << "enough configurations for the" << endl
       << "number of rotor files provided." << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- InvalidIndexExptn Class -------------------------------*/
InvalidIndexExptn::InvalidIndexExptn( int exception, const char *fileName ): 
  ExceptionBase( exception, fileName ){}

void InvalidIndexExptn::exceptionMsg( const char *fileName )
{
  cerr << endl << endl;
  cerr << "A configuration value in file " << fileName << endl
       << "was not within range 0-25" << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- NonNumCharExptn Class ---------------------------------*/
NonNumCharExptn::NonNumCharExptn( int exception, const char *fileName ): 
  ExceptionBase( exception, fileName ){}

void NonNumCharExptn::exceptionMsg( const char *fileName )
{
  cerr << endl << endl;
  cerr << "A configuration value in file " << fileName << endl
       << "was a non numeric value." << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- FileOpenErrExptn Class --------------------------------*/
FileOpenErrExptn::FileOpenErrExptn( int exception, const char *fileName ): 
  ExceptionBase( exception, fileName ){}

void FileOpenErrExptn::exceptionMsg( const char *fileName )
{
  cerr << endl << endl;
  cerr << "Error occured while opening " << fileName << " file." << endl;
  cerr << "Program terminating." << endl;
}



/*------------------- InvUserInputExptn Class -------------------------------*/
InvUserInputExptn::InvUserInputExptn( int exception ): ExceptionBase(exception)
{}

void InvUserInputExptn::exceptionMsg()
{
  cerr << endl << endl;
  cerr << "Invalid input into enigma keyboard. Only Uppercase" << endl
       << "characters can be input into enigma." << endl;
  cerr << "Program terminating." << endl;
}
