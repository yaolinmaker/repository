#include "rclcpp/rclcpp.hpp"
#include "fibonacci_interfaces/srv/fibonacci.hpp"

#include <chrono>
#include <memory>
#include <thread>

using Fibonacci = fibonacci_interfaces::srv::Fibonacci;
using namespace std::chrono_literals;

class FibonacciClient : public rclcpp::Node
{
public:
  FibonacciClient() : Node("fibonacci_client")
  {
    client_ = this->create_client<Fibonacci>("fibonacci");

    // 等待服务端上线，否则请求会失败
    while (!client_->wait_for_service(1s)) {
      RCLCPP_INFO(this->get_logger(), "等待服务端上线...");
    }
    RCLCPP_INFO(this->get_logger(), "服务端已上线，开始请求斐波那契数列");

    // 循环请求 n = 1 到 10
    for (int64_t n = 1; n <= 10; ++n) {
      auto request = std::make_shared<Fibonacci::Request>();
      request->n = n;

      // 客户端发送前的打印
      RCLCPP_INFO(this->get_logger(), "【客户端】请求第 %ld 个斐波那契数", n);

      // 异步发送请求，然后同步等待结果
      auto future = client_->async_send_request(request);

      auto ret = rclcpp::spin_until_future_complete(
        this->get_node_base_interface(), future);

      if (ret == rclcpp::FutureReturnCode::SUCCESS) {
        auto response = future.get();
        // 客户端收到后的打印
        RCLCPP_INFO(
          this->get_logger(),
          "【客户端】收到 fib(%ld) = %ld",
          n, response->fib_n);
      } else {
        RCLCPP_ERROR(this->get_logger(), "第 %ld 次请求失败", n);
      }

      // 稍作间隔，让终端输出更清晰（可选）
      std::this_thread::sleep_for(300ms);
    }
  }

private:
  rclcpp::Client<Fibonacci>::SharedPtr client_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FibonacciClient>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}