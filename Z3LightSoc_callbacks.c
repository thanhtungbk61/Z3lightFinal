/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.
// user include
#include "userCharStruct.h"
#include "userFlash.h"
#include "userCommand.h"
#include "userBase64.h"
#include "em_msc.h"
#include "userRTCC.h"
// v2
#include "userFlashV2.h"
#include "userJsonStruct.h"
#include "app/framework/include/af.h"
#include "userPeripheral.h"
#include EMBER_AF_API_NETWORK_CREATOR
#include EMBER_AF_API_NETWORK_CREATOR_SECURITY
#include EMBER_AF_API_NETWORK_STEERING
#include EMBER_AF_API_FIND_AND_BIND_TARGET
#include EMBER_AF_API_ZLL_PROFILE



#define LIGHT_ENDPOINT (1)
EmberEventControl myDelay;
EmberEventControl scheduleControl;

#define MY_DELAY_IN_MS 1000
EmberEventControl commissioningLedEventControl;
EmberEventControl findingAndBindingEventControl;

char* date ="010203";
char* time ="123030";
char* alarm_date ="010203";
char* alarm_time ="123130";
uint8_t pingReport[8];
uint8_t pingLen =8;
void emberAfGroupsClusterServerAttributeChangedCallback(int8u endpoint,
                                                        EmberAfAttributeId attributeId)
{
	emberAfCorePrintln("emberAfGroupsClusterServerAttributeChangedCallback");
}


void emberAfGroupsClusterServerDefaultResponseCallback(int8u endpoint,
                                                       int8u commandId,
                                                       EmberAfStatus status)
{
//	EmberNodeId userNewNodeId =emberGetSender();
//	uint8_t stt=addGroupRespond(status,userNewNodeId,groupId);
	emberAfCorePrintln("emberAfGroupsClusterServerDefaultResponseCallback:%d",status);
}
//
void printfSub(Sub s){
	emberAfCorePrintln("Address  :%d\n", s.Address);
	emberAfCorePrintln("Type     :%d\n", s.Type);
	emberAfCorePrintln("Endpoint :%d\n", s.Endpoint);
	emberAfCorePrintln("Profile  :%d\n", s.ProfileID);
	emberAfCorePrintln("Cluster  :%d\n", s.ClusterID);
	emberAfCorePrintln("Attribute:%d\n", s.AttributeID);
	emberAfCorePrintln("TypeValue:%d\n", s.ValueType);
	emberAfCorePrintln("StrValue format Light :%d\n", (int8_t)getIntFromString(s.StrValue, INT8));
}


