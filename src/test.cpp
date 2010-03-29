#include "test.h"

using namespace std;

namespace testing{
  void testAll(){
    testOCVConvert();
    testFileWriter();
    cout << "all tests complete" << endl;
  }

  void testOCVConvert(){

  }

  void testFileWriter(){

    vector<float> descriptor(200);
    for(int i = 0; i < 200; ++i){
      float value = i * -10.00200010000200025;
      descriptor[i] = value;
    }
    writeDescriptor(&descriptor, "test.desc");
    vector<float> read_descriptor;
    readDescriptor(&read_descriptor, "test.desc");
    for(int i = 0; i < (int) read_descriptor.size(); ++i){
      cout << read_descriptor[i] << " ";
      assert(read_descriptor[i] == descriptor[i]);
      }
    cout << endl;
  }
}
