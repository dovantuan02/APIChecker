#ifndef _AK_ISP_TOOL_SERVER_H_
#define _AK_ISP_TOOL_SERVER_H_

/**
 * ak_its_get_version - get ISP tool server version
 * return: version string
 * notes:
 */
const char* ak_its_get_version(void);

/**
 * ak_its_start - start anyka ISP tool server
 * @port[IN]:port
 * notes: If you wan't use ISP tool to debug, do not start this server.
 */
void ak_its_start(unsigned int port);

/**
 * ak_its_stop - stop anyka ISP tool server
 * notes:
 */
void ak_its_stop(void);


#endif
/* end of file*/
