// FUN_0049f752 @ 0049f752 size=119 sig=undefined FUN_0049f752() cc=unknown
// callers: FUN_004a2ac6
// callees: 

int * FUN_0049f752(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    piVar1 = param_2;
    if (param_2 == (int *)0x0) {
      if (param_3 == 0) {
        param_2 = *(int **)(*(int *)(param_1 + 300) + 4);
        piVar1 = param_2;
      }
      else {
        param_2 = (int *)**(undefined4 **)(param_1 + 300);
        piVar1 = param_2;
      }
    }
    do {
      if (param_3 == 0) {
        param_2 = (int *)param_2[1];
        if (param_2 == (int *)0x0) {
          param_2 = (int *)**(undefined4 **)(param_1 + 300);
        }
      }
      else {
        param_2 = (int *)*param_2;
        if (param_2 == (int *)0x0) {
          param_2 = *(int **)(*(int *)(param_1 + 300) + 4);
        }
      }
      if ((*(byte *)((int)param_2 + 0x2b) & 1) != 0) {
        return param_2;
      }
    } while (piVar1 != param_2);
  }
  return (int *)0x0;
}

