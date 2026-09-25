#include "connect4.h"
#include "raylib.h"

#define MAX_CELL 100
#define MIN_CELL 10

static int	get_cell_size(t_game *game, int monitor)
{
	int	max_w;
	int	max_h;
	int	cell;

	max_w = GetMonitorWidth(monitor) * 0.9;
	max_h = GetMonitorHeight(monitor) * 0.9;
	cell = max_w / game->columns;
	if (max_h / game->rows < cell)
		cell = max_h / game->rows;
	if (cell > MAX_CELL)
		cell = MAX_CELL;
	return (cell);
}

static int	setup_window(t_game *game)
{
	int	monitor;
	int	cell;
	int	win_w;
	int	win_h;

	InitWindow(800, 600, "Connect 4");
	monitor = GetCurrentMonitor();
	cell = get_cell_size(game, monitor);
	if (cell < MIN_CELL)
		return (0);
	win_w = cell * game->columns;
	win_h = cell * game->rows;
	SetWindowSize(win_w, win_h);
	SetWindowPosition((GetMonitorWidth(monitor) - win_w) / 2,
		(GetMonitorHeight(monitor) - win_h) / 2);
	SetTargetFPS(60);
	return (cell);
}

void	draw_grid(t_game *game)
{
	int	cell;
	int	i;
	int j;
	int	x;
	int	y;

	cell = setup_window(game);
	if (!cell)
	{
		CloseWindow();
		ft_putendl_fd("Grid too large to be displayed in a window !", 2);
		return ;
	}
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKBLUE);
		j = 0;
		y = cell / 2;
		while (game->rows > j)
		{
			i = 0;
			x = cell / 2;
			while (game->columns > i)
			{
				DrawCircle(x, y, (cell - 1) / 2, BLUE);
				x += cell;
				i++;
			}
			y+= cell;
			j++;
		}
		EndDrawing();
	}
	CloseWindow();
}
