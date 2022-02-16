/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgana <morgana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:28:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/02/16 12:43:27 by morgana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Minishell.h"

/*
	stat function check status of file such as permissions and type
	S_IXUSR = check if it is executable
*/
t_bool	is_executable(char *path_cmd)
{
	struct stat	buffer;

	if (!path_cmd)
		return (false);
	if (stat(path_cmd, &buffer) != 0)
		return (false);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (false);
	if ((buffer.st_mode & S_IXUSR))
		return (true);
	return (false);
}

char	*find_full_path(t_ht_tab *env, char *command)
{
	t_ht_item	*path;
	char		**path_split;
	int			i;
	char		*final_path;

	i = 0;
	path = ht_search(env, "PATH");
	if (path == NULL)
		return (NULL);
	path_split = ft_split(path->value, ':');
	while (path_split[i] != NULL)
	{
		final_path = ft_join_var(3, path_split[i], "/", command);
		if (is_executable(final_path) == true)
		{
			free_matrix(path_split);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_matrix(path_split);
	return (NULL);
}

char	*get_fullpath(t_session *session, char *command)
{
	char	*full_path;

	if (is_executable(command) == true)
		full_path = ft_strdup(command);
	else
		full_path = find_full_path(session->env, command);
	if (full_path == NULL)
	{
		session->errcd = ft_check_error(ECMDNF, "command not found", NULL);
		return (NULL);
	}
	return (full_path);
}

void	remove_temp_fd(char	*argv[], t_session *s)
{
	char	*full_path;
	int		pid;
	int		i;

	i = 0;
	full_path = get_fullpath(s, "rm");
	if (full_path == NULL)
		return ;
	pid = fork();
	if (pid < 0)
		perror("error creating fork");
	else if (pid == 0)
	{
		s->errcd = execve(full_path, argv, NULL);
		perror("error execve");
		return ;
	}
	while (argv[i] != NULL)
		free(argv[i++]);
	waitpid(pid, &s->stat, 0);
	free (full_path);
}
