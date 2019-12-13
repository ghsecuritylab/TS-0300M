#include "types.h"

void IIC_Start(T_I2C_Master_PIN_OPT * PIN_OPT)
{
	PIN_OPT->SDA_Mode(IIC_IO_OUT);     //SDO线输出
	PIN_OPT->SDO(1);
	PIN_OPT->SCK(1);
	delay_us(4);
	PIN_OPT->SDO(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	PIN_OPT->SCK(0);//钳住I2C总线，准备发送或接收数据,使其后面可以改变其SDO的值 
}

void IIC_Stop(T_I2C_Master_PIN_OPT * PIN_OPT)
{
	PIN_OPT->SDA_Mode(IIC_IO_OUT); //SDO线输出
	PIN_OPT->SCK(0);
	PIN_OPT->SDO(0); //拉低SCL,使SDO可变     
 	delay_us(4);
	PIN_OPT->SCK(1);
	PIN_OPT->SDO(1);//STOP:when CLK is high DATA change form low to high
	delay_us(4);							   	
}

u8 IIC_Wait_Ack(T_I2C_Master_PIN_OPT * PIN_OPT)
{
	u8 ucErrTime=0;
	PIN_OPT->SDA_Mode(IIC_IO_IN);     //SDO设置为输入  
	PIN_OPT->SDO(1);delay_us(1);	   
	PIN_OPT->SCK(1);delay_us(1);	 
	while(PIN_OPT->SDI())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop(PIN_OPT);
			return 1;
		}
	}
	PIN_OPT->SCK(0);//时钟输出0 	   
	return 0;  
}

void IIC_Ack(T_I2C_Master_PIN_OPT * PIN_OPT)
{
	PIN_OPT->SCK(0);
	PIN_OPT->SDA_Mode(IIC_IO_OUT);
	PIN_OPT->SDO(0);
	delay_us(2);
	PIN_OPT->SCK(1);
	delay_us(2);
	PIN_OPT->SCK(0);
}

void IIC_NAck(T_I2C_Master_PIN_OPT * PIN_OPT)
{
	PIN_OPT->SCK(0);
	PIN_OPT->SDA_Mode(IIC_IO_OUT);
	PIN_OPT->SDO(1);
	delay_us(2);
	PIN_OPT->SCK(1);
	delay_us(2);
	PIN_OPT->SCK(0);
}

void IIC_Send_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 txd)
{                        
    u8 t;   
    PIN_OPT->SDA_Mode(IIC_IO_OUT);	    
    PIN_OPT->SCK(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
      if((txd&0x80)>>7)PIN_OPT->SDO(1);
      else PIN_OPT->SDO(0);
        txd<<=1; 	  
        delay_us(2);   
	PIN_OPT->SCK(1);
	delay_us(2); 
	PIN_OPT->SCK(0);	
	delay_us(2);
    }
} 

u8 IIC_Read_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 ack)
{
	u8 i,receive=0;
	PIN_OPT->SDA_Mode(IIC_IO_IN);//SDO设置为输入
    for(i=0;i<8;i++ )
	{
        PIN_OPT->SCK(0);
        delay_us(2);
		PIN_OPT->SCK(1);
        receive<<=1;
        if(PIN_OPT->SDI())receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck(PIN_OPT);//发送nACK
    else
        IIC_Ack(PIN_OPT); //发送ACK   
    return receive;
}

void IIC_BUS_Write_One_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u8 txd)
{
  IIC_Start(PIN_OPT);				                 //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00)); //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,Sub_Addr);		             	//发送8位寄存器地址
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,txd);                      	 //发送需要写入寄存器的数据
  IIC_Wait_Ack(PIN_OPT);
  IIC_Stop(PIN_OPT);                                //结束信号
  delay_ms(3);
}

