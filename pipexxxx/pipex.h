/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 04:34:06 by izouine           #+#    #+#             */
/*   Updated: 2024/04/18 16:43:55 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	*join(char **argv, int k, char **cmd, char **envp);
char	*file(char **argv);
char	*ft_strjoin(char *line, char *buff);
char	**ft_split(char const *s, char c);
void	exitt(int check);
void	ft_free(char **argv);
int		la_fin(int i);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char    **find_path(char **envp);
#endif
