#include "../minishell.h"

static t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
    t_env	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
}

static t_env	*ft_lstnew_env(char *key, char *value)
{
    t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
    new->next = NULL;
	return (new);
}

void    fill_linked_lists(char **envp)
{
    t_env   *env;
    int     i;
    char    **tmp;

    i = 0;
    env = NULL;
    while (envp[i])
    {
        tmp = ft_split(envp[i], '=');
        ft_lstadd_back_env(&env, ft_lstnew_env(tmp[0], tmp[1]));
        i++;
    }
    char **cmds;
    cmds = malloc(sizeof(char *) * 2);
    cmds[0] = "cat";
    cmds[1] = NULL;
    t_cmd   *cmd;
    t_redir *redir;

    cmd = malloc(sizeof(t_cmd));
    redir = malloc(sizeof(t_redir));
    redir->key = "EOF";
    redir->mode = HEREDOC;
    redir->next = NULL;
    cmd->next = NULL;
    cmd->redir = redir;
    cmd->cmd = cmds;
    g_sh->env = env;
    g_sh->cmd = cmd;

}