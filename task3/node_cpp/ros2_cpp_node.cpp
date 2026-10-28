#include"rclcpp/rclcpp.hpp"

using namespace std;
int main(int argc,char** argv)
{
  rclcpp::init(argc,argv);
  auto node =std::make_shared<rclcpp::Node>("cpp_node");
  RCLCPP_INFO(node->get_logger(),"你好C++节点！");
  RCLCPP_INFO(node->get_logger(),"Hello,World!");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}