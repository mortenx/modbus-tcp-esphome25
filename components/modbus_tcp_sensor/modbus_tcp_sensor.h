#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <WiFiClient.h>


namespace esphome {
namespace modbus_tcp_sensor {


class ModbusTCPSensor : public sensor::Sensor, public PollingComponent {
public:
void set_host(const std::string &host) { host_ = host; }
void set_port(uint16_t port) { port_ = port; }
void set_unit_id(uint8_t unit) { unit_id_ = unit; }
void set_register(uint16_t reg) { reg_ = reg; }
void set_register_count(uint16_t count) { reg_count_ = count; }
void set_scale(float scale) { scale_ = scale; }
void set_word_order(const std::string &order) { word_order_ = order; }


void update() override;


protected:
std::string host_;
uint16_t port_{502};
uint8_t unit_id_{1};
uint16_t reg_{0};
uint16_t reg_count_{2};
float scale_{1.0};
std::string word_order_;
};


} // namespace modbus_tcp_sensor
} // namespace esphome