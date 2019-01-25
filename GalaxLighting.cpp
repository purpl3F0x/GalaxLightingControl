/*  
*   GalaxLighting.cpp
*   -------------------------
*   Stavros Avramidis	1/17/2019
*/

#include "GalaxLighting.hpp"

/*
 * TODO: manually start the XT+ service if not present
 */


GalaxLighting::GalaxLighting() : Window(NULL), procID(0) {

  Window = FindWindow(NULL, "XtremeTuner Plus");
  if (!Window) {
    throw ("Window not found");
  } else {
    if (!GetWindowThreadProcessId(Window, &procID)) {
      throw ("Get window process ID error: %i", GetLastError());
    }
  }

  if (procID!=0)
    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

  if (!hProc) {
    throw ("Can't open process: %i", GetLastError());
  } else {
    printf("Ready override XT+ values\n");
  }
}

GalaxLighting::~GalaxLighting() = default;

void GalaxLighting::Apply() {
  WriteProcessMemory(hProc, (BYTE*) RED_ADDRESS, (LPDWORD) &red, sizeof(DWORD), NULL);
  WriteProcessMemory(hProc, (BYTE*) GREEN_ADDRESS, (LPDWORD) &green, sizeof(DWORD), NULL);
  WriteProcessMemory(hProc, (BYTE*) BLUE_ADDRESS, (LPDWORD) &blue, sizeof(DWORD), NULL);
}

void GalaxLighting::SetColor(uint32_t r, uint32_t g, uint32_t b) {
  red = r;
  green = g;
  blue = b;
}

uint32_t* GalaxLighting::Red() { return &red; }
uint32_t* GalaxLighting::Green() { return &green; }
uint32_t* GalaxLighting::Blue() { return &blue; }