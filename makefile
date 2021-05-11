# GNU Make project makefile autogenerated by Premake

ifndef config
  config=work_win64
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),work_win64)
  ifeq ($(origin CC), default)
    CC = F:\dev\gcc\bin\gcc.exe
  endif
  ifeq ($(origin CXX), default)
    CXX = F:\dev\gcc\bin\g++.exe
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  RESCOMP = default
  TARGETDIR = bin_cxx
  TARGET = $(TARGETDIR)/nc_lib.lib
  OBJDIR = bin_cxx/win64/work
  DEFINES +=
  INCLUDES += -Isrc_cxx
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -ffloat-store -g -w -std=c99
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -ffloat-store -g -w
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += ../nc_cfg/bin_cxx/nc_cfg.lib
  LDDEPS += ../nc_cfg/bin_cxx/nc_cfg.lib
  ALL_LDFLAGS += $(LDFLAGS) -L../nc_cfg -L/usr/lib64 -m64
  LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),test_win64)
  ifeq ($(origin CC), default)
    CC = F:\dev\gcc\bin\gcc.exe
  endif
  ifeq ($(origin CXX), default)
    CXX = F:\dev\gcc\bin\g++.exe
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  RESCOMP = default
  TARGETDIR = bin_cxx
  TARGET = $(TARGETDIR)/nc_lib.lib
  OBJDIR = bin_cxx/win64/test
  DEFINES +=
  INCLUDES += -Isrc_cxx
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -ffast-math -O2 -w -std=c99
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -ffast-math -O2 -w
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += ../nc_cfg/bin_cxx/nc_cfg.lib
  LDDEPS += ../nc_cfg/bin_cxx/nc_cfg.lib
  ALL_LDFLAGS += $(LDFLAGS) -L../nc_cfg -L/usr/lib64 -m64 -s
  LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),play_win64)
  ifeq ($(origin CC), default)
    CC = F:\dev\gcc\bin\gcc.exe
  endif
  ifeq ($(origin CXX), default)
    CXX = F:\dev\gcc\bin\g++.exe
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  RESCOMP = default
  TARGETDIR = bin_cxx
  TARGET = $(TARGETDIR)/nc_lib.lib
  OBJDIR = bin_cxx/win64/play
  DEFINES +=
  INCLUDES += -Isrc_cxx
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -ffast-math -O3 -w -std=c99
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -ffast-math -O3 -w
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += ../nc_cfg/bin_cxx/nc_cfg.lib
  LDDEPS += ../nc_cfg/bin_cxx/nc_cfg.lib
  ALL_LDFLAGS += $(LDFLAGS) -L../nc_cfg -L/usr/lib64 -m64 -s
  LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
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
	$(OBJDIR)/nc_lib_load.o \
	$(OBJDIR)/nc_lib_entry.o \
	$(OBJDIR)/nc_lib_pch.o \
	$(OBJDIR)/nc_stb_img.o \
	$(OBJDIR)/nc_stb_rect_pack.o \
	$(OBJDIR)/nc_stb_text_edit.o \
	$(OBJDIR)/nc_stb_true_type.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

$(TARGET): $(GCH) ${CUSTOMFILES} $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking nc_lib
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
	@echo Cleaning nc_lib
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
	$(SILENT) $(CC) -x c-header $(ALL_CFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
else
$(OBJECTS): | $(OBJDIR)
endif

$(OBJDIR)/nc_lib_load.o: src_cxx/core/nc_lib_load.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
$(OBJDIR)/nc_lib_entry.o: src_cxx/nc_lib_entry.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
$(OBJDIR)/nc_lib_pch.o: src_cxx/nc_lib_pch.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
$(OBJDIR)/nc_stb_img.o: src_cxx/stb/nc_stb_img.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
$(OBJDIR)/nc_stb_rect_pack.o: src_cxx/stb/nc_stb_rect_pack.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
$(OBJDIR)/nc_stb_text_edit.o: src_cxx/stb/nc_stb_text_edit.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
$(OBJDIR)/nc_stb_true_type.o: src_cxx/stb/nc_stb_true_type.c
	@echo $(notdir $<)
ifeq ($(config),work_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),test_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif
ifeq ($(config),play_win64)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
endif

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif