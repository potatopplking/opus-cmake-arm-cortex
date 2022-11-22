#include <stdio.h>
#include <opus.h>

int main(void)
{
    printf("Size of encoder: %d B\n", opus_encoder_get_size(2));
    return 0;
}
