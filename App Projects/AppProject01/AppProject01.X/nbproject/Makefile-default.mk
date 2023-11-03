#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ourSource/ChangeClk.c ourSource/IOs.c ourSource/TimeDelay.c ourSource/UART2.c ourSource/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ourSource/ChangeClk.o ${OBJECTDIR}/ourSource/IOs.o ${OBJECTDIR}/ourSource/TimeDelay.o ${OBJECTDIR}/ourSource/UART2.o ${OBJECTDIR}/ourSource/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/ourSource/ChangeClk.o.d ${OBJECTDIR}/ourSource/IOs.o.d ${OBJECTDIR}/ourSource/TimeDelay.o.d ${OBJECTDIR}/ourSource/UART2.o.d ${OBJECTDIR}/ourSource/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ourSource/ChangeClk.o ${OBJECTDIR}/ourSource/IOs.o ${OBJECTDIR}/ourSource/TimeDelay.o ${OBJECTDIR}/ourSource/UART2.o ${OBJECTDIR}/ourSource/main.o

# Source Files
SOURCEFILES=ourSource/ChangeClk.c ourSource/IOs.c ourSource/TimeDelay.c ourSource/UART2.c ourSource/main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24F16KA101
MP_LINKER_FILE_OPTION=,--script=p24F16KA101.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ourSource/ChangeClk.o: ourSource/ChangeClk.c  .generated_files/flags/default/911ba9e31cc4ed39a16a2d619faf26fac0f34132 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/ChangeClk.o.d 
	@${RM} ${OBJECTDIR}/ourSource/ChangeClk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/ChangeClk.c  -o ${OBJECTDIR}/ourSource/ChangeClk.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/ChangeClk.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/IOs.o: ourSource/IOs.c  .generated_files/flags/default/3ce72a3827f11077bd62d5b3d2e02f3b41f866bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/IOs.o.d 
	@${RM} ${OBJECTDIR}/ourSource/IOs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/IOs.c  -o ${OBJECTDIR}/ourSource/IOs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/IOs.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/TimeDelay.o: ourSource/TimeDelay.c  .generated_files/flags/default/f3123d92d124923d8ad9fce989310cd78fe72dd3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/ourSource/TimeDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/TimeDelay.c  -o ${OBJECTDIR}/ourSource/TimeDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/TimeDelay.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/UART2.o: ourSource/UART2.c  .generated_files/flags/default/1248dab8fc2df9bedb481f7a8c6907806f7a6bf2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/UART2.o.d 
	@${RM} ${OBJECTDIR}/ourSource/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/UART2.c  -o ${OBJECTDIR}/ourSource/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/UART2.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/main.o: ourSource/main.c  .generated_files/flags/default/1a24395ce0ae0939167d580f0016f8a13f10bca7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/main.o.d 
	@${RM} ${OBJECTDIR}/ourSource/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/main.c  -o ${OBJECTDIR}/ourSource/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/ourSource/ChangeClk.o: ourSource/ChangeClk.c  .generated_files/flags/default/577813ad64a7273f8b491d45161047a6a7989f7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/ChangeClk.o.d 
	@${RM} ${OBJECTDIR}/ourSource/ChangeClk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/ChangeClk.c  -o ${OBJECTDIR}/ourSource/ChangeClk.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/ChangeClk.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/IOs.o: ourSource/IOs.c  .generated_files/flags/default/75278f9e751fc1bf376f852a8b414693cd12ac02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/IOs.o.d 
	@${RM} ${OBJECTDIR}/ourSource/IOs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/IOs.c  -o ${OBJECTDIR}/ourSource/IOs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/IOs.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/TimeDelay.o: ourSource/TimeDelay.c  .generated_files/flags/default/fdc52806caad14e3415ec3bbfab2356081d6a313 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/ourSource/TimeDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/TimeDelay.c  -o ${OBJECTDIR}/ourSource/TimeDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/TimeDelay.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/UART2.o: ourSource/UART2.c  .generated_files/flags/default/43c9262a75699744e8124905681f608d58d3e8a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/UART2.o.d 
	@${RM} ${OBJECTDIR}/ourSource/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/UART2.c  -o ${OBJECTDIR}/ourSource/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/UART2.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ourSource/main.o: ourSource/main.c  .generated_files/flags/default/955871c985623a74f2783f1312c242ab57de58c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/ourSource" 
	@${RM} ${OBJECTDIR}/ourSource/main.o.d 
	@${RM} ${OBJECTDIR}/ourSource/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ourSource/main.c  -o ${OBJECTDIR}/ourSource/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ourSource/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/AppProject01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
