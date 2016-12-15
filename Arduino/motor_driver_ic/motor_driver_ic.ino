int ainp1=1; int inp2=11;
int ainp2=2; int inp2=12;
int aen=3; int ben=5;
int aop1=7; int bop1=13;
int aop2=8; int bop2=14;
int vss=4; int icp=6;
void setup()
{
  pinMode(ainp1,INPUT);
  pinMode(ainp2,INPUT);
  pinMode(binp1,INPUT);
  pinMode(binp2,INPUT);
  pinMode(aop1,0UTPUT);
  pinMode(aop2,OUTPUT);
  pinMode(bop1,OUTPUT);
  pinMode(bop2,OUTPUT);
  pinMode(vss,INPUT);
  pinMode(aen,INPUT);
  pinMode(ben,INPUT);
  pinMode(icp,INPUT);
}
void loop()
{
  if(aen==HIGH)
  {
    if(ainp1==HIGH || ainp2==high)
  
