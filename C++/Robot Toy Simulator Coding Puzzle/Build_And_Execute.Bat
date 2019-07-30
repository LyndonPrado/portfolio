g++ -c robot_toy_simulator_lib.cpp
g++ -shared -o robot_toy_simulator_lib.dll robot_toy_simulator_lib.o -Wl,--out-implib,librobot_toy_simulator_lib.a
g++ -c main.cpp
g++ -o Robot_Toy_Simulator_Program.exe main.o -L. -lrobot_toy_simulator_lib
Robot_Toy_Simulator_Program.exe Commands.txt
type NUL > run_program.bat
ECHO Robot_Toy_Simulator_Program.exe Commands.txt>> run_program.bat
ECHO pause >> run_program.bat
pause