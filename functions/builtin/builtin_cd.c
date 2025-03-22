#include <minishell.h>
#include <sys/stat.h>
void	fun_cd(char *str)
{
	char **res;
	char *path;
	struct stat path_stat;
	// chdir function
	// check the path
	// char *pwd;
	// char *new_pwd;
	res = utils_split(str, ' ');
	// pwd = malloc(sizeof(char) * 1000);
	// if (!pwd)
	// 	return ;
	// if (utils_strstr(res[0], "cd"))
	// {
	// 	getcwd(pwd, 1000);
	// 	new_pwd = utils_strjoin(pwd, "/", res[1]);
	// 	if (!access(new_pwd, F_OK))
	// 		chdir(new_pwd);
	// 	else
	// 		printf("no such file or directory: %s\n", res[1]);
	// }
	// free(pwd);
	// free(new_pwd);
	path = res[1];
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (chdir(path) != 0)
			{
				perror("cd");
			}
		}
		else
		{
			printf("cd: %s is not directory\n", path);
		}
	}
	else
	{
		printf("cd : no such file or directory %s\n", path);
	}
}
