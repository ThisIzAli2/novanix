# /**
#  ** This file is part of AliNix.

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
# Makefile of Alinix kernelm licensed under GNU affero GPL
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

VERSION = 1
PATCHLEVEL = 8
SUBLEVEL = 0

# Check if the make version is exactly 3.80
ifeq ($(MAKE_VERSION),3.80)
    $(error This makefile requires GNU Make version 3.80. Your Make version is $(MAKE_VERSION))
endif

INCLUDEDIRS := include
QEMUOPTIONS := -boot d -device VGA,edid=on,xres=1024,yres=768 -trace events=../qemuTrace.txt -d cpu_reset #-readconfig qemu-usb-config.cfg -drive if=none,id=stick,file=disk.img -device usb-storage,bus=ehci.0,drive=stick

G++PARAMS := -m32 -g -D Alinix  -I $(INCLUDEDIRS) -I arch/mips/include -I arch/alpha/include -Wall -fno-omit-frame-pointer -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-exceptions -fno-rtti -fno-leading-underscore -Wno-write-strings -fpermissive -Wno-unknown-pragmas -lgcc -L/usr/lib/gcc/i686-elf/10.2.0/ -w  -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I arch/alpha/include -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-implicit-function-declaration -Wno-implicit-int  -Wno-missing-prototypes -Wno-declaration-missing-parameter-type -Wno-return-mismatch 
GCCPARAMS := -m32 -g -x c -c   -D Alinix -I $(INCLUDEDIRS) -I arch/mips/include -I arch/alpha/include -Wall -fno-omit-frame-pointer -nostdlib -fno-builtin -Wno-unknown-pragmas -lgcc -L/usr/lib/gcc/i686-elf/10.2.0/ -w  -std=c++17 -ffreestanding -O2 -Wall -Wextra  -I arch/alpha/include  -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-implicit-function-declaration -Wno-implicit-int  -Wno-missing-prototypes -Wno-declaration-missing-parameter-type -Wno-return-mismatch 
ASPARAMS := --32
LDPARAMS := -m elf_i386

KRNLSRCDIR := kernel
KRNLOBJDIR := kernel/obj
KERNEL_SEC_DIR = security

KERNEL_CXX_DIR = kernelcxx/src
LIB_CXX_DIR = libcxx

SECURITY_SRCS := $(wildcard security/*.c)

# Create a list of object files corresponding to the source files
SECURITY_OBJS := $(patsubst $(KRNLSRCDIR)/%.c,$(KRNLOBJDIR)/%.o,$(SECURITY_SRCS))


KRNLFILES := $(shell find $(KRNLSRCDIR) -type f \( -name \*.cpp -o -name \*.s -o -name \*.asm -o -name \*.c \)) #Find all the files that end with .cpp/.s/.asm/.c
KRNLOBJS := $(patsubst $(KRNLSRCDIR)/%,$(KRNLOBJDIR)/%,$(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(KRNLFILES)))))) #Replace the .cpp/.s/.asm/.c extension with .o

####################################
#C++ source files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.cpp
	mkdir -p $(@D)
	@echo "COMPILING $@"
	i686-elf-g++ $(G++PARAMS) -c -o $@ $<

####################################
#C source files
####################################
$(KRNLOBJDIR)/%.o: $(KRNLSRCDIR)/%.c
	mkdir -p $(@D)
	@echo "COMPILING $@"
	i686-elf-gcc $(GCCPARAMS) -c -o $@ $<

$(KRNLOBJDIR)/%.o: libcx/kernelcc/src/%.cpp
	mkdir -p $(@D)
	@echo "COMPILING $@"
	i686-elf-g++ $(GCCPARAMS) -c -o $@ $<



####################################
#GDB Stub
####################################
$(KRNLOBJDIR)/gdb/i386-stub.o: $(KRNLSRCDIR)/gdb/i386-stub.c
	mkdir -p $(@D)
	@echo "COMPILING $@"
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
	@echo "ASSEMBLING $@"
	nasm -f elf32 -O0 $< -o $@

	

# $(KRNLOBJDIR)/security/%.o: $(KRNLSRCDIR)/security/%.c
#     mkdir -p $(@D)
#     @echo "COMPILING $@"
#     $(CC) $(GCCPARAMS) -c -o $@ $<

$(SECURITY_OBJS)/%.o: (SECURITY_SRCS)/%.c
	mkdir -p $(@D)
	@echo "COMPILING $@"
	i686-elf-gcc  $(GCCPARAMS) -c -o $@ $< 




drivers:
	cd drivers && $(MAKE) all

Alinix.bin: kernel/linker.ld $(KRNLOBJS)
	# cd security && $(MAKE) all
	# cd drivers && $(MAKE) all 
	# cd libcs && make || true
	i686-elf-ld $(LDPARAMS) -T $< -o $@ $(KRNLOBJS)

loader :
	cd libcx && make qemu || true
install : Alinix.bin loader



Alinix.iso: Alinix.bin
	nm -a Alinix.bin | sort -d > isofiles/debug.sym || true
	cp -r isofiles/. iso || true
	mkdir iso/boot || true
	mkdir iso/boot/grub || true
	cp Alinix.bin iso/boot/Alinix.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	hdiutil makehybrid -o Alinix.iso iso -iso -joliet
	# rm -rf iso

all : Alinix.iso  drivers install

versionInfo:
	@echo "Kernel Version: $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)"

# menuconfig: $(shell chmod +x dialog.sh && ./dialog.sh)


.PHONY: clean

clean:
	rm -rf $(KRNLOBJDIR) Alinix.bin Alinix.iso
	cd libcx && make clean || true
