/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:15 by jkong             #+#    #+#             */
/*   Updated: 2022/04/26 21:56:18 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"

static t_pixel	*_get_data_pos(char *ptr, long x, long y, int size_of_line)
{
	return (&((t_pixel *)ptr)[x + y * (size_of_line / sizeof(t_pixel))]);
}

/*
 * 0 : Little Endian
 * 1 : Bit Endian (Network Endian)
*/
static t_pixel	_make_pixel(int color, int endian)
{
	t_pixel			result;
	unsigned char	*buf;
	size_t			i;
	size_t			size;
	unsigned char	temp;

	result = (t_pixel)color;
	if (endian != 0)
	{
		buf = (unsigned char *)&result;
		size = sizeof(result);
		i = 0;
		while (i < size / 2)
		{
			temp = buf[size - 1 - i];
			buf[i] = buf[size - 1 - i];
			buf[size - 1 - i] = temp;
			i++;
		}
	}
	return (result);
}

void	fill_image(t_fdf *unit, unsigned char byte)
{
	char	*ptr;
	int		size_of_line;
	int		ignore;

	ptr = mlx_get_data_addr(unit->img_ptr, &ignore, &size_of_line, &ignore);
	ft_memset(ptr, byte, size_of_line * unit->win_dim.y);
}

void	put_pixel(t_fdf *unit, long x, long y, int color)
{
	char	*ptr;
	int		bpp;
	int		size_of_line;
	int		endian;
	t_pixel	pixel;

	if (x < 0 || x >= unit->win_dim.x || y < 0 || y >= unit->win_dim.y)
		return ;
	ptr = mlx_get_data_addr(unit->img_ptr, &bpp, &size_of_line, &endian);
	if (bpp != sizeof(t_pixel) * BIT_COUNT)
		exit(EXIT_FAILURE);
	pixel = _make_pixel(color, endian);
	*_get_data_pos(ptr, x, y, size_of_line) = pixel;
}

void	refresh_window(t_fdf *unit)
{
	mlx_clear_window(unit->mlx_ptr, unit->win_ptr);
	mlx_put_image_to_window(unit->mlx_ptr, unit->win_ptr, unit->img_ptr, 0, 0);
}
