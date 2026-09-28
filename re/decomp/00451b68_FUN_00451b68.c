// FUN_00451b68 @ 00451b68 size=617 sig=undefined FUN_00451b68() cc=unknown
// callers: FUN_0045640c,FUN_00452250,FUN_00456258,FUN_004522c6,FUN_004566c4,FUN_00451de4,FUN_004568c8
// callees: SetRetreat,FUN_00450de0,FUN_00446bf0,FUN_004ae068,FUN_004518f8,FUN_00451550,FUN_00448008,FUN_004512d4,FUN_00450f60,FUN_00450e04,FUN_00451b00,FUN_00447f44,FUN_00447da4

int * FUN_00451b68(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined2 uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  
  cVar1 = (&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24];
  iVar5 = FUN_00446bf0(param_1);
  if ((iVar5 == 0) &&
     ((cVar1 != '\t' || ((int)*(char *)(param_1 + 8) != (int)*(short *)(DAT_0057cdf8 + 8))))) {
    if (DAT_00574348 == DAT_0057434c) {
      piVar6 = (int *)0x0;
    }
    else {
      uVar8 = (DAT_00574348 + 1) % 0x348;
      iVar5 = DAT_00574348 * 0x4c;
      piVar6 = (int *)(&DAT_005649e8 + iVar5);
      DAT_00574348 = uVar8;
      if (*(int *)(DAT_0057cdf8 + 0x78) == 0) {
        *(int **)(DAT_0057cdf8 + 0x74) = piVar6;
      }
      else {
        *(int **)(*(int *)(DAT_0057cdf8 + 0x78) + 0x44) = piVar6;
      }
      *(int **)(DAT_0057cdf8 + 0x78) = piVar6;
      *(undefined4 *)(&DAT_00564a2c + iVar5) = 0;
      *(int *)(&DAT_005649ec + iVar5) = (int)*(char *)(param_1 + 6);
      uVar2 = *(undefined1 *)(param_1 + 8);
      (&DAT_00564a06)[iVar5] = uVar2;
      (&DAT_005649f0)[iVar5] = uVar2;
      *(byte *)(DAT_0057cdf8 + 0xc) =
           *(byte *)(DAT_0057cdf8 + 0xc) | '\x01' << (*(byte *)(param_1 + 8) & 0x1f);
      iVar7 = FUN_00450e04(piVar6);
      if ((iVar7 == 0) || (*(char *)(param_1 + 0x24) != '\x02')) {
        (&DAT_005649f1)[iVar5] = *(undefined1 *)(param_1 + 0x24);
      }
      else {
        (&DAT_005649f1)[iVar5] = 3;
      }
      *(undefined2 *)(&DAT_005649f2 + iVar5) = *(undefined2 *)(param_1 + 0x28);
      *(undefined2 *)(&DAT_005649fe + iVar5) = *(undefined2 *)(param_1 + 0x2c);
      FUN_00447da4(piVar6);
      uVar4 = FUN_004ae068();
      *(undefined2 *)(&DAT_00564a00 + iVar5) = uVar4;
      if (('\0' < *(char *)(param_1 + 0x26)) && (*(short *)(&DAT_00564a00 + iVar5) == 0)) {
        *(undefined2 *)(&DAT_00564a00 + iVar5) = 1;
      }
      if ((((&DAT_0059f169)[*(char *)(param_1 + 8) * 0x2d8] & 1) == 0) &&
         (((&DAT_0059f169)[*(char *)(param_1 + 8) * 0x2d8] & 2) == 0)) {
        (&DAT_00564a04)[iVar5] = 0;
      }
      else {
        (&DAT_00564a04)[iVar5] = 0xff;
      }
      if (cVar1 != '\n') {
        *piVar6 = param_1;
        FUN_00451550(piVar6);
      }
      FUN_004518f8(piVar6);
      (&DAT_00564a05)[iVar5] = 1;
      (&DAT_00564a06)[iVar5] = (&DAT_005649f0)[iVar5];
      *(undefined4 *)(&DAT_00564a10 + iVar5) = *(undefined4 *)(&DAT_005649f4 + iVar5);
      *(undefined4 *)(&DAT_00564a08 + iVar5) = *(undefined4 *)(&DAT_005649f4 + iVar5);
      *(undefined4 *)(&DAT_00564a14 + iVar5) = *(undefined4 *)(&DAT_005649f8 + iVar5);
      *(undefined4 *)(&DAT_00564a0c + iVar5) = *(undefined4 *)(&DAT_005649f8 + iVar5);
      (&DAT_00564a18)[iVar5] = (&DAT_005649fc)[iVar5];
      *(undefined2 *)(&DAT_00564a1a + iVar5) = *(undefined2 *)(&DAT_005649fe + iVar5);
      *(undefined4 *)(&DAT_00564a24 + iVar5) = 0;
      *(undefined4 *)(&DAT_00564a28 + iVar5) = 0;
      uVar2 = FUN_00447f44(piVar6);
      (&DAT_00564a1c)[iVar5] = uVar2;
      uVar2 = FUN_00448008(piVar6);
      (&DAT_00564a1d)[iVar5] = uVar2;
      (&DAT_00564a1e)[iVar5] = 0;
      uVar4 = SetRetreat(piVar6);
      *(undefined2 *)(&DAT_00564a02 + iVar5) = uVar4;
      if (cVar1 == '\t') {
        bVar3 = FUN_00447da4(piVar6);
        *(ushort *)(&DAT_00564a00 + iVar5) = (ushort)bVar3;
        if ((1 << ((&DAT_00564a06)[iVar5] & 0x1f) & (int)DAT_004fc02a) == 0) {
          (&DAT_005649f1)[iVar5] = 0x17;
        }
      }
      FUN_00451b00(piVar6);
      if (((((&DAT_004faf8d)[*(int *)(&DAT_005649ec + iVar5) * 0x24] != '\x03') &&
           (iVar7 = FUN_00450f60(piVar6), iVar7 == 0)) && (*(int *)(&DAT_005649ec + iVar5) != 0x17))
         && (cVar1 != '\n')) {
        FUN_004512d4(*(undefined4 *)(&DAT_00564a08 + iVar5),*(undefined4 *)(&DAT_00564a0c + iVar5));
      }
      iVar5 = FUN_00450f60(piVar6);
      if (iVar5 == 0) {
        iVar5 = FUN_00450de0(piVar6);
        if (iVar5 == 0) {
          DAT_005649e4 = DAT_005649e4 + 1;
        }
        else {
          DAT_005649e0 = DAT_005649e0 + 1;
        }
      }
    }
  }
  else {
    piVar6 = (int *)0x0;
  }
  return piVar6;
}

