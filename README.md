# random
What is normally needed for random numbers

     // The random state generator (one per thread)
     // auto-initialized from current epoch in milliseconds
     // on thread start
     thread_local unsigned random_state;

     // Returns an uniform random number x ∈ [0 ... max[
     unsigned rnd(int max);

     // Returns an uniform floating point number x ∈ [0.0 ... 1.0[
     double rnd();

     // Randomly shuffles [first ... last[
     template<typename RIT>
     void rndShuffle(RIT first, RIT last);

     // Randomly shuffles [std::begin(c) ... std::end(c)[
     template<typename T>
     void rndShuffle(T& c);