void IIC_BUS_Write_More_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,uc8 *txd,u8 dat_Length)
{
  u8 dat_i;
  IIC_Start(PIN_OPT);				                  //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                    //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,Sub_Addr);		                  //发送8位寄存器地址
  IIC_Wait_Ack(PIN_OPT);
  for(dat_i=0;dat_i<dat_Length;dat_i++)
  {
    IIC_Send_Byte(PIN_OPT,*(txd+dat_i));                 //从最高位开始传输
    IIC_Wait_Ack(PIN_OPT);	
  }
  IIC_Stop(PIN_OPT);                                              //结束信号
  delay_ms(3);			
}

void IIC_BUS_Write_4_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,uc32 data)
{
  u8 dat_i;
  static u8 send_data;
  IIC_Start(PIN_OPT);				                  //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                    //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,Sub_Addr);		                  //发送8位寄存器地址
  IIC_Wait_Ack(PIN_OPT);
  for(dat_i=0;dat_i<4;dat_i++)
  {
    send_data=(u8)(((data>>(24-dat_i*8))&0xff));
    IIC_Send_Byte(PIN_OPT,send_data);                          //从最高位开始传输
    IIC_Wait_Ack(PIN_OPT);	
  }
  IIC_Stop(PIN_OPT);                                              //结束信号
  delay_ms(3);			
}

void IIC_BUS_Write_More_Byte_2_Byte_Rigister_Address(T_I2C_Master_PIN_OPT * PIN_OPT,u16 Sub_Addr,u16 dat_Length,const u8 *txd)
{
  u8 Hiaddres,Loaddres;
  u16 dat_i;
  IIC_Start(PIN_OPT);				                  //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                    //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);

  //address2

	Hiaddres=(u8)(Sub_Addr>>8);
	Loaddres=(u8)(0x00ff & Sub_Addr);
//high byte	
	IIC_Send_Byte(PIN_OPT,Hiaddres);		                  //发送高8位寄存器地址
//ack of high byte	
	IIC_Wait_Ack(PIN_OPT);
//low byte	
	IIC_Send_Byte(PIN_OPT,Loaddres);		                  //发送低8位寄存器地址
//ack of low byte	
	IIC_Wait_Ack(PIN_OPT);

  for(dat_i=0;dat_i<dat_Length;dat_i++)
  {
    IIC_Send_Byte(PIN_OPT,*(txd+dat_i));                 //从最高位开始传输
    IIC_Wait_Ack(PIN_OPT);
  }
  IIC_Stop(PIN_OPT);                                              //结束信号
  delay_ms(3);			
}


u8 IIC_BUS_Read_One_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr)
{
  u8 Read_dat;
  IIC_Start(PIN_OPT);  				           //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                     //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,((Sub_Addr<<1)|0x00));		                   //发送8位寄存器地址
  IIC_Wait_Ack(PIN_OPT);
  IIC_Start(PIN_OPT);                                             //再一次的起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x01));                      //发送7位设备地址+读标志
  IIC_Wait_Ack(PIN_OPT);
  Read_dat=IIC_Read_Byte(PIN_OPT,1);                               //接收数据并发送ACK
  Read_dat=Read_dat<<8;	
  Read_dat=IIC_Read_Byte(PIN_OPT,0);                               //接收数据并发送NACK
  IIC_Stop(PIN_OPT);                                              //结束信号
  delay_ms(3);                                            //结束信号
  return Read_dat;		
}

void IIC_BUS_Read_More_Byte(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u8 *rxd,u8 dat_Length)
{
   u8 dat_i;
   IIC_Start(PIN_OPT);  						//起始信号
   IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                         //发送7位设备地址+写标志
   IIC_Wait_Ack(PIN_OPT);
   IIC_Send_Byte(PIN_OPT,Sub_Addr);				        //发送8位寄存器地址
   IIC_Wait_Ack(PIN_OPT);
   IIC_Start(PIN_OPT);                               			//再一次的起始信号
   IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x01));    	                //发送7位设备地址+读标志
   IIC_Wait_Ack(PIN_OPT);
   for(dat_i=0;dat_i<dat_Length;dat_i++)
   {
      *(rxd+dat_Length)=IIC_Read_Byte(PIN_OPT,(dat_Length-1-dat_i));    //接收到最后一个字节不发送应答
   }
   IIC_Stop(PIN_OPT);                                			//结束信号		
}

