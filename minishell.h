/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:48:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/17 13:07:31 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

extern int	g_lastexitstatus;

# define SUCCESS 0
# define FAILURE 1
# define NOT_FOUND 127
# define NOT_EXECUTABLE 126
# define SIGNAL_SIGINT 130
# define SYNTAX_ERROR 2

char	*git_branch(void);
char	*get_folder_name(void);
char	*readline_prompt(void);
void	check_command_line(const char *command_line);

char	**utils_split(const char *string, char c);
char	**utils_split_pro(const char *string, char *c);
char	*utils_strdup(const char *string);
char	*utils_strjoin(const char *s1, const char *s2, const char *s3);
char	*utils_strstr(const char *string, const char *search);
char	*utils_strstr_pro(const char *string, const char *search);
int		utils_strcmp(const char *string, char c);
size_t	utils_strlen(const char *string);

void	signals_sigint(int sig);

typedef struct s_cmd_line
{
	char				*data;
	struct s_cmd_line	*next;
	struct s_cmd_line	*prev;
}	t_cmd_line;

#endif