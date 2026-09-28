// FUN_0041b71c @ 0041b71c size=446 sig=undefined FUN_0041b71c() cc=unknown
// callers: FUN_0041be6c
// callees: FUN_0044ba40,FUN_0041b500,FUN_0049eb44,FUN_0044c754,FUN_0044b7d8,sprintf
// strings: \"%s\\n%d / %d \\n%s\"|\"%s\\n%d / %d \\n%d\"|\"House Populace\"|\"%s\\n%d / %d\"

void FUN_0041b71c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_120 [28];
  undefined1 local_104 [256];
  
  iVar1 = DAT_0053b850;
  switch(*(undefined4 *)(param_1 + 0x30)) {
  case 10:
    FUN_0041b500(1,local_120,0x19);
    iVar1 = DAT_0053b850;
    puVar4 = local_120;
    uVar2 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,s__s__d____d__s_004b789d,(&PTR_s__00509178)[*(char *)(iVar1 + 0x2c)],
            *(undefined4 *)(iVar1 + 0x18),uVar2,puVar4);
    break;
  case 0xd:
    uVar2 = DAT_0053b858;
    uVar3 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,s__s__d____d__d_004b78ac,(&PTR_s__00509178)[*(char *)(iVar1 + 0x2d)],
            *(undefined4 *)(iVar1 + 0x1c),uVar3,uVar2);
    break;
  case 0x10:
    uVar2 = DAT_0053b85c;
    uVar3 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,s__s__d____d__d_004b78ac,(&PTR_s__00509178)[*(char *)(iVar1 + 0x2e)],
            *(undefined4 *)(iVar1 + 0x20),uVar3,uVar2);
    break;
  case 0x13:
    uVar2 = DAT_0053b860;
    uVar3 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,s__s__d____d__d_004b78ac,(&PTR_s__00509178)[*(char *)(iVar1 + 0x2f)],
            *(undefined4 *)(iVar1 + 0x24),uVar3,uVar2);
    break;
  case 0x16:
    uVar2 = DAT_0053b864;
    uVar3 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,s__s__d____d__d_004b78ac,(&PTR_s__00509178)[*(char *)(iVar1 + 0x30)],
            *(undefined4 *)(iVar1 + 0x28),uVar3,uVar2);
    break;
  case 0x19:
    uVar2 = FUN_0044b7d8(DAT_0053b84c);
    uVar3 = FUN_0044c754(DAT_0053b84c);
    sprintf(local_104,s__s__d____d_004b78bb,PTR_s_House_Populace_005091c8,uVar3,uVar2);
  }
  FUN_0049eb44(DAT_004b7758,*(undefined4 *)(param_1 + 0x30),1,0xf,0,local_104);
  return;
}

