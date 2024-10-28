#include <reg51.h>
void UART_init();
void UART_TX(char);
char UART_RX();
void UART_SENDSTRING(char *);
sbit light=P0^0;
sbit fan=P0^1;

void UART_init(){
		TMOD=0X20;
		TH1=0XFD;
		SCON=0X50;
		TR1=1;
}
void UART_TX(char Data){
		SBUF=Data;
		while(TI==0);
		TI=0;
}
char UART_RX(){
		char rData;
		while(RI==0);
		RI=0;
		rData=SBUF;
		return(rData);
}
void UART_SENDSTRING(char *str){
		int i;
		for(i=0;str[i]!=0;i++){
			UART_TX(str[i]);
		}
	}
	
void main(){
	char Data_in;
	UART_init();
	P0=0;
	
	while(1){
		Data_in=UART_RX();
		if(Data_in=='1'){
			light=1;
			UART_SENDSTRING("light on");
			}
		else if(Data_in=='2'){
			light=0;
			UART_SENDSTRING("light off");
			}
		else if(Data_in=='3'){
			fan=1;
			UART_SENDSTRING("fan on");
			}
		else if(Data_in=='4'){
			fan=0;
			UART_SENDSTRING("fan off");
			}
		else{
				UART_SENDSTRING("error");
		}
	}	
}
	
