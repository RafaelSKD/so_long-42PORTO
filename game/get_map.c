/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:50 by rafaefer          #+#    #+#             */
/*   Updated: 2024/10/07 16:49:58 by rafaefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	check_width(t_idk *game)
{
	int		height;
	int		new_width;

	height = 0;
	while (height < game->heightmap)
	{
		new_width = 0;
		while (game->map[height][new_width] != '\0')
			new_width++;
		if (game->map[height][new_width - 1] == '\n')
			new_width--;
		if (new_width > game->widthmap)
			game->widthmap = new_width;
		height++;
	}
}

static int	width_of_map(char *string)
{
	static int	width;

	width = 0;
	while (string[width] != '\0')
		width++;
	if (string[width - 1] == '\n')
		width--;
	return (width);
}

static void	find_player(t_idk *game)
{
	int	height;
	int	width;

	height = 0;
	while (height < game->heightmap)
	{
		width = 0;
		while (game->map[height][width])
		{
			if (game->map[height][width] == 'P')
			{
				game->i = width;
				game->j = height;
			}
			if (game->map[height][width] == 'C')
				game->collectables++;
			width++;
		}
		height++;
	}
}

static int	add_line(t_idk *game, char *line)
{
	char	**temporary;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->heightmap++;
	temporary = ft_calloc(sizeof(char *), (game->heightmap + 1));
	if (!temporary)
		return (0);
	temporary[game->heightmap] = NULL;
	while (i < game->heightmap - 1)
	{
		temporary[i] = game->map[i];
		i++;
	}
	temporary[i] = line;
	if (game->map)
		free(game->map);
	game->map = temporary;
	return (1);
}

int	map_reading(t_idk *game, char **argv)
{
	char		*readmap;

	readmap = NULL;
	game->fd = open(argv[1], O_RDONLY);
	while (1)
	{
		readmap = get_next_line(game->fd);
		if (!add_line(game, readmap))
			break ;
	}
	close(game->fd);
	find_player(game);
	if (!game->map || !game->map[0])
	{
		ft_printf("Error\n Map don't exist\n");
		exit_game(game);
	}
	game->widthmap = width_of_map(game->map[0]);
	check_width(game);
	return (1);
}
