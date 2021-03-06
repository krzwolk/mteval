#include <mteval/utils.h>

using namespace std;

namespace MTEval {

Sentence Utility::makeNGram(const Sentence & sent, size_t begin, size_t n) {
    if (begin + n > sent.size()) throw runtime_error("out of range");
    Sentence ret(n);
    for (size_t i = 0; i < n; ++i) ret[i] = sent[i + begin];
    return ret;
}

int Utility::countOverlapping(const Sentence & pattern, const Sentence & sent) {
    int n = 0;
    int len_pattern = pattern.size();
    int max_k = sent.size() - len_pattern + 1;
    for (int k = 0; k < max_k; ++k) {
        int m = 1;
        for (int i = 0; i < len_pattern; ++i) {
            if (sent[k + i] != pattern[i]) {
                m = 0;
                break;
            }
        }
        n += m;
    }
    return n;
}

int Utility::findSubsentence(const Sentence & pattern, const Sentence & sent) {
    int len_pattern = pattern.size();
    int max_k = sent.size() - len_pattern + 1;
    for (int k = 0; k < max_k; ++k) {
        bool p = true;
        for (int i = 0; i < len_pattern; ++i) {
            if (sent[k + i] != pattern[i]) {
                p = false;
                break;
            }
        }
        if (p) return k;
    }
    return -1;
}

unique_ptr<ifstream> Utility::openInputStream(const string & filename) {
    unique_ptr<ifstream> ifs(new ifstream(filename));
    if (!ifs->is_open()) {
        throw runtime_error("could not open \"" + filename + "\"");
    }
    return ifs;
}

} // namespace MTEval

