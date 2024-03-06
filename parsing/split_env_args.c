

#include "minishell.h"

// this function shouldn't fail fail
static int handle_digit_arg(t_list *node)
{
  if (ft_isdigit(((char *) node->content)[1]))
  {
    char *tmp;

    tmp = &((char *) node->content)[2];
    if (*tmp == '\0')
      return (1);
    ft_memmove(node->content, tmp, ft_strlen(tmp) + 1);
    return (1);
  }
  return (0);
}

// allocs: tmp
int split_arg_node(t_list *node, t_list **dest)
{
  char *content;
  char *tmp;

  if (handle_digit_arg(node))
    return (add_node(dest, node));
  content = node->content;
  content++;
  while (ft_isalpha(*content) || ft_isdigit(*content) || *content == '_')
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
      else if (add_node(&new, tmp))
        return (ft_lstclear(&new, &free), 1);
    }
    else if (add_node(&new, tmp))
      return (ft_lstclear(&new, &free), 1);
    tmp = tmp->next;
  }
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}
