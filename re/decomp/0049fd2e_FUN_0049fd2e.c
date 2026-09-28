// FUN_0049fd2e @ 0049fd2e size=213 sig=undefined FUN_0049fd2e() cc=unknown
// callers: FUN_00425d68,FUN_00429a04,FUN_0042a08c,FUN_0042c934,FUN_0049c710
// callees: FUN_00498aab,FUN_0049a93f,FUN_0049a760,FUN_0049a8ed,FUN_0049aa95,FUN_00496c61,FUN_0049aa64

void FUN_0049fd2e(int param_1,int *param_2,int param_3,int param_4,undefined4 param_5,int param_6,
                 undefined4 param_7)

{
  int *piVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 local_c [3];
  byte local_9;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x38) != 0) {
    if (param_6 == 0) {
      param_6 = *(int *)(param_1 + 0x54);
    }
    if ((*(uint *)(param_1 + 0x24) & 0x1f) == 2) {
      local_8 = FUN_00498aab(*(undefined4 *)(param_1 + 0x38),1);
      piVar1 = (int *)FUN_00496c61(local_8,param_6,param_5,0,param_7,0,0,local_c);
      if ((piVar1 != (int *)0x0) && ((local_9 & 0x40) == 0)) {
        uVar2 = 8;
        if ((*(byte *)(*piVar1 + 8) & 3) != 0) {
          uVar2 = 0x10;
        }
        uVar3 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | uVar2);
        FUN_0049a8ed();
        FUN_0049aa64(param_2);
        FUN_0049aa95(*piVar1,*param_2 + param_3,param_2[1] + param_4,(int)*(short *)(*piVar1 + 0xe),
                     0);
        FUN_0049a93f();
        FUN_0049a760(uVar3);
      }
      FUN_00498aab(*(undefined4 *)(param_1 + 0x38),0);
    }
  }
  return;
}

