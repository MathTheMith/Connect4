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
	SetTraceLogLevel(LOG_NONE);
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

static bool	handle_click(t_game *game, int cell)
{
	int	x;

	x = GetMousePosition().x / cell;
	if (x < 0 || x >= game->columns)
		return (false);
	return (drop_piece(game, x, game->current) != -1);
}

static void	draw_result(t_game *game, int cell)
{
	char	*msg;
	int		size;
	int		width;
	int		x;
	int		y;

	msg = "It's a draw !";
	if (game->state == WIN_X)
		msg = "Player X won !";
	else if (game->state == WIN_O)
		msg = "Player O won !";
	size = cell / 2;
	if (size < 20)
		size = 20;
	width = MeasureText(msg, size);
	x = (GetScreenWidth() - width) / 2;
	y = (GetScreenHeight() - size) / 2;
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4));
	DrawRectangle(x - size / 2, y - size / 2, width + size, size * 2,
		Fade(BLACK, 0.8));
	DrawText(msg, x, y, size, RAYWHITE);
}

void draw_board(t_game *game, int cell)
{
	int i;
	int j;
	j = 0;
	Color color;
	while (game->rows > j)
	{
		i = 0;
		while (game->columns > i)
		{
			color = BLUE;
			if (game->grid[j][i] == 'X')
				color = RED;
			if (game->grid[j][i] == 'O')
				color = YELLOW;
			DrawCircle(i * cell + cell / 2, j * cell + cell /2, (cell * 0.97) / 2, color);
			i++;
		}
		j++;
	}
}

bool	draw_gui_grid(t_game *game)
{
	int		cell;
	bool	redraw;

	cell = setup_window(game);
	if (!cell)
	{
		CloseWindow();
		ft_putendl_fd("Grid too large to be displayed in a window !", 2, true);
		return (false);
	}
	redraw = true;
	while (!WindowShouldClose())
	{
		if (game->state == PLAYING && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
			&& handle_click(game, cell))
		{
			game->state = get_game_state(game);
			game->current = (game->current == 'X') ? 'O' : 'X';
			redraw = true;
		}
		if (redraw)
		{
			draw_grid(game);
			redraw = false;
		}
		BeginDrawing();
		ClearBackground(DARKBLUE);
		draw_board(game, cell);
		if (game->state != PLAYING)
			draw_result(game, cell);
		EndDrawing();
	}
	if (game->state == PLAYING)
		game->state = QUIT;
	CloseWindow();
	return (true);
}
