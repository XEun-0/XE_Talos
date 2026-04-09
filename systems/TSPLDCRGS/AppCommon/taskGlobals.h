#ifndef TASKGLOBALS_H
#define TASKGLOBALS_H

//========================================================
//=========== Delays =====================================
//========================================================
#define I_VERT_ACT_DELAY_8HZ                pdMS_TO_TICKS(125)
#define MAIN_CONTROLLER_TASK_DELAY_10HZ     pdMS_TO_TICKS(100)

#define TEN_SECONDS_DELAY                   pdMS_TO_TICKS(10000) 
#define FIVE_SECONDS_DELAY                  pdMS_TO_TICKS(5000) 
#define SYS_BAUD_RATE                       115200

//========================================================
//=========== Misc =======================================
//========================================================


//========================================================
//=========== Queues =====================================
//========================================================
extern QueueHandle_t gImuQueue;

#endif // TASKGLOBALS_H