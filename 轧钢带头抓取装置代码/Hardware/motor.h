#ifndef _MOTOR_H
#define _MOTOR_H

void TIM2_Init(void);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void Motor_Init(void);
void xw_Init(void);
void Motor1_ZHENG(void);           //电机1正转
void Motor1_FAN(void);          //电机1反转
void Motor2_ZHENG(void);          //电机2正转
void Motor2_FAN(void);          //电机2反转
void Motor1_enable(void);			// 电机1使能
void Motor1_disable(void);			// 电机1失能
void Motor2_enable(void);			// 电机2使能
void Motor2_disable(void);			// 电机2失能
void maichong1(int mb);
void maichong2(int mb);


#endif
