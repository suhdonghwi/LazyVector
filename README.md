# lazy_vector
Implementation of lazy evaluation to C++ std::vector.


# Example usage

Fibonacci sequence
``` C++
int main()
{
	std::vector<uint64_t> fib_vec = { 0, 1 };
	auto fib_lv = lazy_vector<uint64_t>(fib_vec, [](auto lv, std::size_t index)
	{
		return lv[index - 2] + lv[index - 1];
	});

	for (std::size_t i = 0; i < 50; i++)
	{
		std::cout << fib_lv[i] << std::endl;
	}
}
```

Getting lazy vector of prime numbers.
``` C++
template <class IntType>
bool is_prime(IntType num) 
{
    if (num <= 3) return num > 1;
    else if (num % 2 == 0 || num % 3 == 0) return false;
    else 
    {
        for (int i = 5; i * i <= num; i += 6) 
        {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }
} //http://codereview.stackexchange.com/questions/84052/checking-if-a-number-is-prime
 
int main()
{
    std::vector<uint64_t> range_vec;
    auto lv = lazy_range(range_vec, 1ULL);
 
    std::vector<std::optional<uint64_t>> primes_vec;
    auto primes_lv = LAZY_COMP(primes_vec, lv, [&lv](auto cur, std::size_t i)
    {
        if (is_prime(lv[i]))
        {
            return std::optional<uint64_t>(i);
        }
        else return std::optional<uint64_t>();
    });
 
    for (std::size_t i = 0; i < 100; i++)
    {
        if(primes_lv[i])
            std::cout << primes_lv[i].value() << std::endl;
    }
}
```

Note that std::optional is C++1z feature.
