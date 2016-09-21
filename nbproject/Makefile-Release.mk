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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/camera.o \
	${OBJECTDIR}/src/dummy/bcm_dummy.o \
	${OBJECTDIR}/src/hyperpan.o \
	${OBJECTDIR}/src/sphere.o \
	${OBJECTDIR}/src/stepper.o \
	${OBJECTDIR}/src/trigger.o \
	${OBJECTDIR}/src/verbose.o


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
LDLIBSOPTIONS=-lbcm2835

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperpan

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperpan: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperpan ${OBJECTFILES} ${LDLIBSOPTIONS} -lm

${OBJECTDIR}/src/camera.o: nbproject/Makefile-${CND_CONF}.mk src/camera.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/camera.o src/camera.c

${OBJECTDIR}/src/dummy/bcm_dummy.o: nbproject/Makefile-${CND_CONF}.mk src/dummy/bcm_dummy.c 
	${MKDIR} -p ${OBJECTDIR}/src/dummy
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dummy/bcm_dummy.o src/dummy/bcm_dummy.c

${OBJECTDIR}/src/hyperpan.o: nbproject/Makefile-${CND_CONF}.mk src/hyperpan.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/hyperpan.o src/hyperpan.c

${OBJECTDIR}/src/sphere.o: nbproject/Makefile-${CND_CONF}.mk src/sphere.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sphere.o src/sphere.c

${OBJECTDIR}/src/stepper.o: nbproject/Makefile-${CND_CONF}.mk src/stepper.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/stepper.o src/stepper.c

${OBJECTDIR}/src/trigger.o: nbproject/Makefile-${CND_CONF}.mk src/trigger.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/trigger.o src/trigger.c

${OBJECTDIR}/src/verbose.o: nbproject/Makefile-${CND_CONF}.mk src/verbose.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -D_GNU_SOURCE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/verbose.o src/verbose.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperpan

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
