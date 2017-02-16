#include "song_timer.h"
void STime_Init(uint16_t period, uint16_t prescaler)
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



