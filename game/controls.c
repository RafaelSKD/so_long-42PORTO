/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:40 by rafaefer          #+#    #+#             */
/*   Updated: 2024/10/07 16:43:51 by rafaefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	moves(t_idk *game, int j, int i)
{
	if (game->map[j][i] == '0')
		game->moves++;
	if (game->map[j][i] == 'C')
	{
		game->collectables--;
		game->moves++;
	}
	if (game->map[j][i] == 'E')
	{
		if (game->collectables != 0)
			return (0);
		exit_game(game);
	}
	if (game->map[j][i] == '1')
		return (0);
	game->map[j][i] = 'P';
	game->i = i;
	game->j = j;
	return (1);
}

static int	move_left_right(int key_code, t_idk *game, int j, int i)
{
	int	moved;

	moved = 0;
	if (key_code == 'a')
	{
		i--;
		moved = moves(game, j, i);
		if (!moved)
			return (0);
		game->map[j][i + 1] = '0';
	}
	else if (key_code == 'd')
	{
		i++;
		moved = moves(game, j, i);
		if (!moved)
			return (0);
		game->map[j][i - 1] = '0';
	}
	ft_printf("moves: %d\n", game->moves);
	return (1);
}

static int	move_up_down(int key_code, t_idk *game, int j, int i)
{
	int	moved;

	moved = 0;
	if (key_code == 'w')
	{
		j--;
		moved = moves(game, j, i);
		if (!moved)
			return (0);
		game->map[j + 1][i] = '0';
	}
	else if (key_code == 's')
	{
		j++;
		moved = moves(game, j, i);
		if (!moved)
			return (0);
		game->map[j - 1][i] = '0';
	}
	ft_printf("moves: %d\n", game->moves);
	return (1);
}

static void	put_movement(t_idk *game)
{
	int	width;
	int	height;

	height = 0;
	while (height < game->heightmap)
	{
		width = 0;
		while (game->map[height][width])
		{
			if (game->map[height][width] == '0')
				mlx_put_image_to_window(game->mlx,
					game->window, game->floor, width * 100, height * 100);
			if (game->map[height][width] == 'P')
				mlx_put_image_to_window(game->mlx,
					game->window, game->player1, width * 100, height * 100);
			width++;
		}
		height++;
	}
}

int	controls(int key_code, t_idk *game)
{
	int	i;
	int	j;
	int	moved;

	moved = 0;
	i = game->i;
	j = game->j;
	if (key_code == 65307)
		exit_game(game);
	if (key_code == 'w' || key_code == 's')
		moved = move_up_down(key_code, game, j, i);
	if (key_code == 'a' || key_code == 'd')
		moved = move_left_right(key_code, game, j, i);
	if (moved)
		put_movement(game);
	return (1);
}
