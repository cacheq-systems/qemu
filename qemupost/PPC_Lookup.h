// Copyright (c) 2018-2021 CacheQ Systems Inc. All rights reserved.
//
//  PPC_Lookup.h
//  qemupost
//

#ifndef PPC_LOOKUP_H
#define PPC_LOOKUP_H

#include <string.h>
#include "itoa.h"

// Make sure this code is always compiled as C
// maximum speed.
#ifdef __cplusplus
extern "C" {
#endif

// Group Mask.
//
// Used to get the high level group of an instruction.
const uint32_t group_mask  = 0xFC000000;
const uint32_t group_shift = 26;

const uint32_t rD_mask     = 0x03E00000;
const uint32_t rD_shift    = 21;

const uint32_t rS_mask     = 0x03E00000;
const uint32_t rS_shift    = 21;

const uint32_t rA_mask     = 0x001F0000;
const uint32_t rA_shift    = 16;

const uint32_t rB_mask     = 0x0000F800;
const uint32_t rB_shift    = 11;

const uint32_t DS_mask     = 0x0000FFFC;
const uint32_t DS_shift    = 2;

const uint32_t BD_mask     = 0x0000FFFC;
const uint32_t BD_shift    = 2;

const uint32_t LI_mask     = 0x03FFFFFC;
const uint32_t LI_shift    = 2;

const uint32_t AA_mask     = 0x00000002;
const uint32_t AA_shift    = 1;

const uint32_t BO_mask     = 0x03E00000;
const uint32_t BO_shift    = 21;

const uint32_t BI_mask     = 0x001F0000;
const uint32_t BI_shift    = 16;

const uint32_t BH_mask     = 0x00001800;
const uint32_t BH_shift    = 11;

const uint32_t SIMM_mask   = 0x0000FFFF;
const uint32_t SIMM_shift  = 0;

const uint32_t UIMM_mask   = 0x0000FFFF;
const uint32_t UIMM_shift  = 0;

const uint32_t LEV_mask    = 0x00000FE0;
const uint32_t LEV_shift   = 5;

const uint32_t mb1_5_mask  = 0x000007C0;
const uint32_t mb1_5_shift = 6;
const uint32_t mb0_mask    = 0x00000020;
const uint32_t mb0_shift   = 0;

const uint32_t me1_5_mask  = 0x000007C0;
const uint32_t me1_5_shift = 6;
const uint32_t me0_mask    = 0x00000020;
const uint32_t me0_shift   = 0;

const uint32_t sh1_5_mask  = 0x0000F800;
const uint32_t sh1_5_shift = 11;
const uint32_t sh0_mask    = 0x00000002;
const uint32_t sh0_shift   = 4;

const uint32_t MB_mask     = 0x000007C0;
const uint32_t MB_shift    = 6;

const uint32_t ME_mask     = 0x0000003E;
const uint32_t ME_shift    = 1;


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: SignExt32
//
// Sign extend values in a signed 32 bit value.
//
///////////////////////////////////////////////////////////////////////////////

inline int32_t
SignExt32( int32_t value, uint32_t bit_size )
    {
    return ( value << ( 32 - bit_size ) ) >> ( 32 - bit_size );
    }


// Accessors to get field values from instruction opcodes.
#define get_group_value( ppc_instruction ) ( ( ppc_instruction & group_mask ) >> group_shift )

#define get_rD_value( ppc_instruction ) ( ( ppc_instruction & rD_mask ) >> rD_shift )
#define get_rS_value( ppc_instruction ) ( ( ppc_instruction & rS_mask ) >> rS_shift )
#define get_rA_value( ppc_instruction ) ( ( ppc_instruction & rA_mask ) >> rA_shift )
#define get_rB_value( ppc_instruction ) ( ( ppc_instruction & rB_mask ) >> rB_shift )

#define get_BD_value( ppc_instruction ) ( ( ppc_instruction & BD_mask ) >> BD_shift )
#define get_DS_value( ppc_instruction ) ( ( ppc_instruction & DS_mask ) >> DS_shift )
#define get_LI_value( ppc_instruction ) ( ( ppc_instruction & LI_mask ) >> LI_shift )
#define get_AA_value( ppc_instruction ) ( ( ppc_instruction & AA_mask ) >> AA_shift )
#define get_BO_value( ppc_instruction ) ( ( ppc_instruction & BO_mask ) >> BO_shift )
#define get_BI_value( ppc_instruction ) ( ( ppc_instruction & BI_mask ) >> BI_shift )
#define get_BH_value( ppc_instruction ) ( ( ppc_instruction & BH_mask ) >> BH_shift )

#define get_SIMM_value( ppc_instruction ) ( ( ppc_instruction & SIMM_mask ) >> SIMM_shift )
#define get_UIMM_value( ppc_instruction ) ( ( ppc_instruction & UIMM_mask ) >> UIMM_shift )

#define get_LEV_value( ppc_instruction ) ( ( ppc_instruction & LEV_mask ) >> LEV_shift )

#define get_mb_value( ppc_instruction ) ( ( ( ppc_instruction & mb0_mask ) >> mb0_shift ) | ( ( ppc_instruction & mb1_5_mask ) >> mb1_5_shift ) )
#define get_me_value( ppc_instruction ) ( ( ( ppc_instruction & me0_mask ) >> me0_shift ) | ( ( ppc_instruction & me1_5_mask ) >> me1_5_shift ) )
#define get_sh_value( ppc_instruction ) ( ( ( ppc_instruction & sh0_mask ) << me0_shift ) | ( ( ppc_instruction & sh1_5_mask ) >> sh1_5_shift ) )
#define get_MB_value( ppc_instruction ) ( ( ppc_instruction & MB_mask ) >> MB_shift )
#define get_ME_value( ppc_instruction ) ( ( ppc_instruction & ME_mask ) >> ME_shift )

#define get_xo_value( ppc_instruction_ptr, ppc_instruction )  ( ( ppc_instruction & ppc_instruction_ptr->xo_mask )  >> ppc_instruction_ptr->xo_shift )
#define get_rc_value( ppc_instruction_ptr, ppc_instruction )  ( ( ppc_instruction & ppc_instruction_ptr->rc_mask )  >> ppc_instruction_ptr->rc_shift )
#define get_l_value( ppc_instruction_ptr, ppc_instruction )   ( ( ppc_instruction & ppc_instruction_ptr->l_mask )   >> ppc_instruction_ptr->l_shift )
#define get_xfx_value( ppc_instruction_ptr, ppc_instruction ) ( ( ppc_instruction & ppc_instruction_ptr->xfx_mask ) >> ppc_instruction_ptr->xfx_shift )
#define get_oe_value( ppc_instruction_ptr, ppc_instruction )  ( ( ppc_instruction & ppc_instruction_ptr->oe_mask )  >> ppc_instruction_ptr->oe_shift )

// Used to fill out switch case values with non XO bit patterns
// when matching the full, wider XO value field.
#define xo_field_left_bits_fill( fill_bits, fill_shift, base_xo ) ( ( fill_bits << fill_shift ) | base_xo )
#define xo_field_right_bits_fill( fill_bits, fill_shift, base_xo ) ( ( base_xo << fill_shift ) | fill_bits )

// Instruction Element.
//
// Contains the cycle data and masks to further dissect
// an instruction to the individual instruction.
struct instruction_element
    {
    const char * mnemonic;
    uint8_t      repeat_rate_cycles;
    uint8_t      latency_cycles;
    uint32_t     xo_mask;
    int32_t      xo_shift;
    uint32_t     rc_mask;
    int32_t      rc_shift;
    uint32_t     l_mask;
    int32_t      l_shift;
    uint32_t     xfx_mask;
    int32_t      xfx_shift;
    uint32_t     oe_mask;
    int32_t      oe_shift;
    uint8_t      addr_cmds[ 12 ];
    };
typedef struct instruction_element instruction_element;


// Addressing string output commands.
enum addressing_string_commands
    {
    end_cmd = 0,
    comma_cmd,
    TO_cmd,   //
    SIMM_cmd,
    UIMM_cmd,
    CRM_cmd,  //
    LEV_cmd,
    CT_cmd,   //
    L_cmd,    //
    E_cmd,    //
    T_cmd,    //
    MO_cmd,   //
    TH_cmd,   //
    OC_cmd,   //
    BD_cmd,
    LI_cmd,
    BO_cmd,
    BI_cmd,
    BH_cmd,
    MB_cmd,
    ME_cmd,
    sh_cmd,
    mb_cmd,
    me_cmd,
    DCRN_cmd, //
    PCRN_cmd, //
    TMRN_cmd, //
    SPR_cmd,  //
    crD_cmd,  //
    crbD_cmd, //
    crbA_cmd, //
    crbB_cmd, //
    rS_cmd,
    rD_cmd,
    rA_cmd,
    rB_cmd,
    rA_disp_indirect_cmd,
    frS_cmd,  //
    frD_cmd,  //
    frA_cmd,  //
    frB_cmd,  //
    frC_cmd   //
    };


// Linear indexes into the Instruction Element tables.
enum instruction_table_indexes
    {
    tdi_index = 0,
    twi_index,
    mulli_index,
    subfic_index,
    cmpli_index,
    cmpi_index,
    addic_index,
    addic_dot_index,
    addi_index,
    addis_index,

    bc_index = 0,
    bcl_index,
    bca_index,
    bcla_index,

    sc_index = 0,

    b_index = 0,
    bl_index,
    ba_index,
    bla_index,

    mcrf_index = 0,
    bclr_index,
    bclrl_index,
    crnor_index,
    rfmci_index,
    rfdi_index,
    rfi_index,
    rfci_index,
    rfgi_index,
    crandc_index,
    isync_index,
    crxor_index,
    dnh_index,
    crnand_index,
    crand_index,
    creqv_index,
    crorc_index,
    cror_index,
    bcctr_index,
    bcctrl_index,

    rlwimi_index = 0,
    rlwimi_dot_index,
    rlwinm_index,
    rlwinm_dot_index,
    rlwnm_index,
    rlwnm_dot_index,

    ori_index = 0,
    oris_index,
    xori_index,
    xoris_index,
    andi_dot_index,
    andis_dot_index,

    rldicl_index = 0,
    rldicl_dot_index,
    rldicr_index,
    rldicr_dot_index,
    rldic_index,
    rldic_dot_index,
    rldimi_index,
    rldimi_dot_index,
    rldcl_index,
    rldcl_dot_index,
    rldcr_index,
    rldcr_dot_index,

    cmp_index = 0,
    tw_index,
    subfc_index,
    subfc_dot_index,
    mulhdu_index,
    mulhdu_dot_index,
    addc_index,
    addc_dot_index,
    mulhwu_index,
    mulhwu_dot_index,
    isel_index,
    tlbilx_index,
    mfcr_index,
    mfocrf_index,
    lwarx_index,
    ldx_index,
    icbt_index,
    lwzx_index,
    slw_index,
    slw_dot_index,
    cntlzw_index,
    cntlzw_dot_index,
    sld_index,
    sld_dot_index,
    and_index,
    and_dot_index,
    ldepx_index,
    lwepx_index,
    cmpl_index,
    subf_index,
    subf_dot_index,
    ldux_index,
    dcbst_index,
    lwzux_index,
    cntlzd_index,
    cntlzd_dot_index,
    andc_index,
    andc_dot_index,
    wait_index,
    dcbstep_index,
    td_index,
    mulhd_index,
    mulhd_dot_index,
    mulhw_index,
    mulhw_dot_index,
    mfmsr_index,
    ldarx_index,
    dcbf_index,
    lbzx_index,
    lbepx_index,
    neg_index,
    neg_dot_index,
    lbzux_index,
    popcntb_index,
    nor_index,
    nor_dot_index,
    dcbfep_index,
    wrtee_index,
    dcbtstls_index,
    subfe_index,
    subfe_dot_index,
    adde_index,
    adde_dot_index,
    mtcrf_index,
    mtocrf_index,
    mtmsr_index,
    stdx_index,
    stwcx_dot_index,
    stwx_index,
    prtyw_index,
    stdepx_index,
    stwepx_index,
    wrteei_index,
    dcbtls_index,
    mfpmr_index,
    mtmsrd_index,
    stdux_index,
    stwux_index,
    prtyd_index,
    subfze_index,
    subfze_dot_index,
    addze_index,
    addze_dot_index,
    msgsnd_index,
    stdcx_dot_index,
    stbx_index,
    stbepx_index,
    icblc_index,
    mtpmr_index,
    subfme_index,
    subfme_dot_index,
    mulld_index,
    mulld_dot_index,
    mulldo_index,
    mulldo_dot_index,
    addme_index,
    addme_dot_index,
    mullw_index,
    mullw_dot_index,
    mullwo_index,
    mullwo_dot_index,
    msgclr_index,
    dcbtst_index,
    stbux_index,
    bpermd_index,
    dcbtstep_index,
    add_index,
    add_dot_index,
    ehpriv_index,
    dcbt_index,
    lhzx_index,
    eqv_index,
    eqv_dot_index,
    lhepx_index,
    lhzux_index,
    xor_index,
    xor_dot_index,
    dcbtep_index,
    mfspr_index,
    lwax_index,
    lhax_index,
    mftb_index,
    lwaux_index,
    lhaux_index,
    popcntw_index,
    dcblc_index,
    sthx_index,
    orc_index,
    orc_dot_index,
    sradi_index,
    sradi_dot_index,
    sthepx_index,
    sthux_index,
    or_index,
    or_dot_index,
    divdu_index,
    divdu_dot_index,
    divwu_index,
    divwu_dot_index,
    mtspr_index,
    dcbi_index,
    nand_index,
    nand_dot_index,
    dsn_index,
    icbtls_index,
    divd_index,
    divd_dot_index,
    divw_index,
    divw_dot_index,
    popcntd_index,
    cmpb_index,
    mcrxr_index,
    lbdx_index,
    subfco_index,
    subfco_dot_index,
    addco_index,
    addco_dot_index,
    ldbrx_index,
    lwbrx_index,
    lfsx_index,
    srw_index,
    srw_dot_index,
    srd_index,
    srd_dot_index,
    lhdx_index,
    subfo_index,
    subfo_dot_index,
    tlbsync_index,
    lfsux_index,
    lwdx_index,
    sync_index,
    lfdx_index,
    lfdepx_index,
    lddx_index,
    nego_index,
    nego_dot_index,
    lfdux_index,
    stbdx_index,
    subfeo_index,
    subfeo_dot_index,
    addeo_index,
    addeo_dot_index,
    stdbrx_index,
    stwbrx_index,
    stfsx_index,
    sthdx_index,
    stfsux_index,
    stwdx_index,
    subfzeo_index,
    subfzeo_dot_index,
    addzeo_index,
    addzeo_dot_index,
    stfdx_index,
    stfdepx_index,
    stddx_index,
    subfmeo_index,
    subfmeo_dot_index,
    addmeo_index,
    addmeo_dot_index,
    dcba_index,
    dcbal_index,
    stfdux_index,
    addo_index,
    addo_dot_index,
    tlbivax_index,
    lhbrx_index,
    sraw_index,
    sraw_dot_index,
    srad_index,
    srad_dot_index,
    lfddx_index,
    srawi_index,
    srawi_dot_index,
    mbar_index,
    tlbsx_index,
    sthbrx_index,
    extsh_index,
    extsh_dot_index,
    stfddx_index,
    tlbre_index,
    extsb_index,
    extsb_dot_index,
    divduo_index,
    divduo_dot_index,
    divwuo_index,
    divwuo_dot_index,
    tlbwe_index,
    icbi_index,
    stfiwx_index,
    extsw_index,
    extsw_dot_index,
    icbiep_index,
    divdo_index,
    divdo_dot_index,
    divwo_index,
    divwo_dot_index,
    dcbz_index,
    dcbzl_index,
    dcbzep_index,
    dcbzlep_index,

    lwz_index = 0,
    lwzu_index,
    lbz_index,
    lbzu_index,
    stw_index,
    stwu_index,
    stb_index,
    stbu_index,
    lhz_index,
    lhzu_index,
    lha_index,
    lhau_index,
    sth_index,
    sthu_index,
    lmw_index,
    stmw_index,
    lfs_index,
    lfsu_index,
    lfd_index,
    lfdu_index,
    stfs_index,
    stfsu_index,
    stfd_index,
    stfdu_index,

    ld_index = 0,
    ldu_index,
    lwa_index,

    fdivs_index = 0,
    fdivs_dot_index,
    fsubs_index,
    fsubs_dot_index,
    fadds_index,
    fadds_dot_index,
    fres_index,
    fres_dot_index,
    fmuls_index,
    fmuls_dot_index,
    fmsubs_index,
    fmsubs_dot_index,
    fmadds_index,
    fmadds_dot_index,
    fnmsubs_index,
    fnmsubs_dot_index,
    fnmadds_index,
    fnmadds_dot_index,

    std_index = 0,
    stdu_index,

    fcmpu_index = 0,
    frsp_index,
    frsp_dot_index,
    fctiw_index,
    fctiw_dot_index,
    fctiwz_index,
    fctiwz_dot_index,
    fdiv_index,
    fdiv_dot_index,
    fsub_index,
    fsub_dot_index,
    fadd_index,
    fadd_dot_index,
    fsel_index,
    fsel_dot_index,
    fmul_index,
    fmul_dot_index,
    frsqrte_index,
    frsqrte_dot_index,
    fmsub_index,
    fmsub_dot_index,
    fmadd_index,
    fmadd_dot_index,
    fnmsub_index,
    fnmsub_dot_index,
    fnmadd_index,
    fnmadd_dot_index,
    fcmpo_index,
    mtfsb1_index,
    mtfsb1_dot_index,
    fneg_index,
    fneg_dot_index,
    mcrfs_index,
    mtfsb0_index,
    mtfsb0_dot_index,
    fmr_index,
    fmr_dot_index,
    mtfsfi_index,
    mtfsfi_dot_index,
    fnabs_index,
    fnabs_dot_index,
    fabs_index,
    fabs_dot_index,
    mffs_index,
    mffs_dot_index,
    mtfsf_index,
    mtfsf_dot_index,
    fctid_index,
    fctid_dot_index,
    fctidz_index,
    fctidz_dot_index,
    fcfid_index,
    fcfid_dot_index,
    
    nop_index = 0,
    li_index,
    lis_index,
    la_index,
    mr_index,
    not_index,
    mtcr_index,
    };


// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element simplified_mnemonics_instruction_data[] =
    {
    { "nop     ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   24,      _,     _,    _,     _,     _,   
                { end_cmd } },
    { "li      ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   14,      _,     _,    _,     _,     _,  
                { rD_cmd, comma_cmd, SIMM_cmd, end_cmd } },
    { "lis     ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   15,      _,     _,    _,     _,     _,  
                { rD_cmd, comma_cmd, SIMM_cmd, end_cmd } },
    { "la      ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   14,      _,     _,    _,     _,     _,  
                { end_cmd } },
    { "mr      ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    444,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "not     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    124,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "mtcr    ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,        0x1,          20,           0,          0,        //   31,    144,     _,    _,     0,     _,   
                { end_cmd } }
    };


// Instruction Element tables.

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_2_to_15_instruction_data[] =
    {
    { "tdi     ",            2,                   2,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //    2,      _,     _,    _,     _,     _, 
                { end_cmd } },
    { "twi     ",            2,                   2,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //    3,      _,     _,    _,     _,     _, 
                { end_cmd } },
    { "mulli   ",            2,                   4,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //    7,      _,     _,    _,     _,     _,  
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, SIMM_cmd ,end_cmd } },
    { "subfic  ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //    8,      _,     _,    _,     _,     _, 
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, SIMM_cmd ,end_cmd } },
    { "cmpli   ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   10,      _,     _,    _,     _,     _,  
                { end_cmd } },
    { "cmpi    ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   11,      _,     _,    _,     _,     _, 
                { end_cmd } },
    { "addic   ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   12,      _,     _,    _,     _,     _, 
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, SIMM_cmd ,end_cmd } },
    { "addic.  ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   13,      _,     _,    _,     _,     _,  
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, SIMM_cmd ,end_cmd } },
    { "addi    ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   14,      _,     _,    _,     _,     _,  
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, SIMM_cmd ,end_cmd } },
    { "addis   ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   15,      _,     _,    _,     _,     _,  
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, SIMM_cmd ,end_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_16_instruction_data[] =
    {
    { "bc      ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   16,      0,     _,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BD_cmd, end_cmd } },
    { "bcl     ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   16,      1,     _,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BD_cmd, end_cmd } },
    { "bca     ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   16,      2,     _,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BD_cmd, end_cmd } },
    { "bcla    ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   16,      3,     _,    _,     _,     _, 
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BD_cmd, end_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_17_instruction_data[] =
    {
    { "sc      ",            0,                   0,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   17,      _,     _,    _,     _,     _,  
                { LEV_cmd, end_cmd } },
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_18_instruction_data[] =
    {
    { "b       ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   18,      0,     _,    _,     _,     _,   
                { LI_cmd, end_cmd } },
    { "bl      ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   18,      1,     _,    _,     _,     _,   
                { LI_cmd, end_cmd } },
    { "ba      ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   18,      2,     _,    _,     _,     _,   
                { LI_cmd, end_cmd } },
    { "bla     ",            1,                   1,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   18,      3,     _,    _,     _,     _, 
                { LI_cmd, end_cmd } },
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_19_instruction_data[] =
    {
    { "mcrf    ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,      0,     _,    _,     _,     _,   
                { end_cmd } },
    { "bclr    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   19,     16,     0,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BH_cmd, end_cmd } },
    { "bclrl   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   19,     16,     1,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BH_cmd, end_cmd } },
    { "crnor   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,     33,     _,    _,     _,     _,   
                { end_cmd } },
    { "rfmci   ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,     38,     _,    _,     _,     _,   
                { end_cmd } },
    { "rfdi    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,     39,     _,    _,     _,     _,   
                { end_cmd } },
    { "rfi     ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,     50,     _,    _,     _,     _,   
                { end_cmd } },
    { "rfci    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,     51,     _,    _,     _,     _,   
                { end_cmd } },
    { "rfgi    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    102,     _,    _,     _,     _,   
                { end_cmd } },
    { "crandc  ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    129,     _,    _,     _,     _,   
                { end_cmd } },
    { "isync   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    150,     _,    _,     _,     _,   
                { end_cmd } },
    { "crxor   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    193,     _,    _,     _,     _,   
                { end_cmd } },
    { "dnh     ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    198,     _,    _,     _,     _,   
                { end_cmd } },
    { "crnand  ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    225,     _,    _,     _,     _,   
                { end_cmd } },
    { "crand   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    257,     _,    _,     _,     _,   
                { end_cmd } },
    { "creqv   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    289,     _,    _,     _,     _,   
                { end_cmd } },
    { "crorc   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    417,     _,    _,     _,     _,   
                { end_cmd } },
    { "cror    ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   19,    449,     _,    _,     _,     _,   
                { end_cmd } },
    { "bcctr   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   19,    528,     0,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BH_cmd, end_cmd } },
    { "bcctrl  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   19,    528,     1,    _,     _,     _,   
                { BO_cmd, comma_cmd, BI_cmd, comma_cmd, BH_cmd, end_cmd } }
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_group_19_instruction_element
//
///////////////////////////////////////////////////////////////////////////////

inline instruction_element *
lookup_group_19_instruction_element( instruction_element * element,
                                     uint32_t              instruction )
    {    
    uint32_t instruction_xo = get_xo_value( element, instruction );

    switch( instruction_xo )
        {
        case 0:
            return &group_19_instruction_data[ mcrf_index ];
        
        case 16:
            return &group_19_instruction_data[ bclr_index ] + get_rc_value( element, instruction );
        
        case 33:
            return &group_19_instruction_data[ crnor_index ];
        
        case 38:
            return &group_19_instruction_data[ rfmci_index ];
        
        case 39:
            return &group_19_instruction_data[ rfdi_index ];
        
        case 50:
            return &group_19_instruction_data[ rfi_index ];
        
        case 51:
            return &group_19_instruction_data[ rfci_index ];
        
        case 102:
            return &group_19_instruction_data[ rfgi_index ];
        
        case 129:
            return &group_19_instruction_data[ crandc_index ];
        
        case 150:
            return &group_19_instruction_data[ isync_index ];
        
        case 193:
            return &group_19_instruction_data[ crxor_index ];
        
        case 198:
            return &group_19_instruction_data[ dnh_index ];
        
        case 225:
            return &group_19_instruction_data[ crnand_index ];
        
        case 257:
            return &group_19_instruction_data[ crand_index ];
        
        case 289:
            return &group_19_instruction_data[ creqv_index ];
        
        case 417:
            return &group_19_instruction_data[ crorc_index ];
        
        case 449:
            return &group_19_instruction_data[ cror_index ];
        
        case 528:
            return &group_19_instruction_data[ bcctr_index ] + get_rc_value( element, instruction );
        };
    
    return (instruction_element *)NULL;
    }


// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_20_to_23_instruction_data[] =
    {
    { "rlwimi  ",            1,                   1,               0,         0,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   20,      _,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, MB_cmd, comma_cmd, ME_cmd, end_cmd } },
    { "rlwimi. ",            1,                   1,               0,         0,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   20,      _,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, MB_cmd, comma_cmd, ME_cmd, end_cmd } },
    { "rlwinm  ",            1,                   1,               0,         0,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   21,      _,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, MB_cmd, comma_cmd, ME_cmd, end_cmd } },
    { "rlwinm. ",            1,                   1,               0,         0,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   21,      _,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, MB_cmd, comma_cmd, ME_cmd, end_cmd } },
    { "rlwnm   ",            2,                   2,               0,         0,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   23,      _,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, MB_cmd, comma_cmd, ME_cmd, end_cmd } },
    { "rlwnm.  ",            2,                   2,               0,         0,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   23,      _,     1,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, MB_cmd, comma_cmd, ME_cmd, end_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_24_to_29_instruction_data[] =
    {
    { "ori     ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   24,      _,     _,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, UIMM_cmd } },
    { "oris    ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   25,      _,     _,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, UIMM_cmd } },
    { "xori    ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   26,      _,     _,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, UIMM_cmd } },
    { "xoris   ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   27,      _,     _,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, UIMM_cmd } },
    { "andi.   ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   28,      _,     _,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, UIMM_cmd } },
    { "andis.  ",            1,                   1,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   29,      _,     _,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, UIMM_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_30_instruction_data[] =
    {
    { "rldicl  ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      0,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldicl. ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      0,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldicr  ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      1,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, me_cmd, end_cmd } },
    { "rldicr. ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      1,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, me_cmd, end_cmd } },
    { "rldic   ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      2,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldic.  ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      2,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldimi  ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      3,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldimi. ",            1,                   1,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      3,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, sh_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldcl   ",            2,                   2,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      8,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldcl.  ",            2,                   2,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      8,     1,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, mb_cmd, end_cmd } },
    { "rldcr   ",            2,                   2,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      9,     0,    _,     _,     _,   
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, me_cmd, end_cmd } },
    { "rldcr.  ",            2,                   2,            0x1E,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   30,      9,     1,    _,     _,     _,  
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, comma_cmd, me_cmd, end_cmd } }
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_group_30_instruction_element
//
///////////////////////////////////////////////////////////////////////////////

inline instruction_element *
lookup_group_30_instruction_element( instruction_element * element,
                                     uint32_t              instruction )
    {    
    uint32_t instruction_xo = get_xo_value( element, instruction );

    switch( instruction_xo )
        {
        case xo_field_right_bits_fill(0, 1, 0 ):
        case xo_field_right_bits_fill(1, 1, 0 ):
            return &group_30_instruction_data[ rldicl_index ] + get_rc_value( element, instruction );
        
        case xo_field_right_bits_fill(0, 1, 1 ):
        case xo_field_right_bits_fill(1, 1, 1 ):
            return &group_30_instruction_data[ rldicr_index ] + get_rc_value( element, instruction );
        
        case xo_field_right_bits_fill(0, 1, 2 ):
        case xo_field_right_bits_fill(1, 1, 2 ):
            return &group_30_instruction_data[ rldic_index ] + get_rc_value( element, instruction );
        
        case xo_field_right_bits_fill(0, 1, 3 ):
        case xo_field_right_bits_fill(1, 1, 3 ):
            return &group_30_instruction_data[ rldimi_index ] + get_rc_value( element, instruction );
        
        case 8:
            return &group_30_instruction_data[ rldcl_index ] + get_rc_value( element, instruction );
        
        case 9:
            return &group_30_instruction_data[ rldcr_index ] + get_rc_value( element, instruction );
        };
    
    return (instruction_element *)NULL;
    }
    
    
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_31_instruction_data[] =
    {
    { "cmp     ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,      0,     _,    _,     _,     _,
                { end_cmd } },
    { "tw      ",            2,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,      4,     _,    _,     _,     _,
                { end_cmd } },
    { "subfc   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,      8,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "subfc.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,      8,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "mulhdu  ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,      9,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mulhdu. ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,      9,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "addc    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     10,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "addc.   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     10,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mulhwu  ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     11,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mulhwu. ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     11,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "isel    ",            1,                   1,            0x3E,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     15,     _,    _,     _,     _,
                { end_cmd } },
    { "tlbilx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     18,     _,    _,     _,     _,
                { end_cmd } },
    { "mfcr    ",            5,                   5,           0x7FE,         1,          0,           0,          0,          0,        0x1,          20,           0,          0,        //   31,     19,     _,    _,     0,     _,
                { end_cmd } },
    { "mfocrf  ",            5,                   5,           0x7FE,         1,          0,           0,          0,          0,        0x1,          20,           0,          0,        //   31,     19,     _,    _,     1,     _,
                { end_cmd } },
    { "lwarx   ",            3,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     20,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "ldx     ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     21,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "icbt    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     22,     _,    _,     _,     _,
                { end_cmd } },
    { "lwzx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     23,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "slw     ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     24,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "slw.    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     24,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "cntlzw  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     26,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "cntlzw. ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     26,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "sld     ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     27,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "sld.    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     27,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "and     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     28,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "and.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     28,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "ldepx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     29,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "lwepx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     31,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "cmpl    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     32,     _,    _,     _,     _,
                { end_cmd } },
    { "subf    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     40,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "subf.   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     40,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "ldux    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     53,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "dcbst   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     54,     _,    _,     _,     _,
                { end_cmd } },
    { "lwzux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     55,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "cntlzd  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     58,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "cntlzd. ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     58,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "andc    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     60,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "andc.   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     60,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "wait    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     62,     _,    _,     _,     _,
                { end_cmd } },
    { "dcbstep ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     63,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "td      ",            2,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     68,     _,    _,     _,     _,
                { end_cmd } },
    { "mulhd   ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     73,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mulhd.  ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     73,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mulhw   ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     75,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mulhw.  ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,     75,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mfmsr   ",            4,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     83,     _,    _,     _,     _,
                { end_cmd } },
    { "ldarx   ",            3,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     84,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "dcbf    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     86,     _,    _,     _,     _,
                { end_cmd } },
    { "lbzx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     87,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lbepx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,     95,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "neg     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    104,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "neg.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    104,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "lbzux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    119,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "popcntb ",            2,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    122,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "nor     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    124,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "nor.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    124,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dcbfep  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    127,     _,    _,     _,     _,
                { end_cmd } },
    { "wrtee   ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    131,     _,    _,     _,     _,
                { rS_cmd, end_cmd } },
    { "dcbtstls ",           1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    134,     _,    _,     _,     _,
                { end_cmd } },
    { "subfe   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    136,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "subfe.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    136,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "adde    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    138,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "adde.   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    138,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "mtcrf   ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,        0x1,          20,           0,          0,        //   31,    144,     _,    _,     0,     _,
                { end_cmd } },
    { "mtocrf  ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,        0x1,          20,           0,          0,        //   31,    144,     _,    _,     1,     _,
                { end_cmd } },
    { "mtmsr   ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    146,     _,    _,     _,     _,
                { end_cmd } },
    { "stdx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    149,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "stwcx.  ",            1,                   3,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    150,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "stwx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    151,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "prtyw   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    154,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "stdepx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    157,     _,    _,     _,     _,
                { rS_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "stwepx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    159,     _,    _,     _,     _,
                { rS_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "wrteei  ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    163,     _,    _,     _,     _,
                { end_cmd } },
    { "dcbtls  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    166,     _,    _,     _,     _,
                { end_cmd } },
    { "mfpmr   ",            4,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    167,     _,    _,     _,     _,
                { end_cmd } },
    { "mtmsrd  ",            4,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    178,     _,    _,     _,     _,
                { rS_cmd, end_cmd } },
    { "stdux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    181,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "stwux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    183,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "prtyd   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    186,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "subfze  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    200,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "subfze. ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    200,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addze   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    202,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addze.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    202,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "msgsnd  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    206,     _,    _,     _,     _,
                { rB_cmd, end_cmd } },
    { "stdcx.  ",            1,                   3,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    214,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd ,end_cmd } },
    { "stbx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    215,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "stbepx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    223,     _,    _,     _,     _,
                { rS_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "icblc   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    230,     _,    _,     _,     _,
                { end_cmd } },
    { "mtpmr   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    231,     _,    _,     _,     _,
                { end_cmd } },
    { "subfme  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    232,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "subfme. ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    232,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "mulld   ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    233,     0,    _,     _,     0,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mulld.  ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    233,     1,    _,     _,     0,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mulldo  ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    233,     0,    _,     _,     1,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mulldo. ",            2,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    233,     1,    _,     _,     1,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "addme   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    234,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addme.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    234,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "mullw   ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    235,     0,    _,     _,     0,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mullw.  ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    235,     1,    _,     _,     0,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mullwo  ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    235,     0,    _,     _,     1,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mullwo. ",            1,                   4,           0x3FE,         1,        0x1,           0,          0,          0,          0,           0,         0x1,         10,        //   31,    235,     1,    _,     _,     1,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "msgclr  ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    238,     _,    _,     _,     _,
                { rB_cmd, end_cmd } },
    { "dcbtst  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    246,     _,    _,     _,     _,
                { end_cmd } },
    { "stbux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    247,     _,    _,     _,     _,
                { rS_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "bpermd  ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    252,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dcbtstep ",           1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    255,     _,    _,     _,     _,
                { end_cmd } },
    { "add     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    266,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "add.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    266,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "ehpriv  ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    270,     _,    _,     _,     _,
                { end_cmd } },
    { "dcbt    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    278,     _,    _,     _,     _,
                { end_cmd } },
    { "lhzx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    279,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "eqv     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    284,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "eqv.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    284,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "lhepx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    287,     _,    _,     _,     _,
                { end_cmd } },
    { "lhzux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    311,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "xor     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    316,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "xor.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    316,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dcbtep  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    319,     _,    _,     _,     _,
                { end_cmd } },
    { "mfspr   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    339,     _,    _,     _,     _,
                { end_cmd } },
    { "lwax    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    341,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lhax    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    343,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "mftb    ",            4,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    371,     _,    _,     _,     _,
                { end_cmd } },
    { "lwaux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    373,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lhaux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    375,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "popcntw ",            2,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    378,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "dcblc   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    390,     _,    _,     _,     _,
                { end_cmd } },
    { "sthx    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    407,     _,    _,     _,     _,
                { end_cmd } },
    { "orc     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    412,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "orc.    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    412,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "sradi   ",            1,                   1,           0x7FC,         2,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    413,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "sradi.  ",            1,                   1,           0x7FC,         2,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    413,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "sthepx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    415,     _,    _,     _,     _,
                { end_cmd } },
    { "sthux   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    439,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "or      ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    444,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "or.     ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    444,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "divdu   ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    457,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divdu.  ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    457,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divwu   ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    459,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divwu.  ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    459,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "mtspr   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    467,     _,    _,     _,     _,
                { end_cmd } },
    { "dcbi    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    470,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "nand    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    476,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "nand.   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    476,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dsn     ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    483,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd ,end_cmd } },
    { "icbtls  ",            1,                   3,           0x7FE,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    486,     _,    _,     _,     _,
                { end_cmd } },
    { "divd    ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    489,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "divd.   ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    489,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "divw    ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    491,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divw.   ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    491,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "popcntd ",            2,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    506,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "cmpb    ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    508,     _,    _,     _,     _,
                { end_cmd } },
    { "mcrxr   ",            1,                   1,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    512,     _,    _,     _,     _,
                { end_cmd } },
    { "lbdx    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    515,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "subfco  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    520,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "subfco. ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    520,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "addco   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    522,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "addco.  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    522,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "ldbrx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    532,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lwbrx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    534,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lfsx    ",            1,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    535,     _,    _,     _,     _,
                { end_cmd } },
    { "srw     ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    536,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "srw.    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    536,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "srd     ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    539,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "srd.    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    539,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "lhdx    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    547,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "subfo   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    552,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "subfo.  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    552,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "tlbsync ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    566,     _,    _,     _,     _,
                { end_cmd } },
    { "lfsux   ",            1,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    567,     _,    _,     _,     _,
                { end_cmd } },
    { "lwdx    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    579,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "sync    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    598,     _,    _,     _,     _,
                { end_cmd } },
    { "lfdx    ",            1,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    599,     _,    _,     _,     _,
                { end_cmd } },
    { "lfdepx  ",            1,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    607,     _,    _,     _,     _,
                { end_cmd } },
    { "lddx    ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    611,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "nego    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    616,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "nego.   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    616,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "lfdux   ",            1,                   4,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    631,     _,    _,     _,     _,
                { end_cmd } },
    { "stbdx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    643,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "subfeo  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    648,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "subfeo. ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    648,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "addeo   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    650,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "addeo.  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    650,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "stdbrx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    660,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stwbrx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    662,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stfsx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    663,     _,    _,     _,     _,
                { end_cmd } },
    { "sthdx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    675,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "stfsux  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    695,     _,    _,     _,     _,
                { end_cmd } },
    { "stwdx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    707,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "subfzeo ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    712,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "subfzeo. ",           2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    712,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addzeo  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    714,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addzeo. ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    714,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "stfdx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    727,     _,    _,     _,     _,
                { end_cmd } },
    { "stfdepx ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    735,     _,    _,     _,     _,
                { end_cmd } },
    { "stddx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    739,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "subfmeo ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    744,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "subfmeo. ",           2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    744,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addmeo  ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    746,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "addmeo. ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    746,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd, end_cmd } },
    { "dcba    ",            1,                   3,           0x7FE,         1,          0,           0,          0x1,       21,          0,           0,           0,          0,        //   31,    758,     _,    0,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "dcbal   ",            1,                   3,           0x7FE,         1,          0,           0,          0x1,       21,          0,           0,           0,          0,        //   31,    758,     _,    1,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "stfdux  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    759,     _,    _,     _,     _,
                { end_cmd } },
    { "addo    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    778,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "addo.   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    778,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd ,end_cmd } },
    { "tlbivax ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    786,     _,    _,     _,     _,
                { end_cmd } },
    { "lhbrx   ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    790,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "sraw    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    792,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "sraw.   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    792,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "srad    ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    794,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "srad.   ",            2,                   2,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    794,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "lfddx   ",            0,                   0,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    803,     _,    _,     _,     _,
                { end_cmd } },
    { "srawi   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    824,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "srawi.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    824,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "mbar    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    854,     _,    _,     _,     _,
                { end_cmd } },
    { "tlbsx   ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    914,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "sthbrx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    918,     _,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "extsh   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    922,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "extsh.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    922,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "stfddx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    931,     _,    _,     _,     _,
                { end_cmd } },
    { "tlbre   ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    946,     _,    _,     _,     _,
                { end_cmd } },
    { "extsb   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    954,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "extsb.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    954,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "divduo  ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    969,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divduo. ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    969,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divwuo  ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    971,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divwuo. ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    971,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "tlbwe   ",            4,                   2,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    978,     _,    _,     _,     _,
                { end_cmd } },
    { "icbi    ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    982,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "stfiwx  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    983,     _,    _,     _,     _,
                { end_cmd } },
    { "extsw   ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    986,     0,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "extsw.  ",            1,                   1,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,    986,     1,    _,     _,     _,
                { rA_cmd, comma_cmd, rS_cmd, end_cmd } },
    { "icbiep  ",            1,                   3,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   31,    991,     _,    _,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "divdo   ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,   1001,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divdo.  ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,   1001,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divwo   ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,   1003,     0,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "divwo.  ",            4,                   4,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   31,   1003,     1,    _,     _,     _,
                { rD_cmd, comma_cmd, rA_cmd ,comma_cmd, rB_cmd, end_cmd } },
    { "dcbz    ",            1,                   3,           0x7FE,         1,          0,           0,          0x1,       21,          0,           0,           0,          0,        //   31,   1014,     _,    0,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dcbzl   ",            1,                   3,           0x7FE,         1,          0,           0,          0x1,       21,          0,           0,           0,          0,        //   31,   1014,     _,    1,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dcbzep  ",            1,                   3,           0x7FE,         1,          0,           0,          0x1,       21,          0,           0,           0,          0,        //   31,   1023,     _,    0,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } },
    { "dcbzlep ",            1,                   3,           0x7FE,         1,          0,           0,          0x1,       21,          0,           0,           0,          0,        //   31,   1023,     _,    1,     _,     _,
                { rA_cmd, comma_cmd, rB_cmd, end_cmd } }
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_group_31_instruction_element
//
///////////////////////////////////////////////////////////////////////////////

inline instruction_element *
lookup_group_31_instruction_element( instruction_element * element,
                                     uint32_t              instruction )
    {    
    uint32_t instruction_xo = get_xo_value( element, instruction );

    switch( instruction_xo )
        {
        case 0:
            return &group_31_instruction_data[ cmp_index ];

        case 4:
            return &group_31_instruction_data[ tw_index ];

        case 8:
            return &group_31_instruction_data[ subfc_index ] + get_rc_value( (&group_31_instruction_data[ subfc_index ]), instruction );

        case xo_field_left_bits_fill(0, 9, 9 ):
        case xo_field_left_bits_fill(1, 9, 9 ):
            return &group_31_instruction_data[ mulhdu_index ] + get_rc_value( (&group_31_instruction_data[ mulhdu_index ]), instruction );

        case 10:
            return &group_31_instruction_data[ addc_index ] + get_rc_value( (&group_31_instruction_data[ addc_index ]), instruction );

        case xo_field_left_bits_fill(0, 9, 11 ):
        case xo_field_left_bits_fill(1, 9, 11 ):
            return &group_31_instruction_data[ mulhwu_index ] + get_rc_value( (&group_31_instruction_data[ mulhwu_index ]), instruction );

        case 15:
        case xo_field_left_bits_fill( 1, 5, 15 ): case xo_field_left_bits_fill( 2, 5, 15 ): case xo_field_left_bits_fill( 3, 5, 15 ):
        case xo_field_left_bits_fill( 4, 5, 15 ): case xo_field_left_bits_fill( 5, 5, 15 ): case xo_field_left_bits_fill( 6, 5, 15 ):
        case xo_field_left_bits_fill( 7, 5, 15 ): case xo_field_left_bits_fill( 8, 5, 15 ): case xo_field_left_bits_fill( 9, 5, 15 ):
        case xo_field_left_bits_fill(10, 5, 15 ): case xo_field_left_bits_fill(11, 5, 15 ): case xo_field_left_bits_fill(12, 5, 15 ):
        case xo_field_left_bits_fill(13, 5, 15 ): case xo_field_left_bits_fill(14, 5, 15 ): case xo_field_left_bits_fill(15, 5, 15 ):
        case xo_field_left_bits_fill(16, 5, 15 ): case xo_field_left_bits_fill(17, 5, 15 ): case xo_field_left_bits_fill(18, 5, 15 ):
        case xo_field_left_bits_fill(19, 5, 15 ): case xo_field_left_bits_fill(20, 5, 15 ): case xo_field_left_bits_fill(21, 5, 15 ):
        case xo_field_left_bits_fill(22, 5, 15 ): case xo_field_left_bits_fill(23, 5, 15 ): case xo_field_left_bits_fill(24, 5, 15 ):
        case xo_field_left_bits_fill(25, 5, 15 ): case xo_field_left_bits_fill(26, 5, 15 ): case xo_field_left_bits_fill(27, 5, 15 ):
        case xo_field_left_bits_fill(28, 5, 15 ): case xo_field_left_bits_fill(29, 5, 15 ): case xo_field_left_bits_fill(30, 5, 15 ):
        case xo_field_left_bits_fill(31, 5, 15 ):
            return &group_31_instruction_data[ isel_index ];

        case 18:
            return &group_31_instruction_data[ tlbilx_index ];

        case 19:
            return &group_31_instruction_data[ mfcr_index ] + get_xfx_value( (&group_31_instruction_data[ mfcr_index ]), instruction );

        case 20:
            return &group_31_instruction_data[ lwarx_index ];

        case 21:
            return &group_31_instruction_data[ ldx_index ];

        case 22:
            return &group_31_instruction_data[ icbt_index ];

        case 23:
            return &group_31_instruction_data[ lwzx_index ];

        case 24:
            return &group_31_instruction_data[ slw_index ] + get_rc_value( (&group_31_instruction_data[ slw_index ]), instruction );

        case 26:
            return &group_31_instruction_data[ cntlzw_index ] + get_rc_value( (&group_31_instruction_data[ cntlzw_index ]), instruction );

        case 27:
            return &group_31_instruction_data[ sld_index ] + get_rc_value( (&group_31_instruction_data[ sld_index ]), instruction );

        case 28:
            return &group_31_instruction_data[ and_index ] + get_rc_value( (&group_31_instruction_data[ and_index ]), instruction );

        case 29:
            return &group_31_instruction_data[ ldepx_index ];

        case 31:
            return &group_31_instruction_data[ lwepx_index ];

        case 32:
            return &group_31_instruction_data[ cmpl_index ];

        case 40:
            return &group_31_instruction_data[ subf_index ] + get_rc_value( (&group_31_instruction_data[ subf_index ]), instruction );

        case 53:
            return &group_31_instruction_data[ ldux_index ];

        case 54:
            return &group_31_instruction_data[ dcbst_index ];

        case 55:
            return &group_31_instruction_data[ lwzux_index ];

        case 58:
            return &group_31_instruction_data[ cntlzd_index ] + get_rc_value( (&group_31_instruction_data[ cntlzd_index ]), instruction );

        case 60:
            return &group_31_instruction_data[ andc_index ] + get_rc_value( (&group_31_instruction_data[ andc_index ]), instruction );

        case 62:
            return &group_31_instruction_data[ wait_index ];

        case 63:
            return &group_31_instruction_data[ dcbstep_index ];

        case 68:
            return &group_31_instruction_data[ td_index ];

        case xo_field_left_bits_fill(0, 9, 73 ):
        case xo_field_left_bits_fill(1, 9, 73 ):
            return &group_31_instruction_data[ mulhd_index ] + get_rc_value( (&group_31_instruction_data[ mulhd_index ]), instruction );

        case xo_field_left_bits_fill(0, 9, 75 ):
        case xo_field_left_bits_fill(1, 9, 75 ):
            return &group_31_instruction_data[ mulhw_index ] + get_rc_value( (&group_31_instruction_data[ mulhw_index ]), instruction );

        case 83:
            return &group_31_instruction_data[ mfmsr_index ];

        case 84:
            return &group_31_instruction_data[ ldarx_index ];

        case 86:
            return &group_31_instruction_data[ dcbf_index ];

        case 87:
            return &group_31_instruction_data[ lbzx_index ];

        case 95:
            return &group_31_instruction_data[ lbepx_index ];

        case 104:
            return &group_31_instruction_data[ neg_index ] + get_rc_value( (&group_31_instruction_data[ neg_index ]), instruction );

        case 119:
            return &group_31_instruction_data[ lbzux_index ];

        case 122:
            return &group_31_instruction_data[ popcntb_index ];

        case 124:
            return &group_31_instruction_data[ nor_index ] + get_rc_value( (&group_31_instruction_data[ nor_index ]), instruction );

        case 127:
            return &group_31_instruction_data[ dcbfep_index ];

        case 131:
            return &group_31_instruction_data[ wrtee_index ];

        case 134:
            return &group_31_instruction_data[ dcbtstls_index ];

        case 136:
            return &group_31_instruction_data[ subfe_index ] + get_rc_value( (&group_31_instruction_data[ subfe_index ]), instruction );

        case 138:
            return &group_31_instruction_data[ adde_index ] + get_rc_value( (&group_31_instruction_data[ adde_index ]), instruction );

        case 144:
            return &group_31_instruction_data[ mtcrf_index ] + get_xfx_value( (&group_31_instruction_data[ mtcrf_index ]), instruction );

        case 146:
            return &group_31_instruction_data[ mtmsr_index ];

        case 149:
            return &group_31_instruction_data[ stdx_index ];

        case 150:
            return &group_31_instruction_data[ stwcx_dot_index ];

        case 151:
            return &group_31_instruction_data[ stwx_index ];

        case 154:
            return &group_31_instruction_data[ prtyw_index ];

        case 157:
            return &group_31_instruction_data[ stdepx_index ];

        case 159:
            return &group_31_instruction_data[ stwepx_index ];

        case 163:
            return &group_31_instruction_data[ wrteei_index ];

        case 166:
            return &group_31_instruction_data[ dcbtls_index ];

        case 167:
            return &group_31_instruction_data[ mfpmr_index ];

        case 178:
            return &group_31_instruction_data[ mtmsrd_index ];

        case 181:
            return &group_31_instruction_data[ stdux_index ];

        case 183:
            return &group_31_instruction_data[ stwux_index ];

        case 186:
            return &group_31_instruction_data[ prtyd_index ];

        case 200:
            return &group_31_instruction_data[ subfze_index ] + get_rc_value( (&group_31_instruction_data[ subfze_index ]), instruction );

        case 202:
            return &group_31_instruction_data[ addze_index ] + get_rc_value( (&group_31_instruction_data[ addze_index ]), instruction );

        case 206:
            return &group_31_instruction_data[ msgsnd_index ];

        case 214:
            return &group_31_instruction_data[ stdcx_dot_index ];

        case 215:
            return &group_31_instruction_data[ stbx_index ];

        case 223:
            return &group_31_instruction_data[ stbepx_index ];

        case 230:
            return &group_31_instruction_data[ icblc_index ];

        case 231:
            return &group_31_instruction_data[ mtpmr_index ];

        case 232:
            return &group_31_instruction_data[ subfme_index ] + get_rc_value( (&group_31_instruction_data[ subfme_index ]), instruction );

        case xo_field_left_bits_fill(0, 9, 233 ):
        case xo_field_left_bits_fill(1, 9, 233 ):
            return &group_31_instruction_data[ mulld_index ] + ( ( get_oe_value( (&group_31_instruction_data[ mulld_index ]), instruction ) << 1 )
                                                              | get_rc_value( (&group_31_instruction_data[ mulld_index ]), instruction ) );

        case 234:
            return &group_31_instruction_data[ addme_index ] + get_rc_value( (&group_31_instruction_data[ addme_index ]), instruction );

        case xo_field_left_bits_fill(0, 9, 235 ):
        case xo_field_left_bits_fill(1, 9, 235 ):
            return &group_31_instruction_data[ mullw_index ] + ( ( get_oe_value( (&group_31_instruction_data[ mullw_index ]), instruction ) << 1 )
                                                              | get_rc_value( (&group_31_instruction_data[ mullw_index ]), instruction ) );

        case 238:
            return &group_31_instruction_data[ msgclr_index ];

        case 246:
            return &group_31_instruction_data[ dcbtst_index ];

        case 247:
            return &group_31_instruction_data[ stbux_index ];

        case 252:
            return &group_31_instruction_data[ bpermd_index ];

        case 255:
            return &group_31_instruction_data[ dcbtstep_index ];

        case 266:
            return &group_31_instruction_data[ add_index ] + get_rc_value( (&group_31_instruction_data[ add_index ]), instruction );

        case 270:
            return &group_31_instruction_data[ ehpriv_index ];

        case 278:
            return &group_31_instruction_data[ dcbt_index ];

        case 279:
            return &group_31_instruction_data[ lhzx_index ];

        case 284:
            return &group_31_instruction_data[ eqv_index ] + get_rc_value( (&group_31_instruction_data[ eqv_index ]), instruction );

        case 287:
            return &group_31_instruction_data[ lhepx_index ];

        case 311:
            return &group_31_instruction_data[ lhzux_index ];

        case 316:
            return &group_31_instruction_data[ xor_index ] + get_rc_value( (&group_31_instruction_data[ xor_index ]), instruction );

        case 319:
            return &group_31_instruction_data[ dcbtep_index ];

        case 339:
            return &group_31_instruction_data[ mfspr_index ];

        case 341:
            return &group_31_instruction_data[ lwax_index ];

        case 343:
            return &group_31_instruction_data[ lhax_index ];

        case 371:
            return &group_31_instruction_data[ mftb_index ];

        case 373:
            return &group_31_instruction_data[ lwaux_index ];

        case 375:
            return &group_31_instruction_data[ lhaux_index ];

        case 378:
            return &group_31_instruction_data[ popcntw_index ];

        case 390:
            return &group_31_instruction_data[ dcblc_index ];

        case 407:
            return &group_31_instruction_data[ sthx_index ];

        case 412:
            return &group_31_instruction_data[ orc_index ] + get_rc_value( (&group_31_instruction_data[ orc_index ]), instruction );

        case xo_field_right_bits_fill(0, 1, 413 ):
        case xo_field_right_bits_fill(1, 1, 413 ):
            return &group_31_instruction_data[ sradi_index ] + get_rc_value( (&group_31_instruction_data[ sradi_index ]), instruction );

        case 415:
            return &group_31_instruction_data[ sthepx_index ];

        case 439:
            return &group_31_instruction_data[ sthux_index ];

        case 444:
            if( get_rS_value( instruction ) == get_rB_value( instruction ) )
                return &simplified_mnemonics_instruction_data[ mr_index ];
            else
                return &group_31_instruction_data[ or_index ] + get_rc_value( (&group_31_instruction_data[ or_index ]), instruction );

        case 457:
            return &group_31_instruction_data[ divdu_index ] + get_rc_value( (&group_31_instruction_data[ divdu_index ]), instruction );

        case 459:
            return &group_31_instruction_data[ divwu_index ] + get_rc_value( (&group_31_instruction_data[ divwu_index ]), instruction );

        case 467:
            return &group_31_instruction_data[ mtspr_index ];

        case 470:
            return &group_31_instruction_data[ dcbi_index ];

        case 476:
            return &group_31_instruction_data[ nand_index ] + get_rc_value( (&group_31_instruction_data[ nand_index ]), instruction );

        case 483:
            return &group_31_instruction_data[ dsn_index ];

        case 486:
            return &group_31_instruction_data[ icbtls_index ];

        case 489:
            return &group_31_instruction_data[ divd_index ] + get_rc_value( (&group_31_instruction_data[ divd_index ]), instruction );

        case 491:
            return &group_31_instruction_data[ divw_index ] + get_rc_value( (&group_31_instruction_data[ divw_index ]), instruction );

        case 506:
            return &group_31_instruction_data[ popcntd_index ];

        case 508:
            return &group_31_instruction_data[ cmpb_index ];

        case 512:
            return &group_31_instruction_data[ mcrxr_index ];

        case 515:
            return &group_31_instruction_data[ lbdx_index ];

        case 520:
            return &group_31_instruction_data[ subfco_index ] + get_rc_value( (&group_31_instruction_data[ subfco_index ]), instruction );

        case 522:
            return &group_31_instruction_data[ addco_index ] + get_rc_value( (&group_31_instruction_data[ addco_index ]), instruction );

        case 532:
            return &group_31_instruction_data[ ldbrx_index ];

        case 534:
            return &group_31_instruction_data[ lwbrx_index ];

        case 535:
            return &group_31_instruction_data[ lfsx_index ];

        case 536:
            return &group_31_instruction_data[ srw_index ] + get_rc_value( (&group_31_instruction_data[ srw_index ]), instruction );

        case 539:
            return &group_31_instruction_data[ srd_index ] + get_rc_value( (&group_31_instruction_data[ srd_index ]), instruction );

        case 547:
            return &group_31_instruction_data[ lhdx_index ];

        case 552:
            return &group_31_instruction_data[ subfo_index ] + get_rc_value( (&group_31_instruction_data[ subfo_index ]), instruction );

        case 566:
            return &group_31_instruction_data[ tlbsync_index ];

        case 567:
            return &group_31_instruction_data[ lfsux_index ];

        case 579:
            return &group_31_instruction_data[ lwdx_index ];

        case 598:
            return &group_31_instruction_data[ sync_index ];

        case 599:
            return &group_31_instruction_data[ lfdx_index ];

        case 607:
            return &group_31_instruction_data[ lfdepx_index ];

        case 611:
            return &group_31_instruction_data[ lddx_index ];

        case 616:
            return &group_31_instruction_data[ nego_index ] + get_rc_value( (&group_31_instruction_data[ nego_index ]), instruction );

        case 631:
            return &group_31_instruction_data[ lfdux_index ];

        case 643:
            return &group_31_instruction_data[ stbdx_index ];

        case 648:
            return &group_31_instruction_data[ subfeo_index ] + get_rc_value( (&group_31_instruction_data[ subfeo_index ]), instruction );

        case 650:
            return &group_31_instruction_data[ addeo_index ] + get_rc_value( (&group_31_instruction_data[ addeo_index ]), instruction );

        case 660:
            return &group_31_instruction_data[ stdbrx_index ];

        case 662:
            return &group_31_instruction_data[ stwbrx_index ];

        case 663:
            return &group_31_instruction_data[ stfsx_index ];

        case 675:
            return &group_31_instruction_data[ sthdx_index ];

        case 695:
            return &group_31_instruction_data[ stfsux_index ];

        case 707:
            return &group_31_instruction_data[ stwdx_index ];

        case 712:
            return &group_31_instruction_data[ subfzeo_index ] + get_rc_value( (&group_31_instruction_data[ subfzeo_index ]), instruction );

        case 714:
            return &group_31_instruction_data[ addzeo_index ] + get_rc_value( (&group_31_instruction_data[ addzeo_index ]), instruction );

        case 727:
            return &group_31_instruction_data[ stfdx_index ];

        case 735:
            return &group_31_instruction_data[ stfdepx_index ];

        case 739:
            return &group_31_instruction_data[ stddx_index ];

        case 744:
            return &group_31_instruction_data[ subfmeo_index ] + get_rc_value( (&group_31_instruction_data[ subfmeo_index ]), instruction );

        case 746:
            return &group_31_instruction_data[ addmeo_index ] + get_rc_value( (&group_31_instruction_data[ addmeo_index ]), instruction );

        case 758:
            return &group_31_instruction_data[ dcba_index ] + get_l_value( (&group_31_instruction_data[ dcba_index ]), instruction );

        case 759:
            return &group_31_instruction_data[ stfdux_index ] + get_rc_value( (&group_31_instruction_data[ stfdux_index ]), instruction );

        case 778:
            return &group_31_instruction_data[ addo_index ] + get_rc_value( (&group_31_instruction_data[ addo_index ]), instruction );

        case 786:
            return &group_31_instruction_data[ tlbivax_index ] + get_rc_value( (&group_31_instruction_data[ tlbivax_index ]), instruction );

        case 790:
            return &group_31_instruction_data[ lhbrx_index ] + get_rc_value( (&group_31_instruction_data[ lhbrx_index ]), instruction );

        case 792:
            return &group_31_instruction_data[ sraw_index ] + get_rc_value( (&group_31_instruction_data[ sraw_index ]), instruction );

        case 794:
            return &group_31_instruction_data[ srad_index ] + get_rc_value( (&group_31_instruction_data[ srad_index ]), instruction );

        case 803:
            return &group_31_instruction_data[ lfddx_index ];

        case 824:
            return &group_31_instruction_data[ srawi_index ] + get_rc_value( (&group_31_instruction_data[ srawi_index ]), instruction );

        case 854:
            return &group_31_instruction_data[ mbar_index ];

        case 914:
            return &group_31_instruction_data[ tlbsx_index ];

        case 918:
            return &group_31_instruction_data[ sthbrx_index ];

        case 922:
            return &group_31_instruction_data[ extsh_index ] + get_rc_value( (&group_31_instruction_data[ extsh_index ]), instruction );

        case 931:
            return &group_31_instruction_data[ stfddx_index ];

        case 946:
            return &group_31_instruction_data[ tlbre_index ];

        case 954:
            return &group_31_instruction_data[ extsb_index ] + get_rc_value( (&group_31_instruction_data[ extsb_index ]), instruction );

        case 969:
            return &group_31_instruction_data[ divduo_index ] + get_rc_value( (&group_31_instruction_data[ divduo_index ]), instruction );

        case 971:
            return &group_31_instruction_data[ divwuo_index ] + get_rc_value( (&group_31_instruction_data[ divwuo_index ]), instruction );

        case 978:
            return &group_31_instruction_data[ tlbwe_index ];

        case 982:
            return &group_31_instruction_data[ icbi_index ];

        case 983:
            return &group_31_instruction_data[ stfiwx_index ];

        case 986:
            return &group_31_instruction_data[ extsw_index ] + get_rc_value( (&group_31_instruction_data[ extsw_index ]), instruction );

        case 991:
            return &group_31_instruction_data[ icbiep_index ];

        case 1001:
            return &group_31_instruction_data[ divdo_index ] + get_rc_value( (&group_31_instruction_data[ divdo_index ]), instruction );

        case 1003:
            return &group_31_instruction_data[ divwo_index ] + get_rc_value( (&group_31_instruction_data[ divwo_index ]), instruction );

        case 1014:
            return &group_31_instruction_data[ dcbz_index ] + get_l_value( (&group_31_instruction_data[ dcbz_index ]), instruction );

        case 1023:
            return &group_31_instruction_data[ dcbzep_index ] + get_l_value( (&group_31_instruction_data[ dcbzep_index ]), instruction );
        };

    return (instruction_element *)NULL;
    }

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_32_to_55_instruction_data[] =
    {
    { "lwz     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   32,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lwzu    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   33,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lbz     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   34,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lbzu    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   35,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stw     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   36,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stwu    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   37,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stb     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   38,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stbu    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   39,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lhz     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   40,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lhzu    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   41,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lha     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   42,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lhau    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   43,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "sth     ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   44,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "sthu    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   45,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lmw     ",            3,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   46,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stmw    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   47,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lfs     ",            1,                   4,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   48,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lfsu    ",            1,                   4,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   49,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lfd     ",            1,                   4,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   50,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lfdu    ",            1,                   4,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   51,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stfs    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   52,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stfsu   ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   53,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stfd    ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   54,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stfdu   ",            1,                   3,               0,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   55,      _,     _,    _,     _,     _,
                    { rD_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_58_instruction_data[] =
    {
    { "ld      ",            1,                   3,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   58,      0,     _,    _,     _,     _,   
                { rS_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "ldu     ",            1,                   3,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   58,      1,     _,    _,     _,     _,   
                { rS_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "lwa     ",            1,                   3,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   58,      2,     _,    _,     _,     _,  
                { rS_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_59_instruction_data[] =
    {
    { "fdivs   ",            2,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     18,     0,    _,     _,     _,
                    { end_cmd } },
    { "fdivs.  ",            2,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     18,     1,    _,     _,     _,
                    { end_cmd } },
    { "fsubs   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     20,     0,    _,     _,     _,
                    { end_cmd } },
    { "fsubs.  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     20,     1,    _,     _,     _,
                    { end_cmd } },
    { "fadds   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     21,     0,    _,     _,     _,
                    { end_cmd } },
    { "fadds.  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     21,     1,    _,     _,     _,
                    { end_cmd } },
    { "fres    ",            2,                   8,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     24,     0,    _,     _,     _,
                    { end_cmd } },
    { "fres.   ",            2,                   8,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     24,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmuls   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     25,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmuls.  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     25,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmsubs  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     28,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmsubs. ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     28,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmadds  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     29,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmadds. ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     29,     1,    _,     _,     _,
                    { end_cmd } },
    { "fnmsubs ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     30,     0,    _,     _,     _,
                    { end_cmd } },
    { "fnmsubs. ",           1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     30,     1,    _,     _,     _,
                    { end_cmd } },
    { "fnmadds ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     31,     0,    _,     _,     _,
                    { end_cmd } },
    { "fnmadds. ",           1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   59,     31,     1,    _,     _,     _,
                    { end_cmd } }
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_group_59_instruction_element
//
///////////////////////////////////////////////////////////////////////////////

inline instruction_element *
lookup_group_59_instruction_element( instruction_element * element,
                                     uint32_t              instruction )
    {    
    uint32_t instruction_xo = get_xo_value( element, instruction );

    switch( instruction_xo )
        {
        case 18:
            return &group_59_instruction_data[ fdivs_index   ] + get_rc_value( (&group_59_instruction_data[ fdivs_index   ]), instruction );

        case 20:
            return &group_59_instruction_data[ fsubs_index   ] + get_rc_value( (&group_59_instruction_data[ fsubs_index   ]), instruction );

        case 21:
            return &group_59_instruction_data[ fadds_index   ] + get_rc_value( (&group_59_instruction_data[ fadds_index   ]), instruction );

        case 24:
            return &group_59_instruction_data[ fres_index    ] + get_rc_value( (&group_59_instruction_data[ fres_index    ]), instruction );

        case 25:
            return &group_59_instruction_data[ fmuls_index   ] + get_rc_value( (&group_59_instruction_data[ fmuls_index   ]), instruction );

        case 28:
            return &group_59_instruction_data[ fmsubs_index  ] + get_rc_value( (&group_59_instruction_data[ fmsubs_index  ]), instruction );

        case 29:
            return &group_59_instruction_data[ fmadds_index  ] + get_rc_value( (&group_59_instruction_data[ fmadds_index  ]), instruction );

        case 30:
            return &group_59_instruction_data[ fnmsubs_index ] + get_rc_value( (&group_59_instruction_data[ fnmsubs_index ]), instruction );

        case 31:
            return &group_59_instruction_data[ fnmadds_index ] + get_rc_value( (&group_59_instruction_data[ fnmadds_index ]), instruction );
        };

    return (instruction_element *)NULL;
    }

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_62_instruction_data[] =
    {
    { "std     ",            1,                   3,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   62,      0,     _,    _,     _,     _,   
                    { rS_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } },
    { "stdu    ",            1,                   3,             0x3,         0,          0,           0,          0,          0,          0,           0,           0,          0,        //   62,      1,     _,    _,     _,     _,   
                    { rS_cmd, comma_cmd, rA_disp_indirect_cmd, end_cmd } }
    };

// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
// |  Mnemonic   |  Repeat Rate Cycles  | Latency Cycles  |  OX Mask  |  XO Shift  |  Rc Mask  |  Rc Shift  |  L Mask  |  L Shift  |  XFX Mask  |  XFX Shift  |  OE Mask  |  OE Shift |    |  Group  |  XO  |  Rc  |  L  |  XFX  |  OE  |
// +-------------+----------------------+-----------------+-----------+------------+-----------+------------+----------+-----------+------------+-------------+-----------+-----------+    +---------+------+------+-----+-------+------+
instruction_element group_63_instruction_data[] =
    {
    { "fcmpu   ",            1,                   7,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   63,      0,     _,    _,     _,     _,
                    { end_cmd } },
    { "frsp    ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     12,     0,    _,     _,     _,
                    { end_cmd } },
    { "frsp.   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     12,     1,    _,     _,     _,
                    { end_cmd } },
    { "fctiw   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     14,     0,    _,     _,     _,
                    { end_cmd } },
    { "fctiw.  ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     14,     1,    _,     _,     _,
                    { end_cmd } },
    { "fctiwz  ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     15,     0,    _,     _,     _,
                    { end_cmd } },
    { "fctiwz. ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     15,     1,    _,     _,     _,
                    { end_cmd } },
    { "fdiv    ",            2,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     18,     0,    _,     _,     _,
                    { end_cmd } },
    { "fdiv.   ",            2,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     18,     1,    _,     _,     _,
                    { end_cmd } },
    { "fsub    ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     20,     0,    _,     _,     _,
                    { end_cmd } },
    { "fsub.   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     20,     1,    _,     _,     _,
                    { end_cmd } },
    { "fadd    ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     21,     0,    _,     _,     _,
                    { end_cmd } },
    { "fadd.   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     21,     1,    _,     _,     _,
                    { end_cmd } },
    { "fsel    ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     23,     0,    _,     _,     _,
                    { end_cmd } },
    { "fsel.   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     23,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmul    ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     25,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmul.   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     25,     1,    _,     _,     _,
                    { end_cmd } },
    { "frsqrte ",            2,                   8,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     26,     0,    _,     _,     _,
                    { end_cmd } },
    { "frsqrte. ",           2,                   8,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     26,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmsub   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     28,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmsub.  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     28,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmadd   ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     29,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmadd.  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     29,     1,    _,     _,     _,
                    { end_cmd } },
    { "fnmsub  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     30,     0,    _,     _,     _,
                    { end_cmd } },
    { "fnmsub. ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     30,     1,    _,     _,     _,
                    { end_cmd } },
    { "fnmadd  ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     31,     0,    _,     _,     _,
                    { end_cmd } },
    { "fnmadd. ",            1,                   7,            0x1F,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     31,     1,    _,     _,     _,
                    { end_cmd } },
    { "fcmpo   ",            1,                   7,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   63,     32,     _,    _,     _,     _,
                    { end_cmd } },
    { "mtfsb1  ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     38,     0,    _,     _,     _,
                    { end_cmd } },
    { "mtfsb1. ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     38,     1,    _,     _,     _,
                    { end_cmd } },
    { "fneg    ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     40,     0,    _,     _,     _,
                    { end_cmd } },
    { "fneg.   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     40,     1,    _,     _,     _,
                    { end_cmd } },
    { "mcrfs   ",            1,                   7,           0x7FE,         1,          0,           0,          0,          0,          0,           0,           0,          0,        //   63,     64,     _,    _,     _,     _,
                    { end_cmd } },
    { "mtfsb0  ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     70,     0,    _,     _,     _,
                    { end_cmd } },
    { "mtfsb0. ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     70,     1,    _,     _,     _,
                    { end_cmd } },
    { "fmr     ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     72,     0,    _,     _,     _,
                    { end_cmd } },
    { "fmr.    ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,     72,     1,    _,     _,     _,
                    { end_cmd } },
    { "mtfsfi  ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    134,     0,    _,     _,     _,
                    { end_cmd } },
    { "mtfsfi. ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    134,     1,    _,     _,     _,
                    { end_cmd } },
    { "fnabs   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    136,     0,    _,     _,     _,
                    { end_cmd } },
    { "fnabs.  ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    136,     1,    _,     _,     _,
                    { end_cmd } },
    { "fabs    ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    264,     0,    _,     _,     _,
                    { end_cmd } },
    { "fabs.   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    264,     1,    _,     _,     _,
                    { end_cmd } },
    { "mffs    ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    583,     0,    _,     _,     _,
                    { end_cmd } },
    { "mffs.   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    583,     1,    _,     _,     _,
                    { end_cmd } },
    { "mtfsf   ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    711,     0,    _,     _,     _,
                    { end_cmd } },
    { "mtfsf.  ",            7,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    711,     1,    _,     _,     _,
                    { end_cmd } },
    { "fctid   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    814,     0,    _,     _,     _,
                    { end_cmd } },
    { "fctid.  ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    814,     1,    _,     _,     _,
                    { end_cmd } },
    { "fctidz  ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    815,     0,    _,     _,     _,
                    { end_cmd } },
    { "fctidz. ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    815,     1,    _,     _,     _,
                    { end_cmd } },
    { "fcfid   ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    846,     0,    _,     _,     _,
                    { end_cmd } },
    { "fcfid.  ",            1,                   7,           0x7FE,         1,        0x1,           0,          0,          0,          0,           0,           0,          0,        //   63,    846,     1,    _,     _,     _,
                    { end_cmd } }
    };


///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_group_63_instruction_element
//
///////////////////////////////////////////////////////////////////////////////

inline instruction_element *
lookup_group_63_instruction_element( instruction_element * element,
                                     uint32_t              instruction )
    {    
    uint32_t instruction_xo = get_xo_value( element, instruction );

    switch( instruction_xo )
        {
        case 0:  
            return &group_63_instruction_data[ fcmpu_index   ];
        
        case 12: 
            return &group_63_instruction_data[ frsp_index    ] + get_rc_value( (&group_63_instruction_data[ frsp_index    ]), instruction );
        
        case 14: 
            return &group_63_instruction_data[ fctiw_index   ] + get_rc_value( (&group_63_instruction_data[ fctiw_index   ]), instruction );
        
        case 15: 
            return &group_63_instruction_data[ fctiwz_index  ] + get_rc_value( (&group_63_instruction_data[ fctiwz_index  ]), instruction );
        
        case 18: 
        case xo_field_left_bits_fill( 1, 5, 18 ): case xo_field_left_bits_fill( 2, 5, 18 ): case xo_field_left_bits_fill( 3, 5, 18 ):
        case xo_field_left_bits_fill( 4, 5, 18 ): case xo_field_left_bits_fill( 5, 5, 18 ): case xo_field_left_bits_fill( 6, 5, 18 ):
        case xo_field_left_bits_fill( 7, 5, 18 ): case xo_field_left_bits_fill( 8, 5, 18 ): case xo_field_left_bits_fill( 9, 5, 18 ):
        case xo_field_left_bits_fill(10, 5, 18 ): case xo_field_left_bits_fill(11, 5, 18 ): case xo_field_left_bits_fill(12, 5, 18 ):
        case xo_field_left_bits_fill(13, 5, 18 ): case xo_field_left_bits_fill(14, 5, 18 ): case xo_field_left_bits_fill(15, 5, 18 ):
        case xo_field_left_bits_fill(16, 5, 18 ): case xo_field_left_bits_fill(17, 5, 18 ): case xo_field_left_bits_fill(18, 5, 18 ):
        case xo_field_left_bits_fill(19, 5, 18 ): case xo_field_left_bits_fill(20, 5, 18 ): case xo_field_left_bits_fill(21, 5, 18 ):
        case xo_field_left_bits_fill(22, 5, 18 ): case xo_field_left_bits_fill(23, 5, 18 ): case xo_field_left_bits_fill(24, 5, 18 ):
        case xo_field_left_bits_fill(25, 5, 18 ): case xo_field_left_bits_fill(26, 5, 18 ): case xo_field_left_bits_fill(27, 5, 18 ):
        case xo_field_left_bits_fill(28, 5, 18 ): case xo_field_left_bits_fill(29, 5, 18 ): case xo_field_left_bits_fill(30, 5, 18 ):
        case xo_field_left_bits_fill(31, 5, 18 ):
            return &group_63_instruction_data[ fdiv_index    ] + get_rc_value( (&group_63_instruction_data[ fdiv_index    ]), instruction );
        
        case 20: 
        case xo_field_left_bits_fill( 1, 5, 20 ): case xo_field_left_bits_fill( 2, 5, 20 ): case xo_field_left_bits_fill( 3, 5, 20 ):
        case xo_field_left_bits_fill( 4, 5, 20 ): case xo_field_left_bits_fill( 5, 5, 20 ): case xo_field_left_bits_fill( 6, 5, 20 ):
        case xo_field_left_bits_fill( 7, 5, 20 ): case xo_field_left_bits_fill( 8, 5, 20 ): case xo_field_left_bits_fill( 9, 5, 20 ):
        case xo_field_left_bits_fill(10, 5, 20 ): case xo_field_left_bits_fill(11, 5, 20 ): case xo_field_left_bits_fill(12, 5, 20 ):
        case xo_field_left_bits_fill(13, 5, 20 ): case xo_field_left_bits_fill(14, 5, 20 ): case xo_field_left_bits_fill(15, 5, 20 ):
        case xo_field_left_bits_fill(16, 5, 20 ): case xo_field_left_bits_fill(17, 5, 20 ): case xo_field_left_bits_fill(18, 5, 20 ):
        case xo_field_left_bits_fill(19, 5, 20 ): case xo_field_left_bits_fill(20, 5, 20 ): case xo_field_left_bits_fill(21, 5, 20 ):
        case xo_field_left_bits_fill(22, 5, 20 ): case xo_field_left_bits_fill(23, 5, 20 ): case xo_field_left_bits_fill(24, 5, 20 ):
        case xo_field_left_bits_fill(25, 5, 20 ): case xo_field_left_bits_fill(26, 5, 20 ): case xo_field_left_bits_fill(27, 5, 20 ):
        case xo_field_left_bits_fill(28, 5, 20 ): case xo_field_left_bits_fill(29, 5, 20 ): case xo_field_left_bits_fill(30, 5, 20 ):
        case xo_field_left_bits_fill(31, 5, 20):
            return &group_63_instruction_data[ fsub_index    ] + get_rc_value( (&group_63_instruction_data[ fsub_index    ]), instruction );
        
        case 21: 
        case xo_field_left_bits_fill( 1, 5, 21 ): case xo_field_left_bits_fill( 2, 5, 21 ): case xo_field_left_bits_fill( 3, 5, 21 ):
        case xo_field_left_bits_fill( 4, 5, 21 ): case xo_field_left_bits_fill( 5, 5, 21 ): case xo_field_left_bits_fill( 6, 5, 21 ):
        case xo_field_left_bits_fill( 7, 5, 21 ): case xo_field_left_bits_fill( 8, 5, 21 ): case xo_field_left_bits_fill( 9, 5, 21 ):
        case xo_field_left_bits_fill(10, 5, 21 ): case xo_field_left_bits_fill(11, 5, 21 ): case xo_field_left_bits_fill(12, 5, 21 ):
        case xo_field_left_bits_fill(13, 5, 21 ): case xo_field_left_bits_fill(14, 5, 21 ): case xo_field_left_bits_fill(15, 5, 21 ):
        case xo_field_left_bits_fill(16, 5, 21 ): case xo_field_left_bits_fill(17, 5, 21 ): case xo_field_left_bits_fill(18, 5, 21 ):
        case xo_field_left_bits_fill(19, 5, 21 ): case xo_field_left_bits_fill(20, 5, 21 ): case xo_field_left_bits_fill(21, 5, 21 ):
        case xo_field_left_bits_fill(22, 5, 21 ): case xo_field_left_bits_fill(23, 5, 21 ): case xo_field_left_bits_fill(24, 5, 21 ):
        case xo_field_left_bits_fill(25, 5, 21 ): case xo_field_left_bits_fill(26, 5, 21 ): case xo_field_left_bits_fill(27, 5, 21 ):
        case xo_field_left_bits_fill(28, 5, 21 ): case xo_field_left_bits_fill(29, 5, 21 ): case xo_field_left_bits_fill(30, 5, 21 ):
        case xo_field_left_bits_fill(31, 5, 21 ):
            return &group_63_instruction_data[ fadd_index    ] + get_rc_value( (&group_63_instruction_data[ fadd_index    ]), instruction );
        
        case 23: 
        case xo_field_left_bits_fill( 1, 5, 23 ): case xo_field_left_bits_fill( 2, 5, 23 ): case xo_field_left_bits_fill( 3, 5, 23 ):
        case xo_field_left_bits_fill( 4, 5, 23 ): case xo_field_left_bits_fill( 5, 5, 23 ): case xo_field_left_bits_fill( 6, 5, 23 ):
        case xo_field_left_bits_fill( 7, 5, 23 ): case xo_field_left_bits_fill( 8, 5, 23 ): case xo_field_left_bits_fill( 9, 5, 23 ):
        case xo_field_left_bits_fill(10, 5, 23 ): case xo_field_left_bits_fill(11, 5, 23 ): case xo_field_left_bits_fill(12, 5, 23 ):
        case xo_field_left_bits_fill(13, 5, 23 ): case xo_field_left_bits_fill(14, 5, 23 ): case xo_field_left_bits_fill(15, 5, 23 ):
        case xo_field_left_bits_fill(16, 5, 23 ): case xo_field_left_bits_fill(17, 5, 23 ): case xo_field_left_bits_fill(18, 5, 23 ):
        case xo_field_left_bits_fill(19, 5, 23 ): case xo_field_left_bits_fill(20, 5, 23 ): case xo_field_left_bits_fill(21, 5, 23 ):
        case xo_field_left_bits_fill(22, 5, 23 ): case xo_field_left_bits_fill(23, 5, 23 ): case xo_field_left_bits_fill(24, 5, 23 ):
        case xo_field_left_bits_fill(25, 5, 23 ): case xo_field_left_bits_fill(26, 5, 23 ): case xo_field_left_bits_fill(27, 5, 23 ):
        case xo_field_left_bits_fill(28, 5, 23 ): case xo_field_left_bits_fill(29, 5, 23 ): case xo_field_left_bits_fill(30, 5, 23 ):
        case xo_field_left_bits_fill(31, 5, 23 ):
            return &group_63_instruction_data[ fsel_index    ] + get_rc_value( (&group_63_instruction_data[ fsel_index    ]), instruction );
        
        case 25: 
        case xo_field_left_bits_fill( 1, 5, 25 ): case xo_field_left_bits_fill( 2, 5, 25 ): case xo_field_left_bits_fill( 3, 5, 25 ):
        case xo_field_left_bits_fill( 4, 5, 25 ): case xo_field_left_bits_fill( 5, 5, 25 ): case xo_field_left_bits_fill( 6, 5, 25 ):
        case xo_field_left_bits_fill( 7, 5, 25 ): case xo_field_left_bits_fill( 8, 5, 25 ): case xo_field_left_bits_fill( 9, 5, 25 ):
        case xo_field_left_bits_fill(10, 5, 25 ): case xo_field_left_bits_fill(11, 5, 25 ): case xo_field_left_bits_fill(12, 5, 25 ):
        case xo_field_left_bits_fill(13, 5, 25 ): case xo_field_left_bits_fill(14, 5, 25 ): case xo_field_left_bits_fill(15, 5, 25 ):
        case xo_field_left_bits_fill(16, 5, 25 ): case xo_field_left_bits_fill(17, 5, 25 ): case xo_field_left_bits_fill(18, 5, 25 ):
        case xo_field_left_bits_fill(19, 5, 25 ): case xo_field_left_bits_fill(20, 5, 25 ): case xo_field_left_bits_fill(21, 5, 25 ):
        case xo_field_left_bits_fill(22, 5, 25 ): case xo_field_left_bits_fill(23, 5, 25 ): case xo_field_left_bits_fill(24, 5, 25 ):
        case xo_field_left_bits_fill(25, 5, 25 ): case xo_field_left_bits_fill(26, 5, 25 ): case xo_field_left_bits_fill(27, 5, 25 ):
        case xo_field_left_bits_fill(28, 5, 25 ): case xo_field_left_bits_fill(29, 5, 25 ): case xo_field_left_bits_fill(30, 5, 25 ):
        case xo_field_left_bits_fill(31, 5, 25 ):
            return &group_63_instruction_data[ fmul_index    ] + get_rc_value( (&group_63_instruction_data[ fmul_index    ]), instruction );
        
        case 26: 
        case xo_field_left_bits_fill( 1, 5, 26 ): case xo_field_left_bits_fill( 2, 5, 26 ): case xo_field_left_bits_fill( 3, 5, 26 ):
        case xo_field_left_bits_fill( 4, 5, 26 ): case xo_field_left_bits_fill( 5, 5, 26 ): case xo_field_left_bits_fill( 6, 5, 26 ):
        case xo_field_left_bits_fill( 7, 5, 26 ): case xo_field_left_bits_fill( 8, 5, 26 ): case xo_field_left_bits_fill( 9, 5, 26 ):
        case xo_field_left_bits_fill(10, 5, 26 ): case xo_field_left_bits_fill(11, 5, 26 ): case xo_field_left_bits_fill(12, 5, 26 ):
        case xo_field_left_bits_fill(13, 5, 26 ): case xo_field_left_bits_fill(14, 5, 26 ): case xo_field_left_bits_fill(15, 5, 26 ):
        case xo_field_left_bits_fill(16, 5, 26 ): case xo_field_left_bits_fill(17, 5, 26 ): case xo_field_left_bits_fill(18, 5, 26 ):
        case xo_field_left_bits_fill(19, 5, 26 ): case xo_field_left_bits_fill(20, 5, 26 ): case xo_field_left_bits_fill(21, 5, 26 ):
        case xo_field_left_bits_fill(22, 5, 26 ): case xo_field_left_bits_fill(23, 5, 26 ): case xo_field_left_bits_fill(24, 5, 26 ):
        case xo_field_left_bits_fill(25, 5, 26 ): case xo_field_left_bits_fill(26, 5, 26 ): case xo_field_left_bits_fill(27, 5, 26 ):
        case xo_field_left_bits_fill(28, 5, 26 ): case xo_field_left_bits_fill(29, 5, 26 ): case xo_field_left_bits_fill(30, 5, 2618 ):
        case xo_field_left_bits_fill(31, 5, 26 ):
            return &group_63_instruction_data[ frsqrte_index ] + get_rc_value( (&group_63_instruction_data[ frsqrte_index ]), instruction );
        
        case 28: 
        case xo_field_left_bits_fill( 1, 5, 28 ): case xo_field_left_bits_fill( 2, 5, 28 ): case xo_field_left_bits_fill( 3, 5, 28 ):
        case xo_field_left_bits_fill( 4, 5, 28 ): case xo_field_left_bits_fill( 5, 5, 28 ): case xo_field_left_bits_fill( 6, 5, 28 ):
        case xo_field_left_bits_fill( 7, 5, 28 ): case xo_field_left_bits_fill( 8, 5, 28 ): case xo_field_left_bits_fill( 9, 5, 28 ):
        case xo_field_left_bits_fill(10, 5, 28 ): case xo_field_left_bits_fill(11, 5, 28 ): case xo_field_left_bits_fill(12, 5, 28 ):
        case xo_field_left_bits_fill(13, 5, 28 ): case xo_field_left_bits_fill(14, 5, 28 ): case xo_field_left_bits_fill(15, 5, 28 ):
        case xo_field_left_bits_fill(16, 5, 28 ): case xo_field_left_bits_fill(17, 5, 28 ): case xo_field_left_bits_fill(18, 5, 28 ):
        case xo_field_left_bits_fill(19, 5, 28 ): case xo_field_left_bits_fill(20, 5, 28 ): case xo_field_left_bits_fill(21, 5, 28 ):
        case xo_field_left_bits_fill(22, 5, 28 ): case xo_field_left_bits_fill(23, 5, 28 ): case xo_field_left_bits_fill(24, 5, 28 ):
        case xo_field_left_bits_fill(25, 5, 28 ): case xo_field_left_bits_fill(26, 5, 28 ): case xo_field_left_bits_fill(27, 5, 28 ):
        case xo_field_left_bits_fill(28, 5, 28 ): case xo_field_left_bits_fill(29, 5, 28 ): case xo_field_left_bits_fill(30, 5, 28 ):
        case xo_field_left_bits_fill(31, 5, 28 ):
            return &group_63_instruction_data[ fmsub_index   ] + get_rc_value( (&group_63_instruction_data[ fmsub_index   ]), instruction );
        
        case 29: 
        case xo_field_left_bits_fill( 1, 5, 29 ): case xo_field_left_bits_fill( 2, 5, 29 ): case xo_field_left_bits_fill( 3, 5, 29 ):
        case xo_field_left_bits_fill( 4, 5, 29 ): case xo_field_left_bits_fill( 5, 5, 29 ): case xo_field_left_bits_fill( 6, 5, 29 ):
        case xo_field_left_bits_fill( 7, 5, 29 ): case xo_field_left_bits_fill( 8, 5, 29 ): case xo_field_left_bits_fill( 9, 5, 29 ):
        case xo_field_left_bits_fill(10, 5, 29 ): case xo_field_left_bits_fill(11, 5, 29 ): case xo_field_left_bits_fill(12, 5, 29 ):
        case xo_field_left_bits_fill(13, 5, 29 ): case xo_field_left_bits_fill(14, 5, 29 ): case xo_field_left_bits_fill(15, 5, 29 ):
        case xo_field_left_bits_fill(16, 5, 29 ): case xo_field_left_bits_fill(17, 5, 29 ): case xo_field_left_bits_fill(18, 5, 29 ):
        case xo_field_left_bits_fill(19, 5, 29 ): case xo_field_left_bits_fill(20, 5, 29 ): case xo_field_left_bits_fill(21, 5, 29 ):
        case xo_field_left_bits_fill(22, 5, 29 ): case xo_field_left_bits_fill(23, 5, 29 ): case xo_field_left_bits_fill(24, 5, 29 ):
        case xo_field_left_bits_fill(25, 5, 29 ): case xo_field_left_bits_fill(26, 5, 29 ): case xo_field_left_bits_fill(27, 5, 29 ):
        case xo_field_left_bits_fill(28, 5, 29 ): case xo_field_left_bits_fill(29, 5, 29 ): case xo_field_left_bits_fill(30, 5, 29 ):
        case xo_field_left_bits_fill(31, 5, 29 ):
            return &group_63_instruction_data[ fmadd_index   ] + get_rc_value( (&group_63_instruction_data[ fmadd_index   ]), instruction );
        
        case 30: 
        case xo_field_left_bits_fill( 1, 5, 30 ): case xo_field_left_bits_fill( 2, 5, 30 ): case xo_field_left_bits_fill( 3, 5, 30 ):
        case xo_field_left_bits_fill( 4, 5, 30 ): case xo_field_left_bits_fill( 5, 5, 30 ): case xo_field_left_bits_fill( 6, 5, 30 ):
        case xo_field_left_bits_fill( 7, 5, 30 ): case xo_field_left_bits_fill( 8, 5, 30 ): case xo_field_left_bits_fill( 9, 5, 30 ):
        case xo_field_left_bits_fill(10, 5, 30 ): case xo_field_left_bits_fill(11, 5, 30 ): case xo_field_left_bits_fill(12, 5, 30 ):
        case xo_field_left_bits_fill(13, 5, 30 ): case xo_field_left_bits_fill(14, 5, 30 ): case xo_field_left_bits_fill(15, 5, 30 ):
        case xo_field_left_bits_fill(16, 5, 30 ): case xo_field_left_bits_fill(17, 5, 30 ): case xo_field_left_bits_fill(18, 5, 30 ):
        case xo_field_left_bits_fill(19, 5, 30 ): case xo_field_left_bits_fill(20, 5, 30 ): case xo_field_left_bits_fill(21, 5, 30 ):
        case xo_field_left_bits_fill(22, 5, 30 ): case xo_field_left_bits_fill(23, 5, 30 ): case xo_field_left_bits_fill(24, 5, 30 ):
        case xo_field_left_bits_fill(25, 5, 30 ): case xo_field_left_bits_fill(26, 5, 30 ): case xo_field_left_bits_fill(27, 5, 30 ):
        case xo_field_left_bits_fill(28, 5, 30 ): case xo_field_left_bits_fill(29, 5, 30 ): case xo_field_left_bits_fill(30, 5, 30 ):
        case xo_field_left_bits_fill(31, 5, 30 ):
            return &group_63_instruction_data[ fnmsub_index  ] + get_rc_value( (&group_63_instruction_data[ fnmsub_index  ]), instruction );
        
        case 31: 
        case xo_field_left_bits_fill( 1, 5, 31 ): case xo_field_left_bits_fill( 2, 5, 31 ): case xo_field_left_bits_fill( 3, 5, 31 ):
        case xo_field_left_bits_fill( 4, 5, 31 ): case xo_field_left_bits_fill( 5, 5, 31 ): case xo_field_left_bits_fill( 6, 5, 31 ):
        case xo_field_left_bits_fill( 7, 5, 31 ): case xo_field_left_bits_fill( 8, 5, 31 ): case xo_field_left_bits_fill( 9, 5, 31 ):
        case xo_field_left_bits_fill(10, 5, 31 ): case xo_field_left_bits_fill(11, 5, 31 ): case xo_field_left_bits_fill(12, 5, 31 ):
        case xo_field_left_bits_fill(13, 5, 31 ): case xo_field_left_bits_fill(14, 5, 31 ): case xo_field_left_bits_fill(15, 5, 31 ):
        case xo_field_left_bits_fill(16, 5, 31 ): case xo_field_left_bits_fill(17, 5, 31 ): case xo_field_left_bits_fill(18, 5, 31 ):
        case xo_field_left_bits_fill(19, 5, 31 ): case xo_field_left_bits_fill(20, 5, 31 ): case xo_field_left_bits_fill(21, 5, 31 ):
        case xo_field_left_bits_fill(22, 5, 31 ): case xo_field_left_bits_fill(23, 5, 31 ): case xo_field_left_bits_fill(24, 5, 31 ):
        case xo_field_left_bits_fill(25, 5, 31 ): case xo_field_left_bits_fill(26, 5, 31 ): case xo_field_left_bits_fill(27, 5, 31 ):
        case xo_field_left_bits_fill(28, 5, 31 ): case xo_field_left_bits_fill(29, 5, 31 ): case xo_field_left_bits_fill(30, 5, 31 ):
        case xo_field_left_bits_fill(31, 5, 31 ):
            return &group_63_instruction_data[ fnmadd_index  ] + get_rc_value( (&group_63_instruction_data[ fnmadd_index  ]), instruction );
        
        case 32: 
            return &group_63_instruction_data[ fcmpo_index   ];
        
        case 38: 
            return &group_63_instruction_data[ mtfsb1_index  ] + get_rc_value( (&group_63_instruction_data[ mtfsb1_index  ]), instruction );
        
        case 40: 
            return &group_63_instruction_data[ fneg_index    ] + get_rc_value( (&group_63_instruction_data[ fneg_index    ]), instruction );
        
        case 64: 
            return &group_63_instruction_data[ mcrfs_index   ];
        
        case 70: 
            return &group_63_instruction_data[ mtfsb0_index  ] + get_rc_value( (&group_63_instruction_data[ mtfsb0_index  ]), instruction );
        
        case 72: 
            return &group_63_instruction_data[ fmr_index     ] + get_rc_value( (&group_63_instruction_data[ fmr_index     ]), instruction );
        
        case 134:
            return &group_63_instruction_data[ mtfsfi_index  ] + get_rc_value( (&group_63_instruction_data[ mtfsfi_index  ]), instruction );
        
        case 136:
            return &group_63_instruction_data[ fnabs_index   ] + get_rc_value( (&group_63_instruction_data[ fnabs_index   ]), instruction );
        
        case 264:
            return &group_63_instruction_data[ fabs_index    ] + get_rc_value( (&group_63_instruction_data[ fabs_index    ]), instruction );
        
        case 583:
            return &group_63_instruction_data[ mffs_index    ] + get_rc_value( (&group_63_instruction_data[ mffs_index    ]), instruction );
        
        case 711:
            return &group_63_instruction_data[ mtfsf_index   ] + get_rc_value( (&group_63_instruction_data[ mtfsf_index   ]), instruction );
        
        case 814:
            return &group_63_instruction_data[ fctid_index   ] + get_rc_value( (&group_63_instruction_data[ fctid_index   ]), instruction );
        
        case 815:
            return &group_63_instruction_data[ fctidz_index  ] + get_rc_value( (&group_63_instruction_data[ fctidz_index  ]), instruction );
        
        case 846:
            return &group_63_instruction_data[ fcfid_index   ] + get_rc_value( (&group_63_instruction_data[ fcfid_index   ]), instruction );
        };

    return (instruction_element *)NULL;
    }
    

///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_instruction_data
//
///////////////////////////////////////////////////////////////////////////////

inline instruction_element *
lookup_instruction_data( uint32_t ppc_instruction )
    {
    uint32_t instruction_group = get_group_value( ppc_instruction );

    switch( instruction_group )
        {
        case 2:
            return &group_2_to_15_instruction_data[ tdi_index ];
        
        case 3:
            return &group_2_to_15_instruction_data[  twi_index ];
        
        case 7:
            return &group_2_to_15_instruction_data[ mulli_index ];
        
        case 8:
            return &group_2_to_15_instruction_data[ subfic_index ];
        
        case 10:
            return &group_2_to_15_instruction_data[ cmpli_index ];
        
        case 11:
            return &group_2_to_15_instruction_data[ cmpi_index ];
        
        case 12:
            return &group_2_to_15_instruction_data[ addic_index ];
        
        case 13:
            return &group_2_to_15_instruction_data[ addic_dot_index ];
        
        case 14:
            if( get_rA_value( ppc_instruction ) == 0 )
                return &simplified_mnemonics_instruction_data[ li_index ];
            else
                return &group_2_to_15_instruction_data[ addi_index ];
        
        case 15:
            if( get_rA_value( ppc_instruction ) == 0 )
                return &simplified_mnemonics_instruction_data[ lis_index ];
            else
                return &group_2_to_15_instruction_data[ addis_index ];
        
        case 16:
            return &group_16_instruction_data[ bc_index ] + get_xo_value( (&group_16_instruction_data[ bc_index ]), ppc_instruction );
        
        case 17:
            return &group_17_instruction_data[ sc_index ];
        
        case 18:
            return &group_18_instruction_data[ b_index ] + get_xo_value( (&group_18_instruction_data[ b_index ]), ppc_instruction );
        
        case 19:
            return lookup_group_19_instruction_element( &group_19_instruction_data[ mcrf_index ],
                                                        ppc_instruction );
        
        case 20:
            return &group_20_to_23_instruction_data[ rlwimi_index ] + get_rc_value( (&group_16_instruction_data[ rlwimi_index ]), ppc_instruction );
        
        case 21:
            return &group_20_to_23_instruction_data[ rlwinm_index ] + get_rc_value( (&group_16_instruction_data[ rlwinm_index ]), ppc_instruction );
        
        case 23:
            return &group_20_to_23_instruction_data[ rlwnm_index ] + get_rc_value( (&group_16_instruction_data[ rlwnm_index ]), ppc_instruction );
        
        case 24:
            if( ( get_rS_value( ppc_instruction ) == 0 ) && ( get_rA_value( ppc_instruction ) == 0 ) && ( get_rB_value( ppc_instruction ) == 0 ) )
                return &simplified_mnemonics_instruction_data[ nop_index ];
            else
                return &group_24_to_29_instruction_data[ ori_index ];
        
        case 25:
            return &group_24_to_29_instruction_data[ oris_index ];
        
        case 26:
            return &group_24_to_29_instruction_data[ xori_index ];
        
        case 27:
            return &group_24_to_29_instruction_data[ xoris_index ];
        
        case 28:
            return &group_24_to_29_instruction_data[ andi_dot_index ];
        
        case 29:
            return &group_24_to_29_instruction_data[ andis_dot_index ];
        
        case 30:
            return lookup_group_30_instruction_element( &group_30_instruction_data[ rldicl_index ],
                                                        ppc_instruction );
        
        case 31:
            return lookup_group_31_instruction_element( &group_31_instruction_data[ cmp_index ],
                                                        ppc_instruction );
        
        case 32:
            return &group_32_to_55_instruction_data[ lwz_index   ];

        case 33:
            return &group_32_to_55_instruction_data[ lwzu_index  ];

        case 34:
            return &group_32_to_55_instruction_data[ lbz_index   ];

        case 35:
            return &group_32_to_55_instruction_data[ lbzu_index  ];

        case 36:
            return &group_32_to_55_instruction_data[ stw_index   ];

        case 37:
            return &group_32_to_55_instruction_data[ stwu_index  ];

        case 38:
            return &group_32_to_55_instruction_data[ stb_index   ];

        case 39:
            return &group_32_to_55_instruction_data[ stbu_index  ];

        case 40:
            return &group_32_to_55_instruction_data[ lhz_index   ];

        case 41:
            return &group_32_to_55_instruction_data[ lhzu_index  ];

        case 42:
            return &group_32_to_55_instruction_data[ lha_index   ];

        case 43:
            return &group_32_to_55_instruction_data[ lhau_index  ];

        case 44:
            return &group_32_to_55_instruction_data[ sth_index   ];

        case 45:
            return &group_32_to_55_instruction_data[ sthu_index  ];

        case 46:
            return &group_32_to_55_instruction_data[ lmw_index   ];

        case 47:
            return &group_32_to_55_instruction_data[ stmw_index  ];

        case 48:
            return &group_32_to_55_instruction_data[ lfs_index   ];

        case 49:
            return &group_32_to_55_instruction_data[ lfsu_index  ];

        case 50:
            return &group_32_to_55_instruction_data[ lfd_index   ];

        case 51:
            return &group_32_to_55_instruction_data[ lfdu_index  ];

        case 52:
            return &group_32_to_55_instruction_data[ stfs_index  ];

        case 53:
            return &group_32_to_55_instruction_data[ stfsu_index ];

        case 54:
            return &group_32_to_55_instruction_data[ stfd_index  ];

        case 55:
            return &group_32_to_55_instruction_data[ stfdu_index ];
        
        case 58:
            return &group_58_instruction_data[ fdivs_index ] + get_xo_value( (&group_58_instruction_data[ fdivs_index ]), ppc_instruction );
        
        case 59:
            return lookup_group_59_instruction_element( &group_59_instruction_data[ cmp_index ],
                                                        ppc_instruction );
        
        case 62:
            return &group_62_instruction_data[ std_index ] + get_xo_value( (&group_62_instruction_data[ std_index ]), ppc_instruction );
        
        case 63:
            return lookup_group_63_instruction_element( &group_59_instruction_data[ cmp_index ],
                                                        ppc_instruction );
        };
    
    return (instruction_element *)NULL;
    }


const char * gpr_register_names[ 32 ] =
    { "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
      "r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",
      "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
      "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
    };

const char * gpr_indirect_register_names[ 32 ] =
    { "(r0)",  "(r1)",  "(r2)",  "(r3)",  "(r4)",  "(r5)",  "(r6)",  "(r7)",
      "(r8)",  "(r9)",  "(r10)", "(r11)", "(r12)", "(r13)", "(r14)", "(r15)",
      "(r16)", "(r17)", "(r18)", "(r19)", "(r20)", "(r21)", "(r22)", "(r23)",
      "(r24)", "(r25)", "(r26)", "(r27)", "(r28)", "(r29)", "(r30)", "(r31)"
    };

const char * floating_point_register_names[ 32 ] =
    { "fr0",  "fr1",  "fr2",  "fr3",  "fr4",  "fr5",  "fr6",  "fr7",
      "fr8",  "fr9",  "fr10", "fr11", "fr12", "fr13", "fr14", "fr15",
      "fr16", "fr17", "fr18", "fr19", "fr20", "fr21", "fr22", "fr23",
      "fr24", "fr25", "fr26", "fr27", "fr28", "fr29", "fr30", "fr31"
    };

///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_instruction_latency_cycles
//
///////////////////////////////////////////////////////////////////////////////

inline char *
get_instruction_text( instruction_element * element,
                      uint32_t              instruction_address,
                      uint32_t              instruction )
    {
    static char string_buffer[ 64 ];
    static char decimal_buffer[ 20 ];
    
    strcpy( (char *)string_buffer,
            element->mnemonic );
    
    uint8_t * addr_cmds = element->addr_cmds;
    while( *addr_cmds != end_cmd )
        {
        switch( *addr_cmds )
            {
            case comma_cmd:
                strcat( (char *)string_buffer,
                        "," );
                break;
            
            case rS_cmd:
                int32_t rS_reg;
                
                rS_reg = get_rS_value( instruction );
                
                strcat( (char *)string_buffer,
                        gpr_register_names[ rS_reg ] );
                break;
            
            case rD_cmd:
                int32_t rD_reg;
                
                rD_reg = get_rD_value( instruction );
                
                strcat( (char *)string_buffer,
                        gpr_register_names[ rD_reg ] );
                break;
            
            case rA_cmd:
                int32_t rA_reg;
                
                rA_reg = get_rA_value( instruction );
                
                strcat( (char *)string_buffer,
                        gpr_register_names[ rA_reg ] );
                break;
            
            case rB_cmd:
                int32_t rB_reg;
                
                rB_reg = get_rB_value( instruction );
                
                strcat( (char *)string_buffer,
                        gpr_register_names[ rB_reg ] );
                break;
            
            case rA_disp_indirect_cmd:
                {
                int32_t DS_reg;
                int32_t rA_reg;
                
                rA_reg = get_rA_value( instruction );
                DS_reg = get_DS_value( instruction );
                DS_reg = SignExt32( DS_reg, 14 ) * sizeof( uint32_t );
                
                itoa( DS_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                
                strcat( (char *)string_buffer,
                        gpr_indirect_register_names[ rA_reg ] );
                }
                break;
            
            case LI_cmd:
                {
                uint32_t LI_reg;
                
                LI_reg = get_DS_value( instruction );
                LI_reg = SignExt32( LI_reg, 24 ) * sizeof( uint32_t );
                
                if( get_AA_value( instruction ) == 0 )
                    LI_reg += instruction_address;
                
                itoa( LI_reg,
                      decimal_buffer,
                      8,
                      16 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                }
                break;
            
            case SIMM_cmd:
                int32_t SIMM_reg;
                
                SIMM_reg = get_SIMM_value( instruction );
                SIMM_reg = SignExt32( SIMM_reg, 16 );
                
                itoa( SIMM_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case UIMM_cmd:
                int32_t UIMM_reg;
                
                UIMM_reg = get_UIMM_value( instruction );
                
                itoa( UIMM_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case LEV_cmd:
                int32_t LEV_reg;
                
                LEV_reg = get_LEV_value( instruction );
                
                itoa( LEV_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case BO_cmd:
                uint32_t BO_reg;
                
                BO_reg = get_BO_value( instruction );
                
                itoa( BO_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case BI_cmd:
                uint32_t BI_reg;
                
                BI_reg = get_BI_value( instruction );
                
                itoa( BI_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case BH_cmd:
                uint32_t BH_reg;
                
                BH_reg = get_BH_value( instruction );
                
                itoa( BH_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case BD_cmd:
                uint32_t BD_reg;
                
                BD_reg = get_BD_value( instruction );
                BD_reg = SignExt32( BD_reg, 14 ) * sizeof( uint32_t );
                
                if( get_AA_value( instruction ) == 0 )
                    BD_reg += instruction_address;
                
                itoa( BD_reg,
                      decimal_buffer,
                      8,
                      16 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case mb_cmd:
                int32_t mb_reg;
                
                mb_reg = get_mb_value( instruction );
                
                itoa( mb_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case me_cmd:
                int32_t me_reg;
                
                me_reg = get_me_value( instruction );
                
                itoa( me_reg,
                      decimal_buffer ,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case sh_cmd:
                int32_t sh_reg;
                
                sh_reg = get_sh_value( instruction );
                
                itoa( sh_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case MB_cmd:
                int32_t MB_reg;
                
                MB_reg = get_MB_value( instruction );
                
                itoa( MB_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            
            case ME_cmd:
                int32_t ME_reg;
                
                ME_reg = get_ME_value( instruction );
                
                itoa( ME_reg,
                      decimal_buffer,
                      0,
                      10 );
                
                strcat( (char *)string_buffer,
                        decimal_buffer );
                break;
            };
        
        ++addr_cmds;
        }
    
    return (char *)string_buffer;
    }


#if 0
///////////////////////////////////////////////////////////////////////////////
//
// FUNCTION: lookup_instruction_latency_cycles
//
///////////////////////////////////////////////////////////////////////////////

uint8_t
lookup_instruction_latency_cycles( uint32_t ppc_instruction )
    {
    uint8_t timing_value = 0;
    
    uint32_t instruction_group = ( ppc_instruction & group_mask ) >> group_shift;
    
    uint32_t instruction_xo = ( ppc_instruction & 0x7FE ) >> 1;
    
    timing_value = 0;
    
    return timing_value;
    }
#endif

#ifdef __cplusplus
}
#endif

#endif /* PPC_LOOKUP_H */
