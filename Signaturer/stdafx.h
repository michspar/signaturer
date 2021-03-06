// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <boost/crc.hpp>
#include <fstream>
#include <boost/thread/thread.hpp>
#include <boost/functional.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/exception/all.hpp>
#include <cassert>

using std::string;
typedef std::vector<char> bytevect;