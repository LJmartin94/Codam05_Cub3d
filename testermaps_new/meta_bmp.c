/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_bmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 15:56:12 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/12 19:35:02 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
//# include <mlx.h>

/*
** For more information on what metadata is being stored
** in the header of a bmp file, visit
** https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
*/


//comment this function out if mlx library is not available in same repo as this file,
//bpp will display as -42 instead.
// int	fetch_bpp()
// {
// 	void *mlx = mlx_init();
// 	void *img;
// 	int	realbpp;
// 	int junk;
// 	int also_junk;

// 	img = mlx_new_image(mlx, 42, 42);
// 	img = mlx_get_data_addr(img, &realbpp, &junk, &also_junk);
// 	return (realbpp);
// }

int		main(int argc, char **argv)
{
	int				fd;
	int				rd;
	char			*buf;
	
	unsigned int	needed_filesize;
	unsigned int	actual_filesize;
	
	char			c;
	unsigned int	ui;
	signed int		si;

	int width;
	int height;
	unsigned int bpp;
	unsigned int real_bpp = -42;

	// real_bpp = fetch_bpp;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		rd = 1;
		actual_filesize = 0;
		while (rd > 0)
		{
			rd = read(fd, buf, 100000);
			actual_filesize = actual_filesize + rd;
		}
		lseek(fd, SEEK_SET, 0);
		read(fd, &c, sizeof(char));
		printf("FileType 0-1: |%c", c);
		read(fd, &c, sizeof(char));
		printf("%c| (should be |BM|)\n", c);
		read(fd, &ui, sizeof(unsigned int));
		printf("FileSize 2-5: |%u|, is actually |%u|\n", ui, actual_filesize);
		ui = 0;
		read(fd, &ui, (2 * sizeof(unsigned char)));
		printf("Reserved 6-7: |%u| (should be set to |0|)\n", ui);
		read(fd, &ui, (2 * sizeof(unsigned char)));
		printf("Reserved 8-9: |%u| (should be set to |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("PixelDataOffset 10-13: |%u| (should be |54|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("Headersize 14-17: |%u| (should be |40|)\n", ui);
		read(fd, &si, sizeof(int));
		printf("ImageWidth 18-21: |%i| (should be 'width')\n", si);
		width = si;
		read(fd, &si, sizeof(int));
		printf("ImageHeight 22-25: |%i| (should be 'height')\n", si);
		height = si;
		ui = 0;
		read(fd, &ui, (2 * sizeof(unsigned char)));
		printf("Planes 26-27: |%u| (should be |1|)\n", ui);
		ui = 0;
		read(fd, &ui, (2 * sizeof(unsigned char)));
		printf("BitsPerPixel 28-29: |%u| (should be |%u|, if mlx library is accessible)\n", ui, real_bpp);
		bpp = ui;
		read(fd, &ui, sizeof(unsigned int));
		printf("Compression 30-33: |%u| (should be |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("ImageSize 34-37: |%u| (should be |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("XpixelsPerMeter  38-41: |%u| (should be |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("YpixelsPerMeter  42-45: |%u| (should be |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("TotalColours  46-49: |%u| (should be |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("ImportantColours  50-53: |%u| (should be |0|)\n", ui);
		read(fd, &ui, sizeof(unsigned int));
		printf("First pixel 54-57 : |%u|\n", ui);
		needed_filesize = width * height * bpp / 8 + 54;
		printf("Actual filesize (%u) ought to be %u, if width height and bpp were returned correctly\n", actual_filesize, needed_filesize);
	}
	else
	{
		printf("Please provide your bmp file as first and only argument");
	}
	return (0);
}
