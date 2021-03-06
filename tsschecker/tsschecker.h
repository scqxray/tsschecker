//
//  ipswme.h
//  tsschecker
//
//  Created by tihmstar on 07.01.16.
//  Copyright © 2016 tihmstar. All rights reserved.
//

#ifndef tsscheker_h
#define tsscheker_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "jsmn.h"
#include <plist/plist.h>
#include "tss.h"
#include "all_tsschecker.h"
    
extern int dbglog;
extern int print_tss_response;
extern int nocache;
extern int save_shshblobs;
extern const char *shshSavePath;


typedef struct{
    char *deviceModel; //either model, or boardconfig
    char *deviceBoard;
    uint64_t ecid;
    uint64_t bbgcid;
    char *apnonce;
    size_t parsedApnonceLen;
    char *sepnonce;
    size_t parsedSepnonceLen;
    char generator[19];
    int isUpgradeInstall : 1;
}t_devicevals;

typedef enum{
    kBasebandModeWithBaseband = 0,
    kBasebandModeWithoutBaseband = 1,
    kBasebandModeOnlyBaseband = 2,
}t_basebandMode;

typedef struct{
    const char *version;
    t_basebandMode basebandMode;
    int isOta       : 1;
    int useBeta     : 1;
    int isBuildid   : 1;
}t_iosVersion;
    
char *getFirmwareJson();
char *getOtaJson();
int parseTokens(const char *json, jsmntok_t **tokens);
char **getListOfiOSForDevice(char *firmwarejson, jsmntok_t *tokens, const char *device, int isOTA, int *versionCntt);
int printListOfDevices(char *firmwarejson, jsmntok_t *tokens);
int printListOfiOSForDevice(char *firmwarejson, jsmntok_t *tokens, char *device, int isOTA);
    
char *getFirmwareUrl(t_devicevals *devVals, t_iosVersion *versVals, const char *firmwarejson, jsmntok_t *tokens);
char *getBuildManifest(char *url, const char *device, const char *version, int isOta);
int64_t getBBGCIDForDevice(const char *deviceModel);

int tssrequest(plist_t *tssrequest, char *buildManifest, t_devicevals *devVals, t_basebandMode basebandMode);
int isManifestSignedForDevice(const char *buildManifestPath, t_devicevals *devVals, t_iosVersion *versVals);
int isManifestBufSignedForDevice(char *buildManifestBuffer, t_devicevals *devVals, t_basebandMode basebandMode);
int isVersionSignedForDevice(char *firmwareJson, jsmntok_t *firmwareTokens, t_iosVersion *versVals, t_devicevals *devVals);


jsmntok_t *getFirmwaresForDevice(const char *device, const char *firmwareJson, jsmntok_t *tokens, int isOta);

    
int checkFirmwareForDeviceExists(t_devicevals *devVals, t_iosVersion *versVals, char *firmwareJson, jsmntok_t *tokens);

int downloadPartialzip(const char *url, const char *file, const char *dst);

const char *getBoardconfigFromModel(const char *model);
const char *getModelFromBoardconfig(const char *boardconfig);
plist_t getBuildidentity(plist_t buildManifest, const char *model, int isUpdateInstall);
plist_t getBuildidentityWithBoardconfig(plist_t buildManifest, const char *boardconfig, int isUpdateInstall);


    
#ifdef __cplusplus
}
#endif
    
#endif /* tsscheker_h */
