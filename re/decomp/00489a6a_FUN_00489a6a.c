// FUN_00489a6a @ 00489a6a size=78 sig=undefined FUN_00489a6a() cc=unknown
// callers: 
// callees: FUN_004955d8

undefined4 FUN_00489a6a(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) {
    uVar2 = 4;
    if (param_2 == 0) {
      uVar2 = 0;
    }
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0xfffffffb | uVar2;
    iVar1 = FUN_004955d8(param_1);
    if (iVar1 != 0) {
      (**(code **)(param_1 + 0x78))(param_1,1);
      (**(code **)(param_1 + 0x58))(param_1,3);
      return 1;
    }
  }
  return 0;
}

