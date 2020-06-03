/*
 * userFlashV2.c
 *
 *  Created on: Apr 19, 2020
 *      Author: who_you_are
 */
#include "userFlashV2.h"
#include "em_msc.h"

#include "em_emu.h"
#include "stdlib.h"
// v2.1


// onoffsch
void writeOnOffSch2FlashV2(char* str)
{
	emberAfCorePrintln("writeOnOffSch2Flashv2");
	for(uint8_t i=0;i<FLASHMAXV2;i++)
	{
		char data[2]={0,0};
		memcpy(data,((uint32_t*)ONOFFSCHEDULEDATA +i*ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX/4),2);
		emberAfCorePrintln("writeOnOffSch2Flashv2--for[%d]:%d",i,data[0]);
		// check empty flash to write
		if(data[0]==0xff && data[1]==0xff)
		{
			emberAfCorePrintln("writeOnOffSch2Flash_2:%d",i);
			 MSC_Init();
			 MSC_WriteWord(((uint32_t*)ONOFFSCHEDULEDATA +i*ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX/4),str,ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX);
			 MSC_Deinit();
			 if(i!=0)
			 {
				 deletePeriousOnOffSch(i);
			 }
			 onOfffSchFlash2RamV2();
			 return;
		}
		if(i == (FLASHMAXV2 -1))
		{
			emberAfCorePrintln("full page");
			updateFlash(str,onOffSch);
//			onOfffSchFlash2RamV2();
//			MSC_ErasePage((uint32_t*)USERDATAV2 ); // have to delete page
//			onOffSchRam2Flash();
//			writeOnOffSch2Flash(onOffSchRam);
		}
	}
}

void onOfffSchFlash2RamV2()
{
	for(uint8_t i=0;i<FLASHMAXV2;i++)
	{
		char data[2]={0,0};
		emberAfCorePrintln("onOfffSchFlash2RamV2");
		memcpy(data,((uint32_t*)ONOFFSCHEDULEDATA +i*ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX/4),2);

		emberAfCorePrintln("for:%d",data[0]);
		if((data[0]!=0||data[1]!=0) && (data[0]!=0xff || data[1]!=0xff))
		{
			emberAfCorePrintln("onOfffSchFlash2RamV2--for:%d",i);
			char str[ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX];
			memcpy(str,(uint32_t*)ONOFFSCHEDULEDATA+ i*ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX/4,ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX);
			schedule_onoff_array_cast(onOffSchRam,ONOFFSCHEDULEMAX, str);
			return;
		}
		else if(data[0]==0xff && data[1]==0xff)
		{
			emberAfCorePrintln("onOffSchFlash empty");
			resetOnOffSchRam();
			// delete onOffSchRam
			return;
		}
	}
}


void deletePeriousOnOffSch(uint8_t pointer)
{
	char data[4]={0,0,0,0};
	emberAfCorePrintln("deletePeriousSch:%d,%s",data[0],data);
	if(pointer==0)
	{
		return;
	}
	MSC_Init();
	MSC_WriteWord(((uint32_t*)ONOFFSCHEDULEDATA +(pointer-1)*ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX/4),data,4);  // -1 to delete previous data
	MSC_Deinit();

}

void resetOnOffSchRam()
{
	emberAfCorePrintln("resetOnOffSchRam");
	schedule_onoff_t reset;
	reset.address =0;
	reset.value =0;
	reset.time.hour = 0;
	reset.time.minute =0;
	reset.time.reserve =0;
	reset.time.second =0;
	for(int i=0;i<ONOFFSCHEDULEMAX;i++)
	{
		onOffSchRam[i]=reset;
	}
}

// dimming schdule

