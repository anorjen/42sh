/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:44:37 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:44:38 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static long	*get_time_last_mod(char *path)
{
	struct stat	sb;
	long		*time;

	if (stat(path, &sb) == -1)
		return (0);
	time = (long*)malloc(sizeof(long));
	*time = sb.st_mtimespec.tv_sec;
	return (time);
}

static int	add_file_in_table(char *path_to_dir, struct dirent *file)
{
	char		*path_to_file;
	struct stat	sb;
	int			res;

	path_to_file = ft_get_path(path_to_dir, file->d_name);
	res = 1;
	if (stat(path_to_file, &sb) == -1
			|| ISDIR(sb.st_mode)
			|| access(path_to_file, X_OK))
		res = 0;
	else
		hash_insert(ft_strdup(file->d_name), g_hash_files,
											ft_strdup(path_to_file));
	free(path_to_file);
	return (res);
}

static void	phash_fill_tables(char **path_to_dirs)
{
	DIR				*dir;
	struct dirent	*file;

	while (path_to_dirs && *path_to_dirs)
	{
		dir = opendir(*path_to_dirs);
		if (dir)
		{
			hash_insert(ft_strdup(*path_to_dirs), g_hash_dirs,
						get_time_last_mod(*path_to_dirs));
			while ((file = readdir(dir)))
				add_file_in_table(*path_to_dirs, file);
			closedir(dir);
		}
		path_to_dirs++;
	}
}

static int	check_time_mod(char **path_to_dirs)
{
	long		*time_old;
	long		*time_new;

	while (path_to_dirs && *path_to_dirs)
	{
		time_old = (long*)phash_search(*path_to_dirs, HASH_DIRS);
		time_new = get_time_last_mod(*path_to_dirs);
		if (time_old && time_new && *time_old != *time_new)
			return (1);
		path_to_dirs++;
	}
	return (0);
}

void		phash_update(void)
{
	static char	*st_path_str = NULL;
	char		*env_path;
	char		**paths;

	env_path = get_env("PATH");
	if (env_path == NULL)
		env_path = "";
	paths = ft_strsplit(env_path, ':');
	if (st_path_str == NULL || ft_strcmp(st_path_str, env_path)
							|| check_time_mod(paths))
	{
		if (st_path_str)
			free(st_path_str);
		st_path_str = ft_strdup(env_path);
		hash_clean_table(g_hash_files, NULL);
		hash_clean_table(g_hash_dirs, NULL);
		phash_fill_tables(paths);
	}
	free_arg(paths);
}
