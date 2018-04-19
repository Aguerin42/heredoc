#include "heredoc.h"

char	*find_delimiter(char *line)
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

t_lstag	*heredoc(char *line, char ** var, char **builtin)
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
			redoc_delimiter(delimiter);
			while (delimiter && !ft_strequ(read, delimiter))
			{
				read ? ft_strdel(&read) : NULL;
				ft_putchar('\n');
				if (!(read = line_input("heredoc>", NULL, var, builtin)))
					sh_error(1, "in heredoc function");
				else
				{
					if (!(node = ag_lstnew(read, ft_strlen(read) + 1)))
						sh_error(1, "in heredoc function");
					if (list)
						ag_lstadd(&list, node);
					else
						list = node;
				}
			}
			read ? ft_strdel(&read) : NULL;
			delimiter ? ft_strdel(&delimiter) : NULL;
		}
		is_in_heredoc(1);
		redoc_delimiter("");
	}
	return (list);
}
