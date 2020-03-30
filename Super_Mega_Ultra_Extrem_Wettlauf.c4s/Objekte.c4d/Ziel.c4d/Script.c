#strict

Initialize:
  SetAction("Los");
  return(1);

Test:
  AlleDa();
  while(Var(0)=FindObject(BIK1,-200,-150,400,300,0,0,0,NoContainer())) return(Erstellen(Var(0)));
  return(1);

AlleDa:
  if(Global(0)!=1)
    return(0);
  var fertig = true;
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      if(!Local(i))
        fertig = false;
      --j;
    }
  if(fertig)
    GameOver();
  return(1);

Erstellen:
  var plr;
  plr = GetOwner(Par(0));
  RemoveObject(Par(0));
  SetPosition(32680,100,GetCrew(plr));
  SetGlobal(plr*2+2,32680);
  SetGlobal(plr*2+3,100);
  SetLocal(plr, 1);

  if(Global(0)==1)
    Marathon(plr);
  if(Global(0)==2)
    Punkterennen(plr);
  return(1);

Marathon:
  var plr, gc, alte_zeit, neue_zeit, sek, min;
  plr = Par(0);
  gc = FindObject(_GCR);
  ObjectCall(gc, "GibPunkt", plr);
  alte_zeit = GetPlrExtraData(plr, "DEFP_SMUEW_Rekordzeit");
  if(alte_zeit==0)
    alte_zeit=65535;
  neue_zeit = ObjectCall(gc, "Zeit");
  sek = ObjectCall(gc, "Sekunden");
  min = ObjectCall(gc, "Minuten");
  if(neue_zeit<alte_zeit) {
    if(sek<10) {
      Message("Spieler %s kommt ins Ziel! Zeit: %d:0%d|EIN NEUER PERSÖNLICHER REKORD!", 0, GetPlayerName(Par()), min, sek);
      Message("Zeit: %d:0%d", GetCrew(plr), min, sek);
    } else {
      Message("Spieler %s kommt ins Ziel! Zeit: %d:%d|EIN NEUER PERSÖNLICHER REKORD!", 0, GetPlayerName(Par()), min, sek);
      Message("Zeit: %d:%d", GetCrew(plr), min, sek);
    }
    SetPlrExtraData(plr, "DEFP_SMUEW_Rekordzeit", neue_zeit);
  } else {
    if(sek<10) {
      Message("Spieler %s kommt ins Ziel! Zeit: %d:%d", 0, GetPlayerName(Par()), min, sek);
      Message("Zeit: %d:0%d", GetCrew(plr), min, sek);
    } else {
      Message("Spieler %s kommt ins Ziel! Zeit: %d:%d", 0, GetPlayerName(Par()), min, sek);
      Message("Zeit: %d:0%d", GetCrew(plr), min, sek);
    }
  }
  return(1);

Punkterennen:
  var plr = Par(0);

  Local(plr,gc)++;

  var gc = FindObject(_GCR);

  var bestePunktzahl = 0;
  var besterSpieler = -1;

  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i))  {
      if(Local(i,gc)>bestePunktzahl) {
        bestePunktzahl = Local(i,gc);
        besterSpieler = i;
      }
      --j;
    }

  Message("Spieler %s gewinnt! Clonk %s erhält 1500 Erfahrungspunkte!", 0, GetPlayerName(besterSpieler), GetName(GetCursor(besterSpieler)));
  DoCrewExp(1500, GetCursor(besterSpieler));

  GameOver();
  return(1);