#include "OpenCLProgram.h"





int OpenCLProgram::init(const char* source, cl_context context, cl_command_queue commands)
{
    this->context = context;
    this->commands = commands;

    int err;
    /* create program from source */
    program = clCreateProgramWithSource(this->context, 1, (const char **)&source, NULL, &err);
    if (err != CL_SUCCESS)
        printf("Issue creating program, error code: %d\n", err);

    /* build the program */
    clBuildProgram(program, 0, NULL, NULL, NULL, &err);
    if (err != CL_SUCCESS)
        printf("Issue building program, error code: %d\n", err);

    /* create kernel */
    //kernel = clCreateKernel(program, kernelname, &err);
}

void OpenCLProgram::createKernel (const char* kernelName)
{
    int err;
    kernels[kernelName] = clCreateKernel(program, kernelName, &err);
    if (err != CL_SUCCESS)
        printf("Issue creating kernel, error code: %d\n", err);
}




void OpenCLProgram::createBuffer (const char* identifier, const unsigned int size)
{
    /* create device memory for input and output */
    buffers[identifier] = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, NULL);
    bufferSizes[identifier] = size;
}



void OpenCLProgram::assignBufferToGlobal(const char* kernelName, int argno, const char* identifier)
{
    clSetKernelArg(kernels[kernelName], argno, sizeof(cl_mem), &(buffers[identifier])); // for input
}


void OpenCLProgram::assignArgument(const char* kernelName, int argno, void* value, unsigned int size)
{
    clSetKernelArg(kernels[kernelName], argno, size, value);
}


void OpenCLProgram::run(const char* kernelName)
{
    unsigned int count = 1000;
    size_t local = 10; // will come back to this later, with better approach

    // set global size
    size_t global = ceil(count / (float) local) * local; // will come back to this later, with better approach. local must be divisor of global

    /* enqueue kernel (which asks the device to run all work items) */
    clEnqueueNDRangeKernel(commands, kernels[kernelName], 1, NULL, &global, &local, 0, NULL, NULL);

}



void OpenCLProgram::runAndWait(const char* kernelName)
{
    unsigned int count = 1000;
    size_t local = 10; // will come back to this later, with better approach

    /* set global size */
    size_t global = ceil(count / (float) local) * local; // will come back to this later, with better approach. local must be divisor of global

    /* enqueue kernel (which asks the device to run all work items) */
    clEnqueueNDRangeKernel(commands, kernels[kernelName], 1, NULL, &global, &local, 0, NULL, NULL);

    /* wait for device to finish */
    clFinish(commands);
}


void OpenCLProgram::readFromBuffer(const char* identifier, void* data)
{
    clEnqueueReadBuffer(commands, buffers[identifier], CL_TRUE, 0, bufferSizes[identifier], data, 0, NULL, NULL);
}


void OpenCLProgram::writeToBuffer (const char* identifier, void* data)
{
    clEnqueueWriteBuffer(commands, buffers[identifier], CL_TRUE, 0, bufferSizes[identifier], data, 0, NULL, NULL);
}





OpenCLProgram::~OpenCLProgram()
{
    for (auto x : buffers)
        clReleaseMemObject(x.second);
    clReleaseProgram(program);
    for (auto x : kernels)
        clReleaseKernel(x.second);
}