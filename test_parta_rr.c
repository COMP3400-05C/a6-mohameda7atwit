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
void test_rr_tq4_5(void) {
    // When
    procs = init_procs((int[]){5}, 1);
    TEST_ASSERT_NOT_NULL(procs);
    int total_time = rr_run(procs, 1, 4);

    // Then
    TEST_ASSERT_EQUAL_INT(5, total_time);
    TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[0].wait);

    // Freed in tearDown above
}
void test_rr_tq4_58(void) {
    // When
    procs = init_procs((int[]){5, 8}, 2);
    TEST_ASSERT_NOT_NULL(procs);
    int total_time = rr_run(procs, 2, 4);

    // Then
    TEST_ASSERT_EQUAL_INT(13, total_time);
    TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(4, procs[0].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[1].burst_left);
    TEST_ASSERT_EQUAL_INT(5, procs[1].wait);
}
void test_rr_tq4_582(void) {
    // When
    procs = init_procs((int[]){5, 8, 2}, 3);
    TEST_ASSERT_NOT_NULL(procs);
    int total_time = rr_run(procs, 3, 4);

    // Then
    TEST_ASSERT_EQUAL_INT(15, total_time);
    TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(6, procs[0].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[1].burst_left);
    TEST_ASSERT_EQUAL_INT(7, procs[1].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[2].burst_left);
    TEST_ASSERT_EQUAL_INT(8, procs[2].wait);

    // Freed in tearDown above
}

void test_rr_tq2_5(void) {
    // When
    procs = init_procs((int[]){ 5 }, 1);
    TEST_ASSERT_NOT_NULL(procs);
    int total_time = rr_run(procs, 1, 2);

    // Then
    TEST_ASSERT_EQUAL_INT(5, total_time);
    TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(0, procs[0].wait);

    // Freed in tearDown above
}
void test_rr_tq2_58(void) {
    // When
    procs = init_procs((int[]){ 5, 8 }, 2);
    TEST_ASSERT_NOT_NULL(procs);
    int total_time = rr_run(procs, 2, 2);

    // Then
    TEST_ASSERT_EQUAL_INT(13, total_time);
    TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(4, procs[0].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[1].burst_left);
    TEST_ASSERT_EQUAL_INT(5, procs[1].wait);

    // Freed in tearDown above
}
void test_rr_tq2_582(void) {
    // When
    procs = init_procs((int[]){5, 8, 2}, 3);
    TEST_ASSERT_NOT_NULL(procs);
    int total_time = rr_run(procs, 3, 2);

    // Then
    TEST_ASSERT_EQUAL_INT(15, total_time);
    TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
    TEST_ASSERT_EQUAL_INT(6, procs[0].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[1].burst_left);
    TEST_ASSERT_EQUAL_INT(7, procs[1].wait);
    TEST_ASSERT_EQUAL_INT(0, procs[2].burst_left);
    TEST_ASSERT_EQUAL_INT(4, procs[2].wait);

    // Freed in tearDown above
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_rr_tq4_5);
    RUN_TEST(test_rr_tq4_58);
    RUN_TEST(test_rr_tq4_582);
    RUN_TEST(test_rr_tq2_5);
    RUN_TEST(test_rr_tq2_58);
    RUN_TEST(test_rr_tq2_582);

    return UNITY_END();
}

