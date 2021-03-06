#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2012 Scientific Computing and Imaging Institute,
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

SET(Modules_Factory_SRCS
  HardCodedModuleFactory.cc
  ModuleFactoryImpl1.cc
  ModuleFactoryImpl2.cc
)

SET(Modules_Factory_HEADERS
  HardCodedModuleFactory.h
  ModuleDescriptionLookup.h
  share.h
)

SCIRUN_ADD_LIBRARY(Modules_Factory 
  ${Modules_Factory_HEADERS}
  ${Modules_Factory_SRCS}
)

TARGET_LINK_LIBRARIES(Modules_Factory
  Dataflow_Network
  Modules_Math
  Modules_Fields
  Modules_FiniteElements
  Modules_BrainStimulator
  Modules_Legacy_FiniteElements
  Modules_Legacy_Forward
  Modules_Basic
  Modules_DataIO
  Modules_String
  Modules_Render
  Modules_Visualization
  Modules_Legacy_Math
  Modules_Legacy_Bundle
  Modules_Legacy_Fields
  Modules_Legacy_Matlab_DataIO
)

IF(BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DBUILD_Modules_Factory)
ENDIF(BUILD_SHARED_LIBS)

SCIRUN_ADD_TEST_DIR(Tests)

