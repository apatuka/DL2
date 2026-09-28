// FUN_004a7d1c @ 004a7d1c size=209 sig=undefined FUN_004a7d1c() cc=unknown
// callers: 
// callees: FUN_004a7c94,FUN_004010f9,__assertfail
// strings: \"XX.CPP\"|\"__CPPexceptionList\"|\"xdrPtr->xdERRaddr == xl\"

/* WARNING: Unable to track spacebase fully for stack */

void FUN_004a7d1c(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined2 in_FS;
  undefined4 unaff_retaddr;
  
  piVar4 = (int *)FUN_004010f9();
  if (*piVar4 == 0) {
    __assertfail(s___CPPexceptionList_0051f37e,s_XX_CPP_0051f391,0x5d7);
  }
  piVar4 = (int *)FUN_004010f9();
  puVar1 = (undefined4 *)*piVar4;
  puVar5 = (undefined4 *)FUN_004010f9();
  *puVar5 = *puVar1;
  iVar2 = puVar1[10];
  piVar4 = (int *)segment(in_FS,0);
  iVar3 = *piVar4;
  if (iVar3 == 0) {
    __assertfail(&DAT_0051f398,s_XX_CPP_0051f39b,0x5e5);
  }
  if (iVar3 != puVar1[10]) {
    __assertfail(s_xdrPtr_>xdERRaddr____xl_0051f3a2,s_XX_CPP_0051f3ba,0x5e6);
  }
  *(undefined2 *)(iVar2 + 0x10) =
       *(undefined2 *)(*(int *)(iVar2 + 8) + (uint)*(ushort *)(iVar2 + 0x10));
  FUN_004a7c94(puVar1);
  (*(code *)puVar1[7])(puVar1);
  *(undefined4 *)(*(int *)(iVar2 + 0xc) + -4) = unaff_retaddr;
  return;
}

