#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;



/* == EXPLICARE ALGORITM ==

Nu am reusit sa gandesc un algoritm 100% ca in cerinta, iar ca punct de plecare masinile sunt primul venit primul servit

Totul se bazeaza pe 3 mari strategii ale firmei, care se impart pe tipul de strategie de la colet

O zi e o iteratie din while(pp), algoritmul calculeaza pentru o zi cine poate lua pachete, cate poate lua, si daca poate

Iteratia se face pe fiecare client (fiecare are cate un colet)

Cand iteratia se incheie, se reseteaza masinile, ramanand la x-ul si y-ul ultimului colet livrat

Pe fiecare colet, masina aleasa se actualizeaza ca si cum a luat pachetul si l-a si livrat, asadar intr-o zi o masina poate lua 4 pachete, iar x-ul si y-ul final este dupa ce le livreaza pe toate

Pentru ca luam iteratie pe colet, masinile se actualizeaza treptat de fiecare data cand au un colet de dus

Am facut constructori/destructori la majoritatea, cele mai mari avand si supraincarcari

M-am gandit tarziu ca tema se putea face si fara mosteniri, dar am vrut sa evidentiez ca scuterul/masina/duba pot face parte din clasa mare vehicul

Desi le-am construit, nu am reusit sa ma gandesc la un algoritm care sa le includa: lista de colete din firma, strategia masinilor

De asemenea nu am reusit sa gandesc un algoritm care sa updateze la ridicarea coletelor schimbarea de strategie a firmei, ci doar la sfarsitul zilei

Unitatea folosita la calcularea strategiilor este redata de cele 2 functii DistVC si DistCD, asadar la intervalul pentru colet o sa se puna valori comparabile cu algoritmul din functii legat de ele

Cel mai aproape de client- DistVC cel mai mic dintre toate masinile care poate lua coletul

Un client are un singur colet

Cea mai rapida livrare - (DistVC+DistCD)/viteza vehiculului

Cel mai putin incarcat - Scadem din masa deja adaugate de alte pachete luate pe parcurs


Pentru colet:

Pana la o secunda din zi - Valoarea se compara cu (DistVC+DistCD)/viteza vehiculului

Interval de preluare - Valoarea se compara cu DistCD/viteza (viteza cu care preda coletul de cand il ia)

Cat mai repede - Merge pe strategiile firmei si ale vehiculului (deci doar pe strategia firmei)

Initializez o singura firma si lucrez cu ea, punand de la inceput cate masini/scutere/dube are, urmand apoi sa testez diferiti vectori de clienti, fiecare cu coletul lui


*/

int DistVC(int x_v, int y_v, int x_c, int y_c, int tip_deplasare) //1 pentru drept, 2 pentru manhattan
{
    int x_dist = abs(x_c-x_v); //Distanta Vehicul-Client
    int y_dist = abs(y_c-y_v);
    if (tip_deplasare==1)
        return sqrt(x_dist*x_dist + y_dist*y_dist);
    else if (tip_deplasare==2)
        return x_dist+y_dist;
}
int DistCD(int x_c, int y_c, int x_d, int y_d, int tip_deplasare)
{
    return DistVC(x_c,y_c,x_d,y_d,tip_deplasare); //Distanta Client-Destinatie Colet
}



class Vehicul
{
private:
    int masa;
    int vol;
    int x;
    int y;
    int strategie;
    int viteza;
    bool ocupat;
    int masa_colet;
    int volum_colet;
    int nr_colete;
public:
    Vehicul(int m,int v,int xd,int yd,int s,int vi,bool o=0)
    {
        masa=m;
        vol=v;
        x=xd;
        y=yd;
        viteza=vi;
        ocupat=o;
        strategie=s;
    }
    Vehicul(const Vehicul &v)
    {
        masa=v.masa;
        vol=v.vol;
        x=v.x;
        y=v.y;
        strategie=v.strategie;
        viteza=v.viteza;
        ocupat=v.ocupat;
        masa_colet=v.masa_colet;
        volum_colet=v.volum_colet;
        nr_colete=v.nr_colete;
    }
    ~Vehicul(){}
    Vehicul();
    void Afisare();
    void ocupare();
    int retx(){return x;}
    int rety(){return y;}
    void setx(int a){x=a;}
    void sety(int a){y=a;}
    bool retocup(){return ocupat;}
    void setocup(){ocupat=1;}
    int retm(){return masa;}
    int retv(){return vol;}
    int retvit(){return viteza;}
    void setmasac(int a){masa_colet=a;}
    int getmasac(){return masa_colet;}
    void setnrc(int a){nr_colete=a;}
    int getnrc(){return nr_colete;}
    void setvolumc(int a){volum_colet=a;}
    int getvolumc(){return volum_colet;}
    void setvolum(int a){vol=a;}
    void setmasa(int a){masa=a;}
    void setstr(int a){strategie=a;}
    int getmasa(){return masa;}
    int getvol(){return vol;}
    int getstr(){return strategie;}
    void reset(){masa_colet=0;nr_colete=0;volum_colet=0;}


