// RunAITurns @ 0045f2d8 size=780 sig=undefined RunAITurns() cc=unknown
// callers: WinMain
// callees: FUN_00482f94,FUN_00449760,MessagePump,FUN_00482f80,FUN_00401990,FUN_00427ee8,FUN_00449fd8,FUN_0044a000,FUN_0045efd0,FUN_0045f214,FUN_00450b20,FUN_00450cb8,FUN_00449fe8,FUN_004229bc,FUN_00423b20,FUN_00404568,FUN_00457b3c,FUN_00449ff0,FUN_00450b4c,FUN_0043aa88,FUN_004437c4,FUN_00427eb4,UpdateWindow,WaitSync,FUN_0045ae00,FUN_0045c67c,FUN_00449f5c,FUN_00423960,FUN_0045f108,FUN_00449dec,FUN_00427f04,FUN_00476ffc
// strings: \"Your silicon-based opponents are considering their strategies.\"|\"Please wait...\"|\"After AI turns\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Runs computer players' turns ("silicon-based opponents") */

void RunAITurns(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  FUN_00457b3c();
LAB_0045f2df:
  do {
    do {
      DAT_004d1bf4 = 0;
      FUN_0045c67c();
      FUN_00482f94(PTR_DAT_004d5988);
      FUN_00449dec();
      FUN_00449f5c();
      FUN_00449fe8();
      FUN_00449ff0();
      FUN_00449fd8();
      FUN_00449760();
      if (DAT_0059f154 == 1) {
        FUN_00450b20();
      }
      FUN_00450cb8();
      FUN_0043aa88();
      bVar2 = false;
      iVar3 = FUN_004229bc();
      if (iVar3 == 0) {
        if ((DAT_0058f1f4 == DAT_004d5a58) || (DAT_0059f154 < 2)) {
          for (DAT_0058f1e8 = 0; DAT_0058f1e8 < DAT_004d5aec; DAT_0058f1e8 = DAT_0058f1e8 + 1) {
            cVar1 = (&DAT_0059f161)[DAT_0058f1e8 * 0x2d8];
            if ((2 < cVar1) && ((&DAT_0059f168)[DAT_0058f1e8 * 0x2d8] == '\0')) {
              if ((!bVar2) && (1 < DAT_0059f154)) {
                FUN_00427eb4(0,PTR_s_Please_wait____0050979c,
                             PTR_s_Your_silicon_based_opponents_are_00509798,0,2);
                FUN_00427f04();
                DAT_004d5a78 = 1;
                UpdateWindow(DAT_004d5974);
              }
              FUN_00401990(&DAT_0059f160 + DAT_0058f1e8 * 0x2d8,&DAT_00521bb4);
              FUN_004437c4(DAT_0058f1e8);
              FUN_00404568(DAT_0058f1e8);
              _DAT_004d5998 = 1;
              (*(code *)(&PTR_DAT_004b5034)[cVar1 * 6])(DAT_0058f1e8);
              _DAT_004d5998 = 0;
              FUN_00476ffc(DAT_0058f1e8);
              bVar2 = true;
            }
            if (DAT_004d1bf4 != 0) {
              FUN_00427ee8();
              goto LAB_0045f2df;
            }
          }
        }
        else {
          FUN_00427eb4(0,PTR_s_Please_wait____0050979c,
                       PTR_s_Your_silicon_based_opponents_are_00509798,0,2);
          FUN_00427f04();
          DAT_004d5a78 = 1;
        }
        WaitSync(s_After_AI_turns_004d1ce6);
        if (1 < DAT_0059f154) {
          FUN_00427ee8();
          DAT_004d5a78 = 0;
        }
      }
      if (DAT_004d5b2c != 0) {
        FUN_0045efd0(DAT_004d5b30);
      }
      if ((DAT_004d598c == 0) && (DAT_0059f154 != 1)) {
        DAT_004b7b40 = 0;
        FUN_00423960();
        if (DAT_004b7b40 != 0) {
          bVar2 = true;
        }
        while (DAT_004b7b40 != 0) {
          MessagePump();
        }
        if ((&DAT_005644fc)[DAT_0058f1f4 * 2] == DAT_0059f154) {
          FUN_0045f214();
          bVar2 = true;
        }
      }
    } while ((DAT_0058f1ec != 0) && (FUN_00423b20(), DAT_004d1bf4 != 0));
    DAT_004d598c = 0;
    if (bVar2) {
      FUN_0044a000();
    }
    iVar3 = FUN_0045f108();
    iVar4 = FUN_0045ae00();
    if (iVar4 <= iVar3) {
LAB_0045f5c9:
      FUN_00450b20();
      DAT_004d1c84 = 0;
      FUN_00482f80(0);
      FUN_00449760();
      return;
    }
    do {
      if (DAT_0058f1ec != 0) goto LAB_0045f5c9;
      iVar3 = FUN_0045f108();
      iVar4 = FUN_0045ae00();
      if (iVar4 <= iVar3) goto LAB_0045f5c9;
      if ((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) {
        FUN_00450b4c();
      }
      iVar3 = MessagePump();
      if (iVar3 != 0) goto LAB_0045f5c9;
    } while (DAT_004d1bf4 == 0);
  } while( true );
}

