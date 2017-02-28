#include <stdint.h>
#include <stdlib.h>
#include <vector>


using namespace std;

#include <iostream>

class CSR {
    private:
        vector<int32_t> value;
        vector<int32_t> IA;
        vector<int32_t> JA;
        int32_t num_rows;
        int32_t num_cols;

    public:
        CSR (int32_t size) {
            IA.resize(size + 1);
            num_rows = (int32_t)size;
            num_cols = (int32_t)size;
            std::cout << "rows: " << num_rows << std::endl;
        }

        vector< vector<int32_t> > iterate() {
            vector< vector<int32_t> > result;
            for(uint32_t i = 0; i < IA.size(); ++i) {
                if(i == 0)
                    continue;
                int32_t current_row_index = 0;
                while (current_row_index < IA.at(i) - IA.at(i - 1)) {
                    int32_t row_value = i - 1;
                    int32_t col_value = JA.at(IA.at(i - 1) + current_row_index);
                    int32_t real_value = value.at(IA.at(i - 1) + current_row_index);
                    vector<int32_t> pairing(3);
                    pairing.at(0) = row_value;
                    pairing.at(1) = col_value;
                    pairing.at(2) = real_value;
                    result.push_back(pairing);
                    current_row_index += 1;
                }
            }
            return result;
        }

        void put (int32_t x, int32_t y, int32_t v) {
            int32_t i;
            for (i = x + 1; i < num_rows + 1; ++i) {
                std::cout << "IA size line27: " << IA.size() << std::endl;
                std::cout << "index of IA: " << i << std::endl; 
                IA.at(i) += 1;
            }

            int32_t previous_row_values_count = IA.at(x);

            bool inserted = 0;
            int32_t j;
            std::cout << "i: " << previous_row_values_count << " j: " << IA.at(x + 1) - 1 << std::endl;
            for (j = previous_row_values_count; j < IA.at(x + 1) - 1; ++j) {
                cout << "Loop Enter" << endl;
                cout << "Index: " << j << " JA size: " << JA.size() << " Val size: " << value.size() << endl;
                if (JA.at(j) > y) {
                    vector<int32_t>::iterator JA_it = JA.begin(); 
                    vector<int32_t>::iterator value_it = value.begin();
                    JA.insert(JA_it + j, y);
                    value.insert(value_it + j, v);
                    inserted = 1;
                    break;
                }
                else if (JA.at(j) == y) {
                    inserted = 1;
                    vector<int32_t>::iterator value_it = value.begin();
                    value.insert(value_it+j, v);
                    break;
                }
            }

            if (!inserted) {
                int32_t idx = IA.at(x + 1) - 1;
                cout << "Line 62: index: " << idx << " JA size: " << JA.size() << " val size: " << value.size() << endl;
                if (JA.size() == 0 && value.size() == 0) {
                    JA.push_back(y);
                    value.push_back(v);
                }
                else if((int)JA.size() == idx && (int)value.size() == idx) {
                    JA.push_back(y);
                    value.push_back(v);
                }
                else {
                    vector<int32_t>::iterator JA_it = JA.begin();
                    vector<int32_t>::iterator value_it = value.begin();
                    JA.insert(JA_it + idx, y);
                    value.insert(value_it + idx, v);
                }
            }
            //cout << "val: ";
            //for (std::vector<int32_t>::const_iterator i = value.begin(); i != value.end(); ++i)
            //    std::cout << *i << ' ';
            //cout << endl;
            //cout << "IA: ";
            //for (std::vector<int32_t>::const_iterator i = IA.begin(); i != IA.end(); ++i)
            //    std::cout << *i << ' ';
            //cout << endl;
            //cout << "JA: ";
            //for (std::vector<int32_t>::const_iterator i = JA.begin(); i != JA.end(); ++i)
            //    std::cout << *i << ' ';
            //cout << endl;
        }

        int32_t get(int32_t x, int32_t y) {
            int32_t prev_row_values_count = IA.at(x);
            int32_t current_row_valid_count = IA.at(x + 1);
            int32_t i;
            for(i = prev_row_values_count; i < current_row_valid_count; ++i) {
                if (JA.at(i) == y) {
                    return  value.at(i);
                }
            }
            return -1;
        }
};