    Vehicul& operator = (const Vehicul& ob);

};
Vehicul& Vehicul::operator = (const Vehicul& ob)
{
    if(this!= &ob)
    {
       this->masa=ob.masa;
       this->vol=ob.vol;
       this->x=ob.x;
       this->y=ob.y;
       this->strategie=ob.strategie;
       this->viteza=ob.viteza;
       this->ocupat=ob.ocupat;
       this->masa_colet=ob.masa_colet;
       this->volum_colet=ob.volum_colet;
       this->nr_colete=ob.nr_colete;
    }
    return *this;
}

void Vehicul::ocupare()
{
    ocupat=1;
}
void Vehicul::Afisare()
{
    cout<<"Masa: "<<masa<<"  "<<"Volumul: "<<vol<<"  "<<"poz. x: "<<x<<"  "<<"poz y: "<<y<<"  "<<"Viteza: "<<viteza<<"  "<<"Nr. strategie: "<<strategie<<"  "<<"Ocupat(bool): "<<ocupat<<"  "<<"Masa colete: "<<masa_colet<<"  "<<"Volum colete: "<<volum_colet<<"  "<<"Nr colete: "<<nr_colete<<endl;

}
Vehicul::Vehicul()
{
    masa=0;
    vol=0;
    x=0;
    y=0;
    strategie=0;
    viteza=0;
    ocupat=0;
    masa_colet=0;
    nr_colete=0;
    volum_colet=0;
}
class Scuter: public Vehicul
{
private:
   int tip_deplasare; //1 drept
public:
    Scuter(int m,int v,int xd,int yd,int s,int vi=20,bool o=0, int tip=1):Vehicul(m,v,xd,yd,s,vi,o)
    {
        tip_deplasare=tip;
    }
    Scuter():Vehicul()
    {
        tip_deplasare=1;
    }
    void Afisare()
    {
        Vehicul::Afisare();
        cout<<"Tip Deplasare: "<<tip_deplasare<<endl;
    }
    ~Scuter(){}

    friend istream &operator>> (istream &in, Scuter& a);
    friend ostream &operator<< (ostream &out, Scuter& a);

};
istream &operator>> (istream &in, Scuter& a)
{
    int x;


        cout<<"Introdu masa: ";
        in>>x;
        a.setmasa(x);
        cout<<"Introdu volumul: ";
        in>>x;
        a.setvolum(x);
        cout<<"Introdu coordonata x: ";
        in>>x;
        a.setx(x);
        cout<<"Introdu coordonata y: ";
        in>>x;
        a.sety(x);
        cout<<"Introdu strategia: ";
        in>>x;
        a.setstr(x);
        a.setnrc(0);
        a.setvolumc(0);
        a.setmasac(0);
}
ostream &operator<< (ostream &out, Scuter& a)
{
    out<<"Masa: "<<a.getmasa()<<"  "<<"Volum: "<<a.getvol()<<"  "<<"Coord. x: "<<a.retx()<<"  "<<"Coord. y: "<<a.rety()<<"  "<<"Strategie: "<<a.getstr()<<"  "<<"Viteza: "<<a.retvit()<<"  "<<"E ocupat: "<<a.retocup()<<"  "<<"Masa colete: "<<a.getmasac()<<"  "<<"Volum colete: "<<a.getvolumc()<<"  "<<"Nr. colete: "<<a.getnrc()<<endl;
}

