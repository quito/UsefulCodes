
NAME	=	GlRenderer

SRC	=	main.cpp \
		renderer.cpp

CC	=	clang++

OBJ	=	$(SRC:.cpp=.o)

CFLAGS =	-w -Wall -Wextra -ggdb

LDFLAGS =	-lSDL -lGL -lGLU

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@