/**
 * @file    :   test_ringbuff.c
 *
 * @brief
 *
 * @author  :   L. Nicholson-Andrews (lewisnich01@outlook.com)
 * @date    :   02.11.2026
 */

/*======Includes======*/
#include <string.h>
#include <stdio.h>

#include "unity.h"
#include "ringbuff.h"
#include "status.h"

/*============Fakes==============*/
static ring_buff_t      rb;
static status_code_t    result;

/*============Variables==========*/


void setUp(void)
{
    /* Fill with garbage first so we know init really resets the state */
    memset(&rb, 0xFF, sizeof(rb));
    RingBuff_init(&rb);
}

void tearDown(void)
{

}

/*=============Helpers===========*/
static status_code_t fill(uint16_t n)
{
    for (uint16_t i = 0; i < n; i++)
    {
        result = RingBuff_Push(&rb, (uint8_t)i);
    }
    return result;
}


/*========Public Functions=======*/
/* ---------- init ---------- */
void test_init_resets_indices_and_count(void)
{
    TEST_ASSERT_EQUAL_INT(0, rb.head);
    TEST_ASSERT_EQUAL_INT(0, rb.tail);
    TEST_ASSERT_EQUAL_INT(0, rb.count);
}

void test_init_after_use_resets_state(void)
{
    fill(20);
    TEST_ASSERT_EQUAL_INT(20, rb.head);
    TEST_ASSERT_EQUAL_INT(0, rb.tail);
    TEST_ASSERT_EQUAL_INT(20, rb.count);
    
    
    RingBuff_init(&rb);
    TEST_ASSERT_EQUAL_INT(0, rb.head);
    TEST_ASSERT_EQUAL_INT(0, rb.tail);
    TEST_ASSERT_EQUAL_INT(0, rb.count);
}

/*-----------Push-------------*/
void test_push_single_returns_done(void)
{
    RingBuff_init(&rb);

    result = fill(1);
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_push_stores_byte_head(void)
{
    RingBuff_init(&rb);

    result = fill(3);

    TEST_ASSERT_EQUAL_INT(3, rb.head);
    TEST_ASSERT_EQUAL_INT(0, result);

}

void test_push_returnDone_untilFull(void)
{
    char msg[64];
    for (int i = 0; i < RING_BUFF; i++)
    {
        result = RingBuff_Push(&rb, (uint8_t)i);
        snprintf(msg, sizeof msg, "push #%d, count=%d", i, rb.count);
        TEST_ASSERT_EQUAL_INT_MESSAGE(DONE, result, msg);
    }
    TEST_ASSERT_EQUAL_INT(RING_BUFF, rb.count);
}

void test_pushFull_HeadWraps(void);

/*-----------Test Runner------*/
int main (void)
{
    UNITY_BEGIN();

    /*---Init---*/
    RUN_TEST(test_init_resets_indices_and_count);
    RUN_TEST(test_init_after_use_resets_state);
    
    /*---Push---*/
    RUN_TEST(test_push_single_returns_done);
    RUN_TEST(test_push_stores_byte_head);
    RUN_TEST(test_push_returnDone_untilFull);

    /*---Pop---*/
    
    return UNITY_END();
}