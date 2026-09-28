// FUN_00436a44 @ 00436a44 size=829 sig=undefined FUN_00436a44() cc=unknown
// callers: FUN_00436db8,FUN_00436ef4,FUN_00437134
// callees: FUN_0049eb44,FUN_0049117e,FUN_0046adac,sprintf,FUN_0046b4d0,FUN_0046ae1c,FUN_004369dc,FUN_0046ac44,FUN_0046d250
// strings: \"%s Colony's Global Tax Rate\"

void FUN_00436a44(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_29c [512];
  undefined1 local_9c [32];
  undefined1 local_7c [8];
  int local_74;
  int local_70;
  
  sprintf(local_29c,PTR_s__s_Colony_s_Global_Tax_Rate_00509b0c,
          (&PTR_s_ChCh_t_00509038)[(char)PTR_DAT_004d5988[2]]);
  FUN_0049eb44(DAT_004c4664,0x11,1,0xf,0,local_29c);
  FUN_0049eb44(DAT_004c4664,0x12,1,0xf,0,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
  sprintf(local_29c,&DAT_004c4668,*(undefined4 *)(&DAT_004d57ec + (char)PTR_DAT_004d5988[0xb] * 4));
  FUN_004369dc(DAT_004c4664,0x14,local_29c,
               *(int *)(&DAT_004d57ec + (char)PTR_DAT_004d5988[0xb] * 4) < 0,0x60);
  FUN_0046ac44(local_7c,DAT_0058f1f4);
  uVar1 = FUN_0046d250(local_74,local_9c);
  uVar2 = FUN_0049117e(0,0x54415453,0xd);
  sprintf(local_29c,uVar2,uVar1);
  FUN_004369dc(DAT_004c4664,0x16,local_29c,local_74 < 0,0x60);
  uVar1 = FUN_0046d250(local_70,local_9c);
  uVar2 = FUN_0049117e(0,0x54415453,0xd);
  sprintf(local_29c,uVar2,uVar1);
  FUN_004369dc(DAT_004c4664,0x18,local_29c,local_70 < 0,0x60);
  puVar4 = local_9c;
  iVar3 = FUN_0046b4d0(DAT_0058f1f4);
  uVar1 = FUN_0046d250(-iVar3,puVar4);
  uVar2 = FUN_0049117e(0,0x54415453,0xd);
  sprintf(local_29c,uVar2,uVar1);
  FUN_004369dc(DAT_004c4664,0x1a,local_29c,-iVar3 < 0,0x60);
  iVar3 = FUN_0046adac(PTR_DAT_004d5988,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
  sprintf(local_29c,&DAT_004c4668,*(undefined4 *)(&DAT_004d57ec + iVar3 * 4));
  uVar1 = 0x60;
  iVar3 = FUN_0046adac(PTR_DAT_004d5988,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
  FUN_004369dc(DAT_004c4664,0x1c,local_29c,*(int *)(&DAT_004d57ec + iVar3 * 4) < 0,uVar1);
  iVar3 = FUN_0046ae1c(PTR_DAT_004d5988,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
  uVar1 = FUN_0046d250(iVar3,local_9c);
  uVar2 = FUN_0049117e(0,0x54415453,0xd);
  sprintf(local_29c,uVar2,uVar1);
  FUN_004369dc(DAT_004c4664,0x1e,local_29c,iVar3 < 0,0x60);
  uVar1 = FUN_0046d250((int)*(short *)(&DAT_005a43fa + DAT_004c5b50 * 0xadc),local_9c);
  uVar2 = FUN_0049117e(0,0x54415453,0xd);
  sprintf(local_29c,uVar2,uVar1);
  FUN_004369dc(DAT_004c4664,0x20,local_29c,*(short *)(&DAT_005a43fa + DAT_004c5b50 * 0xadc) < 0,0x60
              );
  return;
}

