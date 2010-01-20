#ifndef BUW_PPMWRITER_HPP
#define BUW_PPMWRITER_HPP

// header, system
#include <string>
#include <vector>

// header, project
#include <pixel.hpp>


class ppmwriter 
{
public:
  ppmwriter(std::size_t w, std::size_t h, std::string const& file);
  ppmwriter(std::size_t w, std::size_t h);
  ~ppmwriter();

public:
  void write(pixel const& p);
  void save(std::string const& file);
  void save();

private:
  std::string file_;
  std::vector<unsigned int> data_;
  size_t width_;
  size_t height_;
};

#endif // BUW_PPMWRITER
