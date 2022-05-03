# Bachelor-Project
Project for Testing Robots in a Simulation
<p> Report can be found in report.pdf </p>
<p> The simulation can be found inside catkin_ws, and it can be run using the following roslaunch command:
  roslaunch turtlebot3_gazebo turtlebot3_mysimobs.launch 
  then in a different terminal:
  roslaunch turtlebot3_navigation turtlebot3_navigation map_file:=map.yaml (provided in this repo)
  in a third terminal:
  rosrun move_bot move_bot
#
Turtlebot 3 is owned by Robotis: https://github.com/ROBOTIS-GIT/turtlebot3
