#include <stdio.h>
#include <string.h>
#include "ascii_video.h"

int main(int argc, char * argv[]) {
	int len = strlen(argv[1]);

	pgm_image * img = get_pgm(argv[1]);
	int scale = argv[2][0]-'0';
	print_pgm(img, scale);

	return 0;
}
