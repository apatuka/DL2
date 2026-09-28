// FUN_0041244c @ 0041244c size=193 sig=undefined FUN_0041244c() cc=unknown
// callers: FUN_00421b24,FUN_0041e9e8,FUN_00424a84,FUN_00411c64,FUN_0042c50c,FUN_00412654,FUN_0041f198,FUN_00411adc,FUN_0042540c,WaveOut_Init,FUN_00467e58,FUN_0042ee18,FUN_00430cd8
// callees: fread,malloc,FUN_004aa418,FUN_004b1270,FUN_004a6b48

undefined4 FUN_0041244c(undefined4 *param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_14 [8];
  undefined1 local_c;
  undefined4 local_a;
  
  if (param_1[3] == 2) {
    uVar1 = 0;
  }
  else {
    FUN_004a6b48(local_14,param_2,8);
    local_c = 0;
    local_a = 0;
    iVar2 = FUN_004b1270(local_14,*param_1,param_1[1],0xe,&LAB_00411d74);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      iVar2 = FUN_004aa418(param_1[4],*(undefined4 *)(iVar2 + 10),0);
      if (iVar2 == 0) {
        iVar2 = fread(param_3,4,1,param_1[4]);
        if (iVar2 == 1) {
          uVar1 = malloc(*param_3);
          iVar2 = fread(uVar1,1,*param_3,param_1[4]);
          if (iVar2 != *param_3) {
            uVar1 = 0;
          }
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

