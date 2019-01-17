

#include "color.hpp"
#include "GalaxLighting.hpp"

int main() {
  GalaxLighting GALAX;

  RGB_COLOR rgb(0, 0, 0);
  HSV_COLOR hsv(0, 1, 1);

  RGB_COLOR c = hsv2rgb(25, 1, 1);

  while (true) {
    rgb = hsv2rgb(hsv.value, hsv.saturation, hsv.hue);
    GALAX.SetColor(rgb.red, rgb.green, rgb.blue);
    GALAX.Apply();
    hsv.hue = (hsv.hue > 360) ? hsv.hue - 300 : hsv.hue + 80;
    Sleep(250);

  }
  return 0;
}
