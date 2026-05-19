#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ble_list.h"
#include "ble_list_utils.h"
#include "bluenrg_def.h"
#include "bluenrg_utils.h"

typedef struct
{
  tListNode link;
  const char *name;
} TestNode;

static int tests_run;
static int tests_failed;

static uint8_t mock_hci_status;
static uint8_t mock_hci_version;
static uint16_t mock_hci_revision;
static uint8_t mock_lmp_pal_version;
static uint16_t mock_manufacturer_name;
static uint16_t mock_lmp_pal_subversion;
static unsigned int mock_hci_call_count;

int hci_le_read_local_version(uint8_t *hci_version, uint16_t *hci_revision,
                              uint8_t *lmp_pal_version, uint16_t *manufacturer_name,
                              uint16_t *lmp_pal_subversion)
{
  mock_hci_call_count++;
  *hci_version = mock_hci_version;
  *hci_revision = mock_hci_revision;
  *lmp_pal_version = mock_lmp_pal_version;
  *manufacturer_name = mock_manufacturer_name;
  *lmp_pal_subversion = mock_lmp_pal_subversion;
  return mock_hci_status;
}

static void fail_test(const char *expression, const char *file, int line)
{
  fprintf(stderr, "FAIL: %s:%d: %s\n", file, line, expression);
  tests_failed++;
}

