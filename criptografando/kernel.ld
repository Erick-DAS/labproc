/* linker script */
SECTIONS {
        .text 0x40000000 : {
                *(.text)
        }
        .data 0x40001000: {
                *(.data)
        }
}
