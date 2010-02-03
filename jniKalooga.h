#ifndef JNIKALOOGA_H
#define JNIKALOOGA_H
#include <jni.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "src/imageHandling.h"
 
#define PATH_SEPARATOR ';' /* define it to be ':' on Solaris */
//#define USER_CLASSPATH ".:src/compiled/:runtime/commons-io-1.4.jar:runtime/commons-logging-1.0.4.jar:runtime/events-client-1.1.jar:runtime/hadoop-0.20.0-core_src.jar:runtime/jgap.jar:runtime/kalooga-commons-2.1-dev.jar:runtime/kalooga-crawl-1.0-jasper.jar:runtime/kalooga-crawl_searchcommon-1.0-dev.jar:runtime/kalooga-web.jar:runtime/log4j-1.2.13.jar:runtime/lucene-core-2.9.0.jar:runtime/nutch-1.0.jar:runtime/spring.jar:runtime/xerces-2_9_1.jar:runtime/xml-apis.jar:runtime/xmlenc-0.52.jar:src/:src/compiled/" /* where Prog.class is */

int saveFile();

#endif
