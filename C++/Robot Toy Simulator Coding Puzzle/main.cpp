#include "robot_toy_simulator_lib.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
    std::cout << "test" << std::endl;
    std::cout << "argc - " << argc;
    for(int i = 0; i < argc; i++)
    {
        std::cout<< "argv_" << i << ":"<< argv[i];
    }
     if(argc == 2)
     {
         //std::cout << "test" << std::endl;
         //std::cout << "argv[1] - " << argv[1] << std::endl;
		 //Robot_Toy_Simulator_Lib robot_simulation;
        Robot_Toy_Simulator_Lib robot_simulation = Robot_Toy_Simulator_Lib(argv[1]);
		 
		 
		std::cout << "ROBOT_TOY_SIMULATOR: " << std::endl;
        std::string Line;
        std::string _Commands;
        std::ifstream Data_File(argv[1]);

        if(Data_File.is_open())
        {
            std::cout<< "***************" << std::endl;
            std::cout<< "Data From File:" << std::endl;
            while(std::getline(Data_File,Line))
            {
                std::cout << Line << std::endl;
                _Commands += Line + '\n';
            }
            std::cout<< "***************" << std::endl;
            std::cout<< std::endl;
        }
        else
        {
            std::cout << "Cant find file - Please pass correct file location of file with commands!";
            return 0;
        }
		 
		std::string c_commands = &_Commands[0];
		robot_simulation.Read_Commands(c_commands); 
     }
    return 0;
}
