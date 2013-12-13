#pragma once

#define GDT_SIZE 19
#define IDT_SIZE 256

#define SZ_64 0x2
#define SZ_32 0x4
#define SZ_G  0x8

#define ACC_A     0x01
#define ACC_TYPE  0x1e

#define ACC_TYPE_SYSTEM  0x00

#define ACC_LDT          0x02
#define ACC_CALL_GATE_16 0x04
#define ACC_TASK_GATE    0x05
#define ACC_TSS          0x09
#define ACC_CALL_GATE    0x0c
#define ACC_INTR_GATE    0x0e
#define ACC_TRAP_GATE    0x0f

#define ACC_TSS_BUSY     0x02

#define ACC_TYPE_USER    0x10

#define ACC_DATA         0x10
#define ACC_DATA_W       0x12
#define ACC_DATA_E       0x14
#define ACC_DATA_EW      0x16

#define ACC_CODE         0x18
#define ACC_CODE_R       0x1a
#define ACC_CODE_C       0x1c
#define ACC_CODE_CR      0x1e

#define ACC_PL           0x60
#define ACC_PL_K         0x00
#define ACC_PL_U         0x60
#define ACC_P            0x80

#define SEL_LDTS         0x04
#define SEL_PL           0x03
#define SEL_PL_K         0x00
#define SEL_PL_U         0x03

#define SEL_TO_INDEX(s)  ((s) >> 3)

#define NULL_SEG       0

#define KERNEL64_CS    (0x08 | 0)
#define KERNEL_DS      (0x10 | 0)
#define USER32_CS      (0x18 | 3)
#define USER32_DS      (0x20 | 3)
#define USER64_CS      (0x28 | 3)
#define USER64_DS      USER32_DS
#define KERNEL_TSS     (0x38 | 0)

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <planck/compiler.h>

#pragma pack(1)

typedef struct
{
    uint16_t size;
    uint32_t address;
} descriptor_descriptor_t;

typedef struct
{
    uint16_t size;
    uint64_t address;
} descriptor_descriptor64_t;

typedef struct
{
    uint32_t limit_low : 16;
    uint32_t base_low : 16;
    uint32_t base_med : 8;
    uint32_t access : 8;
    uint32_t limit_high : 4;
    uint32_t granularity : 4;
    uint32_t base_high : 8;
} gdt_descriptor_t;

typedef struct
{
    uint32_t limit_low : 16;
    uint32_t base_low : 16;
    uint32_t base_med : 8;
    uint32_t access : 8;
    uint32_t limit_high : 4;
    uint32_t granularity :4 ;
    uint32_t base_high : 8;
    uint32_t base_top : 32;
    uint32_t reserved : 32;
} gdt_descriptor64_t;

typedef struct
{
    uint32_t offset_low : 16;
    uint32_t selector : 16;
    uint32_t word_count : 8;
    uint32_t access : 8;
    uint32_t offset_high : 16;
} idt_gate_t;

typedef struct
{
    uint32_t offset_low16 : 16;
    uint32_t selector16 : 16;
    uint32_t IST : 3;
    uint32_t zeroes5 : 5;
    uint32_t access8 : 8;
    uint32_t offset_high16 : 16;
    uint32_t offset_top32 : 32;
    uint32_t reserved32 : 32;
} idt_gate64_t;

#pragma pack(0)

#define MAKE_GDT_DESCRIPTOR(base, lim, gran, acc) { \
    .limit_low = lim & 0xffff, \
    .limit_high = (lim >> 16) & 0xf, \
    .base_low = base & 0xffff, \
    .base_med = (base >> 16) & 0xff, \
    .base_high = (base >> 24) & 0xff, \
    .access = acc, \
    .granularity = gran \
}

__BEGIN_DECLS

void segment_init();

__END_DECLS

#endif
