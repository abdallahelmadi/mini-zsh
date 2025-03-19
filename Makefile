CC = cc
RM = rm -rf
NAME = minishell
LINKINGFLAGS = -lreadline
CFLAGS = -Wextra -Wall -Werror -I./
OBJECTS = minishell.o \
		  functions/prompt/prompt_branch.o functions/prompt/prompt_folder.o functions/prompt/prompt_zsh.o functions/parsin/parsin_check.o \
		  functions/utils/utils_split.o functions/utils/utils_strcmp.o functions/utils/utils_strdup.o functions/utils/utils_strjoin.o \
		  functions/signals/signals_sigint.o functions/utils/utils_strstr.o functions/utils/utils_split_pro.o functions/utils/utils_strstr_pro.o \
		  functions/utils/utils_strlen.o functions/utils/utils_nodes.o functions/utils/utils_free.o

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