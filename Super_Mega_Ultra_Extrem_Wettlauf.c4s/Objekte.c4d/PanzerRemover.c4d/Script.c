Initialize:
  SetAction("Los");
  return(1);

Test:
  if(Var(0)=FindObject(PM7K,-25,-80,50,160)) return(Erstellen(Var(0)));
  if(Var(0)=FindObject(PN7K,-25,-80,50,160)) return(Erstellen(Var(0)));
  return(1);

Erstellen:

RemoveObject(Par(0));

  return(1);