char dimmingsch[DIMMINGSCHSIZE*DIMMINGSCHMAX] ={0x12, 0x34, 0, 21, 15, 30, 0, 100, 0x12, 0x34, 0, 0, 0, 0, 0, 100, 0x12, 0x34, 0, 23, 30, 15, 0, 100,0x12, 0x34, 0, 21, 15, 30, 0, 100, 0x12, 0x34, 0, 0, 0, 0, 0, 100, 0x12, 0x34, 0, 23, 30, 15, 0, 100,0x12, 0x34, 0, 21, 15, 30, 0, 100, 0x12, 0x34, 0, 0, 0, 0, 0, 100, 0x12, 0x34, 0, 23, 30, 15, 0, 100,0x12, 0x34, 0, 21, 15, 30, 0, 100, 0x12, 0x34, 0, 0, 0, 0, 0, 100, 0x12, 0x34, 0, 23, 30, 15, 0, 100,0x12, 0x34, 0, 21, 15, 30, 0, 100, 0x12, 0x34, 0, 0, 0, 0, 0, 100, 0x12, 0x34, 0, 23, 30, 15, 0, 100,1,2,3,4,5,6,7,8};
void scheduleHandler()
{
//	static int schduleCount;

	emberAfCorePrintln("scheduleHandler");
	emberEventControlSetInactive(scheduleControl);
	if (emberAfNetworkState() != EMBER_JOINED_NETWORK)
	{
//		GPIO_PinOutToggle(LED_PORT,LED_PIN);
		emberEventControlSetDelayMS(scheduleControl, 30 * MY_DELAY_IN_MS);
	}
	else
	{

		uint16_t year=0;
		uint8_t month=0;
		uint8_t day=0;
		uint8_t weekday=0;
		uint8_t hour=0;
		uint8_t min= 0;
		uint8_t sec= 0;
		uint16_t ms =0;
		get_date_and_time(&year,
		                  &month,
		                  &day,
		                  &weekday,
		                  &hour,
		                  &min,
		                  &sec,
		                  &ms);

		emberAfCorePrintln("hour:%d--min:%d--sec:%d",hour,min,sec);
		if(hour==0 && min==0)
		{
			emberEventControlSetDelayMS(scheduleControl, 50 * MY_DELAY_IN_MS);
			return;
		}
		for(int i=0;i<DIMMINGSCHMAX;i++)
		{
			if(dimmingSchRam[i].time.hour==hour&&dimmingSchRam[i].time.minute==min)
			{
				for(int j=0;j<GROUPSCHMAX;j++)
				{
					if((dimmingSchRam[i].address ==SELFADDRESS) || (dimmingSchRam[i].address==groupSchRam[j].address))
					{
						uint8_t dimmingValue= (uint8_t)dimmingSchRam[i].value;
						emberAfWriteServerAttribute(1,ZCL_LEVEL_CONTROL_CLUSTER_ID,ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,(uint8_t *)&dimmingValue,0x20);
						if(onOffSchRam[i].value==1)
						{
							setLevel(dimmingValue);
						}
						else
						{
							setLevel(dimmingValue);
						}
						break;
					}
				}

			}
		}
		for(int i=0;i<ONOFFSCHEDULEMAX;i++)
		{
			if(onOffSchRam[i].time.hour==hour&&onOffSchRam[i].time.minute==min)
			{
				for(int j=0;j<GROUPSCHMAX;j++)
				{
					if((onOffSchRam[i].address ==SELFADDRESS) || (onOffSchRam[i].address==groupSchRam[j].address))
					{
						bool onoffValue=onOffSchRam[i].value;
						emberAfWriteServerAttribute(1,ZCL_ON_OFF_CLUSTER_ID,ZCL_ON_OFF_ATTRIBUTE_ID,(uint8_t *)&onoffValue,0x10);
						if(onOffSchRam[i].value==1)
						{
							setLevel(100);
						}
						else
						{
							setLevel(0);
						}
						break;
					}
				}

			}
		}

		emberEventControlSetDelayMS(scheduleControl, 10 * MY_DELAY_IN_MS);
	}
}

void myDelayHandler(void)
{
	// setup peripheral
	static uint64_t mydelayCount;
	mydelayCount++;
	emberEventControlSetInactive(myDelay);
	if (emberAfNetworkState() != EMBER_JOINED_NETWORK) {

		emberAfCorePrintln("mydelayCount:%d",mydelayCount);
		if(mydelayCount ==1)
		{
			emberAfCorePrintln("delete Flash");
			MSC_ErasePage((uint32_t*)USERDATAV2 );
		}
	    EmberStatus status = emberAfPluginNetworkSteeringStart();
	    emberAfCorePrintln("%p network %p: 0x%X", "Join", "start", status);
		emberEventControlSetDelayMS(myDelay, 20 * MY_DELAY_IN_MS);
	}
	else
	{
		if(mydelayCount%2)
		{
			reportLevelAttribute();
		}
		if(mydelayCount%3)
		{
//			reportPing(pingReport);
		}
		else
		{
			reportLightAttribute();
		}


		emberEventControlSetDelayMS(myDelay, 50 * MY_DELAY_IN_MS);
	}
	uint16_t nodeId =emberAfGetNodeId();
	emberAfCorePrintln("emberAfGetNodeId:%d",nodeId);
}

