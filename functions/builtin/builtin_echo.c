#include "minishell.h"

int echo_implement(char *str, char *option)
{
	if (utils_strstr(option, "-n") != NULL)
		printf("%s", str);
	else
		printf("%s\n", str);
	return 0;
}

