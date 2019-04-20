CC=g++
CFLAGS= -std=c++17 -Wall -Wextra
OUTDIR=.
SRCDIR= src
OBJDIR= obj
INCLUDE_PATHS := -I"./include"

CPP_SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(CPP_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TARGET = sdizo

${TARGET} : ${OBJECTS}
	${CC} ${CFLAGS}  ${OBJECTS} -o ${TARGET}

${OBJDIR}/%.o : ${SRCDIR}/%.cpp
	${CC} ${INCLUDE_PATHS} ${CFLAGS} -c $? -o $@

clean:
	del /F /S /Q ${OBJDIR}\*
	del ${TARGET}.exe