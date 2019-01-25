
#include <chrono>
#include <stdio.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include "color.hpp"
#include "GalaxLighting.hpp"

#define EXIT_ON_ERROR(hr)  \
              if (FAILED(hr)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

#define IDC_STATIC_MINVOL      1001
#define IDC_STATIC_MAXVOL      1002
#define IDC_PEAK_METER         1003


int main() {
  GalaxLighting GALAX;

  RGB_COLOR rgb(0, 0, 0);
  HSV_COLOR hsv(0, 1, 1);

  RGB_COLOR c = hsv2rgb(25, 1, 1);
  HRESULT hr;
  IMMDeviceEnumerator* pEnumerator = nullptr;
  IMMDevice* pDevice = nullptr;
  IAudioMeterInformation* pMeterInfo = nullptr;
  float a = 0;

  CoInitialize(nullptr);

  hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                        nullptr, CLSCTX_INPROC_SERVER,
                        __uuidof(IMMDeviceEnumerator),
                        (void**) &pEnumerator);
  EXIT_ON_ERROR(hr)

  hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
  EXIT_ON_ERROR(hr)

  hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
                         CLSCTX_ALL, nullptr, (void**) &pMeterInfo);
  EXIT_ON_ERROR(hr)

  while (true) {
    auto start = std::chrono::high_resolution_clock::now();
    hr = pMeterInfo->GetPeakValue(&a);
    //if (rgb.green > 254 || rgb.green < 0) isIncreasing = !isIncreasing;
    rgb = hsv2rgb(hsv.hue, hsv.saturation, hsv.value*a);
    GALAX.SetColor(rgb.red, rgb.green, rgb.blue);
    GALAX.Apply();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    printf("Render time: %2.5f s\tR:%4d G:%4d B:%4d\tVolume: %3.1f\r",
           elapsed.count(),
           rgb.red,
           rgb.green,
           rgb.blue,
           a);

    hsv.hue += .05*a;
    Sleep(1);

  }

  Exit:
  printf("Exiting with Error: %ld", hr);
  SAFE_RELEASE(pEnumerator)
  SAFE_RELEASE(pDevice)
  SAFE_RELEASE(pMeterInfo)
  CoUninitialize();
  return 0;

}


