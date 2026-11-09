import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from my_action_interfaces.action import Sum
import sys

class SumClient(Node):
    def __init__(self):
        super().__init__('sum_client')
        self._action_client = ActionClient(self, Sum, 'sum_action')
        self.get_logger().info('客户端已启动，等待服务器...')

    def send_goal(self, n):
        self.get_logger().info('等待动作服务器...')
        self._action_client.wait_for_server()

        goal_msg = Sum.Goal()
        goal_msg.target_number = n

        self.get_logger().info(f'发送目标：累加到 {n}')
        self._send_goal_future = self._action_client.send_goal_async(
            goal_msg, feedback_callback=self.feedback_callback)
        self._send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('目标被服务器拒绝')
            return
        self.get_logger().info('目标已被接受，等待结果...')
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def feedback_callback(self, feedback_msg):
        fb = feedback_msg.feedback
        self.get_logger().info(
            f'[反馈] 当前数字 {fb.current_number}，当前和 {fb.current_sum}')

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info(f'[最终结果] 累加和 = {result.final_sum}')
        rclpy.shutdown()


def main(args=None):
    rclpy.init(args=args)
    node = SumClient()
    
    # 默认数字是 10，如果用户输入了参数，就取用户输入的那个
    n = 10
    if len(sys.argv) > 1:
        n = int(sys.argv[1])
        
    node.send_goal(n)
    rclpy.spin(node)
    node.destroy_node()

if __name__ == '__main__':
    main()