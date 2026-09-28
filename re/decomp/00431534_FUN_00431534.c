// FUN_00431534 @ 00431534 size=417 sig=undefined FUN_00431534() cc=unknown
// callers: FUN_0043210c,FUN_004316d8,CheckSubTech
// callees: FUN_0049eb44,FUN_00483c3c,sprintf
// strings: \"%s\\n%s\\n%s\"|\"%d Cr.\"

void FUN_00431534(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_410 [1024];
  undefined *local_10;
  undefined *local_c;
  undefined *local_8;
  
  iVar1 = param_1 * 0x32;
  uVar2 = FUN_00483c3c(PTR_DAT_004d5988,&DAT_004fbbac + param_1 * 0x19);
  if (*(short *)(&DAT_004fbbd0 + iVar1) == 0) {
    local_8 = &DAT_004c4588;
  }
  else {
    local_8 = *(undefined **)
               ((int)&PTR_s_Nothing_004fbbc0 + *(short *)(&DAT_004fbbd0 + iVar1) * 0x32);
  }
  if (*(short *)(&DAT_004fbbd2 + iVar1) == 0) {
    local_c = &DAT_004c4588;
  }
  else {
    local_c = *(undefined **)
               ((int)&PTR_s_Nothing_004fbbc0 + *(short *)(&DAT_004fbbd2 + iVar1) * 0x32);
  }
  if (*(short *)(&DAT_004fbbd4 + iVar1) == 0) {
    local_10 = &DAT_004c4588;
  }
  else {
    local_10 = *(undefined **)
                ((int)&PTR_s_Nothing_004fbbc0 + *(short *)(&DAT_004fbbd4 + iVar1) * 0x32);
  }
  sprintf(local_410,&DAT_004c458a,*(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar1));
  FUN_0049eb44(DAT_004c42dc,0xf,1,0xf,0,local_410);
  sprintf(local_410,&DAT_004c458d,uVar2);
  FUN_0049eb44(DAT_004c42dc,0x11,1,0xf,0,local_410);
  sprintf(local_410,s__s__s__s_004c4590,local_8,local_c,local_10);
  FUN_0049eb44(DAT_004c42dc,0x13,1,0xf,0,local_410);
  FUN_0049eb44(DAT_004c42dc,0xe,1,0x42,0,param_1 + 999);
  DAT_004c4504 = param_1;
  sprintf(local_410,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
  FUN_0049eb44(DAT_004c42dc,2,1,0xf,0,local_410);
  return;
}

