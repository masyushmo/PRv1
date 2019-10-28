/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasyush <mmasyush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:51:51 by mmasyush          #+#    #+#             */
/*   Updated: 2019/10/28 20:23:29 by mmasyush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>
# ifdef __APPLE__
#  include "../frameworks/SDL2.framework/Headers/SDL.h"
# else
#  include <SDL2/SDL.h>
# endif
# include <stdio.h>

# define WIN_W 800
# define WIN_H 600
# define FOW 60
# define PI 3.14159265
# define FOW_RAD FOW * PI / 180
# define T_MIN 0
# define T_MAX 9e9
# define OBJ_MAX 50
# define VEC_SPLT 6
# define MOVE_SPEED 0.2
# define ROT_SPEED 0.2
# define D 0.1
# define VW	(1.732 * D)
# define VH	(VW * WIN_H / WIN_W)
# define BACKROUND (t_vector){0, 0, 0}
# define R "\033[0;31m"
# define G "\033[0;32*m"
# define B "\033[0;34m"
# define BADNUM "\033[0;31mBAD numbers \033[22;35m(•̀o•́)"
# define BADSPH "\033[0;31mBAD sphere data \033[22;35m(•̀o•́)"
# define BADCONE "\033[0;31mBAD cone data \033[22;35m(•̀o•́)"
# define BADCYL "\033[0;31mBAD cylinder data \033[22;35m(•̀o•́)"
# define BADPLN "\033[0;31mBAD plane data \033[22;35m(•̀o•́)"
# define BADLIG "\033[0;31mBAD light data \033[22;35m(•̀o•́)"
# define BADCAM "\033[0;31mBAD camera data \033[22;35m(•̀o•́)"
# define BADCOL "\033[0;31mBAD color \033[22;35m(•̀o•́)"
# define BADFILE "\033[0;31mBAD FILE  \033[22;35mლ(ಠ_ಠლ)"
# define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
# define MIN(a,b)			(((a) < (b)) ? (a) : (b))
# define MAX(a,b)			(((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi,ma)	MIN(MAX(a,mi),ma)

typedef struct s_sdl		t_sdl;
typedef struct s_rtv		t_rtv;
typedef struct s_map		t_map;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;
typedef struct s_light		t_light;
typedef struct s_calc		t_calc;
typedef struct s_plane		t_plane;
typedef struct s_raycheck	t_raycheck;
typedef struct s_camera		t_camera;
typedef struct s_inter		t_inter;
typedef union u_obj			t_obj;
typedef	double	t_vector __attribute__((vector_size(sizeof(double) * 4)));
typedef	double	t_roots __attribute__((vector_size(sizeof(double) * 2)));

struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
};

struct	s_camera
{
	t_vector	pos;
	t_vector	dir;
	double		sinx;
	double		siny;
	double		cosx;
	double		cosy;
	int			rotate;
};

struct	s_sphere
{
	int			spec;
	double		rad;
	t_vector	o;
	t_vector	col;
};

struct	s_plane
{
	int			spec;
	t_vector	o;
	t_vector	norm;
	t_vector	col;
};

struct	s_cylinder
{
	int			spec;
	double		rad;
	t_vector	o;
	t_vector	dir;
	t_vector	col;
};

struct	s_inter
{
	t_vector	oc;
	double		k1;
	double		k2;
	double		k3;
	double		dis;
};

struct	s_cone
{
	int			spec;
	double		rad;
	double		ang;
	t_vector	o;
	t_vector	dir;
	t_vector	col;
};

struct	s_light
{
	int			type;
	double		i;
	t_vector	vect;
};

struct	s_raycheck
{
	double		min_dist;
	int			close_obj;
};

struct	s_calc
{
	t_inter		inter;
	t_raycheck	check;
	t_vector	dir;
	t_vector	camera;
	t_vector	point;
	t_vector	normal;
	t_raycheck	shadow;
	t_vector	ld;
	t_vector	lr;
};

union	u_obj
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
	t_plane		plane;
	t_light		light;
};

struct	s_map
{
	int			onum;
	int			lnum;
	int			olist[OBJ_MAX];
	t_obj		obj[OBJ_MAX];
	t_light		light[OBJ_MAX];
	t_camera	camera;
};

struct	s_rtv
{
	int			quit;
	t_map		map;
	t_sdl		sdl;
	t_calc		calc;
};

enum	e_obj
{
	SPHERE = 0, CONE = 1, CYLINDER = 2, PLANE = 3
};

enum	e_light
{
	AMBIENT = 0, POINT = 1, DIRECT = 2
};

/*
**main.c
*/
int				main(int argc, char **argv);
/*
**print.c
*/
int				ft_error(char *message);
int				usage(void);
/*
**math.c
*/
t_vector		canvas_to_view(int x, int y);
t_vector		vect_mult(t_vector a, double k);
double			vect_dot(t_vector a, t_vector b);
double			vect_len(t_vector a);
t_vector		vect_div(t_vector a, double k);
/*
**math_v2.c
*/
void			dir_angls(t_camera *camera);
t_vector		rotate_cam(t_vector d, t_camera *cam);
int				rgb_color(t_vector color);
/*
**raytrace.c
*/
t_raycheck		close_inter(t_vector start, \
					t_vector dir, double min, t_rtv *rtv);
t_vector		trace_ray(t_rtv *rtv, t_calc *calc);
void			trace_loop(t_rtv *rtv);
int				loop(t_rtv *rtv);
/*
**parser.c
*/
void			check_color(t_vector color);
int				read_scene(t_map *map, char *filename);
int				check_obj(t_map *map, char *line);
/*
**sdl.c
*/
Uint32			get_pixel(SDL_Surface *texture, int x, int y);
void			set_pixel(int x, int y, Uint32 color, SDL_Surface *surr);
int				init_sdl(t_sdl *sdl);
void			mouse_lock(t_rtv *rtv);
/*
**geters.c
*/
t_vector		get_vect(char *line);
double			get_double(char *line, int skip, int comp);
int				get_int(char *line, int skip, int comp);
/*
**sphere.c
*/
int				save_sphere(t_map *map, char *line);
t_vector		sphere_norm(t_rtv *rtv, t_calc *calc);
t_roots			inter_sphere(t_vector camera, t_vector d, int n, t_rtv *rtv);
/*
**cylinder.c
*/
int				save_cyl(t_map *map, char *line);
t_vector		cyl_norm(t_rtv *rtv, t_calc *calc);
t_roots			inter_cyl(t_vector camera, t_vector d, int n, t_rtv *rtv);
/*
**plane.c
*/
int				save_plane(t_map *map, char *line);
t_vector		plane_norm(t_rtv *rtv, t_calc *calc);
t_roots			inter_plane(t_vector camera, t_vector d, int n, t_rtv *rtv);
/*
**cone.c
*/
int				save_cone(t_map *map, char *line);
t_vector		cone_norm(t_rtv *rtv, t_calc *calc);
t_roots			inter_cone(t_vector camera, t_vector d, int n, t_rtv *rtv);
/*
**light.c
*/
int				save_light(t_map *map, char *line);
double			calc_light(t_rtv *rtv, t_calc *calc, int spec);
/*
**camera.c
*/
int				save_camera(t_map *map, char *line);
/*
**events.c
*/
void			keyses(t_rtv *rtv);
int				new_dir(t_camera *camera);
/*
**check_prep.c
*/
void			prepare_all(t_map *map);

#endif
