/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2011 Advanced Micro Devices, Inc.  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///original author: Erwin Coumans

#include "Bullet3OpenCL/Initialize/b3OpenCLUtils.h"
#include <stdio.h>

cl_context			g_cxMainContext;
cl_command_queue	g_cqCommandQue;



int main(int argc, char* argv[])
{
	int ciErrNum = 0;
	
	cl_device_type deviceType = CL_DEVICE_TYPE_ALL;
	const char* vendorSDK = b3OpenCLUtils::getSdkVendorName();

	printf("This program was compiled using the %s OpenCL SDK\n",vendorSDK);
	int numPlatforms = b3OpenCLUtils::getNumPlatforms();
	printf("Num Platforms = %d\n", numPlatforms);

	for (int i=0;i<numPlatforms;i++)
	{
		cl_platform_id platform = b3OpenCLUtils::getPlatform(i);
		b3OpenCLPlatformInfo platformInfo;
		b3OpenCLUtils::getPlatformInfo(platform,&platformInfo);
		printf("--------------------------------\n");
		printf("Platform info for platform nr %d:\n",i);
		printf("  CL_PLATFORM_VENDOR: \t\t\t%s\n",platformInfo.m_platformVendor);
		printf("  CL_PLATFORM_NAME: \t\t\t%s\n",platformInfo.m_platformName);
		printf("  CL_PLATFORM_VERSION: \t\t\t%s\n",platformInfo.m_platformVersion);
		
		cl_context context = b3OpenCLUtils::createContextFromPlatform(platform,deviceType,&ciErrNum);
		
		int numDevices = b3OpenCLUtils::getNumDevices(context);
		printf("Num Devices = %d\n", numDevices);
		for (int j=0;j<numDevices;j++)
		{
			cl_device_id dev = b3OpenCLUtils::getDevice(context,j);
			b3OpenCLDeviceInfo devInfo;
			b3OpenCLUtils::getDeviceInfo(dev,&devInfo);
			b3OpenCLUtils::printDeviceInfo(dev);
		}

		clReleaseContext(context);
	}

	///Easier method to initialize OpenCL using createContextFromType for a GPU
	deviceType = CL_DEVICE_TYPE_GPU;
	
	void* glCtx=0;
	void* glDC = 0;
	printf("Initialize OpenCL using b3OpenCLUtils::createContextFromType for CL_DEVICE_TYPE_GPU\n");
	g_cxMainContext = b3OpenCLUtils::createContextFromType(deviceType, &ciErrNum, glCtx, glDC);
	oclCHECKERROR(ciErrNum, CL_SUCCESS);

	if (g_cxMainContext)
	{
		int numDev = b3OpenCLUtils::getNumDevices(g_cxMainContext);

		for (int i=0;i<numDev;i++)
		{
			cl_device_id		device;
			device = b3OpenCLUtils::getDevice(g_cxMainContext,i);
			b3OpenCLDeviceInfo clInfo;
			b3OpenCLUtils::getDeviceInfo(device,&clInfo);
			b3OpenCLUtils::printDeviceInfo(device);
			// create a command-queue
			g_cqCommandQue = clCreateCommandQueue(g_cxMainContext, device, 0, &ciErrNum);
			oclCHECKERROR(ciErrNum, CL_SUCCESS);
			//normally you would create and execute kernels using this command queue

			clReleaseCommandQueue(g_cqCommandQue);
		}

		clReleaseContext(g_cxMainContext);

	}
	else {
		printf("No OpenCL capable GPU found!");
	}
	printf("press <Enter>\n");
	getchar();
	return 0;
}