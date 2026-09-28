// FUN_00411d28 @ 00411d28 size=73 sig=undefined FUN_00411d28() cc=unknown
// callers: 
// callees: FUN_00411990,FUN_00411a68

int FUN_00411d28(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_8 [4];
  
  iVar1 = FUN_00411a68(param_1,param_2,local_8);
  if (iVar1 == 0) {
    iVar1 = (**(code **)**(undefined4 **)(param_1 + 0x18))(*(undefined4 **)(param_1 + 0x18),param_2)
    ;
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      FUN_00411990(param_1,param_2,iVar1,0);
    }
  }
  return iVar1;
}

