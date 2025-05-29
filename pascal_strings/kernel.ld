/* linker script */
SECTIONS {
        .text 0x40000000 : {
                *(.text)
        }
        .data : {
                *(.data)
        }
	.c 0x40001000 : {
		*(.c)
	}
	.pascal 0x40000500 : { 
		*(.pascal)	
	}	
}
