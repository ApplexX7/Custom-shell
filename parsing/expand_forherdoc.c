/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_forherdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:21:49 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/24 17:21:53 by mohilali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void push_to_front(t_list **source, t_list *dest)
{
  t_list *tmp;
  t_list *tmp2;

  tmp = *source;
  while (tmp)
  {
    tmp2 = tmp;
    tmp = tmp->next;
    tmp2->next = NULL;
    ft_lstadd_back(&dest, tmp2);
  }
  *source = dest;
}

void donothing(void *arg)
{
  (void) arg;
}

// the last element of arr must be NULL
// note: avoit freeing the element of arr,
//       since they are put in the list
t_list *convert_to_list(char **arr)
{
  int i;
  t_list *new;
  t_list *node;
  
  new = NULL;
  i = 0;
  while (arr[i])
  {
    node = ft_lstnew(arr[i]);
    if (!node)
      return (ft_lstclear(&new, &donothing), NULL);
    ft_lstadd_back(&new, node);
    i++;
  }
  return (new);
}

// the is_op is set to 0 here
void appendto_list(t_list *source, t_list **dest, char op)
{
  t_list *tmp;

  while (source)
  {
    tmp = source;
    source = source->next;
    tmp->next = NULL;
    ft_lstadd_back(dest, tmp);
  }
}

char *get_envarg_value(char *arg)
{
  int i;
  char *value;

  arg++;
  i = 0;
  value = get_exported_arg_value(arg, NULL, 0);
  if (value)
    return (value);
  else
    return (NULL);
}

t_list *get_right_node(t_list *head ,t_list *node)
{
  if (head == node)
    return (NULL);
  while (head->next != node)
    head = head->next;
  return (head);
}

void lst_delete_node(t_list **lst, t_list *node)
{
  t_list *right_node;

  right_node = get_right_node(*lst, node);
  if (right_node)
    right_node->next = node->next;
  if (*lst == node)
    *lst = node->next;
  ft_lstdelone(node, &free);
}

// allocs: list, new_lst
int add_env_args(char *arg, t_list **dest)
{
  char **arr;
  t_list *new_lst;

  arr = ft_split(arg, ' ');
  if (!arr)
    return (1);
  new_lst = convert_to_list(arr);
  if (!new_lst)
    return (free_2d_arr((void **)arr), 1);
  appendto_list(new_lst, dest, '\'');
  free(arr);
  return (0);
}

// allocs: content, node
int addback_node(t_list **dest, t_list *node)
{
  char *content;
  t_list *new_node;

  content = ft_strdup(node->content);
  if (!content)
    return (1);
  new_node = ft_lstnew(content);
  if (!new_node)
    return (free(content), 1);
  ft_lstadd_back(dest, new_node);
  return (0);
}

static int handle_single_dolor(t_list *node, t_list **dest)
{
  if (!ft_strncmp(node->content, "$", 2))
    return (addback_node(dest, node));
  else
    return (0);
}

// lst should be labled before passing
// it frees lst on success
// allocs: new
int expand_herdoc(t_list **lst)
{
  t_list *tmp;
  t_list *new;

  tmp = *lst;
  new = NULL;
  while (tmp)
  {
    if (ft_strchr(tmp->content, '$'))
    {
      if (/*tmp->is_op != '\''&&*/ get_envarg_value(tmp->content) && ft_strncmp(tmp->content, "$", 2))
      {
        if (add_env_args(get_envarg_value(tmp->content), &new))
          return (ft_lstclear(&new, &free), 1);
      }
      else if (handle_single_dolor(tmp, &new))
        return (ft_lstclear(&new, &free), 1);
    }
    else if (addback_node(&new, tmp)) // add node if it's not env arg
      return (ft_lstclear(&new, &free), 1);
    tmp = tmp->next;
  }
  return (ft_lstclear(lst, &free), *lst = new, 0);
}
