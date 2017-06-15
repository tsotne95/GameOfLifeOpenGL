TARGET  := GOL
FILES   := main coordinates cell play list


CC               := g++
LD               := g++
OBJSUFFIX	 := .o
LIBPREFIX	 := lib
STATIC_LIBSUFFIX := .a
CFLAGS 		 := -g
CFLAGS_PLATFORM  :=
LDFLAGS		 :=
FRAMEWORKS	 :=
LIBS		 :=
EXESUFFIX        :=
DEPARGS          := -MD
# how we link to libraries depends on the platform
ARCH=$(shell uname | sed -e 's/-.*//g')

ifeq ($(ARCH), CYGWIN_NT)
# If building on Cygwin, use glut32, opengl32
EXESUFFIX := .exe
LIBS      += glut32 opengl32
else

ifeq ($(ARCH), Darwin)
FRAMEWORKS += OpenGL GLUT
else
# Building on Linux
LIBS += GL glut
endif

endif # Not CYGWIN_END


TARGET := $(addsuffix $(EXESUFFIX), $(TARGET))
INCDIRS := .
LIBDIRS :=

CFLAGS += $(addprefix -I, $(INCDIRS)) $(CFLAGS_PLATFORM)
LDFLAGS += $(addprefix -L, $(LIBDIRS))

LDLIBS  := $(addprefix -l, $(LIBS))
LDFRAMEWORKS := $(addprefix -framework , $(FRAMEWORKS))


OBJS := $(addsuffix $(OBJSUFFIX), $(FILES))
DEPS := $(addsuffix .d, $(FILES))

.SUFFIXES: .cpp $(OBJSUFFIX)

.PHONY: clean release all

all: $(TARGET)

# Handle dependencies
-include $(patsubst %.o,%.d,$(OBJS))

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LDLIBS) $(LDFRAMEWORKS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $< $(DEPARGS)

clean:
	rm -rf $(OBJS) $(TARGET) $(DEPS)

release:
	@make --no-print-directory RELEASE=1
