#include "rclcpp/rclcpp.hpp"
#include "cloud_point_interfaces/msg/cloud_points.hpp"
#include "cloud_point_interfaces/srv/transform_points.hpp"

class CloudSubscriber : public rclcpp::Node {
public:
    CloudSubscriber() : Node("cloud_subscriber") {
        subscription_ = this->create_subscription<cloud_point_interfaces::msg::CloudPoints>(
            "cloud_points", 10, std::bind(&CloudSubscriber::processCloudPoints, this, std::placeholders::_1));

        client_ = this->create_client<cloud_point_interfaces::srv::TransformPoints>("transform_service");
    }

private:
    void processCloudPoints(const cloud_point_interfaces::msg::CloudPoints::SharedPtr msg) {
        if (!client_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Transformation service not available");
            return;
        }

        auto request = std::make_shared<cloud_point_interfaces::srv::TransformPoints::Request>();
        request->input_points = msg->points;

        auto future = client_->async_send_request(request);
        RCLCPP_INFO(this->get_logger(), "Requesting transformation for %zu points", msg->points.size());
    }

    rclcpp::Subscription<cloud_point_interfaces::msg::CloudPoints>::SharedPtr subscription_;
    rclcpp::Client<cloud_point_interfaces::srv::TransformPoints>::SharedPtr client_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CloudSubscriber>());
    rclcpp::shutdown();
    return 0;
}
