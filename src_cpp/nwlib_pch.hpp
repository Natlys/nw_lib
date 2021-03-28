#ifndef NWLIB_PCH_HPP
#define NWLIB_PCH_HPP
/// pre-compiled header file
/// this file contains the most usable standard include files
/// nwlib_pch.cpp file gets it and generates .pch file in the intermediate files
/// .pch header isn't essentially compiles every time we want to run the app
/// .pch header includes in every cpp file of project

// --<standard>--
// --stl
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <algorithm>
// --data_proc
#include <iostream>
#include <sstream>
#include <fstream>
// --numbers
#include <random>
// --strings
#include <string>
#include <string_view>
#include <xstring>
// --support
#include <yvals_core.h>
#include <locale>
#include <exception>
#include <system_error>
#include <typeinfo>
#include <type_traits>
#include <typeindex>
// --memory
#include <new>
#include <memory>
// --parallel computation
#include <thread>
#include <future>
#include <mutex>
// --console
#include <conio.h>
// --</standard>--

// --<native>--
#include <cwchar>
#include <cstddef>
#include <cstdarg>
#include <cstdio>
#include <ctime>
// --</native>--

// --<external>-
#include <../ext/std/file_sys.h>
#include <../ext/glm/trigonometric.hpp>
#include <../ext/glm/vec2.hpp>
#include <../ext/glm/vec3.hpp>
#include <../ext/glm/vec4.hpp>

#include <../ext/glm/mat2x2.hpp>
#include <../ext/glm/mat3x3.hpp>
#include <../ext/glm/mat4x4.hpp>
#include <../ext/glm/matrix.hpp>
#include <../ext/glm/ext/matrix_transform.hpp>
#include <../ext/glm/gtx/transform.hpp>
// --</external>--

#include "std/nwlib_std_os.h"

#endif	// NWLIB_PCH_HPP