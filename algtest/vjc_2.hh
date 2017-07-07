#include <stdio.h>
#include <math.h>
double func(int k,int r0,int V)
{
    return r0*r0*k+r0*k*k+k*k*k-V;
}
double r,R,H,V;
#define pi 3.141592653
double solve()
{
    return pow(3*V/pi+pow(r,3),1.0/3)-r;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%lf %lf %lf %lf",&r,&R,&H,&V);
        double h;
        if(R!=r)
        {
            double tana=H/(R-r);
            double k=solve();
            h=tana*k;
        }
        else
        {
            h=V/(pi*r*r);
        }
        printf("%.6lf\n",h);
    }
}
