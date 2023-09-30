
#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>      

#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))    
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
int     i ;                   
int     a , b ;            
float   Temperature ;     
char    Buffer_LCD[16];
char heater; 
char cooler; 
heater = 0; 
cooler = 0;           

DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

ADMUX=ADC_VREF_TYPE;       
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

lcd_init(16);   
lcd_clear();    

while (1)
{
       
      
      a=0;  b=0;   
      for(i=1;i<=10;i++)  
      {
      a=a+read_adc(0);          
      delay_ms(30);
      }
      b=a/10; 
       
      Temperature=(b/2.054) ;                         
      sprintf(Buffer_LCD,"T=%3.1f",Temperature);  
      lcd_gotoxy(0,0);        
      lcd_puts(Buffer_LCD);  
      lcd_gotoxy(7,0); 
           
      if(cooler == 0 && heater == 0 &&  Temperature < 15 )     
      {  
      heater = 1;  
      }
       
      else if(cooler == 0 && heater == 0 &&  Temperature > 35  )    
      {
        cooler = 1; 
        lcd_gotoxy(1,1);     
        lcd_putsf("cooler on");
      } 
        
      
      else if(cooler &&  heater == 0 && Temperature< 25 ) 
      {
       cooler = 0 ;
       lcd_gotoxy(1,1);     
        lcd_putsf("cooler of");
      
      } 
      
      else if(!cooler && heater &&  Temperature> 30 )
      {
        
        heater = 0;            
        lcd_gotoxy(1,1);     
        lcd_putsf("heater  off");
         
      }
      
      else 
      { 
        heater = heater; 
        cooler = cooler ;
      } 
      
      if (heater == 1) 
      {
            PORTD = 9 <<4 ;
            delay_ms(35) ;  
            PORTD = 12 <<4; 
            delay_ms(35);
            PORTD = 6 <<4 ;
            delay_ms(35);
            PORTD = 3 <<4 ;
            delay_ms(35);  
      } 
      
       if(cooler == 1)
      { 
        PORTD = 9;
        delay_ms(35) ;  
        PORTD = 12; 
        delay_ms(35);
        PORTD = 6 ;
        delay_ms(35);
        PORTD = 3  ;
        delay_ms(35);  
        
      
      } 
      
}
      
}
