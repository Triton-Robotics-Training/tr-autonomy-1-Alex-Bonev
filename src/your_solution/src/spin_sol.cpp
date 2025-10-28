#include "spin_sol.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

//your code here
SpinSolution::SpinSolution() : Node("spinsolution") {
  sub_pos = this->create_subscription<ArrayMsg>("measuredpos", 10, std::bind(&SpinSolution::pos_callback, this, std::placeholders::_1));
  sub_vel = this->create_subscription<ArrayMsg>("measuredvel", 10, std::bind(&SpinSolution::vel_callback, this, std::placeholders::_1));
  pub_pred = this->create_publisher<ArrayMsg>("predictedpos", 10);
  loaded = false;

  timer = this->create_wall_timer(1ms, std::bind(&SpinSolution::timer_callback, this));
}

void SpinSolution::pos_callback(ArrayMsg::SharedPtr pos){
  curr_pos = pos;
}

void SpinSolution::vel_callback(ArrayMsg::SharedPtr vel){
  curr_vel = vel;
}

void SpinSolution::timer_callback(){
  if (!curr_pos || !curr_vel){
    RCLCPP_WARN(this->get_logger(), "Waiting on values...");
    return;
  }
  if (!loaded) {
    RCLCPP_INFO(this -> get_logger(), "Values transmitted!");
    loaded = true;
  }

  curr_pos->data[0] += curr_vel->data[0]/500;
  curr_pos->data[1] += curr_vel->data[1]/500;

  // RCLCPP_INFO(this->get_logger(), "Received: [%.3f, %.3f]", curr_pos->data[0], curr_pos->data[1]);
  // RCLCPP_INFO(this->get_logger(), "For Velocity, Received: [%.3f, %.3f]", curr_vel->data[0], curr_vel->data[1]);
  pub_pred -> publish(*curr_pos);
}
