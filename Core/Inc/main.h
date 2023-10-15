/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PAD9_Pin GPIO_PIN_13
#define PAD9_GPIO_Port GPIOC
#define ENC_BTN_Pin GPIO_PIN_14
#define ENC_BTN_GPIO_Port GPIOC
#define ENC_BTN_EXTI_IRQn EXTI15_10_IRQn
#define ATT_Pin GPIO_PIN_15
#define ATT_GPIO_Port GPIOC
#define xV_BAT_Pin GPIO_PIN_0
#define xV_BAT_GPIO_Port GPIOA
#define PREAMP_Pin GPIO_PIN_1
#define PREAMP_GPIO_Port GPIOA
#define SWR_Pin GPIO_PIN_4
#define SWR_GPIO_Port GPIOA
#define cEN_SWR_Pin GPIO_PIN_0
#define cEN_SWR_GPIO_Port GPIOB
#define A_Pin GPIO_PIN_1
#define A_GPIO_Port GPIOB
#define B_Pin GPIO_PIN_2
#define B_GPIO_Port GPIOB
#define C_Pin GPIO_PIN_10
#define C_GPIO_Port GPIOB
#define D_Pin GPIO_PIN_11
#define D_GPIO_Port GPIOB
#define Band_80m_Pin GPIO_PIN_12
#define Band_80m_GPIO_Port GPIOB
#define Band_40m_Pin GPIO_PIN_13
#define Band_40m_GPIO_Port GPIOB
#define Band_20m_Pin GPIO_PIN_14
#define Band_20m_GPIO_Port GPIOB
#define TX_OUT_Pin GPIO_PIN_15
#define TX_OUT_GPIO_Port GPIOB
#define cENC_A_Pin GPIO_PIN_8
#define cENC_A_GPIO_Port GPIOA
#define cENC_B_Pin GPIO_PIN_9
#define cENC_B_GPIO_Port GPIOA
#define cENC_BTN_Pin GPIO_PIN_10
#define cENC_BTN_GPIO_Port GPIOA
#define PAD10_Pin GPIO_PIN_11
#define PAD10_GPIO_Port GPIOA
#define PAD11_Pin GPIO_PIN_12
#define PAD11_GPIO_Port GPIOA
#define PAD12_Pin GPIO_PIN_15
#define PAD12_GPIO_Port GPIOA
#define cTX_RX_Pin GPIO_PIN_3
#define cTX_RX_GPIO_Port GPIOB
#define cEN_PREAMP_Pin GPIO_PIN_4
#define cEN_PREAMP_GPIO_Port GPIOB
#define cEN_ATT_Pin GPIO_PIN_5
#define cEN_ATT_GPIO_Port GPIOB
#define PAD7_Pin GPIO_PIN_8
#define PAD7_GPIO_Port GPIOB
#define PAD8_Pin GPIO_PIN_9
#define PAD8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
