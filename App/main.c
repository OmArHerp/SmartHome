/*
 * SmartHome.c
 *
 * Created: 12/17/2022 4:05:05 PM
 * Author : Dell
 */ 


/***************************************************************INCLUDE*************************************************************************/
#include "Includes.h"
/***************************************************************PROTOTYPES_FUNCTIONS************************************************************/
void LCD_Welcome(void);
void ADC_ISR(void);
void TimerISR(void);
void X_ISR(void);
/***************************************************************GLOBAL_VARIABLES****************************************************************/
//void LCD_EEPROM_AdminMode(u8 Admin);
u16 Gloable_u16_ADC_Reading =0 ;
u16 Gloable_u16_Analog_MV ;
u8  Gloable_u8_temp        ;
u8  Gloable_u8_AC_Flag       ;
u8 static Local_u8_Admin = 0; /*while it's a 0 no admin has been entered just yet*/
u8 static Local_u8_Error = 0;
u8 Local_u8_Variable6 =0;
u8  Local_u8_Variable13 ;

/**************************************************************************************************************************************************/

int main(void)
{
	
	/*****************************************************INITS***********************************************************/
	//H_KeyPad_Init();
	H_Lcd_Init();
	H_Buzzer_Init();
	HC05_Init();
	H_H_Bridge_Init();
	M_ADC_INIT();
	H_H_Bridge_Init();
	TIMER1_Init();
	M_Timer1_CallBackFn(TimerISR);
	TIMER0_Init();
	TIMER0_SetCompVal(2);
	M_EXTI_Init();
	M_Dio_PinMode(PB3,OUTPUT);
	M_GIE_EnableGlobal();
	H_Led_Init(LED0);
	H_Led_Init(LED1);
	H_Led_Init(LED2);
	H_Led_Init(LED3);
	H_Led_Init(LED4);
	H_KeyPad_Init();
    M_EXTI_CallBack(INT0,X_ISR);

	/*************************************************LOCAL_VARIABLES*******************************************************/
	u8 Local_u8_ID = TAKE_ID;
	u8 Local_u8_AdminID = 0;
	u8 Local_u8_AdminCounter = 0;
	u8 Local_u8_IDAndPass[40] = {0};
	u8 Local_u8_counter = 0;
	u8 Local_u8_ForLoopcounter = 0;
	u8 static Local_u8_Trials = 3;
	u8 Local_u8_EEPROM = 0;
	u8 Local_u8_EEPROMCount = 0;
	u8 Local_u8_Variable1 =0;
	u8 Local_u8_Variable2 =0;
	u8 Local_u8_Variable3 =0;
	u8 Local_u8_Variable4 =0;
	u8 Local_u8_Variable5 =0;
// 	u8 Local_u8_Variable6 =0;
	u8 Local_u8_Variable7 =0;
	u8 Local_u8_Variable8 =0;
	u8 Local_u8_Variable9 =0;
	u8 Local_u8_Variable10 =0;
	u8 Local_u8_Variable11 =0;
	u8 Local_u8_Variable12 =0;
	u8 Local_u8_Wrong = 10;
	u8 Local_u8_Mode = ADMIN_MODE;//BY DEFAULT
	u8 Local_u8_Menu = 0 ;
	/***************************************************************CHOOSING_MODE************************************************************/
															/*
																 [WAIT FOR AN 'A']
																
																   HC-05  --> ADMIN_MODE
																   KEYPAD --> USER_MODE
																	
																						*/
																	
	LCD_Welcome();
	while(WATING_FOR_A)
	{ 
	 
		while (Local_u8_Variable13 == 0)
		{
					Local_u8_Variable5 = HC05_Rx();
					if(Local_u8_Variable5 != 0)
					break;

		}
	
		

		if(Local_u8_Variable5 == 'A' || Local_u8_Variable5 == 'a')
		{
			Local_u8_Mode = ADMIN_MODE; 
			break;
		}
		else if(Local_u8_Variable6 == 'A')
		{
			Local_u8_Mode = USER_MODE;
			break;
		}
		else
		{
			//Do Nothing
		}	
	}
	/***************************************************************REGISTER_ADMIN************************************************************/

														/*SUPPOSED TO WORK THE FIRST TIME ONLY*/
	
	
	Local_u8_EEPROM = EEPROMINT_ReadByte(FIRST_BYTE); // IF EMPTY --> THERE'S NO ADMIN JUST YET
	
	if(Local_u8_EEPROM == EMPTY)
	{
		
																		/*ID*/
																		
		UART_TxString(" The First time you need to create an admin");
		_delay_ms(DISPLAY_TIME);
		UART_Tx(NEXTLINE);
		UART_TxString(" Enter Name: ");
		UART_Tx(NEXTLINE);
		while(Local_u8_Admin == NO_ADMIN)
		{
			Local_u8_Variable3 = HC05_Rx();
			
			if((Local_u8_Variable3 == ENTER) && (Local_u8_Error == ERROR)) //IF ENTER IS PRESSED ON A BLANK SCREEN
			{
				UART_TxString(" Error please try again");
				_delay_ms(DISPLAY_TIME);
				UART_Tx(NEXTLINE);
				UART_TxString(" Enter Name: ");
				UART_Tx(NEXTLINE);
			}
			else if (Local_u8_Variable3 == ENTER)
			{
				break; //STOP TAKING ID
			}
			else if(Local_u8_Variable3 != ENTER)
			{
				Local_u8_Error = NO_ERROR; //THE SCREEN IS NOT BLANK ANYMORE
				Local_u8_AdminID = Local_u8_Variable3;
				//_delay_ms(10);
				EEPROMINT_WriteByte(Local_u8_AdminCounter,Local_u8_AdminID);
				Local_u8_AdminCounter++;
			}
			else
			{
				//Do Nothing
			}
		}
		
		
		Local_u8_Error = ERROR; //SETTING IT BACK TO MAKE ANOTHER CHECK ON ANOTHER ITERATION
		UART_Tx(NEXTLINE);
		_delay_ms(DISPLAY_TIME);

		
		
																	/*PASSWORD*/
		UART_TxString("Now Enter Password: ");
		UART_Tx(NEXTLINE);
		while(Local_u8_Admin == NO_ADMIN)
		{
			Local_u8_Variable4 = HC05_Rx();

			if((Local_u8_Variable4 == ENTER) && (Local_u8_Error == ERROR))
			{
				UART_TxString("Error please try again");
				_delay_ms(DISPLAY_TIME);
				UART_Tx(NEXTLINE);
				UART_TxString("Password: ");
				UART_Tx(NEXTLINE);
			}
			else if(Local_u8_Variable4 != ENTER)
			{
				Local_u8_Error = NO_ERROR;
				Local_u8_AdminID = Local_u8_Variable4;
				EEPROMINT_WriteByte(Local_u8_AdminCounter,Local_u8_AdminID);
				Local_u8_AdminCounter++;
			}
			else if(Local_u8_Variable4 == ENTER)
			{
				EEPROMINT_WriteByte(Local_u8_AdminCounter,END_OF_CREDENTIALS);//END OF ID & PASS
				Local_u8_AdminCounter++;
				EEPROMINT_WriteByte(LAST_BYTE,Local_u8_AdminCounter);
				Local_u8_Admin = ADMIN_EXISTS;//EXIT WHILE
			}
		}
	}
	Local_u8_Error = NO_ERROR;	
	/***************************************************************LOGIN*******************************************************************/
	 while (STILL_LOGGING_IN)
	 {
		 if(Local_u8_Mode == ADMIN_MODE)
		 {
			 UART_TxString(" Log In");
			 UART_Tx(NEXTLINE);
			 
			 while(Local_u8_EEPROM != END_OF_CREDENTIALS)
			 {
				 
																		/*ENTER ID*/
				 
				 UART_TxString("ID:");
				 while(Local_u8_ID == TAKE_ID)
				 {
					 Local_u8_Variable1 = HC05_Rx();
					 
					 if( (Local_u8_Variable1 == ENTER) && (Local_u8_Error == ERROR))
					 {
						 UART_TxString(" Error please try again");
				         UART_Tx(NEXTLINE);
						 UART_TxString(" ID:");
					 }
					 else if(Local_u8_Variable1 == ENTER)
					 {
						 Local_u8_Error = ERROR;
						 Local_u8_ID = STOP_TAKING_ID;//STOP TAKING ID
					 }
					 else if(Local_u8_Variable1 != ENTER)
					 {
						 Local_u8_Error = NO_ERROR;
						 Local_u8_IDAndPass[Local_u8_counter] = Local_u8_Variable1;
						 Local_u8_counter++;
						 //_delay_ms(10);
					 }
					 else
					 {
						 //Do Nothing
					 }
				 }
				 
																		 /*ENTER PASSWORD*/
																		 
		         UART_Tx(NEXTLINE);
				 UART_TxString(" PASSWORD: ");
		         UART_Tx(NEXTLINE);
				 
				 while(Local_u8_ID == START_TAKING_PASS)
				 {
					 Local_u8_Variable2 = HC05_Rx();
					 
					 if((Local_u8_Variable2 == ENTER) && (Local_u8_Error == ERROR))
					 {
						 UART_TxString(" Error please try again");
		                 UART_Tx(NEXTLINE);
						 UART_TxString(" PASSWORD: ");
		                 UART_Tx(NEXTLINE);
					 }
					 else if(Local_u8_Variable2 == ENTER)
					 {
						 Local_u8_Error = ERROR;
						 Local_u8_ID = STOP_TAKING_PASS; //Breaks
					 }
					 
					 /*Enter the password you want untill 'ENTER'*/
					 else if(Local_u8_Variable2 != ENTER)
					 {
						 Local_u8_Error = NO_ERROR;
						 Local_u8_IDAndPass[Local_u8_counter] = Local_u8_Variable2;
						 Local_u8_counter++;
						// _delay_ms(10);
					 }
					 else
					 {
						 //Do Nothing
					 }
				 }
				 /************************************************************Checking_ID_PASS***********************************************************/
															/*Checking is still in the WHILE(Local_u8_EEPROM != END_OF_CREDENTIALS) LOOP */
															
				 for(Local_u8_Trials ; Local_u8_Trials >= NO_TRIALS ; --Local_u8_Trials)
				 {
					 Local_u8_ForLoopcounter = 0;
					 Local_u8_EEPROMCount = FIRST_EEPROM_PLACE; // --> PLACE NOT VALUE!
					 for(Local_u8_ForLoopcounter; Local_u8_ForLoopcounter < sizeof(Local_u8_IDAndPass) ; Local_u8_ForLoopcounter++)
					 {
						 Local_u8_EEPROM = EEPROMINT_ReadByte(Local_u8_EEPROMCount); //Reading EEPROM consecutively
						 Local_u8_EEPROMCount++;
						 if(Local_u8_EEPROM == END_OF_CREDENTIALS)// while can't break before the for in it
						 {
							 break;
						 }
						 else if(Local_u8_IDAndPass[Local_u8_ForLoopcounter] != Local_u8_EEPROM && Local_u8_Wrong == 10 )
						 {
		                     UART_Tx(NEXTLINE);
							 UART_TxString(" Wrong ID/PASS");
		                     UART_Tx(NEXTLINE);
							 switch(Local_u8_Trials)
							 {
								 case TWO_TRIALS:
								 UART_TxString(" 2 trials left ");
		                         UART_Tx(NEXTLINE);
								 break;
								 case ONE_TRIAL:
								 UART_TxString(" 1 trial left ");
		                         UART_Tx(NEXTLINE);
								 break;
								 case ZERO_TRIALS:
		                         UART_Tx(NEXTLINE);
								 UART_TxString(" EMERGENCY");
		                         UART_Tx(NEXTLINE);
								 UART_TxString(" CALLING 911");
								 while (EMERGENCY)
								 {
									 H_Buzzer_On();
								 }
								 break;
								 default:
								 break;
							 }
							 break; // don't keep searching in the wrong user and pass
						 }
					 }
					 Local_u8_counter = RESET;
					 Local_u8_ID = TAKE_ID; //RESETTING IT TO DEFAULT --> PREPARING TO LOOP AGAIN
					 --Local_u8_Trials;
					 break; //GO DO THE 'while(Local_u8_EEPROM != END_OF_CREDENTIALS)' AGAIN (BREAK FROM THE OUTTER FOR LOOP)
				 }	 
			 }
	/***************************************************************END_OF_LOGIN*******************************************************************/
		     UART_Tx(NEXTLINE);
			 UART_TxString(" Successful LOGIN");
		     UART_Tx(NEXTLINE);
	
	/***************************************************************MAIN_MENU*******************************************************************/
			 while(WAITING_FOR_CHOICE)
			 {
				 UART_TxString(" 1-ADD USER");
			     UART_Tx(NEXTLINE);
				 UART_TxString(" 2-REMOVE USER");
		         UART_Tx(NEXTLINE);
				 UART_TxString(" 3-MENU");
				 
				 
				 Local_u8_AdminCounter = EEPROMINT_ReadByte(LAST_BYTE);//UPDATE THE COUNTER
				 Local_u8_Variable7 = HC05_Rx();
				 switch (Local_u8_Variable7)
				 {
					 case ADD_USER:
		             UART_Tx(NEXTLINE);
					 UART_TxString(" ID: ");
					 while(ADDING_ID)
					 {
						 Local_u8_Variable8 = HC05_Rx();
						 
						 if( (Local_u8_Variable8 == ENTER) && (Local_u8_Error == ERROR))
						 {
							 UART_TxString(" Error please try again");
		                     UART_Tx(NEXTLINE);
							 UART_TxString(" ID: ");
		                     UART_Tx(NEXTLINE);
						 }
						 
						 else if(Local_u8_Variable8 == ENTER)
						 {
							 Local_u8_Error = ERROR;
							 EEPROMINT_WriteByte(LAST_BYTE,Local_u8_AdminCounter);//can be removed as counter is saved after password Right?!!
							 break;//END OF TAKING ID
						 }
						 else if(Local_u8_Variable8 != ENTER)
						 {
							 Local_u8_Error = NO_ERROR;
							 Local_u8_AdminID = Local_u8_Variable8;
							 //_delay_ms(10);
							 EEPROMINT_WriteByte(Local_u8_AdminCounter,Local_u8_AdminID);
							 Local_u8_AdminCounter++;
						 }
					 }
					 
		             UART_Tx(NEXTLINE);
					 UART_TxString(" PASSWORD:");
					 Local_u8_AdminCounter = EEPROMINT_ReadByte(LAST_BYTE);//UPDATE THE COUNTER
					 
					 while(ADDING_PASS)
					 {
						 Local_u8_Variable9 = HC05_Rx();
			
						 if( (Local_u8_Variable9 == ENTER) && (Local_u8_Error == ERROR))
						 {
							 UART_TxString(" Error please try again");
		                     UART_Tx(NEXTLINE);
							 UART_TxString(" PASSWORD:");
		                     UART_Tx(NEXTLINE);
						 }
						 else if(Local_u8_Variable9 != ENTER)
						 {
							 Local_u8_Error = NO_ERROR;
							 Local_u8_AdminID = Local_u8_Variable9;
						//	 H_Lcd_WriteCharacter(Local_u8_AdminID);
							 EEPROMINT_WriteByte(Local_u8_AdminCounter,Local_u8_AdminID);
							 Local_u8_AdminCounter++;
						 }
						 else if(Local_u8_Variable9 == ENTER)
						 {
							 EEPROMINT_WriteByte(Local_u8_AdminCounter,END_OF_CREDENTIALS);
							 Local_u8_Error = ERROR;
							 Local_u8_AdminCounter++;
							 EEPROMINT_WriteByte(LAST_BYTE,Local_u8_AdminCounter);//UPDATE THE COUNTER (IN EEPROM)
		                     UART_Tx(NEXTLINE);
							 UART_TxString(" USER ADDED");
		                     UART_Tx(NEXTLINE);
							 break;//END OF TAKING PASS
						 }
						 else
						 {
							 //Do Nothing
						 }
					 }
					 
					 break;
					 case REMOVE_USER:
		             UART_Tx(NEXTLINE);
					 UART_TxString(" Enter ID&PASS");
					 UART_TxString(" Combined");
		             UART_Tx(NEXTLINE);
					 Local_u8_counter = RESET;
					 Local_u8_EEPROMCount = RESET;
					 u8 Local_u8_EEPROMTEMP = NONE;
					 u8 Local_u8_EEPROMVALUE = NONE;
					 while(TAKING_ID_PASS)
					 {
						 Local_u8_Variable10 = HC05_Rx();
						 
						 if(Local_u8_Variable10 == ENTER)
						 {
							 break;
						 }
						 else if(Local_u8_Variable10 != ENTER)
						 {
							 Local_u8_IDAndPass[Local_u8_counter] = Local_u8_Variable10;
							// H_Lcd_WriteCharacter(Local_u8_Variable10);
							 Local_u8_counter++;
							 Local_u8_EEPROMVALUE = EEPROMINT_ReadByte(Local_u8_EEPROMCount) ;
							 if(Local_u8_EEPROMVALUE == END_OF_CREDENTIALS)
							 {
								 //Do Nothing
							 }
							 else
							 {
								 Local_u8_EEPROMCount++;
							 }
						 }
						 else
						 {
							 //Do Nothing
						 }
					 }
					 
					 while(REMOVING_USER)
					 {
						 u8 Local_u8_BREAK = NO;//END 'while(REMOVING_USER)' LOOP
						 if(Local_u8_EEPROMCount == LAST_PLACE)
						 {
		                     UART_Tx(13);
							 UART_TxString(" USER DOESN'T");
		                     UART_Tx(13);
							 UART_TxString(" EXIST");
							 break; //END 'while(REMOVING_USER)' LOOP
						 }
						 else
						 {
							 Local_u8_counter = RESET;
							 Local_u8_EEPROMCount++;
							 Local_u8_EEPROMTEMP = Local_u8_EEPROMCount;
							 while(CHECKING)
							 {
								 if(Local_u8_IDAndPass[Local_u8_counter] == EEPROMINT_ReadByte(Local_u8_EEPROMTEMP))
								 {
									 Local_u8_EEPROMCount++;
									 UART_Tx(NEXTLINE);
									 UART_TxString(" CHECKING...");
									 
									 if(EEPROMINT_ReadByte(Local_u8_EEPROMCount) == END_OF_CREDENTIALS)
									 {
										 while(EEPROMINT_ReadByte(Local_u8_EEPROMTEMP) != END_OF_CREDENTIALS)
										 {
											 EEPROMINT_WriteByte(Local_u8_EEPROMTEMP,EMPTY);
											 --Local_u8_EEPROMTEMP;
										 }
										 UART_Tx(NEXTLINE);
										 UART_TxString(" USER DELETED");
										 UART_Tx(NEXTLINE);
										 Local_u8_BREAK = YES;
										 break;//END 'while(CHECKING)' LOOP
									 }
									 Local_u8_EEPROMTEMP++;
									 Local_u8_counter++;
								 }
								 else
								 {
									 Local_u8_EEPROMTEMP++;
									 Local_u8_EEPROMCount++;
									 
									 if(Local_u8_EEPROMCount == LAST_PLACE)
									 {
										 break;//END 'while(CHECKING)' LOOP
									 }
								 }
							 }
							 if(Local_u8_BREAK == YES)
							 {
								 break;
							 }
						 }
					 }
					 break;
					 case MENU:
					 UART_Tx(NEXTLINE);
					 UART_TxString(" Welcome sir");
					 UART_Tx(NEXTLINE);
					 while (WAITING_FOR_CHOICE)
					 {
						  u8 Local_u8_FlagToMenu = 0;
						 UART_TxString(" 1-Door  2-Light");
						 UART_Tx(NEXTLINE);
						 UART_TxString(" 3-Dim_Light 4-AC");
						 UART_Tx(NEXTLINE);
						 UART_TxString(" 5-Back To Main Menu");
						 UART_Tx(NEXTLINE);

						 Local_u8_Menu =	HC05_Rx() ;
						 if (Local_u8_Menu != 0)
						 {
							 
							 switch(Local_u8_Menu)
							 {
								 case 49:H_Lcd_Clr();  Door_Control();                break;
								 case 50:H_Lcd_Clr();  Light_Control();			      break;
								 case 51:H_Lcd_Clr();  Dim_Light_Control();		      break;
								 case 52:H_Lcd_Clr();  AirCond_EN();                  break;
								 case 53:H_Lcd_Clr();  Local_u8_FlagToMenu = 1;       break;								 
								 default:							                  break;
							 }
						 }
						  if(Local_u8_FlagToMenu == 1)
						  {
							  break;
						  }

						 
					 }// end of super loop
					 break;
					 default:                        					 break;
					 }

				 }
			 }
/************************************************** USER_MODE***************************************************************************************/
else if (Local_u8_Mode == USER_MODE)
{     
	H_Lcd_WriteString("Welcome");
	_delay_ms(DISPLAY_TIME);
	H_Lcd_Clr();
	Local_u8_EEPROM = 0;
	Local_u8_counter = 0;
	Local_u8_ID = 1;
	Local_u8_Wrong == 10;
	Local_u8_Trials = 3;
	while(1)
	{
		if(Local_u8_Wrong == 11)
		{
			break;
		}
		
		/*Taking the ID*/
		H_Lcd_WriteString("ID:");
		H_Lcd_GoTo(1,0);
		while(Local_u8_ID)
		{
			Local_u8_Variable11 = H_KeyPad_Read();
			if((Local_u8_Variable11 == '=') && (Local_u8_Error == ERROR))
			{
				H_Lcd_WriteString("Error please try again");
				_delay_ms(750);
				H_Lcd_Clr();
				H_Lcd_WriteString("ID:");
				H_Lcd_GoTo(1,0);
			}
			else if(Local_u8_Variable11 == '=')
			{
				/*The end of taking the ID*/
				Local_u8_Error = ERROR;
				Local_u8_ID = 0;
			}
			else if(Local_u8_Variable1 != '=')
			{
				Local_u8_Error = NO_ERROR;
				Local_u8_IDAndPass[Local_u8_counter] = Local_u8_Variable11;
				H_Lcd_WriteCharacter(Local_u8_IDAndPass[Local_u8_counter]);
				Local_u8_counter++;
				_delay_ms(10);
			}
		}
		
		/*Taking the PASSWORD*/
		H_Lcd_Clr();
		H_Lcd_WriteString("PASSWORD: ");
		_delay_ms(DISPLAY_TIME);
		H_Lcd_GoTo(1,0);
		
		while(!Local_u8_ID)
		{
			Local_u8_Variable12 = H_KeyPad_Read();
			if((Local_u8_Variable12 == '=') && (Local_u8_Error == ERROR))
			{
				H_Lcd_WriteString("Error please try again");
				_delay_ms(DISPLAY_TIME);
				H_Lcd_Clr();
				H_Lcd_WriteString("PASSWORD: ");
				H_Lcd_GoTo(1,0);
			}
			else if(Local_u8_Variable12 == '=')
			{
				/*The end of taking the ID*/
				Local_u8_Error = ERROR;
				Local_u8_ID = 1;
			}
			
			/*Enter the password you want untill 'ENTER'*/
			else if(Local_u8_Variable12 != '=')
			{
				Local_u8_Error = NO_ERROR;
				Local_u8_IDAndPass[Local_u8_counter] = Local_u8_Variable12;
				H_Lcd_WriteCharacter(Local_u8_IDAndPass[Local_u8_counter]);
				Local_u8_counter++;
				_delay_ms(10);
			}
			
		}
		
		/*Checking if ID & PASS are RIGHT*/
		
		for(Local_u8_Trials ; Local_u8_Trials >=0 ; --Local_u8_Trials)
		{
			Local_u8_ForLoopcounter = 0;
			Local_u8_EEPROMCount = 0;
			for(Local_u8_ForLoopcounter; Local_u8_ForLoopcounter < 255 ; Local_u8_ForLoopcounter++)
			{
				Local_u8_EEPROM = EEPROMINT_ReadByte(Local_u8_EEPROMCount); //Reading EEPROM consecutively
				Local_u8_EEPROMCount++;
				if(Local_u8_IDAndPass[Local_u8_ForLoopcounter] == Local_u8_EEPROM)
				{
					H_Lcd_Clr();
					H_Lcd_WriteString("CHECKING...");
					if(EEPROMINT_ReadByte(Local_u8_EEPROMCount) == '$')
					{
						break;
						Local_u8_Wrong == 11;
					}
					
				}
				else if(Local_u8_IDAndPass[Local_u8_ForLoopcounter] != Local_u8_EEPROM && Local_u8_Wrong == 10 )
				{
					H_Lcd_Clr();
					H_Lcd_WriteString("Wrong ID/PASS");
					_delay_ms(500);
					H_Lcd_GoTo(1,0);
					switch(Local_u8_Trials)
					{
						case 3:
						H_Lcd_WriteString("2 trials left ");
						_delay_ms(500);
						H_Lcd_Clr();
						break;
						case 2:
						H_Lcd_WriteString("1 trial left ");
						_delay_ms(500);
						H_Lcd_Clr();
						break;
						case 1:
						H_Lcd_Clr();
						H_Lcd_GoTo(0,4);
						H_Lcd_WriteString("EMERGENCY");
						H_Lcd_GoTo(1,0);
						H_Lcd_WriteString("CALLING 911");
						while (6)
						{
							//ALARM ON
						}
						break;
						default:
						break;
					}
					break;
				}
			}
			Local_u8_counter = 0;
			Local_u8_ID = 1;
			--Local_u8_Trials;
			break;
		}
	}
	
	H_Lcd_Clr();
	while(1)
	{
		H_Lcd_WriteString("MENU"); //MENU
	}
	
}

}
//}





			
		// }
	
	
}//end of main
/***********************************************************************************************************************************************/
void LCD_Welcome(void)
{
	H_Lcd_GoTo(0,0);
	H_Lcd_WriteString("Welcome to your"); 
	H_Lcd_GoTo(1,0);
	H_Lcd_WriteString("home sir");
	_delay_ms(500);
	H_Lcd_Clr();
	_delay_ms(500);
	H_Lcd_WriteString("Press 'A' To");
	H_Lcd_GoTo(1,0);
	H_Lcd_WriteString("Proceed");
	/*****************************************************************************/
	UART_TxString("Welcome to your home sir");
	UART_Tx(13);
	UART_TxString(" Press 'A' To");
	UART_Tx(13);
	UART_TxString(" Proceed");
	UART_Tx(13);	
}

 void Door_Control(void)
 {
	 M_Dio_PinMode(PD7,OUTPUT);
	 u8 Local_u8_reading = 0 ;
	 UART_Tx(NEXTLINE);
	 UART_TxString(" 1-Door Open");
	 UART_Tx(NEXTLINE);
	 UART_TxString(" 2-Door Close");
	 Local_u8_reading = HC05_Rx() ;
	 if (Local_u8_reading == '1')
	 {
		 M_Dio_PinWrite(PD7,HIGH);
		 _delay_ms(2);
		 M_Dio_PinWrite(PD7,LOW);
	     UART_Tx(13);
		 UART_TxString("DONE");

		 
	 }
	 else if(Local_u8_reading == '2')
	 {
		 M_Dio_PinWrite(PD7,HIGH);
		 _delay_ms(1.5);
		 M_Dio_PinWrite(PD7,LOW);
	     UART_Tx(NEXTLINE);
		 UART_TxString("  DONE");
		 UART_Tx(NEXTLINE);

	 }
	 else
	 {
		 	 //do nothing

	 }


 }


 void Light_Control(void)
 {
	u8 Local_u8_reading = 0 ;
    UART_Tx(NEXTLINE);
	UART_TxString(" 1-Lights ON");
	UART_Tx(NEXTLINE);
	UART_TxString(" 2-Lights OFF");
	UART_Tx(NEXTLINE);

	Local_u8_reading = HC05_Rx() ;
	if (Local_u8_reading == '1')
	{
		H_Led_On(LED0);
		H_Led_On(LED1);
		H_Led_On(LED2);
		H_Led_On(LED3);
		H_Led_On(LED4);
	}
	else if (Local_u8_reading == '2')
	{
		H_Led_Off(LED0);
		H_Led_Off(LED1);
		H_Led_Off(LED2);
		H_Led_Off(LED3);
		H_Led_Off(LED4);
	}
	else 
	{
		//do nothing
	}
	 
 }
 
 
  void Dim_Light_Control(void)
  {
	  u8 Local_u8_reading = 0 ;
	  UART_Tx(NEXTLINE);
	  UART_TxString(" Enter intensity from 0:9");
	  UART_Tx(NEXTLINE);
	  Local_u8_reading = HC05_Rx() ;
	  if (Local_u8_reading != 0)
	  {
		  switch(Local_u8_reading)
		  {
			  case 48: TIMER0_SetCompVal(2);       break;
			  case 49: TIMER0_SetCompVal(25);      break;
			  case 50: TIMER0_SetCompVal(50);      break;
			  case 51: TIMER0_SetCompVal(75);      break;
			  case 52: TIMER0_SetCompVal(100);     break;
			  case 53: TIMER0_SetCompVal(125);     break;
			  case 54: TIMER0_SetCompVal(150);     break;
			  case 55: TIMER0_SetCompVal(175);     break;
			  case 56: TIMER0_SetCompVal(200);     break;
			  case 57: TIMER0_SetCompVal(250);     break;
			  
			  default:                    break;
		  }
	  }  

  }




