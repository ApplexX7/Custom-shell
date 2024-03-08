/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohilali <mohilali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:59:07 by mohilali          #+#    #+#             */
/*   Updated: 2024/03/08 18:52:26 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

// allocs: cwd, current_dir, lst
t_list *get_current_files()
{
  char *cwd;
  DIR *current_dir;
  struct dirent *content;
  t_list *lst;

  lst = NULL;
  cwd = getcwd(NULL, 0);
  if (!cwd)
    return (NULL);
  current_dir = opendir(cwd);
  if (!current_dir)
    return (free(cwd), NULL);
  content = readdir(current_dir);
  while (content)
  {
    if (new_and_add(&lst, (void *) content->d_name, '\''))
      return (free(cwd), closedir(current_dir), ft_lstclear(&lst, &free), NULL);
    content = readdir(current_dir);
  }
  closedir(current_dir);
  return (free(cwd), lst);
}

int lst_next_wildcard(t_list *head, t_list **start, t_list **end)
{
  t_list *s;
  t_list *e;

  s = head;
  while (head && !is_wildcard(head))
    head = head->next;
  if (!head)
    return (*start = NULL, *end = NULL, 0);
  if (s != head)
  {
    while (s->next != head)
      s = s->next;
    if (s->is_op == 0)
      s = head;
  }
  e = head;
  if (e->next && e->next->is_op != 0)
    e = e->next;
  *start = s;
  *end = e;
  return (0);
}

// allocs: new
t_list *lst_copy_portion(t_list *start, t_list *end)
{
  t_list *tmp;
  t_list *new;

  tmp = end->next;
  end->next = NULL;
  new = copy_lst(start);
  end->next = tmp;
  if (!new)
    return (NULL);
  return (new);
}

void set_ends(int *open_end, int *open_start, t_list *lst)
{

  *open_end = ((char *)lst->content)[ft_strlen(lst->content) - 1] == '*';
  *open_start = ((char *)lst->content)[0] == '*';
}

// allocs: arr
int split_and_add(t_list *tmp, t_list **dest)
{
  char **arr;
  int i;

  arr = ft_split(tmp->content, '*');
  if (!arr)
    return (1);
  i = 0;
  while (arr[i])
  {
    if (new_and_add(dest, arr[i], 0))
      return (free_2d_arr((void **)arr), 1);
    i++;
  }
  free_2d_arr((void **) arr);
  return (0);
}

// allocs: new
// it frees lst on sucess
// it also set the open_end bit and open_start bit
int split_by_star(t_list **lst, int *open_end, int *open_start)
{
  t_list *new;
  t_list *tmp;

  tmp = *lst;
  new = NULL;
  if (!is_wildcard(tmp))
  {
    if (new_and_add(&new, tmp->content, tmp->is_op))
      return (ft_lstclear(&new, &free), 1);
    tmp = tmp->next;
  }
  set_ends(open_end, open_start, tmp);
  if (split_and_add(tmp, &new))
    return (ft_lstclear(&new, &free), 1);
  if (tmp->next && !is_wildcard(tmp->next))
  {
    if (new_and_add(&new, tmp->next->content, tmp->next->is_op))
      return (ft_lstclear(&new, &free), 1);
  }
  return (ft_lstclear(lst, &free), *lst = new, 0);
}

// allocs: new
/*
t_list *combine_wildcard_tokens(t_list *unsplited, t_list *splited)
{
  t_list *new;

  new = NULL;
  if (!is_wildcard(unsplited))
  {
    if (((char *)unsplited->next->content)[0] != '*')
    {
      if (join_and_add(&new, splited, splited->next))
        return (ft_lstclear(&new, &free), NULL);
      splited = splited->next->next;
    }
    else
    {
      while (splited->next->next)
      {
        if (new_and_add(&new, splited, splited->is_op))
          return (ft_lstclear(&new, &free), NULL);
        splited = splited->next;
      }
    }
  }
  if (unsplited->next && unsplited->next->next && !is_wildcard())
}
*/

// allocs: new
// frees splited on success
int combine_wildcard_tokens(t_list **splited)
{
  t_list *new;
  t_list *tmp;

  tmp = *splited;
  if (!tmp)
    return (0);
  new = NULL;
  if (tmp->is_op && tmp->next && !tmp->next->is_op)
  {
    if (join_and_add(&new, tmp, tmp->next->next))
      return (ft_lstclear(&new, &free), 1);
    tmp = tmp->next->next;
  }
  while (tmp && !tmp->is_op && (!tmp->next || !tmp->next->is_op))
  {
    if (new_and_add(&new, tmp->content, tmp->is_op))
      return (ft_lstclear(&new, &free), 1);
    tmp = tmp->next;
  }
  if (tmp)
  {
    if (join_and_add(&new, tmp, NULL))
      return (ft_lstclear(&new, &free), 1);
  }
  return (ft_lstclear(splited, &free), *splited = new, 0);
}

