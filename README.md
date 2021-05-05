# Kernel Simulator 
[Version 1.00] 
February 5, 2021

CONTACT INFORMATION
___________________

Contact Name:		Trong Nguyen, 100848232
                	Evan Smedley, 100848232
Affiliation: 		Carleton University - Systems and Computer Engineering


DESCRIPTION
___________

- Kernel Simulator is a program that generates an executable file that
simulates a simple OS kernel, which can be used for performance analysis of
various scheduling algorithms.

![image](https://user-images.githubusercontent.com/55768917/117086371-5c0c5880-ad1a-11eb-8132-4dbdd025609e.png)

- The application is composed of five files:
	main.c				(main C programming script)
	main.exe			(excutable file generated from main.c)
	test1.bat	 		(batch file for test1.txt)
	test1.txt	 		(text input file for test1.bat)
	test2.bat			(batch file for test2.txt)
	test2.txt 			(text input file for test2.bat)
	test3.bat			(batch file for test3.txt)
	test3.txt			(text input file for test3.bat)


INSTALLATION
____________

This program has only been tested for Windows 10 and macOS.

-------------------------- Installation Dependencies -------------------------

The application should work with the most current version of C programming 
language update C17 ISO/IEC 9899:2018. 

No other supplementary libraries and testing file with modular dependencies
are required to run this application.


USAGE
_____

---------------------------- Generating Executable ---------------------------

In order to generate the executable file, the user may wish to directly run 
the program from the source code. Open up the main.c source code in your 
desired C programming IDE and compile the source code within a Win64 Console
program (EXE) to generate the C supporting files. Once complie execute the
code which should generate an main.exe in the same directory.

----------------------------- Creating Batch file ----------------------------

test1.bat file was created using a .txt with the following script input:

	main name_of_test_file.txt name_of_output_file.txt

and save the program extension to a .bat file. This batch files calls the
main.exe to act upon name_of_test_file.txt to generate the output in another
file called name_of_output.txt.

---------------------------------- Input Data --------------------------------

The input file (called test1.txt) should contain one process per line, with a 
space between each field for example:

PID_1 Arrival_Time_1 Total_CPU_Time_1 I/O_Frequency_1 I/O_Duration_1

PID_2 Arrival_Time_2 Total_CPU_Time_2 I/O_Frequency_2 I/O_Duration_2

Note that the input file should not contain any other information such as
header, additional information, etc. All the data in the input file should be 
considered to be integers. Which looks like this in the .txt file:

	1111 5 50 20 10
	2222 10 50 20 10

Meaning: Two processes. Named 1111 and 2222. Both require 50 "ticks" to 
execute, and call a trap to request I/O service access every 20 ticks. Each 
I/O lasts 10 ticks. Process 1111 is available at tick 5, process 2222 is 
available at tick 10.

---------------------------------- Output Data --------------------------------

Similarly to the input file, the output file (output1.txt) should contain one 
process per line, with a space between each field, for example:

Time_Of_Transition_1 PID_1 Old_State_1 New_State_1

Time_Of_Transition_2 PID_2 Old_State_2 New_State_2

Note that the Old State and New State should be output to the file as a string 
(Ready, Running, Waiting, etc).

The output files have been formatted so that each output value is lined up,
making them easier to understand. This means that there are multiple spaces in
between each output value and an extra newline at the end of each line. 
If the user wants to use the output files as input for another program and 
needs the format of the output to only have one space in between output 
values, there are alternate fprintf statements commented out in the transition
function starting at line 170.

CREDITS
_______

Thanks to the support of TAs and Instructors during the development of this
application.

LICENSE
_______

[MIT](https://choosealicense.com/licenses/mit/)

Copyright (c) 2021 Trong Nguyen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
