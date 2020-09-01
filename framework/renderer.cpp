// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include"ray.hpp"



Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render(Scene const& scene)
{
    for (int i = 0; i < 2; ++i)
    {
        // send a ray through each pixel
        for (unsigned y = 0; y < height_; ++y)
        {
            for (unsigned x = 0; x < width_; ++x)
            {
                Pixel p(x, y);
                Ray ray = scene.camera.shootRay(x,y, width_, height_);
                Color color{0.0, 0.0, 0.0};
                p.color = color;
                write(p);
            }
        }
        ppm_.save(filename_ + "_" + std::to_string(i) + ".ppm");
    }
}

/*
Color Renderer::trace(Scene const& scene, Ray const& ray)
{
    Color backgroundColor{0.2, 0.2, 0.2};
    std::shared_ptr<Hit> hit = nullptr;
    std::shared_ptr<Hit> closest_hit = nullptr;
    std::shared_ptr<Shape> closest_object{nullptr};
    float closest_distance = 1000000;

    for (auto const& i : scene.shape_vector)
    {
        hit = (*i).intersect(ray);
        if (hit != nullptr)
        {
            if (glm::length(hit->position - ray.origin) < closest_distance)
            {
                closest_hit = hit;
                closest_distance = glm::length(hit->position - ray.origin);
                closest_object = i;
            }
        }
    }
    if (closest_object != nullptr)
    {
        Color pix_col = shade(*closest_object, ray, closest_hit, scene);
        return pix_col;
    }
    return backgroundColor;
}


Color Renderer::shade(Shape const& shape, Ray const& ray, std::shared_ptr<Hit> hit, Scene const& scene)
{
    return { 0.0,0.0,1.0 };
}
*/

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