void emberAfMainInitCallback(void)
{


	// init value of cluster

	pwmInit();
	TIMER_CompareBufSet(TIMER1, TIMER_CHANNEL, 100);

    emberEventControlSetActive(commissioningLedEventControl);
    emberEventControlSetDelayMS(myDelay, 1 * MY_DELAY_IN_MS);
    emberEventControlSetDelayMS(scheduleControl, 5 * MY_DELAY_IN_MS);

}
// all callback


bool emberAfManagerSetSchedualCallback(uint8_t* setSchedual)
{
	return 1;
}


void commissioningLedEventHandler(void)
{
  emberEventControlSetInactive(commissioningLedEventControl);

  static uint8_t ledCount;
  ledCount++;
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
	    onOfffSchFlash2RamV2();
	    dimmingSchFlash2RamV2();
	    groupSchFlash2RamV2();
	    //
		uint8_t dimmingValue=0,status;
		bool onoffValue=0;
		status= emberAfWriteServerAttribute(1,ZCL_LEVEL_CONTROL_CLUSTER_ID,ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,&dimmingValue,0x20);
		emberAfCorePrintln("emberAfWriteServerAttribute:%d",status);
		status =emberAfWriteServerAttribute(1,ZCL_ON_OFF_CLUSTER_ID,ZCL_ON_OFF_ATTRIBUTE_ID,(uint8_t *)&onoffValue,0x10);
		emberAfCorePrintln("emberAfReadServerAttribute:%d",status);
		setLevel(0);
  } else {
	  if(ledCount%2==0)
	  {
		  GPIO_PinOutSet(LED_PORT,LED_PIN);
		  setLevel(100);
	  }
	  else
	  {
		  setLevel(0);
	  }
	  emberAfCorePrintln("toggle_led");
//	  GPIO_PinOutToggle(LED_PORT,LED_PIN);
	  emberEventControlSetDelayMS(commissioningLedEventControl,LED_BLINK_PERIOD_MS >>1);
    EmberStatus status = emberAfPluginNetworkSteeringStart();
    emberAfCorePrintln("%p network %p: 0x%X", "Join", "start", status);
  }
}

