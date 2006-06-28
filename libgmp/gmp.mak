# Microsoft Developer Studio Generated NMAKE File, Based on gmp.dsp
!IF "$(CFG)" == ""
CFG=gmp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to gmp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gmp - Win32 Release" && "$(CFG)" != "gmp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gmp.mak" CFG="gmp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gmp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gmp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gmp - Win32 Release"

OUTDIR=..\lib
INTDIR=.\Release

ALL : "$(OUTDIR)\gmp.lib"


CLEAN :
	-@erase "$(INTDIR)\asprintf.obj"
	-@erase "$(INTDIR)\asprntffuns.obj"
	-@erase "$(INTDIR)\assert.obj"
	-@erase "$(INTDIR)\compat.obj"
	-@erase "$(INTDIR)\doprnt.obj"
	-@erase "$(INTDIR)\doprntf.obj"
	-@erase "$(INTDIR)\doprnti.obj"
	-@erase "$(INTDIR)\doscan.obj"
	-@erase "$(INTDIR)\errno.obj"
	-@erase "$(INTDIR)\extract-dbl.obj"
	-@erase "$(INTDIR)\fprintf.obj"
	-@erase "$(INTDIR)\fscanf.obj"
	-@erase "$(INTDIR)\fscanffuns.obj"
	-@erase "$(INTDIR)\insert-dbl.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\mp_bpl.obj"
	-@erase "$(INTDIR)\mp_clz_tab.obj"
	-@erase "$(INTDIR)\mp_minv_tab.obj"
	-@erase "$(INTDIR)\mp_set_fns.obj"
	-@erase "$(INTDIR)\mpf\vc60.idb"
	-@erase "$(INTDIR)\mpn\vc60.idb"
	-@erase "$(INTDIR)\mpq\vc60.idb"
	-@erase "$(INTDIR)\mpz\vc60.idb"
	-@erase "$(INTDIR)\obprintf.obj"
	-@erase "$(INTDIR)\obprntffuns.obj"
	-@erase "$(INTDIR)\obvprintf.obj"
	-@erase "$(INTDIR)\pow_1.obj"
	-@erase "$(INTDIR)\printf.obj"
	-@erase "$(INTDIR)\printffuns.obj"
	-@erase "$(INTDIR)\rand.obj"
	-@erase "$(INTDIR)\randclr.obj"
	-@erase "$(INTDIR)\randdef.obj"
	-@erase "$(INTDIR)\randlc.obj"
	-@erase "$(INTDIR)\randlc2s.obj"
	-@erase "$(INTDIR)\randlc2x.obj"
	-@erase "$(INTDIR)\randraw.obj"
	-@erase "$(INTDIR)\rands.obj"
	-@erase "$(INTDIR)\randsd.obj"
	-@erase "$(INTDIR)\randsdui.obj"
	-@erase "$(INTDIR)\repl-vsnprintf.obj"
	-@erase "$(INTDIR)\scanf.obj"
	-@erase "$(INTDIR)\snprintf.obj"
	-@erase "$(INTDIR)\snprntffuns.obj"
	-@erase "$(INTDIR)\sprintf.obj"
	-@erase "$(INTDIR)\sprintffuns.obj"
	-@erase "$(INTDIR)\sscanf.obj"
	-@erase "$(INTDIR)\sscanffuns.obj"
	-@erase "$(INTDIR)\vasprintf.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(INTDIR)\vfprintf.obj"
	-@erase "$(INTDIR)\vfscanf.obj"
	-@erase "$(INTDIR)\vprintf.obj"
	-@erase "$(INTDIR)\vscanf.obj"
	-@erase "$(INTDIR)\vsnprintf.obj"
	-@erase "$(INTDIR)\vsprintf.obj"
	-@erase "$(INTDIR)\vsscanf.obj"
	-@erase "$(OUTDIR)\gmp.lib"
	-@erase "$(INTDIR)\mpf\abs.obj"
	-@erase "$(INTDIR)\mpf\add.obj"
	-@erase "$(INTDIR)\mpf\add_ui.obj"
	-@erase "$(INTDIR)\mpf\ceilfloor.obj"
	-@erase "$(INTDIR)\mpf\clear.obj"
	-@erase "$(INTDIR)\mpf\cmp.obj"
	-@erase "$(INTDIR)\mpf\cmp_d.obj"
	-@erase "$(INTDIR)\mpf\cmp_si.obj"
	-@erase "$(INTDIR)\mpf\cmp_ui.obj"
	-@erase "$(INTDIR)\mpf\div.obj"
	-@erase "$(INTDIR)\mpf\div_2exp.obj"
	-@erase "$(INTDIR)\mpf\div_ui.obj"
	-@erase "$(INTDIR)\mpf\dump.obj"
	-@erase "$(INTDIR)\mpf\eq.obj"
	-@erase "$(INTDIR)\mpf\fits_sint.obj"
	-@erase "$(INTDIR)\mpf\fits_slong.obj"
	-@erase "$(INTDIR)\mpf\fits_sshort.obj"
	-@erase "$(INTDIR)\mpf\fits_uint.obj"
	-@erase "$(INTDIR)\mpf\fits_ulong.obj"
	-@erase "$(INTDIR)\mpf\fits_ushort.obj"
	-@erase "$(INTDIR)\mpf\get_d.obj"
	-@erase "$(INTDIR)\mpf\get_d_2exp.obj"
	-@erase "$(INTDIR)\mpf\get_dfl_prec.obj"
	-@erase "$(INTDIR)\mpf\get_prc.obj"
	-@erase "$(INTDIR)\mpf\get_si.obj"
	-@erase "$(INTDIR)\mpf\get_str.obj"
	-@erase "$(INTDIR)\mpf\get_ui.obj"
	-@erase "$(INTDIR)\mpf\init.obj"
	-@erase "$(INTDIR)\mpf\init2.obj"
	-@erase "$(INTDIR)\mpf\inp_str.obj"
	-@erase "$(INTDIR)\mpf\int_p.obj"
	-@erase "$(INTDIR)\mpf\iset.obj"
	-@erase "$(INTDIR)\mpf\iset_d.obj"
	-@erase "$(INTDIR)\mpf\iset_si.obj"
	-@erase "$(INTDIR)\mpf\iset_str.obj"
	-@erase "$(INTDIR)\mpf\iset_ui.obj"
	-@erase "$(INTDIR)\mpf\mul.obj"
	-@erase "$(INTDIR)\mpf\mul_2exp.obj"
	-@erase "$(INTDIR)\mpf\mul_ui.obj"
	-@erase "$(INTDIR)\mpf\neg.obj"
	-@erase "$(INTDIR)\mpf\out_str.obj"
	-@erase "$(INTDIR)\mpf\pow_ui.obj"
	-@erase "$(INTDIR)\mpf\random2.obj"
	-@erase "$(INTDIR)\mpf\reldiff.obj"
	-@erase "$(INTDIR)\mpf\set.obj"
	-@erase "$(INTDIR)\mpf\set_d.obj"
	-@erase "$(INTDIR)\mpf\set_dfl_prec.obj"
	-@erase "$(INTDIR)\mpf\set_prc.obj"
	-@erase "$(INTDIR)\mpf\set_prc_raw.obj"
	-@erase "$(INTDIR)\mpf\set_q.obj"
	-@erase "$(INTDIR)\mpf\set_si.obj"
	-@erase "$(INTDIR)\mpf\set_str.obj"
	-@erase "$(INTDIR)\mpf\set_ui.obj"
	-@erase "$(INTDIR)\mpf\set_z.obj"
	-@erase "$(INTDIR)\mpf\size.obj"
	-@erase "$(INTDIR)\mpf\sqrt.obj"
	-@erase "$(INTDIR)\mpf\sqrt_ui.obj"
	-@erase "$(INTDIR)\mpf\sub.obj"
	-@erase "$(INTDIR)\mpf\sub_ui.obj"
	-@erase "$(INTDIR)\mpf\swap.obj"
	-@erase "$(INTDIR)\mpf\trunc.obj"
	-@erase "$(INTDIR)\mpf\ui_div.obj"
	-@erase "$(INTDIR)\mpf\ui_sub.obj"
	-@erase "$(INTDIR)\mpf\urandomb.obj"
	-@erase "$(INTDIR)\mpn\add.obj"
	-@erase "$(INTDIR)\mpn\add_1.obj"
	-@erase "$(INTDIR)\mpn\add_n.obj"
	-@erase "$(INTDIR)\mpn\addmul_1.obj"
	-@erase "$(INTDIR)\mpn\bdivmod.obj"
	-@erase "$(INTDIR)\mpn\cmp.obj"
	-@erase "$(INTDIR)\mpn\dc_divrem_n.obj"
	-@erase "$(INTDIR)\mpn\dive_1.obj"
	-@erase "$(INTDIR)\mpn\diveby3.obj"
	-@erase "$(INTDIR)\mpn\divis.obj"
	-@erase "$(INTDIR)\mpn\divrem.obj"
	-@erase "$(INTDIR)\mpn\divrem_1.obj"
	-@erase "$(INTDIR)\mpn\divrem_2.obj"
	-@erase "$(INTDIR)\mpn\dump.obj"
	-@erase "$(INTDIR)\mpn\fib2_ui.obj"
	-@erase "$(INTDIR)\mpn\gcd.obj"
	-@erase "$(INTDIR)\mpn\gcd_1.obj"
	-@erase "$(INTDIR)\mpn\gcdext.obj"
	-@erase "$(INTDIR)\mpn\get_str.obj"
	-@erase "$(INTDIR)\mpn\hamdist.obj"
	-@erase "$(INTDIR)\mpn\jacbase.obj"
	-@erase "$(INTDIR)\mpn\lshift.obj"
	-@erase "$(INTDIR)\mpn\mod_1.obj"
	-@erase "$(INTDIR)\mpn\mod_34lsub1.obj"
	-@erase "$(INTDIR)\mpn\mode1o.obj"
	-@erase "$(INTDIR)\mpn\mp_bases.obj"
	-@erase "$(INTDIR)\mpn\mul.obj"
	-@erase "$(INTDIR)\mpn\mul_1.obj"
	-@erase "$(INTDIR)\mpn\mul_basecase.obj"
	-@erase "$(INTDIR)\mpn\mul_fft.obj"
	-@erase "$(INTDIR)\mpn\mul_n.obj"
	-@erase "$(INTDIR)\mpn\perfsqr.obj"
	-@erase "$(INTDIR)\mpn\popcount.obj"
	-@erase "$(INTDIR)\mpn\pre_divrem_1.obj"
	-@erase "$(INTDIR)\mpn\pre_mod_1.obj"
	-@erase "$(INTDIR)\mpn\random.obj"
	-@erase "$(INTDIR)\mpn\random2.obj"
	-@erase "$(INTDIR)\mpn\rshift.obj"
	-@erase "$(INTDIR)\mpn\sb_divrem_mn.obj"
	-@erase "$(INTDIR)\mpn\scan0.obj"
	-@erase "$(INTDIR)\mpn\scan1.obj"
	-@erase "$(INTDIR)\mpn\set_str.obj"
	-@erase "$(INTDIR)\mpn\sqr_basecase.obj"
	-@erase "$(INTDIR)\mpn\sqrtrem.obj"
	-@erase "$(INTDIR)\mpn\sub.obj"
	-@erase "$(INTDIR)\mpn\sub_1.obj"
	-@erase "$(INTDIR)\mpn\sub_n.obj"
	-@erase "$(INTDIR)\mpn\submul_1.obj"
	-@erase "$(INTDIR)\mpn\tdiv_qr.obj"
	-@erase "$(INTDIR)\mpq\abs.obj"
	-@erase "$(INTDIR)\mpq\aors.obj"
	-@erase "$(INTDIR)\mpq\canonicalize.obj"
	-@erase "$(INTDIR)\mpq\clear.obj"
	-@erase "$(INTDIR)\mpq\cmp.obj"
	-@erase "$(INTDIR)\mpq\cmp_si.obj"
	-@erase "$(INTDIR)\mpq\cmp_ui.obj"
	-@erase "$(INTDIR)\mpq\div.obj"
	-@erase "$(INTDIR)\mpq\equal.obj"
	-@erase "$(INTDIR)\mpq\get_d.obj"
	-@erase "$(INTDIR)\mpq\get_den.obj"
	-@erase "$(INTDIR)\mpq\get_num.obj"
	-@erase "$(INTDIR)\mpq\get_str.obj"
	-@erase "$(INTDIR)\mpq\init.obj"
	-@erase "$(INTDIR)\mpq\inp_str.obj"
	-@erase "$(INTDIR)\mpq\inv.obj"
	-@erase "$(INTDIR)\mpq\md_2exp.obj"
	-@erase "$(INTDIR)\mpq\mul.obj"
	-@erase "$(INTDIR)\mpq\neg.obj"
	-@erase "$(INTDIR)\mpq\out_str.obj"
	-@erase "$(INTDIR)\mpq\set.obj"
	-@erase "$(INTDIR)\mpq\set_d.obj"
	-@erase "$(INTDIR)\mpq\set_den.obj"
	-@erase "$(INTDIR)\mpq\set_f.obj"
	-@erase "$(INTDIR)\mpq\set_num.obj"
	-@erase "$(INTDIR)\mpq\set_si.obj"
	-@erase "$(INTDIR)\mpq\set_str.obj"
	-@erase "$(INTDIR)\mpq\set_ui.obj"
	-@erase "$(INTDIR)\mpq\set_z.obj"
	-@erase "$(INTDIR)\mpq\swap.obj"
	-@erase "$(INTDIR)\mpz\abs.obj"
	-@erase "$(INTDIR)\mpz\add.obj"
	-@erase "$(INTDIR)\mpz\add_ui.obj"
	-@erase "$(INTDIR)\mpz\and.obj"
	-@erase "$(INTDIR)\mpz\aorsmul.obj"
	-@erase "$(INTDIR)\mpz\aorsmul_i.obj"
	-@erase "$(INTDIR)\mpz\array_init.obj"
	-@erase "$(INTDIR)\mpz\bin_ui.obj"
	-@erase "$(INTDIR)\mpz\bin_uiui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_q.obj"
	-@erase "$(INTDIR)\mpz\cdiv_q_ui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_qr.obj"
	-@erase "$(INTDIR)\mpz\cdiv_qr_ui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_r.obj"
	-@erase "$(INTDIR)\mpz\cdiv_r_ui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_ui.obj"
	-@erase "$(INTDIR)\mpz\cfdiv_q_2exp.obj"
	-@erase "$(INTDIR)\mpz\cfdiv_r_2exp.obj"
	-@erase "$(INTDIR)\mpz\clear.obj"
	-@erase "$(INTDIR)\mpz\clrbit.obj"
	-@erase "$(INTDIR)\mpz\cmp.obj"
	-@erase "$(INTDIR)\mpz\cmp_d.obj"
	-@erase "$(INTDIR)\mpz\cmp_si.obj"
	-@erase "$(INTDIR)\mpz\cmp_ui.obj"
	-@erase "$(INTDIR)\mpz\cmpabs.obj"
	-@erase "$(INTDIR)\mpz\cmpabs_d.obj"
	-@erase "$(INTDIR)\mpz\cmpabs_ui.obj"
	-@erase "$(INTDIR)\mpz\com.obj"
	-@erase "$(INTDIR)\mpz\cong.obj"
	-@erase "$(INTDIR)\mpz\cong_2exp.obj"
	-@erase "$(INTDIR)\mpz\cong_ui.obj"
	-@erase "$(INTDIR)\mpz\dive_ui.obj"
	-@erase "$(INTDIR)\mpz\divegcd.obj"
	-@erase "$(INTDIR)\mpz\divexact.obj"
	-@erase "$(INTDIR)\mpz\divis.obj"
	-@erase "$(INTDIR)\mpz\divis_2exp.obj"
	-@erase "$(INTDIR)\mpz\divis_ui.obj"
	-@erase "$(INTDIR)\mpz\dump.obj"
	-@erase "$(INTDIR)\mpz\fac_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_q.obj"
	-@erase "$(INTDIR)\mpz\fdiv_q_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_qr.obj"
	-@erase "$(INTDIR)\mpz\fdiv_qr_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_r.obj"
	-@erase "$(INTDIR)\mpz\fdiv_r_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_ui.obj"
	-@erase "$(INTDIR)\mpz\fib2_ui.obj"
	-@erase "$(INTDIR)\mpz\fib_ui.obj"
	-@erase "$(INTDIR)\mpz\fits_sint.obj"
	-@erase "$(INTDIR)\mpz\fits_slong.obj"
	-@erase "$(INTDIR)\mpz\fits_sshort.obj"
	-@erase "$(INTDIR)\mpz\fits_uint.obj"
	-@erase "$(INTDIR)\mpz\fits_ulong.obj"
	-@erase "$(INTDIR)\mpz\fits_ushort.obj"
	-@erase "$(INTDIR)\mpz\gcd.obj"
	-@erase "$(INTDIR)\mpz\gcd_ui.obj"
	-@erase "$(INTDIR)\mpz\gcdext.obj"
	-@erase "$(INTDIR)\mpz\get_d.obj"
	-@erase "$(INTDIR)\mpz\get_d_2exp.obj"
	-@erase "$(INTDIR)\mpz\get_si.obj"
	-@erase "$(INTDIR)\mpz\get_str.obj"
	-@erase "$(INTDIR)\mpz\get_ui.obj"
	-@erase "$(INTDIR)\mpz\getlimbn.obj"
	-@erase "$(INTDIR)\mpz\hamdist.obj"
	-@erase "$(INTDIR)\mpz\init.obj"
	-@erase "$(INTDIR)\mpz\init2.obj"
	-@erase "$(INTDIR)\mpz\inp_raw.obj"
	-@erase "$(INTDIR)\mpz\inp_str.obj"
	-@erase "$(INTDIR)\mpz\invert.obj"
	-@erase "$(INTDIR)\mpz\ior.obj"
	-@erase "$(INTDIR)\mpz\iset.obj"
	-@erase "$(INTDIR)\mpz\iset_d.obj"
	-@erase "$(INTDIR)\mpz\iset_si.obj"
	-@erase "$(INTDIR)\mpz\iset_str.obj"
	-@erase "$(INTDIR)\mpz\iset_ui.obj"
	-@erase "$(INTDIR)\mpz\jacobi.obj"
	-@erase "$(INTDIR)\mpz\kronsz.obj"
	-@erase "$(INTDIR)\mpz\kronuz.obj"
	-@erase "$(INTDIR)\mpz\kronzs.obj"
	-@erase "$(INTDIR)\mpz\kronzu.obj"
	-@erase "$(INTDIR)\mpz\lcm.obj"
	-@erase "$(INTDIR)\mpz\lcm_ui.obj"
	-@erase "$(INTDIR)\mpz\lucnum2_ui.obj"
	-@erase "$(INTDIR)\mpz\lucnum_ui.obj"
	-@erase "$(INTDIR)\mpz\millerrabin.obj"
	-@erase "$(INTDIR)\mpz\mod.obj"
	-@erase "$(INTDIR)\mpz\mul.obj"
	-@erase "$(INTDIR)\mpz\mul_2exp.obj"
	-@erase "$(INTDIR)\mpz\mul_si.obj"
	-@erase "$(INTDIR)\mpz\mul_ui.obj"
	-@erase "$(INTDIR)\mpz\n_pow_ui.obj"
	-@erase "$(INTDIR)\mpz\neg.obj"
	-@erase "$(INTDIR)\mpz\nextprime.obj"
	-@erase "$(INTDIR)\mpz\out_raw.obj"
	-@erase "$(INTDIR)\mpz\out_str.obj"
	-@erase "$(INTDIR)\mpz\perfpow.obj"
	-@erase "$(INTDIR)\mpz\perfsqr.obj"
	-@erase "$(INTDIR)\mpz\popcount.obj"
	-@erase "$(INTDIR)\mpz\pow_ui.obj"
	-@erase "$(INTDIR)\mpz\powm.obj"
	-@erase "$(INTDIR)\mpz\powm_ui.obj"
	-@erase "$(INTDIR)\mpz\pprime_p.obj"
	-@erase "$(INTDIR)\mpz\random.obj"
	-@erase "$(INTDIR)\mpz\random2.obj"
	-@erase "$(INTDIR)\mpz\realloc.obj"
	-@erase "$(INTDIR)\mpz\realloc2.obj"
	-@erase "$(INTDIR)\mpz\remove.obj"
	-@erase "$(INTDIR)\mpz\root.obj"
	-@erase "$(INTDIR)\mpz\rootrem.obj"
	-@erase "$(INTDIR)\mpz\rrandomb.obj"
	-@erase "$(INTDIR)\mpz\scan0.obj"
	-@erase "$(INTDIR)\mpz\scan1.obj"
	-@erase "$(INTDIR)\mpz\set.obj"
	-@erase "$(INTDIR)\mpz\set_d.obj"
	-@erase "$(INTDIR)\mpz\set_f.obj"
	-@erase "$(INTDIR)\mpz\set_q.obj"
	-@erase "$(INTDIR)\mpz\set_si.obj"
	-@erase "$(INTDIR)\mpz\set_str.obj"
	-@erase "$(INTDIR)\mpz\set_ui.obj"
	-@erase "$(INTDIR)\mpz\setbit.obj"
	-@erase "$(INTDIR)\mpz\size.obj"
	-@erase "$(INTDIR)\mpz\sizeinbase.obj"
	-@erase "$(INTDIR)\mpz\sqrt.obj"
	-@erase "$(INTDIR)\mpz\sqrtrem.obj"
	-@erase "$(INTDIR)\mpz\sub.obj"
	-@erase "$(INTDIR)\mpz\sub_ui.obj"
	-@erase "$(INTDIR)\mpz\swap.obj"
	-@erase "$(INTDIR)\mpz\tdiv_q.obj"
	-@erase "$(INTDIR)\mpz\tdiv_q_2exp.obj"
	-@erase "$(INTDIR)\mpz\tdiv_q_ui.obj"
	-@erase "$(INTDIR)\mpz\tdiv_qr.obj"
	-@erase "$(INTDIR)\mpz\tdiv_qr_ui.obj"
	-@erase "$(INTDIR)\mpz\tdiv_r.obj"
	-@erase "$(INTDIR)\mpz\tdiv_r_2exp.obj"
	-@erase "$(INTDIR)\mpz\tdiv_r_ui.obj"
	-@erase "$(INTDIR)\mpz\tdiv_ui.obj"
	-@erase "$(INTDIR)\mpz\tstbit.obj"
	-@erase "$(INTDIR)\mpz\ui_pow_ui.obj"
	-@erase "$(INTDIR)\mpz\urandomb.obj"
	-@erase "$(INTDIR)\mpz\urandomm.obj"
	-@erase "$(INTDIR)\mpz\xor.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"
    if not exist "$(INTDIR)\mpf" mkdir "$(INTDIR)\mpf"
    if not exist "$(INTDIR)\mpn" mkdir "$(INTDIR)\mpn"
    if not exist "$(INTDIR)\mpq" mkdir "$(INTDIR)\mpq"
    if not exist "$(INTDIR)\mpz" mkdir "$(INTDIR)\mpz"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"$(INTDIR)\gmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gmp.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../lib/gmp.lib" 
