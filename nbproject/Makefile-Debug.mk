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
	${OBJECTDIR}/Cluster.o \
	${OBJECTDIR}/CosineSim.o \
	${OBJECTDIR}/DataPoints.o \
	${OBJECTDIR}/DistanceMatrix.o \
	${OBJECTDIR}/Distances.o \
	${OBJECTDIR}/Euclidean.o \
	${OBJECTDIR}/Hamming.o \
	${OBJECTDIR}/Hashtable.o \
	${OBJECTDIR}/K_medoids.o \
	${OBJECTDIR}/LSH.o \
	${OBJECTDIR}/LinkedList.o \
	${OBJECTDIR}/NN_recommend.o \
	${OBJECTDIR}/NeighbourSearch.o \
	${OBJECTDIR}/PAM.o \
	${OBJECTDIR}/Silhouette.o \
	${OBJECTDIR}/alaLloyds.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/randomfunc.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj-phase3-part1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj-phase3-part1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj-phase3-part1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cluster.o: Cluster.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Cluster.o Cluster.cpp

${OBJECTDIR}/CosineSim.o: CosineSim.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/CosineSim.o CosineSim.cpp

${OBJECTDIR}/DataPoints.o: DataPoints.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataPoints.o DataPoints.cpp

${OBJECTDIR}/DistanceMatrix.o: DistanceMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DistanceMatrix.o DistanceMatrix.cpp

${OBJECTDIR}/Distances.o: Distances.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Distances.o Distances.cpp

${OBJECTDIR}/Euclidean.o: Euclidean.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Euclidean.o Euclidean.cpp

${OBJECTDIR}/Hamming.o: Hamming.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Hamming.o Hamming.cpp

${OBJECTDIR}/Hashtable.o: Hashtable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Hashtable.o Hashtable.cpp

${OBJECTDIR}/K_medoids.o: K_medoids.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/K_medoids.o K_medoids.cpp

${OBJECTDIR}/LSH.o: LSH.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/LSH.o LSH.cpp

${OBJECTDIR}/LinkedList.o: LinkedList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/LinkedList.o LinkedList.cpp

${OBJECTDIR}/NN_recommend.o: NN_recommend.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/NN_recommend.o NN_recommend.cpp

${OBJECTDIR}/NeighbourSearch.o: NeighbourSearch.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/NeighbourSearch.o NeighbourSearch.cpp

${OBJECTDIR}/PAM.o: PAM.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/PAM.o PAM.cpp

${OBJECTDIR}/Silhouette.o: Silhouette.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Silhouette.o Silhouette.cpp

${OBJECTDIR}/alaLloyds.o: alaLloyds.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/alaLloyds.o alaLloyds.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/randomfunc.o: randomfunc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/randomfunc.o randomfunc.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj-phase3-part1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
