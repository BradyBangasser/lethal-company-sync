#ifndef FILES_HPP
#define FILES_HPP

#define PROGRAM_FILES "C:\\lcs"

#ifdef __cplusplus
// CPP specific definitions 

extern "C" {
#endif
// C or ASM definitions

/**
 * @brief Checks to see if a mod, game, or modpack is installed
 * 
 * @param id the id of the resource
 * @return install path or null
 */
const char *checkInstall(const char *id);

/**
 * @brief Verifies that the program required folder and files are in the correct place
 * @todo Added file verification 
 * 
 * @return 0 on ok
 */
int checkSystemFiles();
int mkInfo(const char *path);

#ifdef __cplusplus
}
#endif

#endif