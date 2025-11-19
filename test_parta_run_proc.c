#include "unity.h"  // For Unity Unit Tests
#include "parta.h"
#include <stdlib.h> // For malloc/free

void setUp(void) {
    // Code to execute at test start up (currently empty)
}
void tearDown(void) {
    // Code to execute at test conclusion (currently empty)
}
void test_run_proc(void) {
    // Set up PCBs [5] current 0, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 } };
        run_proc(procs, 1, 0, 2);
        TEST_ASSERT_EQUAL_INT(3, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
    }
    // Set up PCBs [5, 8] current 0, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 8, 0 } };
        run_proc(procs, 2, 0, 2);
        TEST_ASSERT_EQUAL_INT(3, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(8, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[1].wait);
    }
    // Set up PCBs [5, 8] current 1, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 8, 0 } };
        run_proc(procs, 2, 1, 2);
        TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(6, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[1].wait);
    }
}
void test_run_proc3(void) {
    // Set up PCBs [5, 8, 2] current 0, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 8, 0 }, { 2, 2, 0 } };
        run_proc(procs, 3, 0, 2);
        TEST_ASSERT_EQUAL_INT(3, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(8, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[1].wait);
        TEST_ASSERT_EQUAL_INT(2, procs[2].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[2].wait);
    }
    // Set up PCBs [5, 8, 2] current 1, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 8, 0 }, { 2, 2, 0 } };
        run_proc(procs, 3, 1, 2);
        TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(6, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[1].wait);
        TEST_ASSERT_EQUAL_INT(2, procs[2].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[2].wait);
    }
    // Set up PCBs [5, 8, 2] current 2, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 8, 0 }, { 2, 2, 0 } };
        run_proc(procs, 3, 2, 2);
        TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(8, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[1].wait);
        TEST_ASSERT_EQUAL_INT(0, procs[2].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[2].wait);
    }
}

void test_run_proc_somedone(void) {
    // Set up PCBs [5, 8, 0] current 0, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 8, 0 }, { 2, 0, 0 } };
        run_proc(procs, 3, 0, 2);
        TEST_ASSERT_EQUAL_INT(3, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(8, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[1].wait);
        TEST_ASSERT_EQUAL_INT(0, procs[2].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[2].wait);
    }
    // Set up PCBs [0, 8, 2] current 1, amount 2
    {
        struct pcb procs[] = { { 0, 0, 0 }, { 1, 8, 0 }, { 2, 2, 0 } };
        run_proc(procs, 3, 1, 2);
        TEST_ASSERT_EQUAL_INT(0, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(6, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[1].wait);
        TEST_ASSERT_EQUAL_INT(2, procs[2].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[2].wait);
    }
    // Set up PCBs [5, 0, 2] current 2, amount 2
    {
        struct pcb procs[] = { { 0, 5, 0 }, { 1, 0, 0 }, { 2, 2, 0 } };
        run_proc(procs, 3, 2, 2);
        TEST_ASSERT_EQUAL_INT(5, procs[0].burst_left);
        TEST_ASSERT_EQUAL_INT(2, procs[0].wait);
        TEST_ASSERT_EQUAL_INT(0, procs[1].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[1].wait);
        TEST_ASSERT_EQUAL_INT(0, procs[2].burst_left);
        TEST_ASSERT_EQUAL_INT(0, procs[2].wait);
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_run_proc);
    RUN_TEST(test_run_proc3);
    RUN_TEST(test_run_proc_somedone);

    return UNITY_END();
}

