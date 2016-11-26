float temperature(char *buffer){
		read(ADC1,buffer,2);
		int16 data;
		int16 temp;
		float temperatureval=0;
	
		data=buffer[1];
		temp=buffer[0];
		temp=(data<<8)|temp;
		//if high voltage is 3.3, if its 5 mulitply by 5.0;
		temperatureval=((((temp*1.0/4096)*1800)-500)/10);
		return temperatureval;

}