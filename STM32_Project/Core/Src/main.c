/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdbool.h"
#include "ssd1306.h"
#include "CANSPI.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CAN1 &hspi1
#define CAN2 &hspi2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for uart_rx */
osThreadId_t uart_rxHandle;
const osThreadAttr_t uart_rx_attributes = {
  .name = "uart_rx",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for adc */
osThreadId_t adcHandle;
const osThreadAttr_t adc_attributes = {
  .name = "adc",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for stepper */
osThreadId_t stepperHandle;
const osThreadAttr_t stepper_attributes = {
  .name = "stepper",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for servo */
osThreadId_t servoHandle;
const osThreadAttr_t servo_attributes = {
  .name = "servo",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for enviar_estado */
osThreadId_t enviar_estadoHandle;
const osThreadAttr_t enviar_estado_attributes = {
  .name = "enviar_estado",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for enviar_tmp */
osThreadId_t enviar_tmpHandle;
const osThreadAttr_t enviar_tmp_attributes = {
  .name = "enviar_tmp",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for oled */
osThreadId_t oledHandle;
const osThreadAttr_t oled_attributes = {
  .name = "oled",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for CAN_remote */
osThreadId_t CAN_remoteHandle;
const osThreadAttr_t CAN_remote_attributes = {
  .name = "CAN_remote",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for uart_rx_queue */
osMessageQueueId_t uart_rx_queueHandle;
const osMessageQueueAttr_t uart_rx_queue_attributes = {
  .name = "uart_rx_queue"
};
/* Definitions for uart_tx_sem */
osSemaphoreId_t uart_tx_semHandle;
const osSemaphoreAttr_t uart_tx_sem_attributes = {
  .name = "uart_tx_sem"
};
/* Definitions for CAN_sem */
osSemaphoreId_t CAN_semHandle;
const osSemaphoreAttr_t CAN_sem_attributes = {
  .name = "CAN_sem"
};
/* USER CODE BEGIN PV */
uint8_t rx_data;
uCAN_MSG txMessage;
uCAN_MSG rxMessage;
bool enable_CAN = false;
bool flag_man_remota=false;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM3_Init(void);
void StartDefaultTask(void *argument);
void uart_rx_task(void *argument);
void adc_task(void *argument);
void stepper_task(void *argument);
void servo_Task(void *argument);
void enviar_estado_Task(void *argument);
void enviar_tmp_task(void *argument);
void oled_Task(void *argument);
void CAN_remote_task(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int temp_rmt_ent, temp_rmt_dec, servo_rmt, rpm_rmt_ent, rpm_rmt_dec;

float temperature, potenciometro, grados;
int entera_TEMP, decimal_TEMP;

float tmp_velocidad=(1/90.0)*1000;
float espera=2000;
float Ta;
float ccr=20000*0.05;
int estado=5, periodo=5;
int controlPP=0;
char direccion='D';

int periodo_TEMP=1000;

uint8_t data_uart_rx, info=0;
bool activar_remota=false;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  ssd1306_Init();
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of uart_tx_sem */
  uart_tx_semHandle = osSemaphoreNew(1, 1, &uart_tx_sem_attributes);

  /* creation of CAN_sem */
  CAN_semHandle = osSemaphoreNew(1, 1, &CAN_sem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of uart_rx_queue */
  uart_rx_queueHandle = osMessageQueueNew (4, sizeof(uint8_t), &uart_rx_queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of uart_rx */
  uart_rxHandle = osThreadNew(uart_rx_task, NULL, &uart_rx_attributes);

  /* creation of adc */
  adcHandle = osThreadNew(adc_task, NULL, &adc_attributes);

  /* creation of stepper */
  stepperHandle = osThreadNew(stepper_task, NULL, &stepper_attributes);

  /* creation of servo */
  servoHandle = osThreadNew(servo_Task, NULL, &servo_attributes);

  /* creation of enviar_estado */
  enviar_estadoHandle = osThreadNew(enviar_estado_Task, NULL, &enviar_estado_attributes);

  /* creation of enviar_tmp */
  enviar_tmpHandle = osThreadNew(enviar_tmp_task, NULL, &enviar_tmp_attributes);

  /* creation of oled */
  oledHandle = osThreadNew(oled_Task, NULL, &oled_attributes);

  /* creation of CAN_remote */
  CAN_remoteHandle = osThreadNew(CAN_remote_task, NULL, &CAN_remote_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	osThreadSuspend(enviar_tmpHandle);
	osThreadSuspend(stepperHandle);
	osThreadSuspend(oledHandle);
	//osThreadSuspend(CAN_remoteHandle);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_41CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 47;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 19999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CAN1_CS_GPIO_Port, CAN1_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, steper_in_4_Pin|CAN2_CS_Pin|steper_in_1_Pin|steper_in_3_Pin
                          |steper_in_2_Pin|CAN1_CSB6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CAN1_CS_Pin */
  GPIO_InitStruct.Pin = CAN1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CAN1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Ican2_Pin */
  GPIO_InitStruct.Pin = Ican2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Ican2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : steper_in_4_Pin CAN2_CS_Pin steper_in_1_Pin steper_in_3_Pin
                           steper_in_2_Pin CAN1_CSB6_Pin */
  GPIO_InitStruct.Pin = steper_in_4_Pin|CAN2_CS_Pin|steper_in_1_Pin|steper_in_3_Pin
                          |steper_in_2_Pin|CAN1_CSB6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Ican1_Pin */
  GPIO_InitStruct.Pin = Ican1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Ican1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	osSemaphoreRelease(uart_tx_semHandle);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	osMessageQueuePut(uart_rx_queueHandle, &rx_data, 0U, 0U);
	HAL_UART_Receive_IT(&huart2, &rx_data, sizeof(rx_data));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == Ican1_Pin || GPIO_Pin==Ican2_Pin) {
		osSemaphoreRelease(CAN_semHandle);
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	osThreadSuspend(defaultTaskHandle);
  for(;;)
  {
	  //HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
	  osDelay(2000);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_uart_rx_task */
/**
* @brief Function implementing the uart_rx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_uart_rx_task */
void uart_rx_task(void *argument)
{
  /* USER CODE BEGIN uart_rx_task */
	HAL_UART_Receive_IT(&huart2, &data_uart_rx, 1);
		uint8_t trama[4], seg, vel[3];
		float veltotal;

		osThreadSuspend(servoHandle);
		osThreadSuspend(stepperHandle);
		osThreadSuspend(oledHandle);
		osThreadSuspend(enviar_tmpHandle);
		osThreadSuspend(CAN_remoteHandle);

		  for(;;)
		  {
			  osMessageQueueGet(uart_rx_queueHandle, &trama[0], 0, osWaitForever);
			  osMessageQueueGet(uart_rx_queueHandle, &trama[1], 0, osWaitForever);
			  osMessageQueueGet(uart_rx_queueHandle, &trama[2], 0, osWaitForever);
			  osMessageQueueGet(uart_rx_queueHandle, &trama[3], 0, osWaitForever);

			if(trama[3]==0xE0){
				switch(trama[0]){
					case 'T':
						osThreadResume(enviar_tmpHandle);
						periodo_TEMP=trama[1]*10;
						break;
					case 't':
						osThreadSuspend(enviar_tmpHandle);
						break;
					case 'M':
						osThreadResume(stepperHandle);
						periodo=(60*1000)/(2048.0*trama[1]);

						if(periodo<2){
							periodo=2;
						}
						break;
					case 'S':
						estado=5;
						osThreadResume(servoHandle);
						grados=trama[1];
						Ta=grados/90.0 +1;
						ccr=Ta*1000;
						htim3.Instance -> CCR2 = ccr;
						break;
					case 'X':
						osThreadResume(oledHandle);
						info=1;
						break;
					case 'C':
						osThreadSuspend(servoHandle);
						osThreadSuspend(stepperHandle);
						info=0;
						osThreadSuspend(enviar_tmpHandle);
						osThreadSuspend(CAN_remoteHandle);
						break;
					case 'D':
						direccion='D';
						osThreadResume(stepperHandle);
						break;
					case 'I':
						direccion='I';
						osThreadResume(stepperHandle);
						break;
					case 'P':
						osThreadResume(servoHandle);
						estado=4;
						break;
					case 'A':
						osThreadSuspend(servoHandle);
						estado=0;
						espera=trama[1]*1000;
						tmp_velocidad=(1000/trama[2]);
						osThreadResume(servoHandle);
						break;
					case 'R':
						activar_remota=true;
						osThreadResume(CAN_remoteHandle);
						break;
					}
			}
		    osDelay(10);
		  }
  /* USER CODE END uart_rx_task */
}

/* USER CODE BEGIN Header_adc_task */
/**
* @brief Function implementing the adc thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_adc_task */
void adc_task(void *argument)
{
  /* USER CODE BEGIN adc_task */
	/* Infinite loop */
	uint16_t adc_value;
	float adc_in_0_voltage;

	HAL_ADCEx_Calibration_Start(&hadc);

	for (;;) {
		//CONVERSIÓN CANAL 0
			  HAL_ADC_Start(&hadc);
			  //Preguntar si la conversion del canal 1 esta lista
			  while(HAL_ADC_PollForConversion(&hadc,1) != HAL_OK);

			  adc_value = HAL_ADC_GetValue(&hadc);

			  //HAL_ADC_Stop(&hadc);

			  adc_in_0_voltage = (adc_value/4096.0)*3.3;

			  temperature= adc_in_0_voltage/0.010;

			  //CONVERSIÓN CANAL 1
			  //HAL_ADC_Start(&hadc);
			  //Preguntar si la conversion del canal 2 esta lista
			  while(HAL_ADC_PollForConversion(&hadc,1) != HAL_OK);

			  adc_value = HAL_ADC_GetValue(&hadc);

			  HAL_ADC_Stop(&hadc);

			  adc_in_0_voltage = (adc_value/4096.0)*3.3;

			  potenciometro = adc_in_0_voltage;

		    osDelay(10);
		  }
  /* USER CODE END adc_task */
}

/* USER CODE BEGIN Header_stepper_task */
/**
* @brief Function implementing the stepper thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_stepper_task */
void stepper_task(void *argument)
{
  /* USER CODE BEGIN stepper_task */
	char numfase=1;
	 /* Infinite loop */
	 for(;;){
		 switch(numfase) {
			 case 1:
				  HAL_GPIO_WritePin(GPIOB, steper_in_1_Pin, 1);
				  HAL_GPIO_WritePin(GPIOB, steper_in_2_Pin, 1);
				  HAL_GPIO_WritePin(GPIOB, steper_in_3_Pin, 0);
				  HAL_GPIO_WritePin(GPIOB, steper_in_4_Pin, 0);
				  break;
			  case 2:
				  HAL_GPIO_WritePin(GPIOB, steper_in_1_Pin, 0);
				  HAL_GPIO_WritePin(GPIOB, steper_in_2_Pin, 1);
				  HAL_GPIO_WritePin(GPIOB, steper_in_3_Pin, 1);
				  HAL_GPIO_WritePin(GPIOB, steper_in_4_Pin, 0);
				  break;
			  case 3:
				  HAL_GPIO_WritePin(GPIOB, steper_in_1_Pin, 0);
				  HAL_GPIO_WritePin(GPIOB, steper_in_2_Pin, 0);
				  HAL_GPIO_WritePin(GPIOB, steper_in_3_Pin, 1);
				  HAL_GPIO_WritePin(GPIOB, steper_in_4_Pin, 1);
				  break;
			  case 4:
				  HAL_GPIO_WritePin(GPIOB, steper_in_1_Pin, 1);
				  HAL_GPIO_WritePin(GPIOB, steper_in_2_Pin, 0);
				  HAL_GPIO_WritePin(GPIOB, steper_in_3_Pin, 0);
				  HAL_GPIO_WritePin(GPIOB, steper_in_4_Pin, 1);
				  break;
			  }

		  if(direccion=='D'){
			numfase++;
			  if(numfase>=5)
				  numfase=1;
		  }
		  if(direccion=='I'){
		  	numfase--;
		  		if(numfase<=0)
		  			numfase=4;
		  }
	  osDelay(periodo);
	 }
  /* USER CODE END stepper_task */
}

/* USER CODE BEGIN Header_servo_Task */
/**
* @brief Function implementing the servo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_servo_Task */
void servo_Task(void *argument)
{
  /* USER CODE BEGIN servo_Task */
	/* Infinite loop */
	for (;;) {
		switch(estado){
		  case 0:
			  grados=0;
			  estado=1;
			  osDelay(10);
			  break;
		  case 1:
			grados++;
			 Ta=grados/90 +1;
			 ccr=Ta*1000;
			 htim3.Instance -> CCR2 = ccr;
				if(grados==90)
					estado=2;
			osDelay(tmp_velocidad);
			break;
		  case 2:
			estado=3;
			osDelay(espera);
				  break;
		  case 3:
			  grados--;
			  Ta=grados/90 +1;				//Ta=1
			  ccr=Ta*1000;
			  htim3.Instance -> CCR2 = ccr;
				  if(grados==0)
					  estado=5;
			  osDelay(tmp_velocidad);
				  break;
		  case 4:
			   grados = (90/3.3)*potenciometro;
			   Ta=grados/90.0 +1;				//Ta=1
			   ccr=Ta*1000;
			   htim3.Instance -> CCR2 = ccr;
			   osDelay(50);
			  break;
		  case 5:
			  osDelay(200);
			  break;
		  }
		  //osDelay(10);
	  }
  /* USER CODE END servo_Task */
}

/* USER CODE BEGIN Header_enviar_estado_Task */
/**
* @brief Function implementing the enviar_estado thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_enviar_estado_Task */
void enviar_estado_Task(void *argument)
{
  /* USER CODE BEGIN enviar_estado_Task */
	/* Infinite loop */
	uint8_t trama[4];

	for (;;) {
		if(flag_man_remota==true){
			osSemaphoreAcquire(uart_tx_semHandle, osWaitForever);
			trama[0]=0x21;
			trama[1]=servo_rmt;
			trama[2]=0xFF;
			trama[3]=0xE0;
			HAL_UART_Transmit_IT(&huart2, trama , 4);

			osSemaphoreAcquire(uart_tx_semHandle, osWaitForever);
			trama[0]=0x31;
			trama[1]=temp_rmt_ent;
			trama[2]=temp_rmt_dec;
			trama[3]=0xE0;
			HAL_UART_Transmit_IT(&huart2, trama , 4);

			osSemaphoreAcquire(uart_tx_semHandle, osWaitForever);
			trama[0]=0x41;
			trama[1]=rpm_rmt_ent;
			trama[2]=rpm_rmt_dec;
			trama[3]=0xE0;
			HAL_UART_Transmit_IT(&huart2, trama , 4);
		}

		osSemaphoreAcquire(uart_tx_semHandle, osWaitForever);
		trama[0]=0x40;
		trama[1]=(60*1000)/(2048.0*periodo);     //(64*4=256 pasos una vuelta * PERIODO(ms))(rev/s) -> pasamos a rad/s
		trama[2]=((60*1000)/(2048.0*periodo)-trama[1])*100;
		trama[3]=0xE0;
		HAL_UART_Transmit_IT(&huart2, trama , 4);

		osSemaphoreAcquire(uart_tx_semHandle, osWaitForever);
		trama[0]=0x20;
		trama[1]=grados;
		trama[2]=0xFF;
		trama[3]=0xE0;
		HAL_UART_Transmit_IT(&huart2, trama , 4);

		osDelay(250);
	}
  /* USER CODE END enviar_estado_Task */
}

/* USER CODE BEGIN Header_enviar_tmp_task */
/**
* @brief Function implementing the enviar_tmp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_enviar_tmp_task */
void enviar_tmp_task(void *argument)
{
  /* USER CODE BEGIN enviar_tmp_task */
	char msg[10];
		int entera_TEMP, decimal_TEMP;
		uint8_t trama[4];

	  for(;;)
	  {
		  osSemaphoreAcquire(uart_tx_semHandle, osWaitForever);
			trama[0]=0x30;
			trama[1]=temperature;
			trama[2]=(temperature - trama[1])*100;
			trama[3]=0xE0;
			HAL_UART_Transmit_IT(&huart2, trama, 4);

	    osDelay(periodo_TEMP);
	  }
  /* USER CODE END enviar_tmp_task */
}

/* USER CODE BEGIN Header_oled_Task */
/**
* @brief Function implementing the oled thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_oled_Task */
void oled_Task(void *argument)
{
  /* USER CODE BEGIN oled_Task */
	/* Infinite loop */
	uint8_t y = 0;
	float vel_pp;
	int entera_TEMP, decimal_TEMP, temp, entera_PP, decimal_PP;
	ssd1306_Fill(Black);
	char msg[28];

	  for(;;)
	  {
		  switch(info){
			  case 0:
				ssd1306_Fill(Black);
				ssd1306_UpdateScreen();
				  break;
			  case 1:
				ssd1306_Fill(Black);

				y=0;
				ssd1306_SetCursor(2, y);
				entera_TEMP = temperature;
				decimal_TEMP=(temperature - entera_TEMP)*100;
				sprintf(msg, "Temperatura: %d.%dC", entera_TEMP, decimal_TEMP);
				ssd1306_WriteString(msg, Font_7x10, White);

				y += 10;
				ssd1306_SetCursor(2, y);
				temp=grados;
				sprintf(msg, "Posicion servo: %d ", temp);
				ssd1306_WriteString(msg, Font_7x10, White);

				y += 10;
				ssd1306_SetCursor(2, y);
				vel_pp=(60*1000)/(2048.0*periodo);
				//vel_pp=(2*3.14)/vel_pp;

				entera_PP = vel_pp;
				decimal_PP=(vel_pp - entera_PP)*100;
				sprintf(msg, "Velocidad: %d.%d", entera_PP, decimal_PP);
				ssd1306_WriteString(msg, Font_7x10, White);

				ssd1306_UpdateScreen();
				  break;
		  }
		osDelay(500);
  }
  /* USER CODE END oled_Task */
}

/* USER CODE BEGIN Header_CAN_remote_task */
/**
* @brief Function implementing the CAN_remote thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CAN_remote_task */
void CAN_remote_task(void *argument)
{
  /* USER CODE BEGIN CAN_remote_task */
	uint8_t tx_buffer[54], i=0;
	bool datos_rmt=false;

	for (i=0; i<54; i++) tx_buffer[i]=0;
	if( CANSPI_Initialize(CAN1)) {
			/*osSemaphoreAcquire(uart_tx_semHandle, portMAX_DELAY);
			sprintf(tx_buffer, "CAN1 initialized OK\n\r");
			HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));*/
			/*txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
			txMessage.frame.id = 0x15;
			txMessage.frame.dlc = 8;
			txMessage.frame.data0 = entera_TEMP;
			txMessage.frame.data1 = decimal_TEMP;
			txMessage.frame.data2 = 6;
			txMessage.frame.data3 = 5;
			txMessage.frame.data4 = 4;
			txMessage.frame.data5 = 3;
			txMessage.frame.data6 = 2;
			txMessage.frame.data7 = 1;
			CANSPI_Transmit(CAN1, &txMessage);
			osSemaphoreAcquire(uart_tx_semHandle, portMAX_DELAY);
			sprintf(tx_buffer, "CAN1 sending Msg...\n\r");
			HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));*/
	  }
	  else
	  {
			osSemaphoreAcquire(uart_tx_semHandle, portMAX_DELAY);
			sprintf(tx_buffer, "Error CAN1 initiali\n\r");
			HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));
	  }
	  osDelay(1000);
	  //for (i=0; i<54; i++) tx_buffer[i]=0;
	  if (CANSPI_Initialize(CAN2)) {
			/*osSemaphoreAcquire(uart_tx_semHandle, portMAX_DELAY);
			sprintf(tx_buffer, "CAN2 initialized OK\n\r");
			HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));*/
			/*txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
			txMessage.frame.id = 0x25;
			txMessage.frame.dlc = 8;
			txMessage.frame.data0 = entera_TEMP;
			txMessage.frame.data1 = decimal_TEMP;
			txMessage.frame.data2 = 3;
			txMessage.frame.data3 = 4;
			txMessage.frame.data4 = 5;
			txMessage.frame.data5 = 6;
			txMessage.frame.data6 = 7;
			txMessage.frame.data7 = 8;
			CANSPI_Transmit(CAN2, &txMessage);*/
			/*osSemaphoreAcquire(uart_tx_semHandle, portMAX_DELAY);
			sprintf(tx_buffer, "CAN2 sending Msg...\n\r");
			HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));*/
	  }
	  else
	  {
			osSemaphoreAcquire(uart_tx_semHandle, portMAX_DELAY);
			sprintf(tx_buffer, "Error CAN2 initiali\n\r");
			HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));

	  }
	  osDelay(1000);

	  /* Infinite loop */
	  for(;;)
	  {
		  //NOSOTROS SOMOS B
		  if(activar_remota==true){
			  	osSemaphoreAcquire(CAN_semHandle, portMAX_DELAY);
				CANSPI_CL_Flag_Int(CAN1);
				txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
				txMessage.frame.id = 0x11;   //QUEREMOS QUE "A" (CAN 2) NOS MANDE LA INFORMACION
				txMessage.frame.dlc = 8;		// LE ENVIAMOS A "A" (CAN 2) UN .id = 0x11
				txMessage.frame.data0 = 0;		//PARA QUE "A" (CAN 2) NOS PASE LOS DATOS
				txMessage.frame.data1 = 0;
				txMessage.frame.data2 = 0;
				txMessage.frame.data3 = 0;
				txMessage.frame.data4 = 0;
				txMessage.frame.data5 = 0;
				txMessage.frame.data6 = 0;
				txMessage.frame.data7 = 0;
				CANSPI_Transmit(CAN1, &txMessage); //Se lo mando al CAN 2

				activar_remota=false;
		  }
		    if(CANSPI_Receive(CAN1, &rxMessage))
		    {
				if(rxMessage.frame.id==0x15 && rxMessage.frame.dlc==8 &&  rxMessage.frame.data5==0x1 &&
						rxMessage.frame.data6==0xC && rxMessage.frame.data7==0x1){
					//RECIBIMOS LA INFORMACIÓN DE A "CAN 2"
					datos_rmt=true;
					temp_rmt_ent=rxMessage.frame.data0;
					temp_rmt_dec=rxMessage.frame.data1;
					servo_rmt = rxMessage.frame.data2;
					rpm_rmt_ent = rxMessage.frame.data3;
					rpm_rmt_dec = rxMessage.frame.data4;
				}
		    } else
		    if(CANSPI_Receive(CAN2, &rxMessage))
		    {
				if(rxMessage.frame.id==0x11 && rxMessage.frame.dlc==8 && rxMessage.frame.data0==0 &&
					rxMessage.frame.data1==0 && rxMessage.frame.data2==0 && rxMessage.frame.data3==0 &&
					rxMessage.frame.data4==0 && rxMessage.frame.data5==0 && rxMessage.frame.data6==0 &&
					rxMessage.frame.data7==0){
					// (A)CAN 2 RECIBE SU ID=0x11 Y ACTIVA LA BANDERA PARA ENVIAR SU INFORMACIÓN EN REMOTO
					flag_man_remota=true;
				}
		    }
		    if(flag_man_remota== true){
				//osSemaphoreAcquire(CAN_semHandle, portMAX_DELAY);
		    	//CAN 2 NOS ENVIA LA INFORMACIÓN
				CANSPI_CL_Flag_Int(CAN2);
				txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
				txMessage.frame.id = 0x15;
				txMessage.frame.dlc = 8;
				txMessage.frame.data0 = temperature;
				txMessage.frame.data1 = (temperature - txMessage.frame.data0)*100;
				txMessage.frame.data2 = grados/*servo*/;
				txMessage.frame.data3 =(60*1000)/(2048.0*periodo)/*vel entera*/;
				txMessage.frame.data4 =((60*1000)/(2048.0*periodo)-txMessage.frame.data3)*100/*vel decimal*/;
				txMessage.frame.data5 = 0x1;
				txMessage.frame.data6 = 0xC;
				txMessage.frame.data7 = 0x1;
				CANSPI_Transmit(CAN2, &txMessage);
		    }
		    osDelay(1000);
	  }
  /* USER CODE END CAN_remote_task */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
