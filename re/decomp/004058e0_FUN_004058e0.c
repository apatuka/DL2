// FUN_004058e0 @ 004058e0 size=61 sig=undefined FUN_004058e0() cc=unknown
// callers: FUN_004107ec,FUN_0040d1a4,FUN_0040cdfc,FUN_00408b58,FUN_00408288,FUN_00410558,FUN_00407d60,FUN_004100e0,FUN_0040cffc,FUN_004101d4,FUN_00408f58,FUN_0040d338
// callees: FUN_00405890

int FUN_004058e0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (&DAT_00522294)[param_1 * 0x11];
  while ((iVar2 != 0 && (param_2 != 0))) {
    iVar1 = FUN_00405890(iVar2,param_2);
    if (iVar1 != 0) {
      return iVar2;
    }
    iVar2 = *(int *)(iVar2 + 0x14);
  }
  return 0;
}

