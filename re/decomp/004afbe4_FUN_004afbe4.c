// FUN_004afbe4 @ 004afbe4 size=166 sig=undefined FUN_004afbe4() cc=unknown
// callers: FUN_004ae230
// callees: sprintf,FUN_004b1570,FUN_004ae51c,FUN_004b12c4
// strings: \"%s: %s error\"

float10 FUN_004afbe4(int param_1,undefined4 param_2,undefined8 *param_3,undefined8 *param_4,
                    undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_74 [80];
  int local_24;
  undefined4 local_20;
  undefined8 local_1c;
  undefined8 local_14;
  undefined4 local_c;
  undefined4 uStack_8;
  
  local_24 = param_1;
  local_20 = param_2;
  if (param_3 == (undefined8 *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = *param_3;
  }
  if (param_4 == (undefined8 *)0x0) {
    local_14 = 0;
  }
  else {
    local_14 = *param_4;
  }
  local_c = param_5;
  uStack_8 = param_6;
  iVar1 = (*(code *)PTR_FUN_00520f5c)(&local_24);
  if (iVar1 == 0) {
    sprintf(local_74,s__s___s_error_00521034,param_2,(&PTR_LAB_00520f60)[param_1]);
    if (param_1 - 2U < 3) {
      puVar2 = (undefined4 *)FUN_004b12c4();
      *puVar2 = 0x22;
    }
    else {
      puVar2 = (undefined4 *)FUN_004b12c4();
      *puVar2 = 0x21;
    }
    FUN_004b1570(local_74);
  }
  return (float10)(double)CONCAT44(uStack_8,local_c);
}

