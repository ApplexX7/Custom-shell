

#include "minishell.h"
/*
void set_input_fd(t_tree *node, int fd)
{
  if (node)
  {
    node->fd = 0;
    free(node->input_file);
    node->input_file = NULL;
    node->fd = fd;
  }
}*/

int tree_copy_output(char *output_file, int out_fd, t_tree *to)
{
  char *new;

  if (!to)
    return (0);
  if (output_file)
  {
    new = ft_strdup(output_file);
    if (!new)
      return (1);
    free(to->output_file);
    to->output_file = new;
    to->out_fd = 1;
  }
  else
  {
    free(to->output_file);
    to->output_file = NULL;
    to->out_fd = out_fd;
  }
  return (0);
}

int tree_copy_input(char *input_file, int fd, t_tree *to)
{
  char *new;

  if (!to)
    return (0);
  if (input_file)
  {
    new = ft_strdup(input_file);
    if (!new)
      return (1);
    free(to->input_file);
    to->input_file = new;
    to->fd = 0;
  }
  else
  {
    free(to->input_file);
    to->input_file = NULL;
    to->fd = fd;
  }
  return (0);
}

int open_pipes(t_tree *root)
{
  int pip[2];

  if (!root)
    return (0);
  if (!ft_strncmp(root->node->content, "|", 2))
  {
    if (pipe(pip))
      return (write(2, "failed to create pipe\n", 22), 1);
    //if (tree_copy_input(root->input_file, root->fd, root->left))
      //return (write(2, "failed to copy tree input\n", 25), 1);
    if (tree_copy_output(NULL, pip[1], root->left))
      return (write(2, "failed to copy tree output\n", 26), 1);
    if (tree_copy_input(NULL, pip[0], root->right))
      return (write(2, "failed to copy tree input\n", 25), 1);
    if (tree_copy_output(root->output_file, root->out_fd, root->right))
      return (write(2, "failed to copy tree input\n", 25), 1);
  }
  if (open_pipes(root->left))
    return (1);
  if (open_pipes(root->right))
    return (1);
  return (0);
}

/*
void itter(t_tree *tree)
{
  if (tree->left == NULL && tree->right == NULL)
  {
    handle_redirections_bottom(tree);
    return ;
  }
  itter(tree->left);
  itter(tree->right);
}
*/
