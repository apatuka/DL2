// FUN_0049fca2 @ 0049fca2 size=140 sig=undefined FUN_0049fca2() cc=unknown
// callers: FUN_00425d68,FUN_00429a04,FUN_0049ba80,FUN_0049ff48,FUN_0042c934,FUN_0049bb73,FUN_0049c710
// callees: FUN_00498aab,FUN_00496c61

bool FUN_0049fca2(int param_1,undefined4 param_2,int param_3,undefined4 param_4,int *param_5,
                 int *param_6)

{
  bool bVar1;
  undefined1 local_10 [4];
  undefined4 local_c;
  int *local_8;
  
  bVar1 = false;
  if (*(int *)(param_1 + 0x38) != 0) {
    if (param_3 == 0) {
      param_3 = *(int *)(param_1 + 0x54);
    }
    if ((*(uint *)(param_1 + 0x24) & 0x1f) == 2) {
      local_c = FUN_00498aab(*(undefined4 *)(param_1 + 0x38),1);
      local_8 = (int *)FUN_00496c61(local_c,param_3,param_2,0,param_4,0,0,local_10);
      bVar1 = local_8 != (int *)0x0;
      if (bVar1) {
        *param_5 = (int)*(short *)(*local_8 + 4);
        *param_6 = (int)*(short *)(*local_8 + 2);
      }
      FUN_00498aab(*(undefined4 *)(param_1 + 0x38),0);
    }
  }
  return bVar1;
}

