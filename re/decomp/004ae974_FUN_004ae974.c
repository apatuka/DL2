// FUN_004ae974 @ 004ae974 size=695 sig=undefined FUN_004ae974() cc=unknown
// callers: 
// callees: FUN_004ad674,FUN_004a6c48,FUN_004ae928,memset,FUN_004af8f4
// strings: u\"-INF\"|u\"+INF\"|u\"-NAN\"|u\"+NAN\"

void FUN_004ae974(undefined4 param_1,int param_2,ushort *param_3,ushort param_4,short param_5,
                 undefined4 param_6)

{
  ushort *puVar1;
  int iVar2;
  wchar_t *pwVar3;
  ushort *puVar4;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  ushort *puVar5;
  int iVar6;
  ushort local_68 [44];
  ushort local_10;
  ushort local_e;
  int local_c;
  int local_8;
  
  puVar1 = (ushort *)FUN_004ad674(0xe);
  local_10 = *puVar1;
  if (0x28 < param_2) {
    param_2 = 0x28;
  }
  local_c = param_2;
  local_e = param_4 & 0xdf;
  if (local_e == 0x46) {
    iVar2 = -param_2;
    if (0 < -param_2) {
      param_2 = 0;
      iVar2 = 0;
    }
  }
  else if (param_2 < 1) {
    iVar2 = 1;
  }
  else {
    iVar2 = param_2;
    if (local_e == 0x45) {
      iVar2 = param_2 + 1;
      param_2 = param_2 + 1;
    }
  }
  iVar2 = FUN_004af8f4(param_1,iVar2,&local_8,local_68,param_6);
  if (iVar2 == 0x7fff) {
    if (local_8 == 0) {
      pwVar3 = u__INF_00520fc6;
    }
    else {
      pwVar3 = u__INF_00520fbc;
    }
    FUN_004a6c48(param_3,pwVar3);
    return;
  }
  if (iVar2 == 0x7ffe) {
    if (local_8 == 0) {
      pwVar3 = u__NAN_00520fda;
    }
    else {
      pwVar3 = u__NAN_00520fd0;
    }
    FUN_004a6c48(param_3,pwVar3);
    return;
  }
  puVar1 = param_3;
  if (local_8 != 0) {
    *param_3 = 0x2d;
    puVar1 = param_3 + 1;
  }
  if (local_e != 0x46) {
    if ((local_e != 0x47) || (iVar2 < -3)) goto LAB_004aeb3f;
    iVar6 = param_2;
    if (param_2 == 0) {
      iVar6 = 1;
    }
    if (iVar6 < iVar2) goto LAB_004aeb3f;
  }
  if (iVar2 < 0x29) {
    if (iVar2 < 1) {
      *puVar1 = 0x30;
      puVar1[1] = local_10;
      puVar1 = puVar1 + 2;
      for (iVar6 = iVar2; iVar2 = 0, iVar6 != 0; iVar6 = iVar6 + 1) {
        *puVar1 = 0x30;
        puVar1 = puVar1 + 1;
      }
    }
    iVar6 = 0;
    for (puVar4 = local_68; *puVar4 != 0; puVar4 = puVar4 + 1) {
      *puVar1 = *puVar4;
      puVar5 = puVar1 + 1;
      iVar2 = iVar2 + -1;
      if (iVar2 == 0) {
        *puVar5 = local_10;
        puVar5 = puVar1 + 2;
        iVar6 = iVar6 + 1;
      }
      puVar1 = puVar5;
    }
    if (iVar6 + local_c < param_2) {
      param_2 = param_2 - (iVar6 + local_c);
      memset(puVar1,0x30,param_2);
      puVar1 = puVar1 + param_2;
    }
    else if ((iVar2 != 1) && (param_5 == 0)) {
      puVar1 = (ushort *)FUN_004ae928(CONCAT22(extraout_var_00,param_4),param_3,puVar1);
    }
    if (puVar1 == param_3) {
      *puVar1 = 0x30;
      puVar1 = puVar1 + 1;
    }
    *puVar1 = 0;
    return;
  }
LAB_004aeb3f:
  *puVar1 = local_68[0];
  puVar4 = puVar1 + 1;
  if (local_68[1] == 0) {
    if (param_5 != 0) {
      *puVar4 = local_10;
      puVar4 = puVar1 + 2;
    }
  }
  else {
    *puVar4 = local_10;
    puVar4 = puVar1 + 2;
    puVar1 = local_68 + 2;
    while (local_68[1] != 0) {
      *puVar4 = local_68[1];
      puVar4 = puVar4 + 1;
      local_68[1] = *puVar1;
      puVar1 = puVar1 + 1;
    }
    if (param_5 == 0) {
      puVar4 = (ushort *)FUN_004ae928(CONCAT22(extraout_var,param_4),param_3,puVar4);
    }
  }
  *puVar4 = param_4 & 0x20 | 0x45;
  iVar2 = iVar2 + -1;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
    puVar4[1] = 0x2d;
  }
  else {
    puVar4[1] = 0x2b;
  }
  if (iVar2 < 1000) {
    if (iVar2 < 100) {
      iVar6 = 2;
    }
    else {
      iVar6 = 3;
    }
  }
  else {
    iVar6 = 4;
  }
  puVar4[iVar6 + 2] = 0;
  puVar4 = puVar4 + iVar6 + 2;
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar4 = puVar4 + -1;
    *puVar4 = (short)(iVar2 % 10) + 0x30;
    iVar2 = iVar2 / 10;
  }
  return;
}

