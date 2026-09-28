// FUN_00471028 @ 00471028 size=63 sig=undefined FUN_00471028() cc=unknown
// callers: FUN_00471068,FUN_00471634,FUN_00471170,FUN_004719a0
// callees: FUN_004ae26c,FUN_00470fc0

bool FUN_00471028(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_18 [20];
  
  iVar1 = FUN_00470fc0(param_1,param_2,local_18,0x14,param_4);
  if (iVar1 != 0) {
    uVar2 = FUN_004ae26c(local_18);
    *param_3 = uVar2;
  }
  return iVar1 != 0;
}

