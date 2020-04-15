/* Tachometer output on pin 2 (Interupt 0)
Only pins 2 & 3 can use INTERUPT
*/


#include <Wire.h>  // Comes with Arduino IDE
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
volatile unsigned int counter = 0;
volatile unsigned int counterDisplay = 0;
//float n;//time mesuring
//float v;//calculated rpm

void setup()
{
//  Serial.begin(9600);  // Used to type in characters

  lcd.begin(16, 2);

  lcd.backlight(); 

/*the Interupt routine*/
  Timer1.initialize(2000000);//set timer length 2 sec
  attachInterrupt(0, blink, RISING); //into
  Timer1.attachInterrupt(timerIsr);//put service routine here

  //End of the Interupt routine
}

/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  lcd.setCursor(0, 0);// NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.print("Speed: ");
//  lcd.setCursor(10, 0);
  lcd.print((counterDisplay)*30, DEC);//As the time interval is 2 Sec, the multiplier for RPM is 60/2=30
  lcd.print(" RPM");
  lcd.print("    ");
  
}

//Function

void blink()
{
  counter++;
}
void timerIsr()
{
  Timer1.detachInterrupt();//disale timer1
//  Serial.print("the motor speed: ");
//  Serial.print(counter, DEC);
  // lcd.print(counter,DEC);
//  Serial.println("round/s");
  counterDisplay = counter;
  counter = 0;
  Timer1.attachInterrupt(timerIsr);//enable timer1
}


/* --(end main loop )-- */


/* ( THE END ) */
