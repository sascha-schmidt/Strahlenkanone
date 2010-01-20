// header i/f
#include "glutwindow.hpp"

// header, system
#if WIN32
  #include <time.h>
  #include <windows.h>
#else
  #include <sys/time.h>
#endif

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#include <iostream>
#include <cassert>

// header, project

// globals
glutwindow* g_glutwindow = 0;


////////////////////////////////////////////////////////////////////////////////
glutwindow::glutwindow(std::size_t width, std::size_t height,
                       std::size_t posx, std::size_t posy,
		                   std::string const& name, 
		                   int argc, char* argv[])
  : width_(width), 
    height_(height),
    posx_(posx),
    posy_(posy),  
    name_(name)   
{ 
  g_glutwindow = this;
  buffer_.resize(width_ * height_);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  
  glutInitWindowPosition(int(posx_), int(posy_));
  glutInitWindowSize(int(width_), int(height_));
  glutCreateWindow(name_.c_str());
  
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
}


////////////////////////////////////////////////////////////////////////////////
glutwindow::~glutwindow()
{}


////////////////////////////////////////////////////////////////////////////////
/*static*/ glutwindow& 
glutwindow::instance()
{
  assert(g_glutwindow);
  return *g_glutwindow;
}


////////////////////////////////////////////////////////////////////////////////
/*static*/ void 
glutwindow::init(std::size_t width, std::size_t height,
                 std::size_t posx, std::size_t posy,
                 std::string const& name, 
	               int argc, char* argv[])
{
  static glutwindow instance(width, height, posx, posy, name, argc, argv);
}


////////////////////////////////////////////////////////////////////////////////
void 
glutwindow::run()
{
  glutMainLoop();
}


////////////////////////////////////////////////////////////////////////////////
std::size_t 
glutwindow::width() const {
  return width_;
}


////////////////////////////////////////////////////////////////////////////////
std::size_t 
glutwindow::height() const {
  return height_;
}


////////////////////////////////////////////////////////////////////////////////
void 
glutwindow::write(const pixel& p) 
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (height_*width_) - (width_*p.y + (width_-p.x));
  if (buf_pos >= buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error glutwindow::write(pixel p) : pixel out of image : " << (int)p.x << "," << (int)p.y << std::endl;
  } else {
    buffer_[buf_pos] = p.color;
  }
}

////////////////////////////////////////////////////////////////////////////////
void 
glutwindow::update()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawPixels(width_, height_, GL_RGB, GL_FLOAT, &(buffer_.front()));
  glutSwapBuffers();
  
  // upate only with 25Hz
#if WIN32
  Sleep(20);
#else
  usleep(20000);
#endif
}


////////////////////////////////////////////////////////////////////////////////
void display() 
{
  glutwindow::instance().update();
}


////////////////////////////////////////////////////////////////////////////////
void reshape(int w, int h) 
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


////////////////////////////////////////////////////////////////////////////////
void idle()
{
  glutPostRedisplay();
}
