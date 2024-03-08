#pragma once

#include "esphome/components/uart/uart.h"
// HaierProtocol
#include <protocol/haier_protocol.h>

namespace esphome {
namespace haier_wm {

class HaierWashingMachine : public esphome::Component,
                            public esphome::uart::UARTDevice,
                            public haier_protocol::ProtocolStream {
 public:
  HaierWashingMachine();
  HaierWashingMachine(const HaierWashingMachine &) = delete;
  HaierWashingMachine &operator=(const HaierWashingMachine &) = delete;
  ~HaierWashingMachine();
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }
  size_t available() noexcept override { return esphome::uart::UARTDevice::available(); };
  size_t read_array(uint8_t *data, size_t len) noexcept override {
    return esphome::uart::UARTDevice::read_array(data, len) ? len : 0;
  };
  void write_array(const uint8_t *data, size_t len) noexcept override {
    esphome::uart::UARTDevice::write_array(data, len);
  };
  bool can_send_message() const { return haier_protocol_.get_outgoing_queue_size() == 0; };
  void set_answer_timeout(uint32_t timeout);

 protected:
  virtual void set_handlers();
  haier_protocol::ProtocolHandler haier_protocol_;
};

}  // namespace haier_wm
}  // namespace esphome
