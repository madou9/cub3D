/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihama <ihama@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:03:05 by kpuwar            #+#    #+#             */
/*   Updated: 2023/11/30 20:22:58 by ihama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
	checks if filename passed as arg has '.cub' extension.
	checks if file can be opened and read, if can be then
	it copies all the data from the file to buffer.
	split the buffer with '\n' to get the raw data in 2d array.
*/
void	get_raw(t_string file, t_map_data *map_data)
{
	char	*ext_ptr;
	int		fd_rd[2];
	char	buffer[5000000];

	ext_ptr = (file + ft_strlen(file)) - 4;
	if (ft_strncmp(ext_ptr, ".cub", 4))
		ft_error(EXT);
	fd_rd[0] = open(file, O_RDONLY);
	if (fd_rd[0] == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&buffer, 5000000);
	fd_rd[1] = read(fd_rd[0], &buffer, sizeof(buffer));
	if (fd_rd[1] == -1)
	{
		perror("Error reading file");
		close(fd_rd[0]);
		exit(EXIT_FAILURE);
	}
	ext_ptr = ft_strtrim(buffer, " \n");
	map_data->raw = ft_split(ext_ptr, '\n');
	free(ext_ptr);
	close(fd_rd[0]);
}

/*
	loops over the raw map data and checks for key count.
	every key should be present exactly one.
*/
void	check_keys(t_map_data *map_data, char keys[6][4])
{
	t_ushort	i;
	t_ushort	j;
	t_ushort	key_count[6];

	i = 0;
	ft_bzero(key_count, sizeof(t_ushort) * 6);
	while (map_data->raw[i][0] != '1' && map_data->raw[i][0] != '0' \
	&& map_data->raw[i] != NULL)
	{
		j = 0;
		while (j < 6)
		{
			if (ft_strncmp(map_data->raw[i], keys[j], ft_strlen(keys[j])) == 0)
				key_count[j] += 1;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 6)
		if (key_count[i++] != 1)
			ft_error(KEY);
}

/*
	gets all the textures paths from the file
*/
void	get_textures(t_map_data *map_data, char text_key[4][4])
{
	t_ushort	i;
	t_ushort	j;
	t_string	*temp_ptr;

	i = 0;
	while (map_data->raw[i][0] != '1' && map_data->raw[i][0] != '0' \
	&& map_data->raw[i] != NULL)
	{
		j = 0;
		while (j < 4)
		{
			if (ft_strncmp(map_data->raw[i], text_key[j], 3) == 0)
			{
				temp_ptr = ft_split(map_data->raw[i], ' ');
				map_data->texture[j] = ft_strdup(temp_ptr[1]);
				ft_free_split(temp_ptr);
			}
			j++;
		}
		i++;
	}
}

/*
	gets all the color info for floor and ceiling in int format.
*/
void	get_colors(t_map_data *map_data)
{
	t_ushort	i;
	short		*arr;
	t_string	*temp_ptr[2];

	i = -1;
	while (map_data->raw[++i][0] != '1' && map_data->raw[i][0] != '0' \
	&& map_data->raw[i] != NULL)
	{
		arr = NULL;
		if (ft_strncmp(map_data->raw[i], "F ", 2) == 0)
			arr = &map_data->floor[0];
		else if (ft_strncmp(map_data->raw[i], "C ", 2) == 0)
			arr = &map_data->ceil[0];
		if (arr != NULL)
		{
			temp_ptr[0] = ft_split(map_data->raw[i], ' ');
			temp_ptr[1] = ft_split(temp_ptr[0][1], ',');
			arr[R] = ft_atoi(temp_ptr[1][R]);
			arr[G] = ft_atoi(temp_ptr[1][G]);
			arr[B] = ft_atoi(temp_ptr[1][B]);
			ft_free_split(temp_ptr[0]);
			ft_free_split(temp_ptr[1]);
		}
	}
}

/*
	checks if RGB values for the colors are in the range [0,255]
*/
void	check_rgb_values(t_map_data *map_data)
{
	t_ushort	i;

	i = 0;
	while (i < 3)
	{
		if (map_data->ceil[i] < 0 || map_data->ceil[i] > 255)
			ft_error(RGB);
		if (map_data->floor[i] < 0 || map_data->floor[i] > 255)
			ft_error(RGB);
		i++;
	}
}

/*
for (size_t i = 0; i < 4; i++)
	printf("%s %s\n", keys[i], map_data->texture[i]);
printf("C %d,%d,%d\n", map_data->ceil[R], map_data->ceil[G], map_data->ceil[B]);
printf("F %d,%d,%d", map_data->floor[R], map_data->floor[G], map_data->floor[B]);
*/
