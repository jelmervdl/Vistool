#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <Carbon/Carbon.h>
#include <stdio.h>

const char * requestFile(void);
void callback( NavEventCallbackMessage theSelector, NavCBRecPtr callBackParams, void *callBackUserData );


#endif
