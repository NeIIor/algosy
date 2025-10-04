#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void fast_sort(unsigned *begin, unsigned *end) {
    size_t n = (size_t)(end - begin);
    if (n <= 1) return;
    
    if (n <= 48) {
        for (size_t i = 1; i < n; i++) {
            unsigned key =  begin[i];
            size_t j = i;
            while (j > 0 && begin[j-1] > key) {
                begin[j] =  begin[j-1];
                j--;
            }
            begin[j] = key;
        }
        return;
    }

    const size_t BUCKETS = 256;
    size_t count[4][256] = {0};
    unsigned *temp = (unsigned*)malloc(n * sizeof(unsigned));
    
    if (!temp) return;

    unsigned *src = begin, *dst = temp;

    for (size_t i = 0; i < n; i++) {
        unsigned val = src[i];
        count[0][(val >> 0 ) & 0xFF]++;
        count[1][(val >> 8 ) & 0xFF]++;
        count[2][(val >> 16) & 0xFF]++;
        count[3][(val >> 24) & 0xFF]++;
    }

    for (int shift = 0; shift < 32; shift += 8) {
        int byte_idx = shift >> 3;
        
        size_t pos = 0;
        for (size_t i = 0; i < BUCKETS; i++) {
            size_t c = count[byte_idx][i];
            count[byte_idx][i] = pos;
            pos += c;
        }
        
        for (size_t i = 0; i < n; i++) {
            unsigned char key = (src[i] >> shift) & 0xFF;
            dst[count[byte_idx][key]++] = src[i];
        }
        
        unsigned *tmp = src;
        src = dst;
        dst = tmp;
    }

    if (src == temp) {
        memcpy(begin, temp, n * sizeof(unsigned));
    }

    free(temp);
}


// int main() {
//     unsigned array[8] = {3,1,4,1,5,9,2,6};
//     fast_sort(array, array+8);
//     for (int i = 0; i < 8; i++) {
//         printf("%u\n", array[i]);
//     }
// }