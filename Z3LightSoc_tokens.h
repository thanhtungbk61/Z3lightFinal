// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// This file contains the tokens for attributes stored in flash


// Identifier tags for tokens
// Creator for attribute: on/off, endpoint: 1
#define CREATOR_ON_OFF_1 0xB000
#define NVM3KEY_ON_OFF_1 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB000 )
// Creator for attribute: start up on off, endpoint: 1
#define CREATOR_START_UP_ON_OFF_1 0xB001
#define NVM3KEY_START_UP_ON_OFF_1 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB001 )
// Creator for attribute: current level, endpoint: 1
#define CREATOR_CURRENT_LEVEL_1 0xB002
#define NVM3KEY_CURRENT_LEVEL_1 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB002 )
// Creator for attribute: start up current level, endpoint: 1
#define CREATOR_START_UP_CURRENT_LEVEL_1 0xB003
#define NVM3KEY_START_UP_CURRENT_LEVEL_1 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB003 )
// Creator for attribute: Dimming Attribute: 0x0001 0x10A2, endpoint: 1
#define CREATOR_Dimming_1 0xB004
#define NVM3KEY_Dimming_1 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB004 )
// Creator for attribute: cluster revision, endpoint: 1
#define CREATOR_MANAGER_CLUSTER_REVISION_SERVER_1 0xB005
#define NVM3KEY_MANAGER_CLUSTER_REVISION_SERVER_1 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB005 )
// Creator for attribute: on/off, endpoint: 2
#define CREATOR_ON_OFF_2 0xB006
#define NVM3KEY_ON_OFF_2 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB006 )
// Creator for attribute: start up on off, endpoint: 2
#define CREATOR_START_UP_ON_OFF_2 0xB007
#define NVM3KEY_START_UP_ON_OFF_2 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB007 )
// Creator for attribute: current level, endpoint: 2
#define CREATOR_CURRENT_LEVEL_2 0xB008
#define NVM3KEY_CURRENT_LEVEL_2 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB008 )
// Creator for attribute: start up current level, endpoint: 2
#define CREATOR_START_UP_CURRENT_LEVEL_2 0xB009
#define NVM3KEY_START_UP_CURRENT_LEVEL_2 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB009 )
// Creator for attribute: color temperature, endpoint: 2
#define CREATOR_COLOR_CONTROL_COLOR_TEMPERATURE_2 0xB00A
#define NVM3KEY_COLOR_CONTROL_COLOR_TEMPERATURE_2 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB00A )
// Creator for attribute: start up color temperature mireds, endpoint: 2
#define CREATOR_START_UP_COLOR_TEMPERATURE_MIREDS_2 0xB00B
#define NVM3KEY_START_UP_COLOR_TEMPERATURE_MIREDS_2 ( NVM3KEY_DOMAIN_ZIGBEE | 0xB00B )


// Types for the tokens
#ifdef DEFINETYPES
typedef uint8_t  tokType_on_off;
typedef uint8_t  tokType_start_up_on_off;
typedef uint8_t  tokType_current_level;
typedef uint8_t  tokType_start_up_current_level;
typedef uint16_t  tokType_color_control_color_temperature;
typedef uint16_t  tokType_start_up_color_temperature_mireds;
typedef uint16_t  tokType_dimming;
typedef uint16_t  tokType_manager_cluster_revision_server;
#endif // DEFINETYPES


// Actual token definitions
#ifdef DEFINETOKENS
DEFINE_BASIC_TOKEN(ON_OFF_1, tokType_on_off, 0x00)
DEFINE_BASIC_TOKEN(START_UP_ON_OFF_1, tokType_start_up_on_off, 0xFF)
DEFINE_BASIC_TOKEN(CURRENT_LEVEL_1, tokType_current_level, 0x00)
DEFINE_BASIC_TOKEN(START_UP_CURRENT_LEVEL_1, tokType_start_up_current_level, 0x33)
DEFINE_BASIC_TOKEN(Dimming_1, tokType_dimming, 0x0000UL)
DEFINE_BASIC_TOKEN(MANAGER_CLUSTER_REVISION_SERVER_1, tokType_manager_cluster_revision_server, 0x0001)
DEFINE_BASIC_TOKEN(ON_OFF_2, tokType_on_off, 0x00)
DEFINE_BASIC_TOKEN(START_UP_ON_OFF_2, tokType_start_up_on_off, 0xFF)
DEFINE_BASIC_TOKEN(CURRENT_LEVEL_2, tokType_current_level, 0x00)
DEFINE_BASIC_TOKEN(START_UP_CURRENT_LEVEL_2, tokType_start_up_current_level, 0x33)
DEFINE_BASIC_TOKEN(COLOR_CONTROL_COLOR_TEMPERATURE_2, tokType_color_control_color_temperature, 0x00FA)
DEFINE_BASIC_TOKEN(START_UP_COLOR_TEMPERATURE_MIREDS_2, tokType_start_up_color_temperature_mireds, 0x4444)
#endif // DEFINETOKENS


