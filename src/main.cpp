#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#include "getSongFolder.hpp"
#include "loadFilesIntoCompany.h"

#define BASE_LETHAL_PATH "%s\\AppData\\Roaming\\Thunderstore Mod Manager\\DataFolder\\LethalCompany\\profiles\\%s"

// Trust me windows

int main() {
    int lcsResult;
    int i;
    char id[64];
    char zipFile[64 + PATH_MAX];
    char profileName[64];
    char profilePath[PATH_MAX];

    printf("Lethal Company Sync (C) Brady Bangasser 2023\nSponsored by Nexus Logic Consulting LLC\n\n");

    printf("Enter Google Drive file: ");
    fgets(id, sizeof(id), stdin);

    i = 0;
    // For some reason memcpy wasn't working on the fgets string
    while (id[i] != '\0') {
        if (id[i] != '\n') zipFile[i] = id[i];
        else {
            id[i] = '\0';
            break;
        }
        i++;
    }

    zipFile[i - 1] = '\0';
    strcat(zipFile, ".zip");

    printf("Attempted to get drive file: %s\n", id);
    

    time_t rtime;
    struct tm *timeInfo;
    time(&rtime);
    timeInfo = localtime(&rtime);
    sprintf(profileName, "NL-LCS-ML#%d%d%d%d%d", timeInfo->tm_mon, timeInfo->tm_mday, 1900 + timeInfo->tm_year, timeInfo->tm_hour, timeInfo->tm_min);

    sprintf(profilePath, BASE_LETHAL_PATH, getenv("USERPROFILE"), profileName);

    lcsResult = getSongFolder(id, zipFile);

    if (lcsResult != 0) {
        printf("An Error Occured\n");
        getchar();
        return -1;
    }

    lcsResult = loadFilesIntoCompany(zipFile, profilePath);

    if (lcsResult != 0) {
        printf("An Error Occured\n");
        getchar();
        return -1;
    }

    if (remove(zipFile) != 0) {
        printf("Failed to remove %s, you can take care of that\n", zipFile);
    }

    printf("Installed spyware\n");
    printf("Uploaded search history to google\n");

    printf("Success\n");
    printf("Press any key...\n");
    getchar();
    return 0;
}