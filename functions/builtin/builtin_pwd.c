#include <minishell.h>

void	builtin_pwd(t_cmd_line *node)
{
	char *pwd;
	if (node->next && node->next->type == 2)
	{
		printf("minishell: pwd: too many arguments\n");
		return ;
	}
	pwd = malloc(sizeof(char) * 1000);
	if (!pwd)
		return;
	getcwd(pwd, 1000);
	printf("%s\n", pwd);
	free(pwd);
}
