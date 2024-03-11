


#include "../parsing/minishell.h"

int set_fd(int *set, t_tree *root)
{
  int fd;

  if (root->output_file)
  {
    //printf("%s\n", root->output_file);
    fd = open(root->output_file, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
      return (perror("open"), 1);
    //manage_fds(fd, CAPTURE)   
    return (*set = fd, 0);
  }
  else
    return (*set = root->out_fd, 0);
}

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
  if (!ft_strncmp(lst->content, "-n", 3))
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
  return (0);
}

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
