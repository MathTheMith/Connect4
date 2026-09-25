#include "connect4.h"


int	is_number(char *str)
{
	size_t	i;

	if (!str[0] || ft_strlen(str) > 9)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac != 3 && ac != 4)
	{
		ft_putendl_fd("Wrong number of arguments !", 2);
		return (0);
	}
	if (!is_number(av[1]) || !is_number(av[2]))
	{
		ft_putendl_fd("Arguments must be positive numbers !", 2);
		return (0);
	}
	if (ft_atoi(av[1]) < 6)
	{
		ft_putendl_fd("First argument must be at least 6 !", 2);
		return (0);
	}
	if (ft_atoi(av[2]) < 7)
	{
		ft_putendl_fd("Second argument must be at least 7 !", 2);
		return (0);
	}
	if (ac == 4 && ft_strncmp(av[3], "--gui", 6) != 0)
	{
		ft_putendl_fd("Unknown option, only --gui is allowed !", 2);
		return (0);
	}
	return (1);
}