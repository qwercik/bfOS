; BIOS Parameter Block structure

system_name 			db "bfOS    " 		; Size = 8 B
bytes_per_sector 		dw 0x200
sectors_per_cluster 	db 1
reserved_sectors		dw 1
fats_amount				db 2
max_root_entries		dw 0xE0
total_sector_number		dw 0xB40
media_descriptor		db 0xF0 			; 2 sides, 80 tracks, 18 sectors per track, 3.5"
fat_sector_number		dw 9
sectors_per_track		dw 18
head_number				db 2
hidden_sectors			dd 0
sectors_per_volume		dd 0				; Only for volumes > 32MB (Floppy has 1.44MB)
drive_number			db 0
reserved				db 0
boot_signature			db 0x29
volume_serial_number	dd 0xFFFFFFFF
volume_label			db "bfOS       " 	; Size = 11 B
file_system_name		db "FAT12 "
