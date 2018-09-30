#if !defined(RANDOM_H_INCLUDED)
#define RANDOM_H_INCLUDED

/******************************************************************************

MIT License

Copyright (c) 2018 Andrea Griffini

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/

#include <algorithm>
#include <chrono>

thread_local unsigned random_state = unsigned(std::chrono::duration_cast< std::chrono::milliseconds >(
                                                  std::chrono::system_clock::now().time_since_epoch()
                                                  ).count());

inline void rndNext() {
    random_state ^= random_state << 13;
    random_state ^= random_state >> 17;
    random_state ^= random_state << 5;
}

inline unsigned rnd(int max) {
    if (max > (1<<20)) {
        unsigned lim = (1ull<<32) / max * max;
        for(;;) {
            rndNext();
            if (random_state < lim) break;
        }
    } else {
        rndNext();
    }
    return random_state % max;
}

inline double rnd() {
    return rnd(1<<30) / double(1<<30);
}

template<typename RIT>
void rndShuffle(RIT first, RIT last) {
    int n = last - first;
    for (int i=n-1; i>0; i--) {
        std::swap(first[i], first[rnd(i+1)]);
    }
}

template<typename T>
void rndShuffle(T& c) {
    rndShuffle(std::begin(c), std::end(c));
}

#endif
