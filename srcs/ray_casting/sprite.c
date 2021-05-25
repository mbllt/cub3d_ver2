#include "cub3D.h"

static int	intersct_sprite(t_vars *cub, t_vector ray, t_plan plan, \
							t_dot_intersct *intersct)
{
	float		division;

	division = (plan.a * ray.x) + (plan.b * ray.y);
	if (division == 0)
		return (0);
	(*intersct).t_distance = - ((plan.a * cub->parsing.px) \
							+ (plan.b * cub->parsing.py) + plan.d);
	(*intersct).t_distance /= division;
	if ((*intersct).t_distance < 0)
		return (0);
	intersct_dot(cub, ray, intersct);
	return (1);
}

static float	get_r(t_vars *cub, t_dot_intersct *intersct, int i)
{
	t_vector	u;
	float		r;

	u = (t_vector){
		.x = intersct->dot.x - cub->ray_c.sprite[i].pos.x,
		.y = intersct->dot.y - cub->ray_c.sprite[i].pos.y,
		.z = 0
	};
	r = scalaire_v(u, cub->ray_c.sprite[i].v2) + 0.5;
	return (r);
}

t_dot_intersct	compare_sprite(t_vars *cub, t_dot_intersct *sprite, \
		float *r_temp, float *r)
{
	t_dot_intersct	temp;
	int				i;

	temp.dot = (t_vector){0, 0, 0};
	temp.t_distance = -1;
	temp.cardinal = -1;
	i = 0;
	while (i < cub->ray_c.nbr_sprite)
	{
		if (sprite[i].t_distance >= 0 && (temp.t_distance == -1 \
			|| sprite[i].t_distance < temp.t_distance))
		{
			temp.t_distance = sprite[i].t_distance;
			temp.dot.x = sprite[i].dot.x;
			temp.dot.y = sprite[i].dot.y;
			temp.dot.z = sprite[i].dot.z;
			temp.cardinal = 6;
			*r = r_temp[i];
		}
		i++;
	}
	return (temp);
}

static void	init(t_vars *cub, t_dot_intersct *sprite, float *r_temp)
{
	int	i;

	i = 0;
	while (i < cub->ray_c.nbr_sprite)
	{
		r_temp[i] = -1;
		sprite[i].dot = (t_vector){0, 0, 0};
		sprite[i].t_distance = -1;
		sprite[i].cardinal = -1;
		i++;
	}
}

static int	check_transparence(t_vars *cub, t_dot_intersct intersct, float r)
{
	unsigned int	pixel;
	int				x;
	int				y;

	x = 0;
	y = 0;
	get_xy_sprite(intersct, cub->parsing.textures[6], &x, &y, r);
	pixel = get_pixel(cub->parsing.textures[6], x, y);
	if ((pixel >> 24) > 0)
		return (0);
	return (1);
}

// static void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*c;

// 	c = (unsigned char*)s;
// 	while (n-- > 0)
// 		c[n] = 0;
// }

// static void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*tab;

// 	tab = malloc(size * count);
// 	if (!tab)
// 		return (NULL);
// 	ft_bzero(tab, (size * count));
// 	return (tab);
// }

t_dot_intersct	sprite(t_vars *cub, t_vector ray, t_dot_intersct *intersct, \
						float *r)
{
	int				i;
	t_dot_intersct	*sprite;
	float			*r_temp;
	t_dot_intersct	temp;

	sprite = malloc(cub->ray_c.nbr_sprite * sizeof(t_dot_intersct));
	if (!sprite)
		return ((t_dot_intersct){(t_vector){0, 0, 0}, 0, -10, \
			(t_vector){0, 0, 0}});
	r_temp = malloc(cub->ray_c.nbr_sprite * sizeof(float));
	if (!r_temp)
		return ((t_dot_intersct){(t_vector){0, 0, 0}, 0, -10, \
			(t_vector){0, 0, 0}});
	init(cub, sprite, r_temp);
	i = 0;
	while (i < cub->ray_c.nbr_sprite)
	{
		if (cub->ray_c.sprite[i].sprite_front >= 0 && intersct_sprite \
			(cub, ray, cub->ray_c.sprite[i].plans, intersct) == 1)
		{
			*r = get_r(cub, intersct, i);
			if ((*intersct).dot.z < 1 && (*intersct).dot.z >= 0 \
				&& *r >= 0 && *r < 1 && check_transparence(cub, *intersct, *r) \
					== 1)
			{
				r_temp[i] = *r;
				sprite[i].dot.x = (*intersct).dot.x;
				sprite[i].dot.y = (*intersct).dot.y;
				sprite[i].dot.z = (*intersct).dot.z;
				sprite[i].t_distance = (*intersct).t_distance;
				sprite[i].ray = (*intersct).ray;
			}
		}
		i++;
	}
	temp = compare_sprite(cub, sprite, r_temp, r);
	if (sprite)
		free(sprite);
	if (r_temp)
		free(r_temp);
	return (temp);
}
