/*
 * userMemory.c
 *
 *  Created on: Dec 13, 2019
 *      Author: who_you_are
 */
#include "userFlash.h"
#include "em_msc.h"

#include "em_emu.h"
#include "stdlib.h"


Sub readSubRam(uint16_t add )
{
	Sub data ={0,0,0,0,0,0,0,"\0"};
	for(uint8_t i=0;i<FLASHMAX;i++)
	{
		// Sub read = ramSubData[i];
//		 emberAfCorePrintln("--read--x:%d--y:%d",read.x,read.y);
		if(ramSubData[i].Address==add)
		{
			return ramSubData[i];
		}
		else if(ramSubData[i].Address ==0xffff)
		{
			return data;
		}
	}
	return data;
}
void writeFlash(Sub dataIn)
{
		for(uint8_t i=0;i<FLASHMAX;i++)
		{
			Sub data = *((Sub*)(USERDATA + 2+i*sizeof(Sub)/4));
			if(data.Address==0xffff)
			{
				 MSC_Init();
				 MSC_WriteWord(((uint32_t*)USERDATA_BASE + 2+ i*sizeof(Sub)/4),&dataIn,sizeof(Sub));
				 MSC_Deinit();
				 flashToRam();
				 return;
			}
			if(i == (FLASHMAX -1))
			{
				flashToRam();
				MSC_ErasePage((uint32_t*)USERDATA_BASE );
				ramToFlash();
				writeFlash(data);
			}
		}
}
void deleteFlash(uint16_t add)
{
	Sub delete={0,0,0,0,0,0,0,"\0"};
	for(uint8_t i=0;i<FLASHMAX;i++)
	{
		Sub data =*((Sub*)(USERDATA + 2+i*sizeof(Sub)/4));
		if(data.Address ==add)
		{
			 MSC_Init();
			 MSC_WriteWord(((uint32_t*)USERDATA_BASE + 2+ i*sizeof(Sub)/4),&delete,sizeof(Sub));
			 MSC_Deinit();

			 // cap nhat  lai bang gtri
			 flashToRam();
			 return;
		}
		else if(data.Address ==0xffff)
		{
			return;
		}
	}
}
void flashToRam()
{
	uint8_t count =0;
	Sub init ={0xffff,0,0,0,0,0,0,"\0"};
	for(uint8_t i=0;i<FLASHMAX;i++)
	{
		Sub data =*((Sub*)(USERDATA + 2+i*sizeof(Sub)/4));
		if(data.Address != 0 && data.Address!= 0xffff)
		{
			ramSubData[count] = data;
			count++;
		}
		else if(data.Address == 0xffff)
		{
			ramSubData[count] = init;
			return;
		}
	}
}
void ramToFlash()
{
	   //Clear the Userdata page of any previous data stored
	MSC_ErasePage((uint32_t*)USERDATA_BASE );
	for(uint8_t i =0;i<FLASHMAX;i++)
	{
		if(ramSubData[i].Address!=0&&ramSubData[i].Address!=0xffff)
		{
			MSC_Init();
			MSC_WriteWord(((uint32_t*)(USERDATA_BASE + 2+i*sizeof(Sub)/4)),&ramSubData[i],sizeof(Sub));
			MSC_Deinit();
		}
		else
		{
			return;
		}
	}
}
