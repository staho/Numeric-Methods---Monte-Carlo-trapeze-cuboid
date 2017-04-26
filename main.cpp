#include <iostream>

double f(double x){
    return x*x+1;
}
double f(double x, double y){
    return x*x+x*y;
}
double randInInterval(double a, double b){
    double randTemp = (double)(rand())/RAND_MAX*(b-a);
    return randTemp;
}
double area(double xp, double xk, int n){
    double h = (xk-xp)/(double)n;
    double sum = 0.;
    double baseLengthA = f(xp), baseLengthB;
    for(int i = 1; i <= n; i++){
        baseLengthB = f(xp + h*i);
        sum += (baseLengthA + baseLengthB);
        baseLengthA = baseLengthB;
    }
    return sum * 0.5 * h;
}

double volume(double xp, double xk, double yp, double yk, int n){
    double h = (xk-xp)/(double)n;
    double h2 = (yk - yp)/(double)n;
    double sum = 0.;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) {
            sum += f(xp + h * i, yp + h2 * j);
        }
    }
    return sum * h2 * h;
}

int funcIn(double x, double y){
    if((y > 0) && (y <= f(x)))
        return 1;
    else if((y > 0) && (y <= f(x)))
        return -1;

    return 0;
}
int funcIn(double x, double y, double z){
    if((z > 0) && (z <= f(x, y)))
        return 1;
    else if((z > 0) && (z <= f(x, y)))
        return -1;

    return 0;
}
double monteCarloIntegral(double xp, double xk, int n){
    double yp = 0., yk = f(xk);
    double hits = 0.;
    for(int i = 0; i < n; i++){
        double x = xp + randInInterval(xp, xk);
        double y = yp + randInInterval(yp, yk);
        hits += funcIn(x, y);
    }
    return (xk - xp)*(yk - yp)*hits/(double)n;
}
double monteCarloDoubleIntegral(double xp, double xk, double yp, double yk, int n){
    double sum = 0.;
    for(int i = 0; i < n; i++){
        double x = xp + randInInterval(xp, xk);
        double y = yp + randInInterval(yp, yk);
        if(y > 0){
            sum += f(x, y);
        }

    }
    return ((xk - xp)*(yk - yp)/(double)n) * sum;
}
double monteCarloDoubleIntegralII(double xp, double xk, double yp, double yk, int n){
    double zp = 0., zk = f(xk, yk);
    double hits = 0.;

    for(int i = 0; i < n; i++){
        double x = xp + randInInterval(xp, xk);
        double y = yp + randInInterval(yp, yk);
        double z = zp + randInInterval(zp, zk);
        hits += funcIn(x, y, z);
    }
    return (xk - xp)*(yk - yp)*(zk-zp)*hits/(double)n;

}

using namespace std;

int main() {
    double xp = -1, xk = 2;
    cout << "Suma funkcji f(x) dla ilości prób: \n";
    cout << "16: " << fixed << area(xp, xk, 16) << endl;
    cout << "128: " << fixed << area(xp, xk, 128) << endl;
    cout << "1000000: " << fixed << area(xp, xk, 1000000) << endl;

    cout << "Suma funkcji f(x) dla ilości prób (MC): \n";
    cout << "16: " << fixed << monteCarloIntegral(xp, xk, 16) << endl;
    cout << "128: " << fixed << monteCarloIntegral(xp, xk, 128) << endl;
    cout << "1000000: " << fixed << monteCarloIntegral(xp, xk, 1000000) << endl;

    xp = 0; xk = 3;
    double yp = 0., yk = 3.;
    cout << "Suma funkcji f(x) dla ilości prób (MC2): \n";
    cout << "16: " << fixed << monteCarloDoubleIntegral(xp, xk, yp, yk, 16) << endl;
    cout << "128: " << fixed << monteCarloDoubleIntegral(xp, xk, yp, yk,  128) << endl;
    cout << "1000000: " << fixed << monteCarloDoubleIntegral(xp, xk, yp, yk,  1000000) << endl;

    yp = 0.; yk = 3.;
    cout << "Suma funkcji f(x) dla ilości prób (prostopadlo): \n";
    cout << "16: " << fixed << volume(xp, xk, yp, yk, 16) << endl;
    cout << "128: " << fixed << volume(xp, xk, yp, yk,  128) << endl;
    cout << "10000: " << fixed << volume(xp, xk, yp, yk,  10000) << endl;


    cout << "Suma funkcji f(x) dla ilości prób (MC2II): \n";
    cout << "16: " << fixed << monteCarloDoubleIntegralII(xp, xk, yp, yk, 16) << endl;
    cout << "128: " << fixed << monteCarloDoubleIntegralII(xp, xk, yp, yk,  128) << endl;
    cout << "10000: " << fixed << monteCarloDoubleIntegralII(xp, xk, yp, yk,  10000) << endl;

    return 0;
}