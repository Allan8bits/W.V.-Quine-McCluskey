CC=gcc
CFLAGS=-Iinclude
SRCDIR=src
BINDIR=bin
TARGET=$(BINDIR)/main.exe

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:$(SRCDIR)/%.c=$(BINDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo Linking $@
	@$(CC) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $<
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo Cleaning
	@del /q /f "$(BINDIR)\*" 2>nul
	@rmdir /q /s "$(BINDIR)" 2>nul

.PHONY: all clean