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

static void	draw_centered(char *msg, int y, int size, Color color)
{
	DrawText(msg, (GetScreenWidth() - MeasureText(msg, size)) / 2, y, size,
		color);
}

bool	title_screen(t_game *game)
{
	bool	started;
	int		size;

	started = false;
	int i = 0;
	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			started = true;
		size = GetScreenWidth() / 10;
		BeginDrawing();
		ClearBackground(DARKBLUE);
		draw_centered("CONNECT 4", GetScreenHeight() / 4, size, RAYWHITE);
		if (game->current == 'X')
			draw_centered("Red (X) starts", GetScreenHeight() / 2, size / 3, RED);
		else
			draw_centered("Yellow (O) starts", GetScreenHeight() / 2,
				size / 3, YELLOW);
		i++;
		if ((i / 45) % 2 == 0 )
			draw_centered("Click anywhere to begin", GetScreenHeight() * 3 / 4,
				size / 2, RAYWHITE);
		EndDrawing();
		if (started)
			return (true);
	}
	return (false);
}

static bool	handle_click(t_game *game, int cell)
{
	int	x;
	int	row;

	x = GetMousePosition().x / cell;
	if (x < 0 || x >= game->columns)
		return (false);
	row = drop_piece(game, x, game->current);
	if (row == -1)
		return (false);
	game->state = check_connects(game, x, row);
	ft_putendl_fd("You played column ", 1, false);
	ft_putnbr_fd(x + 1, 1);
	ft_putendl_fd("", 1, true);
	return (true);
}

static void	draw_thinking(int cell)
{
	int	size;

	size = cell / 3;
	if (size < 16)
		size = 16;
	DrawRectangle(0, 0, GetScreenWidth(), size * 2, Fade(BLACK, 0.6));
	draw_centered("AI is thinking...", size / 2, size, RAYWHITE);
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
	if (!title_screen(game))
	{
		game->state = QUIT;
		CloseWindow();
		return (true);
	}
	redraw = true;
	while (!WindowShouldClose())
	{
		if (game->state == PLAYING && game->current == 'O'
			&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && handle_click(game, cell))
		{
			game->current = 'X';
			redraw = true;
		}
		if (redraw)
		{
			draw_grid(game);
			if (game->state == PLAYING && game->current == 'O')
				ft_putendl_fd("Your turn: click a column in the window", 1, true);
			redraw = false;
		}
		BeginDrawing();
		ClearBackground(DARKBLUE);
		draw_board(game, cell);
		if (game->state != PLAYING)
			draw_result(game, cell);
		else if (game->current == 'X')
			draw_thinking(cell);
		EndDrawing();
		if (game->state == PLAYING && game->current == 'X')
		{
			ai_play(game);
			redraw = true;
		}
	}
	if (game->state == PLAYING)
		game->state = QUIT;
	CloseWindow();
	return (true);
}
