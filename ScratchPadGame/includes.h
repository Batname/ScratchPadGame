#ifndef includes_h
#define includes_h

// std
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <set>
#include <cstdint>
#include <cassert>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// qt
#include <QtOpenGL/qgl.h>
#include <QtOpenGL/qglshaderprogram.h>
#include <QtWidgets/qapplication.h>
#include <QtCore/qfile.h>
#include <QtCore/qfile.h>
#include <QtCore/qtimer.h>
#include <QtCore/qthread.h>
#include <QtCore/qdebug.h>
#include <QtCore/qdatetime.h>
#include <QtGui/qevent.h>
#include <QtCore/qset.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// engine
#include <BatGameEngine/Vector2D.h>
#include <BatGameEngine/Clock.hpp>

#endif /* includes_h */
