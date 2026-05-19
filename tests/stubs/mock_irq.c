#include "ble_list_utils.h"

uint32_t mock_primask_value;
unsigned int mock_get_primask_calls;
unsigned int mock_disable_irq_calls;
unsigned int mock_set_primask_calls;
uint32_t mock_last_primask_set;

uint32_t __get_PRIMASK(void)
{
  mock_get_primask_calls++;
  return mock_primask_value;
}

void __disable_irq(void)
{
  mock_disable_irq_calls++;
}

void __set_PRIMASK(uint32_t value)
{
  mock_set_primask_calls++;
  mock_last_primask_set = value;
}

void mock_irq_reset(void)
{
  mock_primask_value = 0U;
  mock_get_primask_calls = 0U;
  mock_disable_irq_calls = 0U;
  mock_set_primask_calls = 0U;
  mock_last_primask_set = 0U;
}
