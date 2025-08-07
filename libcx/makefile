# /**
#  ** This file is part of Novanix.

# **AliNix is free software: you can redistribute it and/or modify
# **it under the terms of the GNU Affero General Public License as published by
# **the Free Software Foundation, either version 3 of the License, or
# **(at your option) any later version.

# **AliNix is distributed in the hope that it will be useful,
# **but WITHOUT ANY WARRANTY; without even the implied warranty of
# **MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# **GNU Affero General Public License for more details.

# **You should have received a copy of the GNU Affero General Public License
# **along with AliNix. If not, see <https://www.gnu.org/licenses/>.
# */

# The makefile for the Novanix project, this file will get more complicated when the OS is in a later stage of development.

##########
# .s files are GAS assembly
# .asm files are nasm assembly
##########
#####################
#xHCI
# nec-usb-xhci
# qemu-xhci
#EHCI
# usb-ehci
# ich9-usb-ehci1
#UHCI
# ich9-usb-uhci1
# ich9-usb-uhci2
# ich9-usb-uhci3
# piix3-usb-uhci
# piix4-usb-uhci
# vt82c686b-usb-uhci
#OHCI
# sysbus-ohci
# pci-ohci
#######################

# x86_64 Compiler Flags
G++PARAMS_64 := -m64 -g -D NovanixKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -Wno-write-strings -fpermissive -Wno-unknown-pragmas -I ../include -I ../arch/x86_64/include
GCCPARAMS_64 := -m64 -g -D NovanixKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas -I ../include -I ../arch/x86_64/include
ASPARAMS_64 := --64
LDPARAMS_64 := -m elf_x86_64


INCLUDEDIRS := kernelcc/include
QEMUOPTIONS := -boot d -device VGA,edid=on,xres=1024,yres=768 -trace events=../qemuTrace.txt -d cpu_reset #-readconfig qemu-usb-config.cfg -drive if=none,id=stick,file=disk.img -device usb-storage,bus=ehci.0,drive=stick

G++PARAMS := -m32 -g -D NovanixKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas -I ../include -I ../arch/alpha/include
GCCPARAMS := -m32 -g -D NovanixKERNEL -I $(INCLUDEDIRS) -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas -I ../include -I ../arch/alpha/include
ASPARAMS := --32
LDPARAMS := -m elf_i386

KRNLSRCDIR := kernelcc/src
KRNLOBJDIR := kernelcc/obj

KRNLFILES := $(shell find $(KRNLSRCDIR) -type f \( -name \*.cpp -o -name \*.s -o -name \*.asm -o -name \*.c \)) #Find all the files that end with .cpp/.s/.asm/.c
KRNLOBJS := $(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(KRNLFILES))))) #Replace the .cpp/.s/.asm/.c extension with .o
KRNLOBJS := $(subst $(KRNLSRCDIR),$(KRNLOBJDIR),$(KRNLOBJS)) #Replace the kernel/src part with kernel/obj

# C++ source files for x86_64
$(KRNLOBJDIR)/x86_64/%.o: $(KRNLSRCDIR)/%.cpp
	mkdir -p $(@D)
	x86_64-elf-g++ $(G++PARAMS_64) -c -o $@ $<

# C source files for x86_64
$(KRNLOBJDIR)/x86_64/%.o: $(KRNLSRCDIR)/%.c
	mkdir -p $(@D)
	x86_64-elf-gcc $(GCCPARAMS_64) -c -o $@ $<

# GAS assembly for x86_64
$(KRNLOBJDIR)/x86_64/%.o: $(KRNLSRCDIR)/%.s
	mkdir -p $(@D)
	x86_64-elf-as $(ASPARAMS_64) -o $@ $<

# NASM assembly for x86_64
$(KRNLOBJDIR)/x86_64/%.o: $(KRNLSRCDIR)/%.asm
	mkdir -p $(@D)
	nasm -f elf64 -O0 $< -o $@

# Find and build object files for x86_64
KRNLOBJS64 := $(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(KRNLFILES)))))
KRNLOBJS64 := $(subst $(KRNLSRCDIR),$(KRNLOBJDIR)/x86_64,$(KRNLOBJS64))

