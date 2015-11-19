enum{GREEN = 0, RED = 1}; //enumerates colors GREEN and RED for easier understanding in programming
char button_1 = 12;  //pin 12 & pin A4 as buttons
char button_2 = A4;
char  love_shape_pattern_one_color[8] = {0x18,0x3c,0x7e,0xff,0xff,0xff,0xff,0x66}; //pattern of "Heart" shape in one color.
char  love_shape_pattern_two_color[8] = {0x1e,0x3f,0x7f,0xfe,0xfe,0x7f,0x3f,0x1e}; //pattern of "Heart" shape in two color.

//patterns for demonstrating effect of expanding and shrinking box.
char  expand_shrink_pattern[7][9] = {
                                    {0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,'\0'},
				    {0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,'\0'},
				    {0x00,0x00,0x00,0x00,0x0f,0x0f,0x0f,0x0f,'\0'},
				    {0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,'\0'},											
				    {0x00,0x00,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,'\0'},
				    {0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,'\0'},
                                    {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,'\0'} 
                                   };
char  number_alphabet[8];  //array for storing alphabet or number chosen.
char  mode = 0;  //variable for mode, default is Mode 0.
void setup()
{
  DDRB = DDRB | 0b00001111; //pin PORTB0 and PORTB3 outputs.
  DDRC = DDRC | 0b00001111; //pin PORTC0 and PORTC3 outputs.
  DDRD = DDRD | 0b11111111; //PORTD as outputs.
  pinMode(button_1,INPUT);  //button_1 as input.
  pinMode(button_2,INPUT);  //button_2 as input.
  digitalWrite(button_1,HIGH);  //pull up pin button_1
  digitalWrite(button_2,HIGH);  //pull up pin button_2
  delay(1000);  //delay 1s for pull up process
  while(digitalRead(button_2)) //While button_2 is not pressed, users can select mode by pressing SW1.
  {
    if(!digitalRead(button_1))
    {
	while(!digitalRead(button_1));
	mode++;
	if(mode>6)
	{
	  mode = 0;
	}
    }
    
    switch(mode) //The dot matrix will display the current mode selected in green color.
    {
      case 0: light_a_number_alphabet('0',GREEN); 
              break;
      case 1: light_a_number_alphabet('1',GREEN); 
  	      break;
      case 2: light_a_number_alphabet('2',GREEN); 
  	      break;
      case 3: light_a_number_alphabet('3',GREEN); 
 	      break;
      case 4: light_a_number_alphabet('4',GREEN); 
  	      break;
      case 5: light_a_number_alphabet('5',GREEN); 
  	      break;
      case 6: light_a_number_alphabet('6',GREEN); 
 	      break;
      default:break;
    }
   }
  while(!digitalRead(button_2));
}

void loop()
{
    //The desired mode will be executed continuously.
    //To executed other modes, press the RESET button of BBFUINO, press Button 1 select desired mode and press the Button 2 to execute it. 
    switch(mode)
    {
      case 0: running_dot(GREEN);
	      break;
      case 1: running_line(GREEN);
	      break;
      case 2: light_pattern_one_color(love_shape_pattern_one_color,GREEN);
	      break;
      case 3: light_pattern_one_color(love_shape_pattern_one_color,GREEN);
	      light_pattern_one_color(love_shape_pattern_one_color,RED);
	      break;
      case 4: light_pattern_two_color(love_shape_pattern_two_color,RED,GREEN);
	      break;
      case 5: running_string("CYTRON",GREEN);
	      break;
      case 6: expand_shrink_square(GREEN);
	      break;
      default: break;
    }	
}


/***************************************************
Name: void light_a_dot(char row, char column, boolean color)
Function: Light up a dot in color chosen located at particular row and column.
Arguments: row - row of the dot.
		   column - column of the dot.
		   color - color of the dot.
Example: light_a_dot(0,0,GREEN);	//light up the dot located at row 1, column 1 of the dot matrix display in green color.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
***************************************************/
void light_a_dot(char  row, char  column, boolean color)
{
  PORTD = 1<<column;
  if(color == GREEN)
  {
     PORTC = PORTC & 0xF0;
     PORTB = (PORTB&0xF0)| 0b00001000 | row;
  }
  else if(color == RED)
  {
     PORTB = PORTB & 0xF0;
     PORTC = (PORTC&0xF0)| 0b00001000 | row;
  }
}

