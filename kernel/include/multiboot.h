#pragma once

#include "stdint.h"

struct multiboot_aout_symbol_table
{
    uint32 tabsize;
    uint32 strsize;
    uint32 addr;
    uint32 reserved;
};

struct multiboot_elf_section_header_table
{
    uint32 num;
    uint32 size;
    uint32 addr;
    uint32 shndx;
};

struct multiboot_info
{
    uint32 flags;
    uint32 mem_lower;
    uint32 mem_upper;
    uint32 boot_device;

    uint32 cmdline;
    uint32 mods_count;
    uint32 mods_addr;

    union
    {
        struct multiboot_aout_symbol_table aout_sym;
        struct multiboot_elf_section_header_table elf_sec;
    } u;

    uint32 mmap_length;
    uint32 mmap_addr;

    uint32 drives_length;
    uint32 drives_addr;

    uint32 config_table;
    uint32 boot_loader_name;

    uint32 apm_table;

    uint32 vbe_control_info;
    uint32 vbe_mode_info;
    uint16 vbe_mode;
    uint16 vbe_interface_seg;
    uint16 vbe_interface_off;
    uint16 vbe_interface_len;
};

struct multiboot_mmap_entry
{
    uint32 size;
    uint32 addr_low;
    uint32 addr_high;
    uint32 len_low;
    uint32 len_high;
#define MULTIBOOT_MEMORY_AVAILABLE 1
#define MULTIBOOT_MEMORY_RESERVED 2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS 4
#define MULTIBOOT_MEMORY_BADRAM 5
    uint32 type;
} __attribute__((packed));
