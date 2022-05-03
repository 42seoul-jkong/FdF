/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:28:26 by jkong             #+#    #+#             */
/*   Updated: 2022/05/04 02:19:57 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"

#include <math.h>

static void	_initialize_unit(t_fdf *unit)
{
	long	i;
	t_rect	br;

	unit->scale = 1024.0 / unit->map.dim.x;
	unit->z_size = 1.0;
	unit->rotate = (t_point3f){M_PI_4, -asin(tan(M_PI_2 / 3.0)), M_PI_2 / 3.0};
	i = 0;
	while (i < unit->map.dim.x * unit->map.dim.y)
	{
		transform_fdf(unit, i % unit->map.dim.x, i / unit->map.dim.x);
		i++;
	}
	br = bound_fdf(&unit->map);
	unit->win_dim.x = br.right - br.left + WIN_WIDTH_MARGIN;
	unit->win_dim.y = br.bottom - br.top + WIN_HEIGHT_MARGIN;
	if (unit->win_dim.x > MAX_WIN_WIDTH)
		unit->win_dim.x = MAX_WIN_WIDTH;
	if (unit->win_dim.y > MAX_WIN_HEIGHT)
		unit->win_dim.y = MAX_WIN_HEIGHT;
	unit->translate.x = -br.left + WIN_WIDTH_MARGIN / 2;
	unit->translate.y = -br.top + WIN_HEIGHT_MARGIN / 2;
}

static int	_create_window(void *mlx_ptr, t_fdf *unit)
{
	const int	width = unit->win_dim.x;
	const int	height = unit->win_dim.y;
	char *const	title = unit->map.path;

	unit->mlx_ptr = mlx_ptr;
	unit->win_ptr = mlx_new_window(unit->mlx_ptr, width, height, title);
	if (!unit->win_ptr)
		return (0);
	unit->img_ptr = mlx_new_image(unit->mlx_ptr, width, height);
	if (!unit->img_ptr)
		return (0);
	unit->depth = calloc_safe(width * height, sizeof(*unit->depth));
	clear_depth(unit);
	draw_fdf(unit);
	unit->default_scale = unit->scale;
	unit->default_z_size = unit->z_size;
	unit->default_rotate = unit->rotate;
	unit->default_translate = unit->translate;
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
		else
			puterr_safe("MLX Error\n");
	}
	else
		puterr_safe("Map Error\n");
	return (0);
}

static void	_fdf_multiple(void *mlx_ptr, int argc, int begin, char *argv[])
{
	t_fdf	*fdf_arr;
	int		i;
	int		loop;

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
	while (--i >= 0)
	{
		if (fdf_arr[i].win_ptr)
			mlx_destroy_window(fdf_arr[i].mlx_ptr, fdf_arr[i].win_ptr);
		if (fdf_arr[i].img_ptr)
			mlx_destroy_image(fdf_arr[i].mlx_ptr, fdf_arr[i].img_ptr);
		free(fdf_arr[i].map.arr);
		free(fdf_arr[i].depth);
	}
	free(fdf_arr);
}

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;

	if (argc < 2)
	{
		putstr_safe("No Map Filename\n");
		return (EXIT_FAILURE);
	}
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (EXIT_FAILURE);
	_fdf_multiple(mlx_ptr, argc, 1, argv);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (EXIT_SUCCESS);
}