class Masina: public Vehicul
{
private:
   int tip_deplasare; //2 manhattan
public:
    Masina(int m,int v,int xd,int yd,int s,int vi=10,bool o=0, int tip=2):Vehicul(m,v,xd,yd,s,vi,o)
    {
        tip_deplasare=tip;
    }
    Masina():Vehicul()
    {
        tip_deplasare=2;
    }
    void Afisare()
    {
        Vehicul::Afisare();
        cout<<"Tip Deplasare: "<<tip_deplasare<<endl;
    }
    ~Masina(){}




};
class Duba: public Vehicul
{
private:
    int tip_deplasare;//2 manhattan
    bool frigo;
public:
    bool retfrigo(){return frigo;}
    Duba(int m,int v,int xd,int yd,int s,int vi=5,bool o=0, int tip=2, bool fr=0):Vehicul(m,v,xd,yd,s,vi,o)
    {
        tip_deplasare=tip;
        frigo=fr;
    }
    Duba():Vehicul()
    {
        tip_deplasare=2;
        frigo=0;
    }
    void Afisare()
    {
        Vehicul::Afisare();
        cout<<"Tip Deplasare: "<<tip_deplasare<<"  "<<"Este frigorifica: "<<frigo<<endl;
    }
    ~Duba(){}


};
class Colet
{
private:
    int destx;
    int desty;
    int masa_c;
    int volum_c;
    int strategie;//Notam 1 pentru pana la o anumita secunda, 2 pentru interval, 3 pentru cat mai repede
    int interval;
    bool rece;
public:
    Colet(int x, int y, int masa, int volum, int strat,int inter, bool re=0)
    {
        destx=x;
        desty=y;
        masa_c=masa;
        volum_c=volum;
        strategie=strat;
        interval=inter;
        rece=re;
    }
    Colet();
    ~Colet(){}
    void citire();
    void afisare();
    bool retrece(){return rece;}
    int retm(){return masa_c;}
    int retv(){return volum_c;}
    int retdestx(){return destx;}
    int retdesty(){return desty;}
    int getstr(){return strategie;}
    int getint(){return interval;}

};
Colet::Colet()
{
    destx=0;
    desty=0;
    masa_c=0;
    volum_c=0;
    strategie=0;
    interval=0;
    rece=0;
}
void Colet::citire()
{
    cout<<"Introdu poz. x a destinatiei coletului: ";
    cin>>destx;
    cout<<"Introdu poz. y a destinatiei coletului: ";
    cin>>desty;
    cout<<"Introdu masa coletului: ";
    cin>>masa_c;
    cout<<"Introdu volumul coletului: ";
    cin>>volum_c;
    cout<<"Introdu strategia de livrare a coletului(1-pana la un anumit timp din zi)(2-Timp de la preluare)(3-cat mai repede): "; //O sa tratez 1/2 pentru ca 3 se trateaza automat
    cin>>strategie;
    cout<<"Introdu intervalul/ora in functie de strategie: ";
    cin>>interval;
    cout<<"Introdu (1) daca coletul e rece sau (0) daca nu: ";
    cin>>rece;
}
void Colet::afisare()
{
    cout<<"Poz. x a destinatiei coletului: "<<destx<<"  "<<"Poz. y a destinatiei coletului: "<<desty<<"  "<<"Masa coletului: "<<masa_c<<"  "<<"Volumul coletului: "<<volum_c<<"  "<<"Strategia de livrare: "<<strategie<<"  "<<"Intervalul(dupa strategie): "<<interval<<"  "<<"E rece: "<<rece<<endl;
}
class Client
{private:
    int x;
    int y;
    Colet *c;
public:
    Client();
    ~Client();
    void Citire();
    void Afisare();
    int retx(){return x;}
    int rety(){return y;}
    Colet* retc(){return c;}
};
Client::~Client()
{
    delete []c;
}
Client::Client()
{
    x=0;
    y=0;
}
void Client::Citire()
{
    cout<<"Introdu poz. x a clientului: ";
    cin>>x;
    cout<<"Introdu poz. y a clientului: ";
    cin>>y;
    c = new Colet;
    c->citire();
}
void Client::Afisare()
{
    cout<<"Poz. x a clientului: "<<x<<"  "<<"Poz. y a clientului: "<<y<<endl;
    cout<<"Detalii despre coletul clientului: "<<endl;
    c->afisare();
}

