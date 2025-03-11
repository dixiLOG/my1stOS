#pragma once // 防止头文件被重复包含

#include "common.h"

// 定义PANIC宏，用于输出错误信息并在出错时无限循环
#define PANIC(fmt, ...) \
    do { \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        while (1) {} \
    } while (0)

// 定义READ_CSR宏，用于从指定CSR寄存器读取值
#define READ_CSR(reg) ({ \
    unsigned long __tmp; \
    __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp)); \
    __tmp; \
})

// 定义WRITE_CSR宏，用于向指定CSR寄存器写入值
#define WRITE_CSR(reg, value) \
    do { \
        uint32_t __tmp = (value); \
        __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp)); \
    } while (0)



#define PROCS_MAX 8       // 最大进程数量

#define PROC_UNUSED   0   // 未使用的进程控制结构
#define PROC_RUNNABLE 1   // 可运行的进程

// 定义页表项的一些标志位
#define SATP_SV32 (1u << 31)
#define PAGE_V    (1 << 0)   // "Valid" 位（表项已启用）
#define PAGE_R    (1 << 1)   // 可读
#define PAGE_W    (1 << 2)   // 可写
#define PAGE_X    (1 << 3)   // 可执行
#define PAGE_U    (1 << 4)   // 用户（用户模式可访问）

// 应用程序镜像的基础虚拟地址。这需要与 `user.ld` 中定义的起始地址匹配。
#define USER_BASE 0x1000000

#define SSTATUS_SPIE (1 << 5)

#define SCAUSE_ECALL 8

#define PROC_EXITED   2

// 全局变量声明
extern char __bss[], __bss_end[], __stack_top[];
extern char __kernel_base[]; // 内核基址
extern char __bss[], __bss_end[], __stack_top[];
extern char __free_ram[], __free_ram_end[];
extern char _binary_shell_bin_start[], _binary_shell_bin_size[]; // shell.bin 的起始地址和大小


// 定义sbiret结构体，用于存储系统调用的返回值和错误码
struct sbiret {
    long error;
    long value;
};


// 定义trap_frame结构体，用于存储陷阱帧信息，__attribute__((packed))确保结构体成员紧密排列
struct trap_frame {
    uint32_t ra;   // 返回地址
    uint32_t gp;   // 全局指针
    uint32_t tp;   // 线程指针
    uint32_t t0;   // 临时寄存器0
    uint32_t t1;   // 临时寄存器1
    uint32_t t2;   // 临时寄存器2
    uint32_t t3;   // 临时寄存器3
    uint32_t t4;   // 临时寄存器4
    uint32_t t5;   // 临时寄存器5
    uint32_t t6;   // 临时寄存器6
    uint32_t a0;   // 参数寄存器0
    uint32_t a1;   // 参数寄存器1
    uint32_t a2;   // 参数寄存器2
    uint32_t a3;   // 参数寄存器3
    uint32_t a4;   // 参数寄存器4
    uint32_t a5;   // 参数寄存器5
    uint32_t a6;   // 参数寄存器6
    uint32_t a7;   // 参数寄存器7
    uint32_t s0;   // 保存寄存器0
    uint32_t s1;   // 保存寄存器1
    uint32_t s2;   // 保存寄存器2
    uint32_t s3;   // 保存寄存器3
    uint32_t s4;   // 保存寄存器4
    uint32_t s5;   // 保存寄存器5
    uint32_t s6;   // 保存寄存器6
    uint32_t s7;   // 保存寄存器7
    uint32_t s8;   // 保存寄存器8
    uint32_t s9;   // 保存寄存器9
    uint32_t s10;  // 保存寄存器10
    uint32_t s11;  // 保存寄存器11
    uint32_t sp;   // 栈指针
} __attribute__((packed));

// 进程控制块（PCB）
struct process {
    int pid;             // 进程 ID
    int state;           // 进程状态: PROC_UNUSED 或 PROC_RUNNABLE
    vaddr_t sp;          // 栈指针
    uint32_t *page_table; // 页表
    uint8_t stack[8192]; // 内核栈
};