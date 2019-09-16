/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:49:01 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/04 15:49:01 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv.h"

int		init_sdl(t_sdl  *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (error((char *)SDL_GetError()));
	if (!(sdl->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_W, \
		WIN_H, SDL_WINDOW_SHOWN)))
		return (error((char *)SDL_GetError()));
	if (!(sdl->surface = SDL_GetWindowSurface(sdl->window)))
		return (error((char *)SDL_GetError()));
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(sdl->window, 1);
	SDL_SetRelativeMouseMode(1);
	return (1);
}

int    main(int argc, char **argv)
{
    t_rtv   rtv;

    if (argc == 2)
    {
        if(!read_scene(&rtv, argv[1]))
            return (1);
        if(!init_sdl(&rtv.sdl))
            return (1);
    }
    else
        return (usage());
}
