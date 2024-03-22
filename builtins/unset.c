

#include "../parsing/minishell.h"


void ft_unset(char *arg, t_list **local_env)
{
  static t_list **env = NULL;
  t_list *tmp;

  if (local_env)
    env = local_env;
  else
  {
    tmp = *env;
    while (tmp)
    {
      if (!ft_strncmp(arg, tmp->content, ft_strlen(arg)) && (((char *) tmp->content)[ft_strlen(arg)] == '=' || ((char *) tmp->content)[ft_strlen(arg)] == '\0'))
      {
        lst_remove_node(env, tmp);
        return ;
      }
      tmp = tmp->next;
    }
  }
}
