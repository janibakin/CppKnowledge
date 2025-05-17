/*
According to the C++23 standard, what is the output of this program?
*/

#include <algorithm>
#include <iostream>

int main() {
    int x = 10;
    int y = 10;

    const int &max = std::max(x, y);
    const int &min = std::min(x, y);

    x = 11;
    y = 9;

    std::cout << max << min;
}

/*
Answer
The program is guaranteed to output: 1111

Explanation
std::min() and std::max() return references to their smallest/largest arguments, respectively. But what if they're equal?

The C++ standard says both for std::min() and for std::max():

Returns the first argument when the arguments are equivalent.

So both the evaluation of std::max(x, y) and std::min(x, y) return x, and both references max and min are bound to x.

We then set x to 11, and print max and min, which are now both 11.

Some say it would be better if min() returned its first element, but max() returned its last element. Sean Parent explains his rationale for this in his BoostCon 2016 Keynote Better Code.
*/
