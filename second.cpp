#include <cstring>
#include <algorithm>

void RemoveDups(char* str)
{
    auto str_length {strlen(str)};
    if (str_length < 2)
    {
        return;
    }
    else
    {
        // do nothing
    }
    auto begin {str};
    auto end {str + str_length};
    auto result {begin};

    while (++begin != end) {
        if ((*result != *begin) && (++result != begin)) {
            *result = std::move(*begin);
        }
        else{
            // do nothing
        }
    }
    auto offset = ++result - str;
    std::fill(str + offset, end, '\0');
}

int main() {
    char data[] = "aaaas    dds e r t uu ioii";
    RemoveDups(data);
    printf("%s\n", data);
    return 0;
}
