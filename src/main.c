#include "connect4.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (!check_args(ac, av))
		return (1);
	if (!init_game(&game, ft_atoi(av[1]), ft_atoi(av[2])))
	{
		ft_putendl_fd("Error: grid allocation failed !", 2, true);
		return (1);
	}
	if (ac != 4 || !draw_gui_grid(&game))
		play_terminal(&game);
	print_result(&game);
	free_game(&game);
	return (0);
}