void AirCond_control(void)
{
	u8 Local_u8_erorr ;
	Local_u8_erorr = M_ADC_StartConversionAsynch(0, &Gloable_u16_ADC_Reading,ADC_ISR);
	

}

void ADC_ISR(void)
{
	Gloable_u16_Analog_MV = (Gloable_u16_ADC_Reading * 5000UL) /1024 ;
	Gloable_u8_temp = Gloable_u16_Analog_MV / 10 ;
}


void TimerISR(void)
{
	AirCond_control();
	if(Gloable_u8_AC_Flag == 1)
	{
	if(Gloable_u8_temp > 27)
	{
		H_H_Bridge_CH1_EN();
	}
	else if  (Gloable_u8_temp < 21)
	{
		H_H_Bridge_CH1_Break();
	}
	else
	{
		// do nothing
	}
	}
	else
	{
		H_H_Bridge_CH1_Break();
	}
}

void AirCond_EN(void)
{
	u8 Local_u8_Number=0;
	u8 Local_u8_Number1=0;
    u8 Local_u8_reading ;
	UART_TxString("LOADING.....");
	while(Gloable_u8_temp == 0); //wait until adc take reading
	_delay_ms(50);
	Local_u8_Number = (Gloable_u8_temp/10)+48 ;
	Local_u8_Number1=  (Gloable_u8_temp%10)+48 ;
    UART_Tx(13);
	_delay_ms(50);
	UART_TxString(" Current temperature is : ");
		_delay_ms(50);
	UART_Tx(Local_u8_Number);
		_delay_ms(50);
	UART_Tx(Local_u8_Number1); 
    UART_Tx(13);
	UART_TxString("   1-AC Enable");
    UART_Tx(13);
	UART_TxString(" 2-AC Disable");
	Local_u8_reading = HC05_Rx() ;
	if (Local_u8_reading == '1')
	{
		Gloable_u8_AC_Flag = 1 ;
	}
	else if (Local_u8_reading == '2')
	{
		Gloable_u8_AC_Flag = 0 ;
	}
	else
	{
		//DO Nothing
	}
	
	
	
}

void X_ISR(void)
  {
	  Local_u8_Variable13 = 1;

	  while(Local_u8_Variable6 == 0)
	  {
		  Local_u8_Variable6 = H_KeyPad_Read();
	  }

  }
