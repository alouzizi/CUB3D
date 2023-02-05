/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 06:24:09 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 09:58:05 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	free_option(int i, char *s1, char *s2)
{
	if (i == 0)
		return (0);
	else if (i == 1)
		return (free(s1), 0);
	else if (i == 2)
		return (free(s2), 0);
	else if (i == 3)
		return (free(s1), free(s2), 0);
	return (0);
}

char	*free_strjoin(char *s1, char *s2, int o)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (i + 1));
	while (!s)
		return (NULL);
	j = -1;
	i = 0;
	while (s1[++j])
		s[j] = s1[j];
	while (s2[i])
		s[j++] = s2[i++];
	s[j] = '\0';
	free_option(o, s1, s2);
	return (s);
}

int	valid(char *map)
{
	if (map[0] == '1' || map[0] == '0' || map[0] == 'N'
		|| map[0] == 'S' || map[0] == 'E' || map[0] == 'W')
		return (1);
	return (0);
}

int	p(char *map)
{
	if (map[0] == 'N' || map[0] == 'S' || map[0] == 'E' || map[0] == 'W')
		return (1);
	return (0);
}

int	check_wall(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == '0' || p(&map[y][x])) && (x == 0 || y == 0))
				return (0);
			if (x <= (int)ft_strlen(map[y]) - 1
				&& y <= (int)ft_strlen(map[y]) - 1)
			{
				if ((map[y][x] == '0' || p(&map[y][x]))
					&& (!valid(&map[y][x + 1]) || !valid(&map[y][x - 1])
						|| !valid(&map[y - 1][x]) || !valid(&map[y + 1][x])))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
