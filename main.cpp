#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
class space{
protected:
    double Scenterofmass_x,Scenterofmass_y;
    int mevcut,Swidth,Sheight,Smass;
    class box{
    protected:
        int width,height,density;
        int mass;

        class cords{
        protected:
            double x;
            double y;

        public:
            void setcords(double a,double b){
                x=a;
                y=b;
            }

            double getx(){
                return x;
            }

            double gety(){
                return y;
            }
        };
        cords kose[4];
        cords centerofmass;
    public:
        void setcenterofmass(double x,double y){
             centerofmass.setcords(x,y);
        }

        void setwidth(int en){
            width=en;
        }
        void setheight(int boy){
            width=boy;
        }

        void setdensity(int nev){
            density=nev;
        }

        void setkose(int i,double x,double y){
            kose[i].setcords(x,y);
        }

        void setmass(int mas){
            mass=mas;
        }

        double getcenterofmass_x(){
            return centerofmass.getx();
        }

        double getcenterofmass_y(){
            return centerofmass.gety();
        }

        double getwidth(){
            return width;
        }

        double getheight(){
            return height;
        }

        double getdensity(){
            return density;
        }

        double getkose_x(int i){
            return kose[i].getx();
        }

        int getkose_y(int i){
            return kose[i].gety();
        }

        int getmass(){
            return mass;
        }
    };

 box *kutular;

public:

     space(double en,double boy){
        Swidth=en;
        Sheight=boy;
    }

    void setbox(int en,int boy,int yogunluk,int adet){
            kutular[adet].setwidth(en);
            kutular[adet].setheight(boy);
            kutular[adet].setdensity(yogunluk);
            kutular[adet].setmass(en*boy*yogunluk);
            int cordx,cordy;

            do{

                int randx=Swidth-en;
                int randy=Sheight-boy;
                cordx=(rand()%randx);
                cordy=(rand()%randy);
            }while(uygunmu(cordx,cordy,en,boy,adet));

            kutular[adet].setkose(0,cordx,cordy);
            kutular[adet].setkose(1,cordx+en,cordy);
            kutular[adet].setkose(2,cordx,cordy+boy);
            kutular[adet].setkose(3,cordx+en,cordy+boy);
            kutular[adet].setcenterofmass(cordx+(en/2),cordy+(boy/2));

        }
    bool uygunmu(int x,int y,int en,int boy,int adet){
            bool sonuc=true;
            for(int i=0;i<adet;i++){

                if( ((kutular[i].getcenterofmass_x()+kutular[i].getwidth()/2<x-en/2)&&
                     (kutular[i].getcenterofmass_x()-kutular[i].getwidth()/2>x-en/2)&&
                     (kutular[i].getcenterofmass_y()+kutular[i].getheight()/2<y-boy/2)&&
                     (kutular[i].getcenterofmass_y()-kutular[i].getheight()/2>y-boy/2))||
                    ((kutular[i].getcenterofmass_x()-kutular[i].getwidth()/2>x+en/2)&&
                     (kutular[i].getcenterofmass_x()+kutular[i].getwidth()/2<x+en/2)&&
                     (kutular[i].getcenterofmass_y()-kutular[i].getheight()/2>y+boy/2)&&
                     (kutular[i].getcenterofmass_y()+kutular[i].getheight()/2<y+boy/2))||
                    ((kutular[i].getcenterofmass_x()+kutular[i].getwidth()/2<x-en/2)&&
                     (kutular[i].getcenterofmass_x()-kutular[i].getwidth()/2>x-en/2)&&
                     (kutular[i].getcenterofmass_y()+kutular[i].getheight()/2<y+boy/2)&&
                     (kutular[i].getcenterofmass_y()-kutular[i].getheight()/2>y+boy/2))||
                    ((kutular[i].getcenterofmass_x()-kutular[i].getwidth()/2>x+en/2)&&
                     (kutular[i].getcenterofmass_x()+kutular[i].getwidth()/2<x+en/2)&&
                     (kutular[i].getcenterofmass_y()-kutular[i].getheight()/2>y-boy/2)&&
                     (kutular[i].getcenterofmass_y()+kutular[i].getheight()/2<y-boy/2))/*||
                     ((kutular[i].getcenterofmass_x()-kutular[i].getwidth()/2)<=0)||
                     ((kutular[i].getcenterofmass_y()-kutular[i].getheight()/2)<=0)*/
                    )
                    {
                        sonuc=false;   break;
                }
            }
            return !sonuc;
        }

