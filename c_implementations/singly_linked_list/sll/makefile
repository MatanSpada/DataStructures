CC = gcc
LDFLAGS = -g
OUTPUT = my_sll

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS += -g
else 
	CFLAGS += -DNDEBUG -O3
endif

VLG = valgrind --leak-check=yes --track-origins=yes

SRCS_TST := $(wildcard *_test.c)
SRCS_LIB := $(filter-out $(SRCS_TST), $(wildcard *.c))
SRCS := $(SRCS_TST) $(SRCS_LIB) 
OBJS_DBG := $(addprefix ../obj/debug/, $(SRCS_LIB:.c=.o))
OBJS_RLS := $(addprefix ../obj/release/, $(SRCS_LIB:.c=.o))
OBJS_TST := $(addprefix ../obj/debug/, $(SRCS_TST:.c=.o))
OBJS := $(OBJS_DBG) $(OBJS_RLS) $(OBJS_TST)
OBJDIR := ../obj
LIBDIR := ../libs

TARGET := $(OUTPUT)

.DEFAULT_GOAL = $(TARGET)

$(OBJS_DBG) $(OBJS_TST) : CFLAGS := -ansi -pedantic-errors -Wall -Wextra -fPIC -g 
$(OBJS_DBG) $(OBJS_TST) : CPPFLAGS := -DDEBUG
$(OBJS_DBG) $(OBJS_TST) : $(OBJDIR)/debug/%.o: %.c | $(OBJDIR)
	$(COMPILE.c) $< -o $@

$(OBJS_RLS) : CFLAGS := -ansi -pedantic-errors -Wall -Wextra -fPIC -O3
$(OBJS_RLS) : CPPFLAGS := -DNDEBUG
$(OBJS_RLS) : $(OBJDIR)/release/%.o: %.c | $(OBJDIR)
	$(COMPILE.c) $< -o $@

$(TARGET): $(OBJS_TST) ../libs/debug/libsll.so	
	$(LINK.o) $< -o $@ -L ../libs/debug -Wl,-rpath=../libs/debug -lsll

$(LIBDIR)/release $(OBJDIR)/release :
	mkdir $@

$(LIBDIR)/debug $(OBJDIR)/debug :
	mkdir $@

.PHONY : all release debug test
all: $(TARGET) release debug

test: LDFLAGS := -g -Wl,-rpath='$(ORIGIN)/$(LIBDIR)/debug' -L $(LIBDIR)/debug/
test: $(TARGET)
	./$(TARGET)

.PHONY : debug 
debug: DEBUG := 1
debug: $(LIBDIR)/debug/libsll.so 
$(LIBDIR)/debug/libsll.so: LDFLAGS := -g -shared -L $(LIBDIR)/debug/ -Wl,-rpath='$$ORIGIN'
$(LIBDIR)/debug/libsll.so: $(OBJS_DBG) | $(LIBDIR)/debug $(OBJDIR)/debug
	$(LINK.o) $^ -o $@

.PHONY : release 
release: DEBUG := 0
release: $(LIBDIR)/release/libsll.so 
$(LIBDIR)/release/libsll.so: LDFLAGS := -shared -L $(LIBDIR)/release/ -Wl,-rpath='$$ORIGIN'
$(LIBDIR)/release/libsll.so: $(OBJS_RLS) | $(LIBDIR)/release $(OBJDIR)/release
	$(LINK.o) $^ -o $@
	
vlg: $(TARGET)
	$(VLG) ./$(TARGET) > vlg.log 2>&1

push: 
	git add ~/git/
	git commit -m $(m)
	git push -u origin master
	
clean:
	rm -rf *.o $(TARGET) vlg.log $(OBJS) $(LIBDIR)/*/libsll.so 

.PHONY: clean all


# CC is the compiler
# CFLAGS is the flags for compiling with gd
# LDFLAGS is the flags for linkage 
# SRCS make shortcut for the makefile to know to .c files in the working directory (as strings)
# OBJS make shortcut for the makefile to know to .o files in the working directory (as strings)

# $@ is a shortcut for a.out (the blue text of the current segment)