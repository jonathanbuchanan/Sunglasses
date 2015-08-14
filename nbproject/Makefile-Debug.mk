#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Audio/SunMusicObject.o \
	${OBJECTDIR}/Audio/SunSoundBufferStorage.o \
	${OBJECTDIR}/Audio/SunSoundListener.o \
	${OBJECTDIR}/Audio/SunSoundObject.o \
	${OBJECTDIR}/Graphics/GUI/SunGUIItem.o \
	${OBJECTDIR}/Graphics/GUI/SunGUIItemMesh.o \
	${OBJECTDIR}/Graphics/GUI/SunGUIMenu.o \
	${OBJECTDIR}/Graphics/GUI/SunGUISystem.o \
	${OBJECTDIR}/Graphics/Shaders/SunShader.o \
	${OBJECTDIR}/Graphics/Shaders/SunShaderUniformObject.o \
	${OBJECTDIR}/Graphics/SunCamera.o \
	${OBJECTDIR}/Graphics/SunMesh.o \
	${OBJECTDIR}/Graphics/SunModel.o \
	${OBJECTDIR}/Graphics/SunPrimitives.o \
	${OBJECTDIR}/Libraries/SOIL/SOIL.o \
	${OBJECTDIR}/Libraries/SOIL/image_DXT.o \
	${OBJECTDIR}/Libraries/SOIL/image_helper.o \
	${OBJECTDIR}/Libraries/SOIL/stb_image_aug.o \
	${OBJECTDIR}/Libraries/glm/detail/glm.o \
	${OBJECTDIR}/SunButtonState.o \
	${OBJECTDIR}/SunDirectionalLightObject.o \
	${OBJECTDIR}/SunGame.o \
	${OBJECTDIR}/SunNode.o \
	${OBJECTDIR}/SunObject.o \
	${OBJECTDIR}/SunPointLightObject.o \
	${OBJECTDIR}/SunScene.o \
	${OBJECTDIR}/Utility.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=Libraries/libassimp.a Libraries/libpugixml.a Libraries/libglfw3.a Libraries/libGLEW.a Libraries/libfreetype.a Libraries/libogg.a Libraries/libFLAC.a Libraries/libvorbis.a Libraries/libsfml-audio-s.a Libraries/libsfml-system-s.a Libraries/libvorbisfile.a Libraries/libvorbisenc.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libassimp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libpugixml.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libglfw3.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libGLEW.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libfreetype.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libogg.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libFLAC.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libvorbis.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libsfml-audio-s.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libsfml-system-s.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libvorbisfile.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libvorbisenc.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses ${OBJECTFILES} ${LDLIBSOPTIONS} -framework OpenGL -framework CoreFoundation -framework CoreVideo -framework Cocoa -lz -framework IOKit -framework OpenAL

${OBJECTDIR}/Audio/SunMusicObject.o: Audio/SunMusicObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Audio
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Audio/SunMusicObject.o Audio/SunMusicObject.cpp

${OBJECTDIR}/Audio/SunSoundBufferStorage.o: Audio/SunSoundBufferStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/Audio
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Audio/SunSoundBufferStorage.o Audio/SunSoundBufferStorage.cpp

${OBJECTDIR}/Audio/SunSoundListener.o: Audio/SunSoundListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/Audio
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Audio/SunSoundListener.o Audio/SunSoundListener.cpp

${OBJECTDIR}/Audio/SunSoundObject.o: Audio/SunSoundObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Audio
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Audio/SunSoundObject.o Audio/SunSoundObject.cpp

${OBJECTDIR}/Graphics/GUI/SunGUIItem.o: Graphics/GUI/SunGUIItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics/GUI
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/GUI/SunGUIItem.o Graphics/GUI/SunGUIItem.cpp

${OBJECTDIR}/Graphics/GUI/SunGUIItemMesh.o: Graphics/GUI/SunGUIItemMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics/GUI
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/GUI/SunGUIItemMesh.o Graphics/GUI/SunGUIItemMesh.cpp

