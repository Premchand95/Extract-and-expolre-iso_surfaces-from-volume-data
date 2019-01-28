# Extract-and-expolre-iso_surfaces-from-volume-data
CSCI 55200 DATA VISUALIZATION

## Requirements:

```
•	Microsoft Visual Studio 2017
•	CMake 3.9.6
•	VTK 8.1.0
```

## Files:

```
•	prem.cxx (source file)
•	CMakeLists.txt (source file)
•	prem.exe (executable file)
```

### Execution

1)	Make sure Visual studio, CMake and VTK installed and synchronized each other perfectly.
2)	Create a “src” folder and put source files in it. i.e prem.cxx and CMakeLists.txt
3)	Create a “build” folder and make sure it is empty.
4)	Open CMake-gui desktop app.
5)	Give folder path of “src” to “where is the source code” in CMake-gui app.

```
Example: path = C:/…../Project2/src
```

6)	Give folder path of “build” to “where to build the binaries”
7)	Click configure 
8)	After successful configure, you will notice Configuring done, then Click Generate 
9)	After successful Generating, you will notice Generating done 
10)	 Files are generated in “build” folder. You will find “prem.sln” in it. Double Click on it. it will lead you to Visual Studio.
11)	 After successful installation and scanning of files, it will show Ready in bottom-left corner. Then Right click on ALL_BUILD and click on Build.
12)	After successful build, you will notice Debug folder in “build” folder containing three files namely prem.exe, prem.dil and prem.pdb. Open Debug folder and put the “ironProt.vtk” in it.
13)	Copy all .dil and .pdb files in ….\VTK\bin\bin\Debug (these files are created while installing VTK through CMake) 
14)	Paste those files in ….\build\Debug i.e debug folder created in build containing prem.exe and ironProt.vtk
15)	Open command prompt navigate to build folder containing executable file.

```
Example: cd C:\.....\Project2\build\Debug
```

16)	Run the executable file in command prompt passing image name as arguments.

```
Example: > prem.exe ironProt.vtk
```
