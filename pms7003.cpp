#include <pms7003.h>



	
void pms7003::read(uint16_t &pm01, uint16_t &pm2_5, uint16_t &pm10){
	
	if( millis() - timer > samplerate){
		char buf[LENGTH];
	if( data_available(buf, LENGTH)){
		
		static unsigned long timer;
		//readBytes(buf,LENGTH);
		char buf2[LENGTH];
		uint8_t start, start2;
		
		for(int i = 0; i < LENGTH; i++){// copie data buffer
			buf2[i] = buf[i];
		}
		
		for(int i = 0; i < LENGTH; i++){ // find start bytes position
			
			if(buf[i] == startByte){
				
				if( buf[ ( i + 1) % LENGTH ] == startByte2){
					start = i;
					start2 = buf[ ( i + 1) % LENGTH];
					break;
				}
			}
		}
		
		for(int i = 0; i < LENGTH; i++){
			buf[i] = buf2[(start + i) % LENGTH];
		}

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
		#ifdef Serial
		case 0:// use uart 0
		Serial.begin(pmsBAUD);
		Serial.setTimeout(timeout);
		break;
		#endif
		#ifdef Serial1
		case 1:// use uart 1	
		Serial1.begin(pmsBAUD);
		Serial1.setTimeout(timeout);
		break;
		#endif
		#ifdef Serial2
		case 2:// use uart 2
		Serial2.begin(pmsBAUD);
		Serial2.setTimeout(timeout);
		break;
		#endif
		#ifdef Serial3
		case 3:// use uart 3
		Serial3.begin(pmsBAUD);
		Serial3.setTimeout(timeout);
		break;
		#endif
	} 
}

bool pms7003::data_available(char *buf, uint8_t length){// check if theres data available
	bool state;
	int x;
	switch(UARTNR){
		#ifdef Serial
		case 0:// use uart 0
		if(Serial.available() > 0){

		while(Serial.available() > 0){
			buf[x] = Serial.read();
			x++;
			if(x == length){
				break;
			}
		}
		state = true;		
		}	
		break;
		#endif
		#ifdef Serial1
		case 1:// use uart 1	
		if(Serial1.available() > 0){

		while(Serial1.available() > 0){
			buf[x] = Serial1.read();
			x++;
			if(x == length){
				break;
			}
		}
		state = true;		
		}	
		break;
		#endif
		#ifdef Serial2
		case 2:// use uart 2
		if(Serial2.available() > 0){

		while(Serial2.available() > 0){
			buf[x] = Serial2.read();
			x++;
			if(x == length){
				break;
			}
		}
		state = true;		
		}		
		break;
		#endif
		#ifdef Serial3
		case 3:// use uart 3
		if(Serial3.available() > 0){

		while(Serial3.available() > 0){
			buf[x] = Serial3.read();
			x++;
			if(x == length){
				break;
			}
		}
		state = true;		
		}	
		break;
		#endif
	} 
	return state;
}
