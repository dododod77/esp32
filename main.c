/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define SR_DATA(x)   HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)

// Makro untuk Clock (Otomatis High-Low)
#define SR_CLOCK()   do { \
                        HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, GPIO_PIN_SET); \
                        HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, GPIO_PIN_RESET); \
                     } while(0)

// Makro untuk Load/Latch (Otomatis High-Low)
#define SR_LOAD()    do { \
                        HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_SET); \
                        HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_RESET); \
                     } while(0)

// Makro untuk Clear (Reset)
#define SR_CLEAR()   do { \
                        HAL_GPIO_WritePin(CLEAR_GPIO_Port, CLEAR_Pin, GPIO_PIN_RESET); \
                        HAL_GPIO_WritePin(CLEAR_GPIO_Port, CLEAR_Pin, GPIO_PIN_SET); \
                     } while(0)

/* Definisi Bit Lampu per Sisi (4-bit) */
#define L_MERAH  0x01 // 0001
#define L_KUNING 0x02 // 0010
#define L_HIJAU  0x04 // 0100
#define L_BIRU   0x08 // 1000

#define LCD_RS(x)  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LCD_RW(x)  HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LCD_E(x)   HAL_GPIO_WritePin(LCD_E_GPIO_Port,  LCD_E_Pin,  (x)?GPIO_PIN_SET:GPIO_PIN_RESET)

