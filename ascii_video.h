#ifndef _ASCII_VIDEO_H_
#define _ASCII_VIDEO_H_

typedef struct {
	int width;
	int height;
	int scale;
	unsigned char * data;	
} pgm_image;

void print_ascii(int x);

pgm_image * get_pgm(char * path);

void print_pgm(pgm_image * img, int scale);

int get_color(pgm_image * img, int scale, int i, int j);

#endif //_ASCII_VIDEO_H_
