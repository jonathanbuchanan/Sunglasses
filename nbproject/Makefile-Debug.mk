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
	${OBJECTDIR}/Libraries/SOIL/SOIL.o \
	${OBJECTDIR}/Libraries/SOIL/image_DXT.o \
	${OBJECTDIR}/Libraries/SOIL/image_helper.o \
	${OBJECTDIR}/Libraries/SOIL/stb_image_aug.o \
	${OBJECTDIR}/Libraries/glm/detail/glm.o \
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
LDLIBSOPTIONS=Libraries/libassimp.a Libraries/libpugixml.a Libraries/libglfw3.a Libraries/libGLEW.a Libraries/libfreetype.a Libraries/libalut.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libassimp.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libpugixml.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libglfw3.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libGLEW.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libfreetype.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: Libraries/libalut.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sunglasses ${OBJECTFILES} ${LDLIBSOPTIONS} -framework OpenGL -framework CoreFoundation -framework CoreVideo -framework Cocoa -lz -framework IOKit -framework OpenAL

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
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -I/usr/local/Cellar/glew/1.12.0/include -I/usr/local/Cellar/glfw3/3.1.1/include -ILibraries -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Libraries/glm/detail/glm.o Libraries/glm/detail/glm.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/System/Library/Frameworks -ILibraries/Freetype -ILibraries/Freetype/config -I/usr/local/Cellar/glew/1.12.0/include -I/usr/local/Cellar/glfw3/3.1.1/include -ILibraries -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
