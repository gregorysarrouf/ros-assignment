#include "rclcpp/rclcpp.hpp"
#include "cloud_point_interfaces/msg/cloud_points.hpp"
#include "geometry_msgs/msg/point.hpp"
#include <vector>

class CloudPublisher : public rclcpp::Node {
public:
    CloudPublisher() : Node("cloud_publisher") {
        publisher_ = this->create_publisher<cloud_point_interfaces::msg::CloudPoints>("cloud_points", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&CloudPublisher::publishPoints, this));
    }

private:
    void publishPoints() {
        auto message = cloud_point_interfaces::msg::CloudPoints();
        for (int i = 0; i < 5; ++i) {
            geometry_msgs::msg::Point p;
            p.x = static_cast<float>(rand() % 10);
            p.y = static_cast<float>(rand() % 10);
            p.z = static_cast<float>(rand() % 10);
            message.points.push_back(p);
        }
        RCLCPP_INFO(this->get_logger(), "Publishing cloud points");
        publisher_->publish(message);
    }

    rclcpp::Publisher<cloud_point_interfaces::msg::CloudPoints>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CloudPublisher>());
    rclcpp::shutdown();
    return 0;
}
