#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

std::string lookandsay(const std::string& str) {
    std::ostringstream newseq;

    auto pos = begin(str);
    while (pos < end(str)) {
        auto new_pos = std::find_if_not(pos, end(str), [=](char c) {return c == *pos; });
        newseq << std::distance(pos, new_pos) << *pos;
        pos = new_pos;
    }

    return newseq.str();
}


int main() {
    std::string laf = "1113122113";

    for (int i = 0; i < 50; i++) {
        laf = lookandsay(laf);
    }
    std::cout << laf.size() << std::endl;

    return 0;
}