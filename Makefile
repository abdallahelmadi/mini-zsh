CC = cc
RM = rm -rf
NAME = minishell
LINKINGFLAGS = -lreadline
CFLAGS = -Wextra -Wall -Werror -I./
OBJECTS = minishell.o \
		  functions/prompt/git_branch.o functions/prompt/get_folder_name.o functions/prompt/readline_prompt.o functions/parsin/check_command_line.o \
		  functions/utils/utils_split.o functions/utils/utils_strcmp.o functions/utils/utils_strdup.o functions/utils/utils_strjoin.o \
		  functions/signals/signals_sigint.o functions/utils/utils_strstr.o functions/utils/utils_split_pro.o functions/utils/utils_strstr_pro.o \
		  functions/utils/utils_strlen.o

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