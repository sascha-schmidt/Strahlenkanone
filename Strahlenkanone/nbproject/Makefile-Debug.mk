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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/pixel.o \
	${OBJECTDIR}/src/glutwindow.o \
	${OBJECTDIR}/src/loader.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/sphere.o \
	${OBJECTDIR}/src/rgb.o \
	${OBJECTDIR}/src/triangle.o \
	${OBJECTDIR}/src/ppmwriter.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../lib -lboost_thread-mt -lglut

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/strahlenkanone

dist/strahlenkanone: ${OBJECTFILES}
	${MKDIR} -p dist
	${LINK.cc} -o ${CND_DISTDIR}/strahlenkanone ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/pixel.o: nbproject/Makefile-${CND_CONF}.mk src/pixel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/pixel.o src/pixel.cpp

${OBJECTDIR}/src/glutwindow.o: nbproject/Makefile-${CND_CONF}.mk src/glutwindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/glutwindow.o src/glutwindow.cpp

${OBJECTDIR}/src/loader.o: nbproject/Makefile-${CND_CONF}.mk src/loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/loader.o src/loader.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/sphere.o: nbproject/Makefile-${CND_CONF}.mk src/sphere.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sphere.o src/sphere.cpp

${OBJECTDIR}/src/rgb.o: nbproject/Makefile-${CND_CONF}.mk src/rgb.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/rgb.o src/rgb.cpp

${OBJECTDIR}/src/triangle.o: nbproject/Makefile-${CND_CONF}.mk src/triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/triangle.o src/triangle.cpp

${OBJECTDIR}/src/ppmwriter.o: nbproject/Makefile-${CND_CONF}.mk src/ppmwriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -I/usr/include/boost -I../../../include -I../libmath -Isrc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ppmwriter.o src/ppmwriter.cpp

# Subprojects
.build-subprojects:
	cd ../libmath && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/strahlenkanone

# Subprojects
.clean-subprojects:
	cd ../libmath && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
