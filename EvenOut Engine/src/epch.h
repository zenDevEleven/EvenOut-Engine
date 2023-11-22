#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>

#include <format>
#include <vector>
#include <string>
#include <sstream>
#include <concepts>
#include <type_traits>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include <SDL3/SDL.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_events.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>


#include "box2d/box2d.h"
#include "box2d/b2_math.h"

#ifdef ENGINE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