LIB32_OBJS= \
	"$(INTDIR)\mpf\abs.obj" \
	"$(INTDIR)\mpq\abs.obj" \
	"$(INTDIR)\mpz\abs.obj" \
	"$(INTDIR)\mpf\add.obj" \
	"$(INTDIR)\mpn\add.obj" \
	"$(INTDIR)\mpz\add.obj" \
	"$(INTDIR)\mpn\add_1.obj" \
	"$(INTDIR)\mpn\add_n.obj" \
	"$(INTDIR)\mpf\add_ui.obj" \
	"$(INTDIR)\mpz\add_ui.obj" \
	"$(INTDIR)\mpn\addmul_1.obj" \
	"$(INTDIR)\mpz\and.obj" \
	"$(INTDIR)\mpq\aors.obj" \
	"$(INTDIR)\mpz\aorsmul.obj" \
	"$(INTDIR)\mpz\aorsmul_i.obj" \
	"$(INTDIR)\mpz\array_init.obj" \
	"$(INTDIR)\asprintf.obj" \
	"$(INTDIR)\asprntffuns.obj" \
	"$(INTDIR)\assert.obj" \
	"$(INTDIR)\mpn\bdivmod.obj" \
	"$(INTDIR)\mpz\bin_ui.obj" \
	"$(INTDIR)\mpz\bin_uiui.obj" \
	"$(INTDIR)\mpq\canonicalize.obj" \
	"$(INTDIR)\mpz\cdiv_q.obj" \
	"$(INTDIR)\mpz\cdiv_q_ui.obj" \
	"$(INTDIR)\mpz\cdiv_qr.obj" \
	"$(INTDIR)\mpz\cdiv_qr_ui.obj" \
	"$(INTDIR)\mpz\cdiv_r.obj" \
	"$(INTDIR)\mpz\cdiv_r_ui.obj" \
	"$(INTDIR)\mpz\cdiv_ui.obj" \
	"$(INTDIR)\mpf\ceilfloor.obj" \
	"$(INTDIR)\mpz\cfdiv_q_2exp.obj" \
	"$(INTDIR)\mpz\cfdiv_r_2exp.obj" \
	"$(INTDIR)\mpf\clear.obj" \
	"$(INTDIR)\mpq\clear.obj" \
	"$(INTDIR)\mpz\clear.obj" \
	"$(INTDIR)\mpz\clrbit.obj" \
	"$(INTDIR)\mpf\cmp.obj" \
	"$(INTDIR)\mpn\cmp.obj" \
	"$(INTDIR)\mpq\cmp.obj" \
	"$(INTDIR)\mpz\cmp.obj" \
	"$(INTDIR)\mpf\cmp_d.obj" \
	"$(INTDIR)\mpz\cmp_d.obj" \
	"$(INTDIR)\mpf\cmp_si.obj" \
	"$(INTDIR)\mpq\cmp_si.obj" \
	"$(INTDIR)\mpz\cmp_si.obj" \
	"$(INTDIR)\mpf\cmp_ui.obj" \
	"$(INTDIR)\mpq\cmp_ui.obj" \
	"$(INTDIR)\mpz\cmp_ui.obj" \
	"$(INTDIR)\mpz\cmpabs.obj" \
	"$(INTDIR)\mpz\cmpabs_d.obj" \
	"$(INTDIR)\mpz\cmpabs_ui.obj" \
	"$(INTDIR)\mpz\com.obj" \
	"$(INTDIR)\compat.obj" \
	"$(INTDIR)\mpz\cong.obj" \
	"$(INTDIR)\mpz\cong_2exp.obj" \
	"$(INTDIR)\mpz\cong_ui.obj" \
	"$(INTDIR)\mpn\dc_divrem_n.obj" \
	"$(INTDIR)\mpf\div.obj" \
	"$(INTDIR)\mpq\div.obj" \
	"$(INTDIR)\mpf\div_2exp.obj" \
	"$(INTDIR)\mpf\div_ui.obj" \
	"$(INTDIR)\mpn\dive_1.obj" \
	"$(INTDIR)\mpz\dive_ui.obj" \
	"$(INTDIR)\mpn\diveby3.obj" \
	"$(INTDIR)\mpz\divegcd.obj" \
	"$(INTDIR)\mpz\divexact.obj" \
	"$(INTDIR)\mpn\divis.obj" \
	"$(INTDIR)\mpz\divis.obj" \
	"$(INTDIR)\mpz\divis_2exp.obj" \
	"$(INTDIR)\mpz\divis_ui.obj" \
	"$(INTDIR)\mpn\divrem.obj" \
	"$(INTDIR)\mpn\divrem_1.obj" \
	"$(INTDIR)\mpn\divrem_2.obj" \
	"$(INTDIR)\doprnt.obj" \
	"$(INTDIR)\doprntf.obj" \
	"$(INTDIR)\doprnti.obj" \
	"$(INTDIR)\doscan.obj" \
	"$(INTDIR)\mpf\dump.obj" \
	"$(INTDIR)\mpn\dump.obj" \
	"$(INTDIR)\mpz\dump.obj" \
	"$(INTDIR)\mpf\eq.obj" \
	"$(INTDIR)\mpq\equal.obj" \
	"$(INTDIR)\errno.obj" \
	"$(INTDIR)\extract-dbl.obj" \
	"$(INTDIR)\mpz\fac_ui.obj" \
	"$(INTDIR)\mpz\fdiv_q.obj" \
	"$(INTDIR)\mpz\fdiv_q_ui.obj" \
	"$(INTDIR)\mpz\fdiv_qr.obj" \
	"$(INTDIR)\mpz\fdiv_qr_ui.obj" \
	"$(INTDIR)\mpz\fdiv_r.obj" \
	"$(INTDIR)\mpz\fdiv_r_ui.obj" \
	"$(INTDIR)\mpz\fdiv_ui.obj" \
	"$(INTDIR)\mpn\fib2_ui.obj" \
	"$(INTDIR)\mpz\fib2_ui.obj" \
	"$(INTDIR)\mpz\fib_ui.obj" \
	"$(INTDIR)\mpf\fits_sint.obj" \
	"$(INTDIR)\mpz\fits_sint.obj" \
	"$(INTDIR)\mpf\fits_slong.obj" \
	"$(INTDIR)\mpz\fits_slong.obj" \
	"$(INTDIR)\mpf\fits_sshort.obj" \
	"$(INTDIR)\mpz\fits_sshort.obj" \
	"$(INTDIR)\mpf\fits_uint.obj" \
	"$(INTDIR)\mpz\fits_uint.obj" \
	"$(INTDIR)\mpf\fits_ulong.obj" \
	"$(INTDIR)\mpz\fits_ulong.obj" \
	"$(INTDIR)\mpf\fits_ushort.obj" \
	"$(INTDIR)\mpz\fits_ushort.obj" \
	"$(INTDIR)\fprintf.obj" \
	"$(INTDIR)\fscanf.obj" \
	"$(INTDIR)\fscanffuns.obj" \
	"$(INTDIR)\mpn\gcd.obj" \
	"$(INTDIR)\mpz\gcd.obj" \
	"$(INTDIR)\mpn\gcd_1.obj" \
	"$(INTDIR)\mpz\gcd_ui.obj" \
	"$(INTDIR)\mpn\gcdext.obj" \
	"$(INTDIR)\mpz\gcdext.obj" \
	"$(INTDIR)\mpf\get_d.obj" \
	"$(INTDIR)\mpq\get_d.obj" \
	"$(INTDIR)\mpz\get_d.obj" \
	"$(INTDIR)\mpf\get_d_2exp.obj" \
	"$(INTDIR)\mpz\get_d_2exp.obj" \
	"$(INTDIR)\mpq\get_den.obj" \
	"$(INTDIR)\mpf\get_dfl_prec.obj" \
	"$(INTDIR)\mpq\get_num.obj" \
	"$(INTDIR)\mpf\get_prc.obj" \
	"$(INTDIR)\mpf\get_si.obj" \
	"$(INTDIR)\mpz\get_si.obj" \
	"$(INTDIR)\mpf\get_str.obj" \
	"$(INTDIR)\mpn\get_str.obj" \
	"$(INTDIR)\mpq\get_str.obj" \
	"$(INTDIR)\mpz\get_str.obj" \
	"$(INTDIR)\mpf\get_ui.obj" \
	"$(INTDIR)\mpz\get_ui.obj" \
	"$(INTDIR)\mpz\getlimbn.obj" \
	"$(INTDIR)\mpn\hamdist.obj" \
	"$(INTDIR)\mpz\hamdist.obj" \
	"$(INTDIR)\mpf\init.obj" \
	"$(INTDIR)\mpq\init.obj" \
	"$(INTDIR)\mpz\init.obj" \
	"$(INTDIR)\mpf\init2.obj" \
	"$(INTDIR)\mpz\init2.obj" \
	"$(INTDIR)\mpz\inp_raw.obj" \
	"$(INTDIR)\mpf\inp_str.obj" \
	"$(INTDIR)\mpq\inp_str.obj" \
	"$(INTDIR)\mpz\inp_str.obj" \
	"$(INTDIR)\insert-dbl.obj" \
	"$(INTDIR)\mpf\int_p.obj" \
	"$(INTDIR)\mpq\inv.obj" \
	"$(INTDIR)\mpz\invert.obj" \
	"$(INTDIR)\mpz\ior.obj" \
	"$(INTDIR)\mpf\iset.obj" \
	"$(INTDIR)\mpz\iset.obj" \
	"$(INTDIR)\mpf\iset_d.obj" \
	"$(INTDIR)\mpz\iset_d.obj" \
	"$(INTDIR)\mpf\iset_si.obj" \
	"$(INTDIR)\mpz\iset_si.obj" \
	"$(INTDIR)\mpf\iset_str.obj" \
	"$(INTDIR)\mpz\iset_str.obj" \
	"$(INTDIR)\mpf\iset_ui.obj" \
	"$(INTDIR)\mpz\iset_ui.obj" \
	"$(INTDIR)\mpn\jacbase.obj" \
	"$(INTDIR)\mpz\jacobi.obj" \
	"$(INTDIR)\mpz\kronsz.obj" \
	"$(INTDIR)\mpz\kronuz.obj" \
	"$(INTDIR)\mpz\kronzs.obj" \
	"$(INTDIR)\mpz\kronzu.obj" \
	"$(INTDIR)\mpz\lcm.obj" \
	"$(INTDIR)\mpz\lcm_ui.obj" \
	"$(INTDIR)\mpn\lshift.obj" \
	"$(INTDIR)\mpz\lucnum2_ui.obj" \
	"$(INTDIR)\mpz\lucnum_ui.obj" \
	"$(INTDIR)\mpq\md_2exp.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\mpz\millerrabin.obj" \
	"$(INTDIR)\mpz\mod.obj" \
	"$(INTDIR)\mpn\mod_1.obj" \
	"$(INTDIR)\mpn\mod_34lsub1.obj" \
	"$(INTDIR)\mpn\mode1o.obj" \
	"$(INTDIR)\mpn\mp_bases.obj" \
	"$(INTDIR)\mp_bpl.obj" \
	"$(INTDIR)\mp_clz_tab.obj" \
	"$(INTDIR)\mp_minv_tab.obj" \
	"$(INTDIR)\mp_set_fns.obj" \
	"$(INTDIR)\mpf\mul.obj" \
	"$(INTDIR)\mpn\mul.obj" \
	"$(INTDIR)\mpq\mul.obj" \
	"$(INTDIR)\mpz\mul.obj" \
	"$(INTDIR)\mpn\mul_1.obj" \
	"$(INTDIR)\mpf\mul_2exp.obj" \
	"$(INTDIR)\mpz\mul_2exp.obj" \
	"$(INTDIR)\mpn\mul_basecase.obj" \
	"$(INTDIR)\mpn\mul_fft.obj" \
	"$(INTDIR)\mpn\mul_n.obj" \
	"$(INTDIR)\mpz\mul_si.obj" \
	"$(INTDIR)\mpf\mul_ui.obj" \
	"$(INTDIR)\mpz\mul_ui.obj" \
	"$(INTDIR)\mpz\n_pow_ui.obj" \
	"$(INTDIR)\mpf\neg.obj" \
	"$(INTDIR)\mpq\neg.obj" \
	"$(INTDIR)\mpz\neg.obj" \
	"$(INTDIR)\mpz\nextprime.obj" \
	"$(INTDIR)\obprintf.obj" \
	"$(INTDIR)\obprntffuns.obj" \
	"$(INTDIR)\obvprintf.obj" \
	"$(INTDIR)\mpz\out_raw.obj" \
	"$(INTDIR)\mpf\out_str.obj" \
	"$(INTDIR)\mpq\out_str.obj" \
	"$(INTDIR)\mpz\out_str.obj" \
	"$(INTDIR)\mpz\perfpow.obj" \
	"$(INTDIR)\mpn\perfsqr.obj" \
	"$(INTDIR)\mpz\perfsqr.obj" \
	"$(INTDIR)\mpn\popcount.obj" \
	"$(INTDIR)\mpz\popcount.obj" \
	"$(INTDIR)\pow_1.obj" \
	"$(INTDIR)\mpf\pow_ui.obj" \
	"$(INTDIR)\mpz\pow_ui.obj" \
	"$(INTDIR)\mpz\powm.obj" \
	"$(INTDIR)\mpz\powm_ui.obj" \
	"$(INTDIR)\mpz\pprime_p.obj" \
	"$(INTDIR)\mpn\pre_divrem_1.obj" \
	"$(INTDIR)\mpn\pre_mod_1.obj" \
	"$(INTDIR)\printf.obj" \
	"$(INTDIR)\printffuns.obj" \
	"$(INTDIR)\rand.obj" \
	"$(INTDIR)\randclr.obj" \
	"$(INTDIR)\randdef.obj" \
	"$(INTDIR)\randlc.obj" \
	"$(INTDIR)\randlc2s.obj" \
	"$(INTDIR)\randlc2x.obj" \
	"$(INTDIR)\mpn\random.obj" \
	"$(INTDIR)\mpz\random.obj" \
	"$(INTDIR)\mpf\random2.obj" \
	"$(INTDIR)\mpn\random2.obj" \
	"$(INTDIR)\mpz\random2.obj" \
	"$(INTDIR)\randraw.obj" \
	"$(INTDIR)\rands.obj" \
	"$(INTDIR)\randsd.obj" \
	"$(INTDIR)\randsdui.obj" \
	"$(INTDIR)\mpz\realloc.obj" \
	"$(INTDIR)\mpz\realloc2.obj" \
	"$(INTDIR)\mpf\reldiff.obj" \
	"$(INTDIR)\mpz\remove.obj" \
	"$(INTDIR)\repl-vsnprintf.obj" \
	"$(INTDIR)\mpz\root.obj" \
	"$(INTDIR)\mpz\rootrem.obj" \
	"$(INTDIR)\mpz\rrandomb.obj" \
	"$(INTDIR)\mpn\rshift.obj" \
	"$(INTDIR)\mpn\sb_divrem_mn.obj" \
	"$(INTDIR)\mpn\scan0.obj" \
	"$(INTDIR)\mpz\scan0.obj" \
	"$(INTDIR)\mpn\scan1.obj" \
	"$(INTDIR)\mpz\scan1.obj" \
	"$(INTDIR)\scanf.obj" \
	"$(INTDIR)\mpf\set.obj" \
	"$(INTDIR)\mpq\set.obj" \
	"$(INTDIR)\mpz\set.obj" \
	"$(INTDIR)\mpf\set_d.obj" \
	"$(INTDIR)\mpq\set_d.obj" \
	"$(INTDIR)\mpz\set_d.obj" \
	"$(INTDIR)\mpq\set_den.obj" \
	"$(INTDIR)\mpf\set_dfl_prec.obj" \
	"$(INTDIR)\mpq\set_f.obj" \
	"$(INTDIR)\mpz\set_f.obj" \
	"$(INTDIR)\mpq\set_num.obj" \
	"$(INTDIR)\mpf\set_prc.obj" \
	"$(INTDIR)\mpf\set_prc_raw.obj" \
	"$(INTDIR)\mpf\set_q.obj" \
	"$(INTDIR)\mpz\set_q.obj" \
	"$(INTDIR)\mpf\set_si.obj" \
	"$(INTDIR)\mpq\set_si.obj" \
	"$(INTDIR)\mpz\set_si.obj" \
	"$(INTDIR)\mpf\set_str.obj" \
	"$(INTDIR)\mpn\set_str.obj" \
	"$(INTDIR)\mpq\set_str.obj" \
	"$(INTDIR)\mpz\set_str.obj" \
	"$(INTDIR)\mpf\set_ui.obj" \
	"$(INTDIR)\mpq\set_ui.obj" \
	"$(INTDIR)\mpz\set_ui.obj" \
	"$(INTDIR)\mpf\set_z.obj" \
	"$(INTDIR)\mpq\set_z.obj" \
	"$(INTDIR)\mpz\setbit.obj" \
	"$(INTDIR)\mpf\size.obj" \
	"$(INTDIR)\mpz\size.obj" \
	"$(INTDIR)\mpz\sizeinbase.obj" \
	"$(INTDIR)\snprintf.obj" \
	"$(INTDIR)\snprntffuns.obj" \
	"$(INTDIR)\sprintf.obj" \
	"$(INTDIR)\sprintffuns.obj" \
	"$(INTDIR)\mpn\sqr_basecase.obj" \
	"$(INTDIR)\mpf\sqrt.obj" \
	"$(INTDIR)\mpz\sqrt.obj" \
	"$(INTDIR)\mpf\sqrt_ui.obj" \
	"$(INTDIR)\mpn\sqrtrem.obj" \
	"$(INTDIR)\mpz\sqrtrem.obj" \
	"$(INTDIR)\sscanf.obj" \
	"$(INTDIR)\sscanffuns.obj" \
	"$(INTDIR)\mpf\sub.obj" \
	"$(INTDIR)\mpn\sub.obj" \
	"$(INTDIR)\mpz\sub.obj" \
	"$(INTDIR)\mpn\sub_1.obj" \
	"$(INTDIR)\mpn\sub_n.obj" \
	"$(INTDIR)\mpf\sub_ui.obj" \
	"$(INTDIR)\mpz\sub_ui.obj" \
	"$(INTDIR)\mpn\submul_1.obj" \
	"$(INTDIR)\mpf\swap.obj" \
	"$(INTDIR)\mpq\swap.obj" \
	"$(INTDIR)\mpz\swap.obj" \
	"$(INTDIR)\mpz\tdiv_q.obj" \
	"$(INTDIR)\mpz\tdiv_q_2exp.obj" \
	"$(INTDIR)\mpz\tdiv_q_ui.obj" \
	"$(INTDIR)\mpn\tdiv_qr.obj" \
	"$(INTDIR)\mpz\tdiv_qr.obj" \
	"$(INTDIR)\mpz\tdiv_qr_ui.obj" \
	"$(INTDIR)\mpz\tdiv_r.obj" \
	"$(INTDIR)\mpz\tdiv_r_2exp.obj" \
	"$(INTDIR)\mpz\tdiv_r_ui.obj" \
	"$(INTDIR)\mpz\tdiv_ui.obj" \
	"$(INTDIR)\mpf\trunc.obj" \
	"$(INTDIR)\mpz\tstbit.obj" \
	"$(INTDIR)\mpf\ui_div.obj" \
	"$(INTDIR)\mpz\ui_pow_ui.obj" \
	"$(INTDIR)\mpf\ui_sub.obj" \
	"$(INTDIR)\mpf\urandomb.obj" \
	"$(INTDIR)\mpz\urandomb.obj" \
	"$(INTDIR)\mpz\urandomm.obj" \
	"$(INTDIR)\vasprintf.obj" \
	"$(INTDIR)\version.obj" \
	"$(INTDIR)\vfprintf.obj" \
	"$(INTDIR)\vfscanf.obj" \
	"$(INTDIR)\vprintf.obj" \
	"$(INTDIR)\vscanf.obj" \
	"$(INTDIR)\vsnprintf.obj" \
	"$(INTDIR)\vsprintf.obj" \
	"$(INTDIR)\vsscanf.obj" \
	"$(INTDIR)\mpz\xor.obj"

