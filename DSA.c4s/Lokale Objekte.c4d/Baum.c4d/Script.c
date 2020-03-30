/*-- Jahreszeiten Baum --*/

#strict
static season;

protected Initialize:
  return(1);

Control:
  if(Inside(GetSeason(),0,15))
{
    SetAction("Year2");
}
  if(Inside(GetSeason(),15,30))
{
    SetAction("Year3");
}
  if(Inside(GetSeason(),30,45))
{
    SetAction("Year4");
}
  if(Inside(GetSeason(),45,61))
{
    SetAction("Year5");
}
  if(Inside(GetSeason(),61,77))
{
    SetAction("Year6");
}
  if(Inside(GetSeason(),77,94))
{
    SetAction("Year7");
}
  if(Inside(GetSeason(),91,100))
{
    SetAction("Year1");
}
  return(1);
