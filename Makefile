.PHONY: image
image: filesystem 
	@ dd if=/dev/zero of=floppy.img bs=512 count=512
	@ dd if=bootloader/bin/boot.bin of=floppy.img conv=notrunc
	@ dd if=bootloader/bin/exboot.bin of=floppy.img bs=512 seek=1 conv=notrunc
	@ dd if=fs.img of=floppy.img bs=512 seek=2 conv=notrunc

.PHONY: bootloader
bootloader:
	make -C bootloader 

.PHONY: kernel
kernel:
	make -C kernel

.PHONY: filesystem
filesystem: bootloader kernel
	-@ rm fs.img
	@ mkfs.vfat -C -n "RPOS BOOT" -s 2 -F12 fs.img 255
	@ mmd -i fs.img ::/boot
	@ mcopy -i fs.img kernel/bin/kernel ::/boot/kernel

.PHONY: run
run: image
	cd emu65el02 && wine emu65el02.exe ../floppy.img

.PHONY: clean
clean:
	-@ rm fs.img
	-@ rm floppy.img
	@ make -C bootloader clean
	@ make -C kernel clean

#cp floppy.img /home/hlep/.minecraft/saves/New\ World-/redpower/disk_79ef917f421be20d.img