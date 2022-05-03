#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <random>

// Define a client for to send goal requests to the move base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
	// Initialize the simple navigation goals node
	ros::init(argc, argv, "move_bot");
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);
	// Wait 5 sec for move base action server to come up
	while(!ac.waitForServer (ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;
	// set up the frame parameters
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();
	
	int min=0;
	srand (time(NULL));

	float goals_first_portion[30] =  {-6.0,-5.7,-5.5,-5.0,-4.7,-4.5,-4.2,-4.0,-3.5,-3,-2.5,-2,-1.7,-1.5,-1,-0.7,0,0.5,1,1.5,2.0,2.5,3,3.5,4,4.3,4.7,5,5.5,6};
	float f_x=6.7;
	float f_w=0.71;
	float goals_first_corner [5][2]={{6.2,6.4},{6.3,7}, {5.1,7.27}, {5.5,8},{4.4,8.4}};
	float f_w_fc=0;
	float goals_second_portion[15] = {4.5,4.3,4,3.7,3.5,3,2.7,2.5,2.3,2,1.7,1.5,1,0.7,0.5};
	float f_y_2=8.4;
	float f_w_2=0.06;
	float goals_third_portion[32][3] = {{1.56,8.51,0.06},{0.08,7.91,0.52},{0.61,7.34,0.42},
					{0,7.15,0.62},{-0.56,6.48,0.45},{-0.07,6.46,0.59},
					{-0.7,6.05,0.66}, {-1.1,5.03,0.92},{-0.36,5,0.71},
					{0.27,4.14,0.17},{-0.94,3.27,0.16},{-1.7,2.98,0.84},
					{-2.04,2.18,0.85},{-1.27,2.03,0.89},{-1.27,1.12,0.82},
					{-0.26,0.69,0.42},{0,0,0.39},{-1,-0.7,0.68},
					{-1.64,-1.34,0.89},{-0.76,-1.69,0.57},{-1.61,-2.61,0.89},
					{-0.49,-3.07,0.41},{-1.62,-3.63,0.43},{-1,-3.8,0.5}, 
					{-1.69,-4.3,0.53},{-2.14,-4.7,0.9},{-1.4,-5.19,0.89},
					{-2.29,-5.18,0.92},{-1.77,-6.3,0.91},{-0.94,-5.89,0.88},
					{-1.09,-6.74,0.91},{-0.36,-6.83,1}};
	float goals_fourth_portion[18][2] ={{-0.45,-7.47},{0.16,-6.79},{0.58,-7.46},
	{1.07,-6.95},{1.81,-7.53},{1.92,-6.92},
	{2.29,-7.3},{2.78,-6.82},{2.17,-7.39},
	{2.86,-7.02},{3.05,-7.55},{3.88,-7.18},
	{3.77,-7.41},{3.69,-7.11},{4.11,-7.46},
	{4.58,-7.18},{4.63,-7.56},{5.09,-7.04}};
	float f_w_4=1;
	float x,y,w;
	
	int max1=29,max2=4,max3=14,max4=31,max5=17;

	
	for (int j=1;j<100;j++)
	{
	int min1=0,min2=0,min3=0,min4=0,min5=0;
	int goal_max=0;
	double start =ros::Time::now().toSec();
	int checkpoints1 =(rand() % static_cast<int>(max1 - 0 + 1));
	int checkpoints2 =(rand() % static_cast<int>(max2 - 0 + 1));
	int checkpoints3 =(rand() % static_cast<int>(max3 - 0 + 1));
	int checkpoints4 =(rand() % static_cast<int>(max4 - 0 + 1));
	int checkpoints5 =(rand() % static_cast<int>(max5 - 0 + 1));
	for (int i =0; i< checkpoints1; i++){
		// Define a position and orientation for the robot to reach
		int random_point=min1 + (rand() % static_cast<int>(max1 - min1 + 1));
		min1=random_point+1;
		if(min1>=max1)
			break;
		goal.target_pose.pose.position.x = f_x;
		goal.target_pose.pose.position.y = goals_first_portion[random_point];
		goal.target_pose.pose.orientation.w = f_w;
		// Send the goal position and orientation for the robot to reach
		ROS_INFO ("Sending goal");
		ac.sendGoal (goal);
		goal_max++;
		// Wait an infinite time for the results
		ac.waitForResult();
		ros::Duration(5.0).sleep();
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO( "checkpoint reached");
	else
		ROS_INFO("checkpoint can't be reached");
		}
	for (int i =0; i< checkpoints2; i++){
		// Define a position and orientation for the robot to reach
		int random_point=min2 + (rand() % static_cast<int>(max2 - min2 + 1));
		min2=random_point+1;
		if(min2>=max2)
			break;
		goal.target_pose.pose.position.x = goals_first_corner [random_point][0];
		goal.target_pose.pose.position.y = goals_first_corner [random_point][1];
		goal.target_pose.pose.orientation.w = f_w_fc;
		// Send the goal position and orientation for the robot to reach
		ROS_INFO ("Sending goal");
		ac.sendGoal (goal);
		goal_max++;
		// Wait an infinite time for the results
		ac.waitForResult();
		ros::Duration(5.0).sleep();
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO( "checkpoint reached");
	else
		ROS_INFO("checkpoint can't be reached");
		}
	for (int i =0; i< checkpoints3; i++){
		// Define a position and orientation for the robot to reach
		int random_point=min3 + (rand() % static_cast<int>(max3 - min3 + 1));
		min3=random_point+1;
		if(min3>=max3)
			break;
		goal.target_pose.pose.position.x = goals_second_portion[random_point];
		goal.target_pose.pose.position.y = f_y_2;
		goal.target_pose.pose.orientation.w = f_w_2;
		// Send the goal position and orientation for the robot to reach
		ROS_INFO ("Sending goal");
		ac.sendGoal (goal);
		goal_max++;
		// Wait an infinite time for the results
		ac.waitForResult();
		ros::Duration(5.0).sleep();
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO( "checkpoint reached");
	else
		ROS_INFO("checkpoint can't be reached");
		}
	for (int i =0; i< checkpoints4; i++){
		// Define a position and orientation for the robot to reach
		int random_point=min4 + (rand() % static_cast<int>(max4 - min4 + 1));
		min4=random_point+1;
		if(min4>=max4)
			break;
		goal.target_pose.pose.position.x = goals_third_portion[random_point][0];
		goal.target_pose.pose.position.y = goals_third_portion[random_point][1];
		goal.target_pose.pose.orientation.w = goals_third_portion[random_point][2];
		// Send the goal position and orientation for the robot to reach
		ROS_INFO ("Sending goal");
		ac.sendGoal (goal);
		goal_max++;
		// Wait an infinite time for the results
		ac.waitForResult();
		ros::Duration(5.0).sleep();
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO( "checkpoint reached");
	else
		ROS_INFO("checkpoint can't be reached");
		}
	for (int i =0; i< checkpoints5; i++){
		// Define a position and orientation for the robot to reach
		int random_point=min5 + (rand() % static_cast<int>(max5 - min5 + 1));
		min5=random_point+1;
		if(min5>=max5)
			break;
		goal.target_pose.pose.position.x = goals_fourth_portion[random_point][0];
		goal.target_pose.pose.position.y = goals_fourth_portion[random_point][1];
		goal.target_pose.pose.orientation.w = f_w_4;
		// Send the goal position and orientation for the robot to reach
		ROS_INFO ("Sending goal");
		ac.sendGoal (goal);
		goal_max++;
		// Wait an infinite time for the results
		ac.waitForResult();
		ros::Duration(5.0).sleep();
	// Check if the robot reached its goal
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO( "checkpoint reached");
	else
		ROS_INFO("checkpoint can't be reached");
		}
	goal.target_pose.pose.position.x = f_x;
	goal.target_pose.pose.position.y = goals_first_portion[0];
	goal.target_pose.pose.orientation.w = f_w;
		// Send the goal position and orientation for the robot to reach
	ROS_INFO ("Sending goal");
	ac.sendGoal (goal);
	goal_max++;
		// Wait an infinite time for the results
	ac.waitForResult();
	ros::Duration(5.0).sleep();
	double final_secs =ros::Time::now().toSec();
	ROS_INFO_STREAM(final_secs-start);
	ROS_INFO_STREAM(goal_max);
	}
	return 0;
}