"$(OUTDIR)\gmp.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

OUTDIR=..\lib
INTDIR=.\Debug

ALL : "$(OUTDIR)\gmpDebug.lib"


CLEAN :
	-@erase "$(INTDIR)\asprintf.obj"
	-@erase "$(INTDIR)\asprntffuns.obj"
	-@erase "$(INTDIR)\assert.obj"
	-@erase "$(INTDIR)\compat.obj"
	-@erase "$(INTDIR)\doprnt.obj"
	-@erase "$(INTDIR)\doprntf.obj"
	-@erase "$(INTDIR)\doprnti.obj"
	-@erase "$(INTDIR)\doscan.obj"
	-@erase "$(INTDIR)\errno.obj"
	-@erase "$(INTDIR)\extract-dbl.obj"
	-@erase "$(INTDIR)\fprintf.obj"
	-@erase "$(INTDIR)\fscanf.obj"
	-@erase "$(INTDIR)\fscanffuns.obj"
	-@erase "$(INTDIR)\insert-dbl.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\mp_bpl.obj"
	-@erase "$(INTDIR)\mp_clz_tab.obj"
	-@erase "$(INTDIR)\mp_minv_tab.obj"
	-@erase "$(INTDIR)\mp_set_fns.obj"
	-@erase "$(INTDIR)\mpf\vc60.idb"
	-@erase "$(INTDIR)\mpf\vc60.pdb"
	-@erase "$(INTDIR)\mpn\vc60.idb"
	-@erase "$(INTDIR)\mpn\vc60.pdb"
	-@erase "$(INTDIR)\mpq\vc60.idb"
	-@erase "$(INTDIR)\mpq\vc60.pdb"
	-@erase "$(INTDIR)\mpz\vc60.idb"
	-@erase "$(INTDIR)\mpz\vc60.pdb"
	-@erase "$(INTDIR)\obprintf.obj"
	-@erase "$(INTDIR)\obprntffuns.obj"
	-@erase "$(INTDIR)\obvprintf.obj"
	-@erase "$(INTDIR)\pow_1.obj"
	-@erase "$(INTDIR)\printf.obj"
	-@erase "$(INTDIR)\printffuns.obj"
	-@erase "$(INTDIR)\rand.obj"
	-@erase "$(INTDIR)\randclr.obj"
	-@erase "$(INTDIR)\randdef.obj"
	-@erase "$(INTDIR)\randlc.obj"
	-@erase "$(INTDIR)\randlc2s.obj"
	-@erase "$(INTDIR)\randlc2x.obj"
	-@erase "$(INTDIR)\randraw.obj"
	-@erase "$(INTDIR)\rands.obj"
	-@erase "$(INTDIR)\randsd.obj"
	-@erase "$(INTDIR)\randsdui.obj"
	-@erase "$(INTDIR)\repl-vsnprintf.obj"
	-@erase "$(INTDIR)\scanf.obj"
	-@erase "$(INTDIR)\snprintf.obj"
	-@erase "$(INTDIR)\snprntffuns.obj"
	-@erase "$(INTDIR)\sprintf.obj"
	-@erase "$(INTDIR)\sprintffuns.obj"
	-@erase "$(INTDIR)\sscanf.obj"
	-@erase "$(INTDIR)\sscanffuns.obj"
	-@erase "$(INTDIR)\vasprintf.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "$(INTDIR)\vfprintf.obj"
	-@erase "$(INTDIR)\vfscanf.obj"
	-@erase "$(INTDIR)\vprintf.obj"
	-@erase "$(INTDIR)\vscanf.obj"
	-@erase "$(INTDIR)\vsnprintf.obj"
	-@erase "$(INTDIR)\vsprintf.obj"
	-@erase "$(INTDIR)\vsscanf.obj"
	-@erase "$(OUTDIR)\gmpDebug.lib"
	-@erase "$(INTDIR)\mpf\abs.obj"
	-@erase "$(INTDIR)\mpf\add.obj"
	-@erase "$(INTDIR)\mpf\add_ui.obj"
	-@erase "$(INTDIR)\mpf\ceilfloor.obj"
	-@erase "$(INTDIR)\mpf\clear.obj"
	-@erase "$(INTDIR)\mpf\cmp.obj"
	-@erase "$(INTDIR)\mpf\cmp_d.obj"
	-@erase "$(INTDIR)\mpf\cmp_si.obj"
	-@erase "$(INTDIR)\mpf\cmp_ui.obj"
	-@erase "$(INTDIR)\mpf\div.obj"
	-@erase "$(INTDIR)\mpf\div_2exp.obj"
	-@erase "$(INTDIR)\mpf\div_ui.obj"
	-@erase "$(INTDIR)\mpf\dump.obj"
	-@erase "$(INTDIR)\mpf\eq.obj"
	-@erase "$(INTDIR)\mpf\fits_sint.obj"
	-@erase "$(INTDIR)\mpf\fits_slong.obj"
	-@erase "$(INTDIR)\mpf\fits_sshort.obj"
	-@erase "$(INTDIR)\mpf\fits_uint.obj"
	-@erase "$(INTDIR)\mpf\fits_ulong.obj"
	-@erase "$(INTDIR)\mpf\fits_ushort.obj"
	-@erase "$(INTDIR)\mpf\get_d.obj"
	-@erase "$(INTDIR)\mpf\get_d_2exp.obj"
	-@erase "$(INTDIR)\mpf\get_dfl_prec.obj"
	-@erase "$(INTDIR)\mpf\get_prc.obj"
	-@erase "$(INTDIR)\mpf\get_si.obj"
	-@erase "$(INTDIR)\mpf\get_str.obj"
	-@erase "$(INTDIR)\mpf\get_ui.obj"
	-@erase "$(INTDIR)\mpf\init.obj"
	-@erase "$(INTDIR)\mpf\init2.obj"
	-@erase "$(INTDIR)\mpf\inp_str.obj"
	-@erase "$(INTDIR)\mpf\int_p.obj"
	-@erase "$(INTDIR)\mpf\iset.obj"
	-@erase "$(INTDIR)\mpf\iset_d.obj"
	-@erase "$(INTDIR)\mpf\iset_si.obj"
	-@erase "$(INTDIR)\mpf\iset_str.obj"
	-@erase "$(INTDIR)\mpf\iset_ui.obj"
	-@erase "$(INTDIR)\mpf\mul.obj"
	-@erase "$(INTDIR)\mpf\mul_2exp.obj"
	-@erase "$(INTDIR)\mpf\mul_ui.obj"
	-@erase "$(INTDIR)\mpf\neg.obj"
	-@erase "$(INTDIR)\mpf\out_str.obj"
	-@erase "$(INTDIR)\mpf\pow_ui.obj"
	-@erase "$(INTDIR)\mpf\random2.obj"
	-@erase "$(INTDIR)\mpf\reldiff.obj"
	-@erase "$(INTDIR)\mpf\set.obj"
	-@erase "$(INTDIR)\mpf\set_d.obj"
	-@erase "$(INTDIR)\mpf\set_dfl_prec.obj"
	-@erase "$(INTDIR)\mpf\set_prc.obj"
	-@erase "$(INTDIR)\mpf\set_prc_raw.obj"
	-@erase "$(INTDIR)\mpf\set_q.obj"
	-@erase "$(INTDIR)\mpf\set_si.obj"
	-@erase "$(INTDIR)\mpf\set_str.obj"
	-@erase "$(INTDIR)\mpf\set_ui.obj"
	-@erase "$(INTDIR)\mpf\set_z.obj"
	-@erase "$(INTDIR)\mpf\size.obj"
	-@erase "$(INTDIR)\mpf\sqrt.obj"
	-@erase "$(INTDIR)\mpf\sqrt_ui.obj"
	-@erase "$(INTDIR)\mpf\sub.obj"
	-@erase "$(INTDIR)\mpf\sub_ui.obj"
	-@erase "$(INTDIR)\mpf\swap.obj"
	-@erase "$(INTDIR)\mpf\trunc.obj"
	-@erase "$(INTDIR)\mpf\ui_div.obj"
	-@erase "$(INTDIR)\mpf\ui_sub.obj"
	-@erase "$(INTDIR)\mpf\urandomb.obj"
	-@erase "$(INTDIR)\mpn\add.obj"
	-@erase "$(INTDIR)\mpn\add_1.obj"
	-@erase "$(INTDIR)\mpn\add_n.obj"
	-@erase "$(INTDIR)\mpn\addmul_1.obj"
	-@erase "$(INTDIR)\mpn\bdivmod.obj"
	-@erase "$(INTDIR)\mpn\cmp.obj"
	-@erase "$(INTDIR)\mpn\dc_divrem_n.obj"
	-@erase "$(INTDIR)\mpn\dive_1.obj"
	-@erase "$(INTDIR)\mpn\diveby3.obj"
	-@erase "$(INTDIR)\mpn\divis.obj"
	-@erase "$(INTDIR)\mpn\divrem.obj"
	-@erase "$(INTDIR)\mpn\divrem_1.obj"
	-@erase "$(INTDIR)\mpn\divrem_2.obj"
	-@erase "$(INTDIR)\mpn\dump.obj"
	-@erase "$(INTDIR)\mpn\fib2_ui.obj"
	-@erase "$(INTDIR)\mpn\gcd.obj"
	-@erase "$(INTDIR)\mpn\gcd_1.obj"
	-@erase "$(INTDIR)\mpn\gcdext.obj"
	-@erase "$(INTDIR)\mpn\get_str.obj"
	-@erase "$(INTDIR)\mpn\hamdist.obj"
	-@erase "$(INTDIR)\mpn\jacbase.obj"
	-@erase "$(INTDIR)\mpn\lshift.obj"
	-@erase "$(INTDIR)\mpn\mod_1.obj"
	-@erase "$(INTDIR)\mpn\mod_34lsub1.obj"
	-@erase "$(INTDIR)\mpn\mode1o.obj"
	-@erase "$(INTDIR)\mpn\mp_bases.obj"
	-@erase "$(INTDIR)\mpn\mul.obj"
	-@erase "$(INTDIR)\mpn\mul_1.obj"
	-@erase "$(INTDIR)\mpn\mul_basecase.obj"
	-@erase "$(INTDIR)\mpn\mul_fft.obj"
	-@erase "$(INTDIR)\mpn\mul_n.obj"
	-@erase "$(INTDIR)\mpn\perfsqr.obj"
	-@erase "$(INTDIR)\mpn\popcount.obj"
	-@erase "$(INTDIR)\mpn\pre_divrem_1.obj"
	-@erase "$(INTDIR)\mpn\pre_mod_1.obj"
	-@erase "$(INTDIR)\mpn\random.obj"
	-@erase "$(INTDIR)\mpn\random2.obj"
	-@erase "$(INTDIR)\mpn\rshift.obj"
	-@erase "$(INTDIR)\mpn\sb_divrem_mn.obj"
	-@erase "$(INTDIR)\mpn\scan0.obj"
	-@erase "$(INTDIR)\mpn\scan1.obj"
	-@erase "$(INTDIR)\mpn\set_str.obj"
	-@erase "$(INTDIR)\mpn\sqr_basecase.obj"
	-@erase "$(INTDIR)\mpn\sqrtrem.obj"
	-@erase "$(INTDIR)\mpn\sub.obj"
	-@erase "$(INTDIR)\mpn\sub_1.obj"
	-@erase "$(INTDIR)\mpn\sub_n.obj"
	-@erase "$(INTDIR)\mpn\submul_1.obj"
	-@erase "$(INTDIR)\mpn\tdiv_qr.obj"
	-@erase "$(INTDIR)\mpq\abs.obj"
	-@erase "$(INTDIR)\mpq\aors.obj"
	-@erase "$(INTDIR)\mpq\canonicalize.obj"
	-@erase "$(INTDIR)\mpq\clear.obj"
	-@erase "$(INTDIR)\mpq\cmp.obj"
	-@erase "$(INTDIR)\mpq\cmp_si.obj"
	-@erase "$(INTDIR)\mpq\cmp_ui.obj"
	-@erase "$(INTDIR)\mpq\div.obj"
	-@erase "$(INTDIR)\mpq\equal.obj"
	-@erase "$(INTDIR)\mpq\get_d.obj"
	-@erase "$(INTDIR)\mpq\get_den.obj"
	-@erase "$(INTDIR)\mpq\get_num.obj"
	-@erase "$(INTDIR)\mpq\get_str.obj"
	-@erase "$(INTDIR)\mpq\init.obj"
	-@erase "$(INTDIR)\mpq\inp_str.obj"
	-@erase "$(INTDIR)\mpq\inv.obj"
	-@erase "$(INTDIR)\mpq\md_2exp.obj"
	-@erase "$(INTDIR)\mpq\mul.obj"
	-@erase "$(INTDIR)\mpq\neg.obj"
	-@erase "$(INTDIR)\mpq\out_str.obj"
	-@erase "$(INTDIR)\mpq\set.obj"
	-@erase "$(INTDIR)\mpq\set_d.obj"
	-@erase "$(INTDIR)\mpq\set_den.obj"
	-@erase "$(INTDIR)\mpq\set_f.obj"
	-@erase "$(INTDIR)\mpq\set_num.obj"
	-@erase "$(INTDIR)\mpq\set_si.obj"
	-@erase "$(INTDIR)\mpq\set_str.obj"
	-@erase "$(INTDIR)\mpq\set_ui.obj"
	-@erase "$(INTDIR)\mpq\set_z.obj"
	-@erase "$(INTDIR)\mpq\swap.obj"
	-@erase "$(INTDIR)\mpz\abs.obj"
	-@erase "$(INTDIR)\mpz\add.obj"
	-@erase "$(INTDIR)\mpz\add_ui.obj"
	-@erase "$(INTDIR)\mpz\and.obj"
	-@erase "$(INTDIR)\mpz\aorsmul.obj"
	-@erase "$(INTDIR)\mpz\aorsmul_i.obj"
	-@erase "$(INTDIR)\mpz\array_init.obj"
	-@erase "$(INTDIR)\mpz\bin_ui.obj"
	-@erase "$(INTDIR)\mpz\bin_uiui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_q.obj"
	-@erase "$(INTDIR)\mpz\cdiv_q_ui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_qr.obj"
	-@erase "$(INTDIR)\mpz\cdiv_qr_ui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_r.obj"
	-@erase "$(INTDIR)\mpz\cdiv_r_ui.obj"
	-@erase "$(INTDIR)\mpz\cdiv_ui.obj"
	-@erase "$(INTDIR)\mpz\cfdiv_q_2exp.obj"
	-@erase "$(INTDIR)\mpz\cfdiv_r_2exp.obj"
	-@erase "$(INTDIR)\mpz\clear.obj"
	-@erase "$(INTDIR)\mpz\clrbit.obj"
	-@erase "$(INTDIR)\mpz\cmp.obj"
	-@erase "$(INTDIR)\mpz\cmp_d.obj"
	-@erase "$(INTDIR)\mpz\cmp_si.obj"
	-@erase "$(INTDIR)\mpz\cmp_ui.obj"
	-@erase "$(INTDIR)\mpz\cmpabs.obj"
	-@erase "$(INTDIR)\mpz\cmpabs_d.obj"
	-@erase "$(INTDIR)\mpz\cmpabs_ui.obj"
	-@erase "$(INTDIR)\mpz\com.obj"
	-@erase "$(INTDIR)\mpz\cong.obj"
	-@erase "$(INTDIR)\mpz\cong_2exp.obj"
	-@erase "$(INTDIR)\mpz\cong_ui.obj"
	-@erase "$(INTDIR)\mpz\dive_ui.obj"
	-@erase "$(INTDIR)\mpz\divegcd.obj"
	-@erase "$(INTDIR)\mpz\divexact.obj"
	-@erase "$(INTDIR)\mpz\divis.obj"
	-@erase "$(INTDIR)\mpz\divis_2exp.obj"
	-@erase "$(INTDIR)\mpz\divis_ui.obj"
	-@erase "$(INTDIR)\mpz\dump.obj"
	-@erase "$(INTDIR)\mpz\fac_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_q.obj"
	-@erase "$(INTDIR)\mpz\fdiv_q_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_qr.obj"
	-@erase "$(INTDIR)\mpz\fdiv_qr_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_r.obj"
	-@erase "$(INTDIR)\mpz\fdiv_r_ui.obj"
	-@erase "$(INTDIR)\mpz\fdiv_ui.obj"
	-@erase "$(INTDIR)\mpz\fib2_ui.obj"
	-@erase "$(INTDIR)\mpz\fib_ui.obj"
	-@erase "$(INTDIR)\mpz\fits_sint.obj"
	-@erase "$(INTDIR)\mpz\fits_slong.obj"
	-@erase "$(INTDIR)\mpz\fits_sshort.obj"
	-@erase "$(INTDIR)\mpz\fits_uint.obj"
	-@erase "$(INTDIR)\mpz\fits_ulong.obj"
	-@erase "$(INTDIR)\mpz\fits_ushort.obj"
	-@erase "$(INTDIR)\mpz\gcd.obj"
	-@erase "$(INTDIR)\mpz\gcd_ui.obj"
	-@erase "$(INTDIR)\mpz\gcdext.obj"
	-@erase "$(INTDIR)\mpz\get_d.obj"
	-@erase "$(INTDIR)\mpz\get_d_2exp.obj"
	-@erase "$(INTDIR)\mpz\get_si.obj"
	-@erase "$(INTDIR)\mpz\get_str.obj"
	-@erase "$(INTDIR)\mpz\get_ui.obj"
	-@erase "$(INTDIR)\mpz\getlimbn.obj"
	-@erase "$(INTDIR)\mpz\hamdist.obj"
	-@erase "$(INTDIR)\mpz\init.obj"
	-@erase "$(INTDIR)\mpz\init2.obj"
	-@erase "$(INTDIR)\mpz\inp_raw.obj"
	-@erase "$(INTDIR)\mpz\inp_str.obj"
	-@erase "$(INTDIR)\mpz\invert.obj"
	-@erase "$(INTDIR)\mpz\ior.obj"
	-@erase "$(INTDIR)\mpz\iset.obj"
	-@erase "$(INTDIR)\mpz\iset_d.obj"
	-@erase "$(INTDIR)\mpz\iset_si.obj"
	-@erase "$(INTDIR)\mpz\iset_str.obj"
	-@erase "$(INTDIR)\mpz\iset_ui.obj"
	-@erase "$(INTDIR)\mpz\jacobi.obj"
	-@erase "$(INTDIR)\mpz\kronsz.obj"
	-@erase "$(INTDIR)\mpz\kronuz.obj"
	-@erase "$(INTDIR)\mpz\kronzs.obj"
	-@erase "$(INTDIR)\mpz\kronzu.obj"
	-@erase "$(INTDIR)\mpz\lcm.obj"
	-@erase "$(INTDIR)\mpz\lcm_ui.obj"
	-@erase "$(INTDIR)\mpz\lucnum2_ui.obj"
	-@erase "$(INTDIR)\mpz\lucnum_ui.obj"
	-@erase "$(INTDIR)\mpz\millerrabin.obj"
	-@erase "$(INTDIR)\mpz\mod.obj"
	-@erase "$(INTDIR)\mpz\mul.obj"
	-@erase "$(INTDIR)\mpz\mul_2exp.obj"
	-@erase "$(INTDIR)\mpz\mul_si.obj"
	-@erase "$(INTDIR)\mpz\mul_ui.obj"
	-@erase "$(INTDIR)\mpz\n_pow_ui.obj"
	-@erase "$(INTDIR)\mpz\neg.obj"
	-@erase "$(INTDIR)\mpz\nextprime.obj"
	-@erase "$(INTDIR)\mpz\out_raw.obj"
	-@erase "$(INTDIR)\mpz\out_str.obj"
	-@erase "$(INTDIR)\mpz\perfpow.obj"
	-@erase "$(INTDIR)\mpz\perfsqr.obj"
	-@erase "$(INTDIR)\mpz\popcount.obj"
	-@erase "$(INTDIR)\mpz\pow_ui.obj"
	-@erase "$(INTDIR)\mpz\powm.obj"
	-@erase "$(INTDIR)\mpz\powm_ui.obj"
	-@erase "$(INTDIR)\mpz\pprime_p.obj"
	-@erase "$(INTDIR)\mpz\random.obj"
	-@erase "$(INTDIR)\mpz\random2.obj"
	-@erase "$(INTDIR)\mpz\realloc.obj"
	-@erase "$(INTDIR)\mpz\realloc2.obj"
	-@erase "$(INTDIR)\mpz\remove.obj"
	-@erase "$(INTDIR)\mpz\root.obj"
	-@erase "$(INTDIR)\mpz\rootrem.obj"
	-@erase "$(INTDIR)\mpz\rrandomb.obj"
	-@erase "$(INTDIR)\mpz\scan0.obj"
	-@erase "$(INTDIR)\mpz\scan1.obj"
	-@erase "$(INTDIR)\mpz\set.obj"
	-@erase "$(INTDIR)\mpz\set_d.obj"
	-@erase "$(INTDIR)\mpz\set_f.obj"
	-@erase "$(INTDIR)\mpz\set_q.obj"
	-@erase "$(INTDIR)\mpz\set_si.obj"
	-@erase "$(INTDIR)\mpz\set_str.obj"
	-@erase "$(INTDIR)\mpz\set_ui.obj"
	-@erase "$(INTDIR)\mpz\setbit.obj"
	-@erase "$(INTDIR)\mpz\size.obj"
	-@erase "$(INTDIR)\mpz\sizeinbase.obj"
	-@erase "$(INTDIR)\mpz\sqrt.obj"
	-@erase "$(INTDIR)\mpz\sqrtrem.obj"
	-@erase "$(INTDIR)\mpz\sub.obj"
	-@erase "$(INTDIR)\mpz\sub_ui.obj"
	-@erase "$(INTDIR)\mpz\swap.obj"
	-@erase "$(INTDIR)\mpz\tdiv_q.obj"
	-@erase "$(INTDIR)\mpz\tdiv_q_2exp.obj"
	-@erase "$(INTDIR)\mpz\tdiv_q_ui.obj"
	-@erase "$(INTDIR)\mpz\tdiv_qr.obj"
	-@erase "$(INTDIR)\mpz\tdiv_qr_ui.obj"
	-@erase "$(INTDIR)\mpz\tdiv_r.obj"
	-@erase "$(INTDIR)\mpz\tdiv_r_2exp.obj"
	-@erase "$(INTDIR)\mpz\tdiv_r_ui.obj"
	-@erase "$(INTDIR)\mpz\tdiv_ui.obj"
	-@erase "$(INTDIR)\mpz\tstbit.obj"
	-@erase "$(INTDIR)\mpz\ui_pow_ui.obj"
	-@erase "$(INTDIR)\mpz\urandomb.obj"
	-@erase "$(INTDIR)\mpz\urandomm.obj"
	-@erase "$(INTDIR)\mpz\xor.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"
    if not exist "$(INTDIR)\mpf" mkdir "$(INTDIR)\mpf"
    if not exist "$(INTDIR)\mpn" mkdir "$(INTDIR)\mpn"
    if not exist "$(INTDIR)\mpq" mkdir "$(INTDIR)\mpq"
    if not exist "$(INTDIR)\mpz" mkdir "$(INTDIR)\mpz"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"$(INTDIR)\gmp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gmp.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../lib/gmpDebug.lib" 
