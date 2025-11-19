#include "unity.h"  // For Unity Unit Tests
#include "parta.h"
#include <stdlib.h> // For malloc/free

static struct pcb* procs = NULL;

void setUp(void) {
    // Code to execute at test start up
    procs = NULL;
}
void tearDown(void) {
    // Code to execute at test conclusion
    free(procs);
}

void test_init5(void) {
    // When
    procs = init_procs((int[]){5}, 1);

    // Then
    TEST_ASSERT_NOT_NULL(procs);
    TEST_ASSERT_EQUAL_INT(0, procs[0].pid);
    TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[0].wait);

    // Freed in tearDown above
}
void test_init8(void) {
    // When
    procs = init_procs((int[]){8}, 1);

    // Then
    TEST_ASSERT_NOT_NULL(procs);
    TEST_ASSERT_EQUAL_INT(0, procs[0].pid);
    TEST_ASSERT_EQUAL_INT(8, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[0].wait);

    // Freed in tearDown above
}
void test_init58(void) {
    // When
    procs = init_procs((int[]){5, 8}, 2);

    // Then
    TEST_ASSERT_NOT_NULL(procs);
    TEST_ASSERT_EQUAL_INT(0, procs[0].pid);
    TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
    TEST_ASSERT_EQUAL_INT(1, procs[1].pid);
    TEST_ASSERT_EQUAL_INT(8, procs[1].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[1].wait);

    // Freed in tearDown above
}
void test_init582(void) {
    // When
    procs = init_procs((int[]){5, 8, 2}, 3);

    // Then
    TEST_ASSERT_NOT_NULL(procs);
    TEST_ASSERT_EQUAL_INT(0, procs[0].pid);
    TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
    TEST_ASSERT_EQUAL_INT(1, procs[1].pid);
    TEST_ASSERT_EQUAL_INT(8, procs[1].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[1].wait);
    TEST_ASSERT_EQUAL_INT(2, procs[2].burst_left);
    TEST_ASSERT_EQUAL_INT(2, procs[2].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[2].wait);

    // Freed in tearDown above
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_init5);
    RUN_TEST(test_init8);
    RUN_TEST(test_init58);

    return UNITY_END();
}

