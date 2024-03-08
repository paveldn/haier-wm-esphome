#include <chrono>
#include <string>
#include "esphome/components/uart/uart.h"
#include "haier_wm.h"

using namespace esphome::uart;

namespace esphome {
namespace haier_wm {

static const char *const TAG = "haier.wm";


HaierWashingMachine::HaierWashingMachine()
    : haier_protocol_(*this) {
}

HaierWashingMachine::~HaierWashingMachine() {}

void HaierWashingMachine::set_answer_timeout(uint32_t timeout) { this->haier_protocol_.set_answer_timeout(timeout); }

void HaierWashingMachine::setup() {
  ESP_LOGI(TAG, "Haier wm initialization...");
  this->set_handlers();
}

void HaierWashingMachine::dump_config() {
  ESP_LOGCONFIG(TAG, "Haier Washing Machine");
}

void HaierWashingMachine::loop() {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  this->haier_protocol_.loop();
}

void HaierWashingMachine::set_handlers() {
  this->haier_protocol_.set_message_handler(
      haier_protocol::FrameType::ALARM_STATUS,
      std::bind(&HaierWashingMachine::accept_all_message_handler_, this, std::placeholders::_1, std::placeholders::_2,
                std::placeholders::_3));
  this->haier_protocol_.set_message_handler(
      haier_protocol::FrameType::REPORT,
      std::bind(&HaierWashingMachine::accept_all_message_handler_, this, std::placeholders::_1, std::placeholders::_2,
                std::placeholders::_3));
  this->haier_protocol_.set_default_answer_handler(
      std::bind(&HaierWashingMachine::default_answer_handler, this, std::placeholders::_1, std::placeholders::_2,
                std::placeholders::_3, std::placeholders::_4));
}

haier_protocol::HandlerError HaierWashingMachine::accept_all_message_handler_(haier_protocol::FrameType type, const uint8_t *buffer, size_t size) {
  this->haier_protocol_.send_answer(haier_protocol::HaierMessage(haier_protocol::FrameType::CONFIRM));
  return haier_protocol::HandlerError::HANDLER_OK;
}

haier_protocol::HandlerError HaierWashingMachine::default_answer_handler(haier_protocol::FrameType message_type, haier_protocol::FrameType request_type, const uint8_t* data, size_t data_size) {
  return haier_protocol::HandlerError::HANDLER_OK;
}

void HaierWashingMachine::send_custom_command(const haier_protocol::HaierMessage &message) {
  this->haier_protocol_.send_message(message, true);
}

}  // namespace haier_wm
}  // namespace esphome
