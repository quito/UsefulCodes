
NAME	=	GlRenderer

SRC	=	ThreadPool.cpp \
		main.cpp

CC	=	clang++

OBJ	=	$(SRC:.cpp=.o)

CFLAGS =	-W -Wall -Wextra -O3

LDFLAGS =	-lpthread

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean $(NAME)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@