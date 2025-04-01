#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define WIDTH 2000
#define HEIGHT 2000
#define MAX_ITER 200

const double C_RE = -0.8;
const double C_IM = 0.156;

int julia(double zx, double zy) {
    int iter = 0;
    while (zx*zx + zy*zy < 4.0 && iter < MAX_ITER) {
        double tmp = zx*zx - zy*zy + C_RE;
        zy = 2.0*zx*zy + C_IM;
        zx = tmp;
        iter++;
    }
    return iter;
}

int main() {
    unsigned char *image = malloc(WIDTH * HEIGHT);
    if (!image) {
        perror("Erreur d'allocation mémoire");
        return 1;
    }

    for (int threads = 1; threads <= 32; threads++) {
        omp_set_num_threads(threads);
        double total_time = 0.0;

        printf("== Using %d threads ==\n", threads);

        for (int iter = 1; iter <= 10; iter++) {
            double start = omp_get_wtime();

            #pragma omp parallel for schedule(static)
            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    double zx = 3.0 * ((double)x / WIDTH) - 1.5;
                    double zy = 3.0 * ((double)y / HEIGHT) - 1.5;

                    int val = julia(zx, zy);
                    unsigned char color = (val == MAX_ITER) ? 0 : 255 - (val * 255 / MAX_ITER);
                    image[y * WIDTH + x] = color;
                }
            }

            double end = omp_get_wtime();
            double elapsed = end - start;
            total_time += elapsed;
            // printf("  Iteration %d: %.4f seconds\n", iter, elapsed);
        }

        printf("Average time using %2d threads: %.4f seconds\n\n", threads, total_time / 10.0);
    }

    // Save one image (from the last run)
    FILE *f = fopen("julia.pgm", "wb");
    if (!f) {
        perror("Impossible d’ouvrir le fichier de sortie");
        free(image);
        return 1;
    }

    fprintf(f, "P5\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(image, sizeof(unsigned char), WIDTH * HEIGHT, f);
    fclose(f);

    free(image);
    printf("Image générée : julia.pgm\n");
    return 0;
}