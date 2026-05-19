#ifndef TEST_BLE_LIST_UTILS_H
#define TEST_BLE_LIST_UTILS_H

#include <stdint.h>

uint32_t __get_PRIMASK(void);
void __disable_irq(void);
void __set_PRIMASK(uint32_t value);

extern uint32_t mock_primask_value;
extern unsigned int mock_get_primask_calls;
extern unsigned int mock_disable_irq_calls;
extern unsigned int mock_set_primask_calls;
extern uint32_t mock_last_primask_set;

void mock_irq_reset(void);

#endif
