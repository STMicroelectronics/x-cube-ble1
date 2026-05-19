#ifndef TEST_HCI_LE_H
#define TEST_HCI_LE_H

#include <stdint.h>

int hci_le_read_local_version(uint8_t *hci_version, uint16_t *hci_revision,
                              uint8_t *lmp_pal_version, uint16_t *manufacturer_name,
                              uint16_t *lmp_pal_subversion);

#endif
