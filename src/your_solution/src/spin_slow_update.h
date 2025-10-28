#ifndef YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_
#define YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SlowSolution : public rclcpp::Node {
 public:
  SlowSolution();
 private:
  void pos_callback(const ArrayMsg::SharedPtr msg);
  rclcpp::Subscription<ArrayMsg>::SharedPtr sub_pos;
  rclcpp::Publisher<ArrayMsg>::SharedPtr pub_pred;
};

#endif //YOUR_SOLUTION_SRC_SPIN_SLOW_UPDATE_H_
