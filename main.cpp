#include <iostream>
#include <cmath>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template <class R>
class UnitTest {
public:
    template <class ... T>
    bool test(R (*foo)(T ... args), R result, T ... args) {
        R ret = foo(args...);
        parseRet(ret);

        if(result == ret){
            return true;
        }
        return false;
    }

    template <class ... T>
    void test(R (*foo)(T ... args), T ... args) {
        R ret = foo(args...);
        parseRet(ret);
    }

    virtual void parseRet(R ret) = 0;
    virtual void resetStats() = 0;
};

struct LinearOutput{
    int branchId = -1;
    int outputType = -1;
    double m1 = 0, m2 = 0;

    bool operator==(const LinearOutput& rhs)
    {
        if(     rhs.outputType == this->outputType &&
                rhs.m1 == this->m1 &&
                rhs.m2 == this->m2 &&
                rhs.branchId == this->branchId) {
            return true;
        }
        else {
            return false;
        }
    }
};

class UTLinearSolver : public UnitTest<LinearOutput>{
private:
    struct TestStats{
        vector<size_t> branchIds;
        vector<size_t> outputTypes;
    };

    int branchAmount = 0;
    int outTypeAmount = 0;

public:
    UTLinearSolver(int branchAmount){
        this->branchAmount = branchAmount;
        this->outTypeAmount = 7;

        for(int i = 0; i < branchAmount; ++i){
            stats.branchIds.push_back(0);
        }
        for(int i = 0; i < outTypeAmount; ++i){
            stats.outputTypes.push_back(0);
        }
    }

    void parseRet(LinearOutput ret) override{
        ++stats.branchIds[ret.branchId];
        ++stats.outputTypes[ret.outputType];
    }

    void resetStats() override{
        for(int i = 0; i < branchAmount; ++i){
            stats.branchIds[i] = 0;
        }
        for(int i = 0; i < outTypeAmount; ++i){
            stats.outputTypes[i] = 0;
        }
    }

    int getBranchAmount(){
        return branchAmount;
    }
    int getOutTypeAmount(){
        return outTypeAmount;
    }

    TestStats stats;
};

LinearOutput solveLinear(double a, double b, double c, double d, double e, double f, bool suspendOutput = false) {
    LinearOutput ret;

    if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
    {
        ret.branchId = 0;
        ret.outputType = 5;
        if(!suspendOutput)
            cout << '5';
    }
    else if ((a * d - c * b != 0) && ((e * d - b * f != 0) || (a * f - c * e != 0)))
    {
        double y = (a * f - c * e) / (a * d - c * b);
        double x = (d * e - b * f) / (d * a - b * c);

        ret.branchId = 1;
        ret.outputType = 2;
        ret.m1 = x;
        ret.m2 = y;
        if(!suspendOutput)
            cout << "2 " << x << ' ' << y;
    }
    else if (((a * d - c * b == 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) ||
        (a == 0 && c == 0 && e / b != f / d) ||
        (b == 0 && d == 0 && e / a != f / c) ||
        (a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0))) {
        if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
            (c == 0 && d == 0 && f == 0 && b != 0 && a == 0)))
        {
            double y;
            if (b == 0){
                ret.branchId = 2;
                y = f / d;
            }
            else if (d == 0){
                ret.branchId = 3;
                y = e / b;
            }
            else if (e == 0 || f == 0){
                ret.branchId = 4;
                y = 0;
            }

            ret.outputType = 4;
            ret.m1 = y;
            if(!suspendOutput)
                cout << '4' << ' ' << y;
        }
        else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
            (c == 0 && d == 0 && f == 0 && a != 0 && b == 0)))
        {
            double x;
            if (a == 0){
                ret.branchId = 5;
                x = f / c;
            }
            else if (c == 0){
                ret.branchId = 6;
                x = e / a;
            }
            else if (e == 0 || f == 0){
                ret.branchId = 7;
                x = 0;
            }

            ret.outputType = 3;
            ret.m1 = x;
            if(!suspendOutput)
                cout << '3' << ' ' << x;
        }
        else {
            ret.branchId = 8;
            ret.outputType = 0;
            if(!suspendOutput)
                cout << '0';
        }
    }
    else if (a == 0 && c == 0)
    {
        double y;
        if (e == 0){
            ret.branchId = 9;
            y = f / d;
        }
        else if (f == 0){
            ret.branchId = 10;
            y = e / b;
        }
        else{
            ret.branchId = 11;
            y = e / b;
        }

        ret.outputType = 4;
        ret.m1 = y;
        if(!suspendOutput)
            cout << '4' << ' ' << y;
    }
    else if (b == 0 && d == 0)
    {
        double x;
        if (e == 0){
            ret.branchId = 12;
            x = f / c;
        }
        else if (f == 0){
            ret.branchId = 13;
            x = e / a;
        }
        else{
            ret.branchId = 14;
            x = e / a;
        }

        ret.outputType = 3;
        ret.m1 = x;
        if(!suspendOutput)
            cout << '3' << ' ' << x;
    }
    else if (b == 0 && e == 0)
    {
        double k, n;
        k = -c / d;
        n = f / d;

        ret.branchId = 15;
        ret.outputType = 1;
        ret.m1 = k;
        ret.m2 = n;
        if(!suspendOutput)
            cout << '1' << ' ' << k << ' ' << n;
    }
    else if (d == 0 && f == 0)
    {
        double k, n;
        k = -a / b;
        n = e / b;

        ret.branchId = 16;
        ret.outputType = 1;
        ret.m1 = k;
        ret.m2 = n;
        if(!suspendOutput)
            cout << '1' << ' ' << k << ' ' << n;
    }
    else if (a == 0 && e == 0)
    {
        double k, n;
        k = -d / c;
        n = f / c;

        ret.branchId = 17;
        ret.outputType = 1;
        ret.m1 = k;
        ret.m2 = n;
        if(!suspendOutput)
            cout << '1' << ' ' << k << ' ' << n;
    }
    else if (c == 0 && f == 0)
    {
        double k, n;
        k = -b / a;
        n = e / a;

        ret.branchId = 18;
        ret.outputType = 1;
        ret.m1 = k;
        ret.m2 = n;
        if(!suspendOutput)
            cout << '1' << ' ' << k << ' ' << n;
    }
    else if ((a / b == c / d))
    {
        double k, n;
        k = -c / d;
        n = f / d;

        ret.branchId = 19;
        ret.outputType = 1;
        ret.m1 = k;
        ret.m2 = n;
        if(!suspendOutput)
            cout << '1' << ' ' << k << ' ' << n;
    }
    else
    {
        ret.branchId = 20;
        ret.outputType = 6;
        if(!suspendOutput)
            cout << "Are you kidding me?";
    }

    return ret;
}

