// FUN_00418660 @ 00418660 size=163 sig=undefined FUN_00418660() cc=unknown
// callers: FUN_00418704
// callees: 

void FUN_00418660(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)(char)(&DAT_004faf86)[param_2 * 0x24];
  iVar2 = *(int *)(param_1 + 8);
  cVar1 = (&DAT_0059f162)[DAT_0058f1f4 * 0x2d8];
  if (iVar2 < 0x2339) {
    if (iVar2 == 0x2338) {
      *(undefined4 *)(param_1 + 8) = 0x1f50;
      *(int *)(param_1 + 0xc) = iVar3 + cVar1 * 7;
    }
    else if (iVar2 == 0x2329) {
      *(undefined4 *)(param_1 + 8) = 0x1f41;
      *(int *)(param_1 + 0xc) = (int)cVar1;
    }
    else if (iVar2 == 0x232f) {
      *(undefined4 *)(param_1 + 8) = 0x1f47;
      *(int *)(param_1 + 0xc) = iVar3;
    }
  }
  else if (iVar2 == 0x2348) {
    *(undefined4 *)(param_1 + 8) = 0x1f60;
    *(int *)(param_1 + 0xc) = iVar3;
  }
  else if (iVar2 == 0x2349) {
    *(undefined4 *)(param_1 + 8) = 0x1f61;
    *(int *)(param_1 + 0xc) = iVar3;
  }
  return;
}

