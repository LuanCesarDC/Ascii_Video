#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ascii_video.h"

#define BUFFER_SIZE 64

void print_ascii(int x) {
	unsigned char grayscale[11] = 	" .:-=+*#%%@";
	unsigned char c = grayscale[(int)x/25];
	printf("%c", c);
}

pgm_image * get_pgm(char * path) {
	int len = strlen(path);
	FILE * ptr;
	unsigned char buffer[BUFFER_SIZE];
	pgm_image * img = (pgm_image *) malloc(sizeof(pgm_image));
	
	if(path[len-4] != 'p' || path[len-4] != 'g' || path[len-4] != 'm') {
		char command[BUFFER_SIZE];
		
		sprintf(command, "convert %s 1.pgm", path);
		system(command);
		strcpy(path, "1.pgm");
	}

	ptr = fopen(path, "rb");
	
	fgets(buffer, BUFFER_SIZE, ptr);
	if(buffer[1] != '5') {
		printf("Tipo de arquivo incorreto!\n");
		return NULL;
	}
	
	fgets(buffer, BUFFER_SIZE, ptr);
	sscanf(buffer, "%d %d", &img->width, &img->height);
	
	fgets(buffer, BUFFER_SIZE, ptr);
	sscanf(buffer, "%d", &img->scale);
	
	img->data = (unsigned char *) malloc(img->width*img->height*sizeof(unsigned char));
	fread(img->data, img->width*img->height*sizeof(unsigned char), 1, ptr);
	
	system("rm 1.pgm");
	return img;
}

void print_pgm(pgm_image * img, int scale) {
	int i, j;
	for(i=0;i<img->height;i+=2*scale) {
		for(j=0;j<img->width;j += 1*scale) {
			int color = get_color(img, scale, i, j);
			//printf("%02X ", img->data[i*img->width+j]);
			print_ascii(color);
		}
		printf("\n");
	}
}

int get_color(pgm_image * img, int scale, int i, int j) {
	int l, m;
	int color = 0, div = 0;
	for(l=i;l<img->height && l<i+2*scale;l++) {
		for(m=j;m<img->width && m < j+scale;m++) {
			color += img->data[l*img->width+m];
			div++;
		}
	}
	return (int) color/div;
}




