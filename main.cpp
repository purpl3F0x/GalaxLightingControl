

#include <Windows.h>
// C libs
#include <stdio.h>

// local includes
#include "nvapi/nvapi.h"

#ifndef _WIN64
#pragma comment(lib, "nvapi/x86/nvapi.lib")
#else
#pragma comment(lib, "nvapi/amd64/nvapi64.lib")
#endif

NvPhysicalGpuHandle hGPU_a[NVAPI_MAX_PHYSICAL_GPUS] = {nullptr};
NvAPI_Status nvapiStatus = NVAPI_OK;
NvU32 gpuCount = 0;

int main(int argc, char** argv) {

  /* Initialize Nv API */
  if ((nvapiStatus = NvAPI_Initialize())!=NVAPI_OK) {
    printf("NvAPI_Initialize() failed with status %d\n", nvapiStatus);
    return 0;
  } else {
    printf("Success on Initializing NvAPI\n\n");
  }


  /* Enumerate Gpus */
  nvapiStatus = NvAPI_EnumPhysicalGPUs(hGPU_a, &gpuCount);
  if (nvapiStatus!=NVAPI_OK) {
    printf("NvAPI_Initialize() failed with status %d\n", nvapiStatus);
    return 0;
  } else {
    printf("Found %i %s \n\n", gpuCount, ((gpuCount > 1) ? "gpus" : "gpu"));
  }


  /* Test i2c Read function */
  auto i2c_info = new NV_I2C_INFO;

  i2c_info->version = NV_I2C_INFO_VER;
  i2c_info->displayMask = 0;
  i2c_info->bIsDDCPort = NV_TRUE;
  i2c_info->i2cDevAddress = 0x40;
  i2c_info->pbI2cRegAddress = nullptr;
  i2c_info->regAddrSize = 0;
  i2c_info->pbData = new NvU8[100];
  i2c_info->cbSize = 100;
  i2c_info->i2cSpeed = NVAPI_I2C_SPEED_DEPRECATED;
  i2c_info->i2cSpeedKhz = NVAPI_I2C_SPEED_DEFAULT;

  nvapiStatus = NvAPI_I2CRead(hGPU_a[0], i2c_info);

  printf("%d\n", nvapiStatus);

  return 0;

}
