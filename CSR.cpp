#include <cstdint>
#include <stdlib.h>
#include <vector>

class CSR {
    private:
        std::vector<int32_t> value;
        std::vector<int32_t> IA;
        std::vector<int32_t> JK;
        int32_t num_rows;
        int32_t num_cols;

    public:
        CSR(int num_rows);
};

CSR::CSR(int num_rows) {
    std::fill(IA.begin(), IA.end(), 0);
    num_rows = num_rows;
    num_cols = num_rows;
}

int main() {
    return 0;
}
