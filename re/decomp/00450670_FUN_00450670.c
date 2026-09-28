// FUN_00450670 @ 00450670 size=671 sig=undefined FUN_00450670() cc=unknown
// callers: FUN_00450b4c
// callees: FUN_0046ca40,LoadStringA,sprintf,FUN_004505d0

void FUN_00450670(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  uint uVar2;
  undefined1 local_404 [512];
  CHAR local_204 [512];
  
  cVar1 = (&DAT_0059f162)[param_1 * 0x2d8];
  uVar2 = FUN_0046ca40();
  LoadStringA(DAT_0058f19c,
              (int)*(short *)(&DAT_004b5400 + (uVar2 % 3) * 2 + param_3 * 6 + cVar1 * 0x42),
              local_204,0x1ff);
  switch(param_3) {
  case 0:
    sprintf(local_404,local_204,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]],
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_4 * 0x2d8]]);
    break;
  case 1:
    sprintf(local_404,local_204,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]]);
    break;
  case 2:
    sprintf(local_404,local_204,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_4 * 0x2d8]]);
    break;
  case 3:
    if (param_4 == DAT_004cacc4) {
      return;
    }
    DAT_004cacc4 = param_4;
    sprintf(local_404,local_204,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_4 * 0x2d8]]);
    break;
  case 4:
    sprintf(local_404,local_204,(&PTR_s_credits_00509098)[param_4],param_5);
    break;
  case 5:
  case 6:
  case 7:
    sprintf(local_404,local_204,&DAT_005a43d0 + param_4 * 0xadc);
    break;
  case 8:
    sprintf(local_404,local_204,*(undefined4 *)(&DAT_004f9dbc + param_4 * 0x32),
            &DAT_005a43d0 + param_5 * 0xadc);
    break;
  case 9:
    sprintf(local_404,local_204,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_4 * 0x2d8]]);
    break;
  case 10:
    sprintf(local_404,local_204,&DAT_005a43d0 + param_4 * 0xadc);
    break;
  default:
    goto switchD_004506e0_default;
  }
  FUN_004505d0(param_1,param_2,local_404);
switchD_004506e0_default:
  return;
}

