cmake_minimum_required(VERSION 3.8)
project(cloud_point_handler)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(cloud_point_interfaces REQUIRED)

add_executable(cloud_publisher src/cloud_publisher.cpp)
ament_target_dependencies(cloud_publisher rclcpp geometry_msgs cloud_point_interfaces)

add_executable(cloud_subscriber src/cloud_subscriber.cpp)
ament_target_dependencies(cloud_subscriber rclcpp geometry_msgs cloud_point_interfaces)

add_executable(transform_service src/transform_service.cpp)
ament_target_dependencies(transform_service rclcpp geometry_msgs cloud_point_interfaces)

install(TARGETS
  cloud_publisher
  cloud_subscriber
  transform_service
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
