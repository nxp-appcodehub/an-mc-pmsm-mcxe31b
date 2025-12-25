/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2025 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 * Generated linker script file for MCXE31B
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v25.6 [Build 136] [2025-06-27] on Dec 15, 2025, 5:47:32 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x400000, LENGTH = 0x400000 /* 4M bytes (alias Flash) */  
  DATA_FLASH (rx) : ORIGIN = 0x10000000, LENGTH = 0x20000 /* 128K bytes (alias Flash2) */  
  SRAM_DATA (rwx) : ORIGIN = 0x20408000, LENGTH = 0x48000 /* 288K bytes (alias RAM) */  
  DTCM (rwx) : ORIGIN = 0x20004000, LENGTH = 0xc000 /* 48K bytes (alias RAM2) */  
  ITCM (rwx) : ORIGIN = 0x0, LENGTH = 0x8000 /* 32K bytes (alias RAM3) */  
  NCACHE_REGION (rwx) : ORIGIN = 0x20000000, LENGTH = 0x4000 /* 16K bytes (alias RAM4) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x400000  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x400000 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x400000 + 0x400000 ; /* 4M bytes */  
  __top_Flash = 0x400000 + 0x400000 ; /* 4M bytes */  
  __base_DATA_FLASH = 0x10000000  ; /* DATA_FLASH */  
  __base_Flash2 = 0x10000000 ; /* Flash2 */  
  __top_DATA_FLASH = 0x10000000 + 0x20000 ; /* 128K bytes */  
  __top_Flash2 = 0x10000000 + 0x20000 ; /* 128K bytes */  
  __base_SRAM_DATA = 0x20408000  ; /* SRAM_DATA */  
  __base_RAM = 0x20408000 ; /* RAM */  
  __top_SRAM_DATA = 0x20408000 + 0x48000 ; /* 288K bytes */  
  __top_RAM = 0x20408000 + 0x48000 ; /* 288K bytes */  
  __base_DTCM = 0x20004000  ; /* DTCM */  
  __base_RAM2 = 0x20004000 ; /* RAM2 */  
  __top_DTCM = 0x20004000 + 0xc000 ; /* 48K bytes */  
  __top_RAM2 = 0x20004000 + 0xc000 ; /* 48K bytes */  
  __base_ITCM = 0x0  ; /* ITCM */  
  __base_RAM3 = 0x0 ; /* RAM3 */  
  __top_ITCM = 0x0 + 0x8000 ; /* 32K bytes */  
  __top_RAM3 = 0x0 + 0x8000 ; /* 32K bytes */  
  __base_NCACHE_REGION = 0x20000000  ; /* NCACHE_REGION */  
  __base_RAM4 = 0x20000000 ; /* RAM4 */  
  __top_NCACHE_REGION = 0x20000000 + 0x4000 ; /* 16K bytes */  
  __top_RAM4 = 0x20000000 + 0x4000 ; /* 16K bytes */  
