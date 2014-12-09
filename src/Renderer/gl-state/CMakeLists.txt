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

SET(Renderer_Glstate_SRCS
  GLState.cpp  
)

SET(Renderer_Glstate_HEADERS
  GLState.hpp    
)

SCIRUN_ADD_LIBRARY(Renderer_Glstate
  ${Renderer_Glstate_HEADERS}
  ${Renderer_Glstate_SRCS}
)

TARGET_LINK_LIBRARIES(Renderer_Glstate
  Renderer_Glplatform
)

IF(BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DBUILD_Renderer_Glstate)
ENDIF(BUILD_SHARED_LIBS)