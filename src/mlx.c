/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihama <ihama@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:13:14 by ihama             #+#    #+#             */
/*   Updated: 2023/11/30 04:15:55 by ihama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	set_mlx_elements(t_game_data *game_data)
{
	short	i;

	i = -1;
	while (++i < 4)
	{
		game_data->walls[i] = mlx_load_png(game_data->map_data.texture[i]);
		if (game_data->walls[i] == NULL)
			ft_error("mlx");
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game_data->mlx = mlx_init(1920, 1080, "cub3D - kpuwar & ihama", true);
	if (game_data->mlx == NULL)
		ft_error("mlx");
	game_data->img = mlx_new_image(game_data->mlx, 1920, 1080);
	if (game_data->img == NULL)
		ft_error("mlx");
	if (mlx_image_to_window(game_data->mlx, game_data->img, 0, 0) == -1)
		ft_error("mlx");
}
