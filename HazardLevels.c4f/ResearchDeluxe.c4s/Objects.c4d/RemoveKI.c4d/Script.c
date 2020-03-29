/*-- KI entfernen --*/

#strict

protected func Activate(plr) {
  if(Var(0)=FindObject(HK00))
    RemoveObject(Var(0));
  return(Message(Format("Es sind %d KI-Bots aktiv", ObjectCount(HK00))));
}
