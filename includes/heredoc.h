#ifndef HEREDOC_H
# define HEREDOC_H

# include "libft.h"
# include "libag.h"
# include "line_input.h"
# include "liberror.h"

/*
**	heredoc.c
*/

int		heredoc(char *line, t_lstag **hd, char **builtin);

/*
**	list.c
*/

void	del_h(void *content, size_t content_size);
char	*lst_to_str(t_lstag *list);

int		ft_expand_dollar(char **cmd, const char **env, const char **loc, int check_tild);
char	***get_loc(char ***loc);
char	***get_env(char ***env);

#endif
