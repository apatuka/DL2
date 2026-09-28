// FUN_004a39f7 @ 004a39f7 size=248 sig=undefined FUN_004a39f7() cc=unknown
// callers: FUN_004a3d26
// callees: FUN_004a33f3,FUN_004a1835,FUN_004a335b,FUN_004a17b0

void FUN_004a39f7(int param_1,int *param_2)

{
  int *piVar1;
  
  while (*param_2 != -1) {
    if (*param_2 == 1000) {
      param_2 = param_2 + 1;
      while (*param_2 != -1) {
        switch(*param_2) {
        default:
          param_2 = (int *)FUN_004a335b(param_2);
          break;
        case 2:
          *(int *)(param_1 + 8) = param_2[1];
          *(int *)(param_1 + 0xc) = param_2[2];
          *(int *)(param_1 + 0x14) = param_2[3];
          *(int *)(param_1 + 0x10) = param_2[4];
          param_2 = param_2 + 5;
          break;
        case 3:
          *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | param_2[1];
          param_2 = param_2 + 2;
          break;
        case 10:
          *(int *)(param_1 + 0x20) = param_2[1];
          param_2 = param_2 + 2;
          break;
        case 0xb:
          piVar1 = param_2 + 1;
          param_2 = param_2 + 2;
          FUN_004a1835(param_1,0,*piVar1);
          break;
        case 0xc:
          *(int *)(param_1 + 0x34) = param_2[1];
          param_2 = param_2 + 2;
          break;
        case 0x12:
          piVar1 = param_2 + 1;
          param_2 = param_2 + 2;
          FUN_004a17b0(param_1,*piVar1);
          break;
        case 0x27:
          *(int *)(param_1 + 0x120) = param_2[1];
          param_2 = param_2 + 2;
          break;
        case 0x28:
          *(int *)(param_1 + 0x124) = param_2[1];
          param_2 = param_2 + 2;
        }
      }
      param_2 = param_2 + 1;
    }
    else {
      param_2 = (int *)FUN_004a33f3(param_2);
    }
  }
  return;
}

