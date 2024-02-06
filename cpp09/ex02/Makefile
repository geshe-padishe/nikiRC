NAME    = PmergeMe

CC      = c++ -MMD

RM      = rm -rf

CFLAGS  = -Wall -Wextra -Werror -g3 -std=c++98 # -g3  -fsanitize=address

SRCS    = main.cpp PmergeMe.cpp

OBJS	= $(SRCS:.cpp=.o)

DPD     = $(SRCS:.cpp=.d)

all: $(NAME)

-include $(DPD)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -I. $(OBJS) -o $(NAME)

%.o: %.cpp
		$(CC) $(CFLAGS) -MMD -o $@ -c $<

clean:
		${RM} $(OBJS) $(DPD)

fclean: clean
		${RM} $(NAME)

re: fclean all

max_shuf=500
example=17 5 6 11 29 9 15 14 18 2 27 16 0 13 25 12 4 30 22 24 10 19 23 20 7 3 28 21 1 26 8

shuf = $(shell shuf -i 0-${max_shuf} | tr '\n' ' ')
#shuf = ${example}
test:
		./PmergeMe ${shuf}

.PHONY : all clean fclean re
