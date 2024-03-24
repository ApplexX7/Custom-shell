/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:59:39 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/24 17:43:48 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
typedef struct s_tree
{
    t_list *node;
    struct s_tree *left;
    struct s_tree *right;
    int input;
    int output;

} t_tree;
*/

t_list *check_combined_redirection(t_list *lst)
{
  int level;

  if (lst && is_open_parenth(lst))
  {
    level = 0;
    lst = lst->next;
    while (lst)
    {
      if (is_open_parenth(lst))
        level++;
      else if (is_close_parenth(lst))
      {
        if (level == 0)
          return (lst->next);
        else
          level--;
      }
      lst = lst->next;
    }
  }
  return (NULL);
}

int is_redirect_op(t_list *lst)
{
  if (is_input_redirect(lst))
    return (1);
  else if (is_output_redirect(lst))
    return (1);
  else
    return (0);
}

int is_input_redirect(t_list *lst)
{
  if (!ft_strncmp(lst->content, "<" ,2) && !lst->is_op)
    return (1);
  else if (!ft_strncmp(lst->content, "<<", 3) && !lst->is_op)
    return (1);
  else
    return (0);
}

int is_output_redirect(t_list *lst)
{
 	// printf("%d\t", (int)lst->is_op);
 	// printf("%s\n", (char *)lst->content);
  if (!ft_strncmp(lst->content, ">" ,2) && !lst->is_op)
    return (1);
  else if (!ft_strncmp(lst->content, ">>" ,3) && !lst->is_op)
    return (1);
  else
    return (0);
}


int set_io(t_tree *node, t_list *start, t_list **input_files, t_list **output_files)
{
  while (start)
  {
    //if (handle_ambiguous_redirection(start->next))
      //return (1);
    if (is_input_redirect(start))
    {
      if (node->fd)
        ft_close(node->fd); // TODO: maybe protect ???
      free(node->input_file);
      if (is_herdoc(start))
      {
        node->input_file = NULL;
        node->fd = start->fd;
      }
      else
      {
        if (new_and_add(input_files, start->next->content, '\''))
          return (perror("set_io: malloc"), 1);
        //node->input_file = ft_strdup(start->next->content);
        //if (node->input_file == NULL)
          //return (write(2, "Malloc Failure\n", 15), 1);
        node->fd = 0;
      }
    }
    else if (is_output_redirect(start))
    {
      if (node->out_fd != 1)
        ft_close(node->fd);
      free(node->output_file);
      if (is_herdoc(start))
      {
        if (new_and_add(output_files, start->next->content, '\''))
          return (perror("set_io: malloc"), 1);
        //node->output_file = ft_strdup(start->next->content);
        //if (node->output_file == NULL)
          //return (write(2, "Malloc Failure\n", 15), 1);
        node->out_fd = 1;
        node->open_mod = O_APPEND;
      }
      else
      {
        if (new_and_add(output_files, start->next->content, '\''))
          return (perror("set_io: malloc"), 1);
        //node->output_file = ft_strdup(start->next->content);
        //if (node->output_file == NULL)
          //return (write(2, "Malloc Failure\n", 15), 1);
        node->out_fd = 1;
        node->open_mod = O_TRUNC;
      }
    }
    start = start->next->next;
  }
  return (0);
}

void remove_redirections(t_tree *node, t_list *start)
{
  t_list *tmp;
  t_list *head;

  head = node->node;
  while (start)
  {
    tmp = start->next;
    lst_remove_node(&head, start);
    start = tmp;
  }
  node->node = head;
}

// allocs: files_list, output_files
int tree_set_io(t_tree *node)
{
  t_list *tmp;
  t_list *tmp2;
  t_list *input_files;
  t_list *output_files;

  if (!node)
    return (0);
  input_files = NULL;
  output_files = NULL;
  node->fd = 0;
  node->out_fd = 1;
  node->input_file = NULL;
  node->output_file = NULL;
  tmp = check_combined_redirection(node->node);
  if (!tmp)
    return (0);
  tmp2 = tmp;
  while (tmp && is_redirect_op(tmp))
    tmp = tmp->next->next;
  if (tmp != NULL)
    return (0);
  if (set_io(node, tmp2, &input_files, &output_files))
    return (ft_lstclear(&input_files, &free), ft_lstclear(&output_files, &free), 1);
  remove_redirections(node, tmp2);
  node->input_files = input_files;
  node->output_files = output_files;
  return (0);
}
