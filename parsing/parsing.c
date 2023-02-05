/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 03:04:05 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 11:07:08 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file(char *file)
{
	int	fd;

	if (!check_file_extention(file))
		exit(1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCan't open file\n", 2);
		exit(1);
	}
	return (fd);
}

int	check_file_extention(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
	{
		ft_putstr_fd("Eror\nFile extension must be '.cub'\n", 2);
		return (0);
	}
	return (1);
}

int	check_map(t_structs *g, char *file)
{
	int	fd;

	g->map = malloc(sizeof(t_map));
	if (!g->map)
		exit(1);
	fd = check_file(file);
	get_data(fd, g->map);
	return (1);
}

void	join_lines(t_map *map, char *line, int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	map->row = 0;
	map->column = ft_strlen(line);
	tmp = ft_strdup("");
	while (line)
	{
		tmp = free_strjoin(tmp, line, 3);
		map->row++;
		line = get_next_line(fd);
	}
	while (tmp[i])
	{
		if (tmp[i] == '\n' && tmp[i + 1] == '\n')
			error_exit("Error\nMissing data\n");
		i++;
	}
	map->map = ft_split(tmp, '\n');
	free(tmp);
}

char	*get_path(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	return (line);
}
