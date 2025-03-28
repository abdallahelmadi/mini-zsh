#include <minishell.h>
#include <string.h>
extern char **environ;

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
// check wach variable kayn f env
static int find_var_env(char *var_name)
{
    int i = 0;
    while (environ[i])
    {
        if (strncmp(environ[i], var_name, strlen(var_name)) == 0 && environ[i][strlen(var_name)] == '=')
            return i;
        i++;
    }
    return -1;
}
// remove variable mn blasto f env
void remove_env_var(int index)
{
    int i;
    int j;
    int env_size = 0;
    while (environ[env_size])
        env_size++;
    char **new_environ = malloc(sizeof(char *) * env_size);
    if (!new_environ)
        return;
    i = 0;
    j = 0;
    while (environ[i])
    {
        if (i != index)
        {
            new_environ[j] = environ[i];
            j++;
        }
        i++;
    }
    new_environ[j] = NULL;
    free(environ);
    environ = new_environ;
}

void    fun_unset(char *str)
{
    char **env;
    char **res;
    int index;

    res = utils_split(str, ' ');
    if (!res || !res[0])
        return ;
    if (utils_strcmp(res[0], "unset") == 0)
    {
        if (!res[1])
        {
            free_array(res);
            return ;
        }
        env = utils_split(res[1], '=');
        if (!env || !env[0])
        {
            free_array(res);
            free_array(env);
            return ;
        }
        index = find_var_env(env[0]);
        if (index != -1)
        {
            remove_env_var(index);
            printf("Variable %s removed from environment\n", env[0]);
        }
        else
        {
            printf("Variable %s not found in environment\n", env[0]);
        }
        free_array(res);
    }
}