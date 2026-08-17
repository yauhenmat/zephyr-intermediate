#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_T_LOW 7
#define PRIO_T_MED 5
#define PRIO_T_HIGH 3
#define PRIO_T_COOP (-1)

void thread_t_low_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_LOW running");
        k_msleep(300);
    }
}

void thread_t_med_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_MED running");
        k_msleep(200);
    }
}

void thread_t_high_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("T_HIGH running");
        k_msleep(100);
    }
}

void thread_t_coop_fn(void *p1, void *p2, void *p3)
{
    LOG_INF("COOP starting");
    for(int i = 0; i < 5; i++) {
        k_busy_wait(40000);
        LOG_INF("COOP step %d - still holding CPU", i + 1);
    }
    LOG_INF("COOP yielding now");
    k_yield();
    LOG_INF("COOP done");
}

K_THREAD_DEFINE(thread_low, STACK_SIZE, thread_t_low_fn,
                NULL, NULL, NULL, PRIO_T_LOW, 0, 0);
K_THREAD_DEFINE(thread_med, STACK_SIZE, thread_t_med_fn,
                NULL, NULL, NULL, PRIO_T_MED, 0, 0);
K_THREAD_DEFINE(thread_high, STACK_SIZE, thread_t_high_fn,
                NULL, NULL, NULL, PRIO_T_HIGH, 0, 0);
K_THREAD_DEFINE(thread_coop, STACK_SIZE, thread_t_coop_fn,
                NULL, NULL, NULL, PRIO_T_COOP, 0, 0);

int main(void)
{
    LOG_INF("=== l1-task1: Thread Interleaving ===");
    return 0;
}

