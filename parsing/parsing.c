/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 03:04:05 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 03:03:28 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_file(char *file)
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

int Check_map(t_structs *g, char *file)
{
	int	fd;
	g->map = malloc(sizeof(t_map));
	if (!g->map)
		exit(1);
	fd = check_file(file);
	Get_data(fd, g->map);
	return (1);
}
