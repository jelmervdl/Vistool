#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "boost/filesystem.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "dataPoint.h"
#include "category.h"

namespace vito{

bool is_image (std::string  str);

}
#endif