LIB32_OBJS= \
	"$(INTDIR)\mpf\abs.obj" \
	"$(INTDIR)\mpq\abs.obj" \
	"$(INTDIR)\mpz\abs.obj" \
	"$(INTDIR)\mpf\add.obj" \
	"$(INTDIR)\mpn\add.obj" \
	"$(INTDIR)\mpz\add.obj" \
	"$(INTDIR)\mpn\add_1.obj" \
	"$(INTDIR)\mpn\add_n.obj" \
	"$(INTDIR)\mpf\add_ui.obj" \
	"$(INTDIR)\mpz\add_ui.obj" \
	"$(INTDIR)\mpn\addmul_1.obj" \
	"$(INTDIR)\mpz\and.obj" \
	"$(INTDIR)\mpq\aors.obj" \
	"$(INTDIR)\mpz\aorsmul.obj" \
	"$(INTDIR)\mpz\aorsmul_i.obj" \
	"$(INTDIR)\mpz\array_init.obj" \
	"$(INTDIR)\asprintf.obj" \
	"$(INTDIR)\asprntffuns.obj" \
	"$(INTDIR)\assert.obj" \
	"$(INTDIR)\mpn\bdivmod.obj" \
	"$(INTDIR)\mpz\bin_ui.obj" \
	"$(INTDIR)\mpz\bin_uiui.obj" \
	"$(INTDIR)\mpq\canonicalize.obj" \
	"$(INTDIR)\mpz\cdiv_q.obj" \
	"$(INTDIR)\mpz\cdiv_q_ui.obj" \
	"$(INTDIR)\mpz\cdiv_qr.obj" \
	"$(INTDIR)\mpz\cdiv_qr_ui.obj" \
	"$(INTDIR)\mpz\cdiv_r.obj" \
	"$(INTDIR)\mpz\cdiv_r_ui.obj" \
	"$(INTDIR)\mpz\cdiv_ui.obj" \
	"$(INTDIR)\mpf\ceilfloor.obj" \
	"$(INTDIR)\mpz\cfdiv_q_2exp.obj" \
	"$(INTDIR)\mpz\cfdiv_r_2exp.obj" \
	"$(INTDIR)\mpf\clear.obj" \
	"$(INTDIR)\mpq\clear.obj" \
	"$(INTDIR)\mpz\clear.obj" \
	"$(INTDIR)\mpz\clrbit.obj" \
	"$(INTDIR)\mpf\cmp.obj" \
	"$(INTDIR)\mpn\cmp.obj" \
	"$(INTDIR)\mpq\cmp.obj" \
	"$(INTDIR)\mpz\cmp.obj" \
	"$(INTDIR)\mpf\cmp_d.obj" \
	"$(INTDIR)\mpz\cmp_d.obj" \
	"$(INTDIR)\mpf\cmp_si.obj" \
	"$(INTDIR)\mpq\cmp_si.obj" \
	"$(INTDIR)\mpz\cmp_si.obj" \
	"$(INTDIR)\mpf\cmp_ui.obj" \
	"$(INTDIR)\mpq\cmp_ui.obj" \
	"$(INTDIR)\mpz\cmp_ui.obj" \
	"$(INTDIR)\mpz\cmpabs.obj" \
	"$(INTDIR)\mpz\cmpabs_d.obj" \
	"$(INTDIR)\mpz\cmpabs_ui.obj" \
	"$(INTDIR)\mpz\com.obj" \
	"$(INTDIR)\compat.obj" \
	"$(INTDIR)\mpz\cong.obj" \
	"$(INTDIR)\mpz\cong_2exp.obj" \
	"$(INTDIR)\mpz\cong_ui.obj" \
	"$(INTDIR)\mpn\dc_divrem_n.obj" \
	"$(INTDIR)\mpf\div.obj" \
	"$(INTDIR)\mpq\div.obj" \
	"$(INTDIR)\mpf\div_2exp.obj" \
	"$(INTDIR)\mpf\div_ui.obj" \
	"$(INTDIR)\mpn\dive_1.obj" \
	"$(INTDIR)\mpz\dive_ui.obj" \
	"$(INTDIR)\mpn\diveby3.obj" \
	"$(INTDIR)\mpz\divegcd.obj" \
	"$(INTDIR)\mpz\divexact.obj" \
	"$(INTDIR)\mpn\divis.obj" \
	"$(INTDIR)\mpz\divis.obj" \
	"$(INTDIR)\mpz\divis_2exp.obj" \
	"$(INTDIR)\mpz\divis_ui.obj" \
	"$(INTDIR)\mpn\divrem.obj" \
	"$(INTDIR)\mpn\divrem_1.obj" \
	"$(INTDIR)\mpn\divrem_2.obj" \
	"$(INTDIR)\doprnt.obj" \
	"$(INTDIR)\doprntf.obj" \
	"$(INTDIR)\doprnti.obj" \
	"$(INTDIR)\doscan.obj" \
	"$(INTDIR)\mpf\dump.obj" \
	"$(INTDIR)\mpn\dump.obj" \
	"$(INTDIR)\mpz\dump.obj" \
	"$(INTDIR)\mpf\eq.obj" \
	"$(INTDIR)\mpq\equal.obj" \
	"$(INTDIR)\errno.obj" \
	"$(INTDIR)\extract-dbl.obj" \
	"$(INTDIR)\mpz\fac_ui.obj" \
	"$(INTDIR)\mpz\fdiv_q.obj" \
	"$(INTDIR)\mpz\fdiv_q_ui.obj" \
	"$(INTDIR)\mpz\fdiv_qr.obj" \
	"$(INTDIR)\mpz\fdiv_qr_ui.obj" \
	"$(INTDIR)\mpz\fdiv_r.obj" \
	"$(INTDIR)\mpz\fdiv_r_ui.obj" \
	"$(INTDIR)\mpz\fdiv_ui.obj" \
	"$(INTDIR)\mpn\fib2_ui.obj" \
	"$(INTDIR)\mpz\fib2_ui.obj" \
	"$(INTDIR)\mpz\fib_ui.obj" \
	"$(INTDIR)\mpf\fits_sint.obj" \
	"$(INTDIR)\mpz\fits_sint.obj" \
	"$(INTDIR)\mpf\fits_slong.obj" \
	"$(INTDIR)\mpz\fits_slong.obj" \
	"$(INTDIR)\mpf\fits_sshort.obj" \
	"$(INTDIR)\mpz\fits_sshort.obj" \
	"$(INTDIR)\mpf\fits_uint.obj" \
	"$(INTDIR)\mpz\fits_uint.obj" \
	"$(INTDIR)\mpf\fits_ulong.obj" \
	"$(INTDIR)\mpz\fits_ulong.obj" \
	"$(INTDIR)\mpf\fits_ushort.obj" \
	"$(INTDIR)\mpz\fits_ushort.obj" \
	"$(INTDIR)\fprintf.obj" \
	"$(INTDIR)\fscanf.obj" \
	"$(INTDIR)\fscanffuns.obj" \
	"$(INTDIR)\mpn\gcd.obj" \
	"$(INTDIR)\mpz\gcd.obj" \
	"$(INTDIR)\mpn\gcd_1.obj" \
	"$(INTDIR)\mpz\gcd_ui.obj" \
	"$(INTDIR)\mpn\gcdext.obj" \
	"$(INTDIR)\mpz\gcdext.obj" \
	"$(INTDIR)\mpf\get_d.obj" \
	"$(INTDIR)\mpq\get_d.obj" \
	"$(INTDIR)\mpz\get_d.obj" \
	"$(INTDIR)\mpf\get_d_2exp.obj" \
	"$(INTDIR)\mpz\get_d_2exp.obj" \
	"$(INTDIR)\mpq\get_den.obj" \
	"$(INTDIR)\mpf\get_dfl_prec.obj" \
	"$(INTDIR)\mpq\get_num.obj" \
	"$(INTDIR)\mpf\get_prc.obj" \
	"$(INTDIR)\mpf\get_si.obj" \
	"$(INTDIR)\mpz\get_si.obj" \
	"$(INTDIR)\mpf\get_str.obj" \
	"$(INTDIR)\mpn\get_str.obj" \
	"$(INTDIR)\mpq\get_str.obj" \
	"$(INTDIR)\mpz\get_str.obj" \
	"$(INTDIR)\mpf\get_ui.obj" \
	"$(INTDIR)\mpz\get_ui.obj" \
	"$(INTDIR)\mpz\getlimbn.obj" \
	"$(INTDIR)\mpn\hamdist.obj" \
	"$(INTDIR)\mpz\hamdist.obj" \
	"$(INTDIR)\mpf\init.obj" \
	"$(INTDIR)\mpq\init.obj" \
	"$(INTDIR)\mpz\init.obj" \
	"$(INTDIR)\mpf\init2.obj" \
	"$(INTDIR)\mpz\init2.obj" \
	"$(INTDIR)\mpz\inp_raw.obj" \
	"$(INTDIR)\mpf\inp_str.obj" \
	"$(INTDIR)\mpq\inp_str.obj" \
	"$(INTDIR)\mpz\inp_str.obj" \
	"$(INTDIR)\insert-dbl.obj" \
	"$(INTDIR)\mpf\int_p.obj" \
	"$(INTDIR)\mpq\inv.obj" \
	"$(INTDIR)\mpz\invert.obj" \
	"$(INTDIR)\mpz\ior.obj" \
	"$(INTDIR)\mpf\iset.obj" \
	"$(INTDIR)\mpz\iset.obj" \
	"$(INTDIR)\mpf\iset_d.obj" \
	"$(INTDIR)\mpz\iset_d.obj" \
	"$(INTDIR)\mpf\iset_si.obj" \
	"$(INTDIR)\mpz\iset_si.obj" \
	"$(INTDIR)\mpf\iset_str.obj" \
	"$(INTDIR)\mpz\iset_str.obj" \
	"$(INTDIR)\mpf\iset_ui.obj" \
	"$(INTDIR)\mpz\iset_ui.obj" \
	"$(INTDIR)\mpn\jacbase.obj" \
	"$(INTDIR)\mpz\jacobi.obj" \
	"$(INTDIR)\mpz\kronsz.obj" \
	"$(INTDIR)\mpz\kronuz.obj" \
	"$(INTDIR)\mpz\kronzs.obj" \
	"$(INTDIR)\mpz\kronzu.obj" \
	"$(INTDIR)\mpz\lcm.obj" \
	"$(INTDIR)\mpz\lcm_ui.obj" \
	"$(INTDIR)\mpn\lshift.obj" \
	"$(INTDIR)\mpz\lucnum2_ui.obj" \
	"$(INTDIR)\mpz\lucnum_ui.obj" \
	"$(INTDIR)\mpq\md_2exp.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\mpz\millerrabin.obj" \
	"$(INTDIR)\mpz\mod.obj" \
	"$(INTDIR)\mpn\mod_1.obj" \
	"$(INTDIR)\mpn\mod_34lsub1.obj" \
	"$(INTDIR)\mpn\mode1o.obj" \
	"$(INTDIR)\mpn\mp_bases.obj" \
	"$(INTDIR)\mp_bpl.obj" \
	"$(INTDIR)\mp_clz_tab.obj" \
	"$(INTDIR)\mp_minv_tab.obj" \
	"$(INTDIR)\mp_set_fns.obj" \
	"$(INTDIR)\mpf\mul.obj" \
	"$(INTDIR)\mpn\mul.obj" \
	"$(INTDIR)\mpq\mul.obj" \
	"$(INTDIR)\mpz\mul.obj" \
	"$(INTDIR)\mpn\mul_1.obj" \
	"$(INTDIR)\mpf\mul_2exp.obj" \
	"$(INTDIR)\mpz\mul_2exp.obj" \
	"$(INTDIR)\mpn\mul_basecase.obj" \
	"$(INTDIR)\mpn\mul_fft.obj" \
	"$(INTDIR)\mpn\mul_n.obj" \
	"$(INTDIR)\mpz\mul_si.obj" \
	"$(INTDIR)\mpf\mul_ui.obj" \
	"$(INTDIR)\mpz\mul_ui.obj" \
	"$(INTDIR)\mpz\n_pow_ui.obj" \
	"$(INTDIR)\mpf\neg.obj" \
	"$(INTDIR)\mpq\neg.obj" \
	"$(INTDIR)\mpz\neg.obj" \
	"$(INTDIR)\mpz\nextprime.obj" \
	"$(INTDIR)\obprintf.obj" \
	"$(INTDIR)\obprntffuns.obj" \
	"$(INTDIR)\obvprintf.obj" \
	"$(INTDIR)\mpz\out_raw.obj" \
	"$(INTDIR)\mpf\out_str.obj" \
	"$(INTDIR)\mpq\out_str.obj" \
	"$(INTDIR)\mpz\out_str.obj" \
	"$(INTDIR)\mpz\perfpow.obj" \
	"$(INTDIR)\mpn\perfsqr.obj" \
	"$(INTDIR)\mpz\perfsqr.obj" \
	"$(INTDIR)\mpn\popcount.obj" \
	"$(INTDIR)\mpz\popcount.obj" \
	"$(INTDIR)\pow_1.obj" \
	"$(INTDIR)\mpf\pow_ui.obj" \
	"$(INTDIR)\mpz\pow_ui.obj" \
	"$(INTDIR)\mpz\powm.obj" \
	"$(INTDIR)\mpz\powm_ui.obj" \
	"$(INTDIR)\mpz\pprime_p.obj" \
	"$(INTDIR)\mpn\pre_divrem_1.obj" \
	"$(INTDIR)\mpn\pre_mod_1.obj" \
	"$(INTDIR)\printf.obj" \
	"$(INTDIR)\printffuns.obj" \
	"$(INTDIR)\rand.obj" \
	"$(INTDIR)\randclr.obj" \
	"$(INTDIR)\randdef.obj" \
	"$(INTDIR)\randlc.obj" \
	"$(INTDIR)\randlc2s.obj" \
	"$(INTDIR)\randlc2x.obj" \
	"$(INTDIR)\mpn\random.obj" \
	"$(INTDIR)\mpz\random.obj" \
	"$(INTDIR)\mpf\random2.obj" \
	"$(INTDIR)\mpn\random2.obj" \
	"$(INTDIR)\mpz\random2.obj" \
	"$(INTDIR)\randraw.obj" \
	"$(INTDIR)\rands.obj" \
	"$(INTDIR)\randsd.obj" \
	"$(INTDIR)\randsdui.obj" \
	"$(INTDIR)\mpz\realloc.obj" \
	"$(INTDIR)\mpz\realloc2.obj" \
	"$(INTDIR)\mpf\reldiff.obj" \
	"$(INTDIR)\mpz\remove.obj" \
	"$(INTDIR)\repl-vsnprintf.obj" \
	"$(INTDIR)\mpz\root.obj" \
	"$(INTDIR)\mpz\rootrem.obj" \
	"$(INTDIR)\mpz\rrandomb.obj" \
	"$(INTDIR)\mpn\rshift.obj" \
	"$(INTDIR)\mpn\sb_divrem_mn.obj" \
	"$(INTDIR)\mpn\scan0.obj" \
	"$(INTDIR)\mpz\scan0.obj" \
	"$(INTDIR)\mpn\scan1.obj" \
	"$(INTDIR)\mpz\scan1.obj" \
	"$(INTDIR)\scanf.obj" \
	"$(INTDIR)\mpf\set.obj" \
	"$(INTDIR)\mpq\set.obj" \
	"$(INTDIR)\mpz\set.obj" \
	"$(INTDIR)\mpf\set_d.obj" \
	"$(INTDIR)\mpq\set_d.obj" \
	"$(INTDIR)\mpz\set_d.obj" \
	"$(INTDIR)\mpq\set_den.obj" \
	"$(INTDIR)\mpf\set_dfl_prec.obj" \
	"$(INTDIR)\mpq\set_f.obj" \
	"$(INTDIR)\mpz\set_f.obj" \
	"$(INTDIR)\mpq\set_num.obj" \
	"$(INTDIR)\mpf\set_prc.obj" \
	"$(INTDIR)\mpf\set_prc_raw.obj" \
	"$(INTDIR)\mpf\set_q.obj" \
	"$(INTDIR)\mpz\set_q.obj" \
	"$(INTDIR)\mpf\set_si.obj" \
	"$(INTDIR)\mpq\set_si.obj" \
	"$(INTDIR)\mpz\set_si.obj" \
	"$(INTDIR)\mpf\set_str.obj" \
	"$(INTDIR)\mpn\set_str.obj" \
	"$(INTDIR)\mpq\set_str.obj" \
	"$(INTDIR)\mpz\set_str.obj" \
	"$(INTDIR)\mpf\set_ui.obj" \
	"$(INTDIR)\mpq\set_ui.obj" \
	"$(INTDIR)\mpz\set_ui.obj" \
	"$(INTDIR)\mpf\set_z.obj" \
	"$(INTDIR)\mpq\set_z.obj" \
	"$(INTDIR)\mpz\setbit.obj" \
	"$(INTDIR)\mpf\size.obj" \
	"$(INTDIR)\mpz\size.obj" \
	"$(INTDIR)\mpz\sizeinbase.obj" \
	"$(INTDIR)\snprintf.obj" \
	"$(INTDIR)\snprntffuns.obj" \
	"$(INTDIR)\sprintf.obj" \
	"$(INTDIR)\sprintffuns.obj" \
	"$(INTDIR)\mpn\sqr_basecase.obj" \
	"$(INTDIR)\mpf\sqrt.obj" \
	"$(INTDIR)\mpz\sqrt.obj" \
	"$(INTDIR)\mpf\sqrt_ui.obj" \
	"$(INTDIR)\mpn\sqrtrem.obj" \
	"$(INTDIR)\mpz\sqrtrem.obj" \
	"$(INTDIR)\sscanf.obj" \
	"$(INTDIR)\sscanffuns.obj" \
	"$(INTDIR)\mpf\sub.obj" \
	"$(INTDIR)\mpn\sub.obj" \
	"$(INTDIR)\mpz\sub.obj" \
	"$(INTDIR)\mpn\sub_1.obj" \
	"$(INTDIR)\mpn\sub_n.obj" \
	"$(INTDIR)\mpf\sub_ui.obj" \
	"$(INTDIR)\mpz\sub_ui.obj" \
	"$(INTDIR)\mpn\submul_1.obj" \
	"$(INTDIR)\mpf\swap.obj" \
	"$(INTDIR)\mpq\swap.obj" \
	"$(INTDIR)\mpz\swap.obj" \
	"$(INTDIR)\mpz\tdiv_q.obj" \
	"$(INTDIR)\mpz\tdiv_q_2exp.obj" \
	"$(INTDIR)\mpz\tdiv_q_ui.obj" \
	"$(INTDIR)\mpn\tdiv_qr.obj" \
	"$(INTDIR)\mpz\tdiv_qr.obj" \
	"$(INTDIR)\mpz\tdiv_qr_ui.obj" \
	"$(INTDIR)\mpz\tdiv_r.obj" \
	"$(INTDIR)\mpz\tdiv_r_2exp.obj" \
	"$(INTDIR)\mpz\tdiv_r_ui.obj" \
	"$(INTDIR)\mpz\tdiv_ui.obj" \
	"$(INTDIR)\mpf\trunc.obj" \
	"$(INTDIR)\mpz\tstbit.obj" \
	"$(INTDIR)\mpf\ui_div.obj" \
	"$(INTDIR)\mpz\ui_pow_ui.obj" \
	"$(INTDIR)\mpf\ui_sub.obj" \
	"$(INTDIR)\mpf\urandomb.obj" \
	"$(INTDIR)\mpz\urandomb.obj" \
	"$(INTDIR)\mpz\urandomm.obj" \
	"$(INTDIR)\vasprintf.obj" \
	"$(INTDIR)\version.obj" \
	"$(INTDIR)\vfprintf.obj" \
	"$(INTDIR)\vfscanf.obj" \
	"$(INTDIR)\vprintf.obj" \
	"$(INTDIR)\vscanf.obj" \
	"$(INTDIR)\vsnprintf.obj" \
	"$(INTDIR)\vsprintf.obj" \
	"$(INTDIR)\vsscanf.obj" \
	"$(INTDIR)\mpz\xor.obj"

