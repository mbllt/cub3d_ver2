#include "cub3D.h"

// static int	init_cos_sin(t_vars *cub)
// {
// 	int	i;

// 	cub->ray_c.cos = malloc(sizeof(float) * 360);
// 	if (!cub->ray_c.cos)
// 		return (0);
// 	cub->ray_c.sin = malloc(sizeof(float) * 360);
// 	if (!cub->ray_c.sin)
// 		return (0);
// 	i = -1;
// 	while (++i <= 360)
// 		cub->ray_c.cos[i] = cos(0.03);
// 	return (1);
// }

static int	init_malloc_plans(t_vars *cub)
{
	int	i;

	cub->ray_c.plans = malloc(sizeof(t_plan *) * 6);
	if (!cub->ray_c.plans)
		return (0);
	i = -1;
	while (++i < 2)
	{
		cub->ray_c.plans[i] = malloc(sizeof(t_plan) * cub->parsing.map_x);
		if (!cub->ray_c.plans[i])
			return (0);
	}
	while (i < 4)
	{
		cub->ray_c.plans[i] = malloc(sizeof(t_plan) * cub->parsing.map_y);
		if (!cub->ray_c.plans[i])
			return (0);
		i++;
	}
	while (i < 6)
	{
		//printf("%d\n", i);
		cub->ray_c.plans[i] = malloc(sizeof(t_plan));
		if (!cub->ray_c.plans[i])
			return (0);
		i++;
	}
	return(1);
}

static void	init_key(t_vars *cub)
{
	cub->ray_c.key.right = 0;
	cub->ray_c.key.left = 0;
	cub->ray_c.key.forward = 0;
	cub->ray_c.key.backward = 0;
	cub->ray_c.key.down = 0;
	cub->ray_c.key.up = 0;
	cub->ray_c.key.rot_x_right = 0;
	cub->ray_c.key.rot_x_left = 0;
	cub->ray_c.key.rot_z_right = 0;
	cub->ray_c.key.rot_z_left = 0;
	cub->ray_c.key.exit = 0;
}

static void	init_xyz(t_vars *cub)
{
	cub->ray_c.xyz.x = 0;
	cub->ray_c.xyz.y = 0;
	cub->ray_c.xyz.z = 0;
}

int	init_ray_casting(t_vars *cub)
{
	cub->ray_c.fov = 0;
	cub->ray_c.ratio_horizon = 0;
	cub->ray_c.ratio_vertical = 0;
	cub->ray_c.mlx = NULL;
	cub->ray_c.win = NULL;
	cub->ray_c.img = 0;
	cub->ray_c.addr = 0;
	cub->ray_c.bits_per_pixel = 0;
	cub->ray_c.line_length = 0;
	cub->ray_c.endian = 0;
	cub->ray_c.distance = 0;
	cub->ray_c.rota_x = 0;
	cub->ray_c.rota_z = 0;
	init_key(cub);
	init_vars_rays(cub);
	if (!(init_stock_rays(cub, cub->parsing.rx, cub->parsing.ry)))
		return (0);
	init_xyz(cub);
	if (!(init_malloc_plans(cub)))
		return (0);
	if (!(init_matrix_x(cub)))
		return (0);
	if (!(init_matrix_z(cub)))
		return (0);
	cub->ray_c.fps = 0;
	cub->ray_c.seconde = 0;
	// if (!init_cos_sin(cub))
	// 	return (0);
	cub->ray_c.pixel_color = NULL;
	cub->ray_c.ray_temp = (t_vector){0,0,0};
	return (1);
}