import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
from my_action_interfaces.action import Sum
import time


class SumServer(Node):
    def __init__(self):
        super().__init__('sum_server')
        self._action_server = ActionServer(
            self, Sum, 'sum_action', self.execute_callback)
        self.get_logger().info('动作服务器已启动，等待目标...')

    def execute_callback(self, goal_handle):
        n = goal_handle.request.target_number
        self.get_logger().info(f'收到目标：累加到 {n}')

        current_sum = 0
        feedback_msg = Sum.Feedback()

        for i in range(1, n + 1):
            current_sum += i
            feedback_msg.current_number = i
            feedback_msg.current_sum = current_sum
            goal_handle.publish_feedback(feedback_msg)
            self.get_logger().info(f'反馈：当前数字 {i}，当前和 {current_sum}')
            time.sleep(0.5)  # 放慢一点，方便看到反馈

        goal_handle.succeed()
        result = Sum.Result()
        result.final_sum = current_sum
        self.get_logger().info(f'完成！最终累加和 = {current_sum}')
        return result


def main(args=None):
    rclpy.init(args=args)
    node = SumServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()