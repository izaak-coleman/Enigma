OBJ=main.o Exceptions.o ErrorsHandle.o PlugBoard.o Reflector.o Rotor.o IOPanel.o EnigmaMachine.o
EXE=enigma
CXX=g++
COMPFLAGS=-Wall -ggdb -MMD
BODIES=./bodies/
HEADERS=./headers/
OBJDIR=./objects/

$(EXE):$(OBJ)
	$(CXX) $(COMPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(COMPFLAGS) -c $< 

-include $(OBJ:.o=.d)	

.PHONY: clean

clean:
	echo cleaning...
	mv ./*.o $(OBJDIR)
	mv ./*.d $(OBJDIR)

