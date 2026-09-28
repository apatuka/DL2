// FUN_004382d0 @ 004382d0 size=211 sig=undefined FUN_004382d0() cc=unknown
// callers: FUN_004383a4,FUN_00432014,FUN_00417f0c,FUN_0041ffd4,FUN_0041c418
// callees: 

void FUN_004382d0(int param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  if (((&DAT_004faf87)[param_3 * 0x24] == '\t') || ((&DAT_004faf87)[param_3 * 0x24] == '\x14')) {
    iVar3 = 0;
  }
  else {
    iVar3 = (int)(char)(&DAT_0059f162)[param_2 * 0x2d8];
  }
  sVar1 = *(short *)(&DAT_004faf84 + param_3 * 0x24);
  iVar2 = (int)(char)(&DAT_004faf86)[param_3 * 0x24];
  if (sVar1 < 0xa0) {
    if (sVar1 == 0x9f) {
      *(undefined4 *)(param_1 + 8) = 0x2338;
      *(int *)(param_1 + 0xc) = iVar2 + iVar3 * 7;
    }
    else if (sVar1 == 0x91) {
      *(undefined4 *)(param_1 + 8) = 0x2329;
      *(int *)(param_1 + 0xc) = iVar3;
    }
    else if (sVar1 == 0x98) {
      *(undefined4 *)(param_1 + 8) = 0x232f;
      *(int *)(param_1 + 0xc) = iVar2 + iVar3 * 8;
    }
  }
  else if (sVar1 == 0xa6) {
    *(undefined4 *)(param_1 + 8) = 0x2348;
    *(int *)(param_1 + 0xc) = iVar2 + iVar3 * 0xe;
  }
  else if (sVar1 == 0xad) {
    *(undefined4 *)(param_1 + 8) = 0x2349;
    *(int *)(param_1 + 0xc) = iVar2;
  }
  return;
}

