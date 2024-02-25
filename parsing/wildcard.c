
#include "minishell.h"

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
  return (lst);
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

// allocs: arr, new
// note: it does not free lst on success this because lst is still needed for combining
t_list *split_by_star(t_list *lst)
{
  char **arr;
  t_list *new;
  int i;

  new = NULL;
  if (!is_wildcard(lst))
  {
    if (new_and_add(&new, lst->content, lst->is_op))
      return (ft_lstclear(&new, &free), NULL);
    lst = lst->next;
  }
  arr = ft_split(lst->content, '*');
  if (!arr)
      return (ft_lstclear(&new, &free), NULL);
  i = 0;
  while (arr[i])
  {
    new_and_add(&new, arr[i], 0);
    i++;
  }
  free_2d_arr((void **) arr);
  if (lst->next && !is_wildcard(lst->next))
  {
    if (new_and_add(&new, lst->next->content, lst->next->is_op))
      return (ft_lstclear(&new, &free), NULL);
  }
  return (new);
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
t_list *combine_wildcard_tokens(t_list *splited)
{
  t_list *new;

  if (!splited)
    return (NULL);
  new = NULL;
  if (splited->is_op && splited->next && !splited->next->is_op)
  {
    if (join_and_add(&new, splited, splited->next->next))
      return (ft_lstclear(&new, &free), NULL);
    splited = splited->next->next;
  }
  while (splited && !splited->is_op && (!splited->next || !splited->next->is_op))
  {
    if (new_and_add(&new, splited->content, splited->is_op))
      return (ft_lstclear(&new, &free), NULL);
    splited = splited->next;
  }
  if (splited)
  {
    if (join_and_add(&new, splited, NULL))
      return (ft_lstclear(&new, &free), NULL);
  }
  return (new);
}

int is_matched(char *str, t_list *wildcard)
{
  if (!wildcard)
    return (1);
  while (wildcard)
  {
    str = ft_strnstr(str, wildcard->content, ft_strlen(wildcard->content));
    //printf("content: %s, str: %s\n", wildcard->content, str);
    if (!str)
      return (0);
    wildcard = wildcard->next;
  }
  return (1);
}

int expand_wildcard(t_list **lst)
{
  t_list *start;
  t_list *end;
  t_list *tmp;
  t_list *combined;

  start = NULL;
  end = NULL;
  lst_next_wildcard(*lst, &start, &end);
  //if (start && end)
  if (start && end)
  {
    tmp = split_by_star(lst_copy_portion(start, end));
    combined = combine_wildcard_tokens(tmp);
    t_list *files = get_current_files();
    print_ouput(combined);
    while (files)
    {
      if (is_matched(files->content, combined))
        printf("%s\n", files->content);
      files = files->next;
    }
  }
  return (0);
}
