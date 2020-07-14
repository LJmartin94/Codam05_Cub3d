/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub3d.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 21:57:22 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/14 22:16:14 by limartin      ########   odam.nl         */
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

typedef	struct	s_mapinfo
{
	int		noerror;
	int		fd;
	long	resx;
	long	resy;
	char	*northtex;
	char	*southtex;
	char	*westtex;
	char	*easttex;
	char	*spritetex;
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
	int		x;
	char	facing;
}				t_mapinfo;

int				ft_printall(t_mapinfo *m); //DEBUG ONLY

int				main(int argc, char **argv);

int				ft_prelimcheck(int argc, char *mapfile, t_mapinfo *m);
int				ft_checkcub(char *mapfile);
int				ft_parserror(int type, t_mapinfo *m);

t_mapinfo		ft_constructor(t_mapinfo mapinfo);
int				ft_parser(t_mapinfo *mapinfo);
int				ft_elemxref(t_mapinfo *mapinfo, char flag);
int				ft_skipspace(char *line, int *i);

char			ft_gettag(char *line, int *i);
int				ft_writevals(t_mapinfo *mapinfo, char tag, char *line, int *i);
void			ft_fetchpath(t_mapinfo *mapinfo, char tag, char *line, int *i);
int				ft_fetchclr(t_mapinfo *mapinfo, char tag, char *line, int *i);
int				ft_fetchres(t_mapinfo *mapinfo, char *line, int *i);

int				ft_processmap(t_mapinfo *m);

void			ft_quit(int ret, t_mapinfo *mapinfo);

int				get_next_line(int fd, char **line);
int				ft_fill_remainder(char *remainder, int fd, int *nl);
int				ft_handle_remainder(char **line, char *rmn, int *i, int *nl);
void			ft_clear_remainder(char *remainder, int j);
int				ft_gnlerror(char *remainder, char **line);

int				ft_malloc_expander(char **str, int size, int grow);
size_t			ft_linelen(const char *s, char n);
char			*ft_strstr(const char *haystack, const char *needle);

#endif
