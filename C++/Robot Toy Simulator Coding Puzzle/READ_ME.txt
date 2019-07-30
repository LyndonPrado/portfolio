# Robot_Toy_Simulator
Author: Lyndon Prado
Robot_Toy_Simulator is a library to simulate a robot moving on a (5x5) grid table 
Robot_Toy_Simulator was written using the QT IDE

## Installation

1 - make sure you have g++ installed using mingw 
(installation guide here: https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html)  
2 - run the "Build_And_Execute.Bat" file (it will run a script to compile the libraries and build the program)
3 - once compiled there will be a "run_program.bat" generated, run that batch file after "Build_And_Execute.Bat" is excuted
(run_program passes in the "Commands.txt" file into the "Robot_Toy_Simulator_Program.exe" as the initial parameters)

## Usage
1 - once the libraries have been compiled either open "Robot_Toy_Simulator_Program.exe" in cmd and enter the text file 
with the data you want to pass into the program. Example: c:\Folder_Location> Robot_Toy_Simulator_Program.exe Commands.txt
2 - Alternatively you can select "run_program.bat" and it will do this automatically with "Commands.txt" (it will also pause the program).
3 - If you want to add additional test cases, you can change the values within the file "Commands.txt".
