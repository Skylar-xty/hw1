//#include <rtthread.h>
//#define THREAD_PRIORITY         25
//#define THREAD_STACK_SIZE       512
//#define THREAD_TIMESLICE        10

//static rt_thread_t tid1 = RT_NULL;
//static rt_thread_t tid3 = RT_NULL;



///***********************************��ʱ�����**********************************************************/
///*******************************************************************************************************/
///* ��ʱ���Ŀ��ƿ� ����ģ�ⰴ��*/
//static rt_timer_t timer1;
//static rt_timer_t timer2;
//static rt_timer_t timer3;

///*���Ƶ�������ź�*/
//int sign1=1;
//int sign2=1;
//int sign3=1;
//int cnt1 =0;
//int cnt2 =0;
//int cnt3 =0;
///* ��ʱ��1��ʱ������������light1 */
//static void timeout1(void *parameter)
//{
//    rt_kprintf("��ת light1 \n");
//		sign1=-sign1;

//    /* ���е�4�Σ�ֹͣ���ڶ�ʱ�� */
//    if (cnt1++ >= 3)
//    {
//        rt_timer_stop(timer1);
//        rt_kprintf("button1 was stopped! \n");
//    }
//}
///* ��ʱ��1��ʱ������������light2 */
//static void timeout2(void *parameter)
//{
//    rt_kprintf("��ת light2\n ");
//		sign2=-sign2;

//    /* ���е�4�Σ�ֹͣ���ڶ�ʱ�� */
//    if (cnt2++ >= 3)
//    {
//        rt_timer_stop(timer2);
//        rt_kprintf("button2 was stopped! \n");
//    }
//}
///* ��ʱ��1��ʱ������������light3 */
//static void timeout3(void *parameter)
//{
//    rt_kprintf("��ת light3\n");
//		sign3=-sign3;

//    /* ���е�4�Σ�ֹͣ���ڶ�ʱ�� */
//    if (cnt3++ >= 3)
//    {
//        rt_timer_stop(timer3);
//        rt_kprintf("button3 was stopped! \n");
//    }
//}


///*********************************************���Ƶ�������߳���ں���***************************************/
///*******************************************************************************************************/
///* �߳�1����ں��� */
//static void thread1_entry(void *parameter)
//{
//  

//    while (1)
//    {
//        if(sign1==1){
//        rt_kprintf("light 1 is on\n");
//        rt_thread_mdelay(500);
//				rt_kprintf("light 1 is off\n");}
//				if(sign2==1){
//				rt_kprintf("light 2 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 2 is off\n\n");}
//				if(sign3==1){
//				rt_kprintf("light 3 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 3 is off\n");}
//    }
//}

//ALIGN(RT_ALIGN_SIZE)
//static char thread2_stack[1024];
//static struct rt_thread thread2;
///* �߳�2��ں��� */
//static void thread2_entry(void *param)
//{
//    rt_uint32_t count2 = 0;

//   
//    for (count2 = 0; count2 < 10 ; count2++)
//    {
//        if(sign3==1){
//        rt_kprintf("light 3 is on\n\n");
//        rt_thread_mdelay(500);
//				rt_kprintf("light 3 is off\n");}
//				if(sign2==1){
//				rt_kprintf("light 2 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 2 is off\n");}
//				if(sign1==1){
//				rt_kprintf("light 1 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 1 is off\n");}
//    }

//}

///* �߳�3����ں��� */
//static void thread3_entry(void *parameter)
//{
//  

//    while (1)
//    {
//        
//        
//				if(sign2==1){
//				rt_kprintf("light 2 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 2 is off\n");}
//				if(sign1==1){
//				rt_kprintf("light 1 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 1 is off\n");}
//				if(sign3==1){
//        rt_kprintf("light 3 is on\n");
//        rt_thread_mdelay(500);
//				rt_kprintf("light 3 is off\n");}
//    }
//}

//ALIGN(RT_ALIGN_SIZE)
//static char thread4_stack[1024];
//static struct rt_thread thread4;
///* �߳�4��ں��� */
//static void thread4_entry(void *param)
//{
//    rt_uint32_t count4 = 0;

//   
//    for (count4 = 0; count4 < 10 ; count4++)
//    {
//        
//        
//				if(sign1==1){
//				rt_kprintf("light 1 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 1 is off\n");}
//				if(sign3==1){
//        rt_kprintf("light 3 is on\n");
//        rt_thread_mdelay(500);
//				rt_kprintf("light 3 is off\n");}
//				if(sign2==1){
//				rt_kprintf("light 2 is on\n");
//				rt_thread_mdelay(500);
//				rt_kprintf("light 2 is off\n");}
//    }
//    rt_kprintf("thread4 exit\n");
//   
//}





/**********************************************�̵߳Ĵ���******************************************/
/*******************************************************************************************************/
//int my_work(void)
//{
//	/* ������ʱ��1  ���ڶ�ʱ�� */
//    timer1 = rt_timer_create("timer1", timeout1,
//                             RT_NULL, 10,
//                             RT_TIMER_FLAG_PERIODIC);
//	
//	/* ������ʱ��2  ���ڶ�ʱ�� */
//    timer2 = rt_timer_create("timer2", timeout2,
//                             RT_NULL, 20,
//                             RT_TIMER_FLAG_PERIODIC);
///* ������ʱ��3  ���ڶ�ʱ�� */
//    timer1 = rt_timer_create("timer3", timeout3,
//                             RT_NULL, 30,
//                             RT_TIMER_FLAG_PERIODIC);

//    /* �����߳�1��������thread1�������thread1_entry*/
//    tid1 = rt_thread_create("thread1",
//                            thread1_entry, RT_NULL,
//                            THREAD_STACK_SIZE,
//                            THREAD_PRIORITY-2, THREAD_TIMESLICE);
//    
//    /* �������߳̿��ƿ飬��������߳� */
//    if (tid1 != RT_NULL)
//        rt_thread_startup(tid1);

//    /* ��ʼ���߳�2��������thread2�������thread2_entry */
//    rt_thread_init(&thread2,
//                   "thread2",
//                   thread2_entry,
//                   RT_NULL,
//                   &thread2_stack[0],
//                   sizeof(thread2_stack),
//                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
//    rt_thread_startup(&thread2);
//									 
//		 /* �����߳�3��������thread3�������thread3_entry*/
//    tid3 = rt_thread_create("thread3",
//                            thread3_entry, RT_NULL,
//                            THREAD_STACK_SIZE,
//                            THREAD_PRIORITY, THREAD_TIMESLICE);
//    
//    /* �������߳̿��ƿ飬��������߳� */
//    if (tid3 != RT_NULL)
//        rt_thread_startup(tid3);

//    /* ��ʼ���߳�4��������thread4�������thread4_entry */
//    rt_thread_init(&thread4,
//                   "thread4",
//                   thread4_entry,
//                   RT_NULL,
//                   &thread4_stack[0],
//                   sizeof(thread4_stack),
//                   THREAD_PRIORITY + 1, THREAD_TIMESLICE);
//    rt_thread_startup(&thread4);
//									 

//    /* ������ʱ��1 */
//    if (timer1 != RT_NULL) rt_timer_start(timer1);


//    /* ������ʱ��2 */
//    if (timer1 != RT_NULL) rt_timer_start(timer2);
//									 
//		

//    /* ������ʱ��3 */
//    if (timer1 != RT_NULL) rt_timer_start(timer3);
//		

//    return 0;
//}

///* ������ msh �����б��� */
//MSH_CMD_EXPORT(my_work, my_work);