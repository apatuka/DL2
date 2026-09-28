// FUN_00497859 @ 00497859 size=102 sig=undefined FUN_00497859() cc=unknown
// callers: FUN_004978f7,FUN_00497956
// callees: FUN_004974ef,FUN_004a6b00,FUN_004ae26c
// strings: \"false\"

undefined4 FUN_00497859(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_104 [256];
  
  FUN_004974ef(param_1,local_104);
  iVar1 = FUN_004a6b00(local_104,&DAT_0051e165);
  if (iVar1 == 0) {
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_004a6b00(local_104,s_false_0051e16a);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_004ae26c(local_104);
    }
  }
  return uVar2;
}

