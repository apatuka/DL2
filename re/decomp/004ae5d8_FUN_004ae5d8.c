// FUN_004ae5d8 @ 004ae5d8 size=82 sig=undefined FUN_004ae5d8() cc=unknown
// callers: FUN_00469e84,FUN_00462724,FUN_00462864,FUN_004843ac,FUN_0046a700,FUN_00466508,FUN_00462cb4,TestWaitSync,FUN_00462994,FUN_004693b0,FUN_004694c0,FUN_0046a020,FUN_0046686c,FUN_0046a1ac,FUN_0046c9d8,FUN_00463014,FUN_00469744,FUN_00469b2c
// callees: FUN_004b366c

uint FUN_004ae5d8(void)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar2 = FUN_004b366c();
  iVar2 = *(int *)(iVar2 + 0x48);
  iVar3 = FUN_004b366c();
  iVar4 = 0;
  if (iVar2 != 0) {
    iVar4 = iVar2 * 0x4e35;
  }
  lVar1 = (ulonglong)*(uint *)(iVar3 + 0x44) * 0x4e35;
  uVar5 = (uint)lVar1;
  uVar6 = (int)((ulonglong)lVar1 >> 0x20) + *(uint *)(iVar3 + 0x44) * 0x15a + iVar4 +
          (uint)(0xfffffffe < uVar5);
  iVar2 = FUN_004b366c();
  *(uint *)(iVar2 + 0x44) = uVar5 + 1;
  iVar2 = FUN_004b366c();
  *(uint *)(iVar2 + 0x48) = uVar6;
  return uVar6 & 0x7fffffff;
}