/***************************************************
Name: void light_a_row(char row, boolean color)
Function: Light up a row of dots in color chosen located at particular row.
Arguments: row - row to be lighted up.
		   color - color of the row lighted up.
Example: light_a_row(0,GREEN);	//light up row of dots located at row 1 of the dot matrix display in green color.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
***************************************************/
void light_a_row(char  row, boolean color)
{
  PORTD = 0xFF;
  if(color == GREEN)
  {
     PORTC = PORTC & 0xF0;
     PORTB = (PORTB&0xF0)| 0b00001000 | row;
  }
  else if(color == RED)
  {
     PORTB = PORTB & 0xF0;
     PORTC = (PORTC&0xF0)| 0b00001000 | row;
  } 
}

/***************************************************
Name: void light_a_column(char column, boolean color)
Function: Light up a column of dots in color chosen located at particular column.
Arguments: column - column to be lighted up.
		   color - color of the column lighted up.
Example: light_a_column(0,GREEN);	//light up column of dots located at column 1 of the dot matrix display in green color.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
***************************************************/
void light_a_column(char  column, boolean color)
{
  for(int i = 0; i<8; i++)
  {
     light_a_dot(i,column,color); 
  }
}

/***************************************************
Name: void light_all_dot(boolean color)
Function: Light up all dots of dot matrix display in color chosen (by light up row by row in sequence rapidly in a continuos way)
Arguments: color - color of dots.
Example: light_all_dot(GREEN);	//light up all dots of dot matrix display in green color.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
***************************************************/
void light_all_dot(boolean color)
{
  for(int i = 0; i<8; i++)
  {
     light_a_row(i,color); 
  }
}

/***************************************************
Name: void light_all_dot_2(boolean color)
Function: Light up all dots of dot matrix display in color chosen (by light up dot by dot in sequence rapidly in a continuos way)
Arguments: color - color of dots.
Example: light_all_dot_2(GREEN);	//light up all dots of dot matrix display in green color.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
***************************************************/
void light_all_dot_2(boolean color)
{
	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			light_a_dot(i,j,color);
		}
	}
}

/***************************************************
Name: void light_pattern_one_color(char pattern[8], boolean color)
Function: Light up a pattern in color chosen.
Arguments: pattern - pattern to be displayed on the dot matrix display.
		   color - color of the pattern.
Example: light_pattern_one_color(pattern, GREEN);	//light up user-defined pattern on the dot matrix display in green color.
Note: 1.Users may need to decalre an array of size 8 and initialize it with pattern to be displayed. 
      2.The index starts from 0 to indicate first row or first coulumn in programming.
For eg: if users desired to display "C" pattern as shown below,
			    By taking 0 as and * as 1	Reverse it since (Column 8 is connected to MSB of PORTD)	Change to hex
row 1 * * * * * * * *	--> 11111111 			0b11111111							0xff
    2 * * * * * * * *   --> 11111111 			0b11111111							0xff
    3 *	* 0 0 0 0 0 0   --> 11000000			0b00000011							0x03
    4 *	* 0 0 0 0 0 0	--> 11000000	                0b00000011							0x03
    5 *	* 0 0 0 0 0 0   --> 11000000                    0b00000011						        0x03
    6 * * 0 0 0 0 0 0   --> 11000000  			0b00000011						        0x03
    7 * * * * * * * *   --> 11111111			0b11111111							0xff
    8 * * * * * * * *   --> 11111111			0b11111111						        0xff
col   1 2 3 4 5 6 7 8 

Fill up the array with the pattern starts from row 8, then proceed untill row 1:
	char array[8] = {0xff,0xff,0x03,0x03,0x03,0x03,0xff,0xff};
Then call subfunction like this:
	light_pattern_one_color(array, GREEN);
***************************************************/
void light_pattern_one_color(char  pattern[8], boolean color)
{
  for(int i = 0; i<8 ; i++)
  {
      PORTD = pattern[7-i];
      if(color == GREEN)
      {
         PORTC = PORTC & 0xF0;
         PORTB = (PORTB&0xF0)| 0b00001000 | i;
      }
      else if(color == RED)
      {
         PORTB = PORTB & 0xF0;
         PORTC = (PORTC&0xF0)| 0b00001000 | i;
      } 
      delay(1);
  }
}

