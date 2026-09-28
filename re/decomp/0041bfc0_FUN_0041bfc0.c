// FUN_0041bfc0 @ 0041bfc0 size=663 sig=undefined FUN_0041bfc0() cc=unknown
// callers: FUN_0041c258
// callees: sprintf,FUN_0049aa64,FUN_0044ba40,FUN_0049a93f,FUN_0049a8ed,FUN_0049eb9f,FUN_00491efa,FUN_00493108,FUN_00491e02
// strings: \"%s\\nLabor Assigned\\t: %d/%d\\nEnergy Use\\t: %d\\n   (when completed)\"|\"%s\\nLabor Assigned\\t: %d/%d\\nEnergy Use\\t: %d\"|\"%s\\nLabor Assigned\\t: %d/%d\\nEnergy Use\\t: %d\\n   (when completed)\\nRun By\\t: %s\"|\"%s\\nLabor Assigned\\t: %d/%d\\nEnergy Use\\t: %d\\nRun By\\t: %s\"

void FUN_0041bfc0(undefined4 param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined1 local_104 [256];
  
  iVar3 = DAT_0053b850;
  iVar4 = 0;
  iVar5 = 0;
  piVar1 = (int *)(DAT_0053b850 + 0x18);
  do {
    iVar5 = iVar5 + *piVar1;
    iVar4 = iVar4 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar4 < 5);
  if (((char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] == DAT_0058f1f4) ||
     (DAT_00583c20 == 0)) {
    if ((*(short *)(DAT_0053b850 + 0x14) == 0) ||
       ((&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32] == '\0')) {
      iVar3 = (int)(char)(&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32];
      if (DAT_0053b33c == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_0044ba40(DAT_0053b850);
      }
      sprintf(local_104,PTR_s__s_Labor_Assigned____d__d_Energy_0050920c,
              *(undefined4 *)(&DAT_004f9dbc + *(char *)(DAT_0053b850 + 4) * 0x32),iVar5,uVar2,iVar3)
      ;
    }
    else {
      iVar4 = (int)(char)(&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32];
      if (DAT_0053b33c == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_0044ba40(DAT_0053b850);
      }
      sprintf(local_104,PTR_s__s_Labor_Assigned____d__d_Energy_00509208,
              *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar3 + 4) * 0x32),iVar5,uVar2,iVar4);
    }
  }
  else if ((*(short *)(DAT_0053b850 + 0x14) == 0) ||
          ((&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32] == '\0')) {
    puVar6 = (&PTR_s_DEFENSE_MIN_004b7830)[*(char *)(DAT_0053b850 + 0xe)];
    iVar4 = (int)(char)(&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32];
    uVar2 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,PTR_s__s_Labor_Assigned____d__d_Energy_00509214,
            *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar3 + 4) * 0x32),iVar5,uVar2,iVar4,puVar6);
  }
  else {
    puVar6 = (&PTR_s_DEFENSE_MIN_004b7830)[*(char *)(DAT_0053b850 + 0xe)];
    iVar4 = (int)(char)(&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32];
    uVar2 = FUN_0044ba40(DAT_0053b850);
    sprintf(local_104,PTR_s__s_Labor_Assigned____d__d_Energy_00509210,
            *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar3 + 4) * 0x32),iVar5,uVar2,iVar4,puVar6);
  }
  local_110 = 0x13;
  local_108 = 0x5f;
  local_114 = 0x98;
  local_10c = 0x15d;
  iVar3 = FUN_0049eb9f(param_1,0);
  if (iVar3 != 0) {
    FUN_00491e02(0x30);
    FUN_00491efa(0xff);
    FUN_0049a8ed();
    FUN_0049aa64(&local_114);
    FUN_00493108(local_104,&local_114,8,0);
    FUN_0049a93f();
  }
  return;
}

