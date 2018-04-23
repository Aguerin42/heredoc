#ifndef HEREDOC_H
# define HEREDOC_H

# include "libft.h"
# include "libag.h"
# include "line_input.h"
# include "liberror.h"

/*
**	heredoc.c
*/

t_lstag	*heredoc(char *line, char **var, char **builtin);

/*
**	list.c
*/

void	del_h(void *content, size_t content_size);
char	*list_to_str(t_lstag *list);

#endif
