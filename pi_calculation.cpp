//pi_calculation.cpp
#include "pi_calculation.hpp"

namespace mynamespace{

big_real spec_sqrt(big_real n, big_real one) {
    const big_real TWO("2");

    big_real floating_point_precision("10000000000000000");
    big_real t = (n * floating_point_precision) / one;
    t.truncing();
    big_real n_float = t / floating_point_precision;
    big_real x = (floating_point_precision * n_float.sqrt() * one) / floating_point_precision;
    x.truncing();
    big_real n_one = n * one;
    while (true) {
        big_real x_old(x);
        big_real t = n_one / x;
        t.truncing();
        x += t;
        x /= TWO;
        x.truncing();
        if (x == x_old) {
            break;
        }
    }

    return x;
}

big_real pi_chudnovsky(int count) {
    const big_real ONE("1");
    const big_real TWO("2");
    const big_real FREE("3");
    const big_real FIVE("5");
    const big_real SIX("6");

    big_real one(big_real("10").pow(big_real(count + 4)));
    big_real k(ONE);
    big_real a_k(one);
    big_real a_sum(one);
    big_real b_sum;
    big_real C("640320");
    big_real C3_OVER_24 = (C.pow(big_real("3")) / big_real("24"));
    C3_OVER_24.truncing();
    while (true) {
        a_k *= -(SIX * k - FIVE) * (TWO * k - ONE) * (SIX * k - ONE);
        a_k /= (k.pow(FREE) * C3_OVER_24);
        a_k.truncing();
        a_sum += a_k;
        b_sum += (k * a_k);
        k += ONE;
        if (a_k.isZero()) {
            break;
        }
    }
        
    big_real total = big_real("13591409") * a_sum + big_real("545140134") * b_sum;
    big_real pi = (big_real("426880") * spec_sqrt(big_real("10005") * one, one) * one) / total;
    pi.truncing();

    pi.end_cut(4);
    pi.spec_movement();

    return pi;
}

}
