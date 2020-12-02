/*
    Target ISA data structs for cycle analysis.
 */
#ifndef TARGET_ISA
#define TARGET_ISA

/*
    VIGGY: Isa analysis code structure...
*/
typedef enum target_isa_tb_state {
    TARG_ISA_TB_LINEAR = 0,
    TARG_ISA_TB_BRANCH
} target_isa_tb_state;

typedef struct TargetInsn {
    // VIGGY: Taken from capstone's cs_insn data struct.

    /// Instruction ID (basically a numeric ID for the instruction mnemonic)
    /// Find the instruction id in the '[ARCH]_insn' enum in the header file
    /// of corresponding architecture, such as 'arm_insn' in arm.h for ARM,
    /// 'x86_insn' in x86.h for X86, etc...
    //unsigned int _id;

    /// Address (EIP) of this instruction
    /// This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
    //uint64_t _address;

    /// Size of this instruction
    /// This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
    uint16_t _size;

    /// Machine bytes of this instruction, with number of bytes indicated by @size above
    /// This information is available even when CS_OPT_DETAIL = CS_OPT_OFF
    uint8_t _bytes[24];

} TargetInsn;

typedef struct TargetIsaData {
    unsigned long       _pc_start_addr;
    unsigned long       _pc_size;
    target_isa_tb_state _tb_state;
    GArray             *_p_tb_exec_time;    // Array of doubles
    GArray             *_p_isa_insns;       // Array of TargetInsn
} TargetIsaData;

#endif