// Macro snippet that loads all the attributes from tokens
#define GENERATED_TOKEN_LOADER(endpoint) do {\
  uint8_t ptr[2]; \
  uint8_t curNetwork = emberGetCurrentNetwork(); \
  uint8_t epNetwork; \
  epNetwork = emberAfNetworkIndexFromEndpoint(1); \
  if((endpoint) == 1 || ((endpoint) == EMBER_BROADCAST_ENDPOINT && epNetwork == curNetwork)) { \
    halCommonGetToken((tokType_on_off *)ptr, TOKEN_ON_OFF_1); \
    emberAfWriteServerAttribute(1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_BOOLEAN_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_start_up_on_off *)ptr, TOKEN_START_UP_ON_OFF_1); \
    emberAfWriteServerAttribute(1, ZCL_ON_OFF_CLUSTER_ID, ZCL_START_UP_ON_OFF_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_ENUM8_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_current_level *)ptr, TOKEN_CURRENT_LEVEL_1); \
    emberAfWriteServerAttribute(1, ZCL_LEVEL_CONTROL_CLUSTER_ID, ZCL_CURRENT_LEVEL_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT8U_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_start_up_current_level *)ptr, TOKEN_START_UP_CURRENT_LEVEL_1); \
    emberAfWriteServerAttribute(1, ZCL_LEVEL_CONTROL_CLUSTER_ID, ZCL_START_UP_CURRENT_LEVEL_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT8U_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_dimming *)ptr, TOKEN_Dimming_1); \
    emberAfWriteManufacturerSpecificServerAttribute(1, ZCL_MANAGER_ID, ZCL_Dimming_ATTRIBUTE_ID, 0x10A2, (uint8_t*)ptr, ZCL_INT16U_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_manager_cluster_revision_server *)ptr, TOKEN_MANAGER_CLUSTER_REVISION_SERVER_1); \
    emberAfWriteManufacturerSpecificServerAttribute(1, ZCL_MANAGER_ID, ZCL_MANAGER_CLUSTER_REVISION_SERVER_ATTRIBUTE_ID, 0x10A2, (uint8_t*)ptr, ZCL_INT16U_ATTRIBUTE_TYPE); \
  } \
  epNetwork = emberAfNetworkIndexFromEndpoint(2); \
  if((endpoint) == 2 || ((endpoint) == EMBER_BROADCAST_ENDPOINT && epNetwork == curNetwork)) { \
    halCommonGetToken((tokType_on_off *)ptr, TOKEN_ON_OFF_2); \
    emberAfWriteServerAttribute(2, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_BOOLEAN_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_start_up_on_off *)ptr, TOKEN_START_UP_ON_OFF_2); \
    emberAfWriteServerAttribute(2, ZCL_ON_OFF_CLUSTER_ID, ZCL_START_UP_ON_OFF_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_ENUM8_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_current_level *)ptr, TOKEN_CURRENT_LEVEL_2); \
    emberAfWriteServerAttribute(2, ZCL_LEVEL_CONTROL_CLUSTER_ID, ZCL_CURRENT_LEVEL_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT8U_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_start_up_current_level *)ptr, TOKEN_START_UP_CURRENT_LEVEL_2); \
    emberAfWriteServerAttribute(2, ZCL_LEVEL_CONTROL_CLUSTER_ID, ZCL_START_UP_CURRENT_LEVEL_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT8U_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_color_control_color_temperature *)ptr, TOKEN_COLOR_CONTROL_COLOR_TEMPERATURE_2); \
    emberAfWriteServerAttribute(2, ZCL_COLOR_CONTROL_CLUSTER_ID, ZCL_COLOR_CONTROL_COLOR_TEMPERATURE_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT16U_ATTRIBUTE_TYPE); \
    halCommonGetToken((tokType_start_up_color_temperature_mireds *)ptr, TOKEN_START_UP_COLOR_TEMPERATURE_MIREDS_2); \
    emberAfWriteServerAttribute(2, ZCL_COLOR_CONTROL_CLUSTER_ID, ZCL_START_UP_COLOR_TEMPERATURE_MIREDS_ATTRIBUTE_ID, (uint8_t*)ptr, ZCL_INT16U_ATTRIBUTE_TYPE); \
  } \
} while(false)


// Macro snippet that saves the attribute to token
#define GENERATED_TOKEN_SAVER do {\
  uint8_t allZeroData[2]; \
  MEMSET(allZeroData, 0, 2); \
  if ( data == NULL ) data = allZeroData; \
  if ( endpoint == 1 ) { \
    if ( clusterId == 0x06 ) { \
      if ( metadata->attributeId == 0x0000 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_ON_OFF_1, data); \
      if ( metadata->attributeId == 0x4003 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_START_UP_ON_OFF_1, data); \
    } else if ( clusterId == 0x08 ) { \
      if ( metadata->attributeId == 0x0000 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_CURRENT_LEVEL_1, data); \
      if ( metadata->attributeId == 0x4000 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_START_UP_CURRENT_LEVEL_1, data); \
    } else if ( clusterId == 0xFC10 ) { \
      if ( metadata->attributeId == 0x0017 && 0x10A2 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_Dimming_1, data); \
      if ( metadata->attributeId == 0xFFFD && 0x10A2 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_MANAGER_CLUSTER_REVISION_SERVER_1, data); \
    } \
  } else if ( endpoint == 2) { \
    if ( clusterId == 0x06 ) { \
      if ( metadata->attributeId == 0x0000 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_ON_OFF_2, data); \
      if ( metadata->attributeId == 0x4003 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_START_UP_ON_OFF_2, data); \
    } else if ( clusterId == 0x08 ) { \
      if ( metadata->attributeId == 0x0000 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_CURRENT_LEVEL_2, data); \
      if ( metadata->attributeId == 0x4000 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_START_UP_CURRENT_LEVEL_2, data); \
    } else if ( clusterId == 0x0300 ) { \
      if ( metadata->attributeId == 0x0007 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_COLOR_CONTROL_COLOR_TEMPERATURE_2, data); \
      if ( metadata->attributeId == 0x4010 && 0x0000 == emberAfGetMfgCode(metadata) &&!emberAfAttributeIsClient(metadata) ) \
        halCommonSetToken(TOKEN_START_UP_COLOR_TEMPERATURE_MIREDS_2, data); \
    } \
  } \
} while(false)

