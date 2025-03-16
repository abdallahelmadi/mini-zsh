#include <minishell.h>

void	fun_cd(char *str)
{
	char **res;
	// chdir function
	// check the path
	char *pwd;
	char *new_pwd;
	res = utils_split(str, ' ');
	pwd = malloc(sizeof(char) * 1000);
	if (!pwd)
		return ;
	if (utils_strstr(res[0], "cd"))
	{
		getcwd(pwd, 1000);
		new_pwd = utils_strjoin(pwd, "/", res[1]);
		if (!access(new_pwd, F_OK))
			chdir(new_pwd);
		else
			printf("no such file or directory: %s\n", res[1]);
	}
	// free(pwd);
	// free(new_pwd);
}
