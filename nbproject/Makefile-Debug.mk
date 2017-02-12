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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ServiceConnection.o \
	${OBJECTDIR}/src/ServiceGUI.o \
	${OBJECTDIR}/src/WinService.o \
	${OBJECTDIR}/src/Window.o \
	${OBJECTDIR}/src/WindowHelper.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resource.o -lgdi32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter.exe: ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resource.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/ServiceConnection.o: src/ServiceConnection.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ServiceConnection.o src/ServiceConnection.cpp

${OBJECTDIR}/src/ServiceGUI.o: src/ServiceGUI.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ServiceGUI.o src/ServiceGUI.cpp

${OBJECTDIR}/src/WinService.o: src/WinService.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/WinService.o src/WinService.cpp

${OBJECTDIR}/src/Window.o: src/Window.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Window.o src/Window.cpp

${OBJECTDIR}/src/WindowHelper.o: src/WindowHelper.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/WindowHelper.o src/WindowHelper.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resource.o: src/resource.rc
	${MKDIR} -p ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}
	@echo Performing Custom Build Step
	windres.exe src/resource.rc ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resource.o

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resource.o

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
