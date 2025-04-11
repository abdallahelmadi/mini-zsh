CC = cc
RM = rm -rf
NAME = minishell
LINKINGFLAGS = -lreadline
CFLAGS = -Wextra -Wall -Werror -I./
OBJECTS = minishell.o \
		  functions/prompt/prompt_branch.o functions/prompt/prompt_folder.o functions/prompt/prompt_zsh.o functions/parsin/parsin_global.o \
		  functions/utils/utils_split.o functions/utils/utils_charcmp.o functions/utils/utils_strdup.o functions/utils/utils_strjoin.o \
		  functions/signals/signals_sigint.o functions/utils/utils_strstr.o functions/utils/utils_split_pro.o functions/utils/utils_strstr_pro.o \
		  functions/utils/utils_strlen.o functions/utils/utils_nodes.o functions/utils/utils_free.o functions/utils/utils_docente.o \
		  functions/parsin/parsin_analyse_quotes.o functions/parsin/parsin_forbidden_keywords.o functions/parsin/parsin_make_list.o \
		  functions/parsin/pasrin_clean_list.o functions/parsin/parsin_tokenization.o functions/utils/utils_exit.o \
		  functions/builtin/builtin_cd.o functions/builtin/builtin_echo.o functions/builtin/builtin_env.o functions/builtin/builtin_exit.o \
		  functions/builtin/builtin_export.o functions/builtin/builtin_pwd.o functions/builtin/builtin_unset.o functions/utils/utils_strcmp.o \
		  functions/utils/utils_strncmp.o functions/execution/execution_global.o functions/execution/execution_syntax.o \
		  functions/utils/utils_env.o functions/utils/utils_getenv.o functions/parsin/parsin_global_variables.o functions/execution/execution_redirection.o

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
