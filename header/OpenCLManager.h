/*
 * OpenCLManager.h
 * 
 * Class for
 * 
 * This class is a part of Project OpenCL Manager
 *       
 *
 * AUTHOR     : Alphin Edgar D'cruz
 * START DATE : April 2019
 *
 */

#pragma once

#include "OpenCLProgram.h"



class OpenCLManager
{
private:
	cl_platform_id platform;
	cl_device_id device;

	cl_context context;
	cl_command_queue commands;

	std::unordered_map<const char*, OpenCLProgram> programs;

	cl_mem input;


public:

	/*
 	 * Default OpenCLManager constructor
 	 * 
 	 * Finds all platforms and assosiated devices and finds the best one
 	 * Also initializes context and command queue
 	 */
	OpenCLManager();



	/*
	* Function: createProgram
	* 
	* IN   : const char* identifier, const char* kernelname, const char* source
	* OUT  : int
	* DESC : This function creates and initializes a new program
	*/
	int createProgram(const char* identifier, const char* source);



	/*
	* Function: getprogram
	* 
	* IN   : const char* identifier
	* OUT  : OpenCLProgram*
	* DESC : This function returns a created program
	*/
	OpenCLProgram* getprogram(const char* identifier);



	/*
	* Function: printDeviceInfo
	* 
	* IN   : -
	* OUT  : -
	* DESC : This function prints information about the selected device
	*/
	void printDeviceInfo();



	/*
	* Function: printPlatformInfo
	* 
	* IN   : -
	* OUT  : -
	* DESC : This function prints information about the selected platform
	*/
	void printPlatformInfo();
	


	/*
 	 * OpenCLManager destructor
 	 * 
 	 * Releases context and command queue
 	 */	
	~OpenCLManager();
};