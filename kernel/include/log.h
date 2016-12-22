#ifndef _KERNEL_LOG_H
#define _KERNEL_LOG_H

typedef enum message_t Message;
enum message_t { INFO_MSG, WARNING_MSG, ERROR_MSG };

void kernel_log(Message type, const char *format, ...);

#endif
