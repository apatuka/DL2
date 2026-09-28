// FUN_0048180c @ 0048180c size=157 sig=undefined FUN_0048180c() cc=unknown
// callers: FUN_00481da0
// callees: FUN_00481c80,FUN_00464620

void FUN_0048180c(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,int param_7)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = param_4;
  local_14 = param_4;
  puVar2 = (undefined4 *)(param_1 + 0x80);
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x7e); iVar3 = iVar3 + 1) {
    pcVar1 = (char *)*puVar2;
    if (param_7 == 0) {
      local_8 = *pcVar1 * param_4 + param_2;
      local_c = pcVar1[1] * param_4 + param_3;
    }
    else {
      FUN_00481c80((int)*pcVar1,(int)pcVar1[1],&local_8,&local_c,&local_10,&local_14,param_4,param_7
                  );
    }
    FUN_00464620(local_8,local_c,local_10,local_14,param_5,param_6);
    puVar2 = puVar2 + 1;
  }
  return;
}

