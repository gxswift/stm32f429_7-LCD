/***
	***************************************************************************
	*	@file  	Touch.c
	*	@brief   ���ݴ�����ʵ�֣�ʹ��IO��ģ��IIC������GT9XXϵ��
	*				���ݴ���оƬ����ͨ��
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include "Touch.h"

TouchStructure touchInfo; //������Ϣ�ṹ��

/*---------------------- IIC��غ��� ------------------------*/

// ����: ����ʱ����
//	˵����Ϊ����ֲ�ļ�����Ҷ���ʱ���Ȳ��ߣ����Բ���Ҫ���ж�ʱ����ʱ
//
void IIC_Touch_Delay(u16 a)
{
	int i;
	while (a --)
	{
		for (i = 0; i < 5; i++);
	}
}

//	����������IIC�����ݽ�Ϊ���ģʽ
//
void IIC_Touch_SDA_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		   	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_InitStructure.GPIO_Pin = IIC_Touch_SDA_PIN ;  	
	GPIO_Init(IIC_Touch_SDA_PORT, &GPIO_InitStructure);		
}

//	����������IIC�����ݽ�Ϊ����ģʽ
//
void IIC_Touch_SDA_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_InitStructure.GPIO_Pin = IIC_Touch_SDA_PIN ;  	
	GPIO_Init(IIC_Touch_SDA_PORT, &GPIO_InitStructure);
}

//	������IIC��ʼ�ź�
//
void IIC_Touch_Start(void)
{
	IIC_Touch_SDA_Out();
	
	SDA(1);
	SCL(1);
	IIC_Touch_Delay( Touch_DelayVaule );
	
	SDA(0);
	IIC_Touch_Delay( Touch_DelayVaule );
	SCL(0);
	IIC_Touch_Delay( Touch_DelayVaule );
}

//	������IICֹͣ�ź�
//
void IIC_Touch_Stop(void)
{
    SCL(0);
    IIC_Touch_Delay( Touch_DelayVaule );
    SDA(0);
    IIC_Touch_Delay( Touch_DelayVaule );
    SCL(1);
    IIC_Touch_Delay( Touch_DelayVaule );
    SDA(1);
    IIC_Touch_Delay( Touch_DelayVaule );
}

//	������IICӦ���ź�
//
void IIC_Touch_Response(void)
{
	IIC_Touch_SDA_Out();

	SDA(0);
	IIC_Touch_Delay( Touch_DelayVaule );	
	SCL(1);
	IIC_Touch_Delay( Touch_DelayVaule );
	SCL(0);
	IIC_Touch_Delay( Touch_DelayVaule );
}

//	������IIC��Ӧ���ź�
//
void IIC_Touch_NoResponse(void)
{
	IIC_Touch_SDA_Out();
	
	SCL(0);	
	IIC_Touch_Delay( Touch_DelayVaule );
	SDA(1);
	IIC_Touch_Delay( Touch_DelayVaule );
	SCL(1);
	IIC_Touch_Delay( Touch_DelayVaule );
	SCL(0);
	IIC_Touch_Delay( Touch_DelayVaule );
}

//	�������ȴ��豸������Ӧ�ͺ�
//
u8 IIC_Touch_WaitResponse(void)
{

	SCL(0);
	IIC_Touch_Delay( Touch_DelayVaule );
	SDA(1);
	IIC_Touch_Delay( Touch_DelayVaule );
	SCL(1);

	IIC_Touch_SDA_In();	//����Ϊ����ģʽ
	IIC_Touch_Delay( Touch_DelayVaule );
	
	SCL(0);	
	if( GPIO_ReadInputDataBit(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN) != 0) //�ж��豸�Ƿ���������Ӧ
	{		
		return (Response_ERR);
	}
	else
	{
		return (Response_OK);
	}

}

// ������IICд�ֽ�
//	������IIC_Data - Ҫд���8λ����
//	���أ��豸����Ӧ�򷵻� 1������Ϊ0
//
u8 IIC_Touch_WriteByte(u8 IIC_Data)
{
	u8 i;

	IIC_Touch_SDA_Out(); //���ݽ�Ϊ���ģʽ
	
	for (i = 0; i < 8; i++)
	{
		SDA(IIC_Data & 0x80);
		
		IIC_Touch_Delay( Touch_DelayVaule );
		SCL(1);
		IIC_Touch_Delay( Touch_DelayVaule );
		SCL(0);		
		
		IIC_Data <<= 1;
	}

	return (IIC_Touch_WaitResponse()); //�ȴ��豸��Ӧ
}

// ������IIC���ֽ�
//	������ResponseMode - Ӧ��ģʽѡ��
//       ResponseMode = 1 ʱ��CPU������Ӧ�źţ�Ϊ 0 ʱ��CPU������Ӧ���ź�
//	���أ�����������
//
u8 IIC_Touch_ReadByte(u8 ResponseMode)
{
	u8 IIC_Data;
	u8 i;
	
	SDA(1);
	SCL(0);

	IIC_Touch_SDA_In(); //����ģʽ
	
	//��һ�ֽ�����
	for (i = 0; i < 8; i++)
	{
		IIC_Data <<= 1;
		
		SCL(1);
		IIC_Touch_Delay( Touch_DelayVaule );

		IIC_Data |= (GPIO_ReadInputDataBit(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN) & 0x01);
		
		SCL(0);
		IIC_Touch_Delay( Touch_DelayVaule );
	}

	//	������Ӧ�ź�
	if (ResponseMode)
	{
		IIC_Touch_Response();
	}
	else
	{
		IIC_Touch_NoResponse();
	}
	
	return (IIC_Data); 
}

