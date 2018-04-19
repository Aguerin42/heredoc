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
	ft_putendl(delimiter);
	return (delimiter);
}

t_lstag	*heredoc(char *line, char ** var, char **builtin)
{
	char	*read;
	char	*delimiter;
	t_lstag	*list;
//	t_lstag	*node;

	list = NULL;
	if (line)
	{
		while ((line = ft_strstr(line, "<<")) && (*(line = line + 2)))
		{
			delimiter = find_delimiter(line);
			while (delimiter && !ft_strequ(read, delimiter))
			{
				ft_putendl("1---");
				read ? ft_strdel(&read) : NULL;
				ft_putchar('\n');
				if (!(read = line_input("heredoc>", NULL, var, builtin)))
					sh_error(1, "in heredoc function");
				else
				{
				ft_putendl("2---");
		//			if (!(node = ag_lstnew(read, ft_strlen(read) + 1)))
		//				sh_error(1, "in heredoc function");
		//			if (list)
		//				ag_lstadd(&list, node);
		//			else
		//				list = node;
				}
			}
				ft_putendl("3---");
			read ? ft_strdel(&read) : NULL;
				ft_putendl("4---");
			delimiter ? ft_strdel(&delimiter) : NULL;
				ft_putendl("5---");
		}
	}
				ft_putendl("6---");
	return (list);
}
