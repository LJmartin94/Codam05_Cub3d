/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_drawsprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 16:49:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/02 15:18:14 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_scanforsprites(t_data *d);
void	ft_handlesprites(t_data *d);
void	ft_sortsprites(t_sprite **sprite, int l, int r, t_sprite val);
int		ft_transformsprite(t_data *d, int s);

void	ft_lodevsprites(t_data *d, double transformX, double transformY);
int		ft_getspritetexel(t_data *d, int texX, int texY);

int		ft_scanforsprites(t_data *d)
{
	int y;
	int x;
	int s;

	y = 0;
	s = 0;
	while (d->m->map[y] != NULL)
	{
		x = 0;
		while (d->m->map[y][x] != '\0')
		{
			if (d->m->map[y][x] == '2' && d->m->copy->map[y][x] == 'x')
			{
				d->m->sprites[s].y = y + 0.5;
				d->m->sprites[s].x = x + 0.5;
				s++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_handlesprites(t_data *d)
{
	int	s;

	s = 0;
	while (s < d->m->spriteno)
	{
		d->m->sprites[s].dist = pow((d->r.pxpos - d->m->sprites[s].x), 2) + \
		pow((d->r.pypos - d->m->sprites[s].y), 2);
		s++;
	}
	ft_sortsprites(&(d->m->sprites), 0, d->m->spriteno - 1, d->m->sprites[0]);
	s = 0;
	while (s < d->m->spriteno)
	{
		ft_transformsprite(d, s);
		s++;
	}
}

void	ft_sortsprites(t_sprite **sprite, int l, int r, t_sprite val)
{
	int s;
	int ch;
	int d;

	s = l;
	ch = 0;
	d = 1;
	while (r > l)
	{
		ch = ((*sprite)[s].dist * d < (*sprite)[s + d].dist * d) ? 0 : ch + 1;
		if ((*sprite)[s].dist * d < (*sprite)[s + d].dist * d)
		{
			val = (*sprite)[s];
			(*sprite)[s] = (*sprite)[s + d];
			(*sprite)[s + d] = val;
		}
		s = s + d;
		if ((d == -1 && s == l) || (d == 1 && s == r))
		{
			d = d * -1;
			s = s + (ch + 1) * d;
			l = (d == 1) ? s : l;
			r = (d == -1) ? s : r;
		}
	}
}

int		ft_transformsprite(t_data *d, int s)
{
	double	xsprite;
	double	ysprite;
	double	xval;

	xsprite = d->m->sprites[s].x - d->r.pxpos;
	ysprite = d->m->sprites[s].y - d->r.pypos;
	xval = (1.0 / (d->r.xplane * d->r.pydir - d->r.pxdir * d->r.yplane)) * \
	(d->r.pydir * xsprite - d->r.pxdir * ysprite);
	ysprite = (1.0 / (d->r.xplane * d->r.pydir - d->r.pxdir * d->r.yplane)) * \
	(-1 * d->r.yplane * xsprite + d->r.xplane * ysprite);
	xsprite = xval;
	ft_lodevsprites(d, xsprite, ysprite);
	return (0);
}

void	ft_lodevsprites(t_data *d, double transformX, double transformY)
{
	  int spriteScreenX = (int)((d->m->resx / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(d->m->resy / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + d->m->resy / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + d->m->resy / 2;
      if(drawEndY >= d->m->resy) drawEndY = d->m->resy - 1;

      //calculate width of the sprite
      int spriteWidth = abs((int)(d->m->resy / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= d->m->resx) drawEndX = d->m->resx - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * d->tex.sptex.width / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < d->m->resx && transformY < d->m->zbuf[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int g = (y) * 256 - d->m->resy * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((g * d->tex.sptex.height) / spriteHeight) / 256;
			t_img	*img;
			int		colour;
		
			img = (d->frame % 2 == 1) ? &(d->imga) : &(d->imgb);
			colour = ft_getspritetexel(d, texX, texY);
            if((colour & 0x00FFFFFF) != 0)
		   		ft_put_pixel_img(img, stripe, y, colour);
        //Uint32 color = texture[sprite[spriteOrder[i]].texture][d->tex.sptex.width * texY + texX]; //get current color from the texture
				//   buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
}

int		ft_getspritetexel(t_data *d, int xtex, int ytex)
{
	t_img	tex;
	char	*texel;

	tex = d->tex.sptex;
	texel = tex.addr + (ytex * tex.line_bytes + \
	xtex * (tex.bits_per_pixel / 8));
	return (*(unsigned int*)texel);
}
