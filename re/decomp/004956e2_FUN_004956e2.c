// FUN_004956e2 @ 004956e2 size=211 sig=undefined FUN_004956e2() cc=unknown
// callers: FUN_0049585a
// callees: strlen,FUN_004956ba,FUN_004975a1,FUN_004974aa,FUN_004ae26c

undefined4 FUN_004956e2(int *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char local_104;
  char local_103;
  char local_102;
  char local_101;
  
  iVar1 = FUN_004974aa(*param_1,&DAT_0051e084);
  *param_1 = iVar1;
  if (iVar1 != 0) {
    iVar1 = FUN_004975a1(*param_1,&local_104,&DAT_0051e086);
    *param_1 = iVar1;
    iVar1 = FUN_004956ba(&local_104);
    if (iVar1 == 0) {
      iVar1 = strlen(&local_104);
      if (4 < iVar1) {
        return 0;
      }
      if (iVar1 < 4) {
        iVar4 = 0x20;
      }
      else {
        iVar4 = (int)local_101;
      }
      if (iVar1 < 3) {
        iVar3 = 0x20;
      }
      else {
        iVar3 = (int)local_102;
      }
      if (iVar1 < 2) {
        iVar1 = 0x20;
      }
      else {
        iVar1 = (int)local_103;
      }
      *param_2 = iVar4 << 0x18 | iVar3 << 0x10 | iVar1 << 8 | (int)local_104;
    }
    else {
      uVar2 = FUN_004ae26c(&local_104);
      *param_2 = uVar2;
    }
  }
  return 1;
}

