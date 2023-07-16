// Copyright 2019 InSoul Tech, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "locate_stylus/locate_stylus.hpp"

#include <memory>

namespace locate_stylus
{

class LocateStylus::_Impl
{
public:
  explicit _Impl(LocateStylus * ptr)
  : _node(ptr)
  {
  }

  ~_Impl()
  {
  }

private:
  LocateStylus * _node;
};

LocateStylus::LocateStylus(const rclcpp::NodeOptions & options)
: Node("locate_stylus_node", options)
{
  _init = std::thread(&LocateStylus::_Init, this);
}

LocateStylus::~LocateStylus()
{
  _init.join();

  _srv.reset();
  _sub.reset();
  _impl.reset();
  _pub.reset();

  RCLCPP_INFO(this->get_logger(), "Destroyed successfully");
}

void LocateStylus::_Init()
{
  try {
    _InitializeParameters();

    _UpdateParameters();

    _pub = this->create_publisher<std_msgs::msg::String>(_pubName, 10);

    _impl = std::make_unique<_Impl>(this);

    _sub = this->create_subscription<std_msgs::msg::String>(
      _subName,
      10,
      std::bind(&LocateStylus::_Sub, this, std::placeholders::_1));

    _srv = this->create_service<std_srvs::srv::Trigger>(
      _srvName,
      std::bind(&LocateStylus::_Srv, this, std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "Initialized successfully");
  } catch (const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "Exception in initializer: %s", e.what());
    rclcpp::shutdown();
  } catch (...) {
    RCLCPP_ERROR(this->get_logger(), "Exception in initializer: unknown");
    rclcpp::shutdown();
  }
}

void LocateStylus::_Sub(std_msgs::msg::String::UniquePtr /*ptr*/)
{
  try {
  } catch (const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "Exception in subscription: %s", e.what());
  } catch (...) {
    RCLCPP_ERROR(this->get_logger(), "Exception in subscription: unknown");
  }
}

void LocateStylus::_Srv(
  const std::shared_ptr<std_srvs::srv::Trigger::Request>/*request*/,
  std::shared_ptr<std_srvs::srv::Trigger::Response>/*response*/)
{
  try {
  } catch (const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "Exception in service: %s", e.what());
  } catch (...) {
    RCLCPP_ERROR(this->get_logger(), "Exception in service: unknown");
  }
}

void LocateStylus::_InitializeParameters()
{
  // this->declare_parameter("");
}

void LocateStylus::_UpdateParameters()
{
  // this->get_parameter("", );
}

}  // namespace locate_stylus

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(locate_stylus::LocateStylus)
