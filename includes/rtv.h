/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:51:51 by mmasyush          #+#    #+#             */
/*   Updated: 2019/09/16 13:12:26 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>
#ifdef __APPLE__
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
# else
#  include <SDL2/SDL.h>
#endif
#include <stdio.h>

# define WIN_W 1280
# define WIN_H 720
# define FOW 60
# define PI 3.14159265
# define FOW_RAD FOW * PI / 180
# define T_MIN 0
# define T_MAX 2147483647
# define OBJ_MAX 10
# define VEC_SPLT 6

# define D 1
# define VW	(1.732 * D)
# define VH	(VW * WIN_H / WIN_W)

# define R "\033[0;31m"
# define G "\033[0;32*m"
# define B "\033[0;34m"
# define BADNUM "\033[0;31mBAD numbers \033[22;35m(•̀o•́)"
# define BADFILE "\033[0;31mBAD FILE  \033[22;35mლ(ಠ_ಠლ)"

# define MIN(a,b)				(((a) < (b)) ? (a) : (b))
# define MAX(a,b)				(((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi,ma)		MIN(MAX(a,mi),ma)

typedef struct  s_sdl       t_sdl;
typedef struct  s_rtv       t_rtv;
typedef struct  s_vector    t_vector;
typedef struct  s_map    t_map;
typedef struct  s_sphere    t_sphere;
typedef struct  s_inter     t_inter;
typedef union   u_obj       t_obj;

struct  s_sdl
{
    SDL_Window  *window;
    SDL_Surface *surface;
};

struct  s_vector
{
    int         x;
    int         y;
    int         z;
};

struct  s_sphere
{
    int         rad;
    t_vector    o;
    t_vector    col;
};

struct  s_inter
{
   int          t1;
   int          t2;
};

union   u_obj
{
    t_sphere    sphere;
};

struct  s_map
{
    int         obj_num;
    t_obj       obj[10]; 
};

struct s_rtv
{
    t_map       map;
    t_sdl       sdl;
};


/*
**main.c
*/
int             main(int argc, char **argv);
/*
**print.c
*/
int			    ft_error(char *message);
int			    usage(void);
/*
**math.c
*/
t_vector        canvas_to_view(int x, int y);
/*
**raytrace.c
*/
t_vector        trace_ray(t_vector camera, t_vector d, t_rtv *rtv);
void            trace_loop(t_rtv *rtv);
int			loop(t_rtv *rtv);
/*
**parser.c
*/
int             read_scene(t_rtv *rtv, char *filename);
int			    check_obj(t_rtv *rtv, char *line, int *b);
t_vector	    get_vector_value(char *line);
int			    et_int_value(char *line, int skip, int comp);
int			    save_sphere(t_rtv *rtv, char *line);
/*
**sdl.c
*/
void	        put_pixel(int x, int y, Uint32 color, SDL_Surface *surr);
int		        init_sdl(t_sdl  *sdl);
#endif
