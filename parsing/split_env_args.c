

#include "minishell.h"

// allocs: tmp
int split_arg_node(t_list *node, t_list **dest)
{
  char *content;
  char *tmp;

  content = node->content;
  content++;
  while (ft_isalpha(*content) || *content == '_')
    content++;
  if (*content == '\0')
  {
    if (new_and_add(dest, node->content, node->is_op))
      return (1);
  }
  else
  {
    tmp = ft_substr(node->content, 0, content - (char *)node->content);
    if (!tmp || new_and_add(dest, tmp, node->is_op))
      return (free(tmp), 1);
    free(tmp);
    if (new_and_add(dest, content, node->is_op))
      return (1);
  }
  return (0);
}

// allocs: new
// frees lst on sucess
int split_env_arg(t_list **lst)
{
  t_list *tmp;
  t_list *new;

  tmp = *lst;
  new = NULL;
  while (tmp)
  {
    if (ft_strchr(tmp->content, '$'))
    {
      if (tmp->is_op != '\'')
      {
        if (split_arg_node(tmp, &new))
          return (ft_lstclear(&new, &free), 1);
      }
    }
    else if (add_node(&new, tmp))
      return (ft_lstclear(&new, &free), 1);
    tmp = tmp->next;
  }
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}
