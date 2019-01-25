/*  
*   color.hpp
*   -------------------------
*
*   -------------------------
*   Stavros Avramidis	1/17/2019
*/


#pragma once

#include <cstdint>
#include <math.h>

struct HSV_COLOR {
  double hue;
  double saturation;
  double value;
  HSV_COLOR() : hue(0), saturation(0), value(0) {}
  HSV_COLOR(uint8_t h, uint8_t s, uint8_t v) : hue(h), saturation(s), value(v) {}
};

struct RGB_COLOR {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  RGB_COLOR() : red(0), green(0), blue(0) {}
  RGB_COLOR(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
//  RGB_COLOR& operator= (HSV_COLOR &hsv) {
//    this = hsv2rgb(hsv.hue, hsv.saturation, hsv.value);
//  }
};

RGB_COLOR hsv2rgb(double H, double S, double V) {

  double P, Q, T, fract;
  double _r = 0, _g = 0, _b = 0;

  while (H > 359) {
    H = H - 360;
  }

  (H==360.) ? (H = 0.) : (H /= 60.);
  fract = H - floor(H);

  P = V*(1. - S);
  Q = V*(1. - S*fract);
  T = V*(1. - S*(1. - fract));

  if (0. <= H && H < 1.) {
    _r = V;
    _g = T;
    _b = P;
  } else if (1. <= H && H < 2.) {
    _r = Q;
    _g = V;
    _b = P;
  } else if (2. <= H && H < 3.) {
    _r = P;
    _g = V;
    _b = T;
  } else if (3. <= H && H < 4.) {
    _r = P;
    _g = Q;
    _b = V;
  } else if (4. <= H && H < 5.) {
    _r = T;
    _g = P;
    _b = V;
  } else if (5. <= H && H < 6.) {
    _r = V;
    _g = P;
    _b = Q;
  }

  uint8_t
      r = 255*_r,
      g = 255*_g,
      b = 255*_b;
  return {r, g, b};
}