int is_matched(char *str, t_list *wildcard, int open_end, int open_start)
{
  t_list *tmp;

  tmp = wildcard;
  if (!tmp)
    return (1);
  while (tmp)
  {
    if (ft_strlen(str) < ft_strlen(tmp->content))
      return (0);
    if (tmp == wildcard && !open_start)
      str = ft_strnstr(str, tmp->content, ft_strlen(tmp->content));
    else if (tmp->next || open_end)
      str = ft_strnstr(str, tmp->content, ft_strlen(str));
    else
      str = ft_strnstr(&str[ft_strlen(str) - ft_strlen(tmp->content)], tmp->content, ft_strlen(str));
    if (!str)
      return (0);
    str += ft_strlen(tmp->content);
    tmp = tmp->next;
  }
  return (1);
}

int add_if_nomatch(t_list **dest, t_list *start, t_list *end, int matched)
{
  if (!matched)
  {
    if (join_and_add(dest, start, end->next))
      return (1);
  }
  return (0);
}

// allocs: files
int add_if_matched(t_list **dest, t_list *portion, int ends[2], int *matched)
{
  t_list *files;
  int open_end;
  int open_start;
  t_list *tmp;

  open_end = ends[0];
  open_start = ends[1];
  files = get_current_files();
  if (!files)
    return (1);
  tmp = files;
  while (tmp)
  {
    if (is_matched(tmp->content, portion, open_end, open_start))
    {
      *matched = 1;
      if (new_and_add(dest, tmp->content, '\''))
        return (ft_lstclear(&files, &free), 1);
    }
    tmp = tmp->next;
  }
  ft_lstclear(&files, &free);
  return (0);
}

void remove_points_dir(t_list *start, t_list **lst)
{
  t_list *tmp;
  t_list *tmp2;

  tmp = *lst;
  if (start && ((char *)start->content)[0] != '.')
  {
    while (tmp)
    {
      tmp2 = tmp->next;
      if (!ft_strncmp(tmp->content, ".", 1))
        lst_remove_node(lst, tmp);
      tmp = tmp2;
    }
  }
}

// allocs: portion
int get_matched_list(t_list *start, t_list *end, t_list **dest)
{
  int open_end;
  int open_start;
  t_list *portion;
  int matched;

  matched = 0;
  if (start && end)
  {
    portion = lst_copy_portion(start, end);
    if (!portion)
      return (1);
    if (split_by_star(&portion, &open_end, &open_start))
      return (ft_lstclear(&portion, &free), 1);
    if (combine_wildcard_tokens(&portion))
      return (ft_lstclear(&portion, &free), 1);
    if (add_if_matched(dest, portion, (int [2]){open_end, open_start}, &matched))
      return (ft_lstclear(&portion, &free), 1);
    if (add_if_nomatch(dest, start, end, matched))
      return (ft_lstclear(&portion, &free), 1);
  }
  remove_points_dir(start, dest);
  ft_lstclear(&portion, &free);
  return (0);
}

// allocs: new
int add_matched_list(t_list **dest, t_list *lst)
{
  t_list *start;
  t_list *end;
  t_list *new;

  lst_next_wildcard(lst, &start, &end);
  while (start && end)
  {
    new = NULL;
    while (lst != start)
    {
      if (new_and_add(dest, lst->content, lst->is_op))
        return (1);
      lst = lst->next;
    }
    if (get_matched_list(start, end, &new))
      return (ft_lstclear(&new, &free), 1);
    lst = end->next;
    append_list(new, dest, '\'');
    lst_next_wildcard(lst, &start, &end);
  }
  while (lst)
  {
    if (new_and_add(dest, lst->content, lst->is_op))
      return (1);
    lst = lst->next;
  }
  return (0);
}

// allocs: new
// frees lst on sucess
int expand_wildcard(t_list **lst)
{
  t_list *new;

  new = NULL;
  if (add_matched_list(&new, *lst))
    return (ft_lstclear(&new, &free), 1);
  ft_lstclear(lst, &free);
  *lst = new;
  return (0);
}
