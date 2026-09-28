// FUN_004961e8 @ 004961e8 size=102 sig=undefined FUN_004961e8() cc=unknown
// callers: FUN_00482ba0
// callees: FUN_0048e656,FUN_0048a667,FUN_00490ab3
// strings: \"..\\\\src\\\\glsound.c\"

int FUN_004961e8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (((byte)DAT_0051e090 & 2) != 0) {
    iVar1 = FUN_00490ab3(param_1,0x45564157,param_2,0,0xc0000000);
    if (iVar1 != 0) {
      if (*(int *)(DAT_0065eba0 + 0x20) != 1) {
        FUN_0048e656(399,s____src_glsound_c_0051e094);
      }
      if (1 < *(int *)(DAT_0065eba0 + 0x20)) {
        iVar1 = FUN_0048a667(iVar1);
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
      }
    }
  }
  return iVar1;
}

