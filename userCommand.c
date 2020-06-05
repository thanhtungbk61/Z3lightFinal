/*
 * userCommand.c
 *
 *  Created on: Dec 16, 2019
 *      Author: who_you_are
 */

#include "af.h"
#include "userCommand.h"

// client to server
uint8_t getPing(uint8_t* value)
{
	//uint8_t sendType;
	uint8_t status;
//	uint8_t value[8]={0,0,0,0,0,0,0,0};
	emberAfFillCommandManagerGetPing(value);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =netR.cluster;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =1;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x00);// 0x00 = coordinator
	return status;
}

uint8_t reportPing(uint8_t* value)
{
	//uint8_t sendType;
	uint8_t status;
//	uint8_t value[8]={0,0,0,0,0,0,0,0};
	emberAfFillCommandManagerPutPing(value);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =netR.cluster;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =1;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x00);// 0x00 = coordinator
	return status;
}

uint8_t addGroupRespond(uint8_t stt,EmberNodeId nodeid,uint16_t groupId)
{
	uint8_t status=1;
	emberAfFillCommandGroupsClusterAddGroupResponse(stt,groupId);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =0x0006;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =0x0001;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,nodeid);

	return status;
}
//
void sendAddGroupCommand(uint16_t groupId,uint8_t* groupName,uint16_t destination)
{
	EmberStatus  test2;
	//emberAfCorePrintln("---testSendCommandUnicast--final: %d",test2);
	emberAfFillCommandGroupsClusterAddGroup(groupId, groupName);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
	emAfCommandApsFrame->clusterId =0x0004;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =0x0001;

	test2 =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,destination);
	emberAfCorePrintln("---sendAddGroupCommand--final: %d",test2);
}
//void addGroup(Sub frame)
//{
//	EmberStatus  test2;
//	//uint16_t groupId =1;
//	//nodeId = emberAfGetNodeId();
//	emberAfCorePrintln("---addGroup-- address:%d",frame.Address);
//	// tu them dia chi
//	emberAfFillCommandGroupsClusterAddGroup(frame.Address,"");
//	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =0x0004;
//	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
//	emAfCommandApsFrame->destinationEndpoint =0x0001;
//	test2 =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,emberAfGetNodeId());
//	emberAfCorePrintln("---sendAddGroupCommand--final: %d",test2);
//}

uint8_t reportLevelAttribute()
{
	uint8_t level;
	uint8_t status=1;
    if (emberAfReadServerAttribute(1,
			   ZCL_LEVEL_CONTROL_CLUSTER_ID,
			   ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
            (uint8_t *)&level,
            sizeof(level))
        == EMBER_ZCL_STATUS_SUCCESS)
    {
	//uint8_t attributeId[2] ={0x40,0x02};
	uint8_t buf[5];
	buf[0] =0;  // attribute
	buf[1]=0;   // attribute
	buf[2]=0;   // status
	buf[3]=0x20;  // type value
	buf[4]=level;  //  value
	emberAfFillCommandGlobalServerToClientReportAttributes(ZCL_LEVEL_CONTROL_CLUSTER_ID,buf,5);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =0x0006;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =0x0001;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x0000);
    }
	return status;
}

uint8_t reportSensor()
{
	static uint16_t count;
	count++;
	emberAfWriteServerAttribute(1,ZCL_ILLUM_MEASUREMENT_CLUSTER_ID,ZCL_ILLUM_MEASURED_VALUE_ATTRIBUTE_ID,&count,0x21);
	uint16_t value;
	uint8_t status=1;
//    if (emberAfReadServerAttribute(1,
//    		ZCL_ILLUM_MEASUREMENT_CLUSTER_ID,
//			ZCL_ILLUM_MEASURED_VALUE_ATTRIBUTE_ID,
//            (uint8_t *)&value,
//            sizeof(value))
//        == EMBER_ZCL_STATUS_SUCCESS)
//    {
	//uint8_t attributeId[2] ={0x40,0x02};
	uint8_t buf[6];
	buf[0] =0;  // attribute
	buf[1]=0;   // attribute
	buf[2]=0;   // status
	buf[3]=0x20;  // type value
	buf[4]=(uint8_t)count;  //  value
	buf[5]=(uint8_t) count&0x00ff;
	emberAfFillCommandGlobalServerToClientReportAttributes(ZCL_ILLUM_MEASUREMENT_CLUSTER_ID,buf,6);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =0x0006;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =0x0001;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x0000);
