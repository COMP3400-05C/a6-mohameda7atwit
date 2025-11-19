#include "unity.h"  // For Unity Unit Tests
#include "parta.h"
#include <stdlib.h> // For malloc/free

void setUp(void) {
    // Code to execute at test start up (currently empty)
}
void tearDown(void) {
    // Code to execute at test conclusion (currently empty)
}
void test_rr_all_done(void) {
    // Set up PCBs [0]
    {
        struct pcb procs[] = { { 0, 0, 0 } };
        TEST_ASSERT_EQUAL_INT(-1, rr_next(0, procs, 1));
    }
    // Set up PCBs [0, 0] current 0
    {
        struct pcb procs[] = { { 0, 0, 0 } };
        TEST_ASSERT_EQUAL_INT(-1, rr_next(0, procs, 1));
    }
    // Set up PCBs [0, 0] current 1
    {
        struct pcb procs[] = { { 0, 0, 0 } };
        TEST_ASSERT_EQUAL_INT(-1, rr_next(1, procs, 1));
    }
    // Set up PCBs [0, 0] current 1
    {
        struct pcb procs[] = { { 0, 0, 0 } };
        TEST_ASSERT_EQUAL_INT(-1, rr_next(1, procs, 1));
    }
}
void test_rr_next(void) {
    // Set up PCBs [2] current 0
    {
        struct pcb procs[] = { { 0, 2, 0 } };
        TEST_ASSERT_EQUAL_INT(0, rr_next(0, procs, 1));
    }

    // Set up PCBs [0,3] current 0
    {
        struct pcb procs[] = { { 0, 0, 0 }, { 1, 3, 0} };
        TEST_ASSERT_EQUAL_INT(1, rr_next(0, procs, 2));
    }

    // Set up PCBs [0,3] current 1
    {
        struct pcb procs[] = { { 0, 0, 0 }, { 1, 3, 0} };
        TEST_ASSERT_EQUAL_INT(1, rr_next(1, procs, 2));
    }

    // Set up PCBs [2,3] current 0
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 3, 0} };
        TEST_ASSERT_EQUAL_INT(1, rr_next(0, procs, 2));
    }

    // Set up PCBs [2,3] current 1
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 3, 0} };
        TEST_ASSERT_EQUAL_INT(0, rr_next(1, procs, 2));
    }

    // Set up PCBs [2,3,4] current 0
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 3, 0}, {2, 4, 0} };
        TEST_ASSERT_EQUAL_INT(1, rr_next(0, procs, 3));
    }

    // Set up PCBs [2,3,4] current 1
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 3, 0}, {2, 4, 0} };
        TEST_ASSERT_EQUAL_INT(2, rr_next(1, procs, 3));
    }

    // Set up PCBs [2,3,4] current 2
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 3, 0}, {2, 4, 0} };
        TEST_ASSERT_EQUAL_INT(0, rr_next(2, procs, 3));
    }

    // Set up PCBs [2,0,4] current 0
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 0, 0}, {2, 4, 0} };
        TEST_ASSERT_EQUAL_INT(2, rr_next(0, procs, 3));
    }

    // Set up PCBs [2,0,4] current 1
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 0, 0}, {2, 4, 0} };
        TEST_ASSERT_EQUAL_INT(2, rr_next(1, procs, 3));
    }

    // Set up PCBs [2,0,4] current 2
    {
        struct pcb procs[] = { { 0, 2, 0 }, { 1, 0, 0}, {2, 4, 0} };
        TEST_ASSERT_EQUAL_INT(0, rr_next(2, procs, 3));
    }

}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_rr_all_done);
    RUN_TEST(test_rr_next);

    return UNITY_END();
}

