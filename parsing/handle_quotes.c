
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

int add_to_list(char *edges[2], int is_quoted, char quote, t_list **lst)
{
  char *content;
  t_list *node;
  char *start;
  char *end;

  start = edges[0];
  end = edges[1];
  if (is_quoted)
    content = remove_quotes(ft_substr(start, 0, end - start), quote); // it skips the quotes
  else
    content = ft_substr(start, 0, end - start);
  if (!content)
    return (1);
  // TODO: pass to handle unquoted before adding
  node = ft_lstnew(content);
  if (node == NULL)
    return (1);
  ft_lstadd_back(lst, node);
  return (0);
}

// parse command into a linked list
// frees command on sucess
t_list *handle_queotes(char *command)
{
  int start;
  int end;
  char *tmp;
  char *tmp2;
  t_list *lst;

  tmp2 = command;
  while (1)
  {
    tmp = get_next_quote(tmp2);
	if (tmp)
	{
		start = tmp - tmp2;
		end = tmp - tmp2;
    while (start - 1 > 0 && tmp2[start - 1] != ' ')
      start--;
    while (end < ft_strlen(tmp2) && (tmp2[end] != tmp[0] || &tmp2[end] == tmp))
      end++;
	}
	else
	{
		start = 0;
		end = ft_strlen(tmp2);
		if (end == 0)
			break;
	}
    if (start)
    {
      if (add_to_list((char *[2]){tmp2, &tmp2[start]}, 0, tmp[0], &lst))
        return (ft_lstclear(&lst, &free), NULL);
    }
    if (add_to_list((char *[2]){&tmp2[start], &tmp2[end]}, 1, tmp[0], &lst))
      return (ft_lstclear(&lst, &free), NULL);
	if (end == ft_strlen(tmp2))
		break;
	tmp2 = &tmp2[end + 1];
  }
  //return (free(command), lst);
  return (lst);
}


#include <stdio.h>
int main(void)
{
  char command[] = "hello world\"how are you\"\" today\" 'how can i helpe you'";
  t_list *lst = handle_queotes(command);

  while (lst)
  {
    printf("%s\n", (char *)lst->content);
    lst = lst->next;
  } }
