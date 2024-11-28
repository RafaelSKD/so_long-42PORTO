/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:43 by rafaefer          #+#    #+#             */
/*   Updated: 2024/10/07 16:48:08 by rafaefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	put_imgs_to_variables(t_idk *game)
{
	int	i;
	int	j;

	game->floor = mlx_xpm_file_to_image(game->mlx, "textures/Floor.xpm", &i,
			&j);
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/Wall.xpm", &i,
			&j);
	game->player1 = mlx_xpm_file_to_image(game->mlx, "textures/P1.xpm", &i,
			&j);
	game->collectable = mlx_xpm_file_to_image(game->mlx, "textures/Coin.xpm",
			&i, &j);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/Exit.xpm", &i, &j);
	if (!game->floor || !game->wall || !game->player1
		||!game->collectable || !game->exit)
		return (0);
	return (1);
}

static void	put_things(t_idk *game, int height, int width)
{
	if (game->map[height][width] == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->wall,
			width * 100, height * 100);
	if (game->map[height][width] == '0')
		mlx_put_image_to_window(game->mlx, game->window, game->floor,
			width * 100, height * 100);
	if (game->map[height][width] == 'P')
		mlx_put_image_to_window(game->mlx, game->window, game->player1,
			width * 100, height * 100);
	if (game->map[height][width] == 'C')
	{
		mlx_put_image_to_window(game->mlx, game->window, game->collectable,
			width * 100, height * 100);
		game->collectables++;
	}
	if (game->map[height][width] == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->exit,
			width * 100, height * 100);
}

void	put_img_in_game(t_idk *game)
{
	int	height;
	int	width;

	height = 0;
	game->collectables = 0;
	while (height < game->heightmap)
	{
		width = 0;
		while (game->map[height][width])
		{
			put_things(game, height, width);
			width++;
		}
		height++;
	}
}
