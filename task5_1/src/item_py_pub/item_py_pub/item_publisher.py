import rclpy
from rclpy.node import Node
from item_interfaces.msg import Item # type: ignore


class ItemPublisher(Node):
    def __init__(self):
        super().__init__('item_publisher')
        self.pub = self.create_publisher(Item, 'item_info', 10)
        self.timer = self.create_timer(1.0, self.publish_item)
        self.count = 0
        self.get_logger().info('Item publisher started.')

    def publish_item(self):
        msg = Item()
        msg.id = f"A{self.count:03d}"
        msg.name = "机械键盘"
        msg.category = "电子产品"
        msg.price = 399.0
        msg.description = "87键 红轴"

        self.pub.publish(msg)
        self.get_logger().info(
            f'发布: id={msg.id}, name={msg.name}, category={msg.category}, '
            f'price={msg.price}, description={msg.description}')
        self.count += 1


def main(args=None):
    rclpy.init(args=args)
    node = ItemPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()