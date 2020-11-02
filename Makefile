##
## EPITECH PROJECT, 2020
## CPP_plazza_2019
## File description:
## Makefile
##

NAME	= plazza

CC	= g++

RM	= rm -f

SRCS	=	./src/General_infos.cpp	\
	  		./src/Pizza/Pizza.cpp	\
	  		./src/Pizza/is_correct.cpp	\
	  		./src/Kitchen/Kitchen.cpp	\
			./src/Kitchen/Cook.cpp	\
			./src/Kitchen/IKitchen.cpp \
			./src/Kitchen/AKitchen.cpp \
	  		./src/Reception/Reception.cpp	\
	  		./src/Reception/Help.cpp	\
			./src/Reception/watchers.cpp \
	  		./src/tools/clean_str.cpp	\
	  		./src/tools/parsing.cpp	\
			./src/tools/clock.cpp	\
	  		./src/Play/loop_plazza.cpp	\
			./src/Ftp/ftp.cpp \
	  		./src/main.cpp	\

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./include/
CPPFLAGS += -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -pthread -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug:	CPPFLAGS += -g
debug:	re

.PHONY: all clean fclean re debug
