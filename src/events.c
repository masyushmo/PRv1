/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:24:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/30 18:17:26 by mmasyush         ###   ########.fr       */
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
	camera->dir[0] += y * ROT_SPEED;
	camera->dir[1] += x * ROT_SPEED;
	dir_angls(camera);
	return (1);
}

void	camera_move(t_camera *camera, SDL_Event event, const Uint8 *state)
{
	if (event.key.keysym.sym == SDLK_w)
		camera->pos[2] += MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_s)
		camera->pos[2] -= MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_a)
		camera->pos[0] -= MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_d)
		camera->pos[0] += MOVE_SPEED;
	if (event.key.keysym.sym == SDLK_SPACE && state[SDL_SCANCODE_TAB])
		camera->pos[1] -= MOVE_SPEED;
	else if (event.key.keysym.sym == SDLK_SPACE)
		camera->pos[1] += MOVE_SPEED;
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
