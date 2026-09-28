// FUN_004233e0 @ 004233e0 size=242 sig=undefined FUN_004233e0() cc=unknown
// callers: FUN_004234d4,FUN_00423690
// callees: FUN_004233c4,memset,FUN_004a67ec,FUN_0042278c,strlen

undefined4 FUN_004233e0(int param_1)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  
  if (DAT_0065209c != 0) {
    FUN_004233c4();
    iVar2 = FUN_0042278c(DAT_00651cb4);
    if (*(short *)(&DAT_004fc90c + iVar2 * 0x12) <= param_1) {
      iVar2 = strlen(DAT_00651cb8);
      uVar1 = DAT_00651cb8;
      iVar2 = iVar2 + 1;
      FUN_004a67ec(DAT_00651cb8,DAT_00651cb8 + iVar2,(int)PTR_DAT_004b7b54 - (DAT_00651cb8 + iVar2))
      ;
      PTR_DAT_004b7b54 = PTR_DAT_004b7b54 + -iVar2;
      memset(PTR_DAT_004b7b54,0,iVar2);
      puVar3 = &DAT_00651ccc;
      for (iVar4 = 1; iVar4 <= DAT_0065209c; iVar4 = iVar4 + 1) {
        if (uVar1 < *puVar3) {
          *puVar3 = *puVar3 - iVar2;
        }
        puVar3 = puVar3 + 5;
      }
      FUN_004a67ec(&DAT_00651cb4,&DAT_00651cc8,(DAT_0065209c + -1) * 0x14);
      memset(&DAT_00651ca0 + DAT_0065209c * 0x14,0,0x14);
      DAT_0065209c = DAT_0065209c + -1;
      return 1;
    }
  }
  return 0;
}

