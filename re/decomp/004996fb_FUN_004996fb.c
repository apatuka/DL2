// FUN_004996fb @ 004996fb size=77 sig=undefined FUN_004996fb() cc=unknown
// callers: FUN_00499470,FUN_004916e9
// callees: FUN_004989cf,FUN_0048bf93,FUN_00498ba9

int FUN_004996fb(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00498ba9(0xc0);
  if (iVar1 != 0) {
    iVar2 = FUN_0048bf93(iVar1,param_1,param_2,param_3);
    if (iVar2 != 0) {
      *(ushort *)(iVar1 + 0x28) = *(ushort *)(iVar1 + 0x28) | 1;
      *(undefined4 *)(iVar1 + 0xb8) = 0;
      *(undefined4 *)(iVar1 + 0xbc) = 0;
      return iVar1;
    }
    FUN_004989cf(iVar1);
  }
  return 0;
}

