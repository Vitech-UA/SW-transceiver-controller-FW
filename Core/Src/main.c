/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "si5351.h"
#include "menu.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define INTERMEDIATE_FREQUENCY_Hz 455000
#define INITIAL_VALUE 27000000

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t clockwise_flag = 0;
uint8_t counterclockwise_flag = 0;
uint8_t enc_btn_pressed_flag = 0;
uint16_t freq_step = 1000;
uint32_t freq_to_set = INITIAL_VALUE;
extern char menu_items;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void dds_print_freq(uint32_t freq, uint8_t x_pos, uint8_t y_pos);
void print_freq_handler(void);
void select_menu_item_handler(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

typedef enum {
	STATE_PRINT_FREQ,
	STATE_SET_STEP,
	STATE_SET_INTERMEDIATE_FREQ,
	STATE_SELECT_MENU_ITEM
} STATE_t;
volatile STATE_t state = STATE_PRINT_FREQ;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_I2C1_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */
	const int32_t correction = 100;

	si5351_Init(correction);
	// Enable CLK0 and CLK2
	si5351_EnableOutputs(1 << 0);
	LCD_Init(&hspi1);
	LCD_FillScreen(BLACK);
	dds_print_freq(freq_to_set, 20, 10);
	//si5351_SetupCLK0(A, SI5351_DRIVE_STRENGTH_8MA);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
		switch (state) {
		case STATE_PRINT_FREQ:
			print_freq_handler();
			break;
		case STATE_SELECT_MENU_ITEM:
			select_menu_item_handler();
			break;
		case STATE_SET_INTERMEDIATE_FREQ:

			break;
		}

	}

	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
void dds_print_freq(uint32_t freq, uint8_t x_pos, uint8_t y_pos) {

	LCD_SetCursor(x_pos, y_pos);
	LCD_SetTextSize(1);
	LCD_SetTextColor(YELLOW, BLUE);
	LCD_Printf("%u", freq);
	LCD_DrawLine(00, 35, 240, 35, WHITE);
}
void print_freq_handler(void) {
	if (clockwise_flag == 1) {
		freq_to_set++;
		clockwise_flag = 0;
	}
	if (counterclockwise_flag == 1) {
		freq_to_set--;
		counterclockwise_flag = 0;
	}
	if (enc_btn_pressed_flag) {
		state = STATE_SELECT_MENU_ITEM;
	}

	dds_print_freq(freq_to_set, 20, 10);
	si5351_SetupCLK0((clockwise_flag * freq_step) - INTERMEDIATE_FREQUENCY_Hz,
			SI5351_DRIVE_STRENGTH_2MA);

}
void select_menu_item_handler(void) {
	static int menu_item_index = 0;
	static uint8_t menu_is_drawed_flag = 0;

	if (!menu_is_drawed_flag) {
		draw_menu();
		menu_is_drawed_flag = 0;
	}

	if (counterclockwise_flag) {
		menu_item_index++;
		if (menu_item_index >= MENU_ITEMS_CNT - 1)
			menu_item_index = MENU_ITEMS_CNT - 1;

		select_menu_item(menu_item_index);
		counterclockwise_flag = 0;
		clockwise_flag = 0;
	}
	if (clockwise_flag) {
		menu_item_index--;
		if (menu_item_index <= 0)
			menu_item_index = 0;

		select_menu_item(menu_item_index);
		counterclockwise_flag = 0;
		clockwise_flag = 0;
	}

}

void EXTI1_IRQHandler(void) {
	enc_btn_pressed_flag = 1;
	HAL_GPIO_EXTI_IRQHandler(ENC_BTN_Pin);

}

void EXTI9_5_IRQHandler(void) {

	if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)) {
		// Сюди потрапляємо, коли енкодер крутитим проти часової
		counterclockwise_flag = 1;
	}
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);

}

void EXTI15_10_IRQHandler(void) {

	if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)) {

		clockwise_flag = 1;
		// Сюди потрапляємо, коли енкодер крутитим за часовою
	}
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
