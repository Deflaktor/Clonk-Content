Initialize:
  return(1);

gagaga:
  if(Contained()) Call("soeinScheiss");
  return(1);

soeinScheiss:
  SetOwner(GetOwner(Contained()));
  if(Equal(GetID(Contained(this())),WL3A)) Call("Moneymaker");
  if(Equal(GetID(Contained(this())),KR3A)) Call("Moneymaker");
  if(Equal(GetID(Contained(this())),MA3A)) Call("Moneymaker");
  if(Equal(GetID(Contained(this())),KRRA)) Call("Moneymaker");
  return(1);

Moneymaker:
  Sound("cash.wav");
  SetWealth(GetOwner(Contained()),Sum(GetWealth(GetOwner(Contained())),10));
  RemoveObject();
  return(1);
  