#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QMetaObject>
#include <thread>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "item_interfaces/msg/item.hpp"

using std::placeholders::_1;

// 继承 rclcpp::Node 的订阅者类
class ItemSubscriber : public rclcpp::Node {
public:
    ItemSubscriber(QLabel* idLabel, QLabel* infoLabel)
        : Node("item_subscriber"), id_label_(idLabel), info_label_(infoLabel) {
        
        // 创建订阅者，订阅 "item_info" 话题
        subscription_ = this->create_subscription<item_interfaces::msg::Item>(
            "item_info", 10, std::bind(&ItemSubscriber::topic_callback, this, _1));
            
        RCLCPP_INFO(this->get_logger(), "C++ Subscriber started.");
    }

private:
    void topic_callback(const item_interfaces::msg::Item::SharedPtr msg) const {
        // 拼接字符串
        QString id_str = "ID: " + QString::fromStdString(msg->id);
        QString info_str = QString("名称: %1\n类别: %2\n价格: %3\n描述: %4")
            .arg(QString::fromStdString(msg->name))
            .arg(QString::fromStdString(msg->category))
            .arg(msg->price)
            .arg(QString::fromStdString(msg->description));

        // 使用 QMetaObject::invokeMethod 将更新 UI 的操作安全地发回主线程
        QMetaObject::invokeMethod(id_label_, [this, id_str]() {
            id_label_->setText(id_str);
        }, Qt::QueuedConnection);

        QMetaObject::invokeMethod(info_label_, [this, info_str]() {
            info_label_->setText(info_str);
        }, Qt::QueuedConnection);
        
        // 终端也打印一下
        RCLCPP_INFO(this->get_logger(), "接收: %s", msg->id.c_str());
    }

    rclcpp::Subscription<item_interfaces::msg::Item>::SharedPtr subscription_;
    QLabel* id_label_;
    QLabel* info_label_;
};

int main(int argc, char** argv) {
    // 1. 初始化 ROS 2
    rclcpp::init(argc, argv);

    // 2. 初始化 Qt 应用
    QApplication app(argc, argv);

    // 3. 构建 UI 界面
    QWidget window;
    window.setWindowTitle("物品信息接收端");
    window.resize(300, 200);

    QLabel idLabel("等待消息...");
    QLabel infoLabel("...");
    idLabel.setStyleSheet("font-size: 16px; font-weight: bold;");
    infoLabel.setStyleSheet("font-size: 14px;");

    QVBoxLayout* layout = new QVBoxLayout(&window);
    layout->addWidget(&idLabel);
    layout->addWidget(&infoLabel);
    window.show();

    // 4. 创建订阅者节点
    auto node = std::make_shared<ItemSubscriber>(&idLabel, &infoLabel);

    // 5. 开启独立的 ROS 线程，防止阻塞 Qt 的事件循环
    std::thread ros_thread([node]() {
        rclcpp::spin(node);
    });
    
    // 6. 进入 Qt 主事件循环
    int ret = app.exec();

    // 7. 退出清理
    rclcpp::shutdown();
    if (ros_thread.joinable()) {
        ros_thread.join();
    }

    return ret;
}