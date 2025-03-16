#include <minishell.h>

extern char **environ;
void	fun_env(char *str)
{
	char **env;
	// char *name = "PATH";
	char **res = utils_split(str, ' ');
	if (utils_strstr(res[0], "env"))
	{
		env = environ;
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
}
