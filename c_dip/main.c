
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

	printf("[load_image] fread ret code = %d\n", bytes_readed);


	fclose(fd);


}


void save_image(char *image_filename, uint8_t *image_buffer, uint32_t buffer_size)
{
	FILE *fd;
	size_t file_size;
	uint32_t counter = 0;
	uint8_t tmp_byte;
	uint32_t bytes_writed;

	if((fd = fopen(image_filename, "wb")) == NULL)
	{
		fprintf(stderr, "ERROR OPEN FILE FOR SAVE: %s\n", image_filename);
		exit(1);
	}


//	fseek(fd, 0L, SEEK_END);
//	file_size = ftell(fd);
//	rewind(fd);

//	printf("FILE SIZE: %d [%s]\n", file_size, image_filename);
	printf("BUFFER SIZE: %d [->%s]\n", buffer_size, image_filename);

/*
	for( ; counter < file_size; counter++)
	{

	}

*/

	bytes_writed = fwrite(image_buffer, buffer_size, 1, fd);

	printf("[save_image] fwrite ret code = %d\n", bytes_writed);


	fclose(fd);


}


void print_image_array(uint8_t *image_buffer, uint32_t image_size)
{
	uint32_t counter = 0;
	for( ; counter < image_size; counter++)
		printf("%d\n", image_buffer[counter]);
}

void test_func(uint8_t *input_buffer, uint8_t *output_buffer, uint32_t buffer_size)
{

	uint32_t i = 0;
	for( ; i < buffer_size; i++)
	{
		output_buffer[i] = 0xFF - input_buffer[i];
	}

}

void transpose_func(uint8_t *input_buffer, uint8_t *output_buffer, uint32_t w, uint32_t h)
{
	uint32_t buffer_size = w*h;
	uint32_t i = 0;
	uint32_t k = 0;
	uint32_t j;

	for( ; i < w; i++)
	{
		for(j = 0; j < h; j++, k++)
		{
			output_buffer[k] = input_buffer[j*w + i];
		}
	}

}




int32_t main(void)
{

	char *filename = "baboon.bin";
	char *out_filename = "baboon_out.bin";
	char *out_filename_2 = "baboon_out_t.bin";

	uint8_t image_array[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint8_t tmp_buffer[DEFAULT_SIZE_W * DEFAULT_SIZE_H + 1024] = { 0 };
	uint32_t image_size = DEFAULT_SIZE_W * DEFAULT_SIZE_H;
	uint32_t buffer_size = DEFAULT_SIZE_W * DEFAULT_SIZE_H;
	uint32_t w_size = DEFAULT_SIZE_W;
	uint32_t h_size = DEFAULT_SIZE_H;


	print_info();
	printf("ARRAY SIZE: %d*%d = %d\n", DEFAULT_SIZE_W, DEFAULT_SIZE_H, sizeof(image_array));
	printf("DEFAULT SIZE W: %d\n", DEFAULT_SIZE_W);
	printf("DEFAULT SIZE H: %d\n", DEFAULT_SIZE_H);


	load_image(filename, image_array);

//	print_image_array(image_array, image_size);

	printf("%d\n", image_array[0]);
	printf("%d\n", image_array[1]);

	test_func(image_array, tmp_buffer, buffer_size);
	save_image(out_filename, tmp_buffer, buffer_size);

	transpose_func(image_array, tmp_buffer, w_size, h_size);
	save_image(out_filename_2, tmp_buffer, buffer_size);

	return 0;

}