/*
uc8 Data[]=
{Address,Length,Data0,Data1.......}
*/
void IICDataDownload(uc8 *Register,T_I2C_Master_PIN_OPT * IICCompment,u16 ArrayLength)
{
	u16 ArrayCount=0;
	u8  RegisterAddress;
	u8  RegisterDataLength;
	while(ArrayCount<ArrayLength)
	{
		RegisterAddress=*(Register+ArrayCount);
		ArrayCount++;
		RegisterDataLength=*(Register+ArrayCount);
		ArrayCount++;
		IIC_BUS_Write_More_Byte(IICCompment,RegisterAddress,(Register+ArrayCount),RegisterDataLength);
		ArrayCount+=RegisterDataLength;
	}
}

void IIC_BUS_Read_More_Byte_2_Byte_Rigister_Address(T_I2C_Master_PIN_OPT * PIN_OPT,u16 Sub_Addr,u8 *rxd,u16 dat_Length)
{
  u8 Hiaddres,Loaddres;
  u16 dat_i;
  u8 temp;
  IIC_Start(PIN_OPT);				                  //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                    //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);

  //address2

	Hiaddres=(u8)(Sub_Addr>>8);
	Loaddres=(u8)(0x00ff & Sub_Addr);
//high byte	
	IIC_Send_Byte(PIN_OPT,Hiaddres);		                  //发送高8位寄存器地址
//ack of high byte	
	IIC_Wait_Ack(PIN_OPT);
//low byte	
	IIC_Send_Byte(PIN_OPT,Loaddres);		                  //发送低8位寄存器地址
//ack of low byte	
	IIC_Wait_Ack(PIN_OPT);

	
	IIC_Start(PIN_OPT); 											//再一次的起始信号
	IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x01));					  //发送7位设备地址+读标志
	IIC_Wait_Ack(PIN_OPT);
	for(dat_i=0;dat_i<dat_Length;dat_i++)
   {
	  temp=dat_Length-1-dat_i;
	  *(rxd+temp)=IIC_Read_Byte(PIN_OPT,temp);    //接收到最后一个字节不发送应答
   }
  IIC_Stop(PIN_OPT);                                              //结束信号
  delay_ms(3);			
}

void IIC_BUS_Write_7Bitadd_9Bitdata(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr,u16 txd)
{
  IIC_Start(PIN_OPT);				                 //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00)); //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,(Sub_Addr << 1)|(txd >>8));		             	//发送8位寄存器地址
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,txd);                      	 //发送需要写入寄存器的数据
  IIC_Wait_Ack(PIN_OPT);
  IIC_Stop(PIN_OPT);                                //结束信号
  delay_ms(3);
}
u8 IIC_BUS_Read_8Bitdata(T_I2C_Master_PIN_OPT * PIN_OPT,u8 Sub_Addr)
{
  u8 Read_dat;
  IIC_Start(PIN_OPT);  				           //起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x00));                     //发送7位设备地址+写标志
  IIC_Wait_Ack(PIN_OPT);
  IIC_Send_Byte(PIN_OPT,Sub_Addr);		                   //发送8位寄存器地址
  IIC_Wait_Ack(PIN_OPT);
  IIC_Start(PIN_OPT);                                             //再一次的起始信号
  IIC_Send_Byte(PIN_OPT,(PIN_OPT->Slave_Address|0x01));                      //发送7位设备地址+读标志
  IIC_Wait_Ack(PIN_OPT);
//  Read_dat=IIC_Read_Byte(PIN_OPT,1);                               //接收数据并发送ACK
//  Read_dat=Read_dat<<8;	
  Read_dat=IIC_Read_Byte(PIN_OPT,0);                               //接收数据并发送NACK
  IIC_Stop(PIN_OPT);                                              //结束信号
  delay_ms(3);                                            //结束信号
  return Read_dat;		
}



/***************************END_FILE********************************/

