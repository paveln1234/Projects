
#ifndef __LOGLEVEL_H__
#define __LOGLEVEL_H__

typedef enum
{
    LOG_TRACE = 0, /* Trace message usually very detailed*/
    LOG_DEBUG, /* A message useful for debugging */
    LOG_INFO, /* Informative message*/
    LOG_WARNING, /*Warning */
    LOG_ERROR, /*An error occurred */
    LOG_CRITICAL, /* Critical error */
    LOG_SEVERE, /*Server error requiring immediate intervention */
    LOG_FATAL, /* Fatal error signaling an emergency*/
    LOG_NONE /*Used only in configuration file */
}LogLevel;


#endif /* __LOGLEVEL_H__ */
