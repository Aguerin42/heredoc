#include "heredoc.h"

/*
**	Recherche du delimiter après avoir rencontré <<
*/

static char		*find_delimiter(char *line)
{
	int		b;
	int		e;
	char	*delimiter;

	delimiter = NULL;
	b = 0;
	while (line[b] && ag_isspace(line[b]))
		b++;
	e = b;
	while (line[e] && !ag_isspace(line[e]))
		e++;
	if ((e - b) && !(delimiter = ft_strsub(line, b, e - b)))
		exit(sh_error_int(1, "in find_delimiter function"));
	return (delimiter);
}

/*
**	Stockage d'une ligne dans un maillon de chaîne
*/

static void		str_to_lst(t_lstag **list, char *str)
{
	t_lstag	*node;

	if (!(node = ag_lstnew(str, ft_strlen(str) + 1)))
		exit(sh_error_int(1, "in heredoc function"));
	if (list && *list)
		ag_lstaddtail(list, node);
	else
		*list = node;
}

/*
**	Appel de l'édition de ligne tant que le delimiter n'a pas été rencontré
**	ou que l'utilisateur n'a pas appuyé sur `Ctrl-d` ou `Ctrl-c`
*/

static char		*read_heredoc(char *delimiter, char **var, char **builtin)
{
	char	*line;
	t_lstag	*list;

	list = NULL;
	line = NULL;
	redoc_delimiter(delimiter);
	while (!ft_strequ(line, delimiter))
	{
		line ? ft_strdel(&line) : NULL;
		if (!(line = line_input("heredoc>", NULL, var, builtin)))
			exit(sh_error_int(1, "in heredoc function"));
		else if (!ft_strequ(line, delimiter))
			str_to_lst(&list, line);
		ft_putchar('\n');
	}
	line ? ft_strdel(&line) : NULL;
	line = lst_to_str(list);
	list ? ag_lstdel(&list, del_h) : NULL;
	if (ft_expand_dollar(&line, (const char **)*get_env(NULL),\
				(const char **)*get_loc(NULL), 0))
		return NULL;
	return (line);
}

static t_lstag	*foreach_heredoc(char *line, char **var, char **builtin)
{
	char	*read;
	char	*delimiter;
	t_lstag	*list;

	list = NULL;
	while ((line = ft_strstr(line, "<<")) && (*(line + 2)))
	{
		line = line + 2;
		delimiter = find_delimiter(line);
		if (delimiter && (read = read_heredoc(delimiter, var, builtin)))
			str_to_lst(&list, read);
		else
			exit(sh_error_int(1, "in read_heredoc function"));
		read ? ft_strdel(&read) : NULL;
		delimiter ? ft_strdel(&delimiter) : NULL;
	}
	return (list);
}

/*
**	Gestion de heredoc dans une ligne de commande
**
**	La fonction parcourt la ligne de commande pour voir s'il y a des heredocs
**	Si oui, elle fait appelle à l'edition de ligne pour que l'utilisateur puisse
**	écrire le heredoc et renvoie une liste. Chaque maillon contient un heredoc.
*/

t_lstag			*heredoc(char *line, char **var, char **builtin)
{
	t_lstag	*list;

	if (!line)
		return (NULL);
	is_in_heredoc(1);
	list = foreach_heredoc(line, var, builtin);
	is_in_heredoc(0);
	redoc_delimiter("");
	return (list);
}