/***************************************************
Name: void light_a_column_two_color(char column, char column_pattern, boolean color_0, boolean color_1)
Function: Light up a column in two colors.
Arguments: column - column to be lighted up. 
		   pattern - pattern to be lighted up at the column chosen.
		   color_0 - color for bit 0.
		   color_1 - color for bit 1.		
Example: light_a_column_two_color(0,pattern, GREEN, RED);	//light up user-defined pattern at column 1 of the dot matrix display. 
								//green color for bit 0, red color for bit 1.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
For eg: if users desired to display pattern as shown below,
			  By taking G as bit 0 and R as bit 1	(G symbolize green, R symbolize red)	
row 1 R 		  --> 1						
    2 R    		  --> 1 						
    3 R	   		  --> 1						
    4 G			  --> 0	                    
    5 G	   		  --> 0                        
    6 G    		  --> 0  						
    7 R   		  --> 1						
    8 R    		  --> 1						
col   1 2 3 4 5 6 7 8 
The MSB is row 8, hence the column 1 pattern is 0b11000111, 0xc7 in hex.
Then, the subfunction can be called like this:
	light_a_column_two_color(0, 0xc7, GREEN, RED);
***************************************************/
void light_a_column_two_color(char  column, char  column_pattern, boolean color_0, boolean color_1)
{
  char  lsb_tester = 0;
  PORTD = 1<<column;
  for(int i = 7; i>=0; i--)
  {
     lsb_tester = (column_pattern >> i) & 0x01;
     if(lsb_tester)
     {
       light_a_dot(i,column,color_1);
     }
     
     else
     {
       light_a_dot(i,column,color_0);
     } 
  }
}

/***************************************************
Name: void light_pattern_two_color(char pattern[8], boolean color_0, boolean color_1)
Function: Light up a pattern in two colors.
Arguments: pattern - pattern to be displayed on the dot matrix display.
           color_0 - color for bit 0.
           color_1 - color for bit 1.		
Example: light_pattern_two_color(pattern, GREEN, RED);	//light up user-defined pattern on the dot matrix display.
							//green color for bit 0, red color for bit 1.
Note: The index starts from 0 to indicate first row or first coulumn in programming.
For eg: if users desired to display pattern as shown below ('C' character in red color with yellow background)

				By taking G as bit 0 and R as bit 1	(G symbolize green, R symbolize red)	
row 1  R R R R R R R R 		--> 1 1 1 1 1 1 1 1						
    2  R R R R R R R R   	--> 1 1 1 1 1 1 1 1					
    3  R R G G G G G G   	--> 1 1	0 0 0 0 0 0 				
    4  R R G G G G G G 		--> 1 1 0 0 0 0 0 0                  
    5  R R G G G G G G  	--> 1 1 0 0 0 0 0 0                    
    6  R R G G G G G G   	--> 1 1 0 0 0 0 0 0					
    7  R R R R R R R R  	--> 1 1 1 1 1 1 1 1 					
    8  R R R R R R R R   	--> 1 1 1 1 1 1 1 1
					
col	  1 2 3 4 5 6 7 8 

The MSB is row 8, hence 
The column 1 pattern is 0b11111111, 0xff in hex.
The column 2 pattern is 0b11111111, 0xff in hex.
The column 3 pattern is 0b11000011, 0xc3 in hex.
The column 4 pattern is 0b11000011, 0xc3 in hex.
The column 5 pattern is 0b11000011, 0xc3 in hex.
The column 6 pattern is 0b11000011, 0xc3 in hex.
The column 7 pattern is 0b11000011, 0xc3 in hex.
The column 8 pattern is 0b11000011, 0xc3 in hex.

Fill up the array with the pattern starts from column 1, then proceed untill column 8:
char array[8] = {0xff,0xff,0xc3,0xc3,0xc3,0xc3,0xff,0xff};
Then, the subfunction can be called like this:
	light_pattern_two_color(array, GREEN, RED);
***************************************************/
void light_pattern_two_color(char  pattern[8],boolean color_0,boolean color_1)
{
  for(int i = 0; i<8; i++)
  {
    for(int time = 0; time<5; time++)
      light_a_column_two_color(i,pattern[i],color_0,color_1);
  }
}

/***************************************************
Name: void running_dot(boolean color)
Function: Effect of a dot running throughout the dot matrix display.
Arguments: color - color of dot
Example: running_dot(GREEN);	//a green dot running throughout the dot matrix display.
***************************************************/
void running_dot(boolean color)
{
	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			light_a_dot(i,j,color);
			delay(50);
		}
	}
}

/***************************************************
Name: void running_line(boolean color)
Function: Effect of a row of dots running throughout the dot matrix display.
Arguments: color - color of dots
Example: running_line(GREEN);	//a row of green dots running throughout the dot matrix display up and down.
***************************************************/
void running_line(boolean color)
{
	for(int i = 0; i<8; i++)
	{
		light_a_row(i,color);
		delay(100);
	}
	
	for(int i = 7; i>=0; i--)
	{
		light_a_row(i,color);
		delay(100);
	}
}

