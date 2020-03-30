Initialize:
  SetAction("Los");
  return(1);

Test:
  if(Var(0)=FindObject(HORS,-25,-80,50,160)) return(Erstellen(Var(0)));
  return(1);

Erstellen:

RemoveObject(Par(0));

  return(1);