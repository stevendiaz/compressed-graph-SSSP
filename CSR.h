#include <stdint.h>
#include <stdlib.h>
#include <vector>


using namespace std;

class CSR {
    private:
        vector<int32_t> value;
        vector<int32_t> IA;
        vector<int32_t> JA;
        int32_t num_rows;
        int32_t num_cols;

    public:
        CSR (string::size_type size) {
            IA = IA(size, 0);
            num_rows = (int32_t)size;
            num_cols = (int32_t)size;
            cout "rows: " << num_rows << endl;
        }

        void put (int32_t x, int32_t y, int32_t v) {
            int32_t i;
            for (i = x + 1; i < num_rows + 1; ++i) {
                IA.at(i) += 1;
            }

            int32_t previous_row_values_count = IA.at(x);

            bool inserted;
            int32_t j;
            for (j = previous_row_values_count; j < IA.at(x + 1) - 1; ++i) {
                if (JA.at(j) > y) {
                    JA.at(j) = y;
                    value.at(j) = v;
                    inserted = 1;
                    break;
                }
                else if (JA.at(j) == y) {
                    inserted = 1;
                    value.at(j) = v;
                    break;
                }
            }

            if (!inserted) {
                int32_t idx = IA.at(x + 1) - 1;
                if (JA.size() == 0 && value.size() == 0) {
                    JA.push_back(y);
                    value.push_back(v);
                }
                else {
                    JA.at(idx) = y;
                    value.at(idx) = v;
                }
            }
        }

        int32_t get(int32_t x, int32_t y) {
            int32_t prev_row_values_count = IA.at(x);
            int32_t current_row_valid_count = IA.at(x + 1);

            int32_t i;
            int32_t result;
            for(i = prev_row_values_count; i < current_row_valid_count; ++i) {
                if (IA.at(i) == y) {
                    result = value.at(i);
                    break;
                }
                else {
                    result = 0;
                    break;
                }
            }
            return result;
        }
};