#define LCD_D4(x)  HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LCD_D5(x)  HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LCD_D6(x)  HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
#define LCD_D7(x)  HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t kondisi1[16] = { 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
uint8_t kondisi2[16] = { 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
uint8_t kondisi3[16] = { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
uint8_t kondisi4[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
uint8_t kondisi5[16] = { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
uint8_t kondisi6[16] = { 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 };
uint8_t kondisi7[16] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };
uint8_t kondisi8[16] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 };

uint8_t birumerah[16] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
uint8_t kuningsemua[16] = { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 };

uint8_t *kondisi_list[8] = { kondisi1, kondisi2, kondisi3, kondisi4, kondisi5,
		kondisi6, kondisi7, kondisi8 };

//int nilai = 123;
char buffer[16];
char buffer2[16];

char status1 = 'O';
char status2 = 'X';
char status3 = 'X';
char status4 = 'X';

int cd1 = 10;
int cd2 = 23;
int cd3 = 36;
int cd4 = 49;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);

void SR_SendArray(uint8_t arr[16]);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	SR_CLEAR();
	SR_Shift16(0x0000);

	LCD_Init();
	LCD_SetCursor(0, 5);
	LCD_Print("4 WAY");

	LCD_SetCursor(1, 1);
	LCD_Print("TRAFFIC LIGHT");
	HAL_Delay(3000);

	LCD_Clear();

//  sprintf(buffer, "Nilai: %d", nilai);
	sprintf(buffer, "1:%c 2:%c 3:%c 4:%c", status1, status2, status3, status4);

	LCD_SetCursor(0, 0);
	LCD_Print(buffer);

	while (1) {
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//	  HAL_Delay(2000);
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//	  HAL_Delay(2000);
		//		SILKUS
		static uint8_t counter = 0;          // kondisi 0–7
		static uint32_t t_prev = 0;
		static uint32_t time_prev = 0;
		static uint32_t durasi = 0;
		uint32_t now = HAL_GetTick();

		/* ================= SIKLUS NORMAL ================= */
		if (now - t_prev >= durasi) {
			t_prev = now;

			if (counter == 0) {
				status1 = 'O';
				status2 = 'X';
				status3 = 'X';
				status4 = 'X';

				cd1 = 10;
				cd2 = 23;
				cd3 = 36;
				cd4 = 49;

// update cd1 - 4
			} else if (counter == 1) {
				status1 = '-';
				status2 = 'X';
				status3 = 'X';
				status4 = 'X';



			} else if (counter == 2) {
				status1 = 'X';
				status2 = 'O';
				status3 = 'X';
				status4 = 'X';



			} else if (counter == 3) {
				status1 = 'X';
				status2 = '-';
				status3 = 'X';
				status4 = 'X';



			} else if (counter == 4) {
				status1 = 'X';
				status2 = 'X';
				status3 = 'O';
				status4 = 'X';



			} else if (counter == 5) {
				status1 = 'X';
				status2 = 'X';
				status3 = '-';
				status4 = 'X';



			} else if (counter == 6) {
				status1 = 'X';
				status2 = 'X';
				status3 = 'X';
				status4 = 'O';



			} else if (counter == 7) {
				status1 = 'X';
				status2 = 'X';
				status3 = 'X';
				status4 = '-';



			}

			sprintf(buffer, "1:%c 2:%c 3:%c 4:%c", status1, status2, status3,
					status4);

			LCD_SetCursor(0, 0);
			LCD_Print(buffer);

			SR_SendArray(kondisi_list[counter]);
//	  		UpdateStatusNormal(idx);
			if ((counter % 2) == 0) {
				durasi = 10000;   // HIJAU
			} else
				durasi = 3000;   // KUNING
			counter++;
			if (counter >= 8)
				counter = 0;

		}

		uint32_t time = HAL_GetTick();

		if (time - time_prev >= 1000) {
			time_prev = time;

			sprintf(buffer2, "%03d %03d %03d %03d", cd1, cd2, cd3, cd4);
			LCD_SetCursor(1, 0);
			LCD_Print(buffer2);

			cd1--;
			cd2--;
			cd3--;
			cd4--;

			if (cd1 < 0)
				cd1 = 51;

			if (cd2 < 0)
				cd2 = 51;

			if (cd3 < 0)
				cd3 = 51;

			if (cd4 < 0)
				cd4 = 51;
		}

//	  SR_Shift16(led3);
//	  SR_Shift16(led4);

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
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

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, LED1_Pin | GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
			DATA_Pin | CLOCK_Pin | CLEAR_Pin | LOAD_Pin | LCD_D4_Pin
					| LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin | LCD_RW_Pin | LCD_E_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : LED1_Pin PC15 */
	GPIO_InitStruct.Pin = LED1_Pin | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : DATA_Pin CLOCK_Pin CLEAR_Pin LOAD_Pin
	 LCD_D4_Pin LCD_D5_Pin LCD_D6_Pin LCD_D7_Pin */
	GPIO_InitStruct.Pin = DATA_Pin | CLOCK_Pin | CLEAR_Pin | LOAD_Pin
			| LCD_D4_Pin | LCD_D5_Pin | LCD_D6_Pin | LCD_D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : LCD_RS_Pin LCD_RW_Pin LCD_E_Pin */
	GPIO_InitStruct.Pin = LCD_RS_Pin | LCD_RW_Pin | LCD_E_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : BTN_Pin */
	GPIO_InitStruct.Pin = BTN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BTN_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void SR_Shift16(uint16_t data) {
	for (int8_t i = 15; i >= 0; i--)  // MSB -> LSB
			{
		SR_DATA((data >> i) & 0x01);
		SR_CLOCK();
	}
	SR_LOAD(); // Latch setelah 16 bit masuk
}

void SR_SendArray(uint8_t arr[16]) {
	for (uint8_t i = 0; i < 16; i++) {
		SR_DATA(arr[i]);
		SR_CLOCK();
	}
	SR_LOAD();
}

//FUNGSI LCD
static void LCD_EnablePulse(void) {
	LCD_E(1);
	HAL_Delay(1);
	LCD_E(0);
	HAL_Delay(1);
}

static void LCD_Send4Bit(uint8_t data) {
	LCD_D4((data >> 0) & 0x01);
	LCD_D5((data >> 1) & 0x01);
	LCD_D6((data >> 2) & 0x01);
	LCD_D7((data >> 3) & 0x01);
	LCD_EnablePulse();
}

void LCD_Command(uint8_t cmd) {
	LCD_RS(0);
	LCD_RW(0);

	LCD_Send4Bit(cmd >> 4);
	LCD_Send4Bit(cmd & 0x0F);

	HAL_Delay(2);
}

void LCD_Data(uint8_t data) {
	LCD_RS(1);
	LCD_RW(0);

	LCD_Send4Bit(data >> 4);
	LCD_Send4Bit(data & 0x0F);

	HAL_Delay(1);
}

void LCD_Init(void) {
	HAL_Delay(50);

	LCD_RS(0);
	LCD_RW(0);

	LCD_Send4Bit(0x03);
	HAL_Delay(5);
	LCD_Send4Bit(0x03);
	HAL_Delay(1);
	LCD_Send4Bit(0x03);
	HAL_Delay(1);
	LCD_Send4Bit(0x02);   // 4-bit mode

	LCD_Command(0x28);   // 4-bit, 2 line, 5x8 font
	LCD_Command(0x0C);   // Display ON, cursor OFF
	LCD_Command(0x06);   // Entry mode
	LCD_Command(0x01);   // Clear
}

void LCD_Clear(void) {
	LCD_Command(0x01);
	HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
	uint8_t addr = (row == 0) ? 0x00 : 0x40;
	LCD_Command(0x80 | (addr + col));
}

void LCD_Print(char *str) {
	while (*str) {
		LCD_Data(*str++);
	}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
