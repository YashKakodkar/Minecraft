CS 378H Honors Graphics
Assignment 6: Virtual Mannequin Milestone 2
------------------------------------

Student 1
Name: Yash Shenvi Kakodkar
UTEID: ys22297

Student 2
Name: Andrew Do
UTEID: amd5637

--------------------------------------
Features Implemented:
We implemented a way to group a group of blocks together (Chunks).
We implemented a way to create the chunks and render them (Chunk Manager).
We implemented chunk loading as we move throughout the world. 
We implemented Perlin noise to randomize our terrain, while still looking like terrain. 
We implemented a day night cycle that cycles every 40 seconds. 

HOW TO COMPILE ON WINDOWS:
1. use the windows src code with a updates cmakelist.txt
2. DOWNLOAD VCPKG https://github.com/Microsoft/vcpkg
3. install dependencies with
.\vcpkg install glfw3
.\vcpkg install glew
.\vcpkg install glm
4. run .\vcpkg integrate install in cmd
5. run cmake with /src being the source
and /build being the build
6. configure cmake with win32
7. hit generate
8. check the advanced options in cmake
9. find the CMAKE_CXX_STANDARD_LIBARARIES and append opengl32.lib to the end of the line (line should have a whole bunch of .lib's to start)
10. generate with visual studio
11. build and run on visual studio
