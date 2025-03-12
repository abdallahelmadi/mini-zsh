/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:48:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/12 15:10:28 by abdael-m         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

# define SUCCESS 0
# define FAILURE 1
# define NOT_FOUND 127
# define NOT_EXECUTABLE 126
# define NOT_CORRECT_OPTIONS 2
# define SIGNAL_SIGINT 130

char	*git_branch(void);
char	*get_folder_name(void);
char	*readline_prompt(int lastexitstatus);
void	check_command_line(const char *command_line, int *lastexitstatus);

char	**utils_split(const char *string, char c);
char	*utils_strdup(const char *string);
char	*utils_strjoin(const char *s1, const char *s2, const char *s3);
int		utils_strcmp(const char *string, char c);

void	signals_sigint(int sig);

#endif