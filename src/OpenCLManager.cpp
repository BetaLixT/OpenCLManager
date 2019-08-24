#include "OpenCLManager.h"
#include <iostream>



/*
 * Function checkIsIntel
 * 
 * IN   : cl_device_id device
 * OUT  : bool
 * DESC : This function takes a device and checks if the vendor is Intel
 */
bool checkIsIntel (cl_device_id device)
{
	char info[1000];
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, 1000, info, NULL);
	std::string deviceName = info;

	if (deviceName.find("Intel") == std::string::npos)
		return false;

	return true;
}





OpenCLManager::OpenCLManager()
{

	cl_platform_id* platform_id;
	cl_uint numPlatforms;
	cl_device_id** device_id;
	cl_uint* numDevices;

	size_t infoSize = 1000;
	char* info = new char[infoSize];

	/* Get Number of platforms */
	clGetPlatformIDs(0, NULL, &numPlatforms);

	
	platform_id = new cl_platform_id[numPlatforms];
	device_id = new cl_device_id*[numPlatforms];
	numDevices = new cl_uint[numPlatforms];

	size_t maxWorkGroupSize = 0;
	int ii = 0, jj = 0;

	std::cout << numPlatforms << " platforms found" << std::endl;

	/* Get platform IDs */
	clGetPlatformIDs(numPlatforms, platform_id, NULL);

	for (int i = 0; i < numPlatforms; i++)
	{
		std::cout << "Platform ID: " << platform_id[i] << std::endl;

		/* Get number of Devices */
		clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_GPU, 0, NULL, &(numDevices[i]));

		std::cout << "\t" << numDevices[i] << " devices found" << std::endl;
		for (int j = 0; j < numDevices[i]; j++)
		{
			size_t size;
			device_id[i] = new cl_device_id[numDevices[i]];

			/* Get Device ID */
			clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_GPU, numDevices[i], device_id[i], &(numDevices[i]));
			std::cout << "\tDevice ID: " << device_id[i][j] << std::endl;

			/* Get Other data from device */
			clGetDeviceInfo(device_id[i][j], CL_DEVICE_NAME, infoSize, info, NULL);
			std::cout << "\tDevice   : " << info << std::endl;

			clGetDeviceInfo(device_id[i][j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(size), &size, NULL);
			std::cout << "\tWorkgroup size: " << size << std::endl;
			
			if (!checkIsIntel(device_id[i][j]))
			{
				maxWorkGroupSize = size;
				ii = i;
				jj = j;
			}
		}
	}

	platform = platform_id[ii];
	device = device_id[ii][jj];
	
	/* create a context */
	context = clCreateContext(0, 1, &device, NULL, NULL, NULL);

	/* create a queue */
	commands = clCreateCommandQueue(context, device, 0, NULL);


	for (int i = 0; i < numPlatforms; i++)
	{
		delete[] device_id[i];
	}
	delete[] platform_id;
	delete[] device_id;
	delete[] numDevices;

	std::cout << "Selected Platform : " << platform << std::endl;
	std::cout << "Selected Device   : " << device << std::endl;
	delete[] info;
}





int OpenCLManager::createProgram(const char* identifier, const char* source)
{
	programs[identifier].init(source, context, commands);
}

OpenCLProgram* OpenCLManager::getprogram(const char* identifier)
{
	return &programs[identifier];
}



void OpenCLManager::printPlatformInfo()
{
	size_t infoSize = 1000;
	char* info = new char[infoSize];
	std::cout << "********************************\n";
	clGetPlatformInfo(platform, CL_PLATFORM_NAME, infoSize, info, NULL);
	std::cout << "Platform : " << info << std::endl;

	clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, infoSize, info, NULL);
	std::cout << "Vendor   : " << info << std::endl;

	clGetPlatformInfo(platform, CL_PLATFORM_VERSION, infoSize, info, NULL);
	std::cout << "Version  : " << info << std::endl;
	std::cout << "********************************\n";
	delete[] info;
}





void OpenCLManager::printDeviceInfo()
{
	size_t infoSize = 1000;
	char* info = new char[infoSize];
	std::cout << "********************************\n";
	clGetDeviceInfo(device, CL_DEVICE_NAME, infoSize, info, NULL);
	std::cout << "Device   : " << info << std::endl;

	clGetDeviceInfo(device, CL_DEVICE_VENDOR, infoSize, info, NULL);
	std::cout << "Vendor   : " << info << std::endl;

	clGetDeviceInfo(device, CL_DEVICE_VERSION, infoSize, info, NULL);
	std::cout << "Version  : " << info << std::endl;

	clGetDeviceInfo(device, CL_DRIVER_VERSION, infoSize, info, NULL);
	std::cout << "Driver   : " << info << std::endl;
	std::cout << "********************************\n";
	delete[] info;
}




OpenCLManager::~OpenCLManager()
{
	clReleaseCommandQueue(commands);
	clReleaseContext(context);
}

