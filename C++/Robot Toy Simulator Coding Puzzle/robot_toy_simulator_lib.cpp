#include "robot_toy_simulator_lib.h"

void Board::Place_Robot_On_Board(Data::Location Robot_Location, Data::Direction_Type Direction_Facing, Robot *Robot_To_Place)
{
    if(this->Robot_Location.X == -1 && this->Robot_Location.Y == -1){
        Place_Robot_On_Board(Robot_Location.X,
                             Robot_Location.Y,
                             Direction_Facing,
                             Robot_To_Place);
    }
    else //Robot is already on board, just need to move it
    {
        Move_Location_Of_Robot(Robot_Location.X,
                               Robot_Location.Y,
                               this->Robot_Location.X,
                               this->Robot_Location.Y,
                               Robot_To_Place,
                               this->_Board);
        Robot_To_Place->Set_Direction_Facing(Direction_Facing);
    }
}

void Board::Move_Location_Of_Robot(Data::Direction_Type Direction, Robot *Robot_To_Move)
{
    auto Get_New_Location = [](Data::Direction_Type Direction, Data::Location &oldLocation){
        switch (Direction) {
        case Data::NORTH: return Data::Location({oldLocation.X,oldLocation.Y + 1});
        case Data::EAST:  return Data::Location({oldLocation.X + 1,oldLocation.Y});
        case Data::SOUTH: return Data::Location({oldLocation.X,oldLocation.Y - 1});
        case Data::WEST:  return Data::Location({oldLocation.X - 1,oldLocation.Y});
        default:
            std::string Error = "invalid direction of Get_New_Location";
            throw Error;
            return oldLocation;
        }
    };

    Data::Location New_Location = (Data::Location)Get_New_Location(Direction,this->Robot_Location);
    Move_Location_Of_Robot(New_Location.X,
                           New_Location.Y,
                           this->Robot_Location.X,
                           this->Robot_Location.Y,
                           Robot_To_Move,
                           this->_Board);
}

Data::Location Board::Get_Location_Of_Robot()
{
    return Robot_Location;
}

int Board::getWidth() const
{
    return Width;
}

int Board::getHeight() const
{
    return Height;
}

void Board::Initialize_Board(std::vector<std::vector<Robot *> > &Board_To_Initialize, int width, int height)
{
    assert(width != 0 && height != 0);
    Board_To_Initialize.resize(height);
    for(int i = 0; i < height; i++)
    {
        std::vector<Robot*> row(width);
        for(int j = 0; j < width; i++)
        {
            row.push_back(nullptr);
        }
        Board_To_Initialize.push_back(row);
    }
    assert(Board_To_Initialize.empty() == false);
}

void Board::Place_Robot_On_Board(int x, int y, Data::Direction_Type Direction, Robot *Robot_To_Place)
{
    Place_Robot_On_Board(x,y,Direction,Robot_To_Place,this->_Board);
    Robot_Location = {x,y};
}

void Board::Place_Robot_On_Board(int x, int y, Data::Direction_Type Facing_Direction, Robot *Robot_To_Place, std::vector<std::vector<Robot *> > &Board_To_Initialize)
{
    Board_To_Initialize[y][x] = Robot_To_Place;
    Robot_To_Place->Set_Direction_Facing(Facing_Direction);
    Robot_To_Place->Set_Board(this);
}

void Board::Move_Location_Of_Robot(int New_x, int New_y, int &Old_x, int &Old_y, Robot *Robot_To_Move, std::vector<std::vector<Robot *> > &Board_To_Move_On)
{
    assert(New_x >= 0 && New_x <= (this->Width - 1));
    assert(New_y >= 0 && New_y <= (this->Height - 1));
//    std::cout << "Robot_To_Move: " << Robot_To_Move;
//    std::cout << " Robot_To_Move_On["<<Old_y<<"]["<<Old_x<<"]: " << Board_To_Move_On[Old_y][Old_x] << std::endl;
    assert(Robot_To_Move == Board_To_Move_On[Old_y][Old_x]);
    Board_To_Move_On[Old_y][Old_x] = nullptr;
    Board_To_Move_On[New_y][New_x] = Robot_To_Move;
    Old_x = New_x;
    Old_y = New_y;

//    std::cout << "Robot_To_Move: " << Robot_To_Move;
//    std::cout << " Robot_To_Move_On["<<Old_y<<"]["<<Old_x<<"]: " << Board_To_Move_On[Old_y][Old_x] << std::endl;
    assert(Robot_To_Move == Board_To_Move_On[New_y][New_x]);
}



std::vector<std::string> String_Parser::_Parse_Command_String(std::string Raw_String)
{
    std::vector<std::string> Parsed_Commands = _Parse_String(Raw_String,'\n');
    return Parsed_Commands;
}

