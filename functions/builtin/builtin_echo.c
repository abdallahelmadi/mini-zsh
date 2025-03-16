#include <minishell.h>

// int echo_implement(char *str, char *option)
// {
// 	if (utils_strstr(option, "-n") != NULL)
// 		printf("%s", str);
// 	else
// 		printf("%s\n", str);
// 	return 0;
// }

// split readline()
// check echo and -n
// loop into the string and print them
void	free_array(char **str)
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

void	fun_echo(char *str)
{
	char **res;
	int i;
	res = utils_split(str, ' ');
	if (utils_strstr(res[1], "$?") != NULL)
	{
		printf("%d\n", SUCCESS);
		return ;
	}
	if (res[1] && utils_strstr(res[1], "-n") != NULL)
		i = 2;
	else
		i = 1;

	while (res[i])
	{
		printf("%s", res[i]);
		if (res[i + 1])
			printf(" ");
		i++;
	}
	if (res[1] && utils_strstr(res[1], "-n") != NULL)
		printf("\n");
	free_array(res);
}
