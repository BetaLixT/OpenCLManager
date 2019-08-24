/*
 * OpenCLProgram.h
 * 
 * Class for
 * 
 * This class is a part of Project OpenCL Manager
 *       
 *
 * AUTHOR     : Alphin Edgar D'cruz
 * START DATE : May 2019
 *
 */

#define CL_SILENCE_DEPRECATION


#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <math.h>
#include <stdio.h>
#include <unordered_map>
#include <string>



class OpenCLProgram
{
    cl_program program;
    //cl_kernel kernel;
    cl_context context;
    cl_command_queue commands;

    //cl_mem input;
    std::unordered_map<const char*, cl_mem> buffers;
    std::unordered_map<const char*, unsigned int> bufferSizes;
    std::unordered_map<const char*, cl_kernel> kernels;

    public:

    /*
    * Function init
    * 
    * IN   : const char* source, const char* kernelname, cl_context context, cl_command_queue commands
    * OUT  : int
    * DESC : This function initializes program and kernel
    */
    int init(const char* source, cl_context context, cl_command_queue commands);




    void createKernel (const char* kernelName);



    /*
    * Function createBuffer
    * 
    * IN   : const char* identifier, const unsigned int size
    * OUT  : -
    * DESC : This function creates a buffer identified by identifier
    */
    void createBuffer (const char* identifier, const unsigned int size);



    /*
    * Function assignBufferToGlobal
    * 
    * IN   : int argno, const char* identifier
    * OUT  : -
    * DESC : This function takes buffer identified by identifier and
    *         assigns them to the argnoth argument of kernel
    */
    void assignBufferToGlobal(const char* kernelName, int argno, const char* identifier);



    /*
    * Function assignArgument
    * 
    * IN   : int argno, void* value, unsigned int size
    * OUT  : -int argno, void* value, unsigned int size
    * DESC : This function value and assigns them to the argnoth
    *        argument of kernel
    */
    void assignArgument(const char* kernelName, int argno, void* value, unsigned int size);



    /*
    * Function run
    * 
    * IN   : -
    * OUT  : -
    * DESC : Runs kernels in command queue
    */
    void run(const char* kernelName);



    /*
    * Function runAndWait
    * 
    * IN   : -
    * OUT  : -
    * DESC : Runs kernels in command queue and waits for them to end
    */
    void runAndWait(const char* kernelName);



    /*
    * Function readFromBuffer
    * 
    * IN   : const char* identifier, void* data
    * OUT  : -
    * DESC : This function reads data from the buffer into memory
    *        pointed to by data
    */
    void readFromBuffer(const char* identifier, void* data);



    /*
    * Function writeToBuffer
    * 
    * IN   : const char* identifier, void* data
    * OUT  : -
    * DESC : This function writes data into the buffer from memory
    *        pointed to by data
    */
    void writeToBuffer (const char* identifier, void* data);



	/*
 	 * OpenCLProgram destructor
 	 * 
 	 * Releases memory objects and kernels
 	 */	
    ~OpenCLProgram();
};