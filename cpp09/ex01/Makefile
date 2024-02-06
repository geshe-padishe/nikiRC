NAME    = RPN

CC      = c++ -MMD

RM      = rm -rf

CFLAGS  = -Wall -Wextra -Werror -g3 -std=c++98 # -g3  -fsanitize=address

SRCS    = main.cpp

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

.PHONY : all clean fclean re