#define EXPECT_TRUE(condition) \
  do { \
    if (!(condition)) { \
      fail_test(#condition, __FILE__, __LINE__); \
      return; \
    } \
  } while (0)

#define EXPECT_EQ_INT(expected, actual) EXPECT_TRUE((expected) == (actual))
#define EXPECT_EQ_PTR(expected, actual) EXPECT_TRUE((expected) == (actual))

#define RUN_TEST(test_function) \
  do { \
    tests_run++; \
    mock_irq_reset(); \
    mock_hci_call_count = 0U; \
    test_function(); \
  } while (0)

static void init_nodes(TestNode *nodes, size_t count)
{
  size_t index;

  memset(nodes, 0, sizeof(*nodes) * count);
  for (index = 0; index < count; index++) {
    nodes[index].name = "";
  }
}

static void expect_irq_calls(unsigned int expected_count, uint32_t expected_primask)
{
  EXPECT_EQ_INT(expected_count, mock_get_primask_calls);
  EXPECT_EQ_INT(expected_count, mock_disable_irq_calls);
  EXPECT_EQ_INT(expected_count, mock_set_primask_calls);
  EXPECT_EQ_INT(expected_primask, mock_last_primask_set);
}

static void expect_list_order(tListNode *head, TestNode **expected, size_t count)
{
  size_t index;
  tListNode *cursor = head->next;

  for (index = 0; index < count; index++) {
    EXPECT_EQ_PTR(&expected[index]->link, cursor);
    cursor = cursor->next;
  }

  EXPECT_EQ_PTR(head, cursor);
  EXPECT_EQ_PTR(count == 0U ? head : &expected[0]->link, head->next);
  EXPECT_EQ_PTR(count == 0U ? head : &expected[count - 1U]->link, head->prev);

  cursor = head->prev;
  for (index = count; index > 0U; index--) {
    EXPECT_EQ_PTR(&expected[index - 1U]->link, cursor);
    cursor = cursor->prev;
  }

  EXPECT_EQ_PTR(head, cursor);
}

static void test_list_init_head_creates_empty_circular_list(void)
{
  tListNode head;
  TestNode *expected[] = {0};

  list_init_head(&head);

  EXPECT_EQ_PTR(&head, head.next);
  EXPECT_EQ_PTR(&head, head.prev);
  EXPECT_EQ_INT(0, list_get_size(&head));
  expect_irq_calls(1U, 0U);
  expect_list_order(&head, expected, 0U);
}

static void test_list_is_empty_reports_state_changes(void)
{
  tListNode head;
  TestNode node;
  TestNode *expected[] = {&node};

  init_nodes(&node, 1U);
  list_init_head(&head);

  mock_irq_reset();
  mock_primask_value = 7U;
  EXPECT_EQ_INT(1, list_is_empty(&head));
  expect_irq_calls(1U, 7U);

  list_insert_head(&head, &node.link);
  expect_list_order(&head, expected, 1U);

  mock_irq_reset();
  mock_primask_value = 3U;
  EXPECT_EQ_INT(0, list_is_empty(&head));
  expect_irq_calls(1U, 3U);
}

static void test_list_insert_head_places_new_node_first(void)
{
  tListNode head;
  TestNode nodes[2];
  TestNode *expected[] = {&nodes[1], &nodes[0]};

  init_nodes(nodes, 2U);
  list_init_head(&head);
  list_insert_head(&head, &nodes[0].link);

  mock_irq_reset();
  mock_primask_value = 9U;
  list_insert_head(&head, &nodes[1].link);

  expect_irq_calls(1U, 9U);
  expect_list_order(&head, expected, 2U);
}

static void test_list_insert_tail_places_new_node_last(void)
{
  tListNode head;
  TestNode nodes[2];
  TestNode *expected[] = {&nodes[0], &nodes[1]};

  init_nodes(nodes, 2U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);

  mock_irq_reset();
  mock_primask_value = 5U;
  list_insert_tail(&head, &nodes[1].link);

  expect_irq_calls(1U, 5U);
  expect_list_order(&head, expected, 2U);
}

static void test_list_insert_node_after_inserts_in_middle(void)
{
  tListNode head;
  TestNode nodes[3];
  TestNode *expected[] = {&nodes[0], &nodes[2], &nodes[1]};

  init_nodes(nodes, 3U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);

  mock_irq_reset();
  mock_primask_value = 4U;
  list_insert_node_after(&nodes[2].link, &nodes[0].link);

  expect_irq_calls(1U, 4U);
  expect_list_order(&head, expected, 3U);
}

static void test_list_insert_node_before_inserts_in_middle(void)
{
  tListNode head;
  TestNode nodes[3];
  TestNode *expected[] = {&nodes[0], &nodes[2], &nodes[1]};

  init_nodes(nodes, 3U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);

  mock_irq_reset();
  mock_primask_value = 6U;
  list_insert_node_before(&nodes[2].link, &nodes[1].link);

  expect_irq_calls(1U, 6U);
  expect_list_order(&head, expected, 3U);
}

static void test_list_remove_node_updates_neighbors(void)
{
  tListNode head;
  TestNode nodes[3];
  TestNode *expected[] = {&nodes[0], &nodes[2]};

  init_nodes(nodes, 3U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);
  list_insert_tail(&head, &nodes[2].link);

  mock_irq_reset();
  mock_primask_value = 8U;
  list_remove_node(&nodes[1].link);

  expect_irq_calls(1U, 8U);
  expect_list_order(&head, expected, 2U);
  EXPECT_EQ_PTR(&nodes[2].link, nodes[0].link.next);
  EXPECT_EQ_PTR(&nodes[0].link, nodes[2].link.prev);
}

static void test_list_remove_head_returns_first_and_detaches_it(void)
{
  tListNode head;
  TestNode nodes[3];
  TestNode *expected[] = {&nodes[1], &nodes[2]};
  tListNode *removed = NULL;

  init_nodes(nodes, 3U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);
  list_insert_tail(&head, &nodes[2].link);

  mock_irq_reset();
  mock_primask_value = 11U;
  list_remove_head(&head, &removed);

  expect_irq_calls(2U, 11U);
  EXPECT_EQ_PTR(&nodes[0].link, removed);
  EXPECT_EQ_PTR(NULL, removed->next);
  EXPECT_EQ_PTR(NULL, removed->prev);
  expect_list_order(&head, expected, 2U);
}

static void test_list_remove_tail_returns_last_and_detaches_it(void)
{
  tListNode head;
  TestNode nodes[3];
  TestNode *expected[] = {&nodes[0], &nodes[1]};
  tListNode *removed = NULL;

  init_nodes(nodes, 3U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);
  list_insert_tail(&head, &nodes[2].link);

  mock_irq_reset();
  mock_primask_value = 10U;
  list_remove_tail(&head, &removed);

  expect_irq_calls(2U, 10U);
  EXPECT_EQ_PTR(&nodes[2].link, removed);
  EXPECT_EQ_PTR(NULL, removed->next);
  EXPECT_EQ_PTR(NULL, removed->prev);
  expect_list_order(&head, expected, 2U);
}

static void test_list_get_size_tracks_number_of_nodes(void)
{
  tListNode head;
  TestNode nodes[3];

  init_nodes(nodes, 3U);
  list_init_head(&head);

  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);
  list_insert_tail(&head, &nodes[2].link);

  mock_irq_reset();
  mock_primask_value = 12U;
  EXPECT_EQ_INT(3, list_get_size(&head));
  expect_irq_calls(1U, 12U);

  list_remove_node(&nodes[1].link);

  mock_irq_reset();
  mock_primask_value = 13U;
  EXPECT_EQ_INT(2, list_get_size(&head));
  expect_irq_calls(1U, 13U);
}

static void test_list_get_next_and_prev_follow_links(void)
{
  tListNode head;
  TestNode nodes[2];
  tListNode *node = NULL;

  init_nodes(nodes, 2U);
  list_init_head(&head);
  list_insert_tail(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[1].link);

  mock_irq_reset();
  mock_primask_value = 1U;
  list_get_next_node(&nodes[0].link, &node);
  EXPECT_EQ_PTR(&nodes[1].link, node);
  expect_irq_calls(1U, 1U);

  mock_irq_reset();
  mock_primask_value = 2U;
  list_get_prev_node(&nodes[0].link, &node);
  EXPECT_EQ_PTR(&head, node);
  expect_irq_calls(1U, 2U);

  mock_irq_reset();
  mock_primask_value = 14U;
  list_get_prev_node(&head, &node);
  EXPECT_EQ_PTR(&nodes[1].link, node);
  expect_irq_calls(1U, 14U);
}