void writeDimmingSch2FlashV2(char* str)
{
	emberAfCorePrintln("writeDimmingSch2FlashV2");
	for(uint8_t i=0;i<FLASHMAXV2;i++)
	{
		char data[2]={0,0};
		memcpy(data,((uint32_t*)DIMMINGSCHEDULEDATA +i*DIMMINGSCHSIZE*DIMMINGSCHMAX/4),2);
		emberAfCorePrintln("writeDimmingSch2FlashV2--data[%d]:%d",i,data[0]);
		// check empty flash to write
		if(data[0]==0xff && data[1]==0xff)
		{
			emberAfCorePrintln("writeDimmingSch2FlashV2:%d",i);
			 MSC_Init();
			 MSC_WriteWord(((uint32_t*)DIMMINGSCHEDULEDATA +i*DIMMINGSCHSIZE*DIMMINGSCHMAX/4),str,DIMMINGSCHSIZE*DIMMINGSCHMAX);
			 MSC_Deinit();
			 if(i!=0)
			 {
				 deletePeriousDimmingSch(i);
			 }

			 dimmingSchFlash2RamV2();
			 return;
		}
		if(i == (FLASHMAXV2 -1))
		{
			emberAfCorePrintln("full page");
			updateFlash(str,dimmingSch);
//			onOfffSchFlash2RamV2();
//			MSC_ErasePage((uint32_t*)USERDATAV2 ); // have to delete page
//			onOffSchRam2Flash();
//			writeOnOffSch2Flash(onOffSchRam);
		}
	}
}

void dimmingSchFlash2RamV2()
{
	for(uint8_t i=0;i<FLASHMAXV2;i++)
	{
		char data[2]={0,0};
		emberAfCorePrintln("dimmingSchFlash2RamV2");
		memcpy(data,((uint32_t*)DIMMINGSCHEDULEDATA +i*DIMMINGSCHSIZE*DIMMINGSCHMAX/4),2);
		emberAfCorePrintln("data:%d",data[0]);
		if((data[0]!=0||data[1]!=0) && (data[0]!=0xff || data[1]!=0xff))
		{
			emberAfCorePrintln("dimmingSchFlash2RamV2--for:%d",i);
			char str[DIMMINGSCHSIZE*DIMMINGSCHMAX];
			memcpy(str,(uint32_t*)DIMMINGSCHEDULEDATA+ i*DIMMINGSCHSIZE*DIMMINGSCHMAX/4,DIMMINGSCHSIZE*DIMMINGSCHMAX);
			schedule_dimming_array_cast(dimmingSchRam,DIMMINGSCHMAX, str);
			return;
		}
		else if(data[0]==0xff&&data[1]==0xff)
		{
			emberAfCorePrintln("dimmingSchFlash empty");
			resetDimmingSchRam();
			// delete onOffSchRam
			return;
		}
	}
}

void deletePeriousDimmingSch(uint8_t pointer)
{
	char data[4]={0,0,0,0};
	emberAfCorePrintln("deletePeriousDimmingSch:%d,%s",data[0],data);
	if(pointer==0)
	{
		return;
	}
	MSC_Init();
	MSC_WriteWord(((uint32_t*)DIMMINGSCHEDULEDATA +(pointer-1)*DIMMINGSCHSIZE*DIMMINGSCHMAX/4),data,4);  // -1 to delete previous data
	MSC_Deinit();

}

void resetDimmingSchRam()
{
	emberAfCorePrintln("resetDimmingSchRam");
	schedule_dimming_t reset;
	reset.address =0;
	reset.value =0;
	reset.time.hour = 0;
	reset.time.minute =0;
	reset.time.reserve =0;
	reset.time.second =0;
	for(int i=0;i<DIMMINGSCHMAX;i++)
	{
		dimmingSchRam[i]=reset;
	}
}


// group

void writeGroupSch2FlashV2(char* str)
{
	emberAfCorePrintln("writeGroupSch2FlashV2");
	for(uint8_t i=0;i<FLASHMAXV2;i++)
	{
		char data[2]={0,0};
		memcpy(data,((uint32_t*)GROUPSCHDATA +i*GROUPSCHSIZE*GROUPSCHMAX/4),2);
		emberAfCorePrintln("writeGroupSch2FlashV2--data[%d]:%d",i,data[0]);
		// check empty flash to write
		if(data[0]==0xff && data[1]==0xff)
		{
			emberAfCorePrintln("writeGroupSch2FlashV2:%d",i);
			 MSC_Init();
			 MSC_WriteWord(((uint32_t*)GROUPSCHDATA +i*GROUPSCHSIZE*GROUPSCHMAX/4),str,GROUPSCHSIZE*GROUPSCHMAX);
			 MSC_Deinit();
			 if(i!=0)
			 {
				 deletePeriousGroupSch(i);
			 }

			 groupSchFlash2RamV2();
			 return;
		}
		if(i == (FLASHMAXV2 -1))
		{
			emberAfCorePrintln("full page");
			updateFlash(str,groupSch);
//			onOfffSchFlash2RamV2();
//			MSC_ErasePage((uint32_t*)USERDATAV2 ); // have to delete page
//			onOffSchRam2Flash();
//			writeOnOffSch2Flash(onOffSchRam);
		}
	}
}

