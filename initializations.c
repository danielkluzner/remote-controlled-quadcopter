







/*This will be used to initialize PortA pins 0-3
  Port A pin x will be used to send PWM signals to Motor(x +1)
	ex: pin 0 corresponds to motor (0 + 1) = motor 1
	
	pin setup
	AF2 
	TIM2 CH1 to CH4
	
	default clock frequency is 4Mhz
	
	
*/

#include "stm32l476xx.h"

void clock_inits(){
	//port A clock in it
	//port A used for onboard joystick, interrupts, and PWM pins
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	//PWM clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;


}

void pwm_init() {
	
	// Configure PE13
	GPIOE->MODER |= GPIO_MODER_MODE13_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE13_0;
	
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD13;
	
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL13;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL13_0;
	// Configure PE14
	GPIOE->MODER |= GPIO_MODER_MODE14_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE14_0;
	
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED14;
	
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD14;
	
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL14;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL14_0;
	
	
	// Configure PWM Output for TIM1 CH 1N
	TIM1->CR1 &= ~TIM_CR1_DIR;
	TIM1->PSC = 3;
	TIM1->ARR = 1999;
	
	TIM1->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM1->CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM1->CCMR2 |= TIM_CCMR2_OC3M_2;
	TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
	
	TIM1->CCMR2 &= ~TIM_CCMR2_OC4M;
	TIM1->CCMR2 |= TIM_CCMR2_OC4M_1;
	TIM1->CCMR2 |= TIM_CCMR2_OC4M_2;
	TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
	
	TIM1->CCER &= ~TIM_CCER_CC3P;
	TIM1->CCER &= ~TIM_CCER_CC4P;
	
	TIM1->CCER |= TIM_CCER_CC3E;
	TIM1->CCER |= TIM_CCER_CC4E;
	
	TIM1->BDTR |= TIM_BDTR_MOE;
	
	//TIM1->CCR1 = 125;
	TIM1->CCR3 = 170;
	TIM1->CCR4 = 170;
	//TIM1->CCR4 = 125;
	
	TIM1->CR1 |= TIM_CR1_CEN;

	
	// Configure PA0-3 for alternate function mode (10)
//	GPIOA->MODER |= GPIO_MODER_MODE0_1;
//	GPIOA->MODER &= ~GPIO_MODER_MODE0_0;
	
	GPIOA->MODER |= GPIO_MODER_MODE1_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_0;
	
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE2_0;
	
//	GPIOA->MODER |= GPIO_MODER_MODE3_1;
//	GPIOA->MODER &= ~GPIO_MODER_MODE3_0;

	//ospeed to very high (11)
		
//	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2;
//	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
	
	//no pull up pull down
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2;
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;
	
	//select AF1 for TIM2
//	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL0;
//	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL0_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_0;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_0;
//	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3;
//	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3_0;
		
	// Configure PWM Output for TIM1 CH 1
	//default 4MHz clock
	TIM2->CR1 &= ~TIM_CR1_DIR;
	TIM2->PSC = 3; //frequency = 4MHz / (PSC + 1) = 1MHz
	TIM2->ARR = 1999; //# steps before reload -> 
	
	//set output compare mode to PWM mode 1 (0110)
	//channel active while TIM2_CNT < TIM2_CCR1
	//channel 1
//	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
//	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;
//	TIM2->CCMR1 |= TIM_CCMR1_OC1M_2;
	//channel 2
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_1;
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_2;
	//channel 3
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_1;
	TIM2->CCMR2 |= TIM_CCMR2_OC3M_2;
	//channel 4
//	TIM2->CCMR2 &= ~TIM_CCMR2_OC4M;
//	TIM2->CCMR2 |= TIM_CCMR2_OC4M_1;
//	TIM2->CCMR2 |= TIM_CCMR2_OC4M_2;
	
	//preload enable
//	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
	TIM2->CCMR2 |= TIM_CCMR2_OC3PE;
//	TIM2->CCMR2 |= TIM_CCMR2_OC4PE;
	
	//capture/compare output polarity
	//0: active high
//	TIM2->CCER &= ~TIM_CCER_CC1P;
	TIM2->CCER &= ~TIM_CCER_CC2P;
	TIM2->CCER &= ~TIM_CCER_CC3P;
//	TIM2->CCER &= ~TIM_CCER_CC4P;
	
	//capture compare output enable
//	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->CCER |= TIM_CCER_CC3E;
//	TIM2->CCER |= TIM_CCER_CC4E;
	
	//auto-reload preload set ot buffer
	TIM2->CR1 |= TIM_CR1_ARPE;
	
	//initialize all registers
	TIM2->EGR |= TIM_EGR_UG;
	
	//ensure set to edge Aligned mode (00)
	TIM2->CR1 &= ~TIM_CR1_CMS;
	
	//ensure set to upcounting
	TIM2->CR1 &= ~TIM_CR1_DIR;
	
	//set compare value
//	TIM2->CCR1 = 125;
	TIM2->CCR2 = 170;
	TIM2->CCR3 = 170;
//	TIM2->CCR4 = 170;
	
	//enable counter
	TIM2->CR1 |= TIM_CR1_CEN;
}

void joystick_init(){
	
	//PA3 and 5 correspond to up and down, respectively
	
	// Initialize Joystick
//	GPIOA->MODER &= ~GPIO_MODER_MODE0;
//	GPIOA->MODER &= ~GPIO_MODER_MODE1;
//	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	
//  GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0_0;
//	
//	GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_1;
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1_0;
//	
//	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_1;
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2_0;
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3_0;
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_0;
	
}

void interrupt_init(){
	// Configure SYSCFG EXTI
//	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
//	
//	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
//	
//	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR2_EXTI5;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR2_EXTI5_PA;
	
	// Configure EXTI Trigger
//	EXTI->FTSR1 |= EXTI_FTSR1_FT0;
//	EXTI->FTSR1 |= EXTI_FTSR1_FT1;
//	EXTI->FTSR1 |= EXTI_FTSR1_FT2;
	EXTI->FTSR1 |= EXTI_FTSR1_FT3;
	EXTI->FTSR1 |= EXTI_FTSR1_FT5;	
	
	// Enable EXTI
//	EXTI->IMR1 |= EXTI_IMR1_IM0;
//	EXTI->IMR1 |= EXTI_IMR1_IM1;
//	EXTI->IMR1 |= EXTI_IMR1_IM2;
	EXTI->IMR1 |= EXTI_IMR1_IM3;
	EXTI->IMR1 |= EXTI_IMR1_IM5;
	
	
	// Configure and Enable in NVIC
//	NVIC_EnableIRQ(EXTI0_IRQn);
//	NVIC_SetPriority(EXTI0_IRQn, 0);
//	NVIC_EnableIRQ(EXTI1_IRQn);
//	NVIC_SetPriority(EXTI1_IRQn, 0);
//	NVIC_EnableIRQ(EXTI2_IRQn);
//	NVIC_SetPriority(EXTI2_IRQn, 0);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_SetPriority(EXTI9_5_IRQn, 0);
}


