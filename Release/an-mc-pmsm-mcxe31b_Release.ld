/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2025 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 * Generated linker script file for MCXE31B
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v25.6 [Build 136] [2025-06-27] on Nov 26, 2025, 3:42:03 PM
 */

INCLUDE "an-mc-pmsm-mcxe31b_Release_library.ld"
INCLUDE "an-mc-pmsm-mcxe31b_Release_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
     .text_Flash2 : ALIGN(4)
    {
       FILL(0xff)
        *(.text_Flash2) /* for compatibility with previous releases */
        *(.text_DATA_FLASH) /* for compatibility with previous releases */
        *(.text.$Flash2)
        *(.text.$DATA_FLASH)
        *(.text_Flash2.*) /* for compatibility with previous releases */
        *(.text_DATA_FLASH.*) /* for compatibility with previous releases */
        *(.text.$Flash2.*)
        *(.text.$DATA_FLASH.*)
        *(.rodata.$Flash2)
        *(.rodata.$DATA_FLASH)
        *(.rodata.$Flash2.*)
        *(.rodata.$DATA_FLASH.*)            } > DATA_FLASH

    /* Boot header (image vector table) */
    .boot_hdr : ALIGN(4)
    {
        FILL(0xFF)
        __boot_hdr_start__ = ABSOLUTE(.) ;
        KEEP(*(.boot_header))
        . = 0x100;
        __boot_hdr_end__ = ABSOLUTE(.) ;
        . = 0x1000;
    } > PROGRAM_FLASH
    /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

       *(.text*)
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(4);
    } > PROGRAM_FLASH
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > PROGRAM_FLASH

    .ARM.exidx : ALIGN(4)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > PROGRAM_FLASH
 
    _etext = .;
        
    /* DATA section for DTCM */

    .data_RAM2 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        PROVIDE(__start_data_DTCM = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$DTCM)
       *(DataQuickAccess)
        *(.data.$RAM2)
        *(.data.$DTCM)
        *(.data.$RAM2.*)
        *(.data.$DTCM.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM2 = .) ;
        PROVIDE(__end_data_DTCM = .) ;
     } > DTCM AT>PROGRAM_FLASH

    /* DATA section for ITCM */

    .data_RAM3 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM3 = .) ;
        PROVIDE(__start_data_ITCM = .) ;
        *(.ramfunc.$RAM3)
        *(.ramfunc.$ITCM)
       *(CodeQuickAccess)
        *(.data.$RAM3)
        *(.data.$ITCM)
        *(.data.$RAM3.*)
        *(.data.$ITCM.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM3 = .) ;
        PROVIDE(__end_data_ITCM = .) ;
     } > ITCM AT>PROGRAM_FLASH

    /* DATA section for NCACHE_REGION */

    .data_RAM4 : ALIGN(4)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM4 = .) ;
        PROVIDE(__start_data_NCACHE_REGION = .) ;
        *(.ramfunc.$RAM4)
        *(.ramfunc.$NCACHE_REGION)
       *(NonCacheable.init)
        *(.data.$RAM4)
        *(.data.$NCACHE_REGION)
        *(.data.$RAM4.*)
        *(.data.$NCACHE_REGION.*)
        . = ALIGN(4) ;
        PROVIDE(__end_data_RAM4 = .) ;
        PROVIDE(__end_data_NCACHE_REGION = .) ;
     } > NCACHE_REGION AT>PROGRAM_FLASH

    /* MAIN DATA SECTION */
    .uninit_RESERVED (NOLOAD) : ALIGN(4)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > SRAM_DATA AT> SRAM_DATA

    /* Main DATA section (SRAM_DATA) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM = .) ;
       PROVIDE(__start_data_SRAM_DATA = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
       *(.data*)
       . = ALIGN(4) ;
       _edata = . ;
       PROVIDE(__end_data_RAM = .) ;
       PROVIDE(__end_data_SRAM_DATA = .) ;
    } > SRAM_DATA AT>PROGRAM_FLASH

    /* BSS section for DTCM */
    .bss_RAM2 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_DTCM = .) ;
       *(.bss.$RAM2)
       *(.bss.$DTCM)
       *(.bss.$RAM2.*)
       *(.bss.$DTCM.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_DTCM = .) ;
    } > DTCM AT> DTCM

    /* BSS section for ITCM */
    .bss_RAM3 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       PROVIDE(__start_bss_ITCM = .) ;
       *(.bss.$RAM3)
       *(.bss.$ITCM)
       *(.bss.$RAM3.*)
       *(.bss.$ITCM.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
       PROVIDE(__end_bss_ITCM = .) ;
    } > ITCM AT> ITCM

    /* BSS section for NCACHE_REGION */
    .bss_RAM4 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
       PROVIDE(__start_bss_NCACHE_REGION = .) ;
       *(NonCacheable)
       *(.bss.$RAM4)
       *(.bss.$NCACHE_REGION)
       *(.bss.$RAM4.*)
       *(.bss.$NCACHE_REGION.*)
       . = ALIGN (. != 0 ? 4 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM4 = .) ;
       PROVIDE(__end_bss_NCACHE_REGION = .) ;
    } > NCACHE_REGION AT> NCACHE_REGION

    /* MAIN BSS SECTION */
    .bss (NOLOAD) : ALIGN(4)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM = .) ;
        PROVIDE(__start_bss_SRAM_DATA = .) ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM = .) ;
        PROVIDE(__end_bss_SRAM_DATA = .) ;
        PROVIDE(end = .);
    } > SRAM_DATA AT> SRAM_DATA

    /* NOINIT section for DTCM */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_DTCM = .) ;
       *(.noinit.$RAM2)
       *(.noinit.$DTCM)
       *(.noinit.$RAM2.*)
       *(.noinit.$DTCM.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_DTCM = .) ;
    } > DTCM AT> DTCM

    /* NOINIT section for ITCM */
    .noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM3 = .) ;
       PROVIDE(__start_noinit_ITCM = .) ;
       *(.noinit.$RAM3)
       *(.noinit.$ITCM)
       *(.noinit.$RAM3.*)
       *(.noinit.$ITCM.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM3 = .) ;
       PROVIDE(__end_noinit_ITCM = .) ;
    } > ITCM AT> ITCM

    /* NOINIT section for NCACHE_REGION */
    .noinit_RAM4 (NOLOAD) : ALIGN(4)
    {
       PROVIDE(__start_noinit_RAM4 = .) ;
       PROVIDE(__start_noinit_NCACHE_REGION = .) ;
       *(.noinit.$RAM4)
       *(.noinit.$NCACHE_REGION)
       *(.noinit.$RAM4.*)
       *(.noinit.$NCACHE_REGION.*)
       . = ALIGN(4) ;
       PROVIDE(__end_noinit_RAM4 = .) ;
       PROVIDE(__end_noinit_NCACHE_REGION = .) ;
    } > NCACHE_REGION AT> NCACHE_REGION

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM = .) ;
        PROVIDE(__start_noinit_SRAM_DATA = .) ;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM_DATA = .) ;        
    } > SRAM_DATA AT> SRAM_DATA

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x200;
    .heap (NOLOAD) :  ALIGN(4)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(4);
        _pvHeapLimit = .;
    } > SRAM_DATA

     _StackSize = 0x200;
     /* Reserve space in memory for Stack */
    .heap2stackfill (NOLOAD) :
    {
        . += _StackSize;
    } > SRAM_DATA
    /* Locate actual Stack in memory map */
    .stack ORIGIN(SRAM_DATA) + LENGTH(SRAM_DATA) - _StackSize - 0 (NOLOAD) :  ALIGN(4)
    {
        _vStackBase = .;
        . = ALIGN(4);
        _vStackTop = . + _StackSize;
    } > SRAM_DATA

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
}