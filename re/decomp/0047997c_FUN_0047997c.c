// FUN_0047997c @ 0047997c size=175 sig=undefined FUN_0047997c() cc=unknown
// callers: FUN_004782ec
// callees: sprintf,fclose,FUN_00427f04,fopen,FUN_00427e80
// strings: \"NetGame.Sav\"|\"Receiving Game Data\\r%d%% complete\"|\"Load MultiPlayer Game\"

void FUN_0047997c(int param_1)

{
  undefined1 local_54 [80];
  
  DAT_004d59a4 = DAT_004d59a4 | 0x4000;
  if (DAT_004dc310 != 0) {
    fclose(DAT_004dc310);
    DAT_004dc310 = 0;
  }
  DAT_004dc310 = fopen(s_NetGame_Sav_004dc304,&DAT_004dc38a);
  DAT_006535fc = 0;
  DAT_006535f8 = CONCAT22(*(undefined2 *)(param_1 + 0x1a),*(undefined2 *)(param_1 + 0x1c));
  DAT_006535f4 = 0;
  DAT_00653638 = 0;
  sprintf(local_54,PTR_s_Receiving_Game_Data__d___complet_00509c38,0);
  FUN_00427e80(0,PTR_s_Load_MultiPlayer_Game_00509c30,local_54,0,2);
  FUN_00427f04();
  return;
}

