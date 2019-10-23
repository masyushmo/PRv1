/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:24:28 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/23 15:25:10 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	keyses(t_rtv *rtv)
{
    int chosen = 1;
	SDL_Event	event;
    const Uint8 *state;

	state = SDL_GetKeyboardState(NULL);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || EXIT)
			rtv->quit = 1;
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == 1073741920)
                rtv->map.obj[chosen].sphere.o[1] += 0.1;
            if (event.key.keysym.sym == 1073741914)
                rtv->map.obj[chosen].sphere.o[1] -= 0.1;
            if (event.key.keysym.sym == 1073741916)
                rtv->map.obj[chosen].sphere.o[0] -= 0.1;
            if (event.key.keysym.sym == 1073741918)
                rtv->map.obj[chosen].sphere.o[0] += 0.1;
            if (event.key.keysym.sym == 1073741917 && state[SDL_SCANCODE_TAB])
                rtv->map.obj[chosen].sphere.o[2] -= 0.1;
            else if (event.key.keysym.sym == 1073741917)
                rtv->map.obj[chosen].sphere.o[2] += 0.1;
            if (event.key.keysym.sym == 1073741910)
                rtv->map.obj[chosen].sphere.spec -= 20;
            if (event.key.keysym.sym == 1073741911)
                rtv->map.obj[chosen].sphere.spec += 20;
            if (rtv->map.obj[chosen].sphere.spec > 1000)
                rtv->map.obj[chosen].sphere.spec = 1000;
            if (rtv->map.obj[chosen].sphere.spec < 0)
                rtv->map.obj[chosen].sphere.spec = 0;
           
            //     rtv->map.obj[0].sphere.o[1] += 1;
            //     rtv->map.obj[0].sphere.o[2] += 1;
            // }

        }
	}
}