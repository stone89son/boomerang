/* Generated by the New Jersey Machine-Code Toolkit, version 0.5a */
/* command line: tools -debug-match dbm -matcher disassembler.m -decoder dec -encoder enc -verbose hppa.spec hppadis.spec */
#include <mclib.h>
#include "boomerang/enc.h"
#define sign_extend(N,SIZE) \
  (((int)((N) << (sizeof(unsigned)*8-(SIZE)))) >> (sizeof(unsigned)*8-(SIZE)))
/**************

c_cmpb_w c3_16 is 
  (COMBT) op == 32 & c3_16 = c3_16 
  | (COMBF) op == 34 & c3_16 = c3_16 
  | (COMIBT) op == 33 & c3_16 = c3_16 
  | (COMIBF) op == 35 & c3_16 = c3_16

***********/
c_c_Instance c_cmpb_w(unsigned /* [0..7] */ c3_16) {
  c_c_Instance _i = { c_cmpb_w_TAG };
  if (!((unsigned)(c3_16) < 0x8)) 
    (*fail) ("c3_16 = %d won't fit in 3 unsigned bits");
  _i.u.c_cmpb_w.c3_16 = c3_16;
  return _i;
}
/**************

c_cmpb_dw c3_16 is 
  (CMPBdwt) op == 39 & c3_16 = c3_16 
  | (CMPBdwf) op == 47 & c3_16 = c3_16 
  | (CMPIBdw) op == 59 & c3_16 = c3_16

***********/
c_c_Instance c_cmpb_dw(unsigned /* [0..7] */ c3_16) {
  c_c_Instance _i = { c_cmpb_dw_TAG };
  if (!((unsigned)(c3_16) < 0x8)) 
    (*fail) ("c3_16 = %d won't fit in 3 unsigned bits");
  _i.u.c_cmpb_dw.c3_16 = c3_16;
  return _i;
}
/**************

c_bbs_w c_16 is 
  (ins_bbs_w) op == 49 & d_18 ==  0 & c_16 = c_16 
  | (ins_bbs_w) op == 48 & d_18 ==  0 & c_16 = c_16

***********/
c_c_Instance c_bbs_w(unsigned /* [0..1] */ c_16) {
  c_c_Instance _i = { c_bbs_w_TAG };
  if (!((unsigned)(c_16) < 0x2)) 
    (*fail) ("c_16 = %d won't fit in 1 unsigned bits");
  _i.u.c_bbs_w.c_16 = c_16;
  return _i;
}
/**************

c_bbs_dw c_16 is 
  (ins_bbs_dw) op == 49 & d_18 ==  1 & c_16 = c_16 
  | (ins_bbs_dw) op == 48 & d_18 ==  1 & c_16 = c_16

***********/
c_c_Instance c_bbs_dw(unsigned /* [0..1] */ c_16) {
  c_c_Instance _i = { c_bbs_dw_TAG };
  if (!((unsigned)(c_16) < 0x2)) 
    (*fail) ("c_16 = %d won't fit in 1 unsigned bits");
  _i.u.c_bbs_dw.c_16 = c_16;
  return _i;
}
/**************

c_arith_w c3_16 is 
  (arith_w) op ==  2 & ext6_20 == 24 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 56 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 28 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 60 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 25 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 57 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 26 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 58 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 27 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 59 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 16 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 48 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 19 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 51 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 20 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 52 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 17 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 ==  0 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 ==  8 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 ==  9 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 10 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 14 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 34 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 38 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 39 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 40 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 41 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 42 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 43 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 46 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 47 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 15 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 13 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 12 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 ==  7 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 ==  5 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 ==  4 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 11 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 29 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 30 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 31 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 21 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 22 & d_26 ==  0 & c3_16 = c3_16 
  | (arith_w) op ==  2 & ext6_20 == 23 & d_26 ==  0 & c3_16 = c3_16 
  | (ADDI) op == 45 & ext_20 ==  0 & c3_16 = c3_16 
  | (ADDI.v) op == 45 & ext_20 ==  1 & c3_16 = c3_16 
  | (ADDI.t) op == 44 & ext_20 ==  0 & c3_16 = c3_16 
  | (ADDI.t.v) op == 44 & ext_20 ==  1 & c3_16 = c3_16 
  | (SUBI) op == 37 & ext_20 ==  0 & c3_16 = c3_16 
  | (SUBI.v) op == 37 & ext_20 ==  1 & c3_16 = c3_16

***********/
c_c_Instance c_arith_w(unsigned /* [0..7] */ c3_16) {
  c_c_Instance _i = { c_arith_w_TAG };
  if (!((unsigned)(c3_16) < 0x8)) 
    (*fail) ("c3_16 = %d won't fit in 3 unsigned bits");
  _i.u.c_arith_w.c3_16 = c3_16;
  return _i;
}
/**************

c_arith_dw c3_16 is 
  (arith_dw) op ==  2 & ext6_20 == 24 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 56 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 28 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 60 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 25 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 57 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 26 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 58 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 27 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 59 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 16 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 48 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 19 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 51 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 20 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 52 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 17 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 ==  0 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 ==  8 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 ==  9 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 10 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 14 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 34 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 38 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 39 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 40 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 41 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 42 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 43 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 46 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 47 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 15 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 13 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 12 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 ==  7 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 ==  5 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 ==  4 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 11 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 29 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 30 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 31 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 21 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 22 & d_26 ==  1 & c3_16 = c3_16 
  | (arith_dw) op ==  2 & ext6_20 == 23 & d_26 ==  1 & c3_16 = c3_16

***********/
c_c_Instance c_arith_dw(unsigned /* [0..7] */ c3_16) {
  c_c_Instance _i = { c_arith_dw_TAG };
  if (!((unsigned)(c3_16) < 0x8)) 
    (*fail) ("c3_16 = %d won't fit in 3 unsigned bits");
  _i.u.c_arith_dw.c3_16 = c3_16;
  return _i;
}
/**************

c_arith_none  is (ins_arith_none) op == 10

***********/
c_c_Instance c_arith_none(void) {
  c_c_Instance _i = { c_arith_none_TAG };
  return _i;
}
/**************

c_br_nnull  is 
  (ins_br_nnull) op == 58 & n_30 ==  0 
  | (ins_br_nnull) op == 32 & n_30 ==  0 
  | (ins_br_nnull) op == 34 & n_30 ==  0 
  | (ins_br_nnull) op == 39 & n_30 ==  0 
  | (ins_br_nnull) op == 47 & n_30 ==  0 
  | (ins_br_nnull) op == 33 & n_30 ==  0 
  | (ins_br_nnull) op == 35 & n_30 ==  0 
  | (ins_br_nnull) op == 59 & n_30 ==  0 
  | (ins_br_nnull) op == 49 & n_30 ==  0 
  | (ins_br_nnull) op == 48 & n_30 ==  0 
  | (ins_br_nnull) op == 56 & n_30 ==  0 
  | (ins_br_nnull) op == 57 & n_30 ==  0

***********/
c_null_Instance c_br_nnull(void) {
  c_null_Instance _i = { c_br_nnull_TAG };
  return _i;
}
/**************

c_br_null  is 
  (ins_br_null) op == 58 & n_30 ==  1 
  | (ins_br_null) op == 32 & n_30 ==  1 
  | (ins_br_null) op == 34 & n_30 ==  1 
  | (ins_br_null) op == 39 & n_30 ==  1 
  | (ins_br_null) op == 47 & n_30 ==  1 
  | (ins_br_null) op == 33 & n_30 ==  1 
  | (ins_br_null) op == 35 & n_30 ==  1 
  | (ins_br_null) op == 59 & n_30 ==  1 
  | (ins_br_null) op == 49 & n_30 ==  1 
  | (ins_br_null) op == 48 & n_30 ==  1 
  | (ins_br_null) op == 56 & n_30 ==  1 
  | (ins_br_null) op == 57 & n_30 ==  1

***********/
c_null_Instance c_br_null(void) {
  c_null_Instance _i = { c_br_null_TAG };
  return _i;
}
/**************

c_mfctl_w  is (MFCTL.w) op ==  0 & ext8_19 == 69 & ext_17 ==  1

***********/
c_wcr_Instance c_mfctl_w(void) {
  c_wcr_Instance _i = { c_mfctl_w_TAG };
  return _i;
}
/**************

c_mfctl r_06 is (MFCTL) op ==  0 & ext8_19 == 69 & ext_17 ==  0 & r_06 = r_06

***********/
c_wcr_Instance c_mfctl(unsigned /* [0..31] */ r_06) {
  c_wcr_Instance _i = { c_mfctl_TAG };
  if (!((unsigned)(r_06) < 0x20)) 
    (*fail) ("r_06 = %d won't fit in 5 unsigned bits");
  _i.u.c_mfctl.r_06 = r_06;
  return _i;
}
/**************

c_bitpos_w p_06 is (ins_bb_w) op == 49 & d_18 ==  0 & p_06 = p_06

***********/
c_bit_Instance c_bitpos_w(unsigned /* [0..31] */ p_06) {
  c_bit_Instance _i = { c_bitpos_w_TAG };
  if (!((unsigned)(p_06) < 0x20)) 
    (*fail) ("p_06 = %d won't fit in 5 unsigned bits");
  _i.u.c_bitpos_w.p_06 = p_06;
  return _i;
}
/**************

c_bitpos_dw p_06 is (ins_bb_dw) op == 49 & d_18 ==  1 & p_06 = p_06

***********/
c_bit_Instance c_bitpos_dw(unsigned /* [0..31] */ p_06) {
  c_bit_Instance _i = { c_bitpos_dw_TAG };
  if (!((unsigned)(p_06) < 0x20)) 
    (*fail) ("p_06 = %d won't fit in 5 unsigned bits");
  _i.u.c_bitpos_dw.p_06 = p_06;
  return _i;
}
/**************

c_bitsar  is (BVB) op == 48

***********/
c_bit_Instance c_bitsar(void) {
  c_bit_Instance _i = { c_bitsar_TAG };
  return _i;
}
/**************

c_addr_mb  is 
  (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  0 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  1 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  2 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  6 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  7 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  8 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 ==  9 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 == 10 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 == 12 & a_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_mb) op ==  3 & addr_19 ==  1 & ext4_22 == 14 & a_18 ==  1 & 
  m_26 ==  1

***********/
c_addr_Instance c_addr_mb(void) {
  c_addr_Instance _i = { c_addr_mb_TAG };
  return _i;
}
/**************

c_addr_ma  is 
  (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  0 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  1 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  2 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  6 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  7 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  8 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 ==  9 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 == 10 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 == 12 & a_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_ma) op ==  3 & addr_19 ==  1 & ext4_22 == 14 & a_18 ==  0 & 
  m_26 ==  1

***********/
c_addr_Instance c_addr_ma(void) {
  c_addr_Instance _i = { c_addr_ma_TAG };
  return _i;
}
/**************

c_addr_s  is 
  (pc_addr_s) op ==  3 & addr_19 ==  0 & ext4_22 ==  0 & u_18 ==  1 & 
  m_26 ==  0 
  | (pc_addr_s) op ==  3 & addr_19 ==  0 & ext4_22 ==  1 & u_18 ==  1 & 
  m_26 ==  0 
  | (pc_addr_s) op ==  3 & addr_19 ==  0 & ext4_22 ==  2 & u_18 ==  1 & 
  m_26 ==  0 
  | (pc_addr_s) op ==  3 & addr_19 ==  0 & ext4_22 ==  6 & u_18 ==  1 & 
  m_26 ==  0 
  | (pc_addr_s) op ==  3 & addr_19 ==  0 & ext4_22 ==  7 & u_18 ==  1 & 
  m_26 ==  0

***********/
c_addr_Instance c_addr_s(void) {
  c_addr_Instance _i = { c_addr_s_TAG };
  return _i;
}
/**************

c_addr_m  is 
  (pc_addr_m) op ==  3 & addr_19 ==  0 & ext4_22 ==  0 & u_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_m) op ==  3 & addr_19 ==  0 & ext4_22 ==  1 & u_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_m) op ==  3 & addr_19 ==  0 & ext4_22 ==  2 & u_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_m) op ==  3 & addr_19 ==  0 & ext4_22 ==  6 & u_18 ==  0 & 
  m_26 ==  1 
  | (pc_addr_m) op ==  3 & addr_19 ==  0 & ext4_22 ==  7 & u_18 ==  0 & 
  m_26 ==  1

***********/
c_addr_Instance c_addr_m(void) {
  c_addr_Instance _i = { c_addr_m_TAG };
  return _i;
}
/**************

c_addr_sm  is 
  (pc_addr_sm) op ==  3 & addr_19 ==  0 & ext4_22 ==  0 & u_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_sm) op ==  3 & addr_19 ==  0 & ext4_22 ==  1 & u_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_sm) op ==  3 & addr_19 ==  0 & ext4_22 ==  2 & u_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_sm) op ==  3 & addr_19 ==  0 & ext4_22 ==  6 & u_18 ==  1 & 
  m_26 ==  1 
  | (pc_addr_sm) op ==  3 & addr_19 ==  0 & ext4_22 ==  7 & u_18 ==  1 & 
  m_26 ==  1

***********/
c_addr_Instance c_addr_sm(void) {
  c_addr_Instance _i = { c_addr_sm_TAG };
  return _i;
}
/**************

addr_index c_addr x(ss,b) is 
  
  CASE c_addr OF 
  | c_addr_m => 
      (?noname?) (?c_addr:): u_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  0 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  1 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  2 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  6 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  7 & x_11 = x & s2_16 = ss & b_06 = b
  | c_addr_ma => <NOMATCH>
  | c_addr_mb => <NOMATCH>
  | c_addr_s => 
      (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  0 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  0 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  0 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  1 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  0 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  2 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  0 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  6 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  0 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  7 & x_11 = x & s2_16 = ss & b_06 = b
  | c_addr_sm => 
      (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  0 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  1 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  2 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  6 & x_11 = x & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): u_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  0 & ext4_22 ==  7 & x_11 = x & s2_16 = ss & b_06 = b
  END (* c_addr *)

***********/
addr_Instance addr_index(c_addr_Instance c_addr, int x, int ss, int b) {
  addr_Instance _i = { addr_index_TAG };
  _i.u.addr_index.c_addr = c_addr;
  _i.u.addr_index.x = x;
  _i.u.addr_index.ss = ss;
  _i.u.addr_index.b = b;
  return _i;
}
/**************

addr_lsdisp c_addr im5(ss,b) is 
  
  CASE c_addr OF 
  | c_addr_m => <NOMATCH>
  | c_addr_ma => 
      (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  0 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  1 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  2 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  6 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  7 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b
  | c_addr_mb => 
      (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  0 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  1 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  2 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  6 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  7 & im4_11 = im5[28:3] & 
      im1_15 = im5[0:31][1!] & s2_16 = ss & b_06 = b
  | c_addr_s => <NOMATCH>
  | c_addr_sm => <NOMATCH>
  END (* c_addr *)

***********/
addr_Instance addr_lsdisp(c_addr_Instance c_addr, int im5, int ss, int b) {
  addr_Instance _i = { addr_lsdisp_TAG };
  _i.u.addr_lsdisp.c_addr = c_addr;
  _i.u.addr_lsdisp.im5 = im5;
  _i.u.addr_lsdisp.ss = ss;
  _i.u.addr_lsdisp.b = b;
  return _i;
}
/**************

addr_ssdisp c_addr im5(ss,b) is 
  
  CASE c_addr OF 
  | c_addr_m => <NOMATCH>
  | c_addr_ma => 
      (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  8 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  9 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 == 10 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 == 12 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  0 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 == 14 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b
  | c_addr_mb => 
      (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  8 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 ==  9 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 == 10 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 == 12 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b 
      | (?noname?) (?c_addr:): a_18 ==  1 & m_26 ==  1 & op ==  3 & 
      addr_19 ==  1 & ext4_22 == 14 & i_31 = im5[0:31][1!] & 
      im4_27 = im5[28:3] & s2_16 = ss & b_06 = b
  | c_addr_s => <NOMATCH>
  | c_addr_sm => <NOMATCH>
  END (* c_addr *)

***********/
addr_Instance addr_ssdisp(c_addr_Instance c_addr, int im5, int ss, int b) {
  addr_Instance _i = { addr_ssdisp_TAG };
  _i.u.addr_ssdisp.c_addr = c_addr;
  _i.u.addr_ssdisp.im5 = im5;
  _i.u.addr_ssdisp.ss = ss;
  _i.u.addr_ssdisp.b = b;
  return _i;
}
/**************
