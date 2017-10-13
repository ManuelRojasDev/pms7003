/*
This library was meant to bue used with the pms7003 plant tower module.
Although al the data sets are merged and saved in the "char DATA[]" array, only 
DATA[4,5,6] are being used as output of this library, those are respectively 
particle sizes 1.0, 2.5 and 10. data output is in micro grams per m^3
This library was created BY Manuel Rojas, use as is,
Follow me on github.com/nodood
*/
 
#include <Arduino.h>
#define _pms7003_H
#define LENGTH 32  // length of data
#include <stream.h> 



class pms7003{
	
	public:
 	pms7003(uint8_t uartnr){// indicate serialcom nr
		begin(uartnr);
	}
	pms7003(){}// default start on uart 0;
	
	void read(uint16_t &pm01, uint16_t &pm2_5, uint16_t &pm10);
	void begin(uint8_t com);// name serial port number
	uint16_t PM1, PM2_5, PM10; // particle values 1.0, 2.5, 10 in micrograms per m^3
	uint16_t timeout = 100;// reading timeout in millis

	
	private:
	unsigned long timer;//
	unsigned long samplerate = 1000;//
	bool data_available(char *buf, uint8_t length);
	void readBytes(char *buf, uint8_t length);
	uint8_t UARTNR;// serial port number	
	char startByte = 0x42;
	char startByte2 = 0x4d;
	uint16_t pmsBAUD = 9600;
	uint8_t DATA[16];
	
	
};

