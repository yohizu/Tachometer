/* Tachometer output on pin 2 (Interupt 0)
Only pins 2 & 3 can use INTERUPT
*/


#include <Wire.h>  // Comes with Arduino IDE
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
volatile unsigned int counter = 0;
volatile unsigned int counterDisplay = 0;

void setup()
{


  lcd.begin(16, 2);

  lcd.backlight(); 

/*the Interupt routine*/
  Timer1.initialize(2000000);//set timer length 2 sec
  attachInterrupt(0, blink, RISING); //into
  Timer1.attachInterrupt(timerIsr);
  //End of the Interupt routine
}




void loop()   
{
  lcd.setCursor(0, 0);// NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.print("Speed: ");

  lcd.print((counterDisplay)*30, DEC);//As the time interval is 2 Sec, the multiplier for RPM is 60/2=30
  lcd.print(" RPM");
  lcd.print("    ");
  
}



void blink()
{
  counter++;
}
void timerIsr()
{
  Timer1.detachInterrupt();//disale timer1

  counterDisplay = counter;
  counter = 0;
  Timer1.attachInterrupt(timerIsr);//enable timer1
}






