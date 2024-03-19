

#include "minishell.h"

void lable_env_args(t_list *lst)
{
  while (lst)
  {
    if (lst->is_op == 0 && ((char *) lst->content)[0] == '$')
      lst->is_op = '"';
    lst = lst->next;
  }
}
