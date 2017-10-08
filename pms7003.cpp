#include <pms7003.h>



	
void pms7003::read(uint16_t &pm01, uint16_t &pm2_5, uint16_t &pm10){
	
	if( millis() - timer > samplerate){
	if( data_available()){
		char buf[LENGTH];
		static unsigned long timer;
		readBytes(buf,LENGTH);
		
		if(buf[0] == startByte){
			for( uint8_t i = 0; i < 12; i++){
			DATA[i] = ((buf[i*2+2] << 8) + buf[i*2+3] );
			}
			PM1 = DATA[4];
			PM2_5 = DATA[5];
			PM10 = DATA[6];
			pm01 = PM1;
			pm2_5 = PM2_5;
			pm10 = PM10;
		}
	}
	timer = millis();
	}
		
}
	
 
   


void pms7003::begin(uint8_t com){// initialize serial uart
	UARTNR = com;// assign serial port number
	switch(UARTNR){
		case 0:// use uart 0
		Serial.begin(pmsBAUD);
		Serial.setTimeout(timeout);
		break;
		case 1:// use uart 1	
		Serial1.begin(pmsBAUD);
		Serial1.setTimeout(timeout);
		break;
		case 2:// use uart 2
		Serial2.begin(pmsBAUD);
		Serial2.setTimeout(timeout);
		case 3:// use uart 3
		Serial3.begin(pmsBAUD);
		Serial3.setTimeout(timeout);
		break;
	} 
}

bool pms7003::data_available(){// check if theres data available
	bool state;
	switch(UARTNR){
		case 0:// use uart 0
		if(Serial.available() > 0){ 
		state = true;
		}	
		break;
		case 1:// use uart 1	
		if(Serial1.available() > 0){   
		state = true;		
		}	
		break;
		case 2:// use uart 2
		if(Serial2.available() > 0){    
		state = true;
		}	
		case 3:// use uart 3
		if(Serial3.available() > 0){    
		state = true;
		}	
		break;
	} 
	return state;
}

void pms7003::readBytes(char *buf, uint8_t length){// read data
int x;
	switch(UARTNR){
		case 0:// read uart 0
		while(Serial.available()){buf[x] = Serial.read();x++;}
		break;
		case 1:// read uart 1		
		while(Serial1.available()){buf[x] = Serial1.read();x++;}
		break;
		case 2:// read uart 2
		while(Serial2.available()){buf[x] = Serial2.read();x++;}
		case 3:// read uart 3
		while(Serial3.available()){buf[x] = Serial3.read();x++;}
		break;
	} 
}
