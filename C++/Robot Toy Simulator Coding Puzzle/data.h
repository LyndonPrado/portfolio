#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <regex>
#include <fstream>

namespace Data {
    constexpr int Commands_Array_Size = 8;
    const std::string Commands[Commands_Array_Size] = {"PLACE",
                                                       "MOVE",
                                                       "LEFT",
                                                       "RIGHT",
                                                       "REPORT"};

    enum Commands_Type{
        PLACE,
        MOVE,
        LEFT,
        RIGHT,
        REPORT,
        INVALID
    };

    static Commands_Type Get_Command_Type(std::string Command_String)
    {
        int Command = Data::PLACE;
        for(const std::string &Command_To_Compare : Data::Commands)
        {
            std::size_t found = Command_String.find(Command_To_Compare);
            if(found != std::string::npos) //if substring of command is found return command type
            {
                return static_cast<Data::Commands_Type>(Command);
            }
            Command++;
        }
        return Data::INVALID;
    }

    enum Turn_Type{
        LEFT_TURN,
        RIGHT_TURN
    };
    constexpr int Direction_Array_Size = 4;
    const std::string Direction[Direction_Array_Size] = { "NORTH",
                                                          "EAST",
                                                          "SOUTH",
                                                          "WEST"
                                                        };
    enum Direction_Type{
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    static Direction_Type Get_Direction_Type(std::string Direction_String)
    {
        int Dir = Data::NORTH;
        for(const std::string &Direction_To_Compare : Data::Direction)
        {
            std::size_t found = Direction_String.find(Direction_To_Compare);
            if(found != std::string::npos) //if substring of command is found return command type
            {
                return static_cast<Data::Direction_Type>(Dir);
            }
            Dir++;
        }
        std::string Error = "Command_String doesn't exist!";
        throw Error;
    }

    struct Location{
        int X;
        int Y;
        Location(){}
        Location(int x, int y):X(x),Y(y){}
    } ;
}
#endif // DATA_H