"$(OUTDIR)\gmpDebug.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("gmp.dep")
!INCLUDE "gmp.dep"
!ELSE 
!MESSAGE Warning: cannot find "gmp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "gmp - Win32 Release" || "$(CFG)" == "gmp - Win32 Debug"
SOURCE=.\mpf\abs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\abs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\abs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\abs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\abs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\abs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\abs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\abs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\abs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\add.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\add.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\add.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\add.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\add.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\add.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\add.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\add.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\add.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\add_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\add_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\add_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\add_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_add_n" /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\add_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_add_n" /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\add_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\add_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\add_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\add_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\add_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\add_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\add_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\addmul_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_addmul_1" /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\addmul_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_addmul_1" /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\addmul_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\and.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\and.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\and.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\aors.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\aors.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\aors.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\aorsmul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\aorsmul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\aorsmul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\aorsmul_i.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\aorsmul_i.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\aorsmul_i.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\array_init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\array_init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\array_init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\asprintf.c

"$(INTDIR)\asprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\asprntffuns.c

"$(INTDIR)\asprntffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\assert.c

"$(INTDIR)\assert.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpn\generic\bdivmod.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\bdivmod.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\bdivmod.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\bin_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\bin_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\bin_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\bin_uiui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\bin_uiui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\bin_uiui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\canonicalize.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\canonicalize.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\canonicalize.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_q_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_q_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_q_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_qr_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_qr_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_qr_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_r.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_r.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_r.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_r_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_r_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_r_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cdiv_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cdiv_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cdiv_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\ceilfloor.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\ceilfloor.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\ceilfloor.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cfdiv_q_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cfdiv_q_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cfdiv_q_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cfdiv_r_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cfdiv_r_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cfdiv_r_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\clear.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\clear.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\clear.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\clear.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\clear.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\clear.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\clear.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\clear.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\clear.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\clrbit.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\clrbit.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\clrbit.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\cmp_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\cmp_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\cmp_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmp_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmp_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmp_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\cmp_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\cmp_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\cmp_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\cmp_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\cmp_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\cmp_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmp_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmp_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmp_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\cmp_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\cmp_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\cmp_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\cmp_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\cmp_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\cmp_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmp_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmp_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmp_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmpabs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmpabs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmpabs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmpabs_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmpabs_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmpabs_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cmpabs_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cmpabs_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cmpabs_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\com.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\com.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\com.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\compat.c

