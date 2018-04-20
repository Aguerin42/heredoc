#include "heredoc.h"

static void		del(void *content, size_t content_size)
{
	if (content_size)
		NULL;
	if (content)
		ft_memdel(&content);
}

static char		*list_to_str(t_lstag *list)
{
	int		len;
	char	*str;
	t_lstag	*head;

	head = list;
	len = 0;
	while (list)
	{
		len += list->content_size;
		list = list->next;
	}
	list = head;
	if (!(str = ft_strnew(len)))
		sh_error(1, "in list_to_str function");
	while (str && list)
	{
		str = ft_strcat(str, list->content);
		str = ft_strcat(str, "\n");
		list = list->next;
	}
	return (str);
}

static char	*find_delimiter(char *line)
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
		sh_error(1, "in find_delimiter function");
	return (delimiter);
}

static char	*read_heredoc(char *delimiter, char **var, char **builtin)
{
	char	*line;
	t_lstag	*list;
	t_lstag	*node;

	list = NULL;
	line = NULL;
	redoc_delimiter(delimiter);
	while (!ft_strequ(line, delimiter))
	{
		ft_putchar('\n');
		line ? ft_strdel(&line) : NULL;
		if (!(line = line_input("heredoc>", NULL, var, builtin)))
			sh_error(1, "in heredoc function");
		else if (!ft_strequ(line, delimiter))
		{
			if (!(node = ag_lstnew(line, ft_strlen(line) + 1)))
				sh_error(1, "in heredoc function");
			if (list)
				ag_lstaddtail(&list, node);
			else
				list = node;
		}
	}
	line ? ft_strdel(&line) : NULL;
	line = list_to_str(list);
	list ? ag_lstdel(&list, del) : NULL;
	return (line);
}

t_lstag		*heredoc(char *line, char ** var, char **builtin)
{
	char	*read;
	char	*delimiter;
	t_lstag	*list;
	t_lstag	*node;

	list = NULL;
	read = NULL;
	if (line)
	{
		is_in_heredoc(1);
		while ((line = ft_strstr(line, "<<")) && (*(line = line + 2)))
		{
			delimiter = find_delimiter(line);
			if ((read = read_heredoc(delimiter, var, builtin)))
			{
				if (!(node = ag_lstnew(read, ft_strlen(read) + 1)))
					sh_error(1, "in heredoc function");
				if (list)
					ag_lstaddtail(&list, node);
				else
					list = node;
			}
			else
				sh_error(1, "in read_heredoc function");
			ft_strdel(&read);
			delimiter ? ft_strdel(&delimiter) : NULL;
		}
		is_in_heredoc(0);
		redoc_delimiter("");
	}
	return (list);
}
