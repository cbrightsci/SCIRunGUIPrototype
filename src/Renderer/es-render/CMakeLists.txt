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

# ++ MODULE: Lodepng png loading library.
CPM_AddModule("lodepng"
  GIT_REPOSITORY "https://github.com/CIBC-Internal/cpm-lodepng.git"
  GIT_TAG "origin/master")

# I don't want more than one version of this module running around.
CPM_ForceOnlyOneModuleVersion()

SET(Renderer_ESrender_SRCS
  BMFont.cpp
  FontMan.cpp
  GeomMan.cpp
  IBOMan.cpp
  Registration.cpp
  Registration1.cpp
  Registration2.cpp
  Registration3.cpp
  ShaderMan.cpp
  TextureMan.cpp
  VBOMan.cpp
  comp/CommonUniforms.cpp
  comp/MatUniform.cpp
  comp/RenderFont.cpp
  comp/RenderSimpleGeom.cpp
  comp/Texture.cpp
  comp/VecUniform.cpp
  systems/ArcBallCameraSys.cpp
  systems/RenderFontSys.cpp
  systems/RenderSimpleGeomSys.cpp
  systems/UtilViewPosAlignSys.cpp
  systems/debug/RenderClickBox2DSys.cpp
  util/Camera.cpp
  util/DebugRender.cpp
  util/Lines.cpp
  util/Shader.cpp
  util/TexQuad.cpp
)

SET(Renderer_ESrender_HEADERS
  BMFont.hpp
  FontMan.hpp
  GeomMan.hpp
  IBOMan.hpp
  Registration.hpp
  ShaderMan.hpp
  TextureMan.hpp
  VBOMan.hpp
  comp/AssetPromise.hpp
  comp/CommonUniforms.cpp
  comp/Font.hpp
  comp/FontPromise.hpp
  comp/Geom.hpp
  comp/GeomPromise.hpp
  comp/GLState.hpp
  comp/IBO.hpp
  comp/MatUniform.hpp
  comp/RenderFont.hpp
  comp/RenderSequence.hpp
  comp/RenderSimpleGeom.hpp
  comp/Shader.hpp
  comp/ShaderPromiseVF.hpp
  comp/SkinnedGeom.hpp
  comp/StaticArcBallCam.hpp
  comp/StaticFontMan.hpp
  comp/StaticGeomMan.hpp
  comp/StaticGLState.hpp
  comp/StaticIBOMan.hpp
  comp/StaticShaderMan.hpp
  comp/StaticTextureMan.hpp
  comp/StaticVBOMan.hpp
  comp/Texture.hpp
  comp/TexturePromise.hpp
  comp/UniformLocation.hpp
  comp/UtilViewPosAlign.hpp
  comp/VBO.hpp
  comp/VecUniform.hpp
  systems/ArcBallCameraSys.hpp
  systems/RenderFontSys.hpp
  systems/RenderSimpleGeomSys.hpp
  systems/UtilViewPosAlignSys.hpp
  systems/debug/RenderClickBox2DSys.hpp
  util/Camera.hpp
  util/DebugRender.hpp
  util/Lines.hpp
  util/Shader.hpp
  util/TexQuad.hpp
  util/Uniform.hpp
  util/helper/TypeToGLUniform.hpp
)

SCIRUN_ADD_LIBRARY(Renderer_ESrender
  ${Renderer_ESrender_HEADERS}
  ${Renderer_ESrender_SRCS}
)

TARGET_LINK_LIBRARIES(Renderer_ESrender
  Renderer_Entitysystem
  Renderer_ESacorn
  Renderer_ESsystems
  Renderer_ESfs
  Renderer_ESgeneral
  Renderer_Glshaders
  Renderer_Glstate
  Renderer_Bserialize
  Renderer_Arclookat
  Renderer_Varbuffer
  ${CPM_LIBRARIES}
)

IF(BUILD_SHARED_LIBS)
  ADD_DEFINITIONS(-DBUILD_Renderer_ESrender)
ENDIF(BUILD_SHARED_LIBS)