${OBJECTDIR}/Graphics/GUI/SunGUIMenu.o: Graphics/GUI/SunGUIMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics/GUI
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/GUI/SunGUIMenu.o Graphics/GUI/SunGUIMenu.cpp

${OBJECTDIR}/Graphics/GUI/SunGUISystem.o: Graphics/GUI/SunGUISystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics/GUI
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/GUI/SunGUISystem.o Graphics/GUI/SunGUISystem.cpp

${OBJECTDIR}/Graphics/Shaders/SunShader.o: Graphics/Shaders/SunShader.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics/Shaders
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Shaders/SunShader.o Graphics/Shaders/SunShader.cpp

${OBJECTDIR}/Graphics/Shaders/SunShaderUniformObject.o: Graphics/Shaders/SunShaderUniformObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics/Shaders
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Shaders/SunShaderUniformObject.o Graphics/Shaders/SunShaderUniformObject.cpp

${OBJECTDIR}/Graphics/SunCamera.o: Graphics/SunCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/SunCamera.o Graphics/SunCamera.cpp

${OBJECTDIR}/Graphics/SunMesh.o: Graphics/SunMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/SunMesh.o Graphics/SunMesh.cpp

${OBJECTDIR}/Graphics/SunModel.o: Graphics/SunModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/SunModel.o Graphics/SunModel.cpp

${OBJECTDIR}/Graphics/SunPrimitives.o: Graphics/SunPrimitives.cpp 
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/SunPrimitives.o Graphics/SunPrimitives.cpp

${OBJECTDIR}/Libraries/SOIL/SOIL.o: Libraries/SOIL/SOIL.c 
	${MKDIR} -p ${OBJECTDIR}/Libraries/SOIL
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/local/lib -I/usr/lib -I/opt/local/lib -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/SOIL/SOIL.o Libraries/SOIL/SOIL.c

${OBJECTDIR}/Libraries/SOIL/image_DXT.o: Libraries/SOIL/image_DXT.c 
	${MKDIR} -p ${OBJECTDIR}/Libraries/SOIL
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/local/lib -I/usr/lib -I/opt/local/lib -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/SOIL/image_DXT.o Libraries/SOIL/image_DXT.c

${OBJECTDIR}/Libraries/SOIL/image_helper.o: Libraries/SOIL/image_helper.c 
	${MKDIR} -p ${OBJECTDIR}/Libraries/SOIL
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/local/lib -I/usr/lib -I/opt/local/lib -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/SOIL/image_helper.o Libraries/SOIL/image_helper.c

${OBJECTDIR}/Libraries/SOIL/stb_image_aug.o: Libraries/SOIL/stb_image_aug.c 
	${MKDIR} -p ${OBJECTDIR}/Libraries/SOIL
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/local/lib -I/usr/lib -I/opt/local/lib -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/SOIL/stb_image_aug.o Libraries/SOIL/stb_image_aug.c

${OBJECTDIR}/Libraries/glm/detail/glm.o: Libraries/glm/detail/glm.cpp 
	${MKDIR} -p ${OBJECTDIR}/Libraries/glm/detail
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/glm/detail/glm.o Libraries/glm/detail/glm.cpp

${OBJECTDIR}/SunButtonState.o: SunButtonState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunButtonState.o SunButtonState.cpp

${OBJECTDIR}/SunDirectionalLightObject.o: SunDirectionalLightObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunDirectionalLightObject.o SunDirectionalLightObject.cpp

${OBJECTDIR}/SunGame.o: SunGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunGame.o SunGame.cpp

${OBJECTDIR}/SunNode.o: SunNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunNode.o SunNode.cpp

${OBJECTDIR}/SunObject.o: SunObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunObject.o SunObject.cpp

${OBJECTDIR}/SunPointLightObject.o: SunPointLightObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunPointLightObject.o SunPointLightObject.cpp

${OBJECTDIR}/SunScene.o: SunScene.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SunScene.o SunScene.cpp

${OBJECTDIR}/Utility.o: Utility.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Utility.o Utility.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -ILibraries -ILibraries/GLFW -ILibraries/GL -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