void findingAndBindingEventHandler()
{
//	uint8_t status = reportDimming();
	emberEventControlSetInactive(findingAndBindingEventControl);
	uint32_t time = RTCC_CounterGet();

	  char test_onoff_array_have_error[ONOFFSCHEDULEMAX * ONOFFSCHEDULESIZE] = {0x12, 0x34, 0, 21, 15, 30, 1, 0x12, 0x34, 0, 0, 0, 0, 1, 0x12, 0x34, 0, 23, 30, 15, 0,0x12, 0x34, 0, 21, 15, 30, 1, 0x12, 0x34, 0, 0, 0, 0, 1, 0x12, 0x34, 0, 23, 30, 15, 0,0x12, 0x34, 0, 21, 15, 30, 1, 0x12, 0x34, 0, 0, 0, 0, 1, 0x12, 0x34, 0, 23, 30, 15, 0,0x12, 0x34, 0, 21, 15, 30, 1, 0x12, 0x34, 0, 0, 0, 0, 1, 0x12, 0x34, 0, 23, 30, 15, 0,0x12, 0x34, 0, 21, 15, 30, 1, 0x12, 0x34, 0, 0, 0, 0, 1, 0x12, 0x34, 0, 23, 30, 15, 0,0x12, 0x34, 0, 21, 15, 30, 1};

//	  writeOnOffSch2FlashV2(test_onoff_array_have_error);
//	  for (int i = 0; i < ONOFFSCHEDULEMAX; i++)
//	  {
//	  	emberAfCorePrintln("\n\taddress=%d", onOffSchRam[i].address);
//	  	emberAfCorePrintln("\n\treserve=%d-hour=%d-minute=%d-second=%d", onOffSchRam[i].time.reserve, onOffSchRam[i].time.hour, onOffSchRam[i].time.minute, onOffSchRam[i].time.second);
//	  	emberAfCorePrintln("\n\tvalue=%d\n", onOffSchRam[i].value);
//	  }
	  emberAfCorePrintln("emberAfManagerPutOnOffScheduleCallback");
//	emberAfCorePrintln("--------------------------buttonIsr------------time:%d-----------------reportDimming:%d",time,status);
	update_calendar();
uint16_t year;
uint8_t month;
uint8_t day;
uint8_t weekday;
uint8_t hour;
uint8_t min;
uint8_t sec;
uint16_t ms;
get_date_and_time(&year,&month,&day,&weekday,&hour,&min,&sec,&ms);
emberAfCorePrintln("findingAndBindingEventHandler:--%4d-%02d-%02d %02d:%02d:%02d.%03d",year,month,day,weekday,hour,min,sec);

emberAfCorePrintln("ONOFFSCHEDULEMAX");
for (int i = 0; i < ONOFFSCHEDULEMAX; i++)
{
	emberAfCorePrintln("\n\taddress=%d", onOffSchRam[i].address);
	emberAfCorePrintln("\n\treserve=%d-hour=%d-minute=%d-second=%d", onOffSchRam[i].time.reserve, onOffSchRam[i].time.hour, onOffSchRam[i].time.minute, onOffSchRam[i].time.second);
	emberAfCorePrintln("\n\tvalue=%d\n", onOffSchRam[i].value);
}
emberAfCorePrintln("DIMMING");
for (int i = 0; i < DIMMINGSCHMAX; i++)
{
	emberAfCorePrintln("\n\taddress=%d", dimmingSchRam[i].address);
	emberAfCorePrintln("\n\treserve=%d-hour=%d-minute=%d-second=%d", dimmingSchRam[i].time.reserve, dimmingSchRam[i].time.hour, dimmingSchRam[i].time.minute, dimmingSchRam[i].time.second);
	emberAfCorePrintln("\n\tvalue=%d\n", dimmingSchRam[i].value);
}
emberAfCorePrintln("group");
for (int i = 0; i < GROUPSCHMAX; i++)
{
	emberAfCorePrintln("\n\taddress=%d", groupSchRam[i].address);
}
}

/** @brief Stack Status
 *
 * This function is called by the application framework from the stack status
 * handler.  This callbacks provides applications an opportunity to be notified
 * of changes to the stack status and take appropriate action.  The return code
 * from this callback is ignored by the framework.  The framework will always
 * process the stack status after the callback returns.
 *
 * @param status   Ver.: always
 */
bool emberAfStackStatusCallback(EmberStatus status)
{
  // Note, the ZLL state is automatically updated by the stack and the plugin.
  if (status == EMBER_NETWORK_DOWN) {
    halClearLed(COMMISSIONING_STATUS_LED);
  } else if (status == EMBER_NETWORK_UP) {
    halSetLed(COMMISSIONING_STATUS_LED);
  //  emberEventControlSetActive(findingAndBindingEventControl);
  }

// This value is ignored by the framework.
  return false;
}
/** @brief Main Init
 *
 * This function is called from the application's main function. It gives the
 * application a chance to do any initialization required at system startup.
 * Any code that you would normally put into the top of the application's
 * main() routine should be put into this function.
        Note: No callback
 * in the Application Framework is associated with resource cleanup. If you
 * are implementing your application on a Unix host where resource cleanup is
 * a consideration, we expect that you will use the standard Posix system
 * calls, including the use of atexit() and handlers for signals such as
 * SIGTERM, SIGINT, SIGCHLD, SIGPIPE and so on. If you use the signal()
 * function to register your signal handler, please mind the returned value
 * which may be an Application Framework function. If the return value is
 * non-null, please make sure that you call the returned function from your
 * handler to avoid negating the resource cleanup of the Application Framework
 * itself.
 *
 */

