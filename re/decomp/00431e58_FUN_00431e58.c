// FUN_00431e58 @ 00431e58 size=255 sig=undefined FUN_00431e58() cc=unknown
// callers: FUN_00476d48,FUN_00476d08
// callees: FUN_00445d30,FUN_00445a04,FUN_00449dec,FUN_00430b04,FUN_00447a40,FUN_0047d3d8

void FUN_00431e58(char *param_1,int param_2,int param_3,undefined2 param_4)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = FUN_00430b04(param_2);
  iVar4 = FUN_00445d30(&DAT_005a43d0 + param_3 * 0xadc,(int)*param_1,
                       *(undefined4 *)(&DAT_004c42f8 + param_2 * 0xe),param_4);
  if ((iVar4 != 0) && (iVar3 <= *(int *)(param_1 + 0xc))) {
    cVar1 = (&DAT_004faf8d)[*(char *)(iVar4 + 6) * 0x24];
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - iVar3;
    *(undefined2 *)(iVar4 + 0x28) = *(undefined2 *)(&DAT_004c42fc + param_2 * 0xe);
    cVar2 = FUN_00447a40((int)*(short *)(iVar4 + 0x28));
    *(short *)(iVar4 + 0x2a) = (short)cVar2;
    *(uint *)(param_1 + 0x42) = *(uint *)(param_1 + 0x42) | 1 << ((byte)param_2 & 0x1f);
    *(ushort *)(iVar4 + 2) = *(ushort *)(iVar4 + 2) | 1;
    if ((cVar1 == '\x01') && ((&DAT_005a43f1)[param_3 * 0xadc] == '\0')) {
      FUN_00445a04(iVar4);
    }
    FUN_0047d3d8((int)*param_1,param_3,3,iVar3);
    if (DAT_004d59b4 == 0) {
      FUN_00449dec();
    }
  }
  return;
}

