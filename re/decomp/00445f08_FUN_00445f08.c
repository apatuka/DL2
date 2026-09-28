// FUN_00445f08 @ 00445f08 size=201 sig=undefined FUN_00445f08() cc=unknown
// callers: NetDisbandUnit,SyncDisbandUnit,FUN_00475854,FUN_00485668
// callees: FUN_0046b0e4,FUN_0044ddf4,FUN_0044d1a4,DeleteUnit,FUN_0044c9a0

void FUN_00445f08(int param_1)

{
  char cVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined1 local_38 [4];
  int local_34;
  int local_30 [11];
  
  iVar2 = *(int *)(param_1 + 0x3c);
  if ((*(char *)(param_1 + 6) == '\x19') || (*(char *)(param_1 + 6) == '\x1f')) {
    if (*(char *)(iVar2 + 0x21) == '\0') {
      iVar4 = FUN_0044d1a4(iVar2,0x14,0);
      if (iVar4 == -1) goto LAB_00445f66;
    }
    *(short *)(iVar2 + 0x30) = *(short *)(iVar2 + 0x30) + 100;
    iVar4 = FUN_0046b0e4(iVar2);
    if (iVar4 < *(short *)(iVar2 + 0x30)) {
      uVar3 = FUN_0046b0e4(iVar2);
      *(undefined2 *)(iVar2 + 0x30) = uVar3;
    }
    FUN_0044c9a0(iVar2,1,0,0,0);
  }
LAB_00445f66:
  cVar1 = *(char *)(param_1 + 8);
  FUN_0044ddf4(&DAT_0059f160 + cVar1 * 0x2d8,(int)*(char *)(param_1 + 6),local_38);
  iVar4 = 1;
  (&DAT_0059f16c)[cVar1 * 0xb6] = (&DAT_0059f16c)[cVar1 * 0xb6] + (int)(short)(local_34 >> 1);
  piVar6 = (int *)(iVar2 + 0x3e);
  piVar5 = local_30;
  do {
    iVar2 = *piVar5;
    piVar5 = piVar5 + 1;
    iVar4 = iVar4 + 1;
    *piVar6 = *piVar6 + (int)(short)(iVar2 >> 1);
    piVar6 = piVar6 + 1;
  } while (iVar4 < 0xb);
  DeleteUnit(param_1);
  return;
}

