#include "cub3D.h"

static void	get_x_y_z(t_vars *cub, char **str_color, char **str)
{
	if (str[0][0] == 'F')
	{
		cub->parsing.f.x = ft_atoi(str_color[0]);
		cub->parsing.f.y = ft_atoi(str_color[1]);
		cub->parsing.f.z = ft_atoi(str_color[2]);
	}
	else if (str[0][0] == 'C')
	{
		cub->parsing.c.x = ft_atoi(str_color[0]);
		cub->parsing.c.y = ft_atoi(str_color[1]);
		cub->parsing.c.z = ft_atoi(str_color[2]);
	}
}

static int	get_color(t_vars *cub, char **str)
{
	int		size;
	char	**str_color;

	if(!(check_nbr_coma(str[1])))
		return (0);
	str_color = NULL;
	size = 0;
	str_color = ft_split(str[1], ',', &size);
	if (!str_color)
		return (0);
	if (size != 3)
	{
		ft_double_free(str_color, size);
		return (0);
	}
	if (!(check_if_not_digit(str_color[0])) \
		|| !(check_if_not_digit(str_color[1])) \
		|| !(check_if_not_digit(str_color[2])))
	{
		return (0);
	}
	get_x_y_z(cub, str_color, str);
	ft_double_free(str_color, size);
	return (1);
}

static int	check_size_colors(t_vars *cub)
{
	if (!(size_colors(cub->parsing.f.x)) || !(size_colors(cub->parsing.f.y)) \
		|| !(size_colors(cub->parsing.f.z)) || !(size_colors(cub->parsing.c.x))\
		|| !(size_colors(cub->parsing.c.y)) || !(size_colors(cub->parsing.c.z)))
	{
		return (0);
	}
	return (1);
}

int	check_colors(t_vars *cub, char **str, int size)
{
	if (str[0][1] != 0)
		return (0);
	if (size != 2)
		return (0);
	if (!(get_color(cub, str)))
	{
		return (0);
	}
	if (!(check_size_colors(cub)))
	{
		return (0);
	}
	if (str[0][0] == 'F')
		cub->parsing.ff = create_trgb(0, cub->parsing.f.x, cub->parsing.f.y, cub->parsing.f.z);
	if (str[0][0] == 'C')
		cub->parsing.cc = create_trgb(0, cub->parsing.c.x, cub->parsing.c.y, cub->parsing.c.z);
	return (1);
}