void groupSchFlash2RamV2()
{
	for(uint8_t i=0;i<FLASHMAXV2;i++)
	{
		char data[2]={0,0};
		emberAfCorePrintln("groupSchFlash2RamV2");
		memcpy(data,((uint32_t*)GROUPSCHDATA +i*GROUPSCHSIZE*GROUPSCHMAX/4),2);
		emberAfCorePrintln("data:%d",data[0]);
		if((data[0]!=0||data[1]!=0) && (data[0]!=0xff || data[1]!=0xff))
		{
			emberAfCorePrintln("groupSchFlash2RamV2--for:%d",i);
			char str[GROUPSCHSIZE*GROUPSCHMAX];
			memcpy(str,(uint32_t*)GROUPSCHDATA+ i*GROUPSCHSIZE*GROUPSCHMAX/4,GROUPSCHSIZE*GROUPSCHMAX);
			group_array_cast(groupSchRam,GROUPSCHMAX, str);
			return;
		}
		else if(data[0]==0xff&&data[1]==0xff)
		{
			emberAfCorePrintln("onOffSchFlash empty");
			resetGroupSchRam();
			// delete onOffSchRam
			return;
		}
	}
}

void deletePeriousGroupSch(uint8_t pointer)
{
	char data[4]={0,0,0,0};
	emberAfCorePrintln("deletePeriousGroupSch:%d,%s",data[0],data);
	if(pointer==0)
	{
		return;
	}
	MSC_Init();
	MSC_WriteWord(((uint32_t*)GROUPSCHDATA +(pointer-1)*GROUPSCHSIZE*GROUPSCHMAX/4),data,4);  // -1 to delete previous data
	MSC_Deinit();

}

void resetGroupSchRam()
{
	emberAfCorePrintln("resetGroupSchRam");
	group_t reset;
	reset.address =0;
	for(int i=0;i<GROUPSCHMAX;i++)
	{
		groupSchRam[i]=reset;
	}
}

//  mai xu ly tiep ok!!!
void updateFlash(char* String,uint8_t type)
{// group// dimming // onoff
	char onOffSchString[ONOFFSCHEDULEMAX*ONOFFSCHEDULESIZE];
	char groupSchString[GROUPSCHMAX*GROUPSCHSIZE];
	char dimmingSchString[DIMMINGSCHMAX*DIMMINGSCHSIZE];
	// convert to string to save to flash//
	schedule_dimming_array_string(dimmingSchRam,DIMMINGSCHMAX,dimmingSchString);
	schedule_onoff_array_string(onOffSchRam,ONOFFSCHEDULEMAX,onOffSchString);
	group_array_string(groupSchRam,GROUPSCHMAX,groupSchString);

	MSC_ErasePage((uint32_t*)USERDATAV2 ); // have to delete page
	switch(type)
	{
		case groupSch:
			emberAfCorePrintln("groupSch");
//			MSC_Init();
			writeGroupSch2FlashV2(String);

			writeDimmingSch2FlashV2(dimmingSchString);
			writeOnOffSch2FlashV2(onOffSchString);
//			MSC_Deinit();
			groupSchFlash2RamV2();
			break;
		case onOffSch:
			emberAfCorePrintln("onOffSch");
//			MSC_Init();
			writeOnOffSch2FlashV2(String);

			writeDimmingSch2FlashV2(dimmingSchString);
			writeGroupSch2FlashV2(groupSchString);
//			MSC_Deinit();
			onOfffSchFlash2RamV2();
			break;
		case dimmingSch:
			emberAfCorePrintln("dimmingSch");
//			MSC_Init();
			writeDimmingSch2FlashV2(String);

			writeOnOffSch2FlashV2(onOffSchString);
			writeGroupSch2FlashV2(groupSchString);
//			MSC_Deinit();
			dimmingSchFlash2RamV2();
			break;
	}
//	writeOnOffSch2FlashV2
//	writeDimmingSch2FlashV2
//	writeGroupSch2FlashV2
//	MSC_Init();
//	//MSC_WriteWord(((uint32_t*)ONOFFSCHEDULEDATA),schString,ONOFFSCHEDULESIZE*ONOFFSCHEDULEMAX);
//	MSC_Deinit();
//	onOfffSchFlash2RamV2();
}