class Firma
{
private:
    int nr_scuter;
    int nr_masina;
    int nr_duba;
    int nr_colet;
    Scuter *s;
    Masina *m;
    Duba *d;
    Colet *c;
public:
    Firma();
    ~Firma();
    Firma(int, int, int, int, Scuter*, Masina*, Duba*, Colet*);
    void citire();
    void afisare();
    void coletare(int, Colet);
    int nrscutere(){return nr_scuter;}
    int nrmasini(){return nr_masina;}
    int nrdube(){return nr_duba;}
    void strategia1(Firma*,Client*); //masina cea mai aproape de client
    void strategia2(Firma*,Client*); //masina cu cea mai rapida livrare
    void strategia3(Firma*,Client*); //masina cea mai putin incarcata
    void resetare();

    Firma& operator = (const Firma& ob);

};

Firma& Firma::operator = (const Firma& ob)
{
    if(this!= &ob)
    {
       this->nr_scuter=ob.nr_scuter;
       this->s=new Scuter[ob.nr_scuter];
       this->s=ob.s;
        this->nr_masina=ob.nr_masina;
       this->m=new Masina[ob.nr_masina];
       this->m=ob.m;
        this->nr_duba=ob.nr_duba;
       this->d=new Duba[ob.nr_duba];
       this->d=ob.d;
        this->nr_colet=ob.nr_colet;
       this->c=new Colet[ob.nr_colet];
       this->c=ob.c;
    }
    return *this;
}

