#include "stdafx.h"
#include "f_File.h"
#include <cstdio>
#include <fstream>
//#include <iostream>

std::ofstream fout; // file output object
std::ifstream fin; // file input object
int open_write(std::string strFileName)
{
	fout.open(strFileName.c_str());
	return 1; //XXX add error checking.
}

int open_read(std::string strFileName)
{
	if (!fin.is_open())
	{
		fin.open(strFileName.c_str());
		return 1;
	}
	else
	{
		return 0; // file all ready open.
	}
}

int open_appened(std::string strFileName)
{
	fout.open(strFileName.c_str(), std::ios::app);
	return 1; //XXX add error checking.
}

int close_file(char* mode)
{
	if (mode != "read")
	{
		fout.close();
		return 2;
	}else
	{
		fin.close();
		return 1;
	}
	return 0;
}

int write_string(char* i)
{
	fout << i << "\n";
	return 1; //XXX add error checking.
}

int write_int(int i)
{
	fout << i << "\n";
	return 1; //XXX add error checking.
}

int write_float(float i)
{
	fout << i << "\n";
	return 1; //XXX add error checking.
}



char* read_string()
{
	char buffer[100] = ""; // Buffer
	char* buffer_str = "";
	fin >> buffer;
	buffer_str = buffer; // convert char back to string
	return buffer_str;
}

int read_int()
{
	int buffer_int = 0;
	fin >> buffer_int;
	return buffer_int;
}

float read_float()
{
	float buffer_float = 0.0f;
	fin >> buffer_float;	
	return buffer_float; //XXX add error checking.
}

bool file_eof(char* mode)
{
	if (mode != "read")
	{
		return fout.good();
	}else
	{
		return fin.good();
		fin.good();
	}
}