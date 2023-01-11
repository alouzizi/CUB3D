/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:44:45 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 01:15:01 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_map *map)
{
	ft_memset(map, 0, sizeof(t_map));
	ft_memset(map->f, -1, sizeof(map->f));
	ft_memset(map->c, -1, sizeof(map->c));
}

void	free_tab(char ***tab)
{
	char	**t;
	int		i;

	t = *tab;
	i = 0;
	if (!t)
		return ;
	while (t[i])
		free(t[i++]);
	free(t);
}

int	max_width(char **s)
{
	int		i;
	int		max;

	i = 0;
	max = 0;
	while (s[i])
	{
		if (get_strlen(s[i]) > max)
			max = get_strlen(s[i]);
		i++;
	}
	return (max);
}

char	*cut(char *str, char **dist)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(str) - 2;
	while (str[start] == ' ')
		start++;
	while (str[end] == ' ')
		end--;
	if (end - start < 0)
		*dist = ft_strdup("");
	else
		*dist = ft_substr(str, start, end - start + 1);
	return (*dist);
}
