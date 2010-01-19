#include "glTexture.h"

int setupGLTexture(char *image, long unsigned int width, long unsigned int height, int texName) 
{	
	if (image == NULL)
    {
		return 0;
    }
	
	printf("(loadTexture) width: %d height: %d\n", (int)width, (int)height); 
	
	/* create a new texture object
	 * and bind it to texname (unsigned integer > 0)
	 */
	glBindTexture(GL_TEXTURE_2D, texName);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
				 GL_RGBA, GL_UNSIGNED_BYTE, image);
	free(image);
	return 1; 
}

void initTexture(GLuint * texName, char *filename, size_t * twidth, size_t * theight){
	long unsigned int result, *width, *height;
	char *image;
	result = pngLoad(filename, &width, &height, &image);
	if (result == 0)
		printf("(pngLoad) %s FAILED.\n", filename);
	else
		printf("(pngLoad) %s SUCCESS.\n", filename);
	*twidth = (size_t) width;
	*theight = (size_t) height;
	glGenTextures(1, texName);
	setupGLTexture(image, (long unsigned int)width, (long unsigned int)height, *texName);
	
}