static void test_list_mixed_operations_preserve_circular_links(void)
{
  tListNode head;
  TestNode nodes[4];
  TestNode *expected[] = {&nodes[1], &nodes[3], &nodes[2]};

  init_nodes(nodes, 4U);
  list_init_head(&head);
  list_insert_head(&head, &nodes[0].link);
  list_insert_tail(&head, &nodes[2].link);
  list_insert_node_after(&nodes[1].link, &head);
  list_insert_node_before(&nodes[3].link, &nodes[2].link);
  list_remove_node(&nodes[0].link);

  expect_list_order(&head, expected, 3U);
  EXPECT_EQ_INT(3, list_get_size(&head));
}

static void configure_hci_response(uint8_t status, uint16_t hci_revision,
                                   uint16_t lmp_pal_subversion)
{
  mock_hci_status = status;
  mock_hci_version = 0x08U;
  mock_hci_revision = hci_revision;
  mock_lmp_pal_version = 0x08U;
  mock_manufacturer_name = 0x0030U;
  mock_lmp_pal_subversion = lmp_pal_subversion;
}

static void test_getBlueNRGVersion_parses_major_minor_patch_fields(void)
{
  uint8_t hw_version = 0U;
  uint16_t fw_version = 0U;

  configure_hci_response(BLE_STATUS_SUCCESS, 0x31A2U, 0x00BCU);

  EXPECT_EQ_INT(BLE_STATUS_SUCCESS, getBlueNRGVersion(&hw_version, &fw_version));
  EXPECT_EQ_INT(1U, mock_hci_call_count);
  EXPECT_EQ_INT(0x31U, hw_version);
  EXPECT_EQ_INT(0xA2BCU, fw_version);
}

static void test_getBlueNRGVersion_handles_zero_version_values(void)
{
  uint8_t hw_version = 0xFFU;
  uint16_t fw_version = 0xFFFFU;

  configure_hci_response(BLE_STATUS_SUCCESS, 0x0000U, 0x0000U);

  EXPECT_EQ_INT(BLE_STATUS_SUCCESS, getBlueNRGVersion(&hw_version, &fw_version));
  EXPECT_EQ_INT(0x00U, hw_version);
  EXPECT_EQ_INT(0x0000U, fw_version);
}

static void test_getBlueNRGVersion_handles_full_minor_and_patch_nibbles(void)
{
  uint8_t hw_version = 0U;
  uint16_t fw_version = 0U;

  configure_hci_response(BLE_STATUS_SUCCESS, 0x12FFU, 0x00FFU);

  EXPECT_EQ_INT(BLE_STATUS_SUCCESS, getBlueNRGVersion(&hw_version, &fw_version));
  EXPECT_EQ_INT(0x12U, hw_version);
  EXPECT_EQ_INT(0xFFFFU, fw_version);
}

static void test_getBlueNRGVersion_does_not_modify_outputs_on_failure(void)
{
  uint8_t hw_version = 0xAAU;
  uint16_t fw_version = 0x55AAU;

  configure_hci_response(0x42U, 0x31A2U, 0x00BCU);

  EXPECT_EQ_INT(0x42U, getBlueNRGVersion(&hw_version, &fw_version));
  EXPECT_EQ_INT(1U, mock_hci_call_count);
  EXPECT_EQ_INT(0xAAU, hw_version);
  EXPECT_EQ_INT(0x55AAU, fw_version);
}

int main(void)
{
  RUN_TEST(test_list_init_head_creates_empty_circular_list);
  RUN_TEST(test_list_is_empty_reports_state_changes);
  RUN_TEST(test_list_insert_head_places_new_node_first);
  RUN_TEST(test_list_insert_tail_places_new_node_last);
  RUN_TEST(test_list_insert_node_after_inserts_in_middle);
  RUN_TEST(test_list_insert_node_before_inserts_in_middle);
  RUN_TEST(test_list_remove_node_updates_neighbors);
  RUN_TEST(test_list_remove_head_returns_first_and_detaches_it);
  RUN_TEST(test_list_remove_tail_returns_last_and_detaches_it);
  RUN_TEST(test_list_get_size_tracks_number_of_nodes);
  RUN_TEST(test_list_get_next_and_prev_follow_links);
  RUN_TEST(test_list_mixed_operations_preserve_circular_links);
  RUN_TEST(test_getBlueNRGVersion_parses_major_minor_patch_fields);
  RUN_TEST(test_getBlueNRGVersion_handles_zero_version_values);
  RUN_TEST(test_getBlueNRGVersion_handles_full_minor_and_patch_nibbles);
  RUN_TEST(test_getBlueNRGVersion_does_not_modify_outputs_on_failure);

  if (tests_failed != 0) {
    fprintf(stderr, "%d of %d tests failed\n", tests_failed, tests_run);
    return EXIT_FAILURE;
  }

  printf("All %d tests passed\n", tests_run);
  return EXIT_SUCCESS;
}
