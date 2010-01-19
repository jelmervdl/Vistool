#include "fileDialog.h"

NavDialogRef dialog;
NavReplyRecord replyRecord;
CFURLRef fileAsCFURLRef = NULL;
FSRef fileAsFSRef;
OSStatus status;
const char * filestr;

const char * requestFile(){
  filestr = (char *) "";
  status = noErr;
  NavDialogCreationOptions opts;
  ProcessSerialNumber psn = {0, kCurrentProcess};

  status = TransformProcessType( &psn, kProcessTransformToForegroundApplication );
  status = SetFrontProcess( &psn );
  status = NavGetDefaultDialogCreationOptions( &opts );
  if( status == noErr ) {
    NavReplyRecord replyRecord;
    opts.modality = kWindowModalityAppModal;
    status = NavCreateGetFileDialog( &opts, NULL, callback, NULL, NULL, NULL, &dialog );
    if( status == noErr ) {
      status = NavDialogRun( dialog );
    }
    if( status == noErr ) {
      status = NavDialogGetReply( dialog, &replyRecord );
    }
    if( status == noErr ) {
      NavDialogDispose( dialog );
    }
  }
  return filestr;
}


void callback( NavEventCallbackMessage theSelector, NavCBRecPtr callBackParams, void *callBackUserData ) {

  switch( theSelector ) {
  case kNavCBUserAction: {
    
    //NavReplyRecord reply;
    NavUserAction userAction = NavDialogGetUserAction( callBackParams->context );
    
    switch( userAction ) {
    case kNavUserActionOpen: {
      status = NavDialogGetReply(dialog, &replyRecord);
      status = AEGetNthPtr(&(replyRecord.selection), 1, typeFSRef, NULL, NULL, &fileAsFSRef, sizeof(FSRef), NULL);
      fileAsCFURLRef = CFURLCreateFromFSRef(NULL, &fileAsFSRef);
      
      CFStringRef nwref = CFURLCopyFileSystemPath(fileAsCFURLRef, 0);
      filestr = CFStringGetCStringPtr(nwref, kCFStringEncodingMacRoman);
      return;
      break;
    }
    case kNavUserActionCancel: {
      break;
    }
    }
    break;
  }
  case kNavCBTerminate: {
    //NavDialogDispose( dialog ); 
    break;
  }
  }
}