"$(INTDIR)\compat.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpz\cong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cong_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cong_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cong_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\cong_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\cong_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\cong_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\dc_divrem_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\dc_divrem_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\dc_divrem_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\div.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\div.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\div.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\div.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\div.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\div.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\div_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\div_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\div_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\div_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\div_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\div_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\dive_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\dive_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\dive_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\dive_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\dive_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\dive_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\diveby3.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\diveby3.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\diveby3.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\divegcd.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\divegcd.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\divegcd.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\divexact.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\divexact.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\divexact.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\divis.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\divis.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\divis.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\divis.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\divis.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\divis.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\divis_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\divis_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\divis_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\divis_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\divis_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\divis_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\divrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\divrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\divrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\divrem_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\divrem_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\divrem_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\divrem_2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\divrem_2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\divrem_2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\doprnt.c

"$(INTDIR)\doprnt.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\doprntf.c

"$(INTDIR)\doprntf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\doprnti.c

"$(INTDIR)\doprnti.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\doscan.c

"$(INTDIR)\doscan.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpf\dump.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\dump.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\dump.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\dump.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\dump.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\dump.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\dump.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\dump.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\dump.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\eq.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\eq.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\eq.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\equal.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\equal.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\equal.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\errno.c

"$(INTDIR)\errno.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=".\extract-dbl.c"