/***************************************************
Name: void choose_num_alphabet(char num_alp, char num_alp_array[8])
Function: Choose pattern of one of the alphabets (A-Z(capital letters)) or one of digits (0-9) to be displayed on the dot matrix display.
Arguments: num_alp - alphabet or digit chosen.
		   num_alp - array to stored alphabet or digit chosen.
Example: choose_num_alphabet('A',array);	//choose the 'A' pattern and store it in an array.
		 choose_num_alphabet('0',array);	//choose the '0' pattern and store it in an array.
***************************************************/
void choose_num_alphabet(char  num_alp, char  num_alp_array[8])
{
	switch(num_alp)
	{
		case 'A':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xc3;
				  num_alp_array[2] = 0xff;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xe7;
				  num_alp_array[6] = 0x7e;
				  num_alp_array[7] = 0x3c;
				  break;

		case 'B':         num_alp_array[0] = 0x3f;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0x3f;
				  break;

		case 'C':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0x03;
				  num_alp_array[3] = 0x03;
                                  num_alp_array[4] = 0x03;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'D':         num_alp_array[0] = 0x3f;
				  num_alp_array[1] = 0x7f;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xc3;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0x7f;
				  num_alp_array[7] = 0x3f;
				  break;

		case 'E':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0x03;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'F':         num_alp_array[0] = 0x03;
				  num_alp_array[1] = 0x03;
				  num_alp_array[2] = 0x03;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'G':         num_alp_array[0] = 0xfe;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xf3;
                                  num_alp_array[4] = 0xf3;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xfe;
				  num_alp_array[7] = 0xfc;
				  break;
					
		case 'H':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xc3;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'I':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0x18;
				  num_alp_array[3] = 0x18;
                                  num_alp_array[4] = 0x18;
				  num_alp_array[5] = 0x18;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'J':         num_alp_array[0] = 0x1e;
				  num_alp_array[1] = 0x3f;
				  num_alp_array[2] = 0x33;
				  num_alp_array[3] = 0x33;
                                  num_alp_array[4] = 0x30;
				  num_alp_array[5] = 0x30;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'K':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0x63;
				  num_alp_array[2] = 0x33;
				  num_alp_array[3] = 0x1f;
                                  num_alp_array[4] = 0x1f;
				  num_alp_array[5] = 0x33;
				  num_alp_array[6] = 0x63;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'L':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0x03;
				  num_alp_array[3] = 0x03;
                                  num_alp_array[4] = 0x03;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0x03;
				  num_alp_array[7] = 0x03;
				  break;

		case 'M':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xc3;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xc3;
                                  num_alp_array[4] = 0xdb;
				  num_alp_array[5] = 0xff;
				  num_alp_array[6] = 0xe7;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'N':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xe3;
				  num_alp_array[2] = 0xf3;
				  num_alp_array[3] = 0xfb;
                                  num_alp_array[4] = 0xdf;
				  num_alp_array[5] = 0xcf;
				  num_alp_array[6] = 0xc7;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'O':         num_alp_array[0] = 0x3c;
				  num_alp_array[1] = 0x7e;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xc3;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0x7e;
				  num_alp_array[7] = 0x3c;
				  break;

		case 'P':         num_alp_array[0] = 0x03;
				  num_alp_array[1] = 0x03;
				  num_alp_array[2] = 0x7f;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0x7f;
				  break;

		case 'Q':         num_alp_array[0] = 0xde;
				  num_alp_array[1] = 0x7f;
				  num_alp_array[2] = 0xf3;
				  num_alp_array[3] = 0xdb;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0x7e;
				  num_alp_array[7] = 0x3c;
				  break;

		case 'R':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xe3;
				  num_alp_array[2] = 0x73;
				  num_alp_array[3] = 0x7f;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0x7f;
				  break;

		case 'S':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc0;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'T':         num_alp_array[0] = 0x18;
				  num_alp_array[1] = 0x18;
				  num_alp_array[2] = 0x18;
				  num_alp_array[3] = 0x18;
                                  num_alp_array[4] = 0x18;
				  num_alp_array[5] = 0x18;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case 'U':         num_alp_array[0] = 0x7e;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xc3;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'V':         num_alp_array[0] = 0x18;
				  num_alp_array[1] = 0x3c;
				  num_alp_array[2] = 0x66;
				  num_alp_array[3] = 0xe7;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'W':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xe7;
				  num_alp_array[2] = 0xff;
				  num_alp_array[3] = 0xdb;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'X':         num_alp_array[0] = 0xc3;
				  num_alp_array[1] = 0xc3;
				  num_alp_array[2] = 0x66;
				  num_alp_array[3] = 0x3c;
                                  num_alp_array[4] = 0x3c;
				  num_alp_array[5] = 0x66;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'Y':         num_alp_array[0] = 0x18;
				  num_alp_array[1] = 0x18;
				  num_alp_array[2] = 0x18;
				  num_alp_array[3] = 0x18;
                                  num_alp_array[4] = 0x3c;
				  num_alp_array[5] = 0x66;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;
				  break;

		case 'Z':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0x0e;
				  num_alp_array[3] = 0x1c;
                                  num_alp_array[4] = 0x38;
				  num_alp_array[5] = 0x70;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;
		case '0':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xc3;
                                  num_alp_array[4] = 0xc3;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;	
				  break;
		case '1':         num_alp_array[0] = 0x18;
				  num_alp_array[1] = 0x18;
				  num_alp_array[2] = 0x18;
				  num_alp_array[3] = 0x18;
                                  num_alp_array[4] = 0x18;
				  num_alp_array[5] = 0x18;
				  num_alp_array[6] = 0x18;
				  num_alp_array[7] = 0x18;	
				  break;

		case '2':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0x03;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc0;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;	
				  break;

		case '3':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc0;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc0;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;	
				  break;
	
		case '4':         num_alp_array[0] = 0xc0;
				  num_alp_array[1] = 0xc0;
				  num_alp_array[2] = 0xc0;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xc3;
				  num_alp_array[7] = 0xc3;	
				  break;

		case '5':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc0;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case '6':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0x03;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case '7':         num_alp_array[0] = 0xc0;
				  num_alp_array[1] = 0xc0;
				  num_alp_array[2] = 0xc0;
				  num_alp_array[3] = 0xc0;
                                  num_alp_array[4] = 0xc0;
				  num_alp_array[5] = 0xc0;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case '8':         num_alp_array[0] = 0xff;
				  num_alp_array[1] = 0xff;
				  num_alp_array[2] = 0xc3;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;
				  break;

		case '9':         num_alp_array[0] = 0xc0;
				  num_alp_array[1] = 0xc0;
				  num_alp_array[2] = 0xc0;
				  num_alp_array[3] = 0xff;
                                  num_alp_array[4] = 0xff;
				  num_alp_array[5] = 0xc3;
				  num_alp_array[6] = 0xff;
				  num_alp_array[7] = 0xff;	
				  break;
		default:break;		  
	}
}

