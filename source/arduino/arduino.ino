#include <SPI.h> //probly not needed

#define DATA_READY_PIN A0


void setup() {
	delay(2000);
	pinMode(DATA_READY_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT); //debug

	// Enable SPI as slave.
	pinMode(SCK, INPUT);
	pinMode(MOSI, INPUT);
	pinMode(MISO, OUTPUT); //always an output as only one slave exists
	pinMode(SS, INPUT); //not used as only one slave exists

	SPDR = 0xAA; //debug
	SPCR |= (1 << SPIE); //enable interrupt
	SPCR |= (1 << SPE); //enable
}

//debug
//void loop() {
//	digitalWrite(LED_BUILTIN, digitalRead(SCK));	
//}

void loop() {
	int cnt = 0;
	SPDR = 0xAA;
	delay(100);
	

	if(SPSR & (1 << SPIF)){
		digitalWrite(LED_BUILTIN, HIGH);
		//if(digitalRead(LED_BUILTIN)){
			//digitalWrite(LED_BUILTIN, LOW);
		//}else{
			//digitalWrite(LED_BUILTIN, HIGH);
		//}
	}

	digitalWrite(DATA_READY_PIN, LOW);
	delay(900);
}

// interrupt vector definitions for leonardo:
// C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr\iom32u4.h
ISR(SPI_STC_vect){
	static byte nextValueToSend;
	SPDR = nextValueToSend;
	nextValueToSend++;
//	if(digitalRead(LED_BUILTIN)){
//		digitalWrite(LED_BUILTIN, LOW);
//	}else{
//		digitalWrite(LED_BUILTIN, HIGH);
//	}
	
}
