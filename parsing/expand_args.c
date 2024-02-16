

#include "minishell.h"
#include <stdio.h>

void free_3d_arr(void **arr)
{
  int i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);
    i++;
  }
  free(arr);
}


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

void do_nothing(void *arg)
{
  (void) arg;
}

// the last element of arr must be NULL
// note: avoit freeing the element of arr,
//       since they are put in the list
t_list *convert_arr_to_list(char **arr)
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
      return (ft_lstclear(&new, &do_nothing), NULL);
    ft_lstadd_back(&new, node);
    i++;
  }
  return (new);
}

void append_list(t_list *source, t_list **dest)
{
  t_list *tmp;

  tmp = source;
  while (tmp)
  {
    ft_lstadd_back(dest, tmp);
    tmp = tmp->next;
  }
}

/*
void append_list(t_list **source, t_list *pos, t_list *dest)
{
  t_list *next;
  t_list *tmp;

  if (pos == NULL)
  {
    push_to_front(source, dest);
    return ;
  }
  next = pos->next;
  pos->next = NULL;
  while (dest)
  {
    tmp = dest;
    dest = dest->next;
    tmp->next = NULL;
    ft_lstadd_back(source, tmp);
  }
  (ft_lstlast(pos))->next = next;
  return ;
}
*/

char **convert_list_to_arr(t_list *lst)
{
  int len;
  char **arr;
  int i;

  len = ft_lstsize(lst);
  arr = (char **) malloc(sizeof(char *) * (len + 1));
  if (!arr)
    return (NULL);
  i = 0;
  while (i < len)
  {
    arr[i] = (char *) lst->content;
    lst = lst->next;
    i++;
  }
  arr[i] = NULL;
  return (arr);
}

int elem_is_single_quoted(int index, t_list *lst)
{
  int flag1;
  int flag2;
  int i;
  char **arr;

  arr = convert_list_to_arr(lst);
  if (arr == NULL)
    return (-1);
  flag1 = 0;
  flag2 = 0;
  i = index;
  while (i >= 0)
  {
    if (!ft_strncmp(arr[i], "'", 2))
    {
      flag1 = 1;
      break;
    }
    if (!ft_strncmp(arr[i], "|", 2) || !ft_strncmp(arr[i], "&", 2))
      break;
    i--;
  }
  i = index;
  while (arr[i])
  {
    if (!ft_strncmp(arr[i], "'", 2))
    {
      flag2 = 1;
      break;
    }
    if (!ft_strncmp(arr[i], "|", 2) || !ft_strncmp(arr[i], "&", 2))
      break;
    i++;
  }
  free(arr);
  if (flag1 && flag2)
    return (1);
  else
    return (0);
}

char *get_env_value(char *arg, char **env)
{
  int i;

  arg++;
  i = 0;
  while (env[i])
  {
    if (!ft_strncmp(arg, env[i], ft_strlen(arg)))
      return (env[i] + ft_strlen(arg) + 1);
    i++;
  }
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

int arr_len(char **arr)
{
  int i;

  i = 0;
  while (arr[i])
    i++;
  return (i);
}

// allocs: list, new_lst
int add_env_arg_to_lst(char *arg, t_list **dest, t_list *node)
{
  char **arr;
  t_list *right_node;
  t_list *new_lst;

  arr = ft_split(arg, ' ');
  if (!arr)
    return (1);
  new_lst = convert_arr_to_list(arr);
  if (!new_lst)
    return (free_3d_arr((void **)arr), 1);
  append_list(new_lst, dest);
  free(arr);
  return (0);
}

// allocs: content, node
int add_node(t_list **dest, t_list *node)
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

// allocs: new
t_list *expand_args(t_list **lst, char **env)
{
  t_list *tmp;
  int i;
  int j;
  t_list *new;

  i = 0;
  tmp = *lst;
  new = NULL;
  while (tmp)
  {
    if (ft_strchr(tmp->content, '$'))
    {
      j = elem_is_single_quoted(i, *lst);
      if (j == -1)
        return (ft_lstclear(&new, &free), NULL);
      else if (j == 0 && get_env_value(tmp->content, env))
      {
        if (add_env_arg_to_lst(get_env_value(tmp->content, env), &new, tmp))
          return (ft_lstclear(&new, &free), NULL);
      }
      else if (j == 1)
      {
        if (add_node(&new, tmp))
          return (ft_lstclear(&new, &free), NULL);
      }
    }
    else if (add_node(&new, tmp))
      return (ft_lstclear(&new, &free), NULL);
    tmp = tmp->next;
    i++;
  }
  return (new);
}

void print_list(t_list *lst)
{
  while (lst)
  {
    printf("%s\n", (char *) lst->content);
    lst = lst->next;
  }
}

int main(int argc, char **argv, char **env)
{
  t_list *head;
  t_list *new;

  head = NULL;
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("$USER")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup(" ")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("\"")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("$USER")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("$USER")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("\"")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("'")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("$USER")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("$USER")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("'")));
  ft_lstadd_back(&head, ft_lstnew(ft_strdup("$USERsdsdf")));
  new = expand_args(&head, env);
  print_list(new);
}

