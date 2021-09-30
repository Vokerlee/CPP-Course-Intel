#include "2q_cache.hpp"
#include "gen_test.hpp"

int main()
{
    cch::CacheGen<int> test(10000, 800);
    cch::Cache_2Q<int> cache_test(800);

    std::ofstream fout_test;
    fout_test.open("../tests/10k.txt");

    //test.print_data();
    test.test_cache(cache_test);
    test.print_test_file(cache_test, fout_test);

    //cache_test.print();

    fout_test.close();

    return 0;
}
