NAME				=		autoCompletion

CXX					=		g++

NOW 				:=	$(shell date +"%d %h %g:%R")

DEFAULT				=		"\033[00m"
GREEN				=		"\033[0;32m"
HIGHLIGHTED			=		"\033[2;102m"
HIGHLIGHTED_R			=		"\033[2;101m"
DELETION 			=		"\033[2;103m"
TEAL				=		"\033[1;34m"
RED					=		"\033[1;31m"
ECHO				=		/bin/echo -e

SRC_P	= ./src/
SRC		=	$(SRC_P)main.cpp \
			$(SRC_P)Address.cpp \
			$(SRC_P)Utils.cpp

OBJ					=		$(SRC:.cpp=.o)

CXXFLAGS			+= 	-Wall -Wextra -std=c++11 -g -fpic -pipe

INCLUDE				=	-I./include

all:		$(NAME) 

$(NAME):	$(OBJ)
		@$(CXX) $(OBJ) -o $(NAME)
		@$(ECHO) $(HIGHLIGHTED)"COMPILATION SUCCEEDED ON "$(NOW)$(DEFAULT)"\n"

clean:
		@$(RM) $(OBJ)
		@$(ECHO) $(DELETION)"OBJs PROPERLY DELETED"$(DEFAULT)

fclean:		clean
		@$(RM) $(NAME)
		@$(ECHO) $(DELETION)"BINARY PROPERLY DELETED"$(DEFAULT)

re:		fclean all

.PHONY:		all clean fclean re

.cpp.o:
		@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@  && \
		$(ECHO) $(GREEN) " [OK] " $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) " [XX] " $(TEAL) $< $(DEFAULT)