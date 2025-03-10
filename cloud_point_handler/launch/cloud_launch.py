from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cloud_point_handler',
            executable='cloud_publisher',
            name='cloud_publisher'
        ),
        Node(
            package='cloud_point_handler',
            executable='cloud_subscriber',
            name='cloud_subscriber'
        ),
        Node(
            package='cloud_point_handler',
            executable='transform_service',
            name='transform_service'
        ),
    ])