"$(INTDIR)\extract-dbl.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpz\fac_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fac_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fac_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_q_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_q_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_q_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_qr_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_qr_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_qr_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_r.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_r.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_r.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_r_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_r_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_r_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fdiv_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fdiv_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fdiv_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\fib2_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\fib2_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\fib2_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fib2_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fib2_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fib2_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fib_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fib_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fib_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\fits_sint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\fits_sint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\fits_sint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fits_sint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fits_sint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fits_sint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\fits_slong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\fits_slong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\fits_slong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fits_slong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fits_slong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fits_slong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\fits_sshort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\fits_sshort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\fits_sshort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fits_sshort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fits_sshort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fits_sshort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\fits_uint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\fits_uint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\fits_uint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fits_uint.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fits_uint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fits_uint.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\fits_ulong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\fits_ulong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\fits_ulong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fits_ulong.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fits_ulong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fits_ulong.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\fits_ushort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\fits_ushort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\fits_ushort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\fits_ushort.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\fits_ushort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\fits_ushort.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\fprintf.c

"$(INTDIR)\fprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\fscanf.c

"$(INTDIR)\fscanf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\fscanffuns.c

"$(INTDIR)\fscanffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpn\generic\gcd.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\gcd.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\gcd.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\gcd.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\gcd.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\gcd.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\gcd_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\gcd_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\gcd_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\gcd_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\gcd_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\gcd_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\gcdext.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\gcdext.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\gcdext.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\gcdext.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\gcdext.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\gcdext.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\get_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\get_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\get_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\get_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\get_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\get_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_d_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_d_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_d_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\get_d_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\get_d_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\get_d_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\get_den.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\get_den.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\get_den.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_dfl_prec.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_dfl_prec.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_dfl_prec.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\get_num.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\get_num.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\get_num.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_prc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_prc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_prc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\get_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\get_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\get_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\get_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\get_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\get_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\get_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\get_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\get_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\get_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\get_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\getlimbn.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\getlimbn.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\getlimbn.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\hamdist.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\hamdist.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\hamdist.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\hamdist.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\hamdist.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\hamdist.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\init.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\init.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\init2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\init2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\init2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\init2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\init2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\init2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\inp_raw.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\inp_raw.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\inp_raw.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\inp_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\inp_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\inp_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\inp_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\inp_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\inp_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\inp_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\inp_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\inp_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=".\insert-dbl.c"

