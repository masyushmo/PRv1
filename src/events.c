/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:24:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/11/13 16:56:42 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int		new_dir(t_camera *camera)
{
	int	x;
	int	y;

	SDL_GetRelativeMouseState(&x, &y);
	if (x == 0 && y == 0)
		return (0);
	camera->dir[0] -= y * ROT_SPEED;
	camera->dir[1] -= x * ROT_SPEED;
	dir_angls(camera);
	return (1);
}

void	camera_move(t_camera *camera, SDL_Event event, const Uint8 *state)
{
	t_vector	temp;

	temp = (t_vector){0, 0, 0};
	if (event.key.keysym.sym == SDLK_w)
		temp[2] += MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_s)
		temp[2] -= MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_a)
		temp[0] -= MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_d)
		temp[0] += MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_SPACE && state[SDL_SCANCODE_TAB])
		temp[1] -= MOVE_SPEED;
	else if (event.key.keysym.sym == SDLK_SPACE)
		temp[1] += MOVE_SPEED;
	camera->pos += rotate_cam(camera, temp);
}

void	keyses(t_rtv *rtv)
{
	SDL_Event	event;
	const Uint8 *state;

	state = SDL_GetKeyboardState(NULL);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || EXIT)
			rtv->quit = 1;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_r)
				mouse_lock(rtv);
		}
		camera_move(&rtv->map.camera, event, state);
	}
	if (rtv->map.camera.rotate == 1)
		new_dir(&rtv->map.camera);
}
