/**
Copyright (c) 2018 Kazim Kamilov

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <direct.h>


/**
	Comment this if you want to use a binary version of the data file.
*/
#define BUILDCOUNTER_TEXT_VERSION


//in this structure we storage all version data
struct BuildData
{
	BuildData() :
		major(0U),
		minor(0U),
		patch(0U),
		build(0U)
	{
	}
	
	unsigned int major;
	unsigned int minor;
	unsigned int patch;
	unsigned int build;
};


void printInfo()
{
	std::cout << "BuildCounter v1.0. Kazim Kamilov, 08.08.2018" << std::endl;
	std::cout << "Possible arguments list:" << std::endl;
	std::cout << "-help Print this info." << std::endl;
	std::cout << "-name Sets project name." << std::endl;
	std::cout << "-major Manually sets major version." << std::endl;
	std::cout << "-minor Manually sets minor version." << std::endl;
	std::cout << "-patch Manually sets patch version." << std::endl;
	std::cout << "-build Manually sets build version." << std::endl;
	std::cout << "-major++ Increments major version." << std::endl;
	std::cout << "-minor++ Increments minor version." << std::endl;
	std::cout << "-patch++ Increments patch version." << std::endl;
	std::cout << "-build++ Increments build version." << std::endl;
}

//converts string into unsigned int
unsigned int toUInt(const std::string& str)
{
	std::istringstream stream(str);
	unsigned int value = 0;
	
	stream >> value;
	
	return value;
}

//processes parameters and writes data to the structure
void processParameters(BuildData& data, int argc, char** argv)
{
	if(argc > 1)
	{
		for(unsigned int i = 1; i < argc; i++)
		{
			std::string comm(argv[i]);
			
			if(comm == "-help")
			{
				printInfo();
			}
			else if(comm == "-major")
			{
				data.major = toUInt(std::string(argv[i + 1]));
			}
			else if(comm == "-minor")
			{
				data.minor = toUInt(std::string(argv[i + 1]));
			}
			else if(comm == "-patch")
			{
				data.patch = toUInt(std::string(argv[i + 1]));
			}
			else if(comm == "-build")
			{
				data.build = toUInt(std::string(argv[i + 1]));
			}
			else if(comm == "-major++")
			{
				data.major++;
			}
			else if(comm == "-minor++")
			{
				data.minor++;
			}
			else if(comm == "-patch++")
			{
				data.patch++;
			}
			else if(comm == "-build++")
			{
				data.build++;
			}
		}	
	}
}


#ifdef BUILDCOUNTER_TEXT_VERSION

int main(int argc, char* argv[])
{
	//sets name of project folder
	std::string project_name("BuildCounterProjects/");
	
	//create folder
	_mkdir(project_name.c_str());
	
	//get project name(if it sets)
	if(argc > 1)
	{
		for(unsigned int i = 1; i < argc; i++)
		{
			std::string comm(argv[i]);
			
			if(comm == "-name")
			{
				project_name += std::string(argv[i + 1]);
			}
		}	
	}

	//data structure
	BuildData data;
	
	//file for in/out data
	std::fstream data_file;
	
	//open file for get version data
	data_file.open(project_name + "_build.dat", std::ios::in);
	if(data_file.good()) //if datafile exist 
	{
		//some temp variables
		std::string temp;
		std::string num;
		unsigned int point_cnt = 0;
		
		//get whole line
		std::getline(data_file, temp);
		
		//that really need, believe me... Tricky trick...
		temp += ".";
		
		//process all characters
		for(unsigned int i = 0; i < temp.size(); i++)
		{
			if(temp.at(i) == '.') //if character is '.'
			{
				//increase number of finded '.'
				point_cnt++;
				
				//counted of the finded characters '.'
				switch(point_cnt)
				{
					case 1:
						data.major = toUInt(num);
						num.clear();
					break;
					
					case 2:
						data.minor = toUInt(num);
						num.clear();
					break;
					
					case 3:
						data.patch = toUInt(num);
						num.clear();
					break;
					
					case 4:
						data.build = toUInt(num);
						num.clear();
					break;
					
					default:
					break;
				}
			}
			else if((temp.at(i) >= '0') && (temp.at(i) <= '9')) //if numbers - put them in data
			{
				num += temp.at(i);
			}
			else //error
			{
				std::cout << "Unknown symbol inside data file in position " << i + 1 << "!" << std::endl;
			}
		}
		
		//close file
		data_file.close();

		//processes parameters...
		processParameters(data, argc, argv);

		//Out some info
		std::cout << "Build version: " << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
		
		//open file for save version data
		data_file.open(project_name + "_build.dat", std::ios::out | std::ios::trunc);
		if(data_file.good())
		{
			data_file << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
			data_file.close();
		}
		else
		{
			std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open!" << std::endl;
		}
	}
	else //Create new data file
	{
		std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open! Creating new file..." << std::endl;
		
		//processes parameters...
		processParameters(data, argc, argv);
		
		std::fstream file;
		file.open(project_name + "_build.dat", std::ios::out | std::ios::trunc);
		
		file << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
		
		file.close();
	}
		
	return 0;
}

#else //binary version
	
int main(int argc, char* argv[])
{
	//sets name of project folder
	std::string project_name("BuildCounterProjects/");
	
	//create folder
	_mkdir(project_name.c_str());
	
	//get project name(if it sets)
	if(argc > 1)
	{
		for(unsigned int i = 1; i < argc; i++)
		{
			std::string comm(argv[i]);
			
			if(comm == "-name")
			{
				project_name += std::string(argv[i + 1]);
			}
		}	
	}

	//data structure
	BuildData data;
	
	//file for in/out data
	std::fstream data_file;
	
	//open file for get version data
	data_file.open(project_name + "_build.dat", std::ios::in | std::ios::binary);
	if(data_file.good()) //if datafile exist 
	{
		//read structure in binary mode
		data_file.read(reinterpret_cast<char*>(&data), sizeof(data));
		
		//close file
		data_file.close();
			
		//processes parameters...
		processParameters(data, argc, argv);
		
		//out some info
		std::cout << "Build version: " << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
		
		//open file for save version data
		data_file.open(project_name + "_build.dat", std::ios::out | std::ios::trunc);
		if(data_file.good()) //file open
		{
			//save structure to binary file
			data_file.write(reinterpret_cast<char*>(&data), sizeof(data));
			
			//close file
			data_file.close();
		}
		else //file was not open
		{
			std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open!" << std::endl;
		}
	}
	else //Create new data file
	{
		std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open! Creating new file..." << std::endl;
		
		//processes parameters...
		processParameters(data, argc, argv);
		
		std::fstream file;
		file.open(project_name + "_build.dat", std::ios::out | std::ios::binary | std::ios::trunc);
		
		file.write(reinterpret_cast<char*>(&data), sizeof(data));
		
		file.close();
	}
	
	return 0;
}

#endif