/*
int main(int argc, char **argv, char **env)
{
  printf("%s\n", get_env_value("$USER", env));
  printf("%s\n", get_env_value("$PWD", env));
  printf("%s\n", get_env_value("$_", env));
}
*/

/*
int main(void)
{
  t_list *head;
  char **arr;

  head = NULL;
  ft_lstadd_back(&head, ft_lstnew("$user1"));
  ft_lstadd_back(&head, ft_lstnew("$hello"));
  ft_lstadd_back(&head, ft_lstnew("'"));
  ft_lstadd_back(&head, ft_lstnew("how"));
  ft_lstadd_back(&head, ft_lstnew("$are"));
  ft_lstadd_back(&head, ft_lstnew("$are2"));
  ft_lstadd_back(&head, ft_lstnew("$are3"));
  ft_lstadd_back(&head, ft_lstnew("'"));
  ft_lstadd_back(&head, ft_lstnew("hello"));
  ft_lstadd_back(&head, ft_lstnew("hello"));
  ft_lstadd_back(&head, ft_lstnew("hello"));
  ft_lstadd_back(&head, ft_lstnew("$user"));
  ft_lstadd_back(&head, ft_lstnew("hello"));

  expand_args(&head);
}
*/

/*
int main(void)
{
  t_list *head;
  char **arr;

  head = NULL;
  ft_lstadd_back(&head, ft_lstnew("hello"));
  ft_lstadd_back(&head, ft_lstnew("world"));
  ft_lstadd_back(&head, ft_lstnew("how"));
  ft_lstadd_back(&head, ft_lstnew("are"));
  ft_lstadd_back(&head, ft_lstnew("you"));
  arr = convert_list_to_arr(head);
  int i = 0;
  while (arr[i])
  {
    printf("%s\n", arr[i]);
    i++;
  }
}
*/


/*
int main(void)
{
  t_list *head;
  t_list *to_append;

  head = NULL;
  to_append = NULL;
  ft_lstadd_back(&head, ft_lstnew("hello"));
  ft_lstadd_back(&head, ft_lstnew("world"));
  ft_lstadd_back(&head, ft_lstnew("how"));
  ft_lstadd_back(&head, ft_lstnew("are"));
  ft_lstadd_back(&head, ft_lstnew("you"));

  ft_lstadd_back(&to_append, ft_lstnew("1"));
  ft_lstadd_back(&to_append, ft_lstnew("2"));
  ft_lstadd_back(&to_append, ft_lstnew("3"));
  ft_lstadd_back(&to_append, ft_lstnew("4"));
  ft_lstadd_back(&to_append, ft_lstnew("5"));

  append_list(&head, NULL, to_append);

  while (head)
  {
    printf("%s\n", (char *)head->content);
    head = head->next;
  }
}
*/

/*
int main(void)
{
  char *arr[3];
  arr[0] = "hello";
  arr[1] = "world";
  arr[2] = NULL;
  t_list *new = convert_arr_to_list(arr);

  while (new)
  {
    printf("%s\n", new->content);
    new = new->next;
  }
}
*/
