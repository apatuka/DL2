// FUN_004a1555 @ 004a1555 size=178 sig=undefined FUN_004a1555() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0048a3ef,FUN_0048a333,FUN_00496199

void FUN_004a1555(int param_1,int param_2,int param_3)

{
  uint *puVar1;
  int iVar2;
  
  if ((param_3 < 0) || (2 < param_3)) {
    if (*(int *)(param_2 + 0x118) != 0) {
      if (param_3 == 0x80) {
        FUN_0048a3ef(*(undefined4 *)(param_2 + 0x118));
      }
      else if (param_3 == 0x81) {
        puVar1 = (uint *)(*(int *)(param_2 + 0x118) + 0xc);
        *puVar1 = *puVar1 | 2;
        *(undefined4 *)(param_2 + 0x118) = 0;
      }
    }
  }
  else {
    iVar2 = *(int *)(param_2 + 0x10c + param_3 * 4);
    if (iVar2 == -1) {
      iVar2 = *(int *)(param_1 + 0x120 + param_3 * 4);
    }
    if (iVar2 != -1) {
      if (*(int *)(param_2 + 0x118) != 0) {
        FUN_0049eb44(param_1,param_2,2,0x3d,0x81,0);
      }
      if (DAT_0069eea0 != 0) {
        iVar2 = FUN_00496199(0,iVar2);
        *(int *)(param_2 + 0x118) = iVar2;
        if (iVar2 != 0) {
          FUN_0048a333(*(undefined4 *)(param_2 + 0x118),0);
        }
      }
    }
  }
  return;
}

