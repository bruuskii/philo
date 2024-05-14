/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:33:49 by izouine           #+#    #+#             */
/*   Updated: 2024/04/18 16:43:16 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char *line, char *buff)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (line && buff)
	{
		len1 = strlen(line);
		len2 = strlen(buff);
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (line[++i])
			str[i] = line[i];
		i = -1;
		while (buff[++i])
		{
			str[len1] = buff[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	la_fin(int i)
{
	i = 0;
	while (wait(NULL))
		;
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i <= n && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
