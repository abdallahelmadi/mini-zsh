/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:48:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 13:55:04 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>             // printf, perror
# include <stdlib.h>            // malloc, free, exit, getenv
# include <unistd.h>            // write, access, open, read, close, fork, ...
# include <sys/types.h>         // wait, waitpid, wait.., stat, lstat, fstat
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/wait.h>          // wait, waitpid, wait3, wait4
# include <signal.h>            // signal, kill, sig..
# include <dirent.h>            // opendir, readdir, closedir
# include <string.h>            // strerror
# include <termios.h>           // tcsetattr, tcgetattr
# include <term.h>              // tgetent, tgetflag, tgetnum, tgetstr, tgoto
# include <readline/readline.h> // readline, rl_replace_line, rl_..
# include <readline/history.h>  // add_history
# include <sys/ioctl.h>         // ioctl

char	*git_branch(void); // return name of branch
char	*get_folder_name(void); // return name of currently directory

char	**utils_split(const char *string, char c); // return a splited string

int		utils_strcmp(const char *string, char c); // return 0 if matched

char	*utils_strdup(const char *string); // return clone of string

#endif