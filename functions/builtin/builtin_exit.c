#include <minishell.h>

void	fun_exit(char *str)
{
	char **res;
	res = utils_split(str, ' ');
	if (utils_strstr(res[0], "exit"))
	{
		printf("exit\n");
		exit(SUCCESS);
	}
}