//	��������ʼ��IIC��GPIO��
//
void IIC_Touch_GPIO_Config (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(IIC_Touch_SCL_CLK | IIC_Touch_SDA_CLK , ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	   
	
	//SCL
	GPIO_InitStructure.GPIO_Pin = IIC_Touch_SCL_PIN; 	
	GPIO_Init(IIC_Touch_SCL_PORT, &GPIO_InitStructure);				   	

	//SDA	
	GPIO_InitStructure.GPIO_Pin = IIC_Touch_SDA_PIN; 
	GPIO_Init(IIC_Touch_SDA_PORT, &GPIO_InitStructure);				   

	GPIO_ResetBits(IIC_Touch_SCL_PORT,IIC_Touch_SCL_PIN);
	GPIO_ResetBits(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN);
	
}

/*---------------------- GT9XX��غ��� ------------------------*/

// ������GT9XX д����
//	������addr - Ҫ�����ļĴ���
//			
u8 GT9XX_WriteHandle (u16 addr)
{
	u8 status;

	IIC_Touch_Start();
	if( IIC_Touch_WriteByte(GT9XX_IIC_WADDR) == Response_OK ) //д����ָ��
	{
		if( IIC_Touch_WriteByte((u8)(addr >> 8)) == Response_OK ) //д��16��ַ
		{
			if( IIC_Touch_WriteByte((u8)(addr)) != Response_OK )
			{
				status = ERROR;
			}			
		}
	}
	status = SUCCESS;
	return status;	
}

// ������GT9XX д����
//	������addr - Ҫд���ݵĵ�ַ
//			value - д�������
//
u8 GT9XX_WriteData (u16 addr,u8 value)
{
	u8 status;
	
	IIC_Touch_Start(); //����IICͨѶ

	if( GT9XX_WriteHandle(addr) == SUCCESS)	//д��Ҫ�����ļĴ���
	{
		if (IIC_Touch_WriteByte(value) != Response_OK) //д����
		{
			status = ERROR;						
		}
	}
	
	IIC_Touch_Stop(); //ֹͣͨѶ
	
	status = SUCCESS;
	return status;
}

// ������GT9XX ������
//	������addr - Ҫ�����ݵĵ�ַ
//			num - �������ֽ���
//			*value - ���ڻ�ȡ�洢���ݵ��׵�ַ
//
u8 GT9XX_ReadData (u16 addr, u8 cnt, u8 *value)
{
	u8 status;
	u8 i;

	status = ERROR;
	IIC_Touch_Start();

	if( GT9XX_WriteHandle(addr) == SUCCESS) //д��Ҫ�����ļĴ���
	{
		IIC_Touch_Start(); //��������IICͨѶ

		if (IIC_Touch_WriteByte(GT9XX_IIC_RADDR) == Response_OK)
		{	
			for(i = 0 ; i < cnt; i++)
			{
				if (i == (cnt - 1))
				{
					value[i] = IIC_Touch_ReadByte(0);//�������һ������ʱ���� ��Ӧ���ź�
				}
				else
				{
					value[i] = IIC_Touch_ReadByte(1);
				}

			}					
			IIC_Touch_Stop();
			status = SUCCESS;
		}
	}
	
	IIC_Touch_Stop();
	return (status);	
}

// ����: ��������ʼ��
//
void Touch_Init(void)
{
	IIC_Touch_GPIO_Config(); //��ʼ������ͨ�ŵ�IIC����
}

// ����������ɨ��
//	˵�����ڳ����������Եĵ��øú��������Լ�ⴥ������
//
u8	Touch_Scan(void)
{
 	u8  touchData[2 + 8 * TOUCH_MAX ]; //���ڴ洢��������
memset(touchData,0,10);
	GT9XX_ReadData (GT9XX_READ_ADDR,2 + 8 * TOUCH_MAX ,touchData);	//������
	GT9XX_WriteData (GT9XX_READ_ADDR,0);	//	�������оƬ�ļĴ�����־λ
	touchInfo.num = touchData[0] & 0x0f;	//ȡ��ǰ�Ĵ�������
	
	if ( (touchInfo.num ) ) //���������� 1-5 ֮��ʱ>= 1) && (touchInfo.num <=5
	{
		// ȡ��Ӧ�Ĵ�������
	if(touchData[5]<200)
						touchInfo.y[0] = ((touchData[5]<<8) | touchData[4])*0.81+1;

		if(touchData[3]<200)
				touchInfo.x[0] = ((touchData[3]<<8) | touchData[2])*0.78+1;	

		return	SUCCESS ;	
	}

	else                       
	{	
		
		touchInfo.x[0] = 0;
		touchInfo.y[0] = 0;

		return	ERROR ;		
	}
	
}



