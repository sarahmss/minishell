/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:11:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/15 19:30:03 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Minishell.h"

static int	create_heredoc(char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < -1)
	{
		perror("error");
		return (0);
	}
	return (fd);
}

static void	here_doc_sig(void)
{
	signal(SIGINT, sig_doc);
	signal(SIGQUIT, SIG_IGN);
}

void	read_write_heredoc(char *delimiter, int fd, char *path)
{
	char	*line;

	here_doc_sig();
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			if (path)
				free(path);
			ft_check_error(-1, "here-doc delimited by EOF\n", NULL);
		}
		if (ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	exit(0);
}

int	redir(char *delimiter, t_session *s)
{
	int		fd;
	int		pid;
	char	*path;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	path = ft_join_var(2, "/tmp/", delimiter);
	remove_fd(path);
	fd = create_heredoc(path);
	if (fd < 0)
	{
		free(path);
		return (0);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		read_write_heredoc(delimiter, fd, path);
	else
		waitpid(pid, &s->stat, 0);
	if (path)
		free(path);
	return (fd);
}