Firma::~Firma()
{
    delete []s;
    delete []m;
    delete []d;
    delete []c;
}
void Firma::resetare()
{
    for(int i=0;i<nrscutere();i++)
        {
        s[i].setmasac(0);
        s[i].setvolumc(0);
        s[i].setnrc(0);
        }
        for(int i=0;i<nrmasini();i++)
        {m[i].setmasac(0);
        m[i].setvolumc(0);
        m[i].setnrc(0);

        }
        for(int i=0;i<nrdube();i++)
        {d[i].setmasac(0);
        d[i].setvolumc(0);
        d[i].setnrc(0);

        }

}
void Firma::strategia1(Firma *x, Client *cl)
{
    int minn1=99999,minn2=99999,minn3=99999;
               Scuter *sc=NULL; //verificam care e cel mai aproape de fiecare client si salvam aici;
               Masina *ma=NULL;
               Duba *du=NULL;
               int tc=cl->retc()->getstr(); //Strategia coletului
               int timp=cl->retc()->getint(); //Timpul coletului
               if(tc==1)
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=(a+b)/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=(a+b)/x->m[j].retvit();
                   if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv()&&c<timp)

                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=(a+b)/x->d[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }
               else if(tc==2)
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=b/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=b/x->m[j].retvit();
                   if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv()&&c<timp)

                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=b/x->d[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }
               else
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);

                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv())
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv())

                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);

                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv())
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }


}
void Firma::strategia2(Firma *x, Client *cl)
{
    int minn1=99999,minn2=99999,minn3=99999;
               Scuter *sc=NULL; //verificam care e cel mai aproape de fiecare client si salvam aici;
               Masina *ma=NULL;
               Duba *du=NULL;
               int tc=cl->retc()->getstr(); //Strategia coletului
               int timp=cl->retc()->getint(); //Timpul coletului
               if(tc==1)
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1); //Acum adaugam si distanta de la client la locatia clientului, si impartim la viteza pentru a vedea cine ajunge primul
                   a=(a+b)/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv()&&a<timp)
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   a=(a+b)/x->m[j].retvit();
                    if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv()&&a<timp)
                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   a=(a+b)/x->d[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv()&&a<timp)
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }
               else if(tc==2)
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1); //Acum adaugam si distanta de la client la locatia clientului, si impartim la viteza pentru a vedea cine ajunge primul
                   a=(a+b)/x->s[j].retvit();
                   int c=b/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   a=(a+b)/x->m[j].retvit();
                   int c=b/x->s[j].retvit();
                    if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   a=(a+b)/x->d[j].retvit();
                   int c=b/x->s[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }
               else
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1); //Acum adaugam si distanta de la client la locatia clientului, si impartim la viteza pentru a vedea cine ajunge primul
                   a=(a+b)/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv())
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   a=(a+b)/x->m[j].retvit();
                    if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv())
                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=DistVC(x->m[j].retx(),x->m[j].rety(),cl->retx(),cl->rety(),2);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   a=(a+b)/x->d[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv())
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }

}
void Firma::strategia3(Firma *x, Client *cl)
{
    int minn1=0,minn2=0,minn3=0;
               Scuter *sc=NULL; //verificam care e cel mai aproape de fiecare client si salvam aici;
               Masina *ma=NULL;
               Duba *du=NULL;
               int tc=cl->retc()->getstr(); //Strategia coletului
               int timp=cl->retc()->getint(); //Timpul coletului
               if(tc==1)
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=(x->s[j].retm()-cl->retc()->retm());
                   int d=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=(d+b)/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=x->m[j].retm()-cl->retc()->retm();
                   int d=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=(d+b)/x->s[j].retvit();
                   if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=x->d[j].retm()-cl->retc()->retm();
                   int d=DistVC(x->s[j].retx(),x->s[j].rety(),cl->retx(),cl->rety(),1);
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=(d+b)/x->s[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }
               else if(tc==2)
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=(x->s[j].retm()-cl->retc()->retm());
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=b/x->s[j].retvit();
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=x->m[j].retm()-cl->retc()->retm();
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=b/x->s[j].retvit();
                   if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=x->d[j].retm()-cl->retc()->retm();
                   int b=DistCD(cl->retx(),cl->rety(),cl->retc()->retdestx(),cl->retc()->retdesty(),1);
                   int c=b/x->s[j].retvit();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv()&&c<timp)
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }
               else
               {
                   for(int j=0;j<x->nrscutere();j++)
               {
                   int a=(x->s[j].retm()-cl->retc()->retm());
                   if(a<=minn1&&(x->s[j].retm()-x->s[j].getmasac())>cl->retc()->retm()&&(x->s[j].retv()-x->s[j].getvolumc())>cl->retc()->retv())
                   {
                       minn1=a;
                       sc=&x->s[j];
                   }
               }
               for(int j=0;j<x->nrmasini();j++)
               {
                   int a=x->m[j].retm()-cl->retc()->retm();
                   if(a<=minn2&&(x->m[j].retm()-x->m[j].getmasac())>cl->retc()->retm()&&(x->m[j].retv() - x->m[j].getvolumc())>cl->retc()->retv())
                   {
                       minn2=a;
                       ma=&x->m[j];
                   }
               }
               for(int j=0;j<x->nrdube();j++)
               {
                   int a=x->d[j].retm()-cl->retc()->retm();
                   if(a<=minn3&&cl->retc()->retrece()==x->d[j].retfrigo()&&(x->d[j].retm()-x->d[j].getmasac())>cl->retc()->retm()&&(x->d[j].retv()-x->d[j].getvolumc())>cl->retc()->retv())
                   {
                       minn3=a;
                       du=&x->d[j];
                   }
               }
               if(cl->retc()->retrece()==1&&du!=NULL)
               {
                   du->setocup();
                   du->setmasac(du->getmasac()+cl->retc()->retm());
                   du->setvolumc(du->getvolumc()+cl->retc()->retv());
                   du->setnrc(du->getnrc()+1);
                   du->setx(cl->retc()->retdestx());
                   du->sety(cl->retc()->retdesty());
               }
               else if(cl->retc()->retrece()==1&&du==NULL)
               {
                   cout<<"Client refuzat"<<endl<<endl;
               }
               else
               {
                   if(minn1<=minn2&&minn1<=minn3&&sc!=NULL)
                   {
                       sc->setocup();
                       sc->setmasac(sc->getmasac()+cl->retc()->retm());
                       sc->setvolumc(sc->getvolumc()+cl->retc()->retv());
                       sc->setnrc(sc->getnrc()+1);
                       sc->setx(cl->retc()->retdestx());
                       sc->sety(cl->retc()->retdesty());
                   }
                   else if(minn2<=minn1&&minn2<=minn3&&ma!=NULL)
                   {
                       ma->setocup();
                       ma->setmasac(ma->getmasac()+cl->retc()->retm());
                       ma->setvolumc(ma->getvolumc()+cl->retc()->retv());
                       ma->setnrc(ma->getnrc()+1);
                       ma->setx(cl->retc()->retdestx());
                       ma->sety(cl->retc()->retdesty());
                   }

                    else if(minn3<=minn2&&minn3<=minn1&&du!=NULL)
                    {
                        du->setocup();
                        du->setmasac(du->getmasac()+cl->retc()->retm());
                       du->setvolumc(du->getvolumc()+cl->retc()->retv());
                       du->setnrc(du->getnrc()+1);
                       du->setx(cl->retc()->retdestx());
                       du->sety(cl->retc()->retdesty());
                    }

                    else
                    cout<<"Client refuzat"<<endl<<endl;

               }
               }


}
Firma::Firma()
{
    nr_scuter=0;
    nr_masina=0;
    nr_duba=0;
    nr_colet=0;
    s=NULL;
    m=NULL;
    d=NULL;
    c=NULL;
}
Firma::
Firma::Firma(int sc, int ma, int du, int co, Scuter* a, Masina* b, Duba* r, Colet* o)
{
    nr_scuter=sc;
    nr_masina=ma;
    nr_duba=du;
    nr_colet=co;
    s= new Scuter[sc];
    s=a;
    m= new Masina[ma];
    m=b;
    d=new Duba[du];
    d=r;
    c= new Colet[co];
    c=o;
}

