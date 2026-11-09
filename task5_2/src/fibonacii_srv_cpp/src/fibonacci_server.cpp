#include "rclcpp/rclcpp.hpp"
#include "fibonacci_interfaces/srv/fibonacci.hpp"

#include <memory>
#include <cstdint>

using Fibonacci = fibonacci_interfaces::srv::Fibonacci;

// 迭代法计算第 n 个斐波那契数（fib(1)=1, fib(2)=1, fib(3)=2 ...）
int64_t compute_fib(int64_t n)
{
  if (n <= 0) return 0;
  if (n == 1 || n == 2) return 1;

  int64_t a = 1;  // fib(1)
  int64_t b = 1;  // fib(2)
  for (int64_t i = 3; i <= n; ++i) {
    int64_t c = a + b;
    a = b;
    b = c;
  }
  return b;
}

class FibonacciServer : public rclcpp::Node
{
public:
  FibonacciServer() : Node("fibonacci_server")
  {
    service_ = this->create_service<Fibonacci>(
      "fibonacci",
      [this](
        const std::shared_ptr<Fibonacci::Request> request,
        std::shared_ptr<Fibonacci::Response> response)
      {
        int64_t n = request->n;
        int64_t fib_n = compute_fib(n);

        // 把结果填入响应
        response->fib_n = fib_n;

        // 服务端在回调中打印，与客户端形成交替输出
        RCLCPP_INFO(
          this->get_logger(),
          "【服务端】收到请求 n=%ld，计算 fib(%ld) = %ld",
          n, n, fib_n);
      });

    RCLCPP_INFO(this->get_logger(), "斐波那契服务端已启动，等待请求...");
  }

private:
  rclcpp::Service<Fibonacci>::SharedPtr service_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FibonacciServer>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}