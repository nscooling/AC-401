/*
 * usart3_remap.c
 *
 * Created on: 30 Jun 2016
 * Author: Feabhas
 *
 * DISCLAIMER:
 * Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
 * of the item whatsoever, whether express, implied, or statutory, including, but
 * not limited to, any warranty of merchantability or fitness for a particular
 * purpose or any warranty that the contents of the item will be error-free.
 * In no respect shall Feabhas incur any liability for any damages, including, but
 * limited to, direct, indirect, special, or consequential damages arising out of,
 * resulting from, or any way connected to the use of the item, whether or not
 * based upon warranty, contract, tort, or otherwise; whether or not injury was
 * sustained by persons or property or otherwise; and whether or not loss was
 * sustained from, or arose out of, the results of, the item, or any services that
 * may be provided by Feabhas.
 *
 */

#include "stm32f4xx.h"
#include "usart3_remap.h"

// USART3 GPIO Configuration
// PB10     ------> USART3_TX
// PB11     ------> USART3_RX
void remap_USART3_IO_Pins(void)
{
  // Enable GPIO B IO Port Clock
  RCC->AHB1ENR |= (1 << 1);			// Bit1 : GPIOBEN

  // Enable USART3 Peripheral
  RCC->APB1ENR |= (1 << 18);

  // if pinNum > 8 then use AFR[1]
  // 4 bits per pin
  // AF7 (0x07) sets the GPIO B (to USART3 AF functions)

  GPIOB->AFR[1] |= (0x07 << ( 4 * (10 % 8)));	// GPIO_AF7_USART3
  GPIOB->AFR[1] |= (0x07 << ( 4 * (11 % 8)));	// GPIO_AF7_USART3

  GPIOB->MODER |= (0x02 << (10 * 2));		// GPIO_MODE_AF_PP
  GPIOB->MODER |= (0x02 << (11 * 2));		// GPIO_MODE_AF_PP

  GPIOB->OSPEEDR |= (0x03 << (10 * 2));	          // GPIO_SPEED_HIGH
  GPIOB->OSPEEDR |= (0x03 << (11 * 2));	          // GPIO_SPEED_HIGH

  GPIOB->PUPDR |= (0x01 << (10 * 2));		// GPIO_PULLUP
  GPIOB->PUPDR |= (0x01 << (11 * 2));		// GPIO_PULLUP
}
