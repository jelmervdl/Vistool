#include "glTexture.h"

using std::string;
using std::endl;
using std::cout;
using Magick::Image;
using Magick::Blob;
using Magick::Color;
using Magick::Geometry;
using Magick::ColorGray;
using VisionToolFeatures::Gradient;
using VisionToolCore::Matrix;

void initTexture(int window, GLuint * texName, string filename, size_t * twidth, size_t * theight){
  Image im(filename);
  initTexture(window, texName, &im, twidth, theight);
}

void initTexture(int window, GLuint * texName, Image * im, size_t * twidth, size_t * theight){
  Blob blob;
  im->magick("RGBA");
  im->write(&blob);
  *twidth = im->columns();
  *theight = im->rows();
  initTexture(window, texName, &blob, twidth, theight);
}

void initTexture(int window, GLuint * texName, Blob * blob, size_t * width, size_t * height){
  glutSetWindow(window);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, *texName);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, *width, *height, 0, 
	       GL_RGBA, GL_UNSIGNED_BYTE, blob->data());
  glDisable(GL_TEXTURE_2D);
}

void  drawTexture(GLuint texName, int twidth, int theight) {
  glEnable(GL_TEXTURE_2D); 
  glBindTexture(GL_TEXTURE_2D, texName); 
  glBegin(GL_QUADS);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(0 + twidth, 0 + theight);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(0 + twidth, 0);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0, 0);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0, 0 + theight);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void initTexture(int window, GLuint * texName, Matrix<float> * matrix, size_t * width, size_t * height){
  Image draw_Image(Geometry(matrix->get_width(), matrix->get_height()), Color("black"));
  draw_Image.depth(8);
  draw_Image.magick("RGBA");
  cout << "made empty im " << endl;
  for(size_t x = 0; x < matrix->get_width(); ++x)
    for(size_t y = 0; y < matrix->get_height(); ++y)
      draw_Image.pixelColor(x, y, ColorGray(matrix->at(x,y)));
  cout << "done " << endl;
  Blob blob;
  draw_Image.write(&blob);
  *width = draw_Image.columns();
  *height = draw_Image.rows();
  initTexture(window, texName, &blob, width, height);
}

void initTexture(int window, GLuint * texName, Matrix<Gradient> * matrix, size_t * width, size_t * height){
  Image draw_Image(Geometry(matrix->get_width(), matrix->get_height()), Color("black"));
  draw_Image.depth(8);
  draw_Image.magick("RGBA");
  cout << "made empty im " << endl;
  for(size_t x = 0; x < matrix->get_width(); ++x)
    for(size_t y = 0; y < matrix->get_height(); ++y)
      draw_Image.pixelColor(x, y, ColorGray(matrix->at(x,y).get_magnitude()));
  cout << "done " << endl;
  Blob blob;
  draw_Image.write(&blob);
  *width = draw_Image.columns();
  *height = draw_Image.rows();
  initTexture(window, texName, &blob, width, height);
}
