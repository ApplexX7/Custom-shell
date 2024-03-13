
#include "../parsing/minishell.h"

int ft_echo(t_tree *root)
{
  int nflag;
  int fd;
  t_list *lst;

  lst = root->node;
  if (set_fd(&fd, root))
    return (1);
  lst = lst->next;
  nflag = 0;
  if (lst && !ft_strncmp(lst->content, "-n", 3))
  {
    nflag = 1;
    lst = lst->next;
  }
  while (lst)
  {
    ft_putstr_fd(lst->content, fd);
    ft_putstr_fd(" ", fd);
    lst = lst->next;
  }
  if (!nflag)
    ft_putstr_fd("\n", fd);
  if (fd != 1)
    close(fd);
  return (0);
}


/*
int main(void)
{
  t_list *node;

  node = NULL;
  ft_lstadd_back(&node, ft_lstnew("echo"));
  //ft_lstadd_back(&node, ft_lstnew("-n"));
  ft_lstadd_back(&node, ft_lstnew("hello"));
  ft_lstadd_back(&node, ft_lstnew("world"));
  ft_lstadd_back(&node, ft_lstnew("hello"));
  t_tree t = {node, NULL, NULL, 0, 1, NULL, "test"};
  ft_echo (&t);
}
*/
