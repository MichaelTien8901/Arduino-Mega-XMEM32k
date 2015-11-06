#include <Arduino.h>
#include <stdlib.h>
void setup() {
  // put your setup code here, to run once:
  XMCRA = (1 << SRE);
  XMCRB = 0;// default, use full PC
  PORTC = 0xFF; // Enable pullups on port C
  while(!Serial);
  delay(200);
  // Open up a serial channel
  Serial.begin(115200);
  // Enable on-board LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("Beginning memory test...");
}

#define INIT_VALUE 0x73 
void writemem( unsigned char *p, unsigned long memsize )
{
  unsigned char *p1 = p;
  long i;
  unsigned char val = INIT_VALUE ^((unsigned long) p);
  for ( i = 0; i < memsize; i ++ ) {
     *p1++ = val;
     val = (val << 1) + ((val >> 7) & 0x01);
     val ^= i;
  }  
}
char testmem( unsigned char *p, unsigned long memsize ) 
{
  unsigned char *p1 = p;
  long i;
  unsigned char val = INIT_VALUE ^((unsigned long) p);
  val = INIT_VALUE ^((unsigned long) p);
  for ( p1 = p, i = 0; i < memsize; i ++ ) {
     if ( *p1++ != val ) return 0;
     val = (val << 1) + ((val >> 7) & 0x01);
     val ^= i;
  }
  return 1;  
}
#define ALLOC_SIZE 512
#define ALLOC_NO  64
void loop() 
{
  // put your main code here, to run repeatedly:
  unsigned char *memp[ALLOC_NO];
  int i, k;
  digitalWrite(LED_BUILTIN, LOW);
  for ( i = 0; i < ALLOC_NO; i ++ ) {
     memp[i] = (unsigned char *)malloc(ALLOC_SIZE);
     if ( memp[i] != 0 ) {
        Serial.print( "write mem " );
        Serial.print( i );       
        Serial.print( " :" );
        Serial.println( (unsigned long) memp[i] & 0xffff, HEX );
        writemem( memp[i], ALLOC_SIZE );
     } else break;
  }
  k = i;
  for ( i = 0; i < k; i ++ ) {
    if ( !testmem( memp[i], ALLOC_SIZE )) {
      Serial.print( "FAIL at " );
      Serial.println( i );
      break;
    }
  }    
  if ( i == k ) {
    Serial.println( "Test memo ok" );
     digitalWrite(LED_BUILTIN, HIGH);
  }
  for ( i = 0; i < k;  i ++ ) {
    free( memp[i] );
  }
  
  delay(5000);
}