"$(INTDIR)\insert-dbl.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpf\int_p.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\int_p.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\int_p.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\inv.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\inv.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\inv.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\invert.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\invert.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\invert.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\ior.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\ior.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\ior.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\iset.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\iset.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\iset.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\iset.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\iset.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\iset.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\iset_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\iset_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\iset_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\iset_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\iset_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\iset_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\iset_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\iset_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\iset_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\iset_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\iset_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\iset_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\iset_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\iset_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\iset_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\iset_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\iset_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\iset_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\iset_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\iset_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\iset_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\iset_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\iset_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\iset_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\jacbase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\jacbase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\jacbase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\jacobi.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\jacobi.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\jacobi.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\kronsz.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\kronsz.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\kronsz.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\kronuz.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\kronuz.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\kronuz.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\kronzs.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\kronzs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\kronzs.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\kronzu.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\kronzu.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\kronzu.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\lcm.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\lcm.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\lcm.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\lcm_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\lcm_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\lcm_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\lshift.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\lshift.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\lshift.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\lucnum2_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\lucnum2_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\lucnum2_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\lucnum_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\lucnum_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\lucnum_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\md_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\md_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\md_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\memory.c

"$(INTDIR)\memory.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpz\millerrabin.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\millerrabin.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\millerrabin.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\mod.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\mod.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\mod.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mod_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mod_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mod_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mod_34lsub1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mod_34lsub1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mod_34lsub1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mode1o.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mode1o.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mode1o.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\mp_bases.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mp_bases.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mp_bases.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mp_bpl.c

"$(INTDIR)\mp_bpl.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mp_clz_tab.c

"$(INTDIR)\mp_clz_tab.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mp_minv_tab.c

"$(INTDIR)\mp_minv_tab.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mp_set_fns.c

"$(INTDIR)\mp_set_fns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpf\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\mul.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\mul.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mul_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mul_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mul_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\mul_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\mul_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\mul_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\mul_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\mul_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\mul_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mul_basecase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mul_basecase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mul_basecase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mul_fft.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mul_fft.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mul_fft.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\mul_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\mul_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\mul_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\mul_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\mul_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\mul_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\mul_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\mul_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\mul_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\mul_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\mul_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\mul_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\n_pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\n_pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\n_pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\neg.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\neg.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\neg.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\neg.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\neg.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\neg.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\neg.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\neg.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\neg.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\nextprime.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\nextprime.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\nextprime.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\obprintf.c

"$(INTDIR)\obprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\obprntffuns.c

"$(INTDIR)\obprntffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\obvprintf.c

"$(INTDIR)\obvprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE=.\mpz\out_raw.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\out_raw.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\out_raw.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\out_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\out_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\out_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\out_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\out_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\out_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\out_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\out_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\out_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\perfpow.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\perfpow.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\perfpow.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\perfsqr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\perfsqr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\perfsqr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\perfsqr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\perfsqr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\perfsqr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\popcount.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\popcount.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\popcount.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\popcount.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\popcount.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\popcount.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\pow_1.c

"$(INTDIR)\pow_1.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpf\pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\powm.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\powm.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\powm.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\powm_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\powm_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\powm_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\pprime_p.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\pprime_p.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\pprime_p.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\pre_divrem_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\pre_divrem_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\pre_divrem_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\pre_mod_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\pre_mod_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\pre_mod_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\printf.c

"$(INTDIR)\printf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\printffuns.c

"$(INTDIR)\printffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\rand.c

"$(INTDIR)\rand.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randclr.c

"$(INTDIR)\randclr.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randdef.c

"$(INTDIR)\randdef.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randlc.c

"$(INTDIR)\randlc.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randlc2s.c

"$(INTDIR)\randlc2s.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randlc2x.c

"$(INTDIR)\randlc2x.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpn\generic\random.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\random.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\random.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\random.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\random.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\random.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\random2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\random2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\random2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\random2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\random2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\random2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\random2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\random2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\random2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\randraw.c

"$(INTDIR)\randraw.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\rands.c

"$(INTDIR)\rands.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randsd.c

"$(INTDIR)\randsd.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\randsdui.c

"$(INTDIR)\randsdui.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\mpz\realloc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\realloc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\realloc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\realloc2.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\realloc2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\realloc2.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\reldiff.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\reldiff.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\reldiff.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\remove.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\remove.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\remove.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=".\printf\repl-vsnprintf.c"

"$(INTDIR)\repl-vsnprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpz\root.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\root.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\root.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\rootrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\rootrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\rootrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\rrandomb.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\rrandomb.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\rrandomb.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\rshift.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\rshift.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\rshift.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\sb_divrem_mn.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\sb_divrem_mn.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\sb_divrem_mn.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\scan0.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\scan0.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\scan0.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\scan0.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\scan0.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\scan0.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\scan1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\scan1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\scan1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\scan1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\scan1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\scan1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\scanf\scanf.c

"$(INTDIR)\scanf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpf\set.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set_d.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set_d.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_den.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_den.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_den.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_dfl_prec.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_dfl_prec.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_dfl_prec.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_f.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_f.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_f.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set_f.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set_f.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set_f.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_num.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_num.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_num.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_prc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_prc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_prc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_prc_raw.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_prc_raw.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_prc_raw.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set_si.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set_si.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set_str.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set_str.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\set_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\set_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\set_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\set_z.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\set_z.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\set_z.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\set_z.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\set_z.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\set_z.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\setbit.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\setbit.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\setbit.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\size.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\size.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\size.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\size.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\size.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\size.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\sizeinbase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\sizeinbase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\sizeinbase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\snprintf.c

"$(INTDIR)\snprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\snprntffuns.c

"$(INTDIR)\snprntffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\sprintf.c

"$(INTDIR)\sprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\sprintffuns.c

"$(INTDIR)\sprintffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpn\generic\sqr_basecase.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\sqr_basecase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\sqr_basecase.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\sqrt.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\sqrt.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\sqrt.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\sqrt.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\sqrt.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\sqrt.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\sqrt_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\sqrt_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\sqrt_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\sqrtrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\sqrtrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\sqrtrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\sqrtrem.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\sqrtrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\sqrtrem.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\scanf\sscanf.c

"$(INTDIR)\sscanf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\sscanffuns.c

"$(INTDIR)\sscanffuns.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpf\sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\sub_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\sub_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\sub_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\sub_n.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_sub_n" /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\sub_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_sub_n" /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\sub_n.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\sub_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\sub_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\sub_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\sub_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\sub_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\sub_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\submul_1.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_submul_1" /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\submul_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /D "OPERATION_submul_1" /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\submul_1.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\swap.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\swap.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\swap.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpq\swap.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpq/" /Fd"Release\mpq/" /FD /c 

"$(INTDIR)\mpq\swap.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpq/" /Fd"Debug\mpq/" /FD /GZ /c 

"$(INTDIR)\mpq\swap.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\swap.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\swap.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\swap.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_q.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_q.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_q_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_q_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_q_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_q_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_q_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_q_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpn\generic\tdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpn/" /Fd"Release\mpn/" /FD /c 

"$(INTDIR)\mpn\tdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpn/" /Fd"Debug\mpn/" /FD /GZ /c 

"$(INTDIR)\mpn\tdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_qr.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_qr.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_qr_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_qr_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_qr_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_r.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_r.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_r.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_r_2exp.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_r_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_r_2exp.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_r_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_r_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_r_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tdiv_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tdiv_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tdiv_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\trunc.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\trunc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\trunc.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\tstbit.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\tstbit.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\tstbit.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\ui_div.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\ui_div.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\ui_div.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\ui_pow_ui.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\ui_pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\ui_pow_ui.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\ui_sub.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\ui_sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\ui_sub.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpf\urandomb.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpf/" /Fd"Release\mpf/" /FD /c 

"$(INTDIR)\mpf\urandomb.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpf/" /Fd"Debug\mpf/" /FD /GZ /c 

"$(INTDIR)\mpf\urandomb.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\urandomb.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\urandomb.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\urandomb.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\mpz\urandomm.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\urandomm.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\urandomm.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\printf\vasprintf.c

"$(INTDIR)\vasprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\version.c

"$(INTDIR)\version.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"


SOURCE=.\printf\vfprintf.c

"$(INTDIR)\vfprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\vfscanf.c

"$(INTDIR)\vfscanf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\vprintf.c

"$(INTDIR)\vprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\vscanf.c

"$(INTDIR)\vscanf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\vsnprintf.c

"$(INTDIR)\vsnprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\printf\vsprintf.c

"$(INTDIR)\vsprintf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\scanf\vsscanf.c

"$(INTDIR)\vsscanf.obj" : "$(INTDIR)" $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\mpz\xor.c

!IF  "$(CFG)" == "gmp - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Release/gmp.pch" /YX /Fo"Release\mpz/" /Fd"Release\mpz/" /FD /c 

"$(INTDIR)\mpz\xor.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "gmp - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D __STDC__=0 /D "HAVE_CONFIG_H" /D quad_t=__int64 /D intmax_t=__int64 /Fp"Debug/gmp.pch" /YX /Fo"Debug\mpz/" /Fd"Debug\mpz/" /FD /GZ /c 

"$(INTDIR)\mpz\xor.obj" : "$(INTDIR)" $(SOURCE)
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

