
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
    if (new_and_add(&lst, (void *) content->d_name))
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

int expand_wildcard(t_list **lst)
{
  t_list *start;
  t_list *end;

  start = NULL;
  end = NULL;
  lst_next_wildcard(*lst, &start, &end);
  printf("-------------\n");
  if (start && end)
    print_ouput(lst_copy_portion(start, end));
  return (0);
}
