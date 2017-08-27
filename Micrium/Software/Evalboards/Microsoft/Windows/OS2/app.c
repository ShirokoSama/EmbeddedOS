/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          APPLICATION CODE
*
*                                          Microsoft Windows
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JJL
*                 FGK
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           TASK_STK_SIZE
*********************************************************************************************************
*/

#define          TASK_STK_SIZE     512

/*
*********************************************************************************************************
*                                            TASK_PRIO_DEFINE
*********************************************************************************************************
*/

#define TASK_1_PRIO		21
#define TASK_2_PRIO		22

/*
*********************************************************************************************************
*                                            TASK_ID_DEFINE
*********************************************************************************************************
*/

#define TASK_1_ID		1
#define TASK_2_ID		2

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];

OS_STK TASK1STK[TASK_STK_SIZE];
OS_STK TASK2STK[TASK_STK_SIZE];

//ddl,start,c,p,remain
edf_tcb_ext edf_exts[] =
{
	{ 4,1,1,3,1, 0 },
	{ 6,1, 3,5,3, 0 },
};

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart(void  *p_arg);

static void task1(void* pdata);
static void task2(void* pdata);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main (void)
{
    OSInit();                                                   /* Init uC/OS-II.                                       */

    //OSTaskCreateExt((void(*)(void *))AppTaskStart,              /* Create the start task                                */
    //    (void          *) 0,
    //    (OS_STK        *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
    //    (INT8U          ) APP_TASK_START_PRIO,
    //    (INT16U         ) APP_TASK_START_PRIO,
    //    (OS_STK        *)&AppTaskStartStk[0],
    //    (INT32U         ) APP_TASK_START_STK_SIZE,
    //    (void          *) 0,
    //    (INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskCreateExt((void(*)(void *))task1,
		(void          *)0,
		(OS_STK		   *)&TASK1STK[TASK_STK_SIZE - 1],
		(INT8U)TASK_1_PRIO,
		(INT16U)TASK_1_ID,
		(OS_STK        *)&TASK1STK[0],
		(INT32U)TASK_STK_SIZE,
		(void          *)&edf_exts[0],
		(INT16U)0);

	OSTaskCreateExt((void(*)(void *))task2,
		(void          *)0,
		(OS_STK		   *)&TASK2STK[TASK_STK_SIZE - 1],
		(INT8U)TASK_2_PRIO,
		(INT16U)TASK_2_ID,
		(OS_STK        *)&TASK2STK[0],
		(INT32U)TASK_STK_SIZE,
		(void          *)&edf_exts[1],
		(INT16U)0);

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg       is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

//static  void  AppTaskStart (void *p_arg)
//{
//    OS_ERR  err;
//
//
//   (void)p_arg;
//
//    BSP_Init();                                                 /* Initialize BSP functions                             */
//    CPU_Init();                                                 /* Initialize uC/CPU services                           */
//
//#if OS_CFG_STAT_TASK_EN > 0u
//    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
//#endif
//
//    APP_TRACE_DBG(("uCOS-II is Running...\n\r"));
//
//    while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
//        OSTimeDlyHMSM(0, 0, 1, 0);
//
//        APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet(&err)));
//    }
//}

static void task1(void *pdata) {
	//INT32U start;
	//INT32U end;
	//INT32U to_delay;
	////BSP_Init();
	////CPU_Init();
	//OSTimeDly(10);
	//start = 0;
	while(1) {
		while (((edf_tcb_ext*)OSTCBCur->OSTCBExtPtr)->is_task_complete==0) {
			//donothing
		}
		OS_ENTER_CRITICAL();
		//APP_TRACE("\nthis is task1");
		OS_EXIT_CRITICAL();
		OSTimeDly(((edf_tcb_ext*)OSTCBCur->OSTCBExtPtr)->start - OSTimeGet());
	}
}

static void task2(void* pdata) {
	//INT32U start;
	//INT32U end;
	//INT32U to_delay;
	////BSP_Init();
	////CPU_Init();
	//start = 0;
	//OSTimeDly(1);
	while(1) {
		while (((edf_tcb_ext*)OSTCBCur->OSTCBExtPtr)->is_task_complete == 0) {
			//do nothing
		}
		OS_ENTER_CRITICAL();
		//APP_TRACE("\nthis is task2");
		OS_EXIT_CRITICAL();
		OSTimeDly(((edf_tcb_ext*)OSTCBCur->OSTCBExtPtr)->start - OSTimeGet());
	}
}
