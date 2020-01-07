DEBUG		= no
CC 			= g++
CFLAGS 		= -Wall -Wextra -std=c++17
# If libXX.a or libXX.so, LDFLAGS = -lXX
# To adapt accordingly to the library we use
LDFLAGS 	=

BIN 		= ../bin
INCLUDES 	= ../include
# INCFLAGS also contains the path to the headers of the library if they exist
INCFLAGS 	= -I$(INCLUDES)
OBJDIR 		= .
SRCDIR 		= .
DOC			= ../doc
# LIB contains the path to the library
LIB 		= /usr/local/lib
LIBFLAGS	= -L$(LIB)

SRC 		= $(wildcard $(SRCDIR)/*.cpp)
OBJ 		= $(SRC:.cpp=.o)

EXEC 		= main


all: $(BIN)/$(EXEC)

$(BIN)/$(EXEC): $(SRC)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Compilation successful!"

# doxygen -g doxygen.cfg à faire dans le dossier doc
# Penser à vérifier les variables PROJECT_NAME, INPUT, RECURSIVE, OUTPUT_DIRECTORY dans doxygen.cfg
doc:
	doxygen $(DOCS)/doxygen.cfg

.PHONY: clean
clean:
	@rm -f $(BIN)/$(EXEC)
	@echo "The file" $(BIN)/$(EXEC) "has been successfully removed"

.PHONY: mrproper
mrproper: clean
	@rm -f $(OBJDIR)/$(OBJ)