    void fillRandomBox(int adet,int maxboyut,double yogunluk){
        mevcut=adet;
        if(maxboyut*maxboyut*mevcut>Swidth*Sheight){
            cout<<"Istenilen kutular uzayi asabilicegi icin islem yapilmadi"<<endl;
        }
        else{
            kutular=new box[mevcut-1];
            srand(time(NULL));
            for(int i=0;i<mevcut;i++){
                int en=(rand()%maxboyut)+1;
                int boy=(rand()%maxboyut)+1;
                setbox(en,boy,yogunluk,i);
            }

            Scenterofmass_x=kutular[0].getcenterofmass_x();
            Scenterofmass_y=kutular[0].getcenterofmass_y();
            Smass=kutular[0].getmass();
            double alfa,beta;
            for(int i=1;i<mevcut;i++){
                Smass+=kutular[i].getmass();
                alfa=fabs(Scenterofmass_x-kutular[i].getcenterofmass_x());
                if(Scenterofmass_x<=kutular[i].getcenterofmass_x()){
                Scenterofmass_x+=alfa/Smass;
                }
                else{
                Scenterofmass_x=kutular[i].getcenterofmass_x()+alfa/Smass;
                }

                beta=fabs(Scenterofmass_y-kutular[i].getcenterofmass_y());
                if(Scenterofmass_y<=kutular[i].getcenterofmass_y()){
                Scenterofmass_y+=beta/Smass;
                }
                else{
                Scenterofmass_y=kutular[i].getcenterofmass_y()+beta/Smass;
                }
            }
        }
    }

    void printcords(int adet){
        ofstream dosya;
        dosya.open("Space.txt",ios::out|ios::app);
        if(dosya.is_open()){
            for(int i=0;i<adet;i++){
                dosya<<"("<<kutular[i].getcenterofmass_x()<<","<<kutular[i].getcenterofmass_y()<<")  ";
                cout<<"("<<kutular[i].getcenterofmass_x()<<","<<kutular[i].getcenterofmass_y()<<")   ";
            }
        }
        else {cout<<"Dosya acýlamadi"<<endl;}
    }

    void printCenterOfMass(){
        cout<<endl<<"("<<Scenterofmass_x<<","<<Scenterofmass_y<<")"<<endl;
    }

    void newdensity(int nwdnsty,int adet){
            int a,b,c,d;
        for(int i=0;i<adet;i++){
            kutular[i].setdensity(nwdnsty);
            a=kutular[i].getheight();b=kutular[i].getwidth();c=kutular[i].getdensity();
            d=a*b*c;
            kutular[i].setmass(d);
            cout<<kutular[i].getmass()<<d<<endl;
        }

            Scenterofmass_x=kutular[0].getcenterofmass_x();
            Scenterofmass_y=kutular[0].getcenterofmass_y();
            Smass=kutular[0].getmass();
            double alfa,beta;
            for(int i=1;i<mevcut;i++){
                Smass+=kutular[i].getmass();
                alfa=fabs(Scenterofmass_x-kutular[i].getcenterofmass_x());
                if(Scenterofmass_x<=kutular[i].getcenterofmass_x()){
                Scenterofmass_x+=alfa/Smass;
                }
                else{
                Scenterofmass_x=kutular[i].getcenterofmass_x()+alfa/Smass;
                }

                beta=fabs(Scenterofmass_y-kutular[i].getcenterofmass_y());
                if(Scenterofmass_y<=kutular[i].getcenterofmass_y()){
                Scenterofmass_y+=beta/Smass;
                }
                else{
                Scenterofmass_y=kutular[i].getcenterofmass_y()+beta/Smass;
                }
            }
        cout<<"Yeni  agirlik merkezi= ("<<Scenterofmass_x<<","<<Scenterofmass_y<<")"<<endl;
    }
};

int main()
{


space s(30,40);
s.fillRandomBox(10,3,1);
s.printcords(10);
s.printCenterOfMass();
s.newdensity(4,10);

return 0;
}