Alinix64.bin: ../linker64.ld $(KRNLOBJS64)
	x86_64-elf-ld $(LDPARAMS_64) -T $< -o $@ $(KRNLOBJS64)

####################################
#C++ source files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.cpp
	mkdir -p $(@D)
	i686-elf-g++ $(G++PARAMS) -c -o $@ $<

####################################
#C source files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCCPARAMS) -c -o $@ $<

####################################
#GDB Stub
####################################
$(KRNLOBJDIR)/gdb/i386-stub.o: $(KRNLSRCDIR)/gdb/i386-stub.c
	mkdir -p $(@D)
	i686-elf-gcc $(GCCPARAMS) -fleading-underscore -c -o $@ $<

####################################
#GAS assembly files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.s
	mkdir -p $(@D)
	i686-elf-as $(ASPARAMS) -o $@ $<

####################################
#NASM assembly files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.asm
	mkdir -p $(@D)
	nasm -f elf32 -O0 $< -o $@



Alinix.bin: ../linker.ld $(KRNLOBJS)
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(KRNLOBJS)

Alinix.iso: Alinix.bin



.PHONY: clean qemu kdbg run filelist serialDBG qemuDBG fastApps
clean:
	rm -rf $(KRNLOBJDIR) Alinix.bin Alinix.iso
	cd lib/ && $(MAKE) clean
	cd apps/ && $(MAKE) clean
	rm -rf isofiles/apps/*.bin
	rm -rf isofiles/apps/*.sym

qemu: Alinix.iso

qemuDBG: Alinix.iso
	qemu-system-i386 -cdrom Alinix.iso -serial stdio $(QEMUOPTIONS) -s -S &

qemuGDB: Alinix.iso
	qemu-system-i386 -cdrom Alinix.iso $(QEMUOPTIONS) -serial pty &
	gdb -ex 'file Alinix.bin' -ex 'target remote /dev/pts/1' -q

run: Alinix.iso
	vboxmanage startvm "Alinix" -E VBOX_GUI_DBG_AUTO_SHOW=true -E VBOX_GUI_DBG_ENABLED=true &
	rm "Alinix.log"
	echo "" > "Alinix.log"
	tail -f "Alinix.log"

serialDBG:
	gcc -o tools/serialDebugger/a.out tools/serialDebugger/main.c
	sudo ./tools/serialDebugger/a.out

kdbg: Alinix.iso
	qemu-system-i386 $(QEMUOPTIONS) -cdrom Alinix.iso -serial stdio -s -S &
	kdbg -r localhost:1234 Alinix.bin

grub-core:
	

# Only rebuild LIBAlinix and the apps without recompiling the kernel
fastApps:
	rm -rf isofiles/apps/*.bin
	cd lib/ && $(MAKE) clean && $(MAKE)
	cd apps/ && $(MAKE) clean && $(MAKE)
	rm Alinix.iso

turboApps:
	rm -rf isofiles/apps/*.bin
	cd apps/ && $(MAKE) clean && $(MAKE)
	rm Alinix.iso

installUSB: Alinix.iso Alinix.bin isofiles/debug.sym isofiles/apps
	rm -rf /media/remco/ISOIMAGE/apps/*.bin
	cp -r isofiles/apps/* /media/remco/ISOIMAGE/apps/
	cp isofiles/debug.sym /media/remco/ISOIMAGE/debug.sym
	cp Alinix.bin /media/remco/ISOIMAGE/boot/Alinix.bin
	umount /media/remco/ISOIMAGE

debug: Alinix.iso
	pyuic5 tools/advancedDebugger/mainGUI.ui -o tools/advancedDebugger/mainWindow.py
	qemu-system-i386 -cdrom Alinix.iso $(QEMUOPTIONS) -serial pty &
	/usr/bin/python3 tools/advancedDebugger/main.py


filelist:
	@echo "Source Files:"
	@echo -$(KRNLFILES)
	@echo "Object Files:"
	@echo -$(KRNLOBJS)

runit:
	qemu-system-x86_64 -kernel alinix.bin

install: qemu runit

run64: Alinix64.bin
	qemu-system-x86_64 -kernel Alinix64.bin
clean64:
	rm -rf $(KRNLOBJDIR) Alinix.bin Alinix64.bin Alinix.iso

install64: qemu runit run64
