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

if (WIN32)
  # Include GLEW cpm module.
  CPM_AddModule("glew"
    GIT_REPOSITORY "https://github.com/CIBC-Internal/cpm-glew"
    GIT_TAG "origin/master"
    EXPORT_MODULE TRUE)
endif()

# Enable debug macros only if we are debugging the program.
if (CMAKE_BUILD_TYPE MATCHES DEBUG) 
  CPM_ExportAdditionalDefinition("-DIAUNS_GLDEBUG_DEBUG")
endif (CMAKE_BUILD_TYPE MATCHES DEBUG) 

if ((DEFINED GL_PLATFORM_NO_DEBUGGING) AND (GL_PLATFORM_NO_DEBUGGING))
  CPM_ExportAdditionalDefinition("-DGL_PLATFORM_NO_DEBUGGING")
endif()

SET(Renderer_Glplatform_SRCS
  GLPlatform.cpp  
)

SET(Renderer_Glplatform_HEADERS
  GLPlatform.hpp    
)

SCIRUN_ADD_LIBRARY(Renderer_Glplatform
  ${Renderer_Glplatform_HEADERS}
  ${Renderer_Glplatform_SRCS}
)

TARGET_LINK_LIBRARIES(Renderer_Glplatform
  ${CPM_LIBRARIES}
)

IF(BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DBUILD_Renderer_Glplatform)
ENDIF(BUILD_SHARED_LIBS)