/***************************************************
Name: void light_a_number_alphabet(char num_alp,boolean color);
Function: Display a particular alphabet or digit in color chosen on the dot matrix display.
Arguments: num_alp - alphabet or digit to be displayed.
		   color - color in which the alphabet or the digit to be displayed.
Example: light_a_number_alphabet('A',GREEN);	//light up the 'A' pattern in green color on the dot matrix display.
		 light_a_number_alphabet('0',GREEN);	//light up the '0' pattern in green color on the dot matrix display.
***************************************************/
void light_a_number_alphabet(char  num_alp,boolean color)
{
	choose_num_alphabet(num_alp,number_alphabet);
	light_pattern_one_color(number_alphabet,color);
}

/***************************************************
Name: running_string(char* sentence,boolean color);
Function: Display each charater of a string in sequence on the dot matrix display.
Arguments: sentence - string to be displayed.
		   color - color in which the string to be displayed.
Example: running_string("CYTRON",char color);	//Display each charater of "CYTRON" in sequence on the dot matrix display. 
Note: Limited for capital letters only.
***************************************************/
void running_string(char* sentence,boolean color)
{
	for(int i = 0; sentence[i] != '\0'; i++)
	{
		for(int j = 0; j<50; j++)
			light_a_number_alphabet(sentence[i], color);
	}
}

/***************************************************
Name: void expand_shrink_square(boolean color)
Function: Effect of expanding and shrinking box on the dot matrix display.
Arguments: color - color in which the effect to be displayed.
Example: expand_shrink_square(GREEN); //Effect of expanding and shrinking box in green color on the dot matrix display	
***************************************************/
void expand_shrink_square(boolean color)
{
	for(int i = 0; i<7; i++)
		for(int j = 0; j<5; j++)
			light_pattern_one_color(expand_shrink_pattern[i],color);
	for(int i = 6; i>=0; i--)
		for(int j = 0; j<5; j++)
			light_pattern_one_color(expand_shrink_pattern[i],color);	
}
