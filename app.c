/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:28:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/19 09:58:37 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"

#include "fdf.h"
#include "get_next_line.h"

#include <math.h>

#include <stdio.h>

static int	_key_hook(int keycode, void *param)
{
	const t_fdf	*app = param;

	(void)app;
	if (keycode > 0xFF)
	{
		printf("Flag Changed Hook %d\n", keycode - 0x100);
	}
	else
	{
		printf("Key Hook %d\n", keycode);
	}
	return (0);
}

static int	_mouse_hook(int button, int x, int y, void *param)
{
	const t_fdf	*app = param;
	int			color;

	if (x < 0 || y < 0)
		return (0);
	printf("Mouse Hook %d, %d, %d\n", button, x, y);
	color = 0xFFFFFF;
	if (button == MLX_MB_LEFT)
		color = 0xFF0000;
	else if (button == MLX_MB_RIGHT)
		color = 0x0000FF;
	else if (button == MLX_MB_OTHER)
		color = 0x00FF00;
	mlx_pixel_put(app->mlx_ptr, app->win_ptr, x, y, color);
	return (0);
}

static int	_mouse_move_hook(int x, int y, void *param)
{
	const t_fdf	*app = param;
	int			color;

	if (x < 0 || y < 0)
		return (0);
	printf("Mouse Move Hook %d, %d\n", x, y);
	color = 0xFFFFFF;
	mlx_pixel_put(app->mlx_ptr, app->win_ptr, x, y, color);
	return (0);
}

static int	_expose_hook(void *param)
{
	(void)param;
	printf("Expose Or Close\n");
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	app;

	if (argc != 2)
	{
		return (EXIT_FAILURE);
	}
	ft_memset(&app, 0, sizeof(app));
	app.map_path = argv[1];
	app.mlx_ptr = mlx_init();
	if (app.mlx_ptr == NULL)
		return (EXIT_FAILURE);
	app.win_ptr = mlx_new_window(app.mlx_ptr, 800, 600, "Test");
	if (app.win_ptr == NULL)
		return (EXIT_FAILURE);
	printf("%lf ; %lf\n", sin(M_PI / 2), cos(M_PI / 2));
	mlx_clear_window(app.mlx_ptr, app.win_ptr);
	mlx_pixel_put(app.mlx_ptr, app.win_ptr, 400, 300, 0x00FFFFFF);
	mlx_hook(app.win_ptr, MLX_EVENT_KEY_DOWN, 0, &_key_hook, &app);
	mlx_key_hook(app.win_ptr, &_key_hook, &app);
	mlx_mouse_hook(app.win_ptr, &_mouse_hook, &app);
	mlx_hook(app.win_ptr, MLX_EVENT_MOUSE_UP, 0, &_mouse_hook, &app);
	mlx_hook(app.win_ptr, MLX_EVENT_MOUSE_MOVE, 0, &_mouse_move_hook, &app);
	mlx_expose_hook(app.win_ptr, &_expose_hook, &app);
	mlx_hook(app.win_ptr, MLX_EVENT_CLOSE, 0, &_expose_hook, &app);
	mlx_loop(app.mlx_ptr);
	return (EXIT_SUCCESS);
}
