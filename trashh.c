
static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Try to load the file
	mlx_texture_t* texture = mlx_load_png("textures/brick1.png");
	if (!texture)
        error();

	// Convert texture to a displayable image
	mlx_image_t* img = mlx_new_image(mlx, HEIGHT, WIDTH);
	if (!img)
        error();

	// Put the texture to image
// Put the texture to image with scaling
uint32_t new_width = 500;
uint32_t new_height = 500;
float x_ratio = texture->width / (float)new_width;
float y_ratio = texture->height / (float)new_height;
uint32_t x, y;
uint8_t* pixelx;
uint8_t* pixeli;

for (uint32_t i = 0; i < new_height; i++) {
    for (uint32_t j = 0; j < new_width; j++) {
        x = (uint32_t)(j * x_ratio);
        y = (uint32_t)(i * y_ratio);
        pixelx = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
        pixeli = &img->pixels[(i * img->width + j) * texture->bytes_per_pixel];
        memmove(pixeli, pixelx, texture->bytes_per_pixel);
    }
}

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}