/** @brief Complete
 *
 * This callback is fired when the Network Steering plugin is complete.
 *
 * @param status On success this will be set to EMBER_SUCCESS to indicate a
 * network was joined successfully. On failure this will be the status code of
 * the last join or scan attempt. Ver.: always
 * @param totalBeacons The total number of 802.15.4 beacons that were heard,
 * including beacons from different devices with the same PAN ID. Ver.: always
 * @param joinAttempts The number of join attempts that were made to get onto
 * an open Zigbee network. Ver.: always
 * @param finalState The finishing state of the network steering process. From
 * this, one is able to tell on which channel mask and with which key the
 * process was complete. Ver.: always
 */
void emberAfPluginNetworkSteeringCompleteCallback(EmberStatus status,
                                                  uint8_t totalBeacons,
                                                  uint8_t joinAttempts,
                                                  uint8_t finalState)
{
  emberAfCorePrintln("%p network %p: 0x%X", "Join", "complete", status);

}

/** @brief Complete
 *
 * This callback notifies the user that the network creation process has
 * completed successfully.
 *
 * @param network The network that the network creator plugin successfully
 * formed. Ver.: always
 * @param usedSecondaryChannels Whether or not the network creator wants to
 * form a network on the secondary channels Ver.: always
 */
void emberAfPluginNetworkCreatorCompleteCallback(const EmberNetworkParameters *network,
                                                 bool usedSecondaryChannels)
{
  emberAfCorePrintln("%p network %p: 0x%X",
                     "Form distributed",
                     "complete",
                     EMBER_SUCCESS);
}

/** @brief On/off Cluster Server Post Init
 *
 * Following resolution of the On/Off state at startup for this endpoint, perform any
 * additional initialization needed; e.g., synchronize hardware state.
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPluginOnOffClusterServerPostInitCallback(uint8_t endpoint)
{
  // At startup, trigger a read of the attribute and possibly a toggle of the
  // LED to make sure they are always in sync
  emberAfOnOffClusterServerAttributeChangedCallback(endpoint,
                                                    ZCL_ON_OFF_ATTRIBUTE_ID);
}

/** @brief Server Attribute Changed
 *
 * On/off cluster, Server Attribute Changed
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param attributeId Attribute that changed  Ver.: always
 */
void emberAfOnOffClusterServerAttributeChangedCallback(uint8_t endpoint,
                                                       EmberAfAttributeId attributeId)
{

  // When the on/off attribute changes, set the LED appropriately.  If an error
  // occurs, ignore it because there's really nothing we can do.
  if (attributeId == ZCL_ON_OFF_ATTRIBUTE_ID) {
		emberAfCorePrintln("emberAfOnOffClusterServerAttributeChangedCallback");
    bool onOff;
    if (emberAfReadServerAttribute(endpoint,
                                   ZCL_ON_OFF_CLUSTER_ID,
                                   ZCL_ON_OFF_ATTRIBUTE_ID,
                                   (uint8_t *)&onOff,
                                   sizeof(onOff))
        == EMBER_ZCL_STATUS_SUCCESS) {
      if (onOff) {
    	  emberAfCorePrintln("halSetLed");
    	  GPIO_PinOutSet(LED_PORT,LED_PIN);
        //halSetLed(ON_OFF_LIGHT_LED);
      } else {
    	  emberAfCorePrintln("halClearLed");
        halClearLed(ON_OFF_LIGHT_LED);
    	  //GPIO_PinOutClear(LED_PORT,LED_PIN);
    	  setLevel(0);
      }
    }
  }
}

