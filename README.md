# modbus-tcp-esphome25


ESPHome external component Modbus TCP sensorite jaoks.


## Kasutamine


```yaml
external_components:
- source: github://mortenx/modbus-tcp-esphome
components: [ modbus_tcp_sensor ]


sensor:
- platform: modbus_tcp_sensor
name: "Dissolved Oxygen (mg/L)"
host: 172.16.48.49
port: 502
unit_id: 1
register: 4
register_count: 2
word_order: AB_CD
scale: 0.00015
