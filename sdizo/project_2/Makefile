CC=g++
CFLAGS= -std=c++17 -Wall -Wextra -ggdb -g3
OUTDIR=.
SRCDIR= src
OBJDIR= obj

SHELL=CMD

INCLUDE_PATHS := -I"./include"

CPP_SOURCES := $(wildcard $(SRCDIR)/*.cpp)
CPP_SOURCES := $(filter-out $(SRCDIR)/list_template.cpp, $(CPP_SOURCES))
CPP_SOURCES := $(filter-out $(SRCDIR)/heap_template.cpp, $(CPP_SOURCES))
OBJECTS := $(CPP_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


TARGET = sdizo

${TARGET} : ${OBJECTS}
	${CC} ${CFLAGS}  ${OBJECTS} -o ${TARGET}

${OBJDIR}/%.o : ${SRCDIR}/%.cpp
	${CC} ${INCLUDE_PATHS} ${CFLAGS} -c $< -o $@


clean:
	del /F /S /Q .\${OBJDIR}\*
	del ${TARGET}.exe