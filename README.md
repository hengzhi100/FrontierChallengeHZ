# FrontierChallengeHZ
For frontier robot challenge practice project
README.md FOR FrontierChallenge By Zhi Heng

**Overview:**

This project is for c++ code practice for Frontier. Main purpose is drive a robot moving around a 5 By 5 grid.

**Prerequisites:

using VisualStudio (2019) to create a c++ windows application including UnitTest project.

**Installation:

Step 1: Clone/download the repository.
Step 2: Navigate to the project directory.
Step 3: Run FrontierChallengeHZ.exe (Or using vs 2019 to load the solution and run the default project)

**Usage:

I created a UI page for display grid and in Grid there will be a circle and a line on the grid (0,0) , which is on bottom left as requied. 
the circle means the robot.
the line indicate the facing direction of this robot.

On right side we have some buttons:
"Left" -- Change robot facing to left (Rotate the robot 90° anticlockwise/counter clockwise)
"Right" -- Change robot facing to right (Rotate the robot 90° clockwise.)
"Move" -- Move robot towards its facing (Moves the robot 1 grid unit in the direction it is facing unless that movement will cause the robot to fall)
"Report" -- Show messagebox for robot location and facing way, like "Output: 3, 3, NORTH"
"Place" -- After input x,y and facing, when you press place, robot will be relocated into new position and facing.


**Function Features:

You can move as many steps as you want until it reaches the boundry of grid, and will alert you already at boundry and can not move again.
You can turn facing direction both right and left.
You can get report at any time for robot's current location and facing direction.

**Code explaination:

FrontierChallengeHZ.cpp -- main entry file, handle window application startup and create default windows view, handle windows event.

FrontierUI.cpp -- create ui for robot, like draw grid, draw robot, draw button and label etc..

FCPosition.cpp -- Main logical file , handle position calculate and control. 



**For test:

Creat a simple unit test file, mainly for test FCPosition functions. In real projects will need to cover all logical ways.
Also, according different project type, like web ui, or windows application, or api will create integration test cases to cover all user cases.



**Additional:

For windows UI operation, using Google search and get some help on stackflow and etc. 
Also searched some C++ language information to refresh my memoery
