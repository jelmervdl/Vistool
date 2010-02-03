#include "jniKalooga.h"

int saveFile() {
  JNIEnv *env;
  JavaVM *jvm;
  jint res;
  jclass cls;
  jmethodID mid;
  jstring jstr;
  jclass stringClass;
  jobjectArray args;
  jmethodID constructorID;
#ifdef JNI_VERSION_1_2
  JavaVMInitArgs vm_args;
  JavaVMOption options[1];

  options[0].optionString =(char *) "-Djava.class.path=" USER_CLASSPATH;
  vm_args.version = 0x00010002;
  vm_args.options = options;
  vm_args.nOptions = 1;
  vm_args.ignoreUnrecognized = JNI_TRUE;
  /* Create the Java VM */
  res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
#else
     JDK1_1InitArgs vm_args;
     char classpath[1024];
     vm_args.version = 0x00010001;
     JNI_GetDefaultJavaVMInitArgs(&vm_args);
     /* Append USER_CLASSPATH to the default system class path */
     sprintf(classpath, "%s%c%s",
             vm_args.classpath, PATH_SEPARATOR, USER_CLASSPATH);
     vm_args.classpath = classpath;
     /* Create the Java VM */
     res = JNI_CreateJavaVM(&jvm, &env, &vm_args);
#endif /* JNI_VERSION_1_2 */
 
     if (res < 0) {
       fprintf(stderr, "Can't create Java VM\n");
       return 1;
     }
     cls = (jclass) env->NewGlobalRef(env->FindClass( "imageHandling"));
     if (cls == NULL) {
       goto destroy;
     }
 
     mid = env->GetStaticMethodID( cls, "main",
				   "([Ljava/lang/String;)V");
     constructorID = env->GetMethodID(cls, "<init>", "()V");
     //hond = env->GetMethodID(cls, "hond", "()Ljava/lang/String;");
     //myclass_object =  env->NewObject(cls, constructorID);
 
     if (mid == NULL) {
       goto destroy;
     }
     jstr = env->NewStringUTF(" from C!");
     if (jstr == NULL) {
       goto destroy;
     }
     stringClass = env->FindClass( "java/lang/String");
     args = env->NewObjectArray( 1, stringClass, jstr);
     if (args == NULL) {
       goto destroy;
     }
     env->CallStaticVoidMethod(cls, mid, args);
     using namespace std;
 destroy:
     if (env->ExceptionOccurred()) {
       env->ExceptionDescribe();
     }
     jvm->DestroyJavaVM();
     return 0;
}
