all :
	cc -Wextra -Wall -Werror *.c **/*.c -I./ -o minishell -lreadline