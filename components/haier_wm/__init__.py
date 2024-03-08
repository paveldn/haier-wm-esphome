import logging
import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.final_validate as fv
from esphome.components import uart, logger
from esphome.const import (
    CONF_ID
)

_LOGGER = logging.getLogger(__name__)

CODEOWNERS = ["@paveldn"]
DEPENDENCIES = ["uart"]


haier_ns = cg.esphome_ns.namespace("haier")
haier_wm_ns = cg.esphome_ns.namespace("haier_wm")
HaierWashingMachine = haier_wm_ns.class_(
    "HaierWashingMachine", uart.UARTDevice, cg.Component
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(HaierWashingMachine),
    }
).extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    cg.add(haier_ns.init_haier_protocol_logging())
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    # https://github.com/paveldn/HaierProtocol
    cg.add_library("pavlodn/HaierProtocol", "0.9.25")