void emberAfLevelControlClusterServerAttributeChangedCallback(int8u endpoint,
                                                              EmberAfAttributeId attributeId)
{
    bool onOff;
    emberAfCorePrintln("emberAfLevelControlClusterServerAttributeChangedCallback");
    emberAfReadServerAttribute(endpoint,
                                   ZCL_ON_OFF_CLUSTER_ID,
                                   ZCL_ON_OFF_ATTRIBUTE_ID,
                                   (uint8_t *)&onOff,
                                   sizeof(onOff));
    if(onOff==1)
    {
  	  if (attributeId == ZCL_CURRENT_LEVEL_ATTRIBUTE_ID) {
  			//emberAfCorePrintln("emberAfOnOffClusterServerAttributeChangedCallback");
  		  uint8_t level=0;

  	    if (emberAfReadServerAttribute(endpoint,
  	    							   ZCL_LEVEL_CONTROL_CLUSTER_ID,
  									   ZCL_CURRENT_LEVEL_ATTRIBUTE_ID,
  	                                   (uint8_t *)&level,
  	                                   sizeof(level))
  	        == EMBER_ZCL_STATUS_SUCCESS) {
  	    	emberAfCorePrintln("level--run:%d",level-1);
  			  setLevel(level-1);
  	    }

  	  }
    }

}
void emberAfOnOffClusterServerDefaultResponseCallback(int8u endpoint,
                                                      int8u commandId,
                                                      EmberAfStatus status)
{
	//emberAfCorePrintln("emberAfOnOffClusterServerDefaultResponseCallback");
}

void emberAfLevelControlClusterServerDefaultResponseCallback(int8u endpoint,
                                                             int8u commandId,
                                                             EmberAfStatus status)
{
//	  if (attributeId == ZCL_ON_OFF_ATTRIBUTE_ID) {
	//emberAfCorePrintln("emberAfLevelControlClusterServerDefaultResponseCallback");
//	  }
}

/** @brief Hal Button Isr
 *
 * This callback is called by the framework whenever a button is pressed on the
 * device. This callback is called within ISR context.
 *
 * @param button The button which has changed state, either BUTTON0 or BUTTON1
 * as defined in the appropriate BOARD_HEADER.  Ver.: always
 * @param state The new state of the button referenced by the button parameter,
 * either ::BUTTON_PRESSED if the button has been pressed or ::BUTTON_RELEASED
 * if the button has been released.  Ver.: always
 */
void emberAfHalButtonIsrCallback(uint8_t button, uint8_t state)
{

//	emberAfZllInitiateTouchLink();
  if (state == BUTTON_RELEASED) {
	  // check flash
    emberEventControlSetActive(findingAndBindingEventControl);

	  if (emberAfNetworkState() == EMBER_JOINED_NETWORK) {
	//    emberEventControlSetInactive(findingAndBindingEventControl);
	    EmberStatus x = emberLeaveNetwork();
	    emberAfCorePrintln("emberLeaveNetwork:%d",x);
	//    emberAfCorePrintln("Find and bind target start: 0x%X",
	//                       emberAfPluginFindAndBindTargetStart(LIGHT_ENDPOINT));
	  }
  }
}

// all  custom callback

bool emberAfManagerGetOnOffScheduleCallback(int8u* OnOffscheduleStr)
{
	emberAfCorePrintln("emberAfManagerGetOnOffScheduleCallback");
	for(int i=0;i<strlen((char*)OnOffscheduleStr);i++)
	{
		emberAfCorePrintln("value[%d]:%d",i,OnOffscheduleStr[i]);
	}
	return 1;
}

bool emberAfManagerPutOnOffScheduleCallback(int8u* OnOffscheduleStr)
{
	emberAfCorePrintln("emberAfManagerPutOnOffScheduleCallback");
	writeOnOffSch2FlashV2((char*)OnOffscheduleStr);
    for (int i = 0; i < ONOFFSCHEDULEMAX; i++)
    {
    	emberAfCorePrintln("\n\taddress=%d", onOffSchRam[i].address);
    	emberAfCorePrintln("\n\treserve=%d-hour=%d-minute=%d-second=%d", onOffSchRam[i].time.reserve, onOffSchRam[i].time.hour, onOffSchRam[i].time.minute, onOffSchRam[i].time.second);
    	emberAfCorePrintln("\n\tvalue=%d\n", onOffSchRam[i].value);
    }
    emberAfCorePrintln("emberAfManagerPutOnOffScheduleCallback");
	return 1;
}

