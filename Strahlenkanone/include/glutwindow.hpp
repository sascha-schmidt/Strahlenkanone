#ifndef BUW_GLUT_WINDOW_HPP
#define BUW_GLUT_WINDOW_HPP

// header, system 
#include <vector>
#include <string>

// header, project
#include <rgb.hpp>
#include <pixel.hpp>



class glutwindow {
public : // typedefs, enums
  typedef std::vector<rgb> colorbuffer_t;
  
  ~glutwindow();

private : // do not copy glutwindow

  glutwindow(std::size_t width, std::size_t height,
             std::size_t posx, std::size_t posy,
		         std::string const& name, 
		         int argc, char* argv[]);

  glutwindow(glutwindow const&);

  glutwindow& operator=(glutwindow const&);
  
public : // methods

  static void init(std::size_t width, std::size_t height,
                   std::size_t posx, std::size_t posy,
		               std::string const& name, 
		               int argc, char* argv[]);
	static glutwindow& instance();
		               
  void write(const pixel& p);
  void update();
  void run();

  std::size_t width() const;
  std::size_t height() const;
  float const& buffer() const;
  
private: // member

  colorbuffer_t buffer_;
  
  std::size_t width_;
  std::size_t height_;
  
  std::size_t posx_;
  std::size_t posy_;
  
  std::string name_;
};

// external glut callbacks
void display();
void reshape(int, int);
void idle();

#endif // BUW_GLUT_WINDOW_HPP