#define cmd_enable_high    4    // en = 1, rs = 0
#define cmd_enable_low     0    // en = 0, rs = 0
#define data_enable_high   12   // en = 1, rs = 1
#define data_enable_low    8    // en = 0, rs = 1



/* -------------------------------------------------------------------- */
/*                             LCD Functions                            */
/* -------------------------------------------------------------------- */

void LCD_Init (void){	       	/* LCD Initialize function */
	delayMicroseconds(2000);		/* LCD Power ON Initialization time >15ms */
	LCD_Command (0x02);	        // 4bit mode
	LCD_Command (0x28);       	//  4bit mode 
	LCD_Command (0x0C);	        //Display ON Cursor OFF 
	LCD_Command (0x06);	        // Auto Increment cursor 
	LCD_Command (0x01);	        // Clear display
	LCD_Command (0x80);	        // Cursor at home position 
  delayMicroseconds(200);     // delay for completion of command setting
}

void LCD_Command (volatile uint8_t cmnd){
	PORTB = cmnd >> 4;           /* Send upper nibble */
	PORTD = cmd_enable_high;
	delayMicroseconds(200);
	PORTD = cmd_enable_low;
	delayMicroseconds(200);

	PORTB = cmnd & 0x0f;        /* Send lower nibble */
	PORTD = cmd_enable_high;
	delayMicroseconds(200);
	PORTD = cmd_enable_low;
	delayMicroseconds(200);
}

void LCD_Char (volatile uint8_t data)	{
	PORTB = data >> 4;          /* Send upper nibble */
	PORTD = data_enable_high;
	delayMicroseconds(200); 
	PORTD = data_enable_low;
	delayMicroseconds(200);

	PORTB = data & 0x0f;       /* Send lower nibble */
	PORTD = data_enable_high;
	delayMicroseconds(200);
	PORTD = data_enable_low;
	delayMicroseconds(200);
}

void LCD_String (volatile uint8_t *str){	/* Send string to LCD function */
	for(int i=0; str[i]!=0; i++){  /* Send each volatile uint8_t of string till the NULL */
		LCD_Char (str[i]);  /* Call LCD data write */
	}
}



/* -------------------------------------------------------------------- */
/*                             Main Functions                            */
/* -------------------------------------------------------------------- */

int main(){
  DDRD = 0x0c;  // Port D 2nd and 3rd bit set as Output
  DDRB = 0x0f;  // Port B 8th, 9th, 10th & 11th bit set as Output 

	LCD_Init();		/* Initialization of LCD*/
	LCD_String("Hello World!");  /* write string on 1st line of LCD*/
	
	while(1);		/* Infinite loop. */
	return 0;
}