#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 TIM_HandleTypeDef htim3;
 DMA_HandleTypeDef hdma_tim3_ch1_trig;

 UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
#define LED 12
#define Lo 25
#define Hi 50
uint8_t buf[LED*24+48]={
		Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,// Green 0
		Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,// Red 1
		Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Lo,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,// Blue 2
		Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,Hi,// White 3
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi, //4
		Hi,Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi,
		Lo,Lo,Lo,Lo,Lo,Hi,Lo,Lo,Hi,Hi,Hi,Lo,Hi,Hi,Hi,Hi,Lo,Lo,Lo,Hi,Lo,Hi,Lo,Hi, // 12
		//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void convert_color(uint32_t color , uint16_t led_no) // led_no 넘버
{
	for (int i=0; i<24; i++)
	{
//		buf[led_no*24+i] = 57;
		if ( color&(1<<(23-i)))
		{
			buf[led_no*24+i] =Hi;//50;
		}

		else
		{
			buf[led_no*24+i] =Lo;//25;
		}
	}
}
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Stop_DMA(&htim3,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t*)buf,LED*24+48);
  while(hdma_tim3_ch1_trig.Instance->CNDTR>0);
  HAL_Delay(3000);

  memset(buf,0,LED*24+48);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  for (int i=0;i<12;i++)
	  {
		  convert_color(rand(),i);
	  }
	  HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t*)buf,LED*24+48);
	  while(hdma_tim3_ch1_trig.Instance->CNDTR>0);
	  HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}
