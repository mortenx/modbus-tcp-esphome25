#include "modbus_tcp_sensor.h"
#include "esphome/core/log.h"


namespace esphome {
namespace modbus_tcp_sensor {


static const char *TAG = "modbus_tcp";


void ModbusTCPSensor::update() {
WiFiClient client;


if (!client.connect(host_.c_str(), port_)) {
ESP_LOGE(TAG, "TCP connect failed");
return;
}


uint8_t tx_id_hi = 0x00;
uint8_t tx_id_lo = 0x01;


uint8_t request[] = {
tx_id_hi, tx_id_lo,
0x00, 0x00,
0x00, 0x06,
unit_id_,
0x03,
uint8_t(reg_ >> 8), uint8_t(reg_ & 0xFF),
uint8_t(reg_count_ >> 8), uint8_t(reg_count_ & 0xFF)
};


client.write(request, sizeof(request));
delay(100);


uint8_t response[32];
int len = client.read(response, sizeof(response));


if (len < 9) {
ESP_LOGE(TAG, "Invalid response");
client.stop();
return;
}


uint32_t raw = 0;


if (reg_count_ == 2) {
uint16_t w1 = (response[9] << 8) | response[10];
uint16_t w2 = (response[11] << 8) | response[12];


if (word_order_ == "AB_CD") raw = (uint32_t(w1) << 16) | w2;
else if (word_order_ == "CD_AB") raw = (uint32_t(w2) << 16) | w1;
} else {
raw = (response[9] << 8) | response[10];
}


float value = raw * scale_;
publish_state(value);


client.stop();
}


} // namespace modbus_tcp_sensor
} // namespace esphome