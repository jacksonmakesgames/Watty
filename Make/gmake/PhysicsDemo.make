# GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_x86
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),debug_x86)
  RESCOMP = windres
  TARGETDIR = ../../bin/Demos
  TARGET = $(TARGETDIR)/PhysicsDemo.exe
  OBJDIR = obj/x86/Debug/PhysicsDemo
  DEFINES += -DDEBUG -DFT2_BUILD_LIBRARY -DCRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE
  INCLUDES += -I../../Demos/PhysicsDemo -I../../L_ETC-core/src -I../../Dependencies/GLFW/include -I../../Dependencies/gorilla-audio/include -I../../Dependencies/FreeImage/include -I../../L_ETC-core/ext/freetype/include -I../../Dependencies/imgui/include -I../../Dependencies/glad/include
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -g
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -g -std=c++11
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += ../../bin/LETC-core.lib -lopengl32 -lglfw3 -lFreeImage -lgorilla -lfreetype_debug
  LDDEPS += ../../bin/LETC-core.lib
  ALL_LDFLAGS += $(LDFLAGS) -L../../Dependencies/gorilla-audio/bin/win32 -L../../Dependencies/FreeImage/lib -L../../Dependencies/GLFW/lib-vc2019 -L../../bin -L../../Dependencies/Freetype/lib -L/usr/lib32 -m32
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_x86)
  RESCOMP = windres
  TARGETDIR = ../../bin/Demos
  TARGET = $(TARGETDIR)/PhysicsDemo.exe
  OBJDIR = obj/x86/Release/PhysicsDemo
  DEFINES += -DNDEBUG -DGLEW_STATIC -DFT2_BUILD_LIBRARY -DCRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE
  INCLUDES += -I../../Demos/PhysicsDemo -I../../L_ETC-core/src -I../../Dependencies/GLFW/include -I../../Dependencies/gorilla-audio/include -I../../Dependencies/FreeImage/include -I../../L_ETC-core/ext/freetype/include -I../../Dependencies/imgui/include -I../../Dependencies/glad/include
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m32 -O2
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m32 -O2 -std=c++11
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += ../../bin/LETC-core.lib -lopengl32 -lglfw3 -lFreeImage -lgorilla -lfreetype_release
  LDDEPS += ../../bin/LETC-core.lib
  ALL_LDFLAGS += $(LDFLAGS) -L../../Dependencies/gorilla-audio/bin/win32 -L../../Dependencies/FreeImage/lib -L../../Dependencies/GLFW/lib-vc2019 -L../../bin -L../../Dependencies/Freetype/lib -L/usr/lib32 -m32 -s
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

OBJECTS := \
	$(OBJDIR)/main.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

$(TARGET): $(GCH) ${CUSTOMFILES} $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking PhysicsDemo
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(CUSTOMFILES): | $(OBJDIR)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning PhysicsDemo
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) $(PCH) | $(OBJDIR)
$(GCH): $(PCH) | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
else
$(OBJECTS): | $(OBJDIR)
endif

$(OBJDIR)/main.o: ../../Demos/PhysicsDemo/src/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif