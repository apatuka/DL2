// FUN_0045f608 @ 0045f608 size=91 sig=undefined FUN_0045f608() cc=unknown
// callers: FUN_004618e8,FUN_00461c68
// callees: FUN_00461ff4

int FUN_0045f608(undefined4 param_1)

{
  int iVar1;
  undefined1 local_a0 [88];
  undefined4 local_48;
  int local_44;
  
  iVar1 = FUN_00461ff4(param_1,local_a0,&DAT_00583da4);
  if (iVar1 == 0) {
    if (((DAT_004d5a88 == 0) || (local_44 == 1)) && ((DAT_004d5a88 != 0 || (local_44 == 0)))) {
      iVar1 = 0;
      DAT_00583da8 = local_48;
    }
    else {
      iVar1 = 2;
    }
  }
  return iVar1;
}

