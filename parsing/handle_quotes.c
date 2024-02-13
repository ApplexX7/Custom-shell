/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:07:20 by ayait-el          #+#    #+#             */
/*   Updated: 2024/02/13 19:41:36 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// hello world "this is " blablabla

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

int add_to_list(char *start, char *end, char quote, t_list **lst)
{
  char *content;
  t_list *node;

  if (start[0] == '"' || start[0] == '\'')
    content = remove_quotes(ft_substr(start + 1, 0, end - start - 1), quote); // it skips the quotes
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
t_list *handle_queotes(char *command)
{
  int i;
  char *start;
  t_list *lst;

  i = 0;
  start = &command[i];
  lst = NULL;
  while (command[i])
  {
    if (command[i] == '"' || command[i] == '\'')
    {
      if (add_to_list(start, &command[i], command[i], &lst))
        return (ft_lstclear(&lst, &free), NULL);
      if (get_next_quote(start, &command[i], command[i]) == NULL)
        return (ft_lstclear(&lst, &free), NULL);
      i += get_next_quote(start, &command[i], command[i]) - &command[i];
      if (start[0] == '"' || command[i] == '\'')
        start = &command[i + 1];
      else
        start = &command[i];
    }
    i++;
  }
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
  }
}
