#include <minishell.h>
#include <string.h>
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
//check wach kayn variable f env
static int check_in(char **env, char *str)
{
	int i = 0;
	while (env[i])
	{
		if (utils_strstr(env[i], str))
			return (1);
		i++;
	}
	return (0);
}
// zid variable jdid ila makanch f env
static char **add_to_environ(char **environ, char *new_var)
{
	int i = 0;
	int j;
	char **new_environ;

	while (environ[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_environ[j] = environ[j];
		j++;
	}
	new_environ[i] = new_var;
	new_environ[i + 1] = NULL;
	free(environ);
	return (new_environ);
}

void fun_export(char *str)
{
	char **env;
	char **res;
	char *joined;

	res = utils_split(str, ' ');
	if (!res || !res[0])
		return ;

	if (utils_strcmp(res[0], "export") == 0)
	{
		if (!res[1])
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
		else
		{
			if (!utils_strstr(res[1], "="))
			{
				printf("export: `%s`: not a valid identifier\n", res[1]);
				free_array(res);
				return ;
			}

			env = utils_split(res[1], '=');
			// if (!env || !env[0] || !env[1])
			// {
			// 	printf("export: `%s`: invalid format\n", res[1]);
			// 	free_array(res);
			// 	free_array(env);
			// 	return ;
			// }
			joined = utils_strjoin(env[0], "=", env[1]);
			if (!joined)
			{
				free_array(env);
				free_array(res);
				return ;
			}
			if (!check_in(environ, env[0]))
			{
				environ = add_to_environ(environ, joined);
				if (!environ)
				{
					free(joined);
					free_array(env);
					free_array(res);
					return ;
				}
				printf("export: %s\n", joined);
			}
			else
				free(joined);

			free_array(env);
		}
	}
	else
		printf("export: `%s`: not a valid identifier\n", res[0]);

	free_array(res);
}
