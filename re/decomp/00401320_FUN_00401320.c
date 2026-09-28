// FUN_00401320 @ 00401320 size=204 sig=undefined FUN_00401320() cc=unknown
// callers: FUN_00401440
// callees: FUN_004467e8,FUN_00447190,FUN_00446b3c

undefined4 FUN_00401320(int param_1,undefined *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_cc [200];
  
  FUN_00446b3c(*(undefined4 *)(param_1 + 0x38),100,
               (int)(char)(&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24],
               (int)(char)*(byte *)(param_1 + 8),0x2000 << (*(byte *)(param_1 + 8) & 0x1f));
  puVar4 = local_cc;
  iVar2 = (int)*(char *)(param_1 + 6);
  uVar3 = 0;
  cVar1 = FUN_00447190(param_1);
  iVar2 = FUN_004467e8(param_2,*(undefined4 *)(param_1 + 0x38),(int)*(char *)(param_1 + 8),
                       (int)cVar1,uVar3,iVar2,puVar4);
  if (iVar2 == -1) {
    uVar3 = 0;
  }
  else if ((*(char *)(param_1 + 7) == '\t') && (param_2 != &DAT_005a43d0 + iVar2 * 0xadc)) {
    uVar3 = 0;
  }
  else if (((*(char *)(param_1 + 7) == '\x03') &&
           (*(char *)(param_1 + 6) < (char)param_2[*(char *)(param_1 + 8) + 0x6d])) ||
          ((*(char *)(param_1 + 7) == '\r' && ('\n' < (char)param_2[*(char *)(param_1 + 8) + 0x6d]))
          )) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