int main()
{
    srand(time(0));

    UTLinearSolver ut(21);

    int counter = 0;
    double from = -50;
    double to = 50;
    //10 is optimal, 5 is long, 3 and less - too long
    double step = 10;

    cout << "start enumeration tests" << endl;

    for(double a = from; a < to; a += step){
        for(double b = from; b < to; b += step){
            for(double c = from; c < to; c += step){
                for(double d = from; d < to; d += step){
                    for(double e = from; e < to; e += step){
                        for(double f = from; f < to; f += step){
                            ut.test(solveLinear, a, b, c, d, e , f, true);
                            ++counter;
                        }
                    }
                }
            }
        }
    }

    cout << "num iterations completed: " << counter << endl;
    cout << "end tests." << endl << endl;

    cout << "stats:" << endl;

    cout << "branches:" << endl;
    for(int i = 0; i < ut.getBranchAmount(); ++i){
        cout << "branchId: " << i << "\ttimes pass: " << ut.stats.branchIds[i] << endl;
    }
    cout << endl;

    cout << "outputTypes:" << endl;
    for(int i = 0; i < ut.getOutTypeAmount(); ++i){
        cout << "outputType: " << i << "\ttimes pass: " << ut.stats.outputTypes[i] << endl;
    }
    cout << endl;

    ut.resetStats();

    cout << "start random double num tests" << endl;

    counter = 0;

    for(double a = from; a < to; a += step){
        for(double b = from; b < to; b += step){
            for(double c = from; c < to; c += step){
                for(double d = from; d < to; d += step){
                    for(double e = from; e < to; e += step){
                        for(double f = from; f < to; f += step){
                            ut.test(solveLinear,
                                    fRand(from, to),
                                    fRand(from, to),
                                    fRand(from, to),
                                    fRand(from, to),
                                    fRand(from, to),
                                    fRand(from, to), true);
                            ++counter;
                        }
                    }
                }
            }
        }
    }

    cout << "num iterations completed: " << counter << endl;
    cout << "end tests." << endl << endl;

    cout << "stats:" << endl;

    cout << "branches:" << endl;
    for(int i = 0; i < ut.getBranchAmount(); ++i){
        cout << "branchId: " << i << "\ttimes pass: " << ut.stats.branchIds[i] << endl;
    }
    cout << endl;

    cout << "outputTypes:" << endl;
    for(int i = 0; i < ut.getOutTypeAmount(); ++i){
        cout << "outputType: " << i << "\ttimes pass: " << ut.stats.outputTypes[i] << endl;
    }
    cout << endl;

    return 0;
}
