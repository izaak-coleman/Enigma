# Enigma
Program inspired by german enigma machine. Allows cypher text generation. 

Enigma was a cypher machine used by the German Forces in WW2. 
A 'key' must be used in order to decypher the cyphertext produced by an enigma
machine. This key is the configuration setting for the rotors.
When an individual wished to encrypt some plain text, he/she would set the
enigma machine to todays configurations, encode the text into cyphertext and 
send it. Upon recival of this cyphertext, a person wishing to decrypt the message
would enter it, letter by letter, into his/her enigma machine that was configured
with exactly the same settings as the enigma machine used to generate 
the cyphertext.

This Enigma program follows the same principles. Users must ensure the same 
settings in order to translate from plain to cyphertext and from cypher to 
plaintext.

This program expands the functionality of the Enigma machine, as 
it allows for a very large number of rotors - 2,147,483,647 rotors can be used, 
instead of the five rotors that can be used in the original enigma machine.

The files to configure the machine must be passed as follows
/enigma <plugboard> <reflector> <rotor1> <rotorx> <rotorstartposition>

The various config files should contain numbers. 0 representing 'A',
25 representing 'Z'. 

In order to use:

1) download zip
2) unzip and add ./objects dir
3) run gnu make
4) run make clean - puts all the object file in the ./object dir
5) run enigma executable using the argument syntax specified above

Example plugboards(.pb), reflectors(.rf), rotors(.rot), and rotorstartposition
(.pos) files can be found in the respective directories. These are usefull
examples. Make a billion or two yourself, for extra security ;)

-- Better explantion of config files coming shortly


  