std::vector<std::string> String_Parser::_Parse_Place_Command(std::string Place_Command)
{
    std::vector<std::string> Place_Command_Parsed = _Parse_String_Collection(_Parse_String(Place_Command,' '),',') ;
    return Place_Command_Parsed;
}

Data::Location String_Parser::_Get_Place_Location(std::string Place_Command)
{
    std::vector<std::string> Place_Command_Parsed = _Parse_Place_Command(Place_Command);
    std::string X_Str = Place_Command_Parsed[1];
    std::string Y_Str = Place_Command_Parsed[2];
    int X = std::stoi(X_Str);
    int Y = std::stoi(Y_Str);
    return {X,Y};
}

Data::Direction_Type String_Parser::_Get_Place_Direction(std::string Place_Command)
{
    std::vector<std::string> Place_Command_Parsed = _Parse_Place_Command(Place_Command);
    return Data::Get_Direction_Type(Place_Command_Parsed[3]);
}


std::vector<std::string> String_Parser::_Parse_String(std::string Raw_String, char Delimiter)
{
    std::vector<std::string> Parsed_String = {};
    std::string String_Buffer;
    for(unsigned int i = 0; i < Raw_String.size();i++)
    {
        char Char_Buffer = Raw_String.at(i);
        if(Char_Buffer != Delimiter)
        {
            String_Buffer += Char_Buffer;
        }
        else
        {
            Parsed_String.push_back(String_Buffer);
            String_Buffer = "";
        }
    }
    if(!String_Buffer.empty())
    {
        Parsed_String.push_back(String_Buffer);
    }
    return Parsed_String;
}

std::vector<std::string> String_Parser::_Parse_String(std::string Raw_String, std::vector<char> Delimiters)
{
    auto Check_For_Delimiters = [](char Char_To_Check, std::vector<char> Delimiters) {
        for(const char &Delimiter: Delimiters)
        {
            if(Delimiter == Char_To_Check) return true;
        }
        return false;
    };

    std::vector<std::string> Parsed_String = {};
    std::string String_Buffer;
    for(unsigned int i = 0; i < Raw_String.size();i++)
    {
        char Char_Buffer = Raw_String.at(i);
        if(!Check_For_Delimiters(Char_Buffer,Delimiters))
        {
            String_Buffer += Char_Buffer;
        }
        else
        {
            Parsed_String.push_back(String_Buffer);
            String_Buffer = "";
        }
    }
    if(!String_Buffer.empty())
    {
        Parsed_String.push_back(String_Buffer);
    }
    return Parsed_String;
}

std::vector<std::string> String_Parser::_Parse_String_Collection(std::vector<std::string> Collection, char Delimiter)
{
    std::vector<std::string> Parsed_String_Collection = {};
    for(std::string & String_To_Parse:Collection)
    {
        std::vector<std::string> Parsed_String = _Parse_String(String_To_Parse,Delimiter);
        Parsed_String_Collection.insert(std::end(Parsed_String_Collection),
                                        std::begin(Parsed_String),
                                        std::end(Parsed_String));
    }
    return Parsed_String_Collection;
}



void Robot::Set_Board(Board *Board_To_Set)
{
    this->_Board = Board_To_Set;
}

Data::Direction_Type Robot::Direction_Facing() const
{
    return _Direction_Facing;
}

void Robot::Set_Direction_Facing(const Data::Direction_Type &Direction_Facing)
{
    _Direction_Facing = Direction_Facing;
}

void Robot::Turn(Data::Turn_Type Turn_Direction)
{
    auto Set_Direction = [](Data::Turn_Type &Turn_Direction, Data::Direction_Type &Current_Direction) {
        int Current_Direction_Int = (int)Current_Direction;
        switch (Turn_Direction) {
        case Data::LEFT_TURN: (Current_Direction != Data::NORTH) ? (Current_Direction_Int--) : (Current_Direction_Int = (int)Data::WEST); break;
        case Data::RIGHT_TURN:(Current_Direction != Data::WEST) ?  (Current_Direction_Int++) : (Current_Direction_Int = (int)Data::NORTH);break;
        default:
            std::string Error_Msg = "incorrect direction type!";
            throw Error_Msg;
            break;
        }
        Current_Direction = static_cast<Data::Direction_Type>(Current_Direction_Int);
    };

    Set_Direction(Turn_Direction,_Direction_Facing);
}

void Robot::Move()
{
    assert(this->_Board != nullptr);
    this->_Board->Move_Location_Of_Robot(this->Direction_Facing(),this);
}

Data::Direction_Type Robot::Get_Facing()
{
    return _Direction_Facing;
}





//void Robot_Toy_Simulator_Lib::Read_Commands(char const* Commands)
//{
//    std::vector<std::string> Command_Collection = String_Parser::_Parse_Command_String(Commands);
//    Command_Conditions conditions;
//    conditions.Update_Commands(Command_Collection,Board_To_Use);
//    for(std::string & Command:Command_Collection)
//    {
//        Execute_Command(Command,this->_Board,this->_Robot);
//    }
//}

