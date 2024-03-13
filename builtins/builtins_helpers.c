
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
