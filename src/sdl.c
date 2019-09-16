/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:55:36 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/16 12:55:37 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv.h"

int		init_sdl(t_sdl  *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->window = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_W, \
		WIN_H, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->surface = SDL_GetWindowSurface(sdl->window)))
		return (error_message((char *)SDL_GetError()));
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(sdl->window, 1);
	SDL_SetRelativeMouseMode(1);
	return (1);
}