/* GPIO library for working with SPI chip W25Q128JVSIQ.
* The work is implemented in two modes: Single SPI (functions with SPI in the name) and Quad SPI (Functions with QSPI in the name).
* Before working with SPI functions, you must first call the Single_Mode () function.
* The QSPI functions for reading and writing themselves reconfigure the GPIO to the required mode of operation (Functions QSPI_Recieve_Init () and QSPI_Transmit_Init ()).
* Registers are read in Single SPI mode.
* QSPI functions for reading and writing 8, 16 and 32 bits are located after 480 pages of this file.
*/

#include "main.h"
#include "Qspi_func.h"

//OSPI_RegularCmdTypeDef idread;
GPIO_InitTypeDef GPIO_InitStruct = {0};

void GPIO_QSPI_Init(void)
{
	
	    /**OCTOSPI1 GPIO Configuration    
    PF6     ------> OCTOSPIM_P1_IO3
    PF7     ------> OCTOSPIM_P1_IO2
    PA2     ------> OCTOSPIM_P1_NCS
    PF10     ------> OCTOSPIM_P1_CLK
    PB0     ------> OCTOSPIM_P1_IO1
    PB1     ------> OCTOSPIM_P1_IO0 
    */
		
		__HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
		
		/* PF6 (IO3), PF7 (IO2) */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		/* PA2 (NCS) */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

		/* PB0 (IO1), PB1 (IO0) */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		/* PF10 (CLK) */
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
}
/* Functions for pin state*/
/* Set */
void Set(uint8_t pin)
{
	switch(pin)
	{
		case io0:
			HAL_GPIO_WritePin(IO0_GPIO_PORT, IO0_PIN, GPIO_PIN_SET);
			break;
		case io1:
			HAL_GPIO_WritePin(IO1_GPIO_PORT, IO1_PIN, GPIO_PIN_SET);
			break;
		case io2:
			HAL_GPIO_WritePin(IO2_GPIO_PORT, IO2_PIN, GPIO_PIN_SET);
			break;
		case io3:
			HAL_GPIO_WritePin(IO3_GPIO_PORT, IO3_PIN, GPIO_PIN_SET);
			break;
		case cs:
			HAL_GPIO_WritePin(CS_GPIO_PORT, CS_PIN, GPIO_PIN_SET);
			break;
		case clk:
			HAL_GPIO_WritePin(CLK_GPIO_PORT, CLK_PIN, GPIO_PIN_SET);
			break;
	}
}
void Reset(uint8_t pin)
{
	switch(pin)
	{
		case io0:
			HAL_GPIO_WritePin(IO0_GPIO_PORT, IO0_PIN, GPIO_PIN_RESET);
			break;
		case io1:
			HAL_GPIO_WritePin(IO1_GPIO_PORT, IO1_PIN, GPIO_PIN_RESET);
			break;
		case io2:
			HAL_GPIO_WritePin(IO2_GPIO_PORT, IO2_PIN, GPIO_PIN_RESET);
			break;
		case io3:
			HAL_GPIO_WritePin(IO3_GPIO_PORT, IO3_PIN, GPIO_PIN_RESET);
			break;
		case cs:
			HAL_GPIO_WritePin(CS_GPIO_PORT, CS_PIN, GPIO_PIN_RESET);
			break;
		case clk:
			HAL_GPIO_WritePin(CLK_GPIO_PORT, CLK_PIN, GPIO_PIN_RESET);
			break;
	}
}