void Firma::citire()
{
    int mas,v,x,y,str,fr;
    cout<<"Introdu numarul de scutere: ";
    cin>>nr_scuter;
    s = new Scuter[nr_scuter];
    for(int i=0;i<nr_scuter;i++)
    {
        cout<<"Introdu masa: ";
        cin>>mas;
        cout<<"Introdu volumul: ";
        cin>>v;
        cout<<"Introdu coordonata x: ";
        cin>>x;
        cout<<"Introdu coordonata y: ";
        cin>>y;
        cout<<"Introdu strategia: ";
        cin>>str;
        s[i]=Scuter(mas,v,x,y,str);
        s[i].setnrc(0);
        s[i].setvolumc(0);
        s[i].setmasac(0);
    }
    cout<<"Introdu numarul de masini: ";
    cin>>nr_masina;
    m=new Masina[nr_masina];
    for(int i=0;i<nr_masina;i++)
    {
        cout<<"Introdu masa: ";
        cin>>mas;
        cout<<"Introdu volumul: ";
        cin>>v;
        cout<<"Introdu coordonata x: ";
        cin>>x;
        cout<<"Introdu coordonata y: ";
        cin>>y;
        cout<<"Introdu strategia: ";
        cin>>str;
        m[i]=Masina(mas,v,x,y,str);
        m[i].setnrc(0);
        m[i].setvolumc(0);
        m[i].setmasac(0);
    }
    cout<<"Introdu numarul de dube: ";
    cin>>nr_duba;
    d=new Duba[nr_duba];
     for(int i=0;i<nr_duba;i++)
    {
        cout<<"Introdu masa: ";
        cin>>mas;
        cout<<"Introdu volumul: ";
        cin>>v;
        cout<<"Introdu coordonata x: ";
        cin>>x;
        cout<<"Introdu coordonata y: ";
        cin>>y;
        cout<<"Introdu strategia: ";
        cin>>str;
        cout<<"Introdu 1 daca e frigorifica sau 0 daca nu e: ";
        cin>>fr;
        d[i]=Duba(mas,v,x,y,str,5,0,2,fr);
        d[i].setnrc(0);
        d[i].setvolumc(0);
        d[i].setmasac(0);
    }
}
void Firma::afisare()
{
    for(int i=0;i<nr_scuter;i++)
        s[i].Afisare();
    for(int i=0;i<nr_masina;i++)
        m[i].Afisare();
    for(int i=0;i<nr_duba;i++)
        d[i].Afisare();

}


int main()
{
   Firma x;
   Client* cl;
   x.citire();
   int pp=1;
   int str;
   int n;
   while(pp)
   {

       cout<<"Introdu numarul de clienti: ";
       cin>>n;
       cl=new Client[n];
       for(int i=0;i<n;i++)
        cl[i].Citire();
       cout<<"Introdu strategia firmei(1-Cel mai aproape de client)(2-Cea mai rapida livrare)(3-Cel mai putin incarcat): ";
       cin>>str;
           if(str==1) //cea mai aproape masina
       {
           for(int i=0;i<n;i++)
           {
               x.strategia1(&x,&cl[i]);
           }
           x.afisare();
       }
       else if(str==2) //cea mai rapida
       {
           for(int i=0;i<n;i++)
           {
               x.strategia2(&x,&cl[i]);
           }
           x.afisare();

       }
       else //cea care are diferenta intre masa sa si cea a obiectului
       {
           for(int i=0;i<n;i++)
           {
               x.strategia3(&x,&cl[i]);
           }
           x.afisare();

       }
       x.resetare();



   }
    return 0;
}
