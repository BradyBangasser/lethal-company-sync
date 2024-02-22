#ifndef LCS_FILES_HPP
#define LCS_FILES_HPP

#include <limits.h>
#include <stdio.h>

#define PROGRAM_FILES "C:\\lcs"
#define INSTALLS_FOLDER "installs"
#define GAME_FILE ".game.lcs"

#ifdef __cplusplus
// CPP specific definitions 

extern "C" {
#endif
// C or ASM definitions

/**
 * @brief Checks to see if a mod, game, or modpack is installed
 * 
 * @param id the id of the resource
 * @param path bath buffer, assumes buffer is PATH_MAX long
 * @return 0 on success
 */
int checkInstall(const char *id, char *path);

/**
 * @brief Verifies that the program required folder and files are in the correct place
 * @todo Added file verification 
 * 
 * @return 0 on ok
 */
int checkAndInstallSystemFiles();
int mkInfo(const char *path);

/**
 * @brief Creates a new game folder at the specified path
 * 
 * @todo Add game updating and file verifcation
 * 
 * @param path The path
 * @param gameFileContents The .game.lcs file contents
 * @return 0 on ok, -1 on error 
 */
int installGameByPath(const char *path, const char *gameFileContents);

/**
 * @brief Wrapper for @ref installGameByPath, generates path using id
 * 
 * @param gid the game id
 * @param gameFileContents The .game.lcs contents
 * @return 0 on ok, -1 on error 
 */
static inline int installGame(const char *gid, const char *gameFileContents) {
    char path[PATH_MAX] = {0};
    snprintf(path, PATH_MAX, "%s\\%s\\%s", PROGRAM_FILES, INSTALLS_FOLDER, gid);
    return installGameByPath(path, gameFileContents);
}


#ifdef __cplusplus
}
#endif

#endif