
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


#define DEFAULT_SIZE_W 512
#define DEFAULT_SIZE_H 512


void print_info(void)
{
	printf("C_DIP [MAIN.C]\n");
}


void load_image(char *image_filename, uint8_t *image_buffer)
{
	FILE *fd;
	size_t file_size;
	uint32_t counter = 0;
	uint8_t tmp_byte;
	uint32_t bytes_readed;

	if((fd = fopen(image_filename, "rb")) == NULL)
	{
		fprintf(stderr, "ERROR OPEN FILE: %s\n", image_filename);
		exit(1);
	}


	fseek(fd, 0L, SEEK_END);
	file_size = ftell(fd);
	rewind(fd);

	printf("FILE SIZE: %d [%s]\n", file_size, image_filename);


/*
	for( ; counter < file_size; counter++)
	{

	}

*/

	bytes_readed = fread(image_buffer, file_size, 1, fd);

	printf("fread ret code = %d\n", bytes_readed);


	fclose(fd);


}


void print_image_array(uint8_t *image_buffer, uint32_t image_size)
{
	uint32_t counter = 0;
	for( ; counter < image_size; counter++)
		printf("%d\n", image_buffer[counter]);
}


int32_t main(void)
{

	char *filename = "baboon.bin";
	uint8_t image_array[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint32_t image_size = DEFAULT_SIZE_W * DEFAULT_SIZE_H;

	print_info();
	printf("ARRAY SIZE: %d*%d = %d\n", DEFAULT_SIZE_W, DEFAULT_SIZE_H, sizeof(image_array));
	printf("DEFAULT SIZE W: %d\n", DEFAULT_SIZE_W);
	printf("DEFAULT SIZE H: %d\n", DEFAULT_SIZE_H);


	load_image(filename, image_array);

	print_image_array(image_array, image_size);

	printf("%d\n", image_array[0]);
	printf("%d\n", image_array[1]);



	return 0;

}

