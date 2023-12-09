#include "screen.h"

// Public Methods
void Screen::initScreen()
{
	GLCD_init();
	clearScreen();
}

void Screen::setPixel(int x, int y)
{
	// Array to determine where pixel will sit in bank.

	// Calc needed info
	size_t column_num = x;
	size_t bank_num = y / 8;
	size_t y_pixel = y % 8;

	// Apply pixel to screen
	screen[column_num][bank_num] = screen[column_num][bank_num] | pixels[y_pixel];
}

void Screen::clearScreen()
{
	GLCD_setCursor(0,0);
	for (size_t i = 0; i < GLCD_WIDTH; i++)
	{
		for(size_t j = 0; j < GLCD_HEIGHT / 8; j++)
		{
			screen[i][j] = 0x00;
		}
	}

	GLCD_clear();
}

void Screen::displayScreen(int score)
{
	GLCD_setCursor(0,0);
	for (size_t i = 0; i < GLCD_WIDTH; i++)
	{
		for(size_t j = 0; j < GLCD_HEIGHT / 8; j++)
		{
			GLCD_setCursor(i,j);
			GLCD_data_write(screen[i][j]);
		}
	}

	displayScore(score);
}

void Screen::displayGameOver(int score)
{
	while(1){
		GLCD_clear();
		// Display GAME OVER
		GLCD_setCursor(13, 2);
		GLCD_putchar(7);  // G
		GLCD_putchar(1);  // A
		GLCD_putchar(13); // M
		GLCD_putchar(5);  // E
		GLCD_putchar(0);  // space
		GLCD_putchar(15); // O
		GLCD_putchar(22); // V
		GLCD_putchar(5);  // E
		GLCD_putchar(18); // R

		// Show Score
		// To Do: Would be cool if this flashed.
		if (score == 0)
		{
			GLCD_setCursor(19, 3);
			GLCD_putchar(25);  // Y
			GLCD_putchar(15);  // O
			GLCD_putchar(21);  // U
			GLCD_putchar(0);   // space
			GLCD_putchar(23);  // W
			GLCD_putchar(15);  // O
			GLCD_putchar(14);  // N
		}
		else
		{
			GLCD_setCursor(16, 3);
			GLCD_putchar(25);  // Y
			GLCD_putchar(15);  // O
			GLCD_putchar(21);  // U
			GLCD_putchar(0);   // space
			GLCD_putchar(12);  // L
			GLCD_putchar(15);  // O
			GLCD_putchar(19);  // S
			GLCD_putchar(5);   // E
		}

	}
}

bool Screen::pixelTaken(int x, int y)
{
	// Calc needed info To Do: Make this priv functions?
	size_t column_num = x;
	size_t bank_num = y / 8;
	size_t y_pixel = y % 8;

	//screen[column_num][bank_num] = screen[column_num][bank_num] | pixels[y_pixel];
	return screen[column_num][bank_num] & pixels[y_pixel];
}

// Private Methods

void Screen::displayScore(int score)
{
	if (score <= 30)
	{
		GLCD_setCursor(72,0);
		GLCD_putnum(score / 10);
		GLCD_putnum(score % 10);
	}
}

void Screen::SPI_write(unsigned char data) {
	// Chip Enable (low is asserted)
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, GPIO_PIN_RESET);
	// Send data over SPI1
	HAL_SPI_Transmit(&hspi1,(uint8_t*) &data, 1, HAL_MAX_DELAY);
	// Chip Disable
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, GPIO_PIN_SET);
}

void Screen::GLCD_data_write(unsigned char data){
	// Switch to "data" mode (D/C pin high)
	HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);
	// Send data over SPI
	SPI_write(data);
}
void Screen::GLCD_command_write(unsigned char data){
	// Switch to "command" mode (D/C pin low)
	HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET);
	// Send data over SPI
	SPI_write(data);
}

void Screen::GLCD_init(void){
	// Keep CE high when not transmitting
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, GPIO_PIN_SET);
	// Reset the screen (low pulse - down & up)
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
	// Configure the screen (according to the datasheet)
	GLCD_command_write(0x21); // enter extended command mode
	GLCD_command_write(0xB0); // set LCD Vop for contrast (this may be adjusted)
	GLCD_command_write(0x04); // set temp coefficient
	GLCD_command_write(0x15); // set LCD bias mode (this may be adjusted)
	GLCD_command_write(0x20); // return to normal command mode
	GLCD_command_write(0x0C); // set display mode normal
}
void Screen::GLCD_setCursor(unsigned char x, unsigned char y){
	GLCD_command_write(0x80 | x); // column
	GLCD_command_write(0x40 | y); // bank
}
void Screen::GLCD_clear(void){
	int i;
	for(i = 0; i < (GLCD_WIDTH * NUM_BANKS); i++)
	{
		GLCD_data_write(0x00); // write zeros
	}
	GLCD_setCursor(0,0); // return cursor to top left
}

void Screen::GLCD_putchar(int font_table_row){
	int i;
	for (i=0; i<6; i++)
	{
		GLCD_data_write(font_table[font_table_row][i]);
	}
}

void Screen::GLCD_putnum(int font_table_row){
	int i;
	for (i=0; i<6; i++)
	{
		GLCD_data_write(number_font_table[font_table_row][i]);
	}
}
