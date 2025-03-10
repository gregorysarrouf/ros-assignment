# ROS Cloud Point Distribution Assignment

## Setup
Source your ros2 install, then copy the cloud_point_handler/ and cloud_point_interfaces/
directories to the src/ directory inside of your workstation folder (usually ros2_ws/src).
Then, build both packages using colcon:
```
colcon build --packages-select cloud_point_handler cloud_point_interfaces
```

## Execution
Open a new terminal (important), navigate to your workstation directory, and source the
setup.bash file:
```
source install/setup.bash
```

If you wish to start all three executables at the same time and within the same terminal,
navigate to the launch/ directory inside of the cloud_point_handler/ directory
(./src/cloud_point_handler/launch/). In there you will find a cloud_launch.py file. Simply
run the following:
```
ros2 launch cloud_launch.py
```

If you wish to start each executable in a different terminal, open 2 more terminals, navigate
to the workstation directory on each one, source the setup.bash files, then run the following
three commands, each one a different terminal (note that the commands are to be executed at
the root of your workstation directory, and preferably in the given order):


Start the publisher process
```
ros2 run cloud_point_handler cloud_publisher
```

Start the transform service process
```
ros2 run cloud_point_handler transform_service
```

Start the subscriber process
```
ros2 run cloud_point_handler cloud_subscriber
```
