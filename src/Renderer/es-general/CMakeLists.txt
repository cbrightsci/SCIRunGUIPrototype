#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2014 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

# ++ MODULE: GLM
CPM_AddModule("glm"
  GIT_REPOSITORY "https://github.com/CIBC-Internal/cpm-glm"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE)

# ++ MODULE: Cereal support for serializing GLM.
CPM_AddModule("cereal_glm"
  GIT_REPOSITORY "https://github.com/CIBC-Internal/cpm-cereal-glm"
  GIT_TAG "origin/master"
  USE_EXISTING_VER TRUE)

# I don't want more than one version of this module running around.
CPM_ForceOnlyOneModuleVersion()

SET(Renderer_ESgeneral_SRCS
  Registration.cpp
  systems/ClickBox2DSys.cpp
  systems/ConstantRotation.cpp
  util/Math.cpp
)

SET(Renderer_ESgeneral_HEADERS
  AABB2D.hpp
  Registration.hpp
  comp/CameraSelect.hpp
  comp/ClickBox2D.hpp
  comp/ConstsnRotation.hpp
  comp/StaticCamera.hpp
  comp/StaticGlobalTime.hpp
  comp/StaticKeyboardInput.hpp
  comp/StaticMouseInput.hpp
  comp/StaticObjRefID.hpp
  comp/StaticOrthoCamera.hpp
  comp/StaticRandom.hpp
  comp/StaticScreenDims.hpp
  comp/Transform.hpp
  systems/ClickBox2DSys.hpp
  systems/ConstantRotation.hpp
  util/Math.hpp
)

SCIRUN_ADD_LIBRARY(Renderer_ESgeneral 
  ${Renderer_ESgeneral_HEADERS}
  ${Renderer_ESgeneral_SRCS}
)

TARGET_LINK_LIBRARIES(Renderer_ESgeneral
  Renderer_Entitysystem
  Renderer_ESacorn
  Renderer_ESsystems
  ${CPM_LIBRARIES}
)

IF(BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DBUILD_Renderer_ESgeneral)
ENDIF(BUILD_SHARED_LIBS)