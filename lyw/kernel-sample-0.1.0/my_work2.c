#include <rtthread.h>
#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        10


#define THREAD_PRIORITY1       6
#define THREAD_TIMESLICE1      5

static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid3 = RT_NULL;

//ģ�ⰴ���Ķ�ʱ��
static rt_timer_t timer;
static void timeout(void *parameter)
{
    rt_kprintf("�ر��߳�3 \n");
		rt_thread_delete(tid3);
		

    
		rt_timer_stop(timer);
    
}

/****************************************************�ź�����ؿ���***********************************************************/
/* �������5��Ԫ���ܹ������� */
#define MAXSEM 5

/* ���ڷ����������������� */
rt_uint32_t array[MAXSEM];

/* ָ�������ߡ���������array�����еĶ�дλ�� */
static rt_uint32_t set, get;

/* ָ���߳̿��ƿ��ָ�� */
static rt_thread_t producer_tid = RT_NULL;
static rt_thread_t consumer_tid = RT_NULL;

struct rt_semaphore sem_lock;
struct rt_semaphore sem_empty, sem_full;







/*********************************************������ˮ�Ƶ��߳���ں���***************************************/
/*******************************************************************************************************/
/* �߳�1����ں��� */
static void thread1_entry(void *parameter)
{
   int cnt1 = 0;

    /* ����10�� */
    while (cnt1 < 10)
    {
				
        /* ��ȡһ����λ */
        rt_sem_take(&sem_empty, RT_WAITING_FOREVER);
			rt_kprintf("��ˮ��Ч��1\n");

        /* �޸�array���ݣ����� */
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        array[set % MAXSEM] = cnt1 + 1;
        rt_kprintf("the thread1 generates a number: %d\n", array[set % MAXSEM]);
        set++;
        rt_sem_release(&sem_lock);

        /* ����һ����λ */
        rt_sem_release(&sem_full);
        cnt1++;

        /* ��ͣһ��ʱ�� */
        rt_thread_mdelay(20);
    }

    rt_kprintf("the thread1 exit!\n");

}

ALIGN(RT_ALIGN_SIZE)
static char thread2_stack[1024];
static struct rt_thread thread2;
/* �߳�2��ں��� */
static void thread2_entry(void *param)
{
    rt_uint32_t count2 = 0;

   rt_uint32_t sum = 0;

    while (1)
    {
			
         
    

        /* ��ȡһ����λ */
        rt_sem_take(&sem_full, RT_WAITING_FOREVER);
			rt_kprintf("��ˮ��Ч��2\n");

        /* �ٽ������������в��� */
        rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
        sum += array[get % MAXSEM];
        rt_kprintf("the consumer[%d] get a number: %d\n", (get % MAXSEM), array[get % MAXSEM]);
        get++;
        rt_sem_release(&sem_lock);

        /* �ͷ�һ����λ */
        rt_sem_release(&sem_empty);

        /* ������10����Ŀ��ֹͣ���߳�1��Ӧֹͣ */
        if (get == 10) break;

        /* ��ͣһС��ʱ�� */
        rt_thread_mdelay(20);
    }

    
    rt_kprintf("the thread2 exit!\n");
    
}

/* �߳�3����ں��� */
static void thread3_entry(void *parameter)
{
  

     rt_uint32_t count3 = 0;

   
    for (count3 = 0; count3 < 10 ; count3++)
    {
        
        
				 rt_kprintf("��ˮ��Ч��3\n");
    }
		rt_kprintf("thread3 exit\n");
}

ALIGN(RT_ALIGN_SIZE)
static char thread4_stack[1024];
static struct rt_thread thread4;
/* �߳�4��ں��� */
static void thread4_entry(void *param)
{
    rt_uint32_t count4 = 0;

   
    for (count4 = 0; count4 < 10 ; count4++)
    {
        
        rt_kprintf("��ˮ��Ч��4\n");
    }
    rt_kprintf("thread4 exit\n");
   
}


int my_work(void)
{
		set = 0;
    get = 0;

    /* ��ʼ��3���ź��� */
    rt_sem_init(&sem_lock, "lock",     1,      RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_empty, "empty",   MAXSEM, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_full, "full",     0,      RT_IPC_FLAG_FIFO);

	
	
	
    /* �����߳�1��������thread1�������thread1_entry*/
    tid1 = rt_thread_create("thread1",
                            thread1_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY-2, THREAD_TIMESLICE);
    
    /* �������߳̿��ƿ飬��������߳� */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* ��ʼ���߳�2��������thread2�������thread2_entry */
    rt_thread_init(&thread2,
                   "thread2",
                   thread2_entry,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread2);
	
		 /* �����߳�3��������thread3�������thread3_entry*/
    tid3 = rt_thread_create("thread3",
                            thread3_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);
    
    /* �������߳̿��ƿ飬��������߳� */
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);
		timer = rt_timer_create("timer", timeout,
                             RT_NULL, 1,
                            RT_TIMER_FLAG_ONE_SHOT);
    /* ������ʱ�� */
    if (timer != RT_NULL) rt_timer_start(timer);
    
    /* ��ʼ���߳�4��������thread4�������thread4_entry */
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


/* ������ msh �����б��� */
MSH_CMD_EXPORT(my_work, my_work);
