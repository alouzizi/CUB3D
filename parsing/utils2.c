/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 06:24:09 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 06:26:53 by alouzizi         ###   ########.fr       */
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