SECTIONS {
  /*
   * Segmento text (programa)
   */
  . = 0x8000;
  .text : { *(.text) }

  /*
   * Segmento rodata (constantes)
   */
  . = ALIGN(8);
  rodata_begin = .;
  .rodata : { *(.rodata) }
  rodata_end = .;
  
  /*
   * Segmento data (variáveis inicializadas)
   */
  . = ALIGN(8);
  data_begin = .;
  .data : { *(.data) }

  /*
   * Segmento bss (variáveis não inicializadas)
   */
  . = ALIGN(8);
  bss_begin = .;
  .bss : { *(.bss*) }
  bss_end = .;

  /*
   * Heap e stack
   */
  . = ALIGN(8);
  heap_svr = .;
  . = . + 8K;
  stack_svr = .;
}