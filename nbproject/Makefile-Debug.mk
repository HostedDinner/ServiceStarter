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
	${OBJECTDIR}/ServiceConnection.o \
	${OBJECTDIR}/ServiceGUI.o \
	${OBJECTDIR}/WinService.o \
	${OBJECTDIR}/Window.o \
	${OBJECTDIR}/WindowHelper.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=resource.o -lgdi32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter.exe: resource.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/servicestarter ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ServiceConnection.o: ServiceConnection.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServiceConnection.o ServiceConnection.cpp

${OBJECTDIR}/ServiceGUI.o: ServiceGUI.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServiceGUI.o ServiceGUI.cpp

${OBJECTDIR}/WinService.o: WinService.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WinService.o WinService.cpp

${OBJECTDIR}/Window.o: Window.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Window.o Window.cpp

${OBJECTDIR}/WindowHelper.o: WindowHelper.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WindowHelper.o WindowHelper.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0600 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

resource.o: resource.rc
	@echo Performing Custom Build Step
	windres.exe resource.rc resource.o

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} resource.o

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
