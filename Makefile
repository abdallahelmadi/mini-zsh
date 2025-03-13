CC = cc
RM = rm -rf
NAME = minishell
LINKINGFLAGS = -lreadline
CFLAGS = -Wextra -Wall -Werror -I./
OBJECTS = minishell.o \
		  functions/git_branch.o functions/get_folder_name.o functions/readline_prompt.o functions/check_command_line.o \
		  functions/utils/utils_split.o functions/utils/utils_strcmp.o functions/utils/utils_strdup.o functions/utils/utils_strjoin.o \
		  functions/signals/signals_sigint.o functions/utils/utils_strstr.o

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LINKINGFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	$(RM) $(OBJECTS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.SECONDARY : $(OBJECTS)