void Robot_Toy_Simulator_Lib::Execute_Command(std::string Command, Board *Board_To_Use, Robot *Robot_To_Use)
{
    std::cout << Command << std::endl;
    Data::Commands_Type Command_To_Execute = Data::Get_Command_Type(Command);
    switch (Command_To_Execute) {
    case Data::PLACE:
    {

//        std::vector<std::string> Place_Command = String_Parser::_Parse_Place_Command(Command);
//        std::string X_Str = Place_Command[1];
//        std::string Y_Str = Place_Command[2];
//        int X = std::stoi(X_Str);
//        int Y = std::stoi(Y_Str);
//        Data::Location Robot_Starting_Point = {X,Y};
//        Data::Direction_Type Direction_Setting = Data::Get_Direction_Type(Place_Command[3]);
        Data::Location Robot_Starting_Point = String_Parser::_Get_Place_Location(Command);
        Data::Direction_Type Direction_Setting = String_Parser::_Get_Place_Direction(Command);
        Board_To_Use->Place_Robot_On_Board(Robot_Starting_Point,Direction_Setting,Robot_To_Use);
        break;
    }
    case Data::MOVE:
    {
        Robot_To_Use->Move();
        break;
    }
    case Data::LEFT:
    {
        Robot_To_Use->Turn(Data::LEFT_TURN);
        break;
    }
    case Data::RIGHT:
    {
        Robot_To_Use->Turn(Data::RIGHT_TURN);
        break;
    }
    case Data::REPORT:
    {
        Data::Location Robot_Location = Board_To_Use->Get_Location_Of_Robot();
        Data::Direction_Type Robot_Facing = Robot_To_Use->Direction_Facing();
        std::cout << "Output: " << Robot_Location.X << "," << Robot_Location.Y << "," << Data::Direction[Robot_Facing] << std::endl << std::endl;
        break;
    }
    default:
        break;
    }
}



void Command_Conditions::Update_Commands(std::vector<std::string> &Command_Collection, Board *Board_Commands_For)
{
    for(auto it = Command_Collection.begin(); it != Command_Collection.end(); it++)
    {
        std::string Command_Str = *it;
        Data::Commands_Type Command = Data::Get_Command_Type(Command_Str);

        if(Command == Data::PLACE)
        {
            Data::Location Place_Location = String_Parser::_Get_Place_Location(Command_Str);
            if(Discard_Command(Command,Board_Commands_For,Place_Location))
            {
                Command_Collection.erase(it--);
            }
            else
            {
                push_Executed_Command(Command); //append command to history of commands
            }
        }
        else if(Command == Data::INVALID)
        {
            Command_Collection.erase(it--);
        }
        else
        {
            if(Discard_Command(Command))
            {
                Command_Collection.erase(it--);
            }
            else
            {
                push_Executed_Command(Command); //append command to history of commands
            }
        }
    }
}

bool Command_Conditions::Discard_Command(Data::Commands_Type Command, Board *Board_Command_For,Data::Location Place_Location)
{
    //check if the first command is place and if there is some checked commands in the already checked buffer
    if(!Check_Empty_Already_Checked_Commands() && !Check_First_Command(Data::PLACE))
    {
        return true;
    }
    else
    {
        if(Command == Data::PLACE)
        {
            if(Within_Boundaries(Board_Command_For,Place_Location))
            {
                return false; //do not discard because it is within range
            }
            else
            {
                return true; //outside of boundaries of the board so discard
            }
        }
        else
        {
            return false; //Other commands after initial place shoud not be discarded
        }
    }
}

bool Command_Conditions::Discard_Command(Data::Commands_Type Command)
{
    if(Check_Empty_Already_Checked_Commands() && !Check_First_Command(Data::PLACE))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Command_Conditions::push_Executed_Command(Data::Commands_Type Command)
{
    Already_Checked_Commands.push_back(Command);
}

bool Command_Conditions::Check_First_Command(Data::Commands_Type Command_To_Check)
{
    //check if the first command is the same as Command to check
    if(Already_Checked_Commands.empty()) return false;
    return (Command_To_Check == Already_Checked_Commands.at(0))? true:false;
}

bool Command_Conditions::Check_Empty_Already_Checked_Commands()
{
    return Already_Checked_Commands.empty();
}

bool Command_Conditions::Within_Boundaries(Board *Board_In_Use, Data::Location Board_Location)
{
    auto Check_In_Range = [](int range_Min,int range_Max,int value)
    {
        return ((value >= range_Min) && (value <= range_Max)) ? true:false;
    };
    bool X_In_Range = Check_In_Range(0,Board_In_Use->getWidth(),Board_Location.X);
    bool Y_In_Range = Check_In_Range(0,Board_In_Use->getHeight(),Board_Location.Y);
    return (X_In_Range == true && Y_In_Range == true) ? true:false;
}
