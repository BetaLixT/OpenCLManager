#include <iostream>
#include "OpenCLManager.h"

#ifdef __APPLE__
	#include <OpenCL/opencl.h>
	#define WIN(x)
	#define FILE_END ("r")
#else
	#include <CL/cl.h>
	#define WIN(x) x
	#define FILE_END ("rb")
#endif

void datatest(int* data);
char *getKernelsFromFile(char *fn);

int main()
{
	OpenCLManager opencl;

	std::cout << std::endl;
	opencl.printPlatformInfo();
	std::cout << std::endl;
	opencl.printDeviceInfo();
	
	
	size_t local = 10;
    // set global size
    size_t global = ceil(1000 / (float) local) * local;

	char *initializeArrayKernel = getKernelsFromFile("arraystuff.cl");

	/* Creating program */
	opencl.createProgram("same", initializeArrayKernel);

	/* Creating and assigning input buffer and setting it to 1 - 1000 */
	opencl.getprogram("same")->createBuffer("input", 1000 * sizeof(int));
	opencl.getprogram("same")->createBuffer("output", (global / local) * sizeof(int));
	opencl.getprogram("same")->createKernel("initializeArray");
	int data[1000];
	for (int i = 0; i < 1000; i++)
		data[i] = i;
	
	opencl.getprogram("same")->writeToBuffer("input", data);
	opencl.getprogram("same")->assignBufferToGlobal("initializeArray", 0, "input");

	opencl.getprogram("same")->assignBufferToGlobal("initializeArray", 1, "output");

	/* Setting count argument */
	int count = 1000;
	opencl.getprogram("same")->assignArgument("initializeArray", 2, &count, sizeof(int));
	opencl.getprogram("same")->runAndWait("initializeArray");

	
	/* Reading results and testing */
	int results[1000];
	opencl.getprogram("same")->readFromBuffer("input", results);
	for (int i = 0; i < 1000; i++)
		std::cout << results[i] << " ";

	std::cout << "\n\nSums: \n";

	int same[100];
	opencl.getprogram("same")->readFromBuffer("output", same);
	for (int i = 0; i < 100; i++)
		std::cout << same[i] << " ";
	
	std::cout << std::endl;
	WIN(system("pause"));
	free(initializeArrayKernel);
}


char *getKernelsFromFile(char *fn) 
{
	FILE *kernelsFile;
	char *kernelsSource;
	size_t source_size, program_size;
	kernelsFile = fopen(fn, FILE_END);
	if (!kernelsFile)
	{
		printf("Failed to load kernel\n");
		exit(1); 
	}
	fseek(kernelsFile, 0, SEEK_END);
	program_size = ftell(kernelsFile);
	rewind(kernelsFile);
	kernelsSource = (char *)malloc(program_size + 1);
	kernelsSource[program_size] = '\0';
	fread(kernelsSource, sizeof(char), program_size, kernelsFile);
	fclose(kernelsFile);
	return kernelsSource;
}