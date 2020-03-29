/*-- KI hinzufügen --*/

#strict


protected func Activate(plr) {
  GameCall("RelaunchBot");
  return(Message(Format("Es sind %d KI-Bots aktiv", ObjectCount(HK00))));
}
