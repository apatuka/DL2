// FUN_0041532c @ 0041532c size=341 sig=undefined FUN_0041532c() cc=unknown
// callers: FUN_00415484
// callees: FUN_0049eb44,FUN_0044e9e4,sprintf
// strings: \"%s%s %s\"

void FUN_0041532c(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 local_204 [512];
  
  iVar3 = param_1 * 0x34 + DAT_00657de0;
  iVar4 = iVar3 + 0x140;
  uVar1 = (int)*(short *)(iVar3 + 0x142) & 0xff;
  if (uVar1 == 0xff) {
    uVar1 = 6;
  }
  sprintf(local_204,s__s_s__s_004b7078,(&PTR_s__00509150)[*(char *)(iVar3 + 0x144)],
          (&PTR_s_Clear_00509134)[uVar1],(&PTR_DAT_00509054)[*(char *)(DAT_00657de0 + 0x21)]);
  FUN_0049eb44(DAT_004b7074,5,1,0xf,0,local_204);
  uVar5 = 0;
  uVar2 = FUN_0044e9e4(DAT_00657de0,iVar4,0xc,100,1);
  FUN_0049eb44(DAT_004b7074,8,1,0x46,uVar2,uVar5);
  uVar5 = 0;
  uVar2 = FUN_0044e9e4(DAT_00657de0,iVar4,0xd,100,1);
  FUN_0049eb44(DAT_004b7074,0xb,1,0x46,uVar2,uVar5);
  uVar5 = 0;
  uVar2 = FUN_0044e9e4(DAT_00657de0,iVar4,0xf,100,1);
  FUN_0049eb44(DAT_004b7074,0xe,1,0x46,uVar2,uVar5);
  uVar5 = 0;
  uVar2 = FUN_0044e9e4(DAT_00657de0,iVar4,3,100,1);
  FUN_0049eb44(DAT_004b7074,0x11,1,0x46,uVar2,uVar5);
  uVar5 = 0;
  uVar2 = FUN_0044e9e4(DAT_00657de0,iVar4,4,100,1);
  FUN_0049eb44(DAT_004b7074,0x14,1,0x46,uVar2,uVar5);
  return;
}

