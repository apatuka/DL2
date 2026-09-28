// FUN_00401a18 @ 00401a18 size=168 sig=undefined FUN_00401a18() cc=unknown
// callers: FUN_0040dbc4
// callees: FUN_004467e8,FUN_0040e1fc,FUN_00447190,FUN_00446b3c

undefined * FUN_00401a18(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined1 local_cc [200];
  
  iVar4 = (int)(char)(&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24];
  DAT_004c5140 = param_1;
  if ((iVar4 == 1) && (*(char *)(param_2 + 0x21) == '\0')) {
    iVar2 = FUN_0040e1fc(param_1,param_2);
    if (iVar2 != 0) {
      iVar4 = 5;
    }
  }
  FUN_00446b3c(*(undefined4 *)(param_1 + 0x38),100,iVar4,(int)(char)*(byte *)(param_1 + 8),
               0x2000 << (*(byte *)(param_1 + 8) & 0x1f));
  puVar6 = local_cc;
  iVar4 = (int)*(char *)(param_1 + 6);
  uVar5 = 0;
  cVar1 = FUN_00447190(param_1);
  iVar4 = FUN_004467e8(param_2,*(undefined4 *)(param_1 + 0x38),(int)*(char *)(param_1 + 8),
                       (int)cVar1,uVar5,iVar4,puVar6);
  if (iVar4 == -1) {
    puVar3 = *(undefined **)(param_1 + 0x38);
  }
  else {
    puVar3 = &DAT_005a43d0 + iVar4 * 0xadc;
  }
  return puVar3;
}

