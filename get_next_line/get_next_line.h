/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:42:27 by mmasuda           #+#    #+#             */
/*   Updated: 2022/02/12 03:30:44 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int			get_next_line(int fd, char **line);
char		*ft_result_if_else(char **line, char *save,
				int result, int *tosave);
int			ft_read(int fd, char **save);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strchr_idx(const char *s, int c);
char		*ft_substr(const char *s, unsigned int start, size_t len);

#endif
