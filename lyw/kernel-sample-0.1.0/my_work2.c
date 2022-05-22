#include <rtthread.h>
#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        10


#define THREAD_PRIORITY1       6
#define THREAD_TIMESLICE1      5

static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid3 = RT_NULL;

//模拟按键的定时器
static rt_timer_t timer;
static void timeout(void *parameter)
{
    rt_kprintf("关闭线程3 \n");
		rt_thread_delete(tid3);
		

    
		rt_timer_stop(timer);
    
}

/****************************************************信号量相关控制***********************************************************/
/* 定义最大5个元素能够被产生 */
#define MAXSEM 5

/* 用于放置生产的整数数组 */
rt_uint32_t array[MAXSEM];

/* 指向生产者、消费者在array数组中的读写位置 */
static rt_uint32_t set, get;

/* 指向线程控制块的指针 */
static rt_thread_t producer_tid = RT_NULL;
static rt_thread_t consumer_tid = RT_NULL;

struct rt_semaphore sem_lock;
struct rt_semaphore sem_empty, sem_full;







/*********************************************控制流水灯的线程入口函数***************************************/
/*******************************************************************************************************/
/* 线程1的入口函数 */
static void thread1_entry(void *parameter)
{
   int cnt1 = 0;

    /* 运行10次 */
    while (cnt1 < 10)
    {
				
        /* 获取一个空位 */
        rt_sem_take(&sem_empty, RT_WAITING_FOREVER);
			rt_kprintf("流水灯效果1\n");

        /* 修改array内容，上锁 */
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        array[set % MAXSEM] = cnt1 + 1;
        rt_kprintf("the thread1 generates a number: %d\n", array[set % MAXSEM]);
        set++;
        rt_sem_release(&sem_lock);

        /* 发布一个满位 */
        rt_sem_release(&sem_full);
        cnt1++;

        /* 暂停一段时间 */
        rt_thread_mdelay(20);
    }

    rt_kprintf("the thread1 exit!\n");

}

ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
static struct rt_thread thread2;
/* 线程2入口函数 */
static void thread2_entry(void *param)
{
    rt_uint32_t count2 = 0;

   rt_uint32_t sum = 0;

    while (1)
    {
			
         
    

        /* 获取一个满位 */
        rt_sem_take(&sem_full, RT_WAITING_FOREVER);
			rt_kprintf("流水灯效果2\n");

        /* 临界区，上锁进行操作 */
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        sum += array[get % MAXSEM];
        rt_kprintf("the consumer[%d] get a number: %d\n", (get % MAXSEM), array[get % MAXSEM]);
        get++;
        rt_sem_release(&sem_lock);

        /* 释放一个空位 */
        rt_sem_release(&sem_empty);

        /* 生产到10个数目，停止，线程1相应停止 */
        if (get == 10) break;

        /* 暂停一小会时间 */
        rt_thread_mdelay(20);
    }

    
    rt_kprintf("the thread2 exit!\n");
    
}

/* 线程3的入口函数 */
static void thread3_entry(void *parameter)
{
  

     rt_uint32_t count3 = 0;

   
    for (count3 = 0; count3 < 10 ; count3++)
    {
        
        
				 rt_kprintf("流水灯效果3\n");
    }
		rt_kprintf("thread3 exit\n");
}

ALIGN(RT_ALIGN_SIZE)
static char thread4_stack[1024];
static struct rt_thread thread4;
/* 线程4入口函数 */
static void thread4_entry(void *param)
{
    rt_uint32_t count4 = 0;

   
    for (count4 = 0; count4 < 10 ; count4++)
    {
        
        rt_kprintf("流水灯效果4\n");
    }
    rt_kprintf("thread4 exit\n");
   
}


int my_work(void)
{
		set = 0;
    get = 0;

    /* 初始化3个信号量 */
    rt_sem_init(&sem_lock, "lock",     1,      RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_empty, "empty",   MAXSEM, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_full, "full",     0,      RT_IPC_FLAG_FIFO);

	
	
	
    /* 创建线程1，名称是thread1，入口是thread1_entry*/
    tid1 = rt_thread_create("thread1",
                            thread1_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY-2, THREAD_TIMESLICE);
    
    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* 初始化线程2，名称是thread2，入口是thread2_entry */
    rt_thread_init(&thread2,
                   "thread2",
                   thread2_entry,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread2);
	
		 /* 创建线程3，名称是thread3，入口是thread3_entry*/
    tid3 = rt_thread_create("thread3",
                            thread3_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    
    /* 如果获得线程控制块，启动这个线程 */
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);
		timer = rt_timer_create("timer", timeout,
                             RT_NULL, 1,
                            RT_TIMER_FLAG_ONE_SHOT);
    /* 启动定时器 */
    if (timer != RT_NULL) rt_timer_start(timer);
    
    /* 初始化线程4，名称是thread4，入口是thread4_entry */
    rt_thread_init(&thread4,
                   "thread4",
                   thread4_entry,
                   RT_NULL,
                   &thread4_stack[0],
                   sizeof(thread4_stack),
                   THREAD_PRIORITY + 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread4);
									 


//    

    return 0;
}


/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(my_work, my_work);
