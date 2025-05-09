/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:48:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/09 20:50:50 by bnafiai          ###   ########.fr       */
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

# define SUCCESS 0
# define FAILURE 1
# define NOT_FOUND 127
# define PERMISSION_DENIED 126
# define SIGNAL_SIGINT 130
# define SYNTAX_ERROR 2

# define TP_CMD 0
# define TP_PIPE 1
# define TP_STRING 2
# define TP_PATH 3
# define TP_REDIR1 4
# define TP_REDIR2 5
# define TP_REDIR11 6
# define TP_REDIR22 7

typedef struct s_smalloc_addr
{
	void					*address;
	struct s_smalloc_addr	*next;
}	t_smalloc_addr;

typedef struct s_cmd_line
{
	char				*data;
	int					type;
	int					heredoc;
	int					heredoc_fd;
	struct s_cmd_line	*next;
	struct s_cmd_line	*prev;
}	t_cmd_line;

typedef struct s_global
{
	int						g_lastexitstatus;
	int						g_oldlastexitstatus;
	char					**g_environments;
	volatile sig_atomic_t	g_signal;
	int						g_foreground_running;
	t_smalloc_addr			*g_smalloc_addr_v;
}	t_global;

extern t_global	g_global;

void		*smalloc(int size);

void		signals_sigint(int sig);
void		signal_handler_heredoc(int sig);
void		restore(void);
void		setup_for_heredoc(void);
void		restore_for_heredoc(void);
void		setup_signals_main(void);
void		setup_for_child(void);

char		*prompt_branch(void);
char		*prompt_folder(void);
char		*prompt_zsh(void);

int			parsin_analyse_quotes(const char *command_line);
int			parsin_forbidden_keywords(const char *command_line);
void		parsin_global(const char *command_line);
void		parsin_make_list(const char *command_line, t_cmd_line **cmd_list);
void		pasrin_clean_list(t_cmd_line **list);
void		parsin_tokenization(t_cmd_line **cmd_list);
void		parsin_global_variables(t_cmd_line **cmd_list);
void		parsin_switcher(t_cmd_line **cmd_list);
void		parsin_syntax(t_cmd_line **cmd_list);

void		builtin_cd(t_cmd_line *node);
void		builtin_echo(t_cmd_line *node);
void		builtin_env(t_cmd_line *node);
void		builtin_exit(t_cmd_line *node);
void		builtin_export(t_cmd_line *node);
void		builtin_pwd(t_cmd_line *node);
void		builtin_unset(t_cmd_line *node);

int			write_to(t_cmd_line *node);
int			write_into(t_cmd_line *node);
int			read_from(t_cmd_line *node);
void		read_to_delimeter(t_cmd_line *node);

int			is_builtin_for_parent(t_cmd_line *node);
int			has_pipe(t_cmd_line *node);
int			has_heredoc(t_cmd_line *node);
int			handle_redirections(t_cmd_line *node);
pid_t		execution_part(t_cmd_line **node);
void		execution_v(t_cmd_line *node);
void		execution_global(t_cmd_line **cmd_list);

t_cmd_line	*utils_new_node(const char *data);
t_cmd_line	*utils_last_node(t_cmd_line *header);
t_cmd_line	*utils_replace_node(t_cmd_line **header, t_cmd_line **node,
				t_cmd_line **new_list);
char		**utils_split(const char *string, char c);
char		**utils_split_pro(const char *string, char *c);
char		*utils_strdup(const char *string);
char		*utils_strjoin(const char *s1, const char *s2, const char *s3);
char		*utils_strstr(const char *string, const char *search);
char		*utils_strstr_pro(const char *string, const char *search);
int			utils_charcmp(const char *string, char c);
int			utils_strcmp(const char *s1, const char *s2);
int			utils_strncmp(const char *s1, const char *s2, int size);
size_t		utils_strlen(const char *string);
int			utils_docente(const char *origin, int index, char c);
t_cmd_line	*utils_delete_node(t_cmd_line **list, t_cmd_line **node);
void		utils_setexit(int status);
int			utils_getexit(void);
char		**utils_gsetenv(const char **env);
char		*utils_getenv(const char *name);
char		*utils_strchar(char *str, char c);
char		*utils_get_next_line(int fd);
char		*utils_itoa(int nbr);

#endif
