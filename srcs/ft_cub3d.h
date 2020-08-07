/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub3d.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 21:57:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/08/07 14:48:19 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <mlx.h>

typedef	struct	s_mapinfo
{
	struct s_mapinfo	*copy;
	int					noerror;
	int					fd;
	long				resx;
	long				resy;
	char				*northtex;
	char				*southtex;
	char				*westtex;
	char				*easttex;
	char				*spritetex;
	int					spriteno;
	int					fr;
	int					fg;
	int					fb;
	int					cr;
	int					cg;
	int					cb;
	int					x;
	char				facing;
	int					posy;
	int					posx;
	int					mapstart;
	int					ydim;
	char				**map;
}				t_mapinfo;

typedef	struct	s_img
{
	void		*cont;
	char		*addr;
	int			bits_per_pixel;
	int			line_bytes;
	int			endian;
}				t_img;

typedef	struct	s_raydata
{
	double		xpos;
	double		ypos;
	double		xdir;
	double		ydir;
	double		xplane;
	double		yplane;
	double		time;
	double		oldtime;
}				t_raydata;

typedef struct	s_data
{
	t_mapinfo		*m;
	t_img			imga;
	t_img			imgb;
	t_raydata		r;
	void			*mlx;
	void			*win;
	long			frame;
}				t_data;

int				ft_printall(t_mapinfo *m); //DEBUG ONLY

int				main(int argc, char **argv);

int				ft_prelimcheck(int argc, char *mapfile, t_mapinfo *m);
int				ft_checkcub(char *mapfile);
int				xt_parserror(int type, t_mapinfo *m);
int				xt_mallocerror(t_mapinfo *m);
int				xt_mlxerror(t_mapinfo *m);

t_mapinfo		ft_constructor(t_mapinfo *mapinfo);
void			ft_parser(t_mapinfo *mapinfo);
int				ft_elemxref(t_mapinfo *mapinfo, char flag);
int				ft_skipspace(char *line, int *i);

char			ft_gettag(char *line, int *i);
int				ft_writevals(t_mapinfo *mapinfo, char tag, char *line, int *i);
void			ft_fetchpath(t_mapinfo *mapinfo, char tag, char *line, int *i);
int				ft_fetchclr(t_mapinfo *mapinfo, char tag, char *line, int *i);
int				ft_fetchres(t_mapinfo *mapinfo, char *line, int *i);

int				ft_processmap(t_mapinfo *m, char *cub);
int				ft_getmap(t_mapinfo *m, char *cub);
void			ft_scanmap(t_mapinfo *m);
void			ft_copymap(t_mapinfo *original, t_mapinfo *copy);
void			ft_floodfill(t_mapinfo *ffm, int x, int y);

t_data			ft_window(t_mapinfo *m);
void			ft_resize(void *mlx, t_mapinfo *m);
void			ft_createimgs(t_img *a, t_img *b, void *mlx, t_mapinfo *m);
void			ft_put_pixel_img(t_img *img, int x, int y, int colour);

int				ft_mlx_run(t_data *data);

void			xt_quit(int ret, t_mapinfo *mapinfo);
int				ft_clearcopy(int error, t_mapinfo *cpy, t_mapinfo *org);

int				get_next_line(t_mapinfo *m, char **line);
int				ft_fill_remainder(char *remainder, int fd, int *nl);
int				ft_handle_remainder(char **line, char *rmn, int *i, int *nl);
void			ft_clear_remainder(char *remainder, int j);
int				xt_gnlerror(char *remainder, char **line, t_mapinfo *m);

int				ft_malloc_expander(char **str, int size, int grow);
size_t			ft_linelen(const char *s, char n);
char			*ft_strstr(const char *haystack, const char *needle);
char			ft_charinset(char tofind, char *set);

#endif
