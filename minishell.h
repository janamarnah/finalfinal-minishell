/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/13 19:24:59 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAXPATH 4096

extern volatile sig_atomic_t	g_lastsig;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		exitstatus;
	int		should_exit;
}	t_shell;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char	**args;
	int		input_fd;
	int		output_fd;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			num_commands;
}	t_pipeline;

typedef struct s_pipe_ctx
{
	pid_t	*pid;
	int		pipefd[2];
	int		previousread;
	int		i;
}	t_pipe_ctx;

t_token		*lexing(char *line, t_shell *shellstate);
void		lst_clear(t_token **list);

t_pipeline	*parse_pipeline(t_token *tokens);
void		free_pipeline(t_pipeline *pipeline);

int			dispatcherexecute(t_shell *shellstate, t_pipeline *pl);
int			executepipeline(t_shell *shellstate, t_pipeline *pl);
int			executesinglecmd(t_shell *shellstate, t_command *cmd);
int			runbuiltinparent(t_shell *shellstate, t_command *cmd);
void		child_single(t_shell *shellstate, t_command *cmd);
int			waitpipeline(pid_t *pid, int count);

int			builtinenv(char **argv, t_env *env, int fd);
int			builtinecho(char **args, int fd);
int			builtinpwd(int fd);
int			builtincd(char **args, t_env **env, int fd);
int			builtinexport(char **args, t_env **env, int fd);
int			builtinunset(char **args, t_env **env, int fd);
int			builtinexit(char **args, int laststatus, int fd);
void		errormsg(const char *cmd, const char *msg, int fd);

t_env		*findenv(t_env *env, const char *key);
t_env		*newenv(const char *key, const char *value);
void		addnode(t_env **env, t_env *node);
char		**envtoenvp(t_env *env);

void		ft_putstr_fd(const char *s, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *str);
void		free_tab(char **tab);
int			valid_identifier(char *str);
int			set_shellenv(t_env **env, const char *key, const char *value,
				int valueprovided);
int			print_export_env(t_env *env, int fd);
int			parse_export_arg(const char *arg, char **key, char **value,
				int *flag);

int			ifsmain(t_shell *shellstate, t_token *tokens, t_pipeline **pl);
void		mainhelper(t_shell *shellstate);
int			handle_line(t_shell *shellstate, char *line);
int			forkcommanderror(t_pipe_ctx *ctx, int hasnext);
int			execpipehelp(t_shell *shellstate, t_pipeline *pl, t_pipe_ctx *ctx);
int			execpipeloop(t_shell *shellstate, t_pipeline *pl, t_pipe_ctx *ctx);
int			savestdio(int *savein, int *saveout);
int			forkcommand(t_shell *shellstate, t_pipeline *pl, t_pipe_ctx *ctx);
void		closefds(int *fd);

void		installsig(void);
void		setup_signals_child(void);
int			isbuiltin(char *cmd);
int			runbuiltinchild(t_shell *shellstate, char **argv);
void		executecmd(t_shell *sh, char **argv);
int			convertstatus(int stat);
char		*findpath(char **envp, char *command);
int			envcount(t_env *env);
char		*joinkeyvalue(const char *key, const char *value);

int			syntax_validator(t_token *tokens);
int			command_counter(t_token *tokens);
int			parse_redir(t_pipeline *pipeline, t_token **tmp_tokens, int i);
int			parse_heredoc(t_pipeline *pipeline, t_token **token, int i);
int			fill_command(t_pipeline **pipeline, t_token *tokens);
int			is_redir_token(t_token_type type);
t_token		*token_list_new(t_token_type type, char *value);
void		ft_lstadd_back(t_token **list, t_token *new);
int			space_finder(char c);
t_token		*word_parser(char *line, int *i, t_shell *shellstate);
char		*expand_word(char *word, t_shell *shellstate);
char		*expand_variable(char *result, char *word, int *x,
				t_shell *shellstate);
char		*append_expand_str(char *dst, const char *src);
char		*append_expand_char(char *dst, char c);
char		*status_to_str(int status);
int			handle_redirect_in(t_token **token_list, char *line, int *i);
int			handle_redirect_out(t_token **token_list, char *line, int *i);
int			handle_pipe(t_token **token_list, int *i);

#endif
