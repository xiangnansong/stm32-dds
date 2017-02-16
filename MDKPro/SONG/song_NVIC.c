#include "song_NVIC.h" 

void NVIC_Configuration(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

}

void SongExitInit(void)
{
	NVIC_InitTypeDef SongNvic;
	GPIO_InitTypeDef SongGpio;
	GPIO_InitTypeDef SongLed;
	EXTI_InitTypeDef   SongExit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	SongGpio.GPIO_Mode = GPIO_Mode_IPU;
	SongGpio.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &SongGpio);

	SongLed.GPIO_Mode = GPIO_Mode_Out_PP;
	SongLed.GPIO_Pin = GPIO_Pin_0;
	SongLed.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &SongLed);
	
	SongNvic.NVIC_IRQChannel = EXTI0_IRQn;
	SongNvic.NVIC_IRQChannelCmd = ENABLE;
	SongNvic.NVIC_IRQChannelPreemptionPriority = 0x03;
	SongNvic.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_Init(&SongNvic);

	SongExit.EXTI_Line = EXTI_Line0;
	SongExit.EXTI_LineCmd = ENABLE;
	SongExit.EXTI_Mode = EXTI_Mode_Interrupt;
	SongExit.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&SongExit);
}

void EXTI0_IRQHandler(void)
{
	if (PBout(0) == 0)
	{
		PBout(0) = 1;
	}
	else if (PBout(0) == 1)
	{
		PBout(0) = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void SongTimeExit(uint16_t period, uint16_t prescaler)
{
	TIM_TimeBaseInitTypeDef time;
	NVIC_InitTypeDef nvic;
	GPIO_InitTypeDef gpio;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);

	time.TIM_Period = period;
	time.TIM_Prescaler = prescaler;
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &time);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	nvic.NVIC_IRQChannel = TIM3_IRQn;
	nvic.NVIC_IRQChannelSubPriority = 0x03;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x03;
	nvic.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvic);

	TIM_Cmd(TIM3, ENABLE);
	
}

