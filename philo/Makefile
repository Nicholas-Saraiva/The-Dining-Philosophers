CC = cc
CC_FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
OBJDIR = objs
NAME = philo

SRCS = main.c errors.c utils.c time.c routines.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all:$(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CC_FLAGS) $(SRCS) -o $(NAME) -pthread

$(OBJDIR):
	mkdir $(OBJDIR)
$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: clean all
