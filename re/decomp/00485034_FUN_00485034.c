// FUN_00485034 @ 00485034 size=278 sig=undefined FUN_00485034() cc=unknown
// callers: SpyCaught
// callees: FUN_00484fa0,FUN_00441388,FUN_00416e70

int FUN_00485034(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 local_c;
  int local_8;
  
  local_8 = (int)*(short *)(&DAT_0055a0a0 +
                           (char)(&DAT_0059f162)[*(char *)(param_1 + 8) * 0x2d8] * 2) +
            (int)*(short *)(&DAT_0055a0ae +
                           (char)(&DAT_0059f162)[*(char *)(param_2 + 0x20) * 0x2d8] * 2);
  local_c = 0;
  for (iVar2 = *(int *)(param_2 + 0x76); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
    if ((*(char *)(iVar2 + 0x25) == '\n') &&
       (iVar3 = FUN_00416e70(iVar2,10,(int)(char)(&DAT_0059f162)[*(char *)(iVar2 + 8) * 0x2d8]),
       iVar3 != 0)) {
      iVar3 = FUN_00484fa0(iVar2,&local_c);
      local_8 = local_8 + iVar3 + 10;
    }
  }
  for (iVar2 = *(int *)(param_2 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
    cVar1 = (&DAT_0059f162)[*(char *)(iVar2 + 8) * 0x2d8];
    if (((*(char *)(iVar2 + 0x25) == '\n') &&
        (iVar3 = FUN_00441388((int)*(char *)(iVar2 + 8),(int)*(char *)(param_2 + 0x20),2),
        iVar3 != 0)) && (iVar3 = FUN_00416e70(iVar2,10,(int)cVar1), iVar3 != 0)) {
      iVar3 = FUN_00484fa0(iVar2,&local_c);
      local_8 = local_8 + iVar3 + 10;
    }
  }
  return local_8;
}

