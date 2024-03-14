
#include "../parsing/minishell.h"

int set_fd(int *set, t_tree *root)
{
  int fd;

  if (root->output_file)
  {
    //printf("%s\n", root->output_file);
    fd = ft_open(root->output_file, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
      return (perror("open"), 1);
    //manage_fds(fd, CAPTURE)   
    return (*set = fd, 0);
  }
  else
    return (*set = root->out_fd, 0);
}

int ft_putnstr_fd(char *str, int fd, int size)
{
  int i;

  i = 0;
  while (str[i] && i < size)
  {
    if (write(fd, &str[i], 1) == -1)
      return (perror("write"), 1);
    i++;
  }
  return (0);
}
