#include <minishell.h>

extern char **environ;
// str get the readline string .
static void	free_array(char **str)
{
	int i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	fun_export(char *str)
{
	char **env;
	char **res;
	char *joined;
	res = utils_split(str, ' ');
	if (utils_strstr(res[0], "export"))
	{
		env = environ;
		while (*env)
		{
			joined = utils_strjoin("declare -x", " ", *env);
			if (joined)
			{
				printf("%s\n", joined);
				free(joined);
			}
			env++;
		}
	}

	free_array(res);
	// free_array(env);
}