boolean emberAfManagerPutDimmingScheduleCallback(int8u* dimmingScheduleStr)
{
	emberAfCorePrintln("emberAfManagerPutDimmingScheduleCallback");
	writeDimmingSch2FlashV2((char*)dimmingScheduleStr);
	return 1;
}
//can  xu ly group//
boolean emberAfManagerPutGroupCallback(int8u* groupStr)
{
	emberAfCorePrintln("emberAfManagerPutGroupCallback");
	// remove//
	for(int i=0;i<GROUPSCHMAX;i++)
	{
		uint8_t test2;
		if(groupSchRam[i].address==0)
		{
			continue;
		}
		emberAfCorePrintln("---remove-- address:%d",groupSchRam[i].address);
		// tu them dia chi
		emberAfFillCommandGroupsClusterRemoveGroup(groupSchRam[i].address);
		emAfCommandApsFrame->profileId=emberAfProfileIdFromIndex(0);
		emAfCommandApsFrame->sourceEndpoint	=emberAfEndpointFromIndex(0);
		emAfCommandApsFrame->destinationEndpoint =0x0001;
		test2 =emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,emberAfGetNodeId());
		emberAfCorePrintln("---sendAddGroupCommand--status: %d",test2);
	}
	writeGroupSch2FlashV2((char*)groupStr);
	addGroup();
	for(int i=0;i<GROUPSCHMAX;i++)
	{
		emberAfCorePrintln("emberAfManagerPutGroupCallback--groupId:%d",groupSchRam[i].address);
	}
	return 1;
}

boolean emberAfManagerPutReportRealTimeCallback(int8u* reportTime)
{
	emberAfCorePrintln("emberAfManagerPutReportRealTimeCallback");
	// dong bo time to check onoff schedule
	emberEventControlSetInactive(scheduleControl);
	emberEventControlSetDelayMS(scheduleControl, 10 * MY_DELAY_IN_MS);
	realtime_t time = realtime_cast((char*)reportTime);
	emberAfCorePrintln("month:%d, day:%d, hour:%d--min:%d--sec:%d",time.month,time.day,time.hour,time.minute,time.second);
	uint16_t year=0;
	uint8_t month=0;
	uint8_t day=0;
	uint8_t weekday=0;
	uint8_t hour=time.hour;
	uint8_t min= time.minute;
	uint8_t sec= time.second;
	uint16_t ms =0;
	set_date_and_time(year,month,day,weekday,hour,min,sec,ms);
	get_date_and_time(&year,&month,&day,&weekday,&hour,&min,&sec,&ms);
	emberAfCorePrintln("hour:%d--min:%d--sec:%d",time.hour,time.minute,time.second);
	return 1;
}
boolean emberAfManagerPutDimmingCallback(int16u dimming)
{
	emberAfCorePrintln("emberAfManagerPutDimmingCallback");
	dimmingValue = dimming;
	setLevel(dimming);
	return 1;
}


boolean emberAfManagerPutHistoricalEventCallback(int8u* HistoryStr)
{
	emberAfCorePrintln("emberAfManagerPutHistoricalEventCallback");
	return 1;
}


boolean emberAfManagerPutReportTimeCallback(int16u reportStr)
{
	return 1;
}

boolean emberAfManagerPutPingCallback(uint8_t* Ping)
{
	emberAfCorePrintln("emberAfManagerPutPingCallback--:%d",Ping);
	for(int i=0;i<pingLen;i++)
	{
		pingReport[i] = Ping[i];
	}
	return 1;
}

boolean emberAfManagerGetPingCallback(int8u* Ping)
{
	emberAfCorePrintln("emberAfManagerGetPingCallback--:%d",Ping);
	getPing(pingReport);
	return 1;
}
