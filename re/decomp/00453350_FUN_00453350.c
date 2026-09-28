// FUN_00453350 @ 00453350 size=535 sig=undefined FUN_00453350() cc=unknown
// callers: FUN_00455c88,FUN_00453ec8,FUN_00453c30,FUN_00453d9c,FUN_00454690,FUN_00454160,FUN_004543f8,FUN_00453568
// callees: FUN_00450e04,_DeleteBuilding,FUN_00451410,FUN_00444fd4,FUN_0045328c,FUN_004512f0,FUN_00447da4,FUN_0043d594,DestroyAnim,FUN_00450f60

void FUN_00453350(int *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  if (*(char *)((int)param_1 + 0x1d) != '\0') {
    if (((*(char *)(DAT_0057cdf8 + 0x23 + (uint)*(byte *)((int)param_1 + 0x1e)) != '\0') &&
        ((((cVar1 = (&DAT_004faf87)[param_1[1] * 0x24], cVar1 == '\x01' || (cVar1 == '\a')) ||
          (cVar1 == '\v')) || (cVar1 == '\x06')))) && (param_1[1] != 0x17)) {
      uVar4 = param_2 + 1;
      param_2 = (int)uVar4 >> 1;
      if (param_2 < 0) {
        param_2 = param_2 + (uint)((uVar4 & 1) != 0);
      }
    }
    if (((1 << (*(byte *)((int)param_1 + 0x1e) & 0x1f) & (int)DAT_004fbf62) != 0) &&
       ((&DAT_004faf87)[param_1[1] * 0x24] == '\n')) {
      uVar4 = param_2 + 1;
      param_2 = (int)uVar4 >> 1;
      if (param_2 < 0) {
        param_2 = param_2 + (uint)((uVar4 & 1) != 0);
      }
    }
    *(short *)((int)param_1 + 0x32) = *(short *)((int)param_1 + 0x32) + (short)param_2;
    iVar2 = FUN_00447da4(param_1);
    if (iVar2 <= *(short *)((int)param_1 + 0x32)) {
      iVar2 = FUN_00450f60(param_1);
      if (iVar2 == 0) {
        iVar2 = FUN_00450e04(param_1);
        if (iVar2 == 0) {
          DAT_005649e0 = DAT_005649e0 + -1;
        }
        else {
          DAT_005649e4 = DAT_005649e4 + -1;
        }
      }
      *(undefined1 *)((int)param_1 + 0x1d) = 0;
      FUN_0045328c(param_1);
      if (((&DAT_004faf8d)[param_1[1] * 0x24] != '\x03') &&
         (FUN_004512f0(param_1[10],param_1[0xb]), (&DAT_004faf8d)[param_1[1] * 0x24] == '\x02')) {
        FUN_004512f0(param_1[8],param_1[9]);
      }
      cVar1 = (&DAT_004faf87)[param_1[1] * 0x24];
      if (DAT_004cf850 == 0) {
        if (cVar1 == '\n') {
          FUN_00451410();
          _DeleteBuilding(*(undefined4 *)(DAT_0057cdf8 + 4),(int)*(char *)(*param_1 + 7));
        }
      }
      else {
        if ((cVar1 == '\t') && (param_2 != 0x7f)) {
          iVar2 = param_1[1];
          param_1[1] = 9;
          DestroyAnim(param_1,param_3);
          param_1[1] = iVar2;
        }
        else if (cVar1 == '\x14') {
          DestroyAnim(param_1,1);
        }
        else {
          DestroyAnim(param_1,param_3);
        }
        if (((&DAT_004faf8d)[param_1[1] * 0x24] == '\x03') ||
           ((&DAT_004faf8d)[param_1[1] * 0x24] == '\x02')) {
          FUN_00444fd4(param_1[0xe]);
        }
        if (cVar1 == '\n') {
          FUN_00451410();
          iVar3 = (char)(&DAT_004f9dc5)[param_1[1] * 0x32] * 3 + -1;
          for (iVar2 = param_1[9]; iVar2 < param_1[9] + iVar3; iVar2 = iVar2 + 1) {
            for (iVar5 = param_1[8]; iVar5 < param_1[8] + iVar3; iVar5 = iVar5 + 1) {
              FUN_0043d594(iVar5,iVar2,1);
            }
          }
        }
      }
    }
  }
  return;
}

