#ͨ��makefile
#���
#����ִ���ļ��� make
#���붯̬��棺make dll

ROOTDIR := ../../
SRCDIRS :=$(ROOTDIR)/container $(ROOTDIR)/net $(ROOTDIR)/net/container $(ROOTDIR)/net/test $(ROOTDIR)/thread
SRCEXTS :=.cpp .c
OUTDIR :=.
OBJ_DIR :=$(OUTDIR)/obj/

OBJDIR :=$(OBJ_DIR)

CPPFLAGS :=-g -D__LINUX -std=c++11

INLIBS  :=
PROGRAMDIR := .
LIBDIRS := $(LIBDIRS)
PROGRAM :=$(PROGRAMDIR)/net_test

CPPFLAGS := $(CPPFLAGS)
LDFLAGS := -lpthread
CFLAGS :=
CXXFLAGS := 

CC  = gcc
CXX = g++
AR=ar

RM = rm -f

SHELL = /bin/sh
FULLSOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
SOURCES = $(notdir $(FULLSOURCES))
OBJS = $(foreach x,$(SRCEXTS), $(patsubst %$(x),%.o,$(filter %$(x),$(SOURCES))))
FULLOBJS = $(addprefix $(OBJDIR),$(OBJS))
DEPS    = $(patsubst %.o,%.d,$(OBJS))

vpath %.c $(SRCDIRS)
vpath %.cpp $(SRCDIRS)
vpath %.o $(OBJDIR)

.PHONY : all objs clean cleanall rebuild link cleanout

all : deldll dir $(PROGRAM)

dll : delexe dir $(PROGRAM)
# Rules for producing the objects.
#---------------------------------------------------
objs : $(OBJS)

%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $(OBJDIR)$(notdir $@)

%.o : %.cpp
	@echo -e "building: $(notdir $@) \t please wait ..."
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $(OBJDIR)$(notdir $@)


# Rules for producing the executable.
#----------------------------------------------
$(PROGRAM) : $(OBJS)
ifeq ($(findstring .a, $(PROGRAM)), .a)
	$(AR) -rc $(PROGRAM) $(FULLOBJS)
else
ifeq ($(strip $(SRCEXTS)), .c) # C file
	$(CC) -o $(PROGRAM) $(FULLOBJS) $(INLIBS) $(LIBDIRS) $(LDFLAGS)
else # C++ file
	$(CXX) -o $(PROGRAM) $(FULLOBJS) $(INLIBS) $(LIBDIRS) $(LDFLAGS)
endif
endif


#-include $(DEPS)


test:
	@echo -e "objs: $(OBJS)"
	@echo -e "all objs: $(FULLOBJS)"

dir:
	@echo -e "making dir..."
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(PROGRAMDIR)

version:
	@echo -e "making release version"

rebuild: clean all

link: cleanout all

cleanout:
	@$(RM) $(PROGRAM)

clean :
	@$(RM) $(FULLOBJS) 
	@$(RM) $(DEPS) 

cleanall: clean cleanout

deldll : 
	@$(RM) test_dll.cpp

delexe : 
	@$(RM) test.cpp
