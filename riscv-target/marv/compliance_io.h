// RISC-V Compliance IO Test Header File

#ifndef _COMPLIANCE_IO_H
#define _COMPLIANCE_IO_H

//-----------------------------------------------------------------------
// RV IO Macros (Mostly non functional)
//-----------------------------------------------------------------------

#define RSIZE 4
// _SP = (volatile register)
#define LOCAL_IO_PUSH(_SP)                                              \
    la      _SP,  begin_regstate;                                       \
    sw      x1,   (1*RSIZE)(_SP);                                       \
    sw      x5,   (5*RSIZE)(_SP);                                       \
    sw      x6,   (6*RSIZE)(_SP);                                       \
    sw      x8,   (8*RSIZE)(_SP);                                       \
    sw      x10,  (10*RSIZE)(_SP);

// _SP = (volatile register)
#define LOCAL_IO_POP(_SP)                                               \
    la      _SP,   begin_regstate;                                      \
    lw      x1,   (1*RSIZE)(_SP);                                       \
    lw      x5,   (5*RSIZE)(_SP);                                       \
    lw      x6,   (6*RSIZE)(_SP);                                       \
    lw      x8,   (8*RSIZE)(_SP);                                       \
    lw      x10,  (10*RSIZE)(_SP);

#define RVTEST_IO_INIT

#define MARV_UART_TX_STATUS (0x21000000)
#define MARV_UART_TX_WRITE (0x21000004)

//#define RVTEST_IO_WRITE_STR(_STR) RVTEST_IO_WRITE_STR(x31, _STR)
#define RVTEST_IO_WRITE_STR(_SP, _STR) \
    LOCAL_IO_PUSH(_SP) \
    .section .data.string; \
20000: \
    .string _STR; \
    .section .text.test; \
    la a0, 20000b; \
10000: \
    lbu t0, (a0); \
    addi a0, a0, 1; \
    beq t0, zero, 10000f; \
30000: \
    li t1, MARV_UART_TX_STATUS; \
    lbu t1, 0(t1); \
    andi t1, t1, 1; \
    beq t1, zero, 30000b; \
    li t1, MARV_UART_TX_WRITE; \
    sb t0, 0(t1); \
    j 10000b; \
10000: \
    LOCAL_IO_POP(_SP)

#define RVTEST_IO_CHECK()
#define RVTEST_IO_ASSERT_GPR_EQ(_SP, _R, _I)
#define RVTEST_IO_ASSERT_SFPR_EQ(_F, _R, _I)
#define RVTEST_IO_ASSERT_DFPR_EQ(_D, _R, _I)

#endif // _COMPLIANCE_IO_H
