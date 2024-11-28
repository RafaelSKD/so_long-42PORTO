/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:47 by rafaefer          #+#    #+#             */
/*   Updated: 2024/10/07 16:49:35 by rafaefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	count_checker(t_idk *game, int height, int width)
{
	if (game->map[height][width] != '1' &&
		game->map[height][width] != '0' &&
		game->map[height][width] != 'C' &&
		game->map[height][width] != 'E' &&
		game->map[height][width] != 'P' &&
		game->map[height][width] != '\n')
	{
		ft_printf("Error\nHere: %c\n", game->map[height][width]);
		exit_game(game);
	}
	if (game->map[height][width] == 'P')
		game->p_count++;
	if (game->map[height][width] == 'E')
		game->e_count++;
	if (game->map[height][width] == 'C')
		game->c_count++;
}

static void	check_count_and_rectangular(t_idk *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->heightmap - 1)
	{
		width = 0;
		while (width <= game->widthmap)
		{
			count_checker(game, height, width);
			width++;
		}
		height++;
	}
	if (!(game->p_count == 1 && game->e_count == 1 && game->c_count >= 1))
	{
		ft_printf("Error\nSomething is wrong!\n");
		ft_printf("either player, exit or collectable issue\n");
		exit_game(game);
	}
}

int	check_errors(t_idk *game)
{
	int	i;
	int	j;

	i = game->widthmap;
	j = 0;
	while (j < i)
	{
		if (!(game->map[0][j] == '1'
			&& game->map[game->heightmap - 1][j] == '1'))
			return (0);
		j++;
	}
	i = game->heightmap;
	j = 0;
	while (j < i)
	{
		if (!(game->map[j][0] == '1'
			&& game->map[j][game->widthmap - 1] == '1'))
			return (0);
		j++;
	}
	check_count_and_rectangular(game);
	if (!check_path(game))
		exit_game(game);
	return (1);
}
