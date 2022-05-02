/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:28:26 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 22:25:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"

#include <math.h>
#include <stdio.h>

static void	_initialize_unit(t_fdf *unit)
{
	int		width;
	int		height;

	width = 800;
	height = 600;
	unit->scale = 1.0;
	unit->z_size = 1.0;
	unit->default_rotate.x = M_PI_4;
	unit->default_rotate.y = -asin(tan(M_PI_2 / 3.0));
	unit->default_rotate.z = M_PI_2 / 3.0;
	unit->rotate = unit->default_rotate;
	unit->win_dim = (t_point2){width, height};
	unit->depth = calloc_safe(width * height, sizeof(*unit->depth));
	clear_depth(unit);
}

static int	_create_window(void *mlx_ptr, t_fdf *unit)
{
	int		width;
	int		height;
	char	*title;

	width = unit->win_dim.x;
	height = unit->win_dim.y;
	title = unit->map.path;
	unit->mlx_ptr = mlx_ptr;
	unit->win_ptr = mlx_new_window(unit->mlx_ptr, width, height, title);
	if (!unit->win_ptr)
		return (0);
	unit->img_ptr = mlx_new_image(unit->mlx_ptr, width, height);
	if (!unit->img_ptr)
		return (0);
	draw_fdf(unit);
	set_hook(unit);
	return (1);
}

static int	_fdf(void *mlx_ptr, t_fdf *unit, char *path)
{
	if (fdf_read_map(&unit->map, path))
	{
		_initialize_unit(unit);
		if (_create_window(mlx_ptr, unit))
			return (1);
	}
	else
		perror("Map Error");
	return (0);
}

static void	_fdf_multiple(void *mlx_ptr, int argc, char *argv[])
{
	int		begin;
	t_fdf	*fdf_arr;
	int		i;
	int		loop;

	begin = 1;
	fdf_arr = calloc_safe(argc - begin, sizeof(*fdf_arr));
	i = 0;
	loop = 0;
	while (i < argc - begin)
	{
		loop |= _fdf(mlx_ptr, &fdf_arr[i], argv[begin + i]);
		i++;
	}
	if (loop)
		mlx_loop(mlx_ptr);
	free(fdf_arr);
}

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;

	if (argc < 2)
	{
		puterr_safe("No Map Filename\n");
		return (EXIT_FAILURE);
	}
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (EXIT_FAILURE);
	_fdf_multiple(mlx_ptr, argc, argv);
	return (EXIT_SUCCESS);
}
