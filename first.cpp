#include <vector>
#include <iostream>
#include <algorithm>

void PrintBinary(long long dec_num)
{
    auto negative = dec_num < 0;
    if (negative)
    {
        dec_num = -dec_num;
    }
    else
    {
        // do nothing
    }

    auto get_digit_of_dec_num = [dec_num]() mutable -> size_t {
        size_t digit_of_num {0};
        while (dec_num > 1)
        {
            dec_num >>=  1;
            ++digit_of_num;
        }
        return digit_of_num;
    };

    std::vector<bool> bin_vector (64U, false);
    size_t count {0};

    while (dec_num > 0)
    {
        bin_vector[count] = dec_num % 2;
        dec_num /= 2;
        ++count;
    }
    std::reverse(std::begin(bin_vector), std::end(bin_vector));

    if (!negative)
    {
        auto offset {get_digit_of_dec_num() + 1};
        std::copy(std::end(bin_vector) - offset, std::end(bin_vector), std::ostream_iterator<bool>(std::cout));
    }
    else
    {
        if (bin_vector.back())
        {
            std::for_each(std::begin(bin_vector), std::end(bin_vector) - 1, [bin_vector](auto& elem){ elem = !elem;});
        }
        else
        {
            std::for_each(std::rbegin(bin_vector), std::rend(bin_vector), [flag = true](auto& elem) mutable {
                elem = !elem;
                if (flag && elem)
                {
                    elem = false;
                    flag = true;
                }
                else if (flag && !elem){
                    elem = true;
                    flag = false;
                }
                else
                {
                    // do nothing
                }
            });
        }
        std::copy(std::begin(bin_vector), std::end(bin_vector), std::ostream_iterator<bool>(std::cout));
    }
}
int main() {
    long long dec_num;
    std::cin >> dec_num;

    PrintBinary(dec_num);

    return 0;
}