//    }
	return status;
}
uint8_t reportLightAttribute()
{
	bool onOff;
	uint8_t status=1;
    if (emberAfReadServerAttribute(1,
                                   ZCL_ON_OFF_CLUSTER_ID,
                                   ZCL_ON_OFF_ATTRIBUTE_ID,
                                   (uint8_t *)&onOff,
                                   sizeof(onOff))
        == EMBER_ZCL_STATUS_SUCCESS)
    {
	//uint8_t attributeId[2] ={0x40,0x02};
	uint8_t buf[5];
	buf[0] =0;  // attribute
	buf[1]=0;   // attribute
	buf[2]=0;   // status
	buf[3]=16;  // type value
	buf[4]=onOff;  //  value
	emberAfFillCommandGlobalServerToClientReportAttributes(0x0006,buf,5);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =0x0006;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =0x0001;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x0000);
    }
	return status;
}

//uint8_t reportPing()
//{
//	//dimmingValue
//	uint8_t  ping;
//	uint8_t status=1;
//	status =emberAfReadManufacturerSpecificServerAttribute(1,ZCL_MANAGER_ID,ZCL_Ping_ATTRIBUTE_ID,0x10A2,&ping,sizeof(ping));
//	emberAfCorePrintln("reportDimming:%d",status);
//	//uint8_t attributeId[2] ={0x40,0x02};
//	uint8_t buf[13];
//	buf[0] =0;  // attribute
//	buf[1]=15;   // attribute
//	buf[2]=0;   // status
//	buf[3]=0x20;  // type value // uint8_t
//	buf[4]=ping;  //  value
//	emberAfFillCommandGlobalServerToClientReportAttributes(0xFC10,buf,5);
//	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
////	emAfCommandApsFrame->clusterId =0x0006;
//	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
//	emAfCommandApsFrame->destinationEndpoint =0x0001;
//	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x0000);
//	return status;
//}
uint8_t reportOnOffSchAttribute()
{
	bool onOff;
	uint8_t status=1;
    if (emberAfReadServerAttribute(1,
                                   ZCL_ON_OFF_CLUSTER_ID,
                                   ZCL_ON_OFF_ATTRIBUTE_ID,
                                   (uint8_t *)&onOff,
                                   sizeof(onOff))
        == EMBER_ZCL_STATUS_SUCCESS)
    {
	//uint8_t attributeId[2] ={0x40,0x02};
	uint8_t buf[5];
	buf[0] =0;  // attribute
	buf[1]=0;   // attribute
	buf[2]=0;   // status
	buf[3]=16;  // type value
	buf[4]=onOff;  //  value
	emberAfFillCommandGlobalServerToClientReportAttributes(0x0006,buf,5);
	emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
//	emAfCommandApsFrame->clusterId =0x0006;
	emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
	emAfCommandApsFrame->destinationEndpoint =0x0001;
	status =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,0x0000);
    }
	return status;
}

void addGroup()
{
	EmberStatus  test2;
	for(int i=0;i<GROUPSCHMAX;i++)
	{
		if(groupSchRam[i].address!=0)
		{
			emberAfCorePrintln("---addGroup-- address:%d",groupSchRam[i].address);
			// tu them dia chi
			emberAfFillCommandGroupsClusterAddGroup(groupSchRam[i].address,"");
			emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
			emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
			emAfCommandApsFrame->destinationEndpoint =0x0001;
			test2 =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,emberAfGetNodeId());
			emberAfCorePrintln("---sendAddGroupCommand--status: %d",test2);
		}

	}
}
