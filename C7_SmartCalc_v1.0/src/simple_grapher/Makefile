#### build flags
CC := gcc -std=c11 -Wall -Wextra -Werror
# ERROR_FLAGS := #-Wall -Wextra
MAKE_DEPENDENCE := -MD
MATH_LIB = -lm -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz\
 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -rdynamic
#SANITIZE := -fsanitize=address

#### files
BUILD_DIR := build
SOURCE_FILES := $(filter-out main.c, $(wildcard *.c))
OBJECT_FILES := $(addprefix $(BUILD_DIR)/,$(SOURCE_FILES:.c=.o))


#### build options
INCLUDE_FLAG := -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0\
 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include\
  -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0\
   -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo\
    -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16\
    -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0\
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

#### include dependence file
-include $(BUILD_DIR)/*.d

#### targets

## build object files
$(BUILD_DIR)/%.o: %.c
ifeq ($(OS), Darwin)
	$(CC) -c `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` $<  -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD
else
	@$(CC) $(INCLUDE_FLAG) $< -c -o $@ $(ERROR_FLAGS) $(SANITIZE) -MD $(MATH_LIB) 
endif

## build libgrapher.a target from object files
libgrapher.a: $(OBJECT_FILES)
	@ar rc $@ $(OBJECT_FILES) # -vrcs
#	 ar rc $@ $(OBJECT_FILES)
#	ar rc $@
	@ranlib $@

#### phony targets
.PHONY: clean all #re clear

# re: clean libgrapher.a

all: libgrapher.a

clean:
	@find . -name "*.o" -delete
	@find . -name "*.a" -delete
	@find . -name "*.d" -delete

# clear:
# 	clear
