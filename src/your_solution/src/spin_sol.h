#ifndef YOUR_SOLUTION_SRC_SPIN_SOL_H_
#define YOUR_SOLUTION_SRC_SPIN_SOL_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;
using namespace std::chrono_literals;

class SpinSolution : public rclcpp::Node {
 public:
  SpinSolution();
 private:
  void pos_callback(const ArrayMsg::SharedPtr pos);
  void vel_callback(const ArrayMsg::SharedPtr vel);
  void timer_callback();
  bool loaded;
  rclcpp::Subscription<ArrayMsg>::SharedPtr sub_pos;
  rclcpp::Subscription<ArrayMsg>::SharedPtr sub_vel;
  rclcpp::Publisher<ArrayMsg>::SharedPtr pub_pred;
  rclcpp::TimerBase::SharedPtr timer;
  ArrayMsg::SharedPtr curr_pos;
  ArrayMsg::SharedPtr curr_vel;
};

#endif //YOUR_SOLUTION_SRC_SPIN_SOL_H_
