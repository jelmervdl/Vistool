#include "test.h"

using namespace std;

namespace testing{
  void testAll(){
    testOCVConvert();
    cout << "all tests complete" << endl;
  }

  void testOCVConvert(){
    vector<float> a, b ,c ,d;
    a.push_back(1.1);
    a.push_back(2.2);
    a.push_back(3.3);
    a.push_back(4.4);
    b.push_back(11.11);
    b.push_back(12.12);
    b.push_back(13.13);
    b.push_back(14.14);
    c.push_back(21.20);
    c.push_back(22.22);
    c.push_back(23.23);
    c.push_back(24.24);
    d.push_back(31.30);
    d.push_back(32.32);
    d.push_back(33.33);
    d.push_back(34.34);
    vector< vector<float> > z;
    z.push_back(a);
    z.push_back(b);
    z.push_back(c);
    z.push_back(d);
    Mat_<float> ocv = OCV_Convert::dataset2Mat(&z);
    assert(ocv(0,0) == 1.1f);
    assert(ocv(3,0) == 4.4f);
    assert(ocv(0,1) == 11.11f);
    assert(ocv(1,1) == 12.12f);
    cout << "OCV Test Complete" << endl;
  }
}
