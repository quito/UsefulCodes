
NAME	=	GlRenderer

SRC	=	main.cpp \
		renderer.cpp \
		MultiCube.cpp 

CC	=	clang++

OBJ	=	$(SRC:.cpp=.o)

CFLAGS =	-w -Wall -Wextra -O3

LDFLAGS =	-lSDL -lGL -lGLU -lglut

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@