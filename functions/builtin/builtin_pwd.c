#include <minishell.h>

void	fun_pwd(char *str)
{
	char **res;
	char *pwd;
	pwd = malloc(sizeof(char) * 1000);
	if (!pwd)
		return;
	res = utils_split(str, ' ');
	if (utils_strstr(res[0], "pwd"))
	{
		getcwd(pwd, 1000);
		printf("%s\n", pwd);
	}
	free(pwd);
}