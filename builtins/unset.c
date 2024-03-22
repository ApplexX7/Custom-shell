

#include "../parsing/minishell.h"


int ft_unset(t_tree *tree, t_list **local_env)
{
  static t_list **env = NULL;
  t_list *tmp;
  t_list *arg;

  if (local_env)
    env = local_env;
  else
  {
    arg = tree->node->next;
    tmp = *env;
    while (arg)
    {
      while (tmp)
      {
        if (!ft_strncmp(arg->content, tmp->content, ft_strlen(arg->content)) && (((char *) tmp->content)[ft_strlen(arg->content)] == '=' || ((char *) tmp->content)[ft_strlen(arg->content)] == '\0'))
        {
          lst_remove_node(env, tmp);
          break;
        }
        tmp = tmp->next;
      }
      arg = arg->next;
    }
  }
  return (0);
}
