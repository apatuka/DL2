// FUN_00466464 @ 00466464 size=163 sig=undefined FUN_00466464() cc=unknown
// callers: FUN_004669d8
// callees: 

void FUN_00466464(int param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  for (iVar3 = param_3 + -1; iVar3 <= param_3 + 1; iVar3 = iVar3 + 1) {
    for (iVar2 = param_2 + -1; iVar2 <= param_2 + 1; iVar2 = iVar2 + 1) {
      if ((((iVar2 < 0) || (iVar3 < 0)) || (5 < iVar2)) || (5 < iVar3)) {
        if (*(char *)(param_1 + 0x21) == '\x05') {
          uVar4 = 5;
        }
        else {
          uVar4 = 7;
        }
      }
      else {
        uVar4 = (int)*(short *)(param_1 + 0x142 + (iVar3 * 6 + iVar2) * 0x34) & 0xff;
        if (uVar4 == 0xff) {
          uVar4 = 6;
        }
      }
      piVar1 = (int *)(param_4 + uVar4 * 4);
      *piVar1 = *piVar1 + 1;
      if ((param_2 == iVar2) && (iVar3 == param_3)) {
        piVar1 = (int *)(param_4 + uVar4 * 4);
        *piVar1 = *piVar1 + 1;
      }
    }
  }
  return;
}

