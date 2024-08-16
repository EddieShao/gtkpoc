CC ?= gcc

PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4)

INC_DIR = include
RES_DIR = res
SRC_DIR = src

RES_XML = sgsm.gresource.xml

RES_INC_FILE = $(INC_DIR)/resources.h
RES_SRC_FILE = $(SRC_DIR)/resources.c
RES_OBJ_FILE = $(SRC_DIR)/resources.o
RES_PATH_INC_FILE = $(INC_DIR)/resource-paths.h
RES_PATH_SRC_FILE = $(SRC_DIR)/resource-paths.c
RES_PATH_OBJ_FILE = $(SRC_DIR)/resource-paths.o

SRC_FILES = $(shell find . -name "*.c")
RES_FILES = $(shell find $(RES_DIR) -name "*.ui" -o -name "*.css")
OBJ_FILES = $(SRC_FILES:.c=.o)

TARGET = sgsm

all: res bin
res: $(RES_INC_FILE) $(RES_OBJ_FILE) $(RES_PATH_INC_FILE) $(RES_PATH_OBJ_FILE)
bin: $(TARGET)

$(TARGET): $(OBJ_FILES) $(RES_OBJ_FILE) $(RES_PATH_OBJ_FILE)
	$(CC) -I$(INC_DIR) -g -Wall -Wextra -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -I$(INC_DIR) -g -Wall -Wextra -c -o $@ $(CFLAGS) $<

$(RES_OBJ_FILE): $(RES_SRC_FILE)
	$(CC) -I$(INC_DIR) -g -Wall -Wextra -c -o $@ $(CFLAGS) $<

$(RES_SRC_FILE) $(RES_INC_FILE): $(RES_XML) $(RES_FILES)
	glib-compile-resources $< --sourcedir=$(RES_DIR) --target=$@ --generate

$(RES_PATH_OBJ_FILE): $(RES_PATH_SRC_FILE)
	$(CC) -I$(INC_DIR) -g -Wall -Wextra -c -o $@ $(CFLAGS) $<

$(RES_PATH_SRC_FILE) $(RES_PATH_INC_FILE): $(RES_XML)
	python3 gen-res-paths.py $< $@

clean:
	rm -f $(RES_INC_FILE) $(RES_SRC_FILE) $(RES_PATH_INC_FILE) $(RES_PATH_SRC_FILE) $(OBJ_FILES) $(TARGET)

.PHONY: all clean
