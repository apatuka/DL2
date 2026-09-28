// FUN_0049b5b7 @ 0049b5b7 size=77 sig=undefined FUN_0049b5b7() cc=unknown
// callers: 
// callees: FUN_0049b47f,FUN_0049b572

undefined4 FUN_0049b5b7(short *param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if ((((param_2 < 0) || (param_1[2] < param_2)) || (param_3 < 0)) || (param_1[1] < param_3)) {
    uVar1 = 0;
  }
  else if (*param_1 == 3) {
    uVar1 = FUN_0049b47f(param_1,param_2,param_3,param_4);
  }
  else {
    uVar1 = FUN_0049b572(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

