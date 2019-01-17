/*  
*   GalaxLighting.hpp
*   -------------------------
*
*   -------------------------
*   Stavros Avramidis	1/17/2019
*/


#pragma once

#include <cstdint>
#include <stdio.h>
#include <windows.h>

#ifndef __GALAXLIGHTING_HPP__
#define __GALAXLIGHTING_HPP__

class GalaxLighting {
  /* */
 public:

  GalaxLighting();
  ~GalaxLighting();
  void Apply();
  void SetColor(uint32_t r, uint32_t g, uint32_t b);

  uint32_t* Red();
  uint32_t* Green();
  uint32_t* Blue();

 private:
  uint32_t BLUE_ADDRESS = 0x0050916C;
  uint32_t GREEN_ADDRESS = 0x00509170;
  uint32_t RED_ADDRESS = 0x00509174;
  uint32_t red = 0, green = 0, blue = 0;

  HWND Window;
  DWORD procID;
  HANDLE hProc;
};

#endif


