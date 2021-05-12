#include "cub3D.h"

int	check_res_color(t_vars *cub, char *line)
{
	int		size;
	char	**str;

	str = NULL;
	size = 0;
	str = ft_split(line, ' ', &size);
	if (!str)
		return (0);
	if (str[0][0] == 'R')
	{
		if (!(check_get_res(cub, str, size)))
			return (0);
	}
	else if (str[0][0] == 'F' || str[0][0] == 'C')
	{
		if (!(check_colors(cub, str, size)))
			return (0);
	}
	else
	{
		if (str)
			ft_double_free(str, size);
		return (0);
	}
	if (str)
		ft_double_free(str, size);
	return (1);
}