#include "rclcpp/rclcpp.hpp"
#include "cloud_point_interfaces/srv/transform_points.hpp"

class TransformService : public rclcpp::Node {
public:
    TransformService() : Node("transform_service") {
        service_ = this->create_service<cloud_point_interfaces::srv::TransformPoints>(
            "transform_service", std::bind(&TransformService::handleTransform, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    // Apply a simple transformation to points (adding 1.0 to all coordinates)
    void handleTransform(
        const std::shared_ptr<cloud_point_interfaces::srv::TransformPoints::Request> request,
        std::shared_ptr<cloud_point_interfaces::srv::TransformPoints::Response> response) {
        
        for (const auto &point : request->input_points) {
            geometry_msgs::msg::Point p;
            p.x = point.x + 1.0;
            p.y = point.y + 1.0;
            p.z = point.z + 1.0;
            response->transformed_points.push_back(p);
        }

        RCLCPP_INFO(this->get_logger(), "Transformed %zu points", request->input_points.size());
    }

    rclcpp::Service<cloud_point_interfaces::srv::TransformPoints>::SharedPtr service_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TransformService>());
    rclcpp::shutdown();
    return 0;
}
