#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "motor.h"
#include "CountSensor.h"
#include "Serial.h"
#include "Serial_2.h"
#include "fuwei.h"
#include "ESP8266.h"

uint8_t S_RxData;
uint16_t RxData[2];
uint8_t S_RxData1;
int a;
int kk;
int i;
int count,count1,count2;
int tingzhi1=0;
int tingzhi2=0;
extern uint16_t CountSensor1_Count;

int PWM_num1 = 0;
int PWM_num2 = 0;
int mai1 = 2;
int mai2 = 2;
int mubiao1=0;
int mubiao2=0;

 int main(void)
{	 	
	ESP8266_Huaweiyun_Init();				//华为云传值
//	TIM2_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先
	CountSensor1_Init();
	EXTI->IMR &= ~(EXTI_Line14);			//外部中断线14关闭，先关闭红外，等到电机到初始位置后再打开
	Motor_Init();	
	xw_Init();
	TIM3_PWM_Init(450-1,5-1);					//这个电机1的速度就不用改了
	TIM4_PWM_Init(2000-1,19-1);				//这个电机2你们可以改
	TIM_SetCompare3(TIM3,50);
	TIM_SetCompare1(TIM4,50);
	Motor1_disable();									//先失能
	Motor2_disable();
	TIM_CCxCmd(TIM3,TIM_Channel_3,ENABLE);		//打开TIM3通道3输出PWM
	TIM_CCxCmd(TIM4,TIM_Channel_1,ENABLE);		//打开TIM4通道1输出PWM
	Motor1_FAN();											//电机1回走，一直碰到限位开关，开局初始化
	Motor2_FAN();											//电机2回走

	Serial_Init(); 			//115200
	Serial_2_Init(); 			//115200
	
//	usart_esp8266();
	 while(1)
	 {

		 Serial_2_SendByte(count-1);
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==SET)				//电机1的限位开关
		{
			 PWM_num1=0;											
			 maichong1(10);										//电机1碰到限位开关后回弹一下
			EXTI->IMR |= EXTI_Line14;					//外部中断线14开启
		 }
		 
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==SET)				//电机2的限位开关
		{			
			 PWM_num2=0;
			 maichong2(1);										//电机2碰到限位开关后回弹一下
		 }
		 
		 
		 if(tingzhi1==1)										//让电机1停止，在定时器里的写法停不了，就写了个标志位到while里来判断，杰哥牛逼
		 {
				TIM_CCxCmd(TIM3,TIM_Channel_3,DISABLE);			 
		 }
		 
		 if(tingzhi2==1)										//让电机2停止
		 {
		   TIM_CCxCmd(TIM4,TIM_Channel_1,DISABLE);			 
		 }
		 
		 if(i==1)														//红外扫到				
		 {
			 if(a==1){printf("page2.tm1.en=1\xff\xff\xff");}			//串口屏进度条
			 EXTI->IMR &= ~(EXTI_Line14);			//外部中断线14关闭
			 
			 maichong1(250000);								//电机1出发的位置，值越大去的越远
			 maichong2(28000);								//电机2出发的位置，这个也是
				
			 Delay_ms(7812);                  //计算：450 * 5 / 72000000 * (250000-10) =7.812秒
		 
			 maichong1(10);										//电机1回来的位置
			 maichong2(1);										//电机2回来的位置
		
			 Delay_ms(7812+200);							//200为了电机回来的时候多走一点碰到限位开关
			 
/**这两个值在碰到限位开关后清零，这样才能进下一次红外，所以回来的时候多走200ms就是为了碰到限位开关**/
			 i=0;															
			 CountSensor1_Count=0;
			 
			 a=0;
			 printf("page2.t3.txt=\"%d\"\xff\xff\xff",count-1);
		 }	 
	 }		 
}		

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		S_RxData = USART_ReceiveData(USART3);
		if(S_RxData==01)
		{
			kk=1;
		}
		if(S_RxData==02)
		{
			kk=2;
		}
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}


void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		S_RxData1 = USART_ReceiveData(USART1);
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}


void TIM3_IRQHandler(void)   //自己debug一下看数值变化就看懂了
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{	
		count1++;
		if(mai1==1)
		{
			PWM_num1++;
			if(PWM_num1==mubiao1)
			{
				//TIM_CCxCmd(TIM3,TIM_Channel_3,DISABLE);		//关闭TIM3通道3输出PWM
				tingzhi1=1;
				mai1=2;
			}
		}
		if(mai1==0)
		{
			PWM_num1--;
			if(PWM_num1==mubiao1)
			{
        tingzhi1=1;
				//TIM_CCxCmd(TIM3,TIM_Channel_3,DISABLE);		//关闭TIM3通道3输出PWM
				mai1=2;
			}
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC3);
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
	}	
}

void TIM4_IRQHandler(void)				
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==RESET)
	{
		count2++;
		if(mai2==1)
		{
			PWM_num2++;
			if(PWM_num2==mubiao2)
			{
//				TIM_CCxCmd(TIM4,TIM_Channel_1,DISABLE);		//关闭TIM4通道1输出PWM
				tingzhi2=1;
				mai2=2;
			}
		}
		if(mai2==0)
		{
			PWM_num2--;
			if(PWM_num2==mubiao2)
			{
//				TIM_CCxCmd(TIM4,TIM_Channel_1,DISABLE);		//关闭TIM4通道1输出PWM
				tingzhi2=1;
				mai2=2;
			}
		}
		TIM_ClearITPendingBit(TIM4,TIM_IT_CC1);
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
	}
}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{ 
		a++;
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor1_Count++;
			if(CountSensor1_Count==1)
			{
				i=1;
				count++;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line14);
}
