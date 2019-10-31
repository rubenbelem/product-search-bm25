//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_SCORING_HPP
#define TECHNICAL_TEST_LINX_SCORING_HPP

#include <cmath>

namespace scoring {
    namespace BM25 {
        double k1 = 1.2;
        double k2 = 100;
        double b = 0.75;
        double R = 0.0;

        double score(int n, int f, int qf, int r, int N, int dl, double avdl) {
            double K = k1 * ((1 - b) + b * (((double) dl) / avdl));
            double first = log(((r + 0.5) / (R - r + 0.5)) /
                               ((n - r + 0.5) / (N - n - R + r + 0.5)));
            double second = ((k1 + 1) * f) / (K + f);
            double third = ((k2 + 1) * qf) / (k2 + qf);
            return first * second * third;
        }
    }
}


#endif //TECHNICAL_TEST_LINX_SCORING_HPP
