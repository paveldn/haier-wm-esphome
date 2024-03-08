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
}

}  // namespace haier_wm
}  // namespace esphome
