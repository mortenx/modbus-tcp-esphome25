import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_NAME


modbus_tcp_ns = cg.esphome_ns.namespace("modbus_tcp_sensor")
ModbusTCPSensor = modbus_tcp_ns.class_(
"ModbusTCPSensor", sensor.Sensor, cg.PollingComponent
)


CONF_HOST = "host"
CONF_PORT = "port"
CONF_REGISTER = "register"
CONF_REGISTER_COUNT = "register_count"
CONF_SCALE = "scale"
CONF_WORD_ORDER = "word_order"
CONF_UNIT_ID = "unit_id"


CONFIG_SCHEMA = sensor.sensor_schema().extend(
{
cv.GenerateID(): cv.declare_id(ModbusTCPSensor),
cv.Required(CONF_HOST): cv.string,
cv.Optional(CONF_PORT, default=502): cv.int_,
cv.Optional(CONF_UNIT_ID, default=1): cv.int_,
cv.Required(CONF_REGISTER): cv.int_,
cv.Optional(CONF_REGISTER_COUNT, default=2): cv.int_,
cv.Optional(CONF_SCALE, default=1.0): cv.float_,
cv.Optional(CONF_WORD_ORDER, default="AB_CD"): cv.string,
}
).extend(cv.polling_component_schema("5s"))


async def to_code(config):
var = cg.new_Pvariable(config[CONF_ID])
await cg.register_component(var, config)
await sensor.register_sensor(var, config)


cg.add(var.set_host(config[CONF_HOST]))
cg.add(var.set_port(config[CONF_PORT]))
cg.add(var.set_unit_id(config[CONF_UNIT_ID]))
cg.add(var.set_register(config[CONF_REGISTER]))
cg.add(var.set_register_count(config[CONF_REGISTER_COUNT]))
cg.add(var.set_scale(config[CONF_SCALE]))
cg.add(var.set_word_order(config[CONF_WORD_ORDER]))