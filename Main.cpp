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
#include <map>
#include <direct.h>


#define BUILDCOUNTER_TEXT_VERSION //Else binary version



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


#ifdef BUILDCOUNTER_TEXT_VERSION

int main(int argc, char* argv[])
{
	std::string project_name("BuildCounterProjects/");
	
	_mkdir(project_name.c_str());
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	BuildData data;
	
	std::fstream data_file;
	
	data_file.open(project_name + "_build.dat", std::ios::in);
	if(data_file.good())
	{
		std::string temp;
		std::string num;
		unsigned int point_cnt = 0;
		std::getline(data_file, temp);
		
		temp += ".";
		
		for(unsigned int i = 0; i < temp.size(); i++)
		{
			if(temp.at(i) == '.')
			{
				point_cnt++;
				
				switch(point_cnt)
				{
					case 1:
						data.major = std::stoul(num);
						num.clear();
					break;
					
					case 2:
						data.minor = std::stoul(num);
						num.clear();
					break;
					
					case 3:
						data.patch = std::stoul(num);
						num.clear();
					break;
					
					case 4:
						data.build = std::stoul(num);
						num.clear();
					break;
					
					default:
					break;
				}
			}
			else if((temp.at(i) >= '0') && (temp.at(i) <= '9'))
			{
				num += temp.at(i);
			}
			else
			{
				std::cout << "Unknown symbol inside data file in position " << i + 1 << "!" << std::endl;
			}
		}
		
		data_file.close();
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if(argc > 1)
		{
			for(unsigned int i = 1; i < argc; i++)
			{
				std::string comm(argv[i]);
				
				if(comm == "-help")
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
				else if(comm == "-major")
				{
					data.major = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-minor")
				{
					data.minor = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-patch")
				{
					data.patch = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-build")
				{
					data.build = std::stoul(std::string(argv[i + 1]));
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << "Build version: " << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
		
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
	else
	{
		std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open! Creating new file..." << std::endl;
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if(argc > 1)
		{
			for(unsigned int i = 1; i < argc; i++)
			{
				std::string comm(argv[i]);
				
				if(comm == "-help")
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
				else if(comm == "-major")
				{
					data.major = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-minor")
				{
					data.minor = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-patch")
				{
					data.patch = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-build")
				{
					data.build = std::stoul(std::string(argv[i + 1]));
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		std::fstream file;
		file.open(project_name + "_build.dat", std::ios::out | std::ios::trunc);
		
		file << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
		
		file.close();
	}
		
	return 0;
}

#else
	
int main(int argc, char* argv[])
{
	std::string project_name("BuildCounterProjects/");
	
	_mkdir(project_name.c_str());
	
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	BuildData data;
	
	std::fstream data_file;
	
	data_file.open(project_name + "_build.dat", std::ios::in | std::ios::binary);
	if(data_file.good())
	{
		data_file.read(reinterpret_cast<char*>(&data), sizeof(data));
		
		data_file.close();
			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if(argc > 1)
		{
			for(unsigned int i = 1; i < argc; i++)
			{
				std::string comm(argv[i]);
				
				if(comm == "-help")
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
				else if(comm == "-major")
				{
					data.major = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-minor")
				{
					data.minor = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-patch")
				{
					data.patch = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-build")
				{
					data.build = std::stoul(std::string(argv[i + 1]));
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << "Build version: " << data.major << "." << data.minor << "." << data.patch << "." << data.build << std::endl;
			
		data_file.open(project_name + "_build.dat", std::ios::out | std::ios::trunc);
		if(data_file.good())
		{
			data_file.write(reinterpret_cast<char*>(&data), sizeof(data));
			data_file.close();
		}
		else
		{
			std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open!" << std::endl;
		}
	}
	else
	{
		std::cout << "Data file \"" << project_name << "_build.dat\" wasn't open! Creating new file..." << std::endl;
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if(argc > 1)
		{
			for(unsigned int i = 1; i < argc; i++)
			{
				std::string comm(argv[i]);
				
				if(comm == "-help")
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
				else if(comm == "-major")
				{
					data.major = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-minor")
				{
					data.minor = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-patch")
				{
					data.patch = std::stoul(std::string(argv[i + 1]));
				}
				else if(comm == "-build")
				{
					data.build = std::stoul(std::string(argv[i + 1]));
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		std::fstream file;
		file.open(project_name + "_build.dat", std::ios::out | std::ios::binary | std::ios::trunc);
		
		file.write(reinterpret_cast<char*>(&data), sizeof(data));
		
		file.close();
	}
	
	return 0;
}

#endif