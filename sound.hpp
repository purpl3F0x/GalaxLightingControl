/*  
*   sound.hpp
*   -------------------------
*   Enter Description
*   -------------------------
*   Stavros Avramidis	1/25/2019
*/


#ifndef GALAXLIGHTINGCONTROL_SOUND_HPP
#define GALAXLIGHTINGCONTROL_SOUND_HPP

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#define TIMER_PERIOD  125

#define EXIT_ON_ERROR(hr)  \
              if (FAILED(hr)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

HRESULT hr;
IMMDeviceEnumerator* pEnumerator = nullptr;
IMMDevice* pDevice = nullptr;
IAudioMeterInformation* pMeterInfo = nullptr;

void SoundInitialize() {
  CoInitialize(nullptr);

  // Get enumerator for audio endpoint devices.
  hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                        nullptr, CLSCTX_INPROC_SERVER,
                        __uuidof(IMMDeviceEnumerator),
                        (void**) &pEnumerator);
  EXIT_ON_ERROR(hr)

  // Get peak meter for default audio-rendering device.
  hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
  EXIT_ON_ERROR(hr)

  hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
                         CLSCTX_ALL, nullptr, (void**) &pMeterInfo);
  EXIT_ON_ERROR(hr);

  Exit:
  if (FAILED(hr)) {
    MessageBox(nullptr, TEXT("This program requires Windows Vista."),
               TEXT("Error termination"), MB_OK);
  }
  SAFE_RELEASE(pEnumerator)
  SAFE_RELEASE(pDevice)
  SAFE_RELEASE(pMeterInfo)
  CoUninitialize();
}

float GetPeakVolume() {
  float peakVolume;
  auto p_peakVolume = &peakVolume;
  hr = pMeterInfo->GetPeakValue(p_peakVolume);

  return peakVolume;
}

#endif //GALAXLIGHTINGCONTROL_SOUND_HPP
