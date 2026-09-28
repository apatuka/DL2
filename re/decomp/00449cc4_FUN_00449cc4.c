// FUN_00449cc4 @ 00449cc4 size=142 sig=undefined FUN_00449cc4() cc=unknown
// callers: FUN_0044ae10,FUN_00458f14,FUN_0041db10,FUN_0044b168,FUN_0044a0e0,FUN_0044ac18,FUN_0044ad14,FUN_0045cd88,FUN_0045b448,FUN_0045c27c,FUN_00419f50,FUN_00421178,FUN_0045c704,FUN_0044b0d4,FUN_0045ca3c,FUN_0044b24c,FUN_0045b094,FUN_0045b970,FUN_0045eadc
// callees: 

int FUN_00449cc4(int param_1,int param_2,int *param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  *param_3 = param_1;
  *param_4 = param_2;
  if (((((DAT_004d59b4 == 1) || (DAT_004d59b4 == 0)) || (DAT_004d59b4 == 0xb)) ||
      ((DAT_004d59b4 == 5 || (DAT_004d59b4 == 0x22)))) || (DAT_004d59b4 == 7)) {
    iVar3 = 0;
    piVar1 = &DAT_004c5450;
    do {
      if (((*piVar1 == 1) && (iVar2 = param_1 - piVar1[2], -1 < iVar2)) &&
         ((iVar2 < piVar1[4] && ((iVar4 = param_2 - piVar1[3], -1 < iVar4 && (iVar4 < piVar1[5])))))
         ) {
        *param_3 = iVar2;
        *param_4 = iVar4;
        return iVar3;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 8;
    } while (iVar3 < 0x33);
  }
  return -1;
}

