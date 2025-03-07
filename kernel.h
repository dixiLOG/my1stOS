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