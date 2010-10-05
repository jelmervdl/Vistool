#import "fd.h"
#if __MAC_OSX
#import <Cocoa/Cocoa.h>

char * askFile(){
  [NSApplication sharedApplication];
  size_t i; // Loop counter.
  NSAutoreleasePool *autoreleasepool = [[NSAutoreleasePool alloc] init];
  // do thread work
  //NSApplicationLoad();
  // Create the File Open Dialog class.
  NSOpenPanel* openDlg = [NSOpenPanel openPanel];

  // Enable the selection of files in the dialog.
  [openDlg setCanChooseFiles:YES];

  // Enable the selection of directories in the dialog.
  [openDlg setCanChooseDirectories:YES];

  // Display the dialog.  If the OK button was pressed,
  // process the files.

  if ( [openDlg runModalForDirectory:nil file:nil] == NSOKButton )
    {
      // Get an array containing the full filenames of all
      // files and directories selected.
      NSArray* files = [openDlg filenames];

      // Loop through all the files and process them.
      for( i = 0; i < [files count]; i++ )
        {
          NSString* fileName = [files objectAtIndex:i];
          char * aapje = (char *)  [fileName UTF8String];
	  return aapje;
        }
    }
  [autoreleasepool release];
  return (char *) "";
}
#else

char* askFile(){
  return (char *) "";
}

#endif
