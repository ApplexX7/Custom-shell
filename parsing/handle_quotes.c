
#include "minishell.h"

// hello world "this is " blablabla

/*
char *get_next_quote(char *start, char *str, char quote)
{
  char *tmp;

  if (start[0] != quote)
    return (ft_strchr(str, quote));
  tmp = ft_strchr(str, quote);
  while (tmp && tmp[1] != quote)
    tmp = ft_strchr(str, quote);
  return (tmp);
}
*/

int is_valid_token(char *token)
{
  int i;

  if (!token)
    return (0);
  i = 0;
  while (token[i])
  {
    if (token[i] != ' ')
      return (1);
    i++;
  }
  return (0);
}

char *get_next_quote(char *str)
{
  char *single;
  char *doble;

  single = ft_strchr(str, '\'');
  doble = ft_strchr(str, '"');
  if (!single && doble)
    return (doble);
  if (!doble && single)
    return (single);
  if (doble && single)
  {
    if (doble > single)
      return (single);
    else
      return (doble);
  }
  return (NULL);
}

int count_char(char *str, char chr)
{
  int i;
  int count;

  i = 0;
  count = 0;
  while (str[i])
  {
    if (str[i] == chr)
      count++;
    i++;
  }
  return (count);
}

// it frees str
char *remove_quotes(char *str, char quote)
{
  char *new;
  int i;
  int j;

  if (str == NULL)
    return (NULL);
  new = malloc(sizeof(char) * ft_strlen(str) - count_char(str, quote) + 1);
  if (!new)
    return (free(str), NULL);
  i = 0;
  j = 0;
  while (str[i])
  {
    if (str[i] != quote)
    {
      new[j] = str[i];
      j++;
    }
    i++;
  }
  new[j] = '\0';
  return (free(str), new);
}

// adds a new node to the back of the list
int add_new_to_list(void *content, t_list **lst)
{
  t_list *new;

  new = ft_lstnew(content);
  if (new == NULL)
    return (1);
  ft_lstadd_back(lst, new);
  return (0);
}

// allocs content
int add_to_list(char *edges[2], int is_quoted, char quote, t_list **lst)
{
  char *content;
  char *start;
  char *end;

  start = edges[0];
  end = edges[1];
  if (is_quoted)
    content = remove_quotes(ft_substr(start, 0, end - start), quote); // it skips the quotes
  else
  {
    content = ft_substr(start, 0, end - start);
    if (!is_valid_token(content))
      return (free(content), add_new_to_list(NULL, lst));
  }
  if (!content)
    return (1);
  // TODO: pass to handle unquoted before adding
  if (add_new_to_list(content, lst))
    return (free(content), 1);
  if (!is_quoted && add_new_to_list(NULL, lst))
    return (free(content), 1);
  return (0);
}

// set start and end to enclose the quote
int set_start_end(int *start, int *end, char *str)
{
  char *tmp;

  tmp = get_next_quote(str);
  if (tmp)
  {
    *start = tmp - str;
    *end = tmp - str;
    while ((*start) - 1 > 0 && str[(*start) - 1] != ' ')
      (*start)--;
    while (*end < ft_strlen(str) && (str[*end] != tmp[0] || &str[*end] == tmp))
      (*end)++;
  }
  else
  {
    *start = 0;
    *end = ft_strlen(str);
    if (*end == 0)
      return (1);
  }
  return (0);
}

// allocs: tmp2
// add the tokens represented by start and end to lst
// note: tmp is recomputed in order to fix norm
// if there is no quote in str, the function add str to lst
int add_tokens_to_list(int start, int end, t_list **lst, char *str)
{
  char *tmp;
  char *tmp2;

  tmp = get_next_quote(str);
  if (!tmp)
  {
    tmp2 = ft_strdup(str);
    if (!tmp2)
      return (free(tmp2), 1);
    if (add_new_to_list(NULL, lst) || add_new_to_list(tmp2, lst))
      return (ft_lstclear(lst, &free), 1);
    return (0);
  }
  if (start)
  {
    if (add_to_list((char *[2]){str, &str[start]}, 0, tmp[0], lst))
      return (ft_lstclear(lst, &free), 1);
  }
  if (add_to_list((char *[2]){&str[start], &str[end]}, 1, tmp[0], lst))
    return (ft_lstclear(lst, &free), 1);
  return (0);
}

int check_for_unclosed_quotes(char *command)
{
  int dbl;
  int single;

  dbl = count_char(command, '"');
  single = count_char(command, '\'');
  if (dbl % 2 != 0)
    return (1);
  if (single % 2 != 0)
    return (1);
  return (0);
}

// allocs: lst
// parse command into a linked list
// frees command on sucess
t_list *handle_queotes(char *command)
{
  int start;
  int end;
  char *tmp;
  t_list *lst;

  if (check_for_unclosed_quotes(command))
    return (NULL);
  lst = NULL;
  tmp = command;
  while (1)
  {
    if (set_start_end(&start, &end, tmp))
      break;
    if (add_tokens_to_list(start, end, &lst, tmp))
      return (NULL);
    if (end == ft_strlen(tmp))
      break;
    tmp = &tmp[end + 1];
  }
  //return (free(command), lst);
  return (lst);
}


/*
#include <stdio.h>
int main(void)
{
  char command[] = "hello world\"how are you\"\" today\" 'how can i helpe you''lmaaao' a b c d e f g'hello'      -l\"hi how are you\"\"\" ''";
  t_list *lst = handle_queotes(command);
  t_list *tmp;

  tmp = lst;
  while (tmp)
  {
    if (tmp->content)
      printf("%s\n", (char *)tmp->content);
    else
      printf("(null)\n");
    tmp = tmp->next;
  }
  ft_lstclear(&lst, &free);
}
*/
