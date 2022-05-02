/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 21:25:54 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 15:39:19 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	write_safe(int fd, const void *buf, size_t len)
{
	size_t	off;
	ssize_t	res;

	off = 0;
	while (off < len)
	{
		res = write(fd, buf + off, len - off);
		if (res < 0)
			exit(EXIT_FAILURE);
		off += res;
	}
}

static size_t	_alone_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	putstr_safe(const char *str)
{
	write_safe(STDOUT_FILENO, str, _alone_strlen(str));
}

void	puterr_safe(const char *str)
{
	write_safe(STDERR_FILENO, str, _alone_strlen(str));
}