/* */
void QSPI_Recieve_Init(void)
{
	/* PB0 (IO1), PB1 (IO0) */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* PF6 (IO3), PF7 (IO2) */
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
void QSPI_Transmit_Init(void)
{
	/* PB0 (IO1), PB1 (IO0) */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/* PF6 (IO3), PF7 (IO2) */
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
void Single_Mode(void)
{
	/* PB1 (IO0) */
	GPIO_InitStruct.Pin = IO0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(IO0_GPIO_PORT, &GPIO_InitStruct);
	
	/* PB0 (IO1) */
	GPIO_InitStruct.Pin = IO1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(IO1_GPIO_PORT, &GPIO_InitStruct);
	
	/* PF7 (IO2) */
	GPIO_InitStruct.Pin = IO2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(IO2_GPIO_PORT, &GPIO_InitStruct);
}

/* Single mode SPI functions */

/* Byte transmit function */
void SPI_Byte_T(uint8_t byte)
{
	for(uint8_t i=0; i<8; i++)
	{
		if(0x80 & byte)
		{
			Set(io0);
		}
		Set(clk);
		Reset(io0);	
		byte=(byte<<1);
		Reset(clk);	
	}	
}
/* 32 bit transmit function */
void SPI_32bit_T(uint32_t byte4)
{
	for(uint8_t i=0; i<32; i++)
	{
		if(0x80000000 & byte4)
		{
			Set(io0);
		}
		Set(clk);
		Reset(io0);
		Reset(clk);	
		byte4=(byte4<<1);
	}	
}
/* Send instruction */
void SPI_Instruction(uint8_t cmd)
{
	SPI_Byte_T(cmd);
	
}
/* Dummy cycles */
void SPI_Dummy(uint8_t n) 	// n - number of dummy cycles
{
	for(uint8_t i=0; i<(n*16); i++)
	{
		HAL_GPIO_TogglePin(CLK_GPIO_PORT, CLK_PIN);
	}
}
/* Send 24 bit address */
void SPI_Address(uint32_t addr)
{
	uint8_t byte=0;
	
	for(uint8_t e=0; e<3; e++)
	{
		byte=(addr >> (8 * (2-e)));
		SPI_Byte_T(byte);
	}
}
/* Send data array */
void SPI_Data(uint8_t* data, uint32_t size)
{
	for(uint32_t e=0; e<size; e++)
	{
		SPI_Byte_T(data[e]);
	}
}
/* Check busy*/
void SPI_Check_Busy(void)
{
	while( SPI_Read_SR(1)&0x01 )
	{
		HAL_Delay(0);
	}
}
/* Transmit data array function */
void SPI_Transmit(uint8_t* data, uint32_t address, uint32_t size)
{
	Reset(cs);
	SPI_Instruction(write_enable);
	Set(cs);
	SPI_Dummy(1);
	
	Reset(cs);
	SPI_Instruction(page_program);
	SPI_Address(address);
	SPI_Data(data, size);
	Set(cs);
	SPI_Dummy(1);
	
	SPI_Check_Busy();
}
/* Byte receive function */
uint8_t SPI_Byte_R(void)
{
	uint8_t byte=0;
	for(uint8_t i=0; i<8; i++)
	{
		if (HAL_GPIO_ReadPin(IO1_GPIO_PORT, IO1_PIN)!=0) byte|=0x01;
		Set(clk);
		if (i<7) byte=(byte<<1);
		Reset(clk);
	}
	return byte;
}
void SPI_Array_R(uint8_t* arr, uint32_t size)
{
	for(uint32_t e=0; e<size; e++)
	{
		arr[e]=SPI_Byte_R();
	}
}
void SPI_Receive(uint8_t* arr, uint32_t address, uint32_t size)
{
	Reset(cs);
	SPI_Instruction(read_data);
	SPI_Address(address);
	SPI_Array_R(arr, size);
	
	Set(cs);

	SPI_Check_Busy();
}
void SPI_Receive_ID(uint8_t* arr)
{
		Reset(cs);
		SPI_Instruction(device_id);
		SPI_Dummy(3);
		SPI_Array_R(arr, 3);
		Set(cs);

		SPI_Check_Busy();
}
/* Read manufacturer & ID */
void SPI_Manuf_ID(uint8_t* arr)
{
		Reset(cs);
		SPI_Instruction(manuf_id);
		SPI_Dummy(2);
		SPI_Byte_T(0);
		SPI_Array_R(arr, 2);
		Set(cs);

		SPI_Check_Busy();
}
/* Full chip erase function */
void SPI_Chip_Erase(void)
{
	Reset(cs);
	SPI_Instruction(write_enable);
	Set(cs);
	SPI_Check_Busy();
	
	Reset(cs);
	SPI_Instruction(chip_erase);
	Set(cs);
	SPI_Check_Busy();
	
	Reset(cs);
	SPI_Instruction(write_disable);
	Set(cs);
	
	SPI_Check_Busy();
}
/* Read status register */
uint8_t SPI_Read_SR(uint8_t sr)
{
	uint8_t reg;
	
	switch(sr)
	{
		case 1:
			Reset(cs);
			SPI_Instruction(0x05);
			reg=SPI_Byte_R();
			Set(cs);
			break;
		case 2:
			Reset(cs);
			SPI_Instruction(0x35);
			reg=SPI_Byte_R();
			Set(cs);
			break;
		case 3:
			Reset(cs);
			SPI_Instruction(0x15);
			reg=SPI_Byte_R();
			Set(cs);
			break;
		default:
			break;

	}
	return reg;

	SPI_Check_Busy();
}
/* Quad mode QSPI functions 
*
*/
/* Recieve byte in quad mode  */
uint8_t QSPI_Byte_R(void)
{
	uint8_t byte=0;
	for(uint8_t i=0; i<2; i++)
	{
		if (HAL_GPIO_ReadPin(IO0_GPIO_PORT, IO0_PIN)!=0) byte|=0x01;
		if (HAL_GPIO_ReadPin(IO1_GPIO_PORT, IO1_PIN)!=0) byte|=0x02;
		if (HAL_GPIO_ReadPin(IO2_GPIO_PORT, IO2_PIN)!=0) byte|=0x04;
		if (HAL_GPIO_ReadPin(IO3_GPIO_PORT, IO3_PIN)!=0) byte|=0x08;
		Set(clk);
		if (i==0) byte=(byte<<4);
		Reset(clk);
	}
	return byte;
}
/* Recieve 16 bit in quad mode  */
uint16_t QSPI_16_R(void)
{
	uint16_t byte=0;
	for(uint8_t i=0; i<4; i++)
	{
		if (HAL_GPIO_ReadPin(IO0_GPIO_PORT, IO0_PIN)!=0) byte|=0x01;
		if (HAL_GPIO_ReadPin(IO1_GPIO_PORT, IO1_PIN)!=0) byte|=0x02;
		if (HAL_GPIO_ReadPin(IO2_GPIO_PORT, IO2_PIN)!=0) byte|=0x04;
		if (HAL_GPIO_ReadPin(IO3_GPIO_PORT, IO3_PIN)!=0) byte|=0x08;
		Set(clk);
		if (i<3) byte=(byte<<4);
		Reset(clk);
	}
	return byte;
}
/* Recieve 32 bit in quad mode  */
uint32_t QSPI_32_R(void)
{
	uint32_t byte=0;
	for(uint8_t i=0; i<8; i++)
	{
		if (HAL_GPIO_ReadPin(IO0_GPIO_PORT, IO0_PIN)!=0) byte|=0x01;
		if (HAL_GPIO_ReadPin(IO1_GPIO_PORT, IO1_PIN)!=0) byte|=0x02;
		if (HAL_GPIO_ReadPin(IO2_GPIO_PORT, IO2_PIN)!=0) byte|=0x04;
		if (HAL_GPIO_ReadPin(IO3_GPIO_PORT, IO3_PIN)!=0) byte|=0x08;
		Set(clk);
		if (i<7) byte=(byte<<4);
		Reset(clk);
	}
	return byte;
}
/* Send byte in quad mode */
void QSPI_Byte_T(uint8_t byte)
{
	for(uint8_t i=0; i<2; i++)
	{
		if(0x80 & byte)	Set(io3);
		if(0x40 & byte)	Set(io2);
		if(0x20 & byte)	Set(io1);
		if(0x10 & byte)	Set(io0);

		Set(clk);
		Reset(io3);	Reset(io2);	Reset(io1);	Reset(io0);	
		byte=(byte<<4);
		Reset(clk);	
	}	
}
/* Send 16 bit in quad mode */
void QSPI_16_T(uint16_t data)
{
	for(uint8_t i=0; i<4; i++)
	{
		if(0x8000 & data)	Set(io3);
		if(0x4000 & data)	Set(io2);
		if(0x2000 & data)	Set(io1);
		if(0x1000 & data)	Set(io0);

		Set(clk);
		Reset(io3);	Reset(io2);	Reset(io1);	Reset(io0);	
		data=(data<<4);
		Reset(clk);	
	}	
}
/* Send 32 bit in quad mode */
void QSPI_32_T(uint32_t data)
{
	for(uint8_t i=0; i<8; i++)
	{
		if(0x80000000 & data)	Set(io3);
		if(0x40000000 & data)	Set(io2);
		if(0x20000000 & data)	Set(io1);
		if(0x10000000 & data)	Set(io0);

		Set(clk);
		Reset(io3);	Reset(io2);	Reset(io1);	Reset(io0);	
		data=(data<<4);
		Reset(clk);	
	}	
}
/* Dummy cycles in Quad Mode */
void QSPI_Dummy(uint8_t n) 	// n - number of dummy cycles
{
	for(uint8_t i=0; i<(n*4); i++)
	{
		HAL_GPIO_TogglePin(CLK_GPIO_PORT, CLK_PIN);
	}
}
/*	Array read in quad mode */
void QSPI_Array_R(uint8_t* arr, uint32_t size)
{
	for(uint32_t e=0; e<size; e++)
	{
		arr[e]=QSPI_Byte_R();
	}
}
/* Address send in quad mode  */
void QSPI_Address(uint32_t addr)	// hasn't worked yet
{
	uint8_t byte=0;
	
	for(uint8_t e=0; e<3; e++)
	{
		byte=(addr >> (8 * (2-e)));
		QSPI_Byte_T(byte);
	}
}
/* Send data array in quad mode */
void QSPI_Data(uint8_t* data, uint32_t size)
{
	for(uint32_t e=0; e<size; e++)
	{
		QSPI_Byte_T(data[e]);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* ??????? QSPI_Recieve_IO ? QSPI_Recieve_O ?????????? ?????? ???????? ???????? ?????? 
		? _IO ????? ???????????? ?? 4 ?????, ? ? _O ??????????????? ????? IO0
*/

/* Read byte array from memory in quad mode */
void QSPI_Recieve_IO(uint8_t* arr, uint32_t address, uint32_t size)		// be aware that this function reconfigurates GPIO
{
	QSPI_Transmit_Init();	
	Reset(cs);
	SPI_Instruction(fastread_quad_io);
	QSPI_Address(address);
	QSPI_Dummy(3);	
	
	QSPI_Recieve_Init();
	QSPI_Array_R(arr, size);	
	Set(cs);

	Single_Mode();
	SPI_Check_Busy();
}
/* Read byte array from memory in quad mode */
void QSPI_Recieve_O(uint8_t* arr, uint32_t address, uint32_t size)		// be aware that this function reconfigurates GPIO
{
	QSPI_Transmit_Init();	
	Reset(cs);
	SPI_Instruction(fastread_quad_o);
	SPI_Address(address);	
	QSPI_Dummy(4);
	
	QSPI_Recieve_Init();
	QSPI_Array_R(arr, size);	
	Set(cs);

	Single_Mode();
	SPI_Check_Busy();
}
/* Send byte array to memory in quad mode */
void QSPI_Transmit(uint8_t* data, uint32_t address, uint32_t size)
{
	Reset(cs);
	SPI_Instruction(write_enable);
	Set(cs);

	QSPI_Transmit_Init();	
	
	Reset(cs);
	SPI_Instruction(q_page_program);
	SPI_Address(address);
	
	for(uint32_t e=0; e<size; e++) QSPI_Byte_T(data[e]);
	
	Set(cs);
	
	Single_Mode();
	SPI_Check_Busy();
}
/* ???? ??????? ??? 16 ? 32 ??? */
/* Read 16 bit array from memory in quad mode */
void QSPI_Recieve_IO_16(uint16_t* arr, uint32_t address, uint32_t size)		// be aware that this function reconfigurates GPIO
{
	QSPI_Transmit_Init();	
	Reset(cs);
	SPI_Instruction(fastread_quad_io);
	QSPI_Address(address);
	QSPI_Dummy(3);	
	
	QSPI_Recieve_Init();
	for(uint32_t e=0; e<size; e++) arr[e]=QSPI_16_R();
	Set(cs);

	Single_Mode();
	SPI_Check_Busy();
}
/* Read 16 bit array from memory in quad mode */
void QSPI_Recieve_O_16(uint16_t* arr, uint32_t address, uint32_t size)		// be aware that this function reconfigurates GPIO
{
	QSPI_Transmit_Init();	
	Reset(cs);
	SPI_Instruction(fastread_quad_o);
	SPI_Address(address);	
	QSPI_Dummy(4);
	
	QSPI_Recieve_Init();
	for(uint32_t e=0; e<size; e++) arr[e]=QSPI_16_R();
	Set(cs);

	Single_Mode();
	SPI_Check_Busy();
}
/* Send 16 bit array to memory in quad mode */
void QSPI_Transmit_16(uint16_t* data, uint32_t address, uint32_t size)		// hasn't worked yet
{
	Reset(cs);
	SPI_Instruction(write_enable);
	Set(cs);

	QSPI_Transmit_Init();	
	
	Reset(cs);
	SPI_Instruction(q_page_program);
	SPI_Address(address);
	for(uint32_t e=0; e<size; e++) QSPI_16_T(data[e]);
	Set(cs);
	
	Single_Mode();
	SPI_Check_Busy();
}
/* Read 32 bit array from memory in quad mode */
void QSPI_Recieve_IO_32(uint32_t* arr, uint32_t address, uint32_t size)		// be aware that this function reconfigurates GPIO
{
	QSPI_Transmit_Init();	
	Reset(cs);
	SPI_Instruction(fastread_quad_io);
	QSPI_Address(address);
	QSPI_Dummy(3);	
	
	QSPI_Recieve_Init();
	for(uint32_t e=0; e<size; e++) arr[e]=QSPI_32_R();
	Set(cs);

	Single_Mode();
	SPI_Check_Busy();
}
/* Read 32 bit array from memory in quad mode */
void QSPI_Recieve_O_32(uint32_t* arr, uint32_t address, uint32_t size)		// be aware that this function reconfigurates GPIO
{
	QSPI_Transmit_Init();	
	Reset(cs);
	SPI_Instruction(fastread_quad_o);
	SPI_Address(address);	
	QSPI_Dummy(4);
	
	QSPI_Recieve_Init();
	for(uint32_t e=0; e<size; e++) arr[e]=QSPI_32_R();
	Set(cs);

	Single_Mode();
	SPI_Check_Busy();
}
/* Send 32 bit array to memory in quad mode */
void QSPI_Transmit_32(uint32_t* data, uint32_t address, uint32_t size)  // hasn't worked yet
{
	Reset(cs);
	SPI_Instruction(write_enable);
	Set(cs);

	QSPI_Transmit_Init();	
	
	Reset(cs);
	SPI_Instruction(q_page_program);
	SPI_Address(address);
	for(uint32_t e=0; e<size; e++) QSPI_32_T(data[e]);
	Set(cs);
	
	Single_Mode();
	SPI_Check_Busy();
}
