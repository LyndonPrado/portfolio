#ifndef ROBOT_TOY_SIMULATOR_LIB_H
#define ROBOT_TOY_SIMULATOR_LIB_H

#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <regex>
#include <fstream>




class String_Parser{
public:
    static std::vector<std::string> _Parse_Command_String(std::string Raw_String);
    static std::vector<std::string> _Parse_Place_Command(std::string Place_Command);
    static Data::Location           _Get_Place_Location(std::string Place_Command);
    static Data::Direction_Type     _Get_Place_Direction(std::string Place_Command);
    static std::vector<std::string> _Parse_String(std::string Raw_String, char Delimiter);
    static std::vector<std::string> _Parse_String(std::string Raw_String, std::vector<char> Delimiters);
    static std::vector<std::string> _Parse_String_Collection(std::vector<std::string> Collection, char Delimiter);
};




class Robot; //forward declaration

class Board{
public:
    Board(int width,int height)
    {
        assert(width != 0 && height != 0);
        for(int i = 0; i < height; i++)
        {
            std::vector<Robot*> row;
            for(int j = 0; j < width; j++)
            {
                row.push_back(nullptr);
            }
            _Board.push_back(row);
        }

        assert(_Board.empty() == false);
        this->Width = width;
        this->Height = height;
        this->Robot_Location = {-1,-1}; //unset robot location
    }
    ~Board(){}
    void Place_Robot_On_Board(Data::Location Robot_Location,
                              Data::Direction_Type Direction,
                              Robot* Robot_To_Place);
    void Move_Location_Of_Robot(Data::Direction_Type Direction, Robot* Robot_To_Move);
    Data::Location Get_Location_Of_Robot();

    int getWidth() const;

    int getHeight() const;

private:
    std::vector<std::vector<Robot*>> _Board;
    int Width, Height;
    Data::Location Robot_Location;
private:
    void Initialize_Board(std::vector<std::vector<Robot*>> &Board_To_Initialize,int width, int height);
    void Place_Robot_On_Board(int x,int y,
                              Data::Direction_Type Direction,
                              Robot* Robot_To_Place);
    void Place_Robot_On_Board(int x, int y,
                              Data::Direction_Type Direction,
                              Robot* Robot_To_Place,
                              std::vector<std::vector<Robot*>> &Board_To_Initialize);
    void Move_Location_Of_Robot(int New_x, int New_y,
                                int &Old_x, int &Old_y,
                                Robot* Robot_To_Move,
                                std::vector<std::vector<Robot*>> &Board_To_Move_On);
};

class Robot{
public:
    Robot(){}
    ~Robot(){}
    void Set_Board(Board* Board_To_Set);
    Data::Direction_Type Direction_Facing() const;
    void Set_Direction_Facing(const Data::Direction_Type &Direction_Facing);
    void Turn(Data::Turn_Type Turn_Direction);
    void Move();
    Data::Direction_Type Get_Facing();


private:
    Data::Direction_Type _Direction_Facing;
    Board* _Board;
};



class Command_Conditions{
public:
    Command_Conditions(){}
    ~Command_Conditions(){}
    void Update_Commands(std::vector<std::string> &Command_Collection,Board* Board_Commands_For);
    bool Discard_Command(Data::Commands_Type Command, Board* Board_Command_For, Data::Location Place_Location);
    bool Discard_Command(Data::Commands_Type Command);
    void push_Executed_Command(Data::Commands_Type Command);
private:
    std::vector<Data::Commands_Type> Already_Checked_Commands;
private:
    bool Check_First_Command(Data::Commands_Type Command_To_Check);
    bool Check_Empty_Already_Checked_Commands();
    bool Within_Boundaries(Board* Board_In_Use,Data::Location Board_Location);

};

class Robot_Toy_Simulator_Lib
{
public:

    Robot_Toy_Simulator_Lib(){std::cout << "ROBOT_TOY_SIMULATOR: " << std::endl;}
    Robot_Toy_Simulator_Lib(std::string File_Location)
    {
        this->_Board = new Board(5,5);
        this->_Robot = new Robot();  
    }
    ~Robot_Toy_Simulator_Lib(){
		delete _Robot;
        delete _Board;
	}
	//reads raw string and then parses them for execution
    void Read_Commands(std::string  Commands)
	{
		std::vector<std::string> Command_Collection = String_Parser::_Parse_Command_String(Commands);
		Command_Conditions conditions;
		conditions.Update_Commands(Command_Collection,this->_Board);
		for(std::string & Command:Command_Collection)
		{
			Execute_Command(Command,this->_Board,this->_Robot);
		}
	}
    void Execute_Command(std::string Command, Board *Board_To_Use, Robot *Robot_To_Use);

private:
	Board* _Board;
	Robot* _Robot;
};

#endif // ROBOT_TOY_SIMULATOR_LIB_H
