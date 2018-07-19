


#include <iostream>
#include <fstream>
#include "Cia402device.h"
#include "CiA301CommPort.h"
#include "SocketCanPort.h"
#include "math.h"

#include "fcontrol.h"
#include "IPlot.h"



main ()
{
    bool onrobot=true;
    //Controllers
    double dts=0.01;

    //fpi w=25 pm=70 //kept from last experiments.
    vector<double> npi ={0.3354  ,  0.3724  , -1.8968 ,  -0.5654  ,  1.9306};
    vector<double> dpi ={0.2381  ,  0.3986  , -1.0645  , -0.5716  ,  1.0000};

//    //w20p50isom scilab
//    vector<double> npd ={-5310.6413 ,  33607.557 , -52182.099 ,  23885.413};
//    vector<double> dpd ={0. ,  0.221738 , -1.1842456  , 1.};

    //w20p65isom matlab
    vector<double> npd ={16.1209  , -8.1197  ,-92.0813 ,  74.6016  ,172.6901};
    vector<double> dpd ={  -0.1151   , 0.0179  ,  1.3106  ,  2.1779   , 1.0000};

//    SystemBlock pi1(npi,dpi,1);
//    SystemBlock pi3(npi,dpi,1);
//    SystemBlock pi2(npi,dpi,1);

    PIDBlock pi1(100/14,1000/14,0,dts);
    PIDBlock pi2(100/14,1000/14,0,dts);
    PIDBlock pi3(100/14,1000/14,0,dts);

    SystemBlock pd1(npd,dpd,1);
    SystemBlock pd2(npd,dpd,1);
    SystemBlock pd3(npd,dpd,1);



    ofstream targets ("targets.csv");
    ofstream responses ("responses.csv");


        SocketCanPort pm1("can0");
        CiA402Device m1 (1, &pm1);
        SocketCanPort pm2("can0");
        CiA402Device m2 (2, &pm2);
        SocketCanPort pm3("can0");
        CiA402Device m3 (3, &pm3);

        if (onrobot)
        {
//  Remember to switch on before to keep this commented.

//        m1.Reset();
//        m2.Reset();
//        m3.Reset();

//        m1.SwitchOn();
//        sleep(1);
//        m2.SwitchOn();
//        sleep(1);
//        m3.SwitchOn();
//        sleep(1);


        m1.Setup_Torque_Mode();
        m2.Setup_Torque_Mode();
        m3.Setup_Torque_Mode();
    }

//    TableKinematics a;
//    vector<double> lengths(3);
//    long orient=1;
//    long incli=1;

//    a.GetIK(incli,orient,lengths);
//    cout << "l1 " << lengths[0]  << ", l2 " << lengths[1] << ", l3 " << lengths[2]<<endl;
//    double posan1, posan2, posan3;
//    posan1=(0.1-lengths[0])*180/(0.01*M_PI);
//    posan2=(0.1-lengths[1])*180/(0.01*M_PI);
//    posan3=(0.1-lengths[2])*180/(0.01*M_PI);
double posan1, posan2, posan3;
    posan1=30;
    posan2=-posan1/2;
    posan3=-posan1/2;
    cout << "pos1 " << posan1  << ", pos2 " << posan2 << ", pos3 " << posan3 <<endl;




    double ep1,ev1;
    double ep2,ev2;
    double ep3,ev3;

    double interval=3; //in seconds

    pd1.SetSaturation(-30,30);
    pd2.SetSaturation(-30,30);
    pd3.SetSaturation(-30,30);

    m1.SetTorque(0);
    m2.SetTorque(0);
    m3.SetTorque(0);

    for (double t=0;t<interval; t+=dts)
    {
        if (onrobot)
        {


//            cout << t << " , " << m1.GetPosition() << " , " << m2.GetPosition() <<  " , " << m3.GetPosition() <<endl;
//            responses << t << " , " << m1.GetPosition() << " , " << m2.GetPosition() <<  " , " << m3.GetPosition() <<endl;
            cout << t << " , " << m1.GetVelocity() << " , " << m2.GetVelocity() <<  " , " << m3.GetVelocity() <<endl;
            responses << t << " , " << m1.GetVelocity() << " , " << m2.GetVelocity() <<  " , " << m3.GetVelocity() <<endl;

        }
        usleep(dts*1000*1000);
        cout << t << " , " << posan1  << " , " << posan2 << " , " << posan3 << endl;
        targets << t << " , " << posan1  << " , " << posan2 << " , " << posan3 << endl;

    }

    if (onrobot)
    {

        m1.SetTorque(0);
        m2.SetTorque(0);
        m3.SetTorque(0);
     }


}