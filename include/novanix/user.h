#ifndef __NOVANIX_KERNEL_USER_H
#define __NOVANIX_KERNEL_USER_H


#define BASE_USER_PASS_BUFFER 32


#define USER_NAME_BUFFER BASE_USER_PASS_BUFFER
#define PASSWORD_BUFFER_SIZE BASE_USER_PASS_BUFFER

#define DEFAULT_PASSWORD "admin"

char user_name[USER_NAME_BUFFER] = "admin";
char *user_password = "admin";



#define PASSWORD  *user_password


#define USER_NOVANIX 8

#endif