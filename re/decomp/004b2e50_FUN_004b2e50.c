// FUN_004b2e50 @ 004b2e50 size=119 sig=undefined FUN_004b2e50() cc=unknown
// callers: FUN_004b3168,FUN_004b3028,FUN_004b30c8,FUN_004b035c
// callees: FUN_004b02a8,FUN_004b3208,strlen,FUN_004a9090

int * FUN_004b2e50(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_2c;
  
  FUN_004a9090();
  iVar1 = FUN_004b02a8(0x12);
  if (iVar1 != 0) {
    if (param_2 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = strlen(param_2,0,0,0);
    }
    FUN_004b3208(iVar1,param_2,uVar2);
  }
  *param_1 = iVar1;
  *unaff_FS_OFFSET = local_2c;
  return param_